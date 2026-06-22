/*
 * Copyright (C) 2018-2021 InvenSense, Inc.
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

#include <linux/delay.h>
#include "../inv_mpu_iio.h"

/**
 * inv_set_idle() - Set Idle bit in PWR_MGMT_0 register
 * @st: struct inv_mpu_state.
 *
 * Set ACCEL_LP_CLK_SEL as well when necessary with a proper wait
 *
 * Return: 0 when successful.
 */
int inv_set_idle(struct inv_mpu_state *st)
{
	(void)st;
	return 0;
}

/**
 * inv_reset_idle() - Reset Idle bit in PWR_MGMT_0 register
 * @st: struct inv_mpu_state.
 *
 * Reset ACCEL_LP_CLK_SEL as well
 *
 * Return: 0 when successful.
 */
int inv_reset_idle(struct inv_mpu_state *st)
{
	(void)st;
	return 0;
}

static int check_out_of_bounds_mreg(uint32_t reg, uint32_t len)
{
	uint32_t min_addr = reg;
	uint32_t max_addr = reg + len - 1;

	/* AN-000364
	 * Users must not access the following register map address space to prevent stalling the device.
	 * - From 0x000023FF to 0x00003FFF
	 * - From 0x000083FF to 0x00009FFF
	 * - From 0x0000AFFF to 0xFFFFFFFF
	 * If user happens to access this space, soft reset is needed after the access to recover from stall.
	 */
	if (((min_addr > 0x000023FF) && (min_addr <= 0x00003FFF)) ||
	    ((max_addr > 0x000023FF) && (max_addr <= 0x00003FFF)) ||
	    ((min_addr <= 0x000023FF) && (max_addr > 0x00003FFF)))
		return -EINVAL;
	if (((min_addr > 0x000083FF) && (min_addr <= 0x00009FFF)) ||
	    ((max_addr > 0x000083FF) && (max_addr <= 0x00009FFF)) ||
	    ((min_addr <= 0x000083FF) && (max_addr > 0x00009FFF)))
		return -EINVAL;
	if (max_addr > 0x0000AFFF)
		return -EINVAL;

	return 0;
}

/**
 * inv_ireg_write() - bytes write to IREG area.
 * @st: struct inv_mpu_state.
 * @addr: IREG register address including bank in upper byte.
 * @size: number of bytes written into the IREG register.
 * @data: data to write.
 *
 * Return: 0 when successful.
 */
int inv_ireg_write(struct inv_mpu_state *st, int addr, int size, const u8 *data)
{
	u8 buf[3];
	int ret, i;

	if (!data || size <= 0)
		return -EINVAL;

	ret = check_out_of_bounds_mreg(addr, size);
	if (ret)
		return ret;

	buf[0] = (addr & 0xFF00) >> 8;
	buf[1] = addr & 0xFF;
	buf[2] = data[0];

	ret = inv_plat_write(st, REG_IREG_ADDR_15_8_DREG_BANK1, ARRAY_SIZE(buf), buf);
	udelay(4);
	if (ret)
		return ret;

	for (i = 1; i < size; ++i) {
		ret = inv_plat_single_write(st, REG_IREG_DATA_DREG_BANK1, data[i]);
		udelay(4);
		if (ret)
			return ret;
	}

	return ret;
}

/**
 * inv_ireg_read() - Multiple byte read from IREG area.
 * @st: struct inv_mpu_state.
 * @addr: IREG register start address including bank in upper byte.
 * @len: length to read in byte.
 * @data: pointer to store read data.
 *
 * Return: 0 when successful.
 */
int inv_ireg_read(struct inv_mpu_state *st, int addr, int len, u8 *data)
{
	u8 buf[2];
	int ret, i;

	if (!data || len <= 0)
		return -EINVAL;

	ret = check_out_of_bounds_mreg(addr, len);
	if (ret)
		return ret;

	buf[0] = (addr & 0xFF00) >> 8;
	buf[1] = addr & 0xFF;

	ret = inv_plat_write(st, REG_IREG_ADDR_15_8_DREG_BANK1, ARRAY_SIZE(buf), buf);
	udelay(4);
	if (ret)
		return ret;

	for (i = 0; i < len; i++) {
		ret = inv_plat_read(st, REG_IREG_DATA_DREG_BANK1, 1, &data[i]);
		udelay(4);
		if (ret)
			return ret;
	}

	return ret;
}

/**
 * inv_imu_soft_reset() - soft reset chip
 * @st: struct inv_mpu_state.
 *
 * Return: 0 when successful.
 */
int inv_imu_soft_reset(struct inv_mpu_state *st)
{
	u8 v;
	int res;

	/* Trigger soft reset */
	res = inv_plat_single_write(st, REG_REG_MISC2_DREG_BANK1, BIT_SOFT_RST);
	if (res)
		return res;
	usleep_range(1000, 2000);

	/* Clear the RESET_DONE interrupt */
	v = 0;
	while (!(v & REG_INT1_STATUS0_INT1_STATUS_RESET_DONE_MASK)) {
		res = inv_plat_read(st, REG_INT1_STATUS0_DREG_BANK1, 1, &v);
	}

	return res;
}

/**
 * inv_get_apex_enabled() - Check if any APEX feature is enabled
 * @st: struct inv_mpu_state.
 *
 * Return: true when any is enabled, otherwise false.
 */
bool inv_get_apex_enabled(struct inv_mpu_state *st)
{
	if (st->step_detector_l_on ||
		st->step_detector_wake_l_on ||
		st->step_counter_l_on ||
		st->step_counter_wake_l_on ||
		st->chip_config.tilt_enable ||
		st->smd.on ||
		st->chip_config.tap_enable ||
		st->chip_config.pick_up_enable)
		return true;

	return false;
}

/**
 * inv_get_apex_odr() - Get min accel ODR according to enabled APEX feature
 * @st: struct inv_mpu_state.
 *
 * Return: min accel ODR in Hz
 */
int inv_get_apex_odr(struct inv_mpu_state *st)
{
#if 1 // TODO
	int odr_hz = 0;

#ifdef SUPPORT_ACCEL_LPM
	odr_hz = MPU_INIT_SENSOR_RATE_LPM;
#else
	odr_hz = MPU_INIT_SENSOR_RATE_LNM;
#endif
	/* returns min accel rate for each algorithm */
	if (st->step_detector_l_on ||
		st->step_detector_wake_l_on ||
		st->step_counter_l_on ||
		st->step_counter_wake_l_on ||
		st->chip_config.tilt_enable ||
		st->smd.on)
		odr_hz = 50;

	return odr_hz;
#else
	(void)st;
	return 0;
#endif
}
