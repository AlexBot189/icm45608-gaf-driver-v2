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
#define DEBUG
#define pr_fmt(fmt) "inv_mpu: " fmt

#include "../inv_mpu_iio.h"
#include "./inv_imu_edmp_memmap.h"

/*
 * EDMP_STC_RESULTS
 */

#define STC_RESULTS_ACCEL_X_MASK   0x0001
#define STC_RESULTS_ACCEL_Y_MASK   0x0002
#define STC_RESULTS_ACCEL_Z_MASK   0x0004
#define STC_RESULTS_GYRO_X_MASK    0x0008
#define STC_RESULTS_GYRO_Y_MASK    0x0010
#define STC_RESULTS_GYRO_Z_MASK    0x0020
#define STC_RESULTS_ACCEL_SC_MASK  0x0040
#define STC_RESULTS_GYRO_SC_MASK   0x0080


/*
 * EDMP_STC_CONFIGPARAMS
 */

#define SELFTESTCAL_INIT_EN_MASK    0x0001
#define SELFTESTCAL_INIT_EN         0x0001
#define SELFTESTCAL_INIT_DIS        0x0000
#define SELFTEST_ACCEL_EN_MASK      0x0002
#define SELFTEST_ACCEL_EN           0x0002
#define SELFTEST_ACCEL_DIS          0x0000
#define SELFTEST_GYRO_EN_MASK       0x0004
#define SELFTEST_GYRO_EN            0x0004
#define SELFTEST_GYRO_DIS           0x0000
#define SELFCAL_ACCEL_EN_MASK       0x0008
#define SELFCAL_ACCEL_EN            0x0008
#define SELFCAL_ACCEL_DIS           0x0000
#define SELFCAL_GYRO_EN_MASK        0x0010
#define SELFCAL_GYRO_EN             0x0010
#define SELFCAL_GYRO_DIS            0x0000
#define SELFCAL_GYRO_METHOD_MASK    0x0020
#define SELFCAL_SSOM_EN_MASK        0x0040
#define SELFCAL_SSOM_EN             0x0040
#define SELFCAL_SSOM_DIS            0x0000
#define SELFTEST_AVERAGE_TIME_MASK  0x0380
#define SELFTEST_ACCEL_THRESH_MASK  0x1C00
#define SELFTEST_GYRO_THRESH_MASK   0xE000

typedef enum {
	SELFTEST_AVG_TIME_10_MS  = 0x0000,
	SELFTEST_AVG_TIME_20_MS  = 0x0080,
	SELFTEST_AVG_TIME_40_MS  = 0x0100,
	SELFTEST_AVG_TIME_80_MS  = 0x0180,
	SELFTEST_AVG_TIME_160_MS = 0x0200,
	SELFTEST_AVG_TIME_320_MS = 0x0280
} selftest_average_time_t;

typedef enum {
	SELFTEST_ACCEL_THRESHOLD_5_PERCENT  = 0x0000,
	SELFTEST_ACCEL_THRESHOLD_10_PERCENT = 0x0400,
	SELFTEST_ACCEL_THRESHOLD_15_PERCENT = 0x0800,
	SELFTEST_ACCEL_THRESHOLD_20_PERCENT = 0x0c00,
	SELFTEST_ACCEL_THRESHOLD_25_PERCENT = 0x1000,
	SELFTEST_ACCEL_THRESHOLD_30_PERCENT = 0x1400,
	SELFTEST_ACCEL_THRESHOLD_40_PERCENT = 0x1800,
	SELFTEST_ACCEL_THRESHOLD_50_PERCENT = 0x1c00
} selftest_accel_threshold_t;

typedef enum {
	SELFTEST_GYRO_THRESHOLD_5_PERCENT  = 0x0000,
	SELFTEST_GYRO_THRESHOLD_10_PERCENT = 0x2000,
	SELFTEST_GYRO_THRESHOLD_15_PERCENT = 0x4000,
	SELFTEST_GYRO_THRESHOLD_20_PERCENT = 0x6000,
	SELFTEST_GYRO_THRESHOLD_25_PERCENT = 0x8000,
	SELFTEST_GYRO_THRESHOLD_30_PERCENT = 0xa000,
	SELFTEST_GYRO_THRESHOLD_40_PERCENT = 0xc000,
	SELFTEST_GYRO_THRESHOLD_50_PERCENT = 0xe000
} selftest_gyro_threshold_t;

/*
 * EDMP_STC_PATCH_EN
 */

#define EDMP_SELFTESTCAL_OTPDATA_ACCEL_X_STR_FT                 0xc
#define EDMP_SELFTESTCAL_OTPDATA_ACCEL_X_STR_FT_SIZE            2

/* selfTestCal_otpData_accel_y_str_ft
 *

 */
#define EDMP_SELFTESTCAL_OTPDATA_ACCEL_Y_STR_FT                 0xe
#define EDMP_SELFTESTCAL_OTPDATA_ACCEL_Y_STR_FT_SIZE            2

/* selfTestCal_otpData_accel_z_str_ft
 *

 */
#define EDMP_SELFTESTCAL_OTPDATA_ACCEL_Z_STR_FT                 0x10
#define EDMP_SELFTESTCAL_OTPDATA_ACCEL_Z_STR_FT_SIZE            2

typedef enum {
	SELFTEST_PATCH_EN_ACCEL_PHASE1  = 0x0001,
	SELFTEST_PATCH_EN_ACCEL_PHASE2  = 0x0002,
	SELFTEST_PATCH_EN_GYRO1_PHASE1  = 0x0004,
	SELFTEST_PATCH_EN_GYRO1_PHASE2  = 0x0008,
	SELFCAL_PATCH_EN_ACCEL_AX_MEMS  = 0x0010,
	SELFCAL_PATCH_EN_ACCEL_AX_CMOS  = 0x0020,
	SELFCAL_PATCH_EN_ACCEL_AY_MEMS  = 0x0040,
	SELFCAL_PATCH_EN_ACCEL_AY_CMOS  = 0x0080,
	SELFCAL_PATCH_EN_ACCEL_AZ_MEMS1 = 0x0100,
	SELFCAL_PATCH_EN_ACCEL_AZ_MEMS2 = 0x0200,
	SELFCAL_PATCH_EN_GYRO2_PHASE1   = 0x0400,
	SELFCAL_PATCH_EN_GYRO2_PHASE2   = 0x0800
} stc_patch_params_t;

static int set_stc_parameters(struct inv_mpu_state *st)
{
	int      res;
	u32 tmp_stc_params;
	u32 patch_settings, stc_results;
	u32 tmp1, tmp2;

	inv_power_up_sram(st);

	res = inv_ireg_read(st, selfTestCal_configParams, selfTestCal_configParams_size,  (u8 *)&tmp_stc_params);
	if (res)
		return res;
	pr_info("read stc_para=%x\n", tmp_stc_params);

	tmp_stc_params &= ~( SELFTESTCAL_INIT_EN_MASK
	                    | SELFTEST_ACCEL_EN_MASK
	                    | SELFTEST_GYRO_EN_MASK
	                    | SELFCAL_ACCEL_EN_MASK
	                    | SELFCAL_GYRO_EN_MASK
	                    | SELFCAL_SSOM_EN_MASK
	                    | SELFCAL_GYRO_METHOD_MASK
	                    | SELFTEST_AVERAGE_TIME_MASK
	                    | SELFTEST_ACCEL_THRESH_MASK
	                    | SELFTEST_GYRO_THRESH_MASK);
	//tmp_stc_params = 0;

	tmp_stc_params |= SELFTESTCAL_INIT_EN;
	tmp_stc_params |= SELFTEST_ACCEL_EN;
	tmp_stc_params |= SELFTEST_GYRO_EN;
	tmp_stc_params |= SELFTEST_ACCEL_THRESHOLD_50_PERCENT;
	tmp_stc_params |= SELFTEST_GYRO_THRESHOLD_50_PERCENT;
	tmp_stc_params |= SELFTEST_AVG_TIME_320_MS;

	pr_info("stc_para=%x\n", tmp_stc_params);
	inv_ireg_write(st, EDMP_STC_CONFIGPARAMS, EDMP_STC_CONFIGPARAMS_SIZE, (u8 *)(&tmp_stc_params));
	patch_settings = 0;
	inv_ireg_write(st, EDMP_STC_PATCH_EN, EDMP_STC_PATCH_EN_SIZE, (u8 *)(&patch_settings));
	stc_results = 0;
	res = inv_ireg_write(st, EDMP_STC_RESULTS, EDMP_STC_RESULTS_SIZE, (u8 *)(&stc_results));

#if 1
	tmp1 = 0;
	tmp2 = 0;
	stc_results = 0;
	inv_ireg_read(st, EDMP_STC_CONFIGPARAMS, EDMP_STC_CONFIGPARAMS_SIZE, (u8 *)(&tmp1));
	inv_ireg_read(st, EDMP_STC_RESULTS, EDMP_STC_RESULTS_SIZE, (u8 *)(&stc_results));
	inv_ireg_read(st, EDMP_STC_PATCH_EN, EDMP_STC_PATCH_EN_SIZE, (u8 *)(&tmp2));

	pr_info("read back paramm= %x %x, stc=%x\n", tmp1, tmp2, stc_results);
#endif

	return res;
}

static void inv_debug_print(struct inv_mpu_state *st) {
	u8 v, v2, v3, v4, v5;
	u8 data[6];

	inv_plat_read(st, REG_PWR_MGMT0_DREG_BANK1, 1, &v);
	inv_plat_read(st, REG_DMP_EXT_SEN_ODR_CFG_DREG_BANK1, 1, &v2);

	inv_ireg_read(st, REG_STATUS_MASK_PIN_0_7_IPREG_TOP1, 1, &v3);
	inv_plat_read(st, REG_EDMP_APEX_EN1_DREG_BANK1, 1, &v4);
	inv_plat_read(st, REG_EDMP_APEX_EN0_DREG_BANK1, 1, &v5);

	pr_info("pwr=%x, ext_sen=%x, pin_07=%x, en1=%x, en0=%x\n", v, v2, v3,v4, v5);

	inv_ireg_read(st, REG_STATUS_MASK_PIN_8_15_IPREG_TOP1, 1, &v3);
	inv_ireg_read(st, REG_STATUS_MASK_PIN_16_23_IPREG_TOP1, 1, &v5);
	inv_ireg_read(st, es_power_mode, 1, &v2);
	inv_plat_read(st, REG_ACCEL_CONFIG0_DREG_BANK1, 1, &v4);
	pr_info("int_8_15=%x, es_pm=%x, accel_config0=%x, 16_23=%x\n", v3, v2, v4, v5);

	inv_ireg_read(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1, 1, &data[0]);
	inv_ireg_read(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1+1, 1, &data[1]);
	inv_ireg_read(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1+2, 1, &data[2]);
	inv_ireg_read(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1+3, 1, &data[3]);
	inv_ireg_read(st, REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1+4, 1, &data[4]);
	inv_ireg_read(st, REG_EDMP_SP_START_ADDR_IPREG_TOP1, 1, &v3);

	pr_info("data_new=%x %x, %x, %x,%x, stack=%x\n", data[0], data[1], data[2], data[3], data[4], v3);

	inv_ireg_read(st, EDMP_GYRO_X_STR_FT, 1, &v2);
	inv_ireg_read(st, EDMP_GYRO_Y_STR_FT, 1, &v3);
	inv_ireg_read(st, EDMP_GYRO_Z_STR_FT, 1, &v4);
	pr_info("gyro self test resp=%x %x %x\n", v2, v3, v4);

	inv_ireg_read(st, EDMP_SELFTESTCAL_OTPDATA_ACCEL_X_STR_FT, 1, &v2);
	inv_ireg_read(st, EDMP_SELFTESTCAL_OTPDATA_ACCEL_Y_STR_FT, 1, &v3);
	inv_ireg_read(st, EDMP_SELFTESTCAL_OTPDATA_ACCEL_Z_STR_FT, 1, &v4);
	pr_info("Accel self test resp=%x %x %x\n", v2, v3, v4);

}

static int inv_imu_run_stc(struct inv_mpu_state *st, int *accel, int *gyro)
{
	int res;
	u32 stc_results;

	res = inv_imu_soft_reset(st);

	msleep(10);
	/* apply parameters as we reset the device before */
	res = set_stc_parameters(st);
	if (res)
		return res;

	res = inv_imu_run_internal_stc(st);

	stc_results = 0;
	/* Read STC results */
	res = inv_ireg_read(st, EDMP_STC_RESULTS, EDMP_STC_RESULTS_SIZE, (u8 *)(&stc_results));
	if (res)
		return res;

	pr_info("self test result=%x\n", stc_results);

	*accel = ((stc_results & (STC_RESULTS_ACCEL_X_MASK | STC_RESULTS_ACCEL_Y_MASK | STC_RESULTS_ACCEL_Z_MASK)) == 0) ?
		    1 : 0;

	*gyro = ((stc_results & (STC_RESULTS_GYRO_X_MASK | STC_RESULTS_GYRO_Y_MASK | STC_RESULTS_GYRO_Z_MASK)) == 0) ?
		    1 : 0;

	pr_info("final=%x %x\n", *accel, *gyro);
	usleep_range(1000, 2000);

	inv_debug_print(st);

	res = inv_imu_soft_reset(st);

	return res;
}

/*
 *  inv_hw_self_test() - main function to do hardware self test
 */
int inv_hw_self_test(struct inv_mpu_state *st)
{
	int res;
	int accel_result = 0;
	int gyro_result = 0;
	int i;
	u8 v;

	//inv_debug_print(st);
	pr_info("start self test\n");
	inv_imu_edmp_init_apex(st, 1);
	//inv_debug_print(st);
	v = 0x0;
	for (i = 0; i < EDMP_STC_PATCH_EN_SIZE; i++) {
		res = inv_ireg_single_write(st, EDMP_STC_PATCH_EN + i, v);
		if (res)
			return res;
	}
	res = inv_imu_run_stc(st, &accel_result, &gyro_result);
	if (res)
		return 0;

	return ((accel_result << 1) | gyro_result);
}
