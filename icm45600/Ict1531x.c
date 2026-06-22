/*
 * Copyright (c) [2023] by InvenSense, Inc.
 * Adapted for Linux inv_mpu driver.
 * Changes from MCU version:
 *   - wait_us() uses udelay() instead of busy-wait loop
 *   - inv_ict1531x_get_time_us() declared extern (implemented in inv_mpu_mag.c)
 */

#include "Ict1531x.h"
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/string.h>

static void wait_us(u32 us)
{
	if (us < 10000)
		udelay(us);
	else
		usleep_range(us, us + 1000);
}

void inv_ict1531x_reset_states(struct inv_ict1531x *s,
			       const struct inv_ict1531x_serif *serif)
{
	memset(s, 0, sizeof(*s));
	s->serif = *serif;
	s->serif.is_first_transaction = 1;
}

int inv_ict1531x_poll_data(struct inv_ict1531x *s, s16 *compass_data_lsb,
			   s16 *temp_data_lsb)
{
	int rc = 1;
	u8 data[10] = { 0 };

	if (s->compass_en) {
		rc = inv_ict1531x_serif_read_reg(&s->serif,
						 ICT1531X_STATUS_REG, data, 1);
		if (rc != 0)
			return rc;

		if ((data[0] & ICT1531X_STATUS_REG_DATA_READY_MASK) == 0)
			return 1;

		rc = inv_ict1531x_serif_read_reg(&s->serif,
						 ICT1531X_FRAME_CNT_REG,
						 &data[1], 9);
		if (rc != 0) {
			s->compass_en = 0;
			return rc;
		}

		s->frame_cnt = data[1];
		*temp_data_lsb = (((s16)data[3]) << 8) | data[2];
		compass_data_lsb[0] = (((s16)data[5]) << 8) | data[4];
		compass_data_lsb[1] = (((s16)data[7]) << 8) | data[6];
		compass_data_lsb[2] = (((s16)data[9]) << 8) | data[8];
	}

	return rc;
}

int inv_ict1531x_get_whoami(struct inv_ict1531x *s, u8 *whoami)
{
	return inv_ict1531x_serif_read_reg(&s->serif,
					   ICT1531X_CHIP_ID_REG, whoami, 1);
}

int inv_ict1531x_soft_reset(struct inv_ict1531x *s)
{
	int rc = 0;
	u8 data;

	rc = inv_ict1531x_global_lock(s, 0);
	if (rc) return rc;

	rc = inv_ict1531x_serif_read_reg(&s->serif,
					 ICT1531X_SEQUENCER_CTRL_REG, &data, 1);
	if (rc) return rc;
	data &= ~ICT1531X_SEQUENCER_CTRL_REG_SOFT_RESET_MASK;
	data |= 1 << ICT1531X_SEQUENCER_CTRL_REG_SOFT_RESET_POS;
	rc = inv_ict1531x_serif_write_reg(&s->serif,
					  ICT1531X_SEQUENCER_CTRL_REG, &data, 1);
	if (rc) return rc;

	rc = inv_ict1531x_global_lock(s, 1);
	if (rc) return rc;

	rc = inv_ict1531x_set_mrm(s);
	return rc;
}

int inv_ict1531x_set_mode(struct inv_ict1531x *s, inv_ict1531x_mode_t mode)
{
	int rc = INV_ERROR_SUCCESS;
	u8 data;
	inv_ict1531x_mode_t cur_mode;

	if (mode == ICT1531X_MODE_CTRL_REG_MODE_PULSED)
		return INV_ERROR_NIMPL;

	rc |= inv_ict1531x_get_mode(s, &cur_mode);
	if ((rc == 0) && (cur_mode != ICT1531X_MODE_CTRL_REG_MODE_STANDBY)) {
		u8 data2;
		int timeout = 1000; /* max 10ms */
		rc = inv_ict1531x_serif_read_reg(&s->serif,
						 ICT1531X_MODE_CTRL_REG,
						 &data2, 1);
		if (rc) return rc;
		data2 &= ~ICT1531X_MODE_CTRL_REG_MODE_MASK;
		data2 |= ICT1531X_MODE_CTRL_REG_MODE_STANDBY;
		rc = inv_ict1531x_serif_write_reg(&s->serif,
						  ICT1531X_MODE_CTRL_REG,
						  &data2, 1);
		do {
			rc |= inv_ict1531x_get_mode(s, &cur_mode);
		} while ((rc == 0) && (cur_mode != ICT1531X_MODE_CTRL_REG_MODE_STANDBY) && (wait_us(10), --timeout > 0));
	}
	if (rc) return rc;

	if (mode == ICT1531X_MODE_CTRL_REG_MODE_STANDBY)
		return rc;

	rc = inv_ict1531x_serif_read_reg(&s->serif,
					 ICT1531X_MODE_CTRL_REG, &data, 1);
	if (rc) return rc;
	data &= ~ICT1531X_MODE_CTRL_REG_MODE_MASK;
	data |= mode;
	rc = inv_ict1531x_serif_write_reg(&s->serif,
					  ICT1531X_MODE_CTRL_REG, &data, 1);
	return rc;
}

int inv_ict1531x_get_mode(struct inv_ict1531x *s, inv_ict1531x_mode_t *cur_mode)
{
	int rc = INV_ERROR_SUCCESS;
	u8 data;

	rc = inv_ict1531x_serif_read_reg(&s->serif,
					 ICT1531X_MODE_STATUS_REG, &data, 1);
	if (rc) return rc;
	*cur_mode = (inv_ict1531x_mode_t)(data & ICT1531X_MODE_CTRL_REG_MODE_MASK);
	return rc;
}

int inv_ict1531x_set_temperature_mode(struct inv_ict1531x *s,
				      inv_ict1531x_chip_config_temp_sel_t temp_mode)
{
	int rc = INV_ERROR_SUCCESS;
	u8 data;

	rc = inv_ict1531x_serif_read_reg(&s->serif,
					 ICT1531X_MODE_STATUS_REG, &data, 1);
	if (rc) return rc;
	data &= ~ICT1531X_CHIP_CONFIG_REG_TEMP_SEL_MASK;
	data |= temp_mode;
	rc = inv_ict1531x_serif_write_reg(&s->serif,
					  ICT1531X_CHIP_CONFIG_REG, &data, 1);
	return rc;
}

int inv_ict1531x_enable_sensor(struct inv_ict1531x *s, u8 en)
{
	int rc = 0;

	if (en) {
		if (s->compass_en) {
			rc = INV_ERROR;
		} else {
			rc = inv_ict1531x_set_mode(s,
				ICT1531X_MODE_CTRL_REG_MODE_SINGLE_SHOT);
			s->compass_en = 1;
		}
	} else {
		rc = inv_ict1531x_set_mode(s,
			ICT1531X_MODE_CTRL_REG_MODE_STANDBY);
		s->compass_en = 0;
	}
	return rc;
}

int inv_ict1531x_set_mrm(struct inv_ict1531x *s)
{
	int rc = 0;
	rc = inv_ict1531x_set_mode(s, ICT1531X_MODE_CTRL_REG_MODE_MRM);
	wait_us(10);
	rc |= inv_ict1531x_set_mode(s, ICT1531X_MODE_CTRL_REG_MODE_STANDBY);
	return rc;
}

int inv_ict1531x_global_lock(struct inv_ict1531x *s, u8 lock)
{
	u8 data;
	if (!lock)
		data = 0xCA;
	else
		data = 0;
	return inv_ict1531x_serif_write_reg(&s->serif,
					    ICT1531X_GLOBAL_LOCK_REG, &data, 1);
}

static int get_stats_over_time_window(struct inv_ict1531x *s,
				      s16 max[3], s16 min[3])
{
	int rc = 0;
	s16 data[3];
	s16 temp;

	max[0] = S16_MIN;
	max[1] = S16_MIN;
	max[2] = S16_MIN;
	min[0] = S16_MAX;
	min[1] = S16_MAX;
	min[2] = S16_MAX;

	for (int i = 0; i < NUMBER_OF_SAMPLES_FOR_SELFTEST; i++) {
		rc |= inv_ict1531x_enable_sensor(s, 1);
		wait_us(4000);
		rc |= inv_ict1531x_poll_data(s, data, &temp);
		rc |= inv_ict1531x_enable_sensor(s, 0);
		for (int j = 0; j < 3; j++) {
			if (data[j] < min[j]) min[j] = data[j];
			if (data[j] > max[j]) max[j] = data[j];
		}
	}
	return rc;
}

int inv_ict1531x_selftest(struct inv_ict1531x *s,
			  inv_ict1531x_selftest_status_t *st_status)
{
	int rc = 0;

	st_status->status = ICT1531X_SELFTEST_SUCCESS;
	wait_us(2000);
	rc |= inv_ict1531x_set_mrm(s);
	wait_us(10);
	rc |= get_stats_over_time_window(s, st_status->max, st_status->min);
	for (int i = 0; i < 3; i++) {
		st_status->pp[i] = st_status->max[i] - st_status->min[i];
		if (st_status->pp[i] < 1)
			st_status->status |= 1 << i;
	}
	return rc;
}
