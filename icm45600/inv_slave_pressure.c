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

#define ICP201xx_REG_PRESS_DATA   0xFA
#define ICP201xx_REG_MODE_SELECT  0xC0
#define ICP201xx_REG_TRIG_CMD    0x90

/*
 *  inv_setup_icp() - Configure ICP20100 presssure sensor
 */
static int inv_setup_icp(struct inv_mpu_state *st)
{
	int res;
	u8 addr;
	u8 i2cm_ch, i2cm_lenW, i2cm_lenR;
	u8 i2cm_command_x;

	if (st->plat_data.aux_slave_id != PRESSURE_ID_ICP201XX) {
		pr_err("Error in pressure type. Only support ICP201XX\n");
		return -EINVAL;
	}
	//depending on AD0 value, it is either 0x64 or 0x63.
	// AD0 is a pin on the sensor.
	addr = st->plat_data.aux_i2c_addr;
	pr_info("setup pressure sensor=%d \n", addr);

	/* ES1 setup */
	i2cm_ch = 1, i2cm_lenW = 2, i2cm_lenR = 6;

	/* Setup profile device ID and read register addresses */
	res = inv_ireg_single_write(st, REG_I2CM_DEV_PROFILE2_IPREG_TOP1, ICP201xx_REG_PRESS_DATA);
	if (res)
		return res;
	res = inv_ireg_single_write(st, REG_I2CM_DEV_PROFILE3_IPREG_TOP1, addr);
	if (res)
		return res;

	/* Setup to read registers, Command 2 using channel 1 */
	i2cm_command_x = (0x00 << REG_I2CM_COMMAND_2_ENDFLAG_2_POS) |
			(i2cm_ch << REG_I2CM_COMMAND_2_CH_SEL_2_POS) |
			(0x01 << REG_I2CM_COMMAND_2_R_W_2_POS) |
			(i2cm_lenR << REG_I2CM_COMMAND_2_BURSTLEN_2_POS);
	res= inv_ireg_single_write(st, REG_I2CM_COMMAND_2_IPREG_TOP1, i2cm_command_x);
	if (res)
		return res;
	/* Setup to write registers, Command 3 using channel 1 */
	i2cm_command_x = (1 << REG_I2CM_COMMAND_3_ENDFLAG_3_POS) |
			(i2cm_ch << REG_I2CM_COMMAND_3_CH_SEL_3_POS) |
			(0x00 << REG_I2CM_COMMAND_3_R_W_3_POS) |
			(i2cm_lenW << REG_I2CM_COMMAND_3_BURSTLEN_3_POS);
	res = inv_ireg_single_write(st, REG_I2CM_COMMAND_3_IPREG_TOP1, i2cm_command_x);
	if (res)
		return res;

	/* Load data to write. Reg CNTL2 = 0x01 for single measurement */
	res = inv_ireg_single_write(st, REG_I2CM_WR_DATA2_IPREG_TOP1, ICP201xx_REG_MODE_SELECT);
	if (res)
		return res;

	res = inv_ireg_single_write(st, REG_I2CM_WR_DATA3_IPREG_TOP1, ICP201xx_REG_TRIG_CMD);

	return res;
}


static struct inv_mpu_slave slave_icp = {
	.setup = inv_setup_icp,
};

int inv_mpu_setup_pressure_slave(struct inv_mpu_state *st)
{
	st->slave_pressure = &slave_icp;

	return st->slave_pressure->setup(st);
}
