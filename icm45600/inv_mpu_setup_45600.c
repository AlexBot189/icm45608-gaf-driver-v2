/*
 * Copyright (C) 2017-2021 InvenSense, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#define pr_fmt(fmt) "inv_mpu: " fmt
#include <linux/math64.h>
#include "../inv_mpu_iio.h"
#include "inv_mpu_gaf.h"

static int inv_get_actual_duration(int rate)
{
	int duration_ns;

	if (rate > 400)
		duration_ns = 1250000;
	else if (rate > 200)
		duration_ns = 2500000;
	else if (rate > 100)
		duration_ns = 5000000;
	else if (rate > 50)
		duration_ns = 10000000;
	else if (rate > 25)
		duration_ns = 20000000;
	else if (rate > 12)
		duration_ns = 40000000;
	else if (rate > 6)
		duration_ns = 80000000;
	else if (rate > 3)
		duration_ns = 160000000;
	else
		duration_ns = 320000000;

	return duration_ns;
}

static int inv_calc_engine_dur(struct inv_mpu_state *st,
				struct inv_engine_info *ei)
{
	if (!ei->running_rate)
		return -EINVAL;
	ei->dur = ei->base_time / ei->orig_rate;
	ei->dur *= ei->divider;

	return 0;
}

int inv_flush_fifo(struct inv_mpu_state *st)
{
	int res = 0;
	u8 v;
	int i;

	res = inv_plat_read(st, REG_FIFO_CONFIG2_DREG_BANK1, 1, &v);
	v |=  (u8)BIT_FIFO_FLUSH;
	res |= inv_plat_single_write(st, REG_FIFO_CONFIG2_DREG_BANK1, v);
	msleep(10);

	/* Wait for FIFO flush (idle bit will go high at appropriate time and unlock flush) */
	res = 0;
	i = 0;
	while((res == 0) &&
		((v & REG_FIFO_CONFIG2_FIFO_FLUSH_MASK) == (uint8_t)BIT_FIFO_FLUSH)) {
		res = inv_plat_read(st, REG_FIFO_CONFIG2_DREG_BANK1, 1, &v);
		usleep_range(1000, 2000);
		pr_debug("flush_fifo=%x\n", v);
		i++;
		if (i > 50) {
			pr_err("error in flush FIFO\n");
			return -EINVAL;
		}
	}

	return res;
}

static int dis_i2cm_block(struct inv_mpu_state *st)
{
	int rc = 0;
	u8 data;

	pr_debug("disable i2cm block\n");
	/* override AUX1 to disable AUX1 */
	rc |= inv_plat_read(st, REG_IOC_PAD_SCENARIO_AUX_OVRD_DREG_BANK1, 1, &data);
	data &= (~REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_VAL_MASK);
	data |= REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_MASK;
	rc |= inv_plat_single_write(st, REG_IOC_PAD_SCENARIO_AUX_OVRD_DREG_BANK1, data);

	return rc;
}

static int init_i2cm_block(struct inv_mpu_state *st)
{
	int rc = 0;
	u8 data;

	/* Configure AUX1 pads for I2CM (match MCU inv_imu_init_i2cm: only mode bits) */
	rc |= inv_plat_read(st, REG_IOC_PAD_SCENARIO_AUX_OVRD_DREG_BANK1, 1, &data);
	data |= REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_MODE_OVRD_MASK |
		(1 << REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_MODE_OVRD_VAL_POS) |
		REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_MASK |
		REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_VAL_MASK;
	rc |= inv_plat_single_write(st, REG_IOC_PAD_SCENARIO_AUX_OVRD_DREG_BANK1, data);

	/* Use reStart to bridge register address W and register data R transition */
	rc |= inv_ireg_read(st, REG_I2CM_CONTROL_IPREG_TOP1, 1, &data);
	data |= REG_I2CM_CONTROL_I2CM_RESTART_EN_MASK;
	data |= REG_I2CM_CONTROL_I2CM_SPEED_MASK;
	//data |= (REG_I2CM_CONTROL_I2CM_GO_MASK |
	//		REG_I2CM_CONTROL_I2CM_SPEED_MASK);
	rc |= inv_ireg_single_write(st, REG_I2CM_CONTROL_IPREG_TOP1, data);


	return rc;
}

static int inv_resume_i2cm(struct inv_mpu_state *st)
{
	int res;

	res = init_i2cm_block(st);

	return res;
}

/* ES0(external sensor 0) can only be used for compass. It supports 6 or 9 bytes.
 * ES1 is only used for pressure. It only has 6 bytes  mode */
static int inv_turn_on_fifo(struct inv_mpu_state *st)
{
	int r;
	u8 int1_config0 = 0;
	u8 fifo_config3 = 0;
	u8 v;

	inv_plat_read(st, REG_FIFO_CONFIG3_DREG_BANK1, 1, &v);
	v &= (~REG_FIFO_CONFIG3_FIFO_IF_EN_MASK);
	pr_debug("disable FIFO interface=%x\n", v);
	r = inv_plat_single_write(st, REG_FIFO_CONFIG3_DREG_BANK1, v);
	if (r)
		return r;

	inv_flush_fifo(st);

	if (st->gesture_only_on && (!st->batch.timeout)) {
		if (st->chip_config.stationary_detect_enable)
			st->gesture_int_count = STATIONARY_DELAY_THRESHOLD;
		else
			st->gesture_int_count = WOM_DELAY_THRESHOLD;

		r = inv_set_accel_intel(st);
		if (r)
			return r;
	}

	if (!st->gesture_only_on) {
		if (st->sensor[SENSOR_GYRO].on ||
			st->sensor[SENSOR_ACCEL].on ||
			st->sensor[SENSOR_COMPASS].on ||
			st->sensor[SENSOR_PRESSURE].on) {
			if (st->chip_config.eis_enable)
				int1_config0 |= BIT_INT1_STATUS_EN_AP_FSYNC;
			int1_config0 |= (BIT_INT1_STATUS_EN_FIFO_THS |
					BIT_INT1_STATUS_EN_FIFO_FULL);
		}
		/* FIFO config4 is set to 0 since we select 6B for ES */
		if (st->sensor[SENSOR_GYRO].on)
			fifo_config3 |= BIT_FIFO_GYRO_EN;

		if (st->sensor[SENSOR_ACCEL].on)
			fifo_config3 |= BIT_FIFO_ACCEL_EN;

		if (st->chip_config.high_res_mode)
			fifo_config3 |= BIT_FIFO_HIRES_EN;

		if (st->sensor[SENSOR_COMPASS].on ||
		    st->chip_config.gaf_enabled)
			fifo_config3 |= REG_FIFO_CONFIG3_FIFO_ES0_EN_MASK;

		if (st->sensor[SENSOR_PRESSURE].on ||
		    st->chip_config.gaf_enabled)
			fifo_config3 |= REG_FIFO_CONFIG3_FIFO_ES1_EN_MASK;

		if (st->sensor[SENSOR_GYRO].on ||
			st->sensor[SENSOR_ACCEL].on ||
			st->sensor[SENSOR_COMPASS].on ||
			st->sensor[SENSOR_PRESSURE].on)
			fifo_config3 |= BIT_FIFO_IF_EN;
	}

	pr_debug("final fifo_config3=%x\n", fifo_config3);

	r = inv_plat_single_write(st, REG_FIFO_CONFIG3_DREG_BANK1, fifo_config3);
	if (r)
		return r;

	/* GAF: ES0 must be 9-byte mode */
	if (st->chip_config.gaf_enabled)
		inv_plat_single_write(st, REG_FIFO_CONFIG4_DREG_BANK1,
				     REG_FIFO_CONFIG4_FIFO_ES0_6B_9B_MASK);

	r = inv_plat_single_write(st, REG_FIFO_CONFIG1_0_DREG_BANK1,
		st->batch.fifo_wm_th & 0xff);
	if (r)
		return r;
	r = inv_plat_single_write(st, REG_FIFO_CONFIG1_1_DREG_BANK1,
		(st->batch.fifo_wm_th >> 8) & 0xff);
	if (r)
		return r;

	r = inv_plat_single_write(st, REG_INT1_CONFIG0_DREG_BANK1, int1_config0);
	if (r)
		return r;

	return r;
}

/*
 *  inv_reset_fifo() - Reset FIFO related registers.
 */
int inv_reset_fifo(struct inv_mpu_state *st, bool turn_off)
{
	int r, i;
	struct inv_timestamp_algo *ts_algo = &st->ts_algo;
	int accel_rate, gyro_rate;

	r = inv_turn_on_fifo(st);
	if (r)
		return r;

	ts_algo->last_run_time = get_time_ns();
	ts_algo->reset_ts = ts_algo->last_run_time;

	accel_rate = 800 / st->eng_info[ENGINE_ACCEL].divider;
	gyro_rate = 800 / st->eng_info[ENGINE_GYRO].divider;

	if (accel_rate >= 800)
		ts_algo->first_drop_samples[SENSOR_ACCEL] =
			FIRST_DROP_SAMPLES_ACC_800HZ;
	else if (accel_rate >= 200)
		ts_algo->first_drop_samples[SENSOR_ACCEL] =
			FIRST_DROP_SAMPLES_ACC_200HZ;
	else
		ts_algo->first_drop_samples[SENSOR_ACCEL] = 1;

	if (gyro_rate >= 800)
		ts_algo->first_drop_samples[SENSOR_GYRO] =
			FIRST_DROP_SAMPLES_GYR_800HZ;
	else if (gyro_rate >= 200)
		ts_algo->first_drop_samples[SENSOR_GYRO] =
			FIRST_DROP_SAMPLES_GYR_200HZ;
	else
		ts_algo->first_drop_samples[SENSOR_GYRO] = 1;

	ts_algo->first_drop_samples[SENSOR_COMPASS] = 0;
	ts_algo->first_drop_samples[SENSOR_PRESSURE] = 0;

	st->last_temp_comp_time = ts_algo->last_run_time;
	st->left_over_size = 0;
	for (i = 0; i < SENSOR_NUM_MAX; i++) {
		st->sensor[i].calib_flag = 0;
		st->sensor[i].sample_calib = 0;
		st->sensor[i].time_calib = ts_algo->last_run_time;
	}

	ts_algo->calib_counter = 0;

	return 0;
}

static int select_rcosc(struct inv_mpu_state *st)
{
	int status = 0;
	u8 data;

	pr_debug("select_rcosc\n");

	status |= inv_ireg_read(st, REG_SMC_CONTROL_0_IPREG_TOP1, 1, &data);
	data &= ~REG_SMC_CONTROL_0_ACCEL_LP_CLK_SEL_MASK;
	data |= BIT_ACCEL_LP_CLK_SEL;
	status |= inv_ireg_single_write(st, REG_SMC_CONTROL_0_IPREG_TOP1, data);
	return status;
}

static int select_wuosc(struct inv_mpu_state *st)
{
	int status = 0;
	u8 data;

	pr_debug("select_wuosc\n");

	status |= inv_ireg_read(st, REG_SMC_CONTROL_0_IPREG_TOP1, 1, &data);
	data &= ~REG_SMC_CONTROL_0_ACCEL_LP_CLK_SEL_MASK;
	data |= SMC_CONTROL_ACCEL_CLK_WUOSC;
	status |= inv_ireg_single_write(st, REG_SMC_CONTROL_0_IPREG_TOP1, data);

	return status;
}

#if 0
static int inv_set_pwr_reg(struct inv_mpu_state *st,
		u8 PWR_MGMT0_reg, u8 accel_mode, u8 gyro_mode) {
	/* we do not need to wait for gyro/accel start up time
	 * because the setup is not finished here. By the time the setup
	 * is finished, the time is longer or equal than the start up time */
	return inv_plat_single_write(st,
				REG_PWR_MGMT0_DREG_BANK1, PWR_MGMT0_reg);
}
#else
#define PLATFORM_WAIT_TIME  0
#define GYRO_START_TIME (35 - PLATFORM_WAIT_TIME)
#define ACCEL_START_TIME (10 - PLATFORM_WAIT_TIME)

static int inv_set_pwr_reg(struct inv_mpu_state *st,
		u8 PWR_MGMT0_reg, u8 accel_mode, u8 gyro_mode)
{
	u8 cur_gyro;
	u8 cur_accel;
	int wait_time;
	int status;

	cur_accel = (PWR_MGMT0_reg & REG_PWR_MGMT0_ACCEL_MODE_MASK);
	cur_gyro  = (PWR_MGMT0_reg & REG_PWR_MGMT0_GYRO_MODE_MASK);
	wait_time = 0;

	if ((cur_accel == 0) && (cur_gyro == 0)) {
		//all set to off. no wait time
	} else if (cur_accel == 0) {
		if (cur_gyro != gyro_mode)
			wait_time = GYRO_START_TIME;
	} else if (cur_gyro == 0) {
		if (cur_accel != accel_mode)
			wait_time = ACCEL_START_TIME;
	} else {
		//both gyro and accel on
		if (cur_gyro != gyro_mode)
			wait_time = GYRO_START_TIME;
		if (cur_accel != accel_mode)
			wait_time = max(wait_time, ACCEL_START_TIME);
	}

	pr_debug("write pwr_reg=%x, wait=%d\n", PWR_MGMT0_reg, wait_time);
	status = inv_plat_single_write(st,
				REG_PWR_MGMT0_DREG_BANK1, PWR_MGMT0_reg);
	if (wait_time > 0)
		msleep(wait_time);

	return status;
}
#endif

static int inv_switch_gyro_accel_engine(struct inv_mpu_state *st)
{
	int status = 0;
	u8 accel_mode;
	u8 gyro_mode;
	uint8_t PWR_MGMT0_reg = 0;
	u8 set_rc_clock;

	status |= select_rcosc(st);

	status |= inv_plat_read(st, REG_PWR_MGMT0_DREG_BANK1, 1, &PWR_MGMT0_reg);
	accel_mode = (PWR_MGMT0_reg & REG_PWR_MGMT0_ACCEL_MODE_MASK);
	gyro_mode = (PWR_MGMT0_reg & REG_PWR_MGMT0_GYRO_MODE_MASK);
	set_rc_clock = 0;

	PWR_MGMT0_reg &= (~REG_PWR_MGMT0_ACCEL_MODE_MASK);
	PWR_MGMT0_reg &= (~REG_PWR_MGMT0_GYRO_MODE_MASK);

	// when gyro is on, both accel and gyro are set to LN; CLOCK is RC
	if (st->chip_config.gyro_enable) {
		PWR_MGMT0_reg |= BIT_GYRO_MODE_LN;
		if (st->chip_config.accel_enable)
			PWR_MGMT0_reg |= BIT_ACCEL_MODE_LN;
		status |= inv_set_pwr_reg(st, PWR_MGMT0_reg,
						accel_mode, gyro_mode);

		return status;
	}

	// gyro off, accel is on;
	if (st->chip_config.accel_enable) {
		if ((st->eng_info[ENGINE_ACCEL].running_rate <= 400) &&
				(st->chip_config.slave_enable == 0)) {
			if (st->chip_config.clk_sel)
				set_rc_clock = 1;
			PWR_MGMT0_reg |= BIT_ACCEL_MODE_LP;
		} else {
			set_rc_clock = 1;
			if (st->eng_info[ENGINE_ACCEL].running_rate <= 400)
				PWR_MGMT0_reg |= BIT_ACCEL_MODE_LP;
			else
				PWR_MGMT0_reg |= BIT_ACCEL_MODE_LN;
		}
		status |= inv_set_pwr_reg(st, PWR_MGMT0_reg,
						accel_mode, gyro_mode);
		if (set_rc_clock == 0)
			status |= select_wuosc(st);

		return status;
	}

	// both gyro and accel off, external sensor is on. clock is RC;
	if (st->chip_config.slave_enable) {
		status |= inv_set_pwr_reg(st, PWR_MGMT0_reg,
						accel_mode, gyro_mode);
		return status;
	}
	// all off. clock is WU;
	status |= inv_set_pwr_reg(st, PWR_MGMT0_reg, accel_mode, gyro_mode);
	status |= select_wuosc(st);

	return status;
}

int inv_imu_run_internal_stc(struct inv_mpu_state *st)
{
	int res = 0;
	int i;
	u8     reg_host_msg;
	u8 int_apex_config1, value;
	u8 v3;

	/* Configure start addresses as we reset the device */
	res = inv_mpu_configure_dmp(st);
	if (res)
		return res;


	res = inv_plat_read(st, REG_REG_HOST_MSG_DREG_BANK1, 1, &reg_host_msg);
	if (res)
		return res;
	reg_host_msg |= REG_REG_HOST_MSG_TESTOPENABLE_MASK;
	res = inv_plat_single_write(st, REG_REG_HOST_MSG_DREG_BANK1, reg_host_msg);
	if (res)
		return res;

	int_apex_config1 = 0xff;
	int_apex_config1 &= (~REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SELFTEST_DONE_MASK);
	res = inv_plat_single_write(st, REG_INT_APEX_CONFIG1_DREG_BANK1, int_apex_config1);
	if (res)
		return res;

	/* unmask the 16_23 interrupt to enable on demand interrupt */
	res = inv_ireg_read(st, REG_STATUS_MASK_PIN_16_23_IPREG_TOP1, 1, &value);
	if (res)
		return res;
	value &= (~REG_STATUS_MASK_PIN_16_23_INT_ON_DEMAND_PIN_2_DIS_MASK);
	res = inv_ireg_single_write(st, REG_STATUS_MASK_PIN_16_23_IPREG_TOP1, value);
	if (res)
		return res;

	/* enable eDMP running */
	res = inv_plat_read(st, REG_EDMP_APEX_EN1_DREG_BANK1, 1, &value);
	if (res)
		return res;
	value |= (REG_EDMP_APEX_EN1_EDMP_ENABLE_MASK) ;
	res = inv_plat_single_write(st, REG_EDMP_APEX_EN1_DREG_BANK1, value);
	if (res)
		return res;

	/* enable on demand running */
	res = inv_plat_read(st, REG_REG_HOST_MSG_DREG_BANK1, 1, &value);
	if (res)
		return res;
	value |= REG_REG_HOST_MSG_EDMP_ON_DEMAND_EN_MASK;
	res = inv_plat_single_write(st, REG_REG_HOST_MSG_DREG_BANK1, value);
	if (res)
		return res;

	msleep(100);

	value  = 0;

	i = 0;
	v3 = 0;
	while (1) {
		if(value & REG_INT_APEX_STATUS1_INT_STATUS_SELFTEST_DONE_MASK) {
				break;
		}
		res = inv_plat_read(st, REG_INT_APEX_STATUS1_DREG_BANK1, 1, &value);
		if (res)
			return res;
		msleep(100);
		i++;
		if (i > 30) {
			pr_info("too long\n");
			break;
		}
		if (value != 0)
			pr_info("int status=%x\n", value);
	}

	/* disable interrupt */
	res = inv_plat_read(st, REG_INT_APEX_CONFIG1_DREG_BANK1, 1, &int_apex_config1);
	if (res)
		return res;
	int_apex_config1 |= REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SELFTEST_DONE_MASK;

	res = inv_plat_single_write(st, REG_INT_APEX_CONFIG1_DREG_BANK1, int_apex_config1);
	if (res)
		return res;

	return 0;
}

int inv_stop_dmp(struct inv_mpu_state *st)
{
	int r, i;
	u8 v;

	/* mask the eDMP wake up source */
	v = 0xff;
	inv_ireg_single_write(st, REG_STATUS_MASK_PIN_0_7_IPREG_TOP1, v);
	inv_ireg_single_write(st, REG_STATUS_MASK_PIN_8_15_IPREG_TOP1, v);

	v = REG_I2CM_STATUS_I2CM_BUSY_MASK;
	i = 0;
	while ((v & REG_I2CM_STATUS_I2CM_BUSY_MASK) != 0) {
		r = inv_ireg_read(st, REG_I2CM_STATUS_IPREG_TOP1, 1, &v);
		if (r)
			return r;

		i++;
		usleep_range(1000, 2000);
		if (i > 100) {
			pr_err("error waiting for I2CM status\n");
			return -EINVAL;
		}
	}

	r = inv_plat_single_write(st, REG_DMP_EXT_SEN_ODR_CFG_DREG_BANK1, 0);
	if (r)
		return r;

	v = 0;
	i = 0;
	while (!(v & REG_IPREG_MISC_EDMP_IDLE_MASK)) {
		usleep_range(5000, 7000);
		r = inv_ireg_read(st, REG_IPREG_MISC_IPREG_TOP1, 1, &v);
		if (r)
			return r;

		i++;
		if (i > 200) {
			pr_err("error wait for eDMP idle %d\n", i);
			return -EINVAL;
		}
	}

	r = inv_plat_read(st, REG_EDMP_APEX_EN1_DREG_BANK1, 1, &v);
	if (r)
		return r;

	v &= (~REG_EDMP_APEX_EN1_EDMP_ENABLE_MASK);
	r = inv_plat_single_write(st, REG_EDMP_APEX_EN1_DREG_BANK1, v);

	return r;
}

static int inv_turn_off_engine(struct inv_mpu_state *st)
{
	dis_i2cm_block(st);

	inv_switch_gyro_accel_engine(st);

	return 0;
}

static int inv_turn_on_engine(struct inv_mpu_state *st)
{
	int r;
	u8 w;

	inv_switch_gyro_accel_engine(st);

	if (st->chip_config.slave_enable) {
		inv_resume_i2cm(st);

		if(st->sensor[SENSOR_COMPASS].on)
			w = 1;
		else
			w = 0;
		r = inv_ireg_single_write(st, es0_compass_en, w);
		r = inv_ireg_read(st, REG_I2CM_COMMAND_1_IPREG_TOP1, 1, &w);
		if (r)
			return r;

		/* set end flag to 0 in case pressure is enabled */
		w &= (~REG_I2CM_COMMAND_1_ENDFLAG_1_MASK);
		if ((!st->chip_config.has_pressure) ||
			(!st->sensor[SENSOR_PRESSURE].on)) {
				w |= (1 << REG_I2CM_COMMAND_1_ENDFLAG_1_POS);
		}
		pr_debug("i2cm command1=%x\n", w);

		r = inv_ireg_single_write(st, REG_I2CM_COMMAND_1_IPREG_TOP1, w);
	} else {
		dis_i2cm_block(st);
	}

	return 0;
}

static int inv_setup_dmp_rate(struct inv_mpu_state *st)
{
	unsigned int sensor_div, engine_div;
	u64 tmp;
	int i;

	for (i = 0; i < SENSOR_NUM_MAX; i++) {
		if (st->sensor[i].on) {
			st->sensor[i].div = 1;
			/* use clock base engine and update with divider */
			sensor_div = st->eng_info[st->sensor[i].engine_base].divider;
			engine_div = st->eng_info[st->ts_algo.clock_base].divider;
			tmp = (u64)st->eng_info[st->ts_algo.clock_base].dur * (u64)sensor_div;
			st->sensor[i].dur = div_u64(tmp, engine_div);
		}
	}

	return 0;
}

static int inv_set_odr_and_filter(struct inv_mpu_state *st, int a_d, int g_d)
{
	int res;
	int accel_hz, gyro_hz;

	u8 a_odr, a_lpm_filter, a_lnm_filter;
	u8 g_odr, g_lpm_filter, g_lnm_filter;
	u8 data, accel_cfg, gyro_cfg;

	accel_hz = 800 / (a_d + 1);
	gyro_hz = 800 / (g_d + 1);
	pr_debug("accel hz=%d, gyro=%d\n", accel_hz, gyro_hz);

	/* accel ODR and filter */
	if (accel_hz > 400) {
		a_odr = BIT_SENSOR_ODR_800HZ;
		a_lnm_filter = BIT_ACC_UI_LPFBW_ODR_4;
		a_lpm_filter = BIT_ACC_LP_AVG_1X;
	} else if (accel_hz > 200) {
		a_odr = BIT_SENSOR_ODR_400HZ;
		a_lnm_filter = BIT_ACC_UI_LPFBW_ODR_4;
		a_lpm_filter = BIT_ACC_LP_AVG_1X;
	} else if (accel_hz > 100) {
		a_odr = BIT_SENSOR_ODR_200HZ;
		a_lnm_filter = BIT_ACC_UI_LPFBW_ODR_4;
		a_lpm_filter = BIT_ACC_LP_AVG_1X;
	} else if (accel_hz > 50) {
		a_odr = BIT_SENSOR_ODR_100HZ;
		a_lnm_filter = BIT_ACC_UI_LPFBW_ODR_4;
		a_lpm_filter = BIT_ACC_LP_AVG_1X;
	} else if (accel_hz > 25) {
		a_odr = BIT_SENSOR_ODR_50HZ;
		a_lnm_filter = BIT_ACC_UI_LPFBW_ODR_4;
		a_lpm_filter = BIT_ACC_LP_AVG_1X;
	} else if (accel_hz > 12) {
		a_odr = BIT_SENSOR_ODR_25HZ;
		a_lnm_filter = BIT_ACC_UI_LPFBW_ODR_4;
		a_lpm_filter = BIT_ACC_LP_AVG_4X;
	} else if (accel_hz > 6) {
		a_odr = BIT_SENSOR_ODR_12HZ;
		a_lnm_filter = BIT_ACC_UI_LPFBW_ODR_4;
		a_lpm_filter = BIT_ACC_LP_AVG_8X;
	} else if (accel_hz > 3) {
		a_odr = BIT_SENSOR_ODR_6HZ;
		a_lnm_filter = BIT_ACC_UI_LPFBW_ODR_4;
		a_lpm_filter = BIT_ACC_LP_AVG_64X;
	} else {
		a_odr = BIT_SENSOR_ODR_3HZ;
		a_lnm_filter = BIT_ACC_UI_LPFBW_ODR_4;
		a_lpm_filter = BIT_ACC_LP_AVG_64X;
	}

	/* gyro ODR and filter */
	if (gyro_hz > 400) {
		g_odr = BIT_SENSOR_ODR_800HZ;
		g_lnm_filter = BIT_GYR_UI_LPFBW_ODR_4;
		g_lpm_filter = BIT_GYR_LP_AVG_2X;
	} else if (gyro_hz > 200) {
		g_odr = BIT_SENSOR_ODR_400HZ;
		g_lnm_filter = BIT_GYR_UI_LPFBW_ODR_4;
		g_lpm_filter = BIT_GYR_LP_AVG_2X;
	} else if (gyro_hz > 100) {
		g_odr = BIT_SENSOR_ODR_200HZ;
		g_lnm_filter = BIT_GYR_UI_LPFBW_ODR_4;
		g_lpm_filter = BIT_GYR_LP_AVG_2X;
	} else if (gyro_hz > 50) {
		g_odr = BIT_SENSOR_ODR_100HZ;
		g_lnm_filter = BIT_GYR_UI_LPFBW_ODR_4;
		g_lpm_filter = BIT_GYR_LP_AVG_2X;
	} else if (gyro_hz > 25) {
		g_odr = BIT_SENSOR_ODR_50HZ;
		g_lnm_filter = BIT_GYR_UI_LPFBW_ODR_4;
		g_lpm_filter = BIT_GYR_LP_AVG_64X;
	} else if (gyro_hz > 12) {
		g_odr = BIT_SENSOR_ODR_25HZ;
		g_lnm_filter = BIT_GYR_UI_LPFBW_ODR_4;
		g_lpm_filter = BIT_GYR_LP_AVG_2X;
	} else if (gyro_hz > 6) {
		g_odr = BIT_SENSOR_ODR_12HZ;
		g_lnm_filter = BIT_GYR_UI_LPFBW_ODR_4;
		g_lpm_filter = BIT_GYR_LP_AVG_2X;
	} else if (gyro_hz > 3) {
		g_odr = BIT_SENSOR_ODR_6HZ;
		g_lnm_filter = BIT_GYR_UI_LPFBW_ODR_4;
		g_lpm_filter = BIT_GYR_LP_AVG_2X;
	} else {
		g_odr = BIT_SENSOR_ODR_3HZ;
		g_lnm_filter = BIT_GYR_UI_LPFBW_ODR_4;
		g_lpm_filter = BIT_GYR_LP_AVG_2X;
	}
	pr_debug("inv_lpm value:lpm=%d, g_odr=%d\n", a_lpm_filter, g_odr);

	/* update registers */
	res = inv_plat_read(st, REG_ACCEL_CONFIG0_DREG_BANK1, 1, &accel_cfg);
	accel_cfg &= (~REG_ACCEL_CONFIG0_ACCEL_ODR_MASK);
	data = (accel_cfg | a_odr);
	res = inv_plat_single_write(st, REG_ACCEL_CONFIG0_DREG_BANK1, data);
	if (res)
		return res;

	res = inv_plat_read(st, REG_ACCEL_CONFIG0_DREG_BANK1, 1, &gyro_cfg);
	gyro_cfg &= (~REG_GYRO_CONFIG0_GYRO_ODR_MASK);
	data = (gyro_cfg | g_odr);
	res = inv_plat_single_write(st, REG_GYRO_CONFIG0_DREG_BANK1, data);
	if (res)
		return res;

	res = inv_ireg_single_write(st, REG_IPREG_SYS2_REG_129_IPREG_SYS2, a_lpm_filter);
	if (res)
		return res;
	res = inv_ireg_single_write(st, REG_IPREG_SYS2_REG_131_IPREG_SYS2, a_lnm_filter);
	if (res)
		return res;

	res = inv_ireg_single_write(st, REG_IPREG_SYS1_REG_170_IPREG_SYS1, g_lpm_filter);
	if (res)
		return res;
	res = inv_ireg_single_write(st, REG_IPREG_SYS1_REG_172_IPREG_SYS1, g_lnm_filter);

	return res;
}

static int inv_set_batch(struct inv_mpu_state *st)
{
	int res = 0;
	u32 w;

	st->batch.pk_size = 0;
	if (st->sensor[SENSOR_ACCEL].on || st->sensor[SENSOR_GYRO].on) {
		if (st->chip_config.high_res_mode)
			st->batch.pk_size = 20;
		else {
			if (st->sensor[SENSOR_ACCEL].on)
				st->batch.pk_size += 8;
			if (st->sensor[SENSOR_GYRO].on)
				st->batch.pk_size += 8;
		}
	}
	if (st->sensor[SENSOR_COMPASS].on ^ st->sensor[SENSOR_PRESSURE].on) {
		st->batch.pk_size += 15;
		st->batch.pk_size /= 16;
		st->batch.pk_size *= 16;
		st->batch.pk_size += 16;
	}
	if (st->sensor[SENSOR_COMPASS].on & st->sensor[SENSOR_PRESSURE].on) {
		if (st->batch.pk_size > 0)
			st->batch.pk_size = 32;
		else
			st->batch.pk_size = 20;
	}

	/* GAF: ES0(9B) + ES1(6B) => 32-byte FIFO packet */
	if (st->chip_config.gaf_enabled &&
	    st->sensor[SENSOR_ACCEL].on && st->sensor[SENSOR_GYRO].on)
		st->batch.pk_size = 32;

	pr_debug("final_pk_size=%d\n", st->batch.pk_size);


	if (st->batch.timeout) {
		w = st->batch.timeout * st->batch.max_rate / 1000;
		if ((w * st->batch.pk_size) > MAX_BATCH_FIFO_SIZE)
			w = MAX_BATCH_FIFO_SIZE / st->batch.pk_size;
	} else {
		w = 1;
	}
	st->batch.fifo_wm_th = w;
	pr_debug("running= %d, pksize=%d, to=%d w=%d\n",
		st->batch.max_rate, st->batch.pk_size, st->batch.timeout, w);

	return res;
}

static int inv_set_rate(struct inv_mpu_state *st)
{
	int g_d, a_d, res;

	res = inv_setup_dmp_rate(st);
	if (res)
		return res;

	g_d = st->eng_info[ENGINE_GYRO].divider - 1;
	a_d = st->eng_info[ENGINE_ACCEL].divider - 1;

	res = inv_set_odr_and_filter(st, a_d, g_d);
	if (res)
		return res;

	res = inv_set_batch(st);

	return res;
}

static int inv_setup_tap(struct inv_mpu_state *st)
{
	u8 tmax = 124;
	u8 tmin = 24;
	u8 max_peak_tol = 2;
	u8 tavg = 8;
	u8 min_jerk = 3;
	u8 smudge = 23;
	s32 tmp32;

	pr_debug("setup tap\n");
	/* Tap parameters */
	tmp32 = min_jerk;
	inv_ireg_write(st, (u32)tap_min_jerk_thr, tap_min_jerk_thr_size, (u8 *)&tmp32);
	/*inv_imu_write_dmp_ram(s, (uint8_t *)&tmpvalue_32bit, (uint32_t)tap_min_jerk_thr, EDMP_tap_min_jerk_thr_size); */
	tmp32 = max_peak_tol;
	inv_ireg_write(st, (u32)tap_max_peak_tol, tap_max_peak_tol_size, (u8 *)&tmp32);
	//inv_imu_write_dmp_ram(s, (uint8_t *)&tmpvalue_32bit, (uint32_t)EDMP_tap_max_peak_tol, EDMP_tap_max_peak_tol_size);
	tmp32 = tmax;
	inv_ireg_write(st, (u32)tap_tmax, tap_tmax_size, (u8 *)&tmp32);
	//inv_imu_write_dmp_ram(s, (uint8_t *)&tmpvalue_32bit, (uint32_t)EDMP_tap_tmax, EDMP_tap_tmax_size);
	tmp32 = tmin;
	inv_ireg_write(st, (u32)tap_tmin, tap_tmin_size, (u8 *)&tmp32);
	//inv_imu_write_dmp_ram(s, (uint8_t *)&tmpvalue_32bit, (uint32_t)EDMP_tap_tmin, EDMP_tap_tmin_size);
	tmp32 = tavg;
	inv_ireg_write(st, (u32)tap_tavg, tap_tavg_size, (u8 *)&tmp32);
	//inv_imu_write_dmp_ram(s, (uint8_t *)&tmpvalue_32bit, (uint32_t)EDMP_tap_tavg, EDMP_tap_tavg_size);
	tmp32 = smudge;
	inv_ireg_write(st, (u32)tap_smudge_reject_thr, tap_smudge_reject_thr_size, (u8 *)&tmp32);
	//inv_imu_write_dmp_ram(s, (uint8_t *)&tmpvalue_32bit, (uint32_t)EDMP_tap_smudge_reject_thr, EDMP_tap_smudge_reject_thr_size);

	return 0;
}

static int inv_setup_r2w(struct inv_mpu_state *st)
{
	s32 sleep_time_out = 5000;
	s32 sleep_gesture_delay = 96;
	s32 motion_thr_angle_cosine = 1069655912;//1046221864;
	s32 motion_thr_timer_fast = 240;
	s32 motion_thr_timer_slow = 500;
	s32 motion_prev_gravity_timeout = 300;
	s32 last_gravity_motion_timer = 480;
	s32 last_gravity_timeout = 2600;
	s32 gesture_validity_timeout = 240;
	s32 gravity_filter_gain = 6;
	s32 tmp32;

	pr_info("setup R2W normal matrix\n");

	/*rc |= inv_ireg_write(st, soft_iron_sensitivity_matrix,
		soft_iron_sensitivity_matrix_size, mag_matrix_data);
*/
	tmp32 = sleep_time_out;
	pr_info("sleep-time-out=%d\n", tmp32);
	inv_ireg_write(st, (u32)r2w_sleep_time_out, r2w_sleep_time_out_size, (u8 *)&tmp32);

	tmp32 = sleep_gesture_delay;
	inv_ireg_write(st, (u32)r2w_sleep_gesture_delay, r2w_sleep_gesture_delay_size, (u8 *)&tmp32);

	tmp32 = 0; //reg_mounting_matrix is normal matrix for 0.
	inv_ireg_write(st, (u32)r2w_mounting_matrix, r2w_mounting_matrix_size, (u8 *)&tmp32);

	tmp32 = gravity_filter_gain;
	inv_ireg_write(st, (u32)r2w_gravity_filter_gain, r2w_gravity_filter_gain_size, (u8 *)&tmp32);

	tmp32 = motion_thr_angle_cosine;
	inv_ireg_write(st, (u32)r2w_motion_thr_angle_cosine, r2w_motion_thr_angle_cosine_size, (u8 *)&tmp32);

	tmp32 = motion_thr_timer_fast;
	inv_ireg_write(st, (u32)r2w_motion_thr_timer_fast, r2w_motion_thr_timer_fast_size, (u8 *)&tmp32);

	tmp32 = motion_thr_timer_slow;
	inv_ireg_write(st, (u32)r2w_motion_thr_timer_slow, r2w_motion_thr_timer_slow_size, (u8 *)&tmp32);

	tmp32 = motion_prev_gravity_timeout;
	inv_ireg_write(st, (u32)r2w_motion_prev_gravity_timeout, r2w_motion_prev_gravity_timeout_size, (u8 *)&tmp32);

	tmp32 = last_gravity_motion_timer;
	inv_ireg_write(st, (u32)r2w_last_gravity_motion_timer, r2w_last_gravity_motion_timer_size, (u8 *)&tmp32);

	tmp32 = last_gravity_timeout;
	inv_ireg_write(st, (u32)r2w_last_gravity_timeout, r2w_last_gravity_timeout_size, (u8 *)&tmp32);

	tmp32 = gesture_validity_timeout;
	inv_ireg_write(st, (u32)r2w_gesture_validity_timeout, r2w_gesture_validity_timeout_size, (u8 *)&tmp32);

	tmp32 = r2w_motion_thr_angle_cosine;


	return 0;
}
int inv_power_up_sram(struct inv_mpu_state *st)
{
	u8 v;
	int res;

	v = 0;
	inv_ireg_read(st, REG_FIFO_SRAM_SLEEP_IPREG_TOP1, 1, &v);
	v |= REG_FIFO_SRAM_SLEEP_FIFO_GSLEEP_SHARED_SRAM_MASK;
	res = inv_ireg_single_write(st, REG_FIFO_SRAM_SLEEP_IPREG_TOP1, v);

	return res;
}

int inv_imu_edmp_init_apex(struct inv_mpu_state *st, int clean_sram)
{
	u8 mask_pin_val, value, w;
	int mask_pin_reg, ram_size;
	int status = 0;
	int i;

	switch (st->chip_rev) {
	case INV_ICM45600_CHIP_REV_B:
		mask_pin_reg = REG_STATUS_MASK_PIN_8_15_IPREG_TOP1;
		mask_pin_val = REG_STATUS_MASK_PIN_8_15_INT_ON_DEMAND_PIN_1_DIS_MASK;
		ram_size = EDMP_RAM_REVB_SIZE;
		break;
	default:
		mask_pin_reg = REG_STATUS_MASK_PIN_0_7_IPREG_TOP1;
		mask_pin_val = REG_STATUS_MASK_PIN_0_7_INT_ON_DEMAND_PIN_0_DIS_MASK;
		ram_size = EDMP_RAM_REVA_SIZE;
		break;
	}

	/* Clear SRAM */
	if (clean_sram) {
		value = 0;
		for (i = 0; i < ram_size; i++) {
			status = inv_ireg_single_write(st, EDMP_RAM_BASE + i, value);
			if (status)
				return status;
		}
	}

	/* unmask on demand interrupt */
	status = inv_ireg_read(st, mask_pin_reg, 1, &value);
	if (status)
		return status;
	value &= ~mask_pin_val;
	status = inv_ireg_single_write(st, mask_pin_reg, value);
	if (status)
		return status;

	/* request to execute init procedure */
	status = inv_plat_read(st, REG_EDMP_APEX_EN1_DREG_BANK1, 1, &value);
	if (status)
		return status;
	value |= REG_EDMP_APEX_EN1_INIT_EN_MASK | REG_EDMP_APEX_EN1_EDMP_ENABLE_MASK;
	status = inv_plat_single_write(st, REG_EDMP_APEX_EN1_DREG_BANK1, value);
	if (status)
		return status;

	/* send pulse to trigger on demand interrupt */
	status = inv_plat_read(st, REG_REG_HOST_MSG_DREG_BANK1, 1, &value);
	if (status)
		return status;
	value |= REG_REG_HOST_MSG_EDMP_ON_DEMAND_EN_MASK;
	status = inv_plat_single_write(st, REG_REG_HOST_MSG_DREG_BANK1, value);
	if (status)
		return status;

	usleep_range(500, 1000);
	for (i = 0; i < 100; ++i) {
		status = inv_ireg_read(st, REG_IPREG_MISC_IPREG_TOP1, 1, &w);
		if (status)
			return status;
		if (w & REG_IPREG_MISC_EDMP_IDLE_MASK)
			break;
		usleep_range(5000, 7000);
	}
	if (i >= 100) {
		pr_err("error in init eDMP idle wait\n");
		return -EINVAL;
	}

	/* put mask on interrupt */
	status = inv_ireg_read(st, mask_pin_reg, 1, &value);
	if (status)
		return status;
	value |= mask_pin_val;
	status = inv_ireg_single_write(st, mask_pin_reg, value);
	if (status)
		return status;

	status = inv_plat_read(st, REG_EDMP_APEX_EN1_DREG_BANK1, 1, &value);
	if (status)
		return status;
	value &= ~(REG_EDMP_APEX_EN1_INIT_EN_MASK | REG_EDMP_APEX_EN1_EDMP_ENABLE_MASK);
	status = inv_plat_single_write(st, REG_EDMP_APEX_EN1_DREG_BANK1, value);
	if (status)
		return status;

	return 0;
}

static int inv_imu_enable_edmp_int(struct inv_mpu_state *st) {
	u8 wom_config = 0;
	u8 int_apex_config0_mask = 0xff;
	u8 int_apex_config1_mask = 0xff;
	u8 edmp_event_en = 0;
	int r;

	/* enable WOM as long as APEX feature is
	 * enabled to support DMP_POWER_SAVE_EN
	 */
	wom_config |= (BIT_WOM_MODE | BIT_WOM_EN);
	edmp_event_en = REG_INT1_CONFIG1_INT1_STATUS_EN_APEX_EVENT_MASK;

	/* Update registers */
	r = inv_plat_single_write(st, REG_TMST_WOM_CONFIG_DREG_BANK1, wom_config);
	if (r)
		return r;

	/* Interrupt for apex gestures. Step counter does
	 * not trigger interrupt. Host should poll sysfs entry of step counter */
	if (st->step_detector_l_on || st->step_detector_wake_l_on ||
			((st->step_counter_wake_l_on || st->step_counter_l_on)
			 && st->ped.int_mode))
		int_apex_config0_mask &= (~REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_STEP_DET_MASK);

	if (st->chip_config.tilt_enable)
		int_apex_config0_mask &= (~REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_TILT_DET_MASK);

	if (st->chip_config.tap_enable)
		int_apex_config0_mask &= (~REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_TAP_DETECT_MASK);

	if (st->chip_config.pick_up_enable) {
		int_apex_config0_mask &= (~REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_R2W_WAKE_DET_MASK);
		int_apex_config1_mask &= (~REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_R2W_SLEEP_DET_MASK);
	}

	if (st->smd.on && st->smd_supported)
		int_apex_config1_mask &= (~REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SMD_DET_MASK);

	pr_debug("apex mask01=%x, %x edmp_on=%x\n", int_apex_config0_mask,
		int_apex_config1_mask, edmp_event_en);
	r = inv_plat_single_write(st, REG_INT_APEX_CONFIG0_DREG_BANK1, int_apex_config0_mask);
	if (r)
		return r;
	r = inv_plat_single_write(st, REG_INT_APEX_CONFIG1_DREG_BANK1, int_apex_config1_mask);
	if (r)
		return r;
	r = inv_plat_single_write(st, REG_INT1_CONFIG1_DREG_BANK1, edmp_event_en);

	return r;
}

static int inv_setup_step_counter(struct inv_mpu_state *st)
{
	u8 buffer_mgmt = 0;
	int res;
	u8 wptr;

	/* setup step counter buffer */
	res = inv_plat_read(st, REG_APEX_BUFFER_MGMT_DREG_BANK1, 1, &buffer_mgmt);
	wptr = (buffer_mgmt & REG_APEX_BUFFER_MGMT_STEP_COUNT_EDMP_WPTR_MASK);
	st->apex_data.step_rptr = wptr;
	buffer_mgmt &= (~REG_APEX_BUFFER_MGMT_STEP_COUNT_HOST_RPTR_MASK);
	buffer_mgmt |= (st->apex_data.step_rptr
			<< REG_APEX_BUFFER_MGMT_STEP_COUNT_HOST_RPTR_POS);
	res = inv_plat_single_write(st, REG_APEX_BUFFER_MGMT_DREG_BANK1, buffer_mgmt);
	if (res)
		return res;

	//res = inv_ireg_single_write(st, ped_step_cnt_wptr, wptr);

	return res;
}

static int inv_enable_apex_gestures(struct inv_mpu_state *st)
{
	int res;
	u8 apex_en0, prev_apex_en0, apex_en1, w, i2cm_rate;

	inv_imu_enable_edmp_int(st);

	res = inv_plat_read(st, REG_EDMP_APEX_EN0_DREG_BANK1, 1, &prev_apex_en0);
	if (res)
		return res;
	pr_debug("prev_apex_en0=%x\n", prev_apex_en0);

	/* most DMP algorithm is running at 50Hz except tap.
	 * pick up gesture is running at 100Hz.
	 * This register is the DMP wake up rate. It must be slower or equal
	 * to accel rate. */
	if (inv_get_apex_enabled(st)) {
		if (st->chip_config.tap_enable)
			w = BIT_DMP_ODR_200HZ;
		else if (st->chip_config.pick_up_enable)
			w = BIT_DMP_ODR_100HZ;
		else
			w = BIT_DMP_ODR_50HZ;
	} else {
		w = BIT_DMP_ODR_25HZ;
	}

	/* 100 Hz is the maximum  for AKM compass*/
	if (st->chip_config.slave_enable) {
		if (st->eng_info[ENGINE_I2C].running_rate >= 100) {
			i2cm_rate = 5;
			if (w < BIT_DMP_ODR_100HZ)
				w = BIT_DMP_ODR_100HZ;
		} else if (st->eng_info[ENGINE_I2C].running_rate >= 50) {
			i2cm_rate = 4;
			if (w < BIT_DMP_ODR_50HZ)
				w = BIT_DMP_ODR_50HZ;
		} else if (st->eng_info[ENGINE_I2C].running_rate >= 25) {
			i2cm_rate = 3;
		} else if (st->eng_info[ENGINE_I2C].running_rate >= 12) {
			i2cm_rate = 2;
		} else {
			i2cm_rate = 1;
		}

		w |= ((i2cm_rate << REG_DMP_EXT_SEN_ODR_CFG_EXT_ODR_POS) |
			REG_DMP_EXT_SEN_ODR_CFG_EXT_SENSOR_EN_MASK);
	}

	pr_debug("ext sensor odr=%x\n", w);
	res = inv_plat_single_write(st, REG_DMP_EXT_SEN_ODR_CFG_DREG_BANK1, w);
	apex_en0 = 0;
	apex_en1 = 0;

	if (st->step_detector_l_on ||
		st->step_detector_wake_l_on ||
		st->step_counter_l_on ||
		st->step_counter_wake_l_on ||
		st->smd.on) {
		inv_setup_step_counter(st);
		apex_en0 |= REG_EDMP_APEX_EN0_PEDO_EN_MASK;
		st->apex_data.step_reset_last_val = true;
	}

	if (st->chip_config.tilt_enable)
		apex_en0 |= REG_EDMP_APEX_EN0_TILT_EN_MASK;

	if (st->chip_config.tap_enable) {
		apex_en0 |= REG_EDMP_APEX_EN0_TAP_EN_MASK;
		inv_setup_tap(st);
	}

	if (st->chip_config.pick_up_enable) {
		//apex_en1 |= REG_EDMP_APEX_EN1_FEATURE3_EN_MASK;
		apex_en0 |= REG_EDMP_APEX_EN0_R2W_EN_MASK;
		inv_setup_r2w(st);
	}

	if (st->smd.on)
		apex_en0 |= REG_EDMP_APEX_EN0_SMD_EN_MASK;

	if (apex_en0 || apex_en1 || st->chip_config.slave_enable) {
		apex_en1 |= (REG_EDMP_APEX_EN1_EDMP_ENABLE_MASK);
			//REG_EDMP_APEX_EN1_DMP_SOFT_HARD_IRON_CORR_EN_MASK);
	}


	if (apex_en0)
		inv_imu_edmp_init_apex(st, 0);

	if (st->chip_config.pick_up_enable) {
		inv_setup_r2w(st);
		pr_info("setup twice\n");
	}

	pr_debug("apex_en0=%x\n", apex_en0);
	res = inv_plat_single_write(st, REG_EDMP_APEX_EN0_DREG_BANK1, apex_en0);
	if (res)
		return res;
	if (st->chip_config.lp_en_mode_off == 0)
		apex_en1 |= REG_EDMP_APEX_EN1_POWER_SAVE_EN_MASK;
	res = inv_plat_single_write(st, REG_EDMP_APEX_EN1_DREG_BANK1, apex_en1);
	if (res)
		return res;

	w = 0xff;
	if (apex_en0 || (apex_en1 & REG_EDMP_APEX_EN1_FEATURE3_EN_MASK))
		w &= ~REG_STATUS_MASK_PIN_0_7_INT_ACCEL_DRDY_PIN_0_DIS_MASK;

	inv_ireg_single_write(st, REG_STATUS_MASK_PIN_0_7_IPREG_TOP1, w);

	w = 0xff;
	/* external sensor is enabled */
	if (st->chip_config.slave_enable)
		w &= ~REG_STATUS_MASK_PIN_8_15_INT_EXT_ODR_DRDY_PIN_1_DIS_MASK;
	pr_debug("mask pin_8_15 value=%x\n", w);
	res = inv_ireg_single_write(st, REG_STATUS_MASK_PIN_8_15_IPREG_TOP1, w);

	return res;
}

static void __maybe_unused inv_dump_debug_reg(struct inv_mpu_state *st){
	u8 v, v2, v3, v4, v5;

	inv_plat_read(st, REG_PWR_MGMT0_DREG_BANK1, 1, &v);
	pr_info("pwr=%x\n", v);
#if 1
	inv_plat_read(st, REG_DMP_EXT_SEN_ODR_CFG_DREG_BANK1, 1, &v2);

	inv_ireg_read(st, REG_STATUS_MASK_PIN_0_7_IPREG_TOP1, 1, &v3);

	inv_plat_read(st, REG_EDMP_APEX_EN1_DREG_BANK1, 1, &v4);
	inv_plat_read(st, REG_EDMP_APEX_EN0_DREG_BANK1, 1, &v5);

	pr_info("pwr=%x, ext_sen=%x, pin_07=%x, en1=%x, en0=%x\n", v, v2, v3,v4, v5);

	inv_ireg_read(st, REG_STATUS_MASK_PIN_8_15_IPREG_TOP1, 1, &v3);
	inv_ireg_read(st, es_power_mode, 1, &v2);
	inv_ireg_read(st, es0_compass_en, 1, &v5);

	inv_plat_read(st, REG_ACCEL_CONFIG0_DREG_BANK1, 1, &v4);
	inv_plat_read(st, REG_GYRO_CONFIG0_DREG_BANK1, 1, &v);

	pr_info("int_8_15=%x, es_pm=%x, accel_config0=%x, es0_comp=%d, gyro_config0=%x\n", v3, v2, v4, v5, v);

	inv_ireg_read(st, REG_I2CM_COMMAND_0_IPREG_TOP1, 1, &v);
	inv_ireg_read(st, REG_I2CM_COMMAND_1_IPREG_TOP1, 1, &v2);
	inv_ireg_read(st, REG_I2CM_WR_DATA0_IPREG_TOP1, 1, &v3);
	inv_ireg_read(st, REG_I2CM_WR_DATA1_IPREG_TOP1, 1, &v4);

	pr_info("i2cm=%x %x, wr_d=%x %x\n", v, v2, v3, v4);

	inv_plat_read(st, REG_FIFO_CONFIG1_0_DREG_BANK1, 1, &v4);
	inv_plat_read(st, REG_FIFO_CONFIG1_1_DREG_BANK1, 1, &v5);
	inv_plat_read(st, REG_FIFO_CONFIG2_DREG_BANK1, 1, &v);
	inv_plat_read(st, REG_FIFO_CONFIG0_DREG_BANK1, 1, &v3);
	inv_ireg_read(st, REG_SMC_CONTROL_0_IPREG_TOP1, 1, &v2);
	pr_info("thresh=%x %x, conf2=%x, ff_conf0=%x, smc_control=%x\n", v4, v5, v, v3, v2);

	inv_plat_read(st, REG_FIFO_CONFIG3_DREG_BANK1, 1, &v);
	inv_plat_read(st, REG_FIFO_CONFIG4_DREG_BANK1, 1, &v2);
	pr_info("ff_34=%x %x\n", v, v2);


	inv_plat_read(st, REG_INT_APEX_CONFIG0_DREG_BANK1, 1, &v2);
	inv_plat_read(st, REG_INT_APEX_CONFIG1_DREG_BANK1, 1, &v3);

	inv_plat_read(st, REG_INT1_CONFIG0_DREG_BANK1, 1, &v4);
	inv_plat_read(st, REG_INT1_CONFIG1_DREG_BANK1, 1, &v5);
	pr_info("apex_int=%x %x, int1_config=%x %x\n", v2, v3, v4, v5);

	inv_plat_read(st, REG_FIFO_COUNT_0_DREG_BANK1, 1, &v4);
	inv_plat_read(st, REG_FIFO_COUNT_1_DREG_BANK1, 1, &v5);
	inv_plat_read(st, REG_TMST_WOM_CONFIG_DREG_BANK1, 1, &v2);

	pr_info("fifc=%x %x, wom=%x\n", v4, v5, v2);
#endif
}

static int inv_determine_engine(struct inv_mpu_state *st)
{
	int i;
	bool a_en, g_en, c_en;
	int accel_rate, gyro_rate, gesture_rate, max_rate, i2c_rate;

	max_rate = 0;

	a_en = false;
	g_en = false;
	c_en = false;
#ifdef SUPPORT_GYRO_LPM
	pr_debug("gyro_lpm\n");
	gyro_rate = MPU_INIT_SENSOR_RATE_LPM;
#else
	gyro_rate = MPU_INIT_SENSOR_RATE_LNM;
#endif
#ifdef SUPPORT_ACCEL_LPM
	accel_rate = MPU_INIT_SENSOR_RATE_LPM;
#else
	accel_rate = MPU_INIT_SENSOR_RATE_LNM;
#endif
	gesture_rate = 0;

	/*
	 * loop the streaming sensors to see which engine needs to be turned on
	 */
	for (i = 0; i < SENSOR_NUM_MAX; i++) {
		if (st->sensor[i].on) {
			a_en |= st->sensor[i].a_en;
			g_en |= st->sensor[i].g_en;
			c_en |= st->sensor[i].c_en;
		}
	}
	if (inv_get_apex_enabled(st)) {
		a_en = true;
		st->sensor[SENSOR_ACCEL].on = 1;
		if (st->chip_config.tap_enable)
			gesture_rate = 200;
		else if (st->chip_config.pick_up_enable)
			gesture_rate = 100;
		else
			gesture_rate = 50;
		accel_rate = max(accel_rate, gesture_rate);
	}

	if (st->chip_config.eis_enable) {
		g_en = true;
		st->eis.frame_count = 0;
		st->eis.fsync_delay = 0;
		st->eis.gyro_counter = 0;
		st->eis.voting_count = 0;
		st->eis.voting_count_sub = 0;
		gyro_rate = BASE_SAMPLE_RATE;
	} else {
		st->eis.eis_triggered = false;
		st->eis.prev_state = false;
	}

	accel_rate = max(accel_rate, st->sensor[SENSOR_ACCEL].rate);
	gyro_rate  = max(gyro_rate, st->sensor[SENSOR_GYRO].rate);
	/* if both accel/gyro and I2CM are enabled, accel/gyro rate must be
	 * higher than I2CM rate */
	if (c_en) {
		i2c_rate = 0;
		if (st->sensor[SENSOR_COMPASS].on)
			i2c_rate = max(i2c_rate, st->sensor[SENSOR_COMPASS].rate);
		if (st->sensor[SENSOR_PRESSURE].on)
			i2c_rate = max(i2c_rate, st->sensor[SENSOR_PRESSURE].rate);
		st->eng_info[ENGINE_I2C].running_rate = i2c_rate;
		if (a_en)
			accel_rate = max(accel_rate, i2c_rate);
		if (g_en)
			gyro_rate = max(gyro_rate, i2c_rate);
	}

	st->eng_info[ENGINE_ACCEL].running_rate = accel_rate;
	st->eng_info[ENGINE_GYRO].running_rate = gyro_rate;

	st->sensor[SENSOR_ACCEL].rate = accel_rate;
	st->sensor[SENSOR_GYRO].rate = gyro_rate;

	if (g_en)
		max_rate = gyro_rate;
	if (a_en)
		max_rate = max(max_rate, accel_rate);
	if (c_en) {
		if (st->eng_info[ENGINE_I2C].running_rate > max_rate)
			max_rate = st->eng_info[ENGINE_I2C].running_rate;
	}
	st->batch.max_rate = max_rate;

	if (st->chip_config.eis_enable) {
		st->eng_info[ENGINE_GYRO].divider = 1;
		st->eng_info[ENGINE_ACCEL].divider = 1;
		for (i = 0 ; i < SENSOR_L_NUM_MAX ; i++) {
			if (st->sensor_l[i].on) {
				st->sensor_l[i].counter = 0;
				if (st->sensor_l[i].rate)
					st->sensor_l[i].div =
					((BASE_SAMPLE_RATE /
					st->eng_info[ENGINE_GYRO].divider) /
						 st->sensor_l[i].rate);
				else
					st->sensor_l[i].div = 0xffff;
			}
		}
	} else {
		st->eng_info[ENGINE_GYRO].divider =
			inv_get_actual_duration(st->eng_info[ENGINE_GYRO].running_rate) / 1250000;
		st->eng_info[ENGINE_ACCEL].divider =
			inv_get_actual_duration(st->eng_info[ENGINE_ACCEL].running_rate) / 1250000;
		st->eng_info[ENGINE_I2C].divider =
			inv_get_actual_duration(st->eng_info[ENGINE_I2C].running_rate) / 1250000;
		/* calculate decimation rate for each sensor */
		for (i = 0; i < SENSOR_L_NUM_MAX; i++) {
			if (st->sensor_l[i].on) {
				if (st->sensor_l[i].rate)
					st->sensor_l[i].div =
				    st->sensor[st->sensor_l[i].base].rate
							/ st->sensor_l[i].rate;
				else
					st->sensor_l[i].div = 0xffff;
				pr_debug(" setup sensor= %d, div= %d\n",
							i, st->sensor_l[i].div);
			}
		}
	}

	if (g_en && a_en) {
		if (st->eng_info[ENGINE_GYRO].running_rate >=
				st->eng_info[ENGINE_ACCEL].running_rate) {
			st->ts_algo.clock_base = ENGINE_GYRO;
		} else {
			st->ts_algo.clock_base = ENGINE_ACCEL;
		}
	} else if (g_en || a_en) {
		if (st->sensor[SENSOR_GYRO].on)
			st->ts_algo.clock_base = ENGINE_GYRO;
		else
			st->ts_algo.clock_base = ENGINE_ACCEL;
	} else {
		st->ts_algo.clock_base = ENGINE_I2C;
	}

	for (i = 0 ; i < SENSOR_L_NUM_MAX ; i++)
		st->sensor_l[i].counter = 0;

	inv_calc_engine_dur(st, &st->eng_info[ENGINE_GYRO]);
	inv_calc_engine_dur(st, &st->eng_info[ENGINE_ACCEL]);
	inv_calc_engine_dur(st, &st->eng_info[ENGINE_I2C]);

	pr_debug("a=%d, %d, g=%d,%d, c=%d, %d, p=%d, %d\n",
		st->sensor[SENSOR_ACCEL].on,st->sensor[SENSOR_ACCEL].rate,
		st->sensor[SENSOR_GYRO].on,st->sensor[SENSOR_GYRO].rate,
		st->sensor[SENSOR_COMPASS].on,st->sensor[SENSOR_COMPASS].rate,
		st->sensor[SENSOR_PRESSURE].on,st->sensor[SENSOR_PRESSURE].rate);


	st->chip_config.gyro_enable = g_en;
	st->chip_config.accel_enable = a_en;
	st->chip_config.slave_enable = c_en;

	if (st->eng_info[ENGINE_I2C].running_rate) {
		st->mag_divider = max_rate /
			st->eng_info[ENGINE_I2C].running_rate;
		st->mag_divider <<= 8;
	}


	return 0;
}

/*
 *  set_inv_enable() - enable function.
 */
int set_inv_enable(struct iio_dev *indio_dev)
{
	int res;
	struct inv_mpu_state *st = iio_priv(indio_dev);
	long long t1, t2, t3;

	t1 = get_time_ns();

	inv_stop_interrupt(st);
	inv_stop_dmp(st);

	inv_determine_engine(st);

	if ((!st->chip_config.gyro_enable) &&
		(!st->chip_config.accel_enable) &&
		(!st->chip_config.slave_enable) &&
		(!inv_get_apex_enabled(st))) {
		inv_turn_off_engine(st);
		//inv_dump_debug_reg(st);
		pr_debug("return nothing is on\n");
		return 0;
	}

	/* GAF: unconditionally enable FIFO GAF support (ICM-45608 always supports it).
	 * Must be set before inv_set_rate() so pk_size=32 is configured correctly.
	 * inv_mpu_gaf_init() called later does the actual hardware init. */
	st->chip_config.gaf_enabled = 1;

	res = inv_set_rate(st);
	if (res) {
		pr_err("inv_set_rate error\n");
		return res;
	}

	res = inv_turn_on_engine(st);
	if (res) {
		pr_err("inv_turn_on_engine error\n");
		return res;
	}
	t3 = get_time_ns();

	if (inv_get_apex_enabled(st) || st->chip_config.slave_enable) {
		res = inv_enable_apex_gestures(st);
		if (res) {
			pr_err("inv_enable_apex_gestures error\n");
			return res;
		}
	}

	/* GAF init — align with MCU main.c:77 icm_45608_init() position.
	 * Called once per sensor enable to configure GAF before FIFO starts.
	 * Try 9-axis first, fallback to 6-axis if mag absent. */
	if (st->chip_config.gaf_enabled) {
		res = inv_mpu_gaf_init(st, 1);
		if (res)
			pr_err("GAF: init failed in enable path=%d\n", res);
	}

	res = inv_reset_fifo(st, false);
	if (res)
		return res;
	//inv_dump_debug_reg(st);
	t2 = get_time_ns();

	pr_debug("time_diff2=%lld, %lld\n", t2 - t1, t2-t3);

	return res;
}

int inv_mpu_unlock_pressure_sensor(struct inv_mpu_state *st) {

	int res;
	u8 w, w_bf0, w_bf1;

#define ICP201xx_REG_MODE_SELECT  0xC0
#define ICP201xx_REG_TRIG_CMD     0x90

#define ICP201xx_MASTER_LOCK     0xBE //write 0x1F to unlock
#define ICP201xx_UNLOCK_CODE     0x1F

	st->sensor[SENSOR_PRESSURE].on = 1;
	st->sensor[SENSOR_PRESSURE].rate = 50;

	res = inv_ireg_read(st, REG_I2CM_COMMAND_2_IPREG_TOP1, 1, &w);
	if (res)
		return res;
	/* set burst length to 0 to disable pressure sensor read */
	w &= (~REG_I2CM_COMMAND_2_BURSTLEN_2_MASK);
	res = inv_ireg_single_write(st, REG_I2CM_COMMAND_2_IPREG_TOP1, w);
	if (res)
		return res;

	w_bf0 = ICP201xx_MASTER_LOCK;
	w_bf1 = ICP201xx_UNLOCK_CODE;

	/* Load data to write. Reg CNTL2 = 0x01 for single measurement */
	inv_ireg_single_write(st, REG_I2CM_WR_DATA2_IPREG_TOP1, w_bf0);
	inv_ireg_single_write(st, REG_I2CM_WR_DATA3_IPREG_TOP1, w_bf1);


	inv_determine_engine(st);

	res = inv_set_rate(st);
	if (res) {
		pr_err("inv_set_rate error\n");
		return res;
	}

	res = inv_turn_on_engine(st);
	if (res) {
		pr_err("inv_turn_on_engine error\n");
		return res;
	}

	msleep(30);

	inv_stop_interrupt(st);
	inv_stop_dmp(st);

	w_bf0 = ICP201xx_REG_MODE_SELECT;
	w_bf1 = ICP201xx_REG_TRIG_CMD;

	/* Load data to write. Reg CNTL2 = 0x01 for single measurement */
	inv_ireg_single_write(st, REG_I2CM_WR_DATA2_IPREG_TOP1, w_bf0);
	inv_ireg_single_write(st, REG_I2CM_WR_DATA3_IPREG_TOP1, w_bf1);

	res = inv_ireg_read(st, REG_I2CM_COMMAND_2_IPREG_TOP1, 1, &w);
	if (res)
		return res;
	/* recover burst length to 6 enable pressure sensor read */
	w |= (6 << REG_I2CM_COMMAND_2_BURSTLEN_2_POS);
	res = inv_ireg_single_write(st, REG_I2CM_COMMAND_2_IPREG_TOP1, w);
	if (res)
		return res;

	inv_turn_off_engine(st);

	return 0;
}

int inv_stop_interrupt(struct inv_mpu_state *st)
{
	int r;

	r = inv_plat_single_write(st, REG_INT1_CONFIG0_DREG_BANK1, 0);
	if (r)
		return r;
	r = inv_plat_single_write(st, REG_INT1_CONFIG1_DREG_BANK1, 0);
	if (r)
		return r;

	r = inv_plat_single_write(st, REG_TMST_WOM_CONFIG_DREG_BANK1, 0);

	return r;
}

int inv_restore_interrupt(struct inv_mpu_state *st)
{
	(void)st;
	return 0;
}

int inv_stop_stream_interrupt(struct inv_mpu_state *st)
{
	(void)st;
	return 0;
}

int inv_restore_stream_interrupt(struct inv_mpu_state *st)
{
	(void)st;
	return 0;
}

/* dummy function for 20608D */
int inv_enable_pedometer_interrupt(struct inv_mpu_state *st, bool en)
{
	return 0;
}

int inv_dmp_read(struct inv_mpu_state *st, int off, int size, u8 *buf)
{
	return 0;
}

int inv_firmware_load(struct inv_mpu_state *st)
{
	return 0;
}
