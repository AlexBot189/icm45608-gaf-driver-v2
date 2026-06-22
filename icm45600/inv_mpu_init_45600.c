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
#include "../inv_mpu_iio.h"
#include "inv_mpu_gaf.h"

static int inv_read_timebase(struct inv_mpu_state *st)
{
	st->eng_info[ENGINE_ACCEL].base_time = NSEC_PER_SEC;
	st->eng_info[ENGINE_ACCEL].base_time_1k = NSEC_PER_SEC;
	st->eng_info[ENGINE_ACCEL].base_time_vr = NSEC_PER_SEC;
	/* talor expansion to calculate base time unit */
	st->eng_info[ENGINE_GYRO].base_time = NSEC_PER_SEC;
	st->eng_info[ENGINE_GYRO].base_time_1k = NSEC_PER_SEC;
	st->eng_info[ENGINE_GYRO].base_time_vr = NSEC_PER_SEC;
	st->eng_info[ENGINE_I2C].base_time = NSEC_PER_SEC;
	st->eng_info[ENGINE_I2C].base_time_1k = NSEC_PER_SEC;
	st->eng_info[ENGINE_I2C].base_time_vr = NSEC_PER_SEC;

	st->eng_info[ENGINE_ACCEL].orig_rate = BASE_SAMPLE_RATE;
	st->eng_info[ENGINE_GYRO].orig_rate = BASE_SAMPLE_RATE;
	st->eng_info[ENGINE_I2C].orig_rate = BASE_SAMPLE_RATE;

	return 0;
}

int inv_set_gyro_sf(struct inv_mpu_state *st)
{
	int result;
	u8 data;

	result = inv_plat_read(st, REG_GYRO_CONFIG0_DREG_BANK1, 1, &data);
	if (result)
		return result;
	data &= ~BIT_GYRO_FSR;
	data |= (4 - st->chip_config.fsr) << SHIFT_GYRO_FS_SEL;
	result = inv_plat_single_write(st, REG_GYRO_CONFIG0_DREG_BANK1, data);
	return result;
}

int inv_set_accel_sf(struct inv_mpu_state *st)
{
	int result;
	u8 data;

	result = inv_plat_read(st, REG_ACCEL_CONFIG0_DREG_BANK1, 1, &data);
	if (result)
		return result;
	data &= ~BIT_ACCEL_FSR;
	data |= (4 - st->chip_config.accel_fs) << SHIFT_ACCEL_FS_SEL;
	result = inv_plat_single_write(st, REG_ACCEL_CONFIG0_DREG_BANK1, data);
	return result;
}

int inv_set_accel_intel(struct inv_mpu_state *st)
{
	int result = 0;
	int8_t val, accel_rate;

	accel_rate = 800 / st->eng_info[ENGINE_ACCEL].divider;
	if (accel_rate > 50)
		val = WOM_THRESHOLD / (accel_rate / 50);
	else
		val = WOM_THRESHOLD;

	result |= inv_ireg_single_write(st, REG_ACCEL_WOM_X_THR_IPREG_TOP1, val);
	result |= inv_ireg_single_write(st, REG_ACCEL_WOM_Y_THR_IPREG_TOP1, val);
	result |= inv_ireg_single_write(st, REG_ACCEL_WOM_Z_THR_IPREG_TOP1, val);

	return result;
}

int inv_config_apex_gestures(struct inv_mpu_state *st)
{
#if 0 // TODO
	int result = 0;
	int8_t rw;
	int8_t dmp_power_save_time = 2;
	int8_t low_energy_amp_th = 10;
	int8_t pedo_amp_th_sel = 8;
	int8_t pedo_step_cnt_th_sel = 5;
	int8_t pedo_step_det_th_sel = 2;
	int8_t pedo_sb_timer_th_sel = 4;
	int8_t pedo_hi_enrgy_th_sel = 1;
	int8_t tilt_wait_time = 1; /* default: 2 */
	int8_t smd_sensitivity = 0;
	int8_t sensitivity_mode = 0;

	/* REG_APEX_CONFIG2_MREG_TOP1 */
	rw = dmp_power_save_time & 0x0f;
	rw |= (low_energy_amp_th << 4) & 0xf0;
	result = inv_mreg_single_write(st, REG_APEX_CONFIG2_MREG_TOP1, rw);
	if (result)
		return result;

	/* REG_APEX_CONFIG3_MREG_TOP1 */
	rw = (pedo_amp_th_sel << 4) & 0xf0;
	rw |= pedo_step_cnt_th_sel & 0x0f;
	result = inv_mreg_single_write(st, REG_APEX_CONFIG3_MREG_TOP1, rw);
	if (result)
		return result;

	/* REG_APEX_CONFIG4_MREG_TOP1 */
	rw = (pedo_step_det_th_sel << 5) & 0xe0;
	rw |= (pedo_sb_timer_th_sel << 2) & 0x1c;
	rw |= pedo_hi_enrgy_th_sel & 0x03;
	result = inv_mreg_single_write(st, REG_APEX_CONFIG4_MREG_TOP1, rw);
	if (result)
		return result;

	/* REG_APEX_CONFIG5_MREG_TOP1 */
	result = inv_mreg_read(st, REG_APEX_CONFIG5_MREG_TOP1, 1, &rw);
	if (result)
		return result;
	rw &= 0x3f;
	rw |= (tilt_wait_time << 6) & 0xc0;
	result = inv_mreg_single_write(st, REG_APEX_CONFIG5_MREG_TOP1, rw);
	if (result)
		return result;

	/* REG_APEX_CONFIG9_MREG_TOP1 */
	result = inv_mreg_read(st, REG_APEX_CONFIG9_MREG_TOP1, 1, &rw);
	if (result)
		return result;
	rw &= 0xf0;
	rw |= (smd_sensitivity << 1) & 0x0e;
	rw |= (sensitivity_mode << 0) & 0x01;
	result = inv_mreg_single_write(st, REG_APEX_CONFIG9_MREG_TOP1, rw);

	return result;
#else
	return 0;
#endif
}

static void inv_init_sensor_struct(struct inv_mpu_state *st)
{
	int i;

#ifdef SUPPORT_ACCEL_LPM
	for (i = 0; i < SENSOR_NUM_MAX; i++)
		st->sensor[i].rate = MPU_INIT_SENSOR_RATE_LPM;
#else
	for (i = 0; i < SENSOR_NUM_MAX; i++)
		st->sensor[i].rate = MPU_INIT_SENSOR_RATE_LNM;
#endif
	st->sensor[SENSOR_GYRO].rate = MPU_INIT_SENSOR_RATE_LNM;

	st->sensor[SENSOR_ACCEL].sample_size = BYTES_PER_SENSOR;
	st->sensor[SENSOR_TEMP].sample_size = BYTES_FOR_TEMP;
	st->sensor[SENSOR_GYRO].sample_size = BYTES_PER_SENSOR;
	st->sensor[SENSOR_COMPASS].sample_size = BYTES_PER_SENSOR;
	st->sensor[SENSOR_PRESSURE].sample_size = BYTES_PER_SENSOR;

	st->sensor_l[SENSOR_L_SIXQ].base = SENSOR_GYRO;
	st->sensor_l[SENSOR_L_PEDQ].base = SENSOR_GYRO;

	st->sensor_l[SENSOR_L_SIXQ_WAKE].base = SENSOR_GYRO;
	st->sensor_l[SENSOR_L_PEDQ_WAKE].base = SENSOR_GYRO;

	st->sensor[SENSOR_ACCEL].a_en = true;
	st->sensor[SENSOR_GYRO].a_en = false;
	st->sensor[SENSOR_COMPASS].a_en = false;
	st->sensor[SENSOR_PRESSURE].a_en = false;

	st->sensor[SENSOR_ACCEL].g_en = false;
	st->sensor[SENSOR_GYRO].g_en = true;
	st->sensor[SENSOR_COMPASS].g_en =false;
	st->sensor[SENSOR_PRESSURE].g_en =false;

	st->sensor[SENSOR_ACCEL].c_en = false;
	st->sensor[SENSOR_GYRO].c_en = false;
	st->sensor[SENSOR_COMPASS].c_en = true;
	st->sensor[SENSOR_PRESSURE].c_en = true;

	st->sensor[SENSOR_ACCEL].p_en = false;
	st->sensor[SENSOR_GYRO].p_en = false;
	st->sensor[SENSOR_COMPASS].p_en = false;
	st->sensor[SENSOR_PRESSURE].p_en = false;

	st->sensor[SENSOR_ACCEL].engine_base = ENGINE_ACCEL;
	st->sensor[SENSOR_GYRO].engine_base = ENGINE_GYRO;
	st->sensor[SENSOR_COMPASS].engine_base = ENGINE_I2C;
	st->sensor[SENSOR_PRESSURE].engine_base = ENGINE_I2C;

	st->sensor_l[SENSOR_L_ACCEL].base = SENSOR_ACCEL;
	st->sensor_l[SENSOR_L_GESTURE_ACCEL].base = SENSOR_ACCEL;
	st->sensor_l[SENSOR_L_GYRO].base = SENSOR_GYRO;
	st->sensor_l[SENSOR_L_GYRO_CAL].base = SENSOR_GYRO;
	st->sensor_l[SENSOR_L_EIS_GYRO].base = SENSOR_GYRO;

	st->sensor_l[SENSOR_L_ACCEL_WAKE].base = SENSOR_ACCEL;
	st->sensor_l[SENSOR_L_GYRO_WAKE].base = SENSOR_GYRO;

	st->sensor_l[SENSOR_L_GYRO_CAL_WAKE].base = SENSOR_GYRO;

	st->sensor_l[SENSOR_L_MAG].base = SENSOR_COMPASS;
	st->sensor_l[SENSOR_L_MAG_CAL].base = SENSOR_COMPASS;
	st->sensor_l[SENSOR_L_PRESSURE].base = SENSOR_PRESSURE;
	st->sensor_l[SENSOR_L_PRESSURE_WAKE].base = SENSOR_PRESSURE;

	st->sensor_l[SENSOR_L_ACCEL].header = ACCEL_HDR;
	st->sensor_l[SENSOR_L_GESTURE_ACCEL].header = ACCEL_HDR;
	st->sensor_l[SENSOR_L_GYRO].header = GYRO_HDR;
	st->sensor_l[SENSOR_L_GYRO_CAL].header = GYRO_CALIB_HDR;

	st->sensor_l[SENSOR_L_EIS_GYRO].header = EIS_GYRO_HDR;
	st->sensor_l[SENSOR_L_SIXQ].header = SIXQUAT_HDR;
	st->sensor_l[SENSOR_L_THREEQ].header = LPQ_HDR;
	st->sensor_l[SENSOR_L_NINEQ].header = NINEQUAT_HDR;
	st->sensor_l[SENSOR_L_PEDQ].header = PEDQUAT_HDR;

	st->sensor_l[SENSOR_L_ACCEL_WAKE].header = ACCEL_WAKE_HDR;
	st->sensor_l[SENSOR_L_GYRO_WAKE].header = GYRO_WAKE_HDR;
	st->sensor_l[SENSOR_L_GYRO_CAL_WAKE].header = GYRO_CALIB_WAKE_HDR;
	st->sensor_l[SENSOR_L_MAG_WAKE].header = COMPASS_WAKE_HDR;
	st->sensor_l[SENSOR_L_MAG].header = COMPASS_HDR;
	st->sensor_l[SENSOR_L_MAG_CAL].header = COMPASS_CALIB_HDR;
	st->sensor_l[SENSOR_L_PRESSURE].header = PRESSURE_HDR;
	st->sensor_l[SENSOR_L_PRESSURE_WAKE].header = PRESSURE_WAKE_HDR;
	st->sensor_l[SENSOR_L_MAG_CAL_WAKE].header = COMPASS_CALIB_WAKE_HDR;
	st->sensor_l[SENSOR_L_SIXQ_WAKE].header = SIXQUAT_WAKE_HDR;
	st->sensor_l[SENSOR_L_NINEQ_WAKE].header = NINEQUAT_WAKE_HDR;
	st->sensor_l[SENSOR_L_PEDQ_WAKE].header = PEDQUAT_WAKE_HDR;

	st->sensor_l[SENSOR_L_ACCEL].wake_on = false;
	st->sensor_l[SENSOR_L_GYRO].wake_on = false;
	st->sensor_l[SENSOR_L_GYRO_CAL].wake_on = false;
	st->sensor_l[SENSOR_L_MAG].wake_on = false;
	st->sensor_l[SENSOR_L_MAG_CAL].wake_on = false;
	st->sensor_l[SENSOR_L_EIS_GYRO].wake_on = false;
	st->sensor_l[SENSOR_L_SIXQ].wake_on = false;
	st->sensor_l[SENSOR_L_NINEQ].wake_on = false;
	st->sensor_l[SENSOR_L_PEDQ].wake_on = false;
	st->sensor_l[SENSOR_L_PRESSURE].wake_on = false;

	st->sensor_l[SENSOR_L_ACCEL_WAKE].wake_on = true;
	st->sensor_l[SENSOR_L_GYRO_WAKE].wake_on = true;
	st->sensor_l[SENSOR_L_GYRO_CAL_WAKE].wake_on = true;
	st->sensor_l[SENSOR_L_MAG_WAKE].wake_on = true;
	st->sensor_l[SENSOR_L_PRESSURE_WAKE].wake_on = true;
	st->sensor_l[SENSOR_L_SIXQ_WAKE].wake_on = true;
	st->sensor_l[SENSOR_L_NINEQ_WAKE].wake_on = true;
	st->sensor_l[SENSOR_L_PEDQ_WAKE].wake_on = true;
	st->sensor_l[SENSOR_L_GESTURE_ACCEL].wake_on = true;
}

static int inv_init_config(struct inv_mpu_state *st)
{
	int res, i;

	st->batch.overflow_on = 0;
	st->chip_config.fsr = MPU_INIT_GYRO_SCALE;
	st->chip_config.accel_fs = MPU_INIT_ACCEL_SCALE;
	st->ped.int_thresh = MPU_INIT_PED_INT_THRESH;
	st->ped.step_thresh = MPU_INIT_PED_STEP_THRESH;
	st->chip_config.low_power_gyro_on = 1;
	st->eis.count_precision = NSEC_PER_MSEC;
	st->firmware = 0;
	st->fifo_count_mode = RECORD_MODE;

	st->eng_info[ENGINE_GYRO].base_time = NSEC_PER_SEC;
	st->eng_info[ENGINE_ACCEL].base_time = NSEC_PER_SEC;

	inv_init_sensor_struct(st);
	res = inv_read_timebase(st);
	if (res)
		return res;

	res = inv_set_gyro_sf(st);
	if (res)
		return res;
	res = inv_set_accel_sf(st);
	if (res)
		return res;
	res =  inv_set_accel_intel(st);
	if (res)
		return res;

	if (st->apex_supported) {
		res =  inv_config_apex_gestures(st);
		if (res)
			return res;
	}

	for (i = 0; i < SENSOR_NUM_MAX; i++)
		st->sensor[i].ts = 0;

	for (i = 0; i < SENSOR_NUM_MAX; i++)
		st->sensor[i].previous_ts = 0;

	return res;
}

int inv_mpu_configure_dmp(struct inv_mpu_state *st)
{
	int status = 0;
	u16 start_addr[] = {EDMP_ROM_START_ADDR_IRQ0,
	                         EDMP_ROM_START_ADDR_IRQ1,
	                         EDMP_ROM_START_ADDR_IRQ2};
	u8 data[6];
	u8 stack_addr = (u8)(EDMP_STACK_ADDR >> 8); /* Only 8 MSB of SP address is written to register */
	pr_debug("configure_DMP = %x\n", stack_addr);


	/* Set Start address for 3 edmp IRQ handlers */
	status |= inv_ireg_write(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1, sizeof(start_addr), (u8*)&start_addr[0]);

	inv_ireg_read(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1, 1, &data[0]);
	inv_ireg_read(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1+1, 1, &data[1]);
	inv_ireg_read(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1+2, 1, &data[2]);
	inv_ireg_read(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1+3, 1, &data[3]);
	inv_ireg_read(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1+4, 1, &data[4]);

	pr_info("data_new=%x %x, %x, %x,%x\n", data[0], data[1], data[2], data[3], data[4]);

	/* Set Stack pointer start address */
	status |= inv_ireg_write(st, REG_EDMP_SP_START_ADDR_IPREG_TOP1, sizeof(stack_addr), (u8*)&stack_addr);

	return status;
}

static int init_mag_matrix(struct inv_mpu_state *st)
{
#define MAG_MATRIX_SIZE soft_iron_sensitivity_matrix_size / 4
#define MAG_OFFSET_SIZE hard_iron_offset_size / 4

	int rc = 0;
	int i;

	s32 mag_matrix[MAG_MATRIX_SIZE] =
					{16711 << 16, -(492 << 16), 327 << 16,
					16 << 16, 16056 << 16, -(1147 << 16),
					81 << 16, -(1475 << 16), 15728 << 16};
	s32 mag_offset[MAG_OFFSET_SIZE] = {-5611, 202, 293};

	u8 mag_matrix_data[soft_iron_sensitivity_matrix_size];
	u8 mag_offset_data[hard_iron_offset_size];

	pr_info("write mag matrix data\n");

	/* Prepare matrix data */
	for (i = 0; i < MAG_MATRIX_SIZE; i++) {
		mag_matrix_data[i * 4 + 3] = (u8)(mag_matrix[i] >> 24) & 0xFF;
		mag_matrix_data[i * 4 + 2] = (u8)(mag_matrix[i] >> 16) & 0xFF;
		mag_matrix_data[i * 4 + 1] = (u8)(mag_matrix[i] >> 8) & 0xFF;
		mag_matrix_data[i * 4 + 0] = (u8)(mag_matrix[i] >> 0) & 0xFF;
	}
	for (i = 0; i < MAG_OFFSET_SIZE; i++) {
		mag_offset_data[i * 4 + 3] = (u8)(mag_offset[i] >> 24) & 0xFF;
		mag_offset_data[i * 4 + 2] = (u8)(mag_offset[i] >> 16) & 0xFF;
		mag_offset_data[i * 4 + 1] = (u8)(mag_offset[i] >> 8) & 0xFF;
		mag_offset_data[i * 4 + 0] = (u8)(mag_offset[i] >> 0) & 0xFF;
	}
	rc |= inv_ireg_write(st, soft_iron_sensitivity_matrix,
		soft_iron_sensitivity_matrix_size, mag_matrix_data);

	rc |= inv_ireg_write(st, hard_iron_offset,
		hard_iron_offset_size, mag_offset_data);

	return rc;
}

static int inv_setup_i2cm(struct inv_mpu_state *st)
{
	int res;
	u8 w;

	/* int_status_i2cm_smc_ext_odr_en = 1, enable external sensor odr interrupt */
	res = inv_ireg_read(st, REG_INT_I2CM_SOURCE_IPREG_TOP1, 1, &w);
	if (res)
		return res;
	w |= (u8)REG_INT_I2CM_SOURCE_INT_STATUS_I2CM_SMC_EXT_ODR_EN_MASK;
	res = inv_ireg_single_write(st, REG_INT_I2CM_SOURCE_IPREG_TOP1, w);

	res = inv_ireg_single_write(st, es_RAM_image_en, 1);
	res = inv_ireg_single_write(st, es_power_mode, 1);

	return res;
}


int inv_mpu_initialize(struct inv_mpu_state *st)
{
	u8 v;
	int result;
	u8 value[2];
	int i;
	 /* reset to make sure previous state are not there */
	inv_plat_read(st, REG_INT1_STATUS0_DREG_BANK1, 1, &v);
	value[0] = 0x00;
	value[1] = 0x00;
	v = 0;

	/* verify whoami */
	result = inv_plat_read(st, REG_WHO_AM_I_DREG_BANK1, 1, &v);
	if (result)
		return result;
	pr_info("whoami= %x\n", v);

#ifdef FPGA_TEST
	inv_ireg_read(st, REG_REVISION1_IPREG_FPGA, 1, &v);
	pr_info("fpga_rev1= %x\n", v);
	inv_ireg_read(st, REG_REVISION2_IPREG_FPGA, 1, &v);
	pr_info("fpga_rev2= %x\n", v);
	st->chip_rev = INV_ICM45600_CHIP_REV_C;
#else
	if (v == 0x00 || v == 0xff)
		return -ENODEV;

	if (v >= 0xE5 && v <= 0xEF) {
		st->chip_rev = INV_ICM45600_CHIP_REV_A;
		pr_info("chip rev A detected\n");
	} else if (v >= 0x81 && v <= 0x8F) {
		st->chip_rev = INV_ICM45600_CHIP_REV_B;
		pr_info("chip rev B detected\n");
	} else {
		pr_warn("unknown whoami, using rev A by default\n");
		st->chip_rev = INV_ICM45600_CHIP_REV_A;
	}
#endif

	v = BIT_SOFT_RST;
	result = inv_plat_single_write(st, REG_REG_MISC2_DREG_BANK1, v);
	if (result)
		return result;
	v = 0;
	i = 0;

	while (!(v & REG_INT2_STATUS0_INT2_STATUS_RESET_DONE_MASK)) {
		msleep(10);
		result = inv_plat_read(st, REG_INT1_STATUS0_DREG_BANK1, 1, &v);
		if (result)
			return result;
		i++;
		if (i > 10)
			return -ENODEV;
	}

	/* set to big endian */
	result = inv_ireg_read(st, REG_SREG_CTRL_IPREG_TOP1, 1, &v);
	if (result)
		return result;
	v |= BIT_SREG_DATA_ENDIAN_SEL_BIG;

	result = inv_ireg_single_write(st, REG_SREG_CTRL_IPREG_TOP1, v);
	if (result)
		return result;

	inv_mpu_configure_dmp(st);

	/* GAF-based mag: ICT1531x is always on AUX I2C, handled by inv_mpu_mag_init() */
	st->chip_config.has_compass = 1;

	if (st->plat_data.aux_slave_type ==  SECONDARY_SLAVE_TYPE_PRESSURE)
		st->chip_config.has_pressure = 1;
	else
		st->chip_config.has_pressure = 0;

	/* Skip old AKM compass slave setup - GAF handles mag via I2CM */

	if (st->chip_config.has_pressure) {
		result = inv_mpu_setup_pressure_slave(st);
		if (result) {
			pr_err("pressure setup failed\n");
			st->chip_config.has_pressure = 0;
		}
	}

	/* INT pin configuration */
	v = (INT_POLARITY << SHIFT_INT1_POLARITY) |
		(INT_MODE << SHIFT_INT1_MODE);
	result = inv_plat_single_write(st, REG_INT1_CONFIG2_DREG_BANK1, v);
	if (result)
		return result;

	/* FIFO mode must be set to stop on full because only
	 * this mode supports 32 bytes packet. Stream mode does not support
	 *  32 bytes. It supports 8, 16, and 20 bytes packet. */
	v = BIT_FIFO_STOPONFULL;
	v |= BIT_FIFO_DEP_4096;

	result = inv_plat_single_write(st, REG_FIFO_CONFIG0_DREG_BANK1, v);
	if (result)
		return result;
	result = inv_plat_single_write(st, REG_FIFO_CONFIG3_DREG_BANK1, 0);
	if (result)
		return result;

	result = inv_plat_single_write(st, REG_FIFO_CONFIG2_DREG_BANK1,
		BIT_FIFO_WR_WM_GT_TH);
	if (result)
		return result;


	/* disable sensors */
	result = inv_plat_single_write(st, REG_PWR_MGMT0_DREG_BANK1, 0);
	if (result)
		return result;

	result = inv_init_config(st);
	if (result)
		return result;

	st->chip_config.lp_en_mode_off = 0;
	inv_power_up_sram(st);

	result = inv_imu_edmp_init_apex(st, 0);
	if (result)
		return result;

	init_mag_matrix(st);
	if (st->chip_config.has_compass || st->chip_config.has_pressure) {
		inv_setup_i2cm(st);
	}

	if (st->chip_config.has_pressure) {
		result = inv_mpu_unlock_pressure_sensor(st);
		if (result)
			pr_err("pressure setup failed\n");

	}


	pr_info("%s: initialize result is %d....\n", __func__, result);

	return 0;
}
