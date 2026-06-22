/*
* Copyright (C) 2017-2019 InvenSense, Inc.
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

/* AKM definitions */
#define REG_AKM_ID			0x00
#define REG_AKM_INFO			0x01
#define REG_AKM_STATUS			0x02
#define REG_AKM_MEASURE_DATA		0x03
#define REG_AKM_MODE			0x0A
#define REG_AKM_ST_CTRL			0x0C
#define REG_AKM_SENSITIVITY		0x10
#define REG_AKM8963_CNTL1		0x0A

/* AK0991X register definition */
#define REG_AK0991X_ST1			0x10
#define REG_AK0991X_CNTL2		0x31

/* AK09916 register definition */
#define REG_AK09916_MEASURE_DATA	0x11
#define DATA_AKM_ID			0x48
#define DATA_AKM_MODE_PD		0x00
#define DATA_AKM_MODE_SM		0x01
#define DATA_AKM_MODE_ST		0x08
#define DATA_AK09911_MODE_ST		0x10
#define DATA_AK09912_MODE_ST		0x10
#define DATA_AK09916_MODE_ST		0x10
#define DATA_AKM_MODE_FR		0x0F
#define DATA_AK09911_MODE_FR		0x1F
#define DATA_AK09912_MODE_FR		0x1F
#define DATA_AKM_SELF_TEST		0x40
#define DATA_AKM_DRDY			0x01
#define DATA_AKM8963_BIT		0x10
#define DATA_AKM_STAT_MASK		0x0C

/* 0.3 uT * (1 << 30) */
#define DATA_AKM8975_SCALE		322122547
/* 0.6 uT * (1 << 30) */
#define DATA_AKM8972_SCALE		644245094
/* 0.6 uT * (1 << 30) */
#define DATA_AKM8963_SCALE0		644245094
/* 0.15 uT *(1 << 30) */
#define DATA_AKM8963_SCALE1		161061273
/* 0.6 uT * (1 << 30) */
#define DATA_AK09911_SCALE		644245094
/* 0.15 uT * (1 << 30) */
#define DATA_AK09912_SCALE		161061273
/* 0.15 uT * (1 << 30) */
#define DATA_AK09916_SCALE		161061273
/* 0.15 uT * (1 << 30) */
#define DATA_AK09915_SCALE              161061273

#define DATA_AKM8963_SCALE_SHIFT	4
#define DATA_AKM_MIN_READ_TIME		(9 * NSEC_PER_MSEC)

/* AK09912C NSF */
/* 0:disable, 1:Low, 2:Middle, 3:High */
#define DATA_AK9912_NSF			1
#define DATA_AK9912_NSF_SHIFT		5

#define DEF_ST_COMPASS_WAIT_MIN		(10 * 1000)
#define DEF_ST_COMPASS_WAIT_MAX		(15 * 1000)
#define DEF_ST_COMPASS_TRY_TIMES	10
#define DEF_ST_COMPASS_8963_SHIFT	2
#define X	0
#define Y	1
#define Z	2

/* milliseconds between each access */
#define AKM_RATE_SCALE			10

/*
 *  inv_setup_compass_akm() - Configure akm series compass.
 */
static int inv_setup_compass_akm(struct inv_mpu_state *st)
{
	int res;
	u8 addr;
	u8 i2cm_ch, i2cm_lenW, i2cm_lenR;
	u8 i2cm_command_x;

	addr = st->plat_data.secondary_i2c_addr;
	pr_info("setup_akm_compass=%d\n", addr);

	/* ES0 setup using I2CM_COMMAND0, 1 */
	i2cm_ch = 0, i2cm_lenW = 2, i2cm_lenR = 9;

	/* Setup profile device ID and read register addresses */
	res = inv_ireg_single_write(st, REG_I2CM_DEV_PROFILE0_IPREG_TOP1,
					REG_AK0991X_ST1);
	if (res)
		return res;
	res = inv_ireg_single_write(st, REG_I2CM_DEV_PROFILE1_IPREG_TOP1, addr);
	if (res)
		return res;

	/* Setup to read registers, Command 0 using channel 0 */
	i2cm_command_x = (0x00 << REG_I2CM_COMMAND_0_ENDFLAG_0_POS) |
			(i2cm_ch << REG_I2CM_COMMAND_0_CH_SEL_0_POS) |
			(0x01 << REG_I2CM_COMMAND_0_R_W_0_POS) |
			(i2cm_lenR << REG_I2CM_COMMAND_0_BURSTLEN_0_POS);
	res= inv_ireg_single_write(st, REG_I2CM_COMMAND_0_IPREG_TOP1, i2cm_command_x);
	if (res)
		return res;
	/* Setup to write registers, Command 1 using channel 0 */
	i2cm_command_x = (0 << REG_I2CM_COMMAND_0_ENDFLAG_0_POS) |
			(i2cm_ch << REG_I2CM_COMMAND_0_CH_SEL_0_POS) |
			(0x00 << REG_I2CM_COMMAND_0_R_W_0_POS) |
			(i2cm_lenW << REG_I2CM_COMMAND_0_BURSTLEN_0_POS);
	res = inv_ireg_single_write(st, REG_I2CM_COMMAND_1_IPREG_TOP1, i2cm_command_x);
	if (res)
		return res;

	/* Load data to write. Reg CNTL2 = 0x01 for single measurement */
	res = inv_ireg_single_write(st, REG_I2CM_WR_DATA0_IPREG_TOP1,
							REG_AK0991X_CNTL2);
	if (res)
		return res;

	res = inv_ireg_single_write(st, REG_I2CM_WR_DATA1_IPREG_TOP1,
							DATA_AKM_MODE_SM);
	if (res)
		return res;

	return res;
}

/*
 *  inv_read_akm_scale() - show AKM scale.
 */
static int inv_read_akm_scale(struct inv_mpu_state *st, int *scale)
{
	if (COMPASS_ID_AK8975 == st->plat_data.sec_slave_id)
		*scale = DATA_AKM8975_SCALE;
	else if (COMPASS_ID_AK8972 == st->plat_data.sec_slave_id)
		*scale = DATA_AKM8972_SCALE;
	else if (COMPASS_ID_AK8963 == st->plat_data.sec_slave_id)
		if (st->slave_compass->scale)
			*scale = DATA_AKM8963_SCALE1;
		else
			*scale = DATA_AKM8963_SCALE0;
	else if (COMPASS_ID_AK09911 == st->plat_data.sec_slave_id)
		*scale = DATA_AK09911_SCALE;
	else if (COMPASS_ID_AK09912 == st->plat_data.sec_slave_id)
		*scale = DATA_AK09912_SCALE;
	else if (COMPASS_ID_AK09916 == st->plat_data.sec_slave_id)
		*scale = DATA_AK09916_SCALE;
	else if (COMPASS_ID_AK09915 == st->plat_data.sec_slave_id)
		*scale = DATA_AK09915_SCALE;
	else
		return -EINVAL;

	return IIO_VAL_INT;
}

static int inv_suspend_akm(struct inv_mpu_state *st)
{
	return 0;
}

static int inv_resume_akm(struct inv_mpu_state *st)
{
	return 0;
}

static struct inv_mpu_slave slave_akm = {
	.suspend = inv_suspend_akm,
	.resume = inv_resume_akm,
	.get_scale = inv_read_akm_scale,
	.setup = inv_setup_compass_akm,
	.rate_scale = AKM_RATE_SCALE,
	.min_read_time = DATA_AKM_MIN_READ_TIME,
};

int inv_mpu_setup_compass_slave(struct inv_mpu_state *st)
{
	switch (st->plat_data.sec_slave_id) {
	case COMPASS_ID_AK8975:
	case COMPASS_ID_AK8972:
	case COMPASS_ID_AK8963:
	case COMPASS_ID_AK09911:
	case COMPASS_ID_AK09912:
	case COMPASS_ID_AK09915:
	case COMPASS_ID_AK09916:
		st->slave_compass = &slave_akm;
		break;
	default:
		return -EINVAL;
	}

	return st->slave_compass->setup(st);
}
