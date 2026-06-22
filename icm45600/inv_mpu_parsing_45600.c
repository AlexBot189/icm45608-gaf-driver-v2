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

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/sysfs.h>
#include <linux/jiffies.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/kfifo.h>
#include <linux/poll.h>
#include <linux/miscdevice.h>
#include <linux/math64.h>

#include "../inv_mpu_iio.h"
#include "inv_mpu_gaf.h"

static int inv_check_fsync(struct inv_mpu_state *st)
{

	return 0;
}

static void __maybe_unused inv_dump_debug_reg(struct inv_mpu_state *st)
{
	u8 v, v2, v3, v4, v5;

#if 0
	inv_plat_read(st, REG_PWR_MGMT0_DREG_BANK1, 1, &v);

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
#endif
	inv_plat_read(st, REG_FIFO_CONFIG1_0_DREG_BANK1, 1, &v4);
	inv_plat_read(st, REG_FIFO_CONFIG1_1_DREG_BANK1, 1, &v5);
	inv_plat_read(st, REG_FIFO_CONFIG2_DREG_BANK1, 1, &v);
	inv_plat_read(st, REG_FIFO_CONFIG0_DREG_BANK1, 1, &v3);
	pr_info("thresh=%x %x, conf2=%x, ff_conf0=%x\n", v4, v5, v, v3);

	inv_plat_read(st, REG_FIFO_CONFIG3_DREG_BANK1, 1, &v);
	inv_plat_read(st, REG_FIFO_CONFIG4_DREG_BANK1, 1, &v2);
	pr_info("ff_34=%x %x\n", v, v2);

#if 0
	inv_plat_read(st, REG_INT_APEX_CONFIG0_DREG_BANK1, 1, &v2);
	inv_plat_read(st, REG_INT_APEX_CONFIG1_DREG_BANK1, 1, &v3);

	inv_plat_read(st, REG_INT1_CONFIG0_DREG_BANK1, 1, &v4);
	inv_plat_read(st, REG_INT1_CONFIG1_DREG_BANK1, 1, &v5);
	pr_info("apex_int=%x %x, int1_config=%x %x\n", v2, v3, v4, v5);

	inv_plat_read(st, REG_FIFO_COUNT_0_DREG_BANK1, 1, &v4);
	inv_plat_read(st, REG_FIFO_COUNT_1_DREG_BANK1, 1, &v5);
	pr_info("fifc=%x %x\n", v4, v5);
#endif
}

static int inv_push_sensor(struct iio_dev *indio_dev, int ind, u64 t, s32 *raw)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);
	s32 calib[3] = { 0, 0, 0 };
	s16 s[3]  = {0, 0, 0};

	switch (ind) {
	case SENSOR_ACCEL:
		inv_push_16bytes_buffer(indio_dev, ind, t, raw, 0);
		break;
	case SENSOR_TEMP:
		inv_check_fsync(st);
		break;
	case SENSOR_GYRO:
		inv_push_gyro_data(indio_dev, raw, calib, t);
		break;
	case SENSOR_COMPASS:
		inv_push_16bytes_buffer(indio_dev, ind, t, raw, 0);
		break;
	case SENSOR_PRESSURE:
		s[0] = 0;
		s[1] = (raw[0] >> 16);
		s[2] = (raw[0] & 0xffff);
		inv_push_8bytes_buffer(indio_dev, ind, t, s);
		break;
	default:
		break;
	}

	return 0;
}

static bool inv_validate_fifo_data(s16 *lsb)
{
	bool ret = true;

	if ((lsb[0] == -32768) && (lsb[1] == -32768) && (lsb[2] == -32768))
		ret = false;

	return ret;
}

static int inv_push_45600_data(struct iio_dev *indio_dev, u8 *dptr)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);
	fifo_header_t header;
	fifo_header2_t header2;
	u8 *d;
	u8 p_4b;
	int i;
	s16 acc_lsb[3] = { 0, 0, 0 };
	s16 gyr_lsb[3] = { 0, 0, 0 };
	s16 mag_lsb[3] = { 0, 0, 0 };
	s32 pressure = 0;
	s32 acc[3], gyr[3], mag[3];
	bool valid_acc = false;
	bool valid_gyr = false;
	bool valid_mag = false;
	bool valid_pressure = false;

	d = dptr;

	header.Byte = *d;
	d++;
	/* check header 2 */
	if (header.bits.ext_header) {
		header2.Byte = *d;
		d++;
	} else {
		header2.Byte = 0;
	}
	pr_debug("header1=%x, header2=%x\n", header.Byte, header2.Byte);
	/* accel data */
	if (st->sensor[SENSOR_ACCEL].on) {
		if (header.bits.s0_bit) {
			acc_lsb[0] = (s16)be16_to_cpup((__be16 *) (&d[0]));
			acc_lsb[1] = (s16)be16_to_cpup((__be16 *) (&d[2]));
			acc_lsb[2] = (s16)be16_to_cpup((__be16 *) (&d[4]));
			valid_acc = inv_validate_fifo_data(acc_lsb);
		}
	}

	if (st->sensor[SENSOR_GYRO].on) {
		if (header.bits.ext_header)
			d = dptr + 8;
		else if (st->sensor[SENSOR_ACCEL].on)
			d = dptr + 7;
		else
			d = dptr + 1;

		gyr_lsb[0] = (s16)be16_to_cpup((__be16 *) (&d[0]));
		gyr_lsb[1] = (s16)be16_to_cpup((__be16 *) (&d[2]));
		gyr_lsb[2] = (s16)be16_to_cpup((__be16 *) (&d[4]));
		valid_gyr = inv_validate_fifo_data(gyr_lsb);
	}

//	if (st->sensor[SENSOR_COMPASS].on) {
	if (st->sensor[SENSOR_COMPASS].on && !st->chip_config.gaf_enabled) {
		if (st->sensor[SENSOR_GYRO].on || st->sensor[SENSOR_ACCEL].on)
			d = dptr + 14;
		else
			d = dptr + 2;
		if(header.bits.ext_header && header2.bits.es0_en)
		 {
			int local_counter;
			int reset_counter;

			local_counter = (st->mag_divider & 0xff);
			reset_counter = ((st->mag_divider >> 8) & 0xff);
			local_counter++;
			/* mag data is NOT always valid while we keep mag
			 * timestamp correct. We achieve this by keep the latest
			 * mag data and output with correct rate ratio.
			 * It is Ok because mag data is slow evolved compared
			 * with gyro/accel */
			if (header2.bits.es0_vld) {
				st->raw_compass_data[0] = (s16)le16_to_cpup((__le16 *) (&d[0]));
				st->raw_compass_data[1] = (s16)le16_to_cpup((__le16 *) (&d[2]));
				st->raw_compass_data[2] = (s16)le16_to_cpup((__le16 *) (&d[4]));
			}

			if (local_counter == reset_counter) {
				local_counter = 0;
				mag_lsb[0] = (s16)st->raw_compass_data[0];
				mag_lsb[1] = (s16)st->raw_compass_data[1];
				mag_lsb[2] = (s16)st->raw_compass_data[2];
				valid_mag = true;
			}
			st->mag_divider &= 0xff00;
			st->mag_divider |= local_counter;
			pr_debug("mag divider=%x\n", st->mag_divider);
			pr_debug("get mag=%d %d %d vld=%d\n", mag_lsb[0], mag_lsb[1], mag_lsb[2], valid_mag);
		}
	}

	if (st->sensor[SENSOR_PRESSURE].on) {
		if (st->sensor[SENSOR_GYRO].on || st->sensor[SENSOR_ACCEL].on)
			d = dptr + 14 + 9;
		else if (st->sensor[SENSOR_COMPASS].on)
			d = dptr + 2 + 9;
		else
			d = dptr + 2;

		/* put pressure sensor in ES1 whether mag is on or off */
		if(header.bits.ext_header && header2.bits.es1_en && header2.bits.es1_vld)
		 {
			pr_debug("pre:: %x %x %x, %d\n", d[0], d[1], d[2], (int)(d-dptr));

			p_4b = (d[2] & 0xf);
			p_4b <<= 4;
			p_4b >>= 4;

			pressure = p_4b;
			pressure <<= 8;
			pressure += d[1];
			pressure <<= 8;
			pressure += d[0];
			if (pressure) {
				st->prev_pressure = pressure;
				valid_pressure = true;
			} else {
				if (st->prev_pressure != 0) {
					pressure = st->prev_pressure;
					valid_pressure = true;
				}
			}

			//P = (POUT>>17) *40K + 70K
			pr_debug("get pressure in ES1=%d, %d\n", pressure, ((pressure * 2000)>>17)*20+70000);
			pressure = ((pressure * 2000)>>17)*20+70000;
			pressure *= 100;
		}
	}

	/* ─── GAF data extraction from ES0/ES1 ─── */
//	if (st->chip_config.gaf_enabled &&
//	    st->sensor[SENSOR_ACCEL].on && st->sensor[SENSOR_GYRO].on &&
//	    (!st->sensor[SENSOR_COMPASS].on && !st->sensor[SENSOR_PRESSURE].on)) {
	if (st->chip_config.gaf_enabled &&
 	    st->sensor[SENSOR_ACCEL].on && st->sensor[SENSOR_GYRO].on) {
		if (header.bits.ext_header && header2.bits.es0_en && header2.bits.es1_en) {
			u8 es0[9], es1[6];
			struct inv_mpu_gaf_outputs gaf_out = {0};
			int quat_q30[4];
			int bias_q16[3];
			u64 gaf_ts;

			/* ES0 at dptr+14 (9B), ES1 at dptr+23 (6B) */
			memcpy(es0, dptr + 14, 9);
			memcpy(es1, dptr + 23, 6);

			if (!inv_mpu_gaf_decode_fifo(st, es0, es1, &gaf_out) &&
			    gaf_out.frame_complete) {
				/* GRV quaternion: Q14 -> Q30 */
				if (gaf_out.grv_quat_valid) {
					quat_q30[0] = (int)gaf_out.grv_quat_q14[0] << 16;
					quat_q30[1] = (int)gaf_out.grv_quat_q14[1] << 16;
					quat_q30[2] = (int)gaf_out.grv_quat_q14[2] << 16;
					quat_q30[3] = (int)gaf_out.grv_quat_q14[3] << 16;

					gaf_ts = st->sensor[SENSOR_GYRO].ts;
					inv_push_16bytes_buffer(indio_dev, SIXQUAT_HDR,
						gaf_ts, quat_q30,
						(s16)gaf_out.gyr_accuracy_flag);
				}

				/* Gyro bias: Q12 -> Q16 */
				if (gaf_out.gyr_bias_valid) {
					bias_q16[0] = (int)gaf_out.gyr_bias_q12[0] << 4;
					bias_q16[1] = (int)gaf_out.gyr_bias_q12[1] << 4;
					bias_q16[2] = (int)gaf_out.gyr_bias_q12[2] << 4;

					gaf_ts = st->sensor[SENSOR_GYRO].ts;
					inv_push_16bytes_buffer(indio_dev, GYRO_CALIB_HDR,
						gaf_ts, bias_q16,
						(s16)gaf_out.gyr_accuracy_flag);
				}

				/* 9-axis RV quaternion (Q14→Q30) + heading (Q11) */
				if (gaf_out.rv_quat_valid) {
					quat_q30[0] = (int)gaf_out.rv_quat_q14[0] << 16;
					quat_q30[1] = (int)gaf_out.rv_quat_q14[1] << 16;
					quat_q30[2] = (int)gaf_out.rv_quat_q14[2] << 16;
					quat_q30[3] = (int)gaf_out.rv_quat_q14[3] << 16;

					gaf_ts = st->sensor[SENSOR_GYRO].ts;
					inv_push_16bytes_buffer(indio_dev, NINEQUAT_HDR,
						gaf_ts, quat_q30,
						gaf_out.rv_heading_q11);
				}

				/* Raw magnetometer (s16) */
				if (gaf_out.rmag_valid) {
					int rmag[3];
					rmag[0] = (int)gaf_out.rmag[0];
					rmag[1] = (int)gaf_out.rmag[1];
					rmag[2] = (int)gaf_out.rmag[2];

					gaf_ts = st->sensor[SENSOR_GYRO].ts;
					inv_push_16bytes_buffer(indio_dev, MAGRAW_HDR,
						gaf_ts, rmag, 1);
				}

				/* Magnetometer bias Q16(uT) + accuracy + anomalies */
				if (gaf_out.mag_bias_valid) {
					int magbias[3];
					s16 mag_flags;
					magbias[0] = gaf_out.mag_bias_q16[0];
					magbias[1] = gaf_out.mag_bias_q16[1];
					magbias[2] = gaf_out.mag_bias_q16[2];
					mag_flags = (s16)((gaf_out.mag_accuracy_flag << 8) |
							  (gaf_out.mag_anomalies & 0xff));

					gaf_ts = st->sensor[SENSOR_GYRO].ts;
					inv_push_16bytes_buffer(indio_dev, MAGBIAS_HDR,
						gaf_ts, magbias, mag_flags);
				}
			}
		}
	}

	/* normal resolution mode */
	acc[0] = acc_lsb[0];
	acc[1] = acc_lsb[1];
	acc[2] = acc_lsb[2];
	gyr[0] = gyr_lsb[0];
	gyr[1] = gyr_lsb[1];
	gyr[2] = gyr_lsb[2];

	/* send accel data */
	if (st->sensor[SENSOR_ACCEL].on) {
		if (header.bits.s0_bit && valid_acc) {
			inv_get_dmp_ts(st, SENSOR_ACCEL);
			st->sensor[SENSOR_ACCEL].sample_calib++;
			if (st->sensor[SENSOR_ACCEL].send &&
					(!st->ts_algo.first_drop_samples[SENSOR_ACCEL])) {
				inv_push_sensor(indio_dev, SENSOR_ACCEL,
						st->sensor[SENSOR_ACCEL].ts, acc);
			}
			if (st->ts_algo.first_drop_samples[SENSOR_ACCEL])
				st->ts_algo.first_drop_samples[SENSOR_ACCEL]--;
		}
	}

	/* send gyro data */
	if (st->sensor[SENSOR_GYRO].on) {
		if (header.bits.s1_bit && valid_gyr) {
			inv_get_dmp_ts(st, SENSOR_GYRO);
			st->sensor[SENSOR_GYRO].sample_calib++;
			if (st->sensor[SENSOR_GYRO].send &&
					(!st->ts_algo.first_drop_samples[SENSOR_GYRO])) {
				inv_push_sensor(indio_dev, SENSOR_GYRO,
						st->sensor[SENSOR_GYRO].ts, gyr);
			}
			if (st->ts_algo.first_drop_samples[SENSOR_GYRO])
				st->ts_algo.first_drop_samples[SENSOR_GYRO]--;
		}
	}

	/* GAF mode: compass data is delivered via GAF fusion output, skip raw push */
 	if (st->sensor[SENSOR_COMPASS].on && !st->chip_config.gaf_enabled) {
//	if (st->sensor[SENSOR_COMPASS].on) {
		if(header.bits.ext_header && header2.bits.es0_en && valid_mag) {
			inv_get_dmp_ts(st, SENSOR_COMPASS);
			st->sensor[SENSOR_COMPASS].sample_calib++;
			if (st->sensor[SENSOR_COMPASS].send &&
					(!st->ts_algo.first_drop_samples[SENSOR_COMPASS])) {
				for (i = 0; i < 3;i++) {
					mag[i] = mag_lsb[i];
				}
				inv_push_sensor(indio_dev, SENSOR_COMPASS,
						st->sensor[SENSOR_COMPASS].ts, mag);
			}
			if (st->ts_algo.first_drop_samples[SENSOR_COMPASS])
				st->ts_algo.first_drop_samples[SENSOR_COMPASS]--;
		}
	}

	if (st->sensor[SENSOR_PRESSURE].on) {
		if(header.bits.ext_header && header2.bits.es1_en && header2.bits.es1_vld) {
			inv_get_dmp_ts(st, SENSOR_PRESSURE);
			st->sensor[SENSOR_PRESSURE].sample_calib++;
			if (valid_pressure && st->sensor[SENSOR_PRESSURE].send &&
					(!st->ts_algo.first_drop_samples[SENSOR_PRESSURE])) {
				inv_push_sensor(indio_dev, SENSOR_PRESSURE,
							st->sensor[SENSOR_PRESSURE].ts, &pressure);
			}
			if (st->ts_algo.first_drop_samples[SENSOR_PRESSURE])
				st->ts_algo.first_drop_samples[SENSOR_PRESSURE]--;
		}
	}

	st->header_count--;

	return 0;
}


static int inv_prescan_fifo_data(struct inv_mpu_state *st, u8 *dptr)
{
	fifo_header_t header;
	fifo_header2_t header2;
	u8 *d;
	s16 acc_lsb[3] = { 0, 0, 0 };
	s16 gyr_lsb[3] = { 0, 0, 0 };
	bool valid_acc = false;
	bool valid_gyr = false;

	d = dptr;

	header.Byte = *d;
	d++;
	/* check header 2 */
	if (header.bits.ext_header) {
		header2.Byte = *d;
		d++;
	} else {
		header2.Byte = 0;
	}
	pr_debug("header1=%x, header2=%x\n", header.Byte, header2.Byte);
	/* accel data */
	if (header.bits.s0_bit) {
		acc_lsb[0] = (s16)be16_to_cpup((__be16 *) (&d[0]));
		acc_lsb[1] = (s16)be16_to_cpup((__be16 *) (&d[2]));
		acc_lsb[2] = (s16)be16_to_cpup((__be16 *) (&d[4]));
		valid_acc = inv_validate_fifo_data(acc_lsb);
		if (valid_acc)
			st->sensor[SENSOR_ACCEL].count++;
		d += 6;
	}
	if (header.bits.s1_bit) {
		if (header.bits.ext_header)
			d = dptr + 8;
		gyr_lsb[0] = (s16)be16_to_cpup((__be16 *) (&d[0]));
		gyr_lsb[1] = (s16)be16_to_cpup((__be16 *) (&d[2]));
		gyr_lsb[2] = (s16)be16_to_cpup((__be16 *) (&d[4]));
		valid_gyr = inv_validate_fifo_data(gyr_lsb);
		if (valid_gyr)
			st->sensor[SENSOR_GYRO].count++;
	}

	if(header.bits.ext_header && header2.bits.es0_en)
	 {
		int local_counter;
		int reset_counter;

		local_counter = (st->mag_divider & 0xff);
		reset_counter = ((st->mag_divider >> 8) & 0xff);
		local_counter++;

		if (local_counter == reset_counter) {
			st->sensor[SENSOR_COMPASS].count++;
			local_counter = 0;
		}
		st->mag_divider &= 0xff00;
		st->mag_divider |= local_counter;
	}

	/* put pressure sensor in ES1 whether mag is on or off */
	if(header.bits.ext_header && header2.bits.es1_en && header2.bits.es1_vld)
	{
		 st->sensor[SENSOR_PRESSURE].count++;
	}

	return 0;
}

static int inv_process_45600_data(struct iio_dev *indio_dev)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);
	int total_bytes, tmp, res, fifo_count, pk_size, i;
	u8 *dptr;
	bool done_flag;

	fifo_count = inv_get_last_run_time_non_dmp_record_mode(st);

	if (!fifo_count) {
		pr_debug("fifo count is 0\n");
		return 0;
	}
	pk_size = st->batch.pk_size;
	if (!pk_size)
		return -EINVAL;

	if (fifo_count >= (HARDWARE_FIFO_SIZE / st->batch.pk_size)) {
		pr_warn("fifo overflow pkt count=%d pkt sz=%d\n",
			fifo_count, st->batch.pk_size);
		return -EOVERFLOW;
	}
	st->header_count = fifo_count;


	fifo_count *= st->batch.pk_size;
	st->fifo_count = fifo_count;
	dptr = st->fifo_data_store;
	total_bytes = fifo_count;

	while (total_bytes > 0) {
		if (total_bytes < pk_size * MAX_FIFO_PACKET_READ)
			tmp = total_bytes;
		else
			tmp = pk_size * MAX_FIFO_PACKET_READ;
		res = inv_plat_read(st, REG_FIFO_DATA_DREG_BANK1, tmp, dptr);
		pr_debug("inside: %x, %x, %x, %x, %x, %x, %x, %x\n",
			dptr[0], dptr[1], dptr[2], dptr[3],
			dptr[4], dptr[5], dptr[6], dptr[7]);
		pr_debug("insid2: %x, %x, %x, %x, %x, %x, %x, %x\n",
			dptr[8], dptr[9], dptr[10], dptr[11],
			dptr[12], dptr[13], dptr[14], dptr[15]);
		pr_debug("insid3: %x, %x, %x, %x, %x, %x, %x, %x\n",
			dptr[16], dptr[17], dptr[18], dptr[19],
			dptr[20], dptr[21], dptr[22], dptr[23]);
		pr_debug("insid4: %x, %x, %x, %x, %x, %x, %x, %x\n",
			dptr[24], dptr[25], dptr[26], dptr[27],
			dptr[28], dptr[29], dptr[30], dptr[31]);

		dptr += tmp;
		total_bytes -= tmp;
	}

	done_flag = false;
	for (i = 0; i < SENSOR_NUM_MAX; i++) {
		st->sensor[i].count = 0;
	}

	dptr = st->fifo_data_store;
	total_bytes = fifo_count;

	/* save the mag_divider before entering pre-scan function,
	 * it needs to recovered for the push data function */
	st->mag_first_drop_cnt = st->mag_divider;
	while (!done_flag) {
		pr_debug("total=%d, pk=%d\n", total_bytes, pk_size);
		if (total_bytes >= pk_size) {
			res = inv_prescan_fifo_data(st, dptr);
			if (res)
				return res;
			total_bytes -= pk_size;
			dptr += pk_size;
		} else {
			done_flag = true;
		}
	}
	st->mag_divider = st->mag_first_drop_cnt;
#if 0
	//if ((st->batch.timeout > 0) && st->sensor[SENSOR_COMPASS].on) {
	if ((st->batch.timeout > 0)) {
		inv_dump_debug_reg(st);
		pr_info("count a=%d, g=%d, c=%d\n", st->sensor[SENSOR_ACCEL].count,
					st->sensor[SENSOR_GYRO].count,
					st->sensor[SENSOR_COMPASS].count);
		pr_info("total=%d, pk=%d\n", fifo_count, pk_size);
		if (st->sensor[SENSOR_COMPASS].count == 0) {
			dptr = st->fifo_data_store;
			pr_debug("inside: %x, %x, %x, %x, %x, %x, %x, %x\n",
			dptr[0], dptr[1], dptr[2], dptr[3],
			dptr[4], dptr[5], dptr[6], dptr[7]);
			pr_debug("insid2: %x, %x, %x, %x, %x, %x, %x, %x\n",
			dptr[8], dptr[9], dptr[10], dptr[11],
			dptr[12], dptr[13], dptr[14], dptr[15]);
		}
	}
#endif
	st->ts_algo.calib_counter++;
	inv_bound_timestamp(st);

	dptr = st->fifo_data_store;
	total_bytes = fifo_count;

	done_flag = false;
	while (!done_flag) {
		pr_debug("total=%d, pk=%d\n", total_bytes, pk_size);
		if (total_bytes >= pk_size) {
			res = inv_push_45600_data(indio_dev, dptr);
			if (res)
				return res;
			total_bytes -= pk_size;
			dptr += pk_size;
		} else {
			done_flag = true;
		}
	}

	return 0;
}

static int _inv_read_steps(struct inv_mpu_state *st, u8 *r, u8 wptr, bool *full,
	u8 buffer_mgmt)
{
	if (st->apex_data.step_rptr & 1) {
		inv_ireg_read(st, ped_step_cnt_buf2, 1, &r[0]);
		inv_ireg_read(st, ped_step_cnt_buf2+1, 1, &r[1]);
	} else {
		inv_ireg_read(st, ped_step_cnt_buf1, 1, &r[0]);
		inv_ireg_read(st, ped_step_cnt_buf1+1, 1, &r[1]);
	}

	if ((st->apex_data.step_rptr & 1) == (wptr & 1)) {
		*full = true;
	} else {
		*full = false;
	}
	pr_debug("read steps: %x %x, wptr=%d, rptr=%d, full=%d\n", r[0], r[1], wptr, st->apex_data.step_rptr, *full);
	st->apex_data.step_rptr++;
	st->apex_data.step_rptr &= 3;

	buffer_mgmt &= (~REG_APEX_BUFFER_MGMT_STEP_COUNT_HOST_RPTR_MASK);
	buffer_mgmt |= (st->apex_data.step_rptr
		<< REG_APEX_BUFFER_MGMT_STEP_COUNT_HOST_RPTR_POS);

	return inv_plat_single_write(st, REG_APEX_BUFFER_MGMT_DREG_BANK1, buffer_mgmt);

}

int inv_get_45600_pedometer_steps(struct inv_mpu_state *st, int *ped,
								int *update)
{
	u8 buffer_mgmt = 0;
	u8 wptr;
	u32 cur_step_cnt;
	int res;
	u8 r[2];
	bool buffer_full;

	res = inv_plat_read(st, REG_APEX_BUFFER_MGMT_DREG_BANK1, 1, &buffer_mgmt);
	if (res)
		return res;
	wptr = (buffer_mgmt & REG_APEX_BUFFER_MGMT_STEP_COUNT_EDMP_WPTR_MASK);
	pr_debug("Enter:rptr=%x, wptr=%x, mgmt=%x\n", st->apex_data.step_rptr,
							wptr, buffer_mgmt);

	if (st->apex_data.step_rptr == wptr) {
		*update = false;
		return 0;
	}

	buffer_full = false;
	r[0] = 0;
	r[1] = 0;

	_inv_read_steps(st, r, wptr, &buffer_full, buffer_mgmt);

	if (buffer_full) {
		msleep(40);
		pr_debug("buffer full, read again\n");
		_inv_read_steps(st, r, wptr, &buffer_full, buffer_mgmt);
	}

	cur_step_cnt = r[1];
	cur_step_cnt <<= 8;
	cur_step_cnt += r[0];
	pr_debug("reset lastvale=%d\n", st->apex_data.step_reset_last_val);
	if (st->apex_data.step_reset_last_val) {
		st->apex_data.step_reset_last_val = false;
		st->apex_data.step_cnt_last_val = cur_step_cnt;
		st->apex_data.step_cnt_total += cur_step_cnt;
	}
	pr_debug("cur=%d, last_val=%d\n", cur_step_cnt, st->apex_data.step_cnt_last_val);
	if (cur_step_cnt !=
		st->apex_data.step_cnt_last_val) {
		if (cur_step_cnt < st->apex_data.step_cnt_last_val) {
			/* overflow */
			st->apex_data.step_cnt_total +=
				cur_step_cnt + (0xFFFF - st->apex_data.step_cnt_last_val);
		} else {
			st->apex_data.step_cnt_total +=
				cur_step_cnt - st->apex_data.step_cnt_last_val;
		}
	}
	st->apex_data.step_cnt_last_val = cur_step_cnt;
	*ped = st->apex_data.step_cnt_total;
	*update = true;

	return res;
}

static int inv_get_tap_param(struct inv_mpu_state *st, s16 *s)
{
	u8 res_tap_num = 0;
	u8 res_tap_axe = 0;
	u8 res_tap_dir = 0;
	int res;

#define EDMP_interf_tap	0x8D
#define EDMP_interf_tap_size	0x1
#define EDMP_interf_tap_axis	0x8E
#define EDMP_interf_tap_axis_size	0x1
#define EDMP_interf_tap_direction	0x8F
#define EDMP_interf_tap_direction_size	0x1
#define EDMP_interf_double_tap_timing	0x90
#define EDMP_interf_double_tap_timing_size	0x1
#define EDMP_interf_tap_interrupt	0x91
#define EDMP_interf_tap_interrupt_size	0x1

	/* only double tap is reported its axes and direction
	 * single tap is reported with 0 */
	res = inv_ireg_read(st, EDMP_interf_tap, EDMP_interf_tap_size, &res_tap_num);
	if (res)
		return res;

	res = inv_ireg_read(st, EDMP_interf_tap_axis, EDMP_interf_tap_axis_size, &res_tap_axe);
	if (res)
		return res;

	res = inv_ireg_read(st, EDMP_interf_tap_direction, EDMP_interf_tap_direction_size, &res_tap_dir);
	if (res)
		return res;
	pr_info("tap_detected: num=%d, axe=0x%x, dir=0x%x\n", res_tap_num, res_tap_axe, res_tap_dir);

	if (res_tap_num == 2)
		s[res_tap_axe] = (res_tap_dir ? -1 : 1);


	return res;
}

static int inv_process_apex_gesture(struct iio_dev *indio_dev)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);
	u8 apex_status0 = 0;
	u8 apex_status1 = 0;
	s16 s[3] = {0};
	u64 t;
	uint32_t cur_step_cnt;
	int ped_update;
	int result;

	if (inv_get_apex_enabled(st)) {
		t = get_time_ns();

		/* check INT_APEX_STATUS1 */
		result = inv_plat_read(st, REG_INT_APEX_STATUS1_DREG_BANK1, 1, &apex_status1);
		if (result)
			return result;

		/* SMD */
		if (st->smd.on && (apex_status1 & REG_INT_APEX_STATUS1_INT_STATUS_SMD_DET_MASK)) {
			sysfs_notify(&indio_dev->dev.kobj, NULL, "poll_smd");
			st->smd.on = false;
			set_inv_enable(indio_dev);
			st->wake_sensor_received = true;
		}

		/* check INT_APEX_STATUS0 */
		result = inv_plat_read(st, REG_INT_APEX_STATUS0_DREG_BANK1, 1, &apex_status0);
		if (result)
			return result;
		pr_debug("apex status=%x %x\n", apex_status0, apex_status1);

		/* Tilt */
		if (apex_status0 & REG_INT_APEX_STATUS0_INT_STATUS_TILT_DET_MASK) {
			if (st->chip_config.tilt_enable) {
				sysfs_notify(&indio_dev->dev.kobj, NULL, "poll_tilt");
				st->wake_sensor_received = true;
			}
		}
		/* tap */
		if (apex_status0 & REG_INT_APEX_STATUS0_INT_STATUS_TAP_DET_MASK) {
			inv_get_tap_param(st, s);
			inv_push_8bytes_buffer(indio_dev, TAP_HDR, t, s);
			st->wake_sensor_received = true;
		}

		/* pick up */
		if ((apex_status0 & REG_INT_APEX_STATUS0_INT_STATUS_R2W_WAKE_DET_MASK) ||
			(apex_status1 & REG_INT_APEX_STATUS1_INT_STATUS_R2W_SLEEP_DET_MASK)) {
			sysfs_notify(&indio_dev->dev.kobj, NULL, "poll_pick_up");
			//st->chip_config.pick_up_enable = 0;
			st->wake_sensor_received = true;
		}
		/* Step detector */
		if (apex_status0 & REG_INT_APEX_STATUS0_INT_STATUS_STEP_DET_MASK) {
			if (st->step_detector_l_on) {
				inv_push_8bytes_buffer(indio_dev,
					STEP_DETECTOR_HDR, t, s);
			}
			if (st->step_detector_wake_l_on) {
				inv_push_8bytes_buffer(indio_dev,
					STEP_DETECTOR_WAKE_HDR, t, s);
				st->wake_sensor_received = true;
			}
			if (st->ped.int_mode &&
				(st->step_counter_l_on || st->step_counter_wake_l_on)) {
				result = inv_get_45600_pedometer_steps(st,
					&cur_step_cnt, &ped_update);
				if (result)
					return result;
				if (ped_update)
					inv_send_steps(indio_dev, st->apex_data.step_cnt_total, t);
				if (st->step_counter_wake_l_on)
					st->wake_sensor_received = true;
			}
		}
	}
	return 0;
}

bool inv_mpu_interrupt_handler(struct iio_dev *indio_dev, s64 timestamp)
{
	return true;
}

/*
 *  inv_read_fifo() - Transfer data from FIFO to ring buffer.
 */
irqreturn_t inv_read_fifo(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct inv_mpu_state *st = iio_priv(indio_dev);
	int result;
	u8 int_status0, int_status1;

	result = wait_event_interruptible_timeout(st->wait_queue,
					st->resume_state, msecs_to_jiffies(300));
	if (result <= 0)
		goto exit_handled;

	mutex_lock(&st->lock);
	st->wake_sensor_received = false;

	/* Ensure data ready status bit is set */
	result = inv_plat_read(st, REG_INT1_STATUS0_DREG_BANK1, 1, &int_status0);
	result |= inv_plat_read(st, REG_INT1_STATUS1_DREG_BANK1, 1, &int_status1);
	if (result)
		goto err_reset_fifo;

	if (int_status1 & REG_INT1_STATUS1_INT1_STATUS_APEX_EVENT_MASK) {
		result = inv_process_apex_gesture(indio_dev);
		if (result)
			goto err_reset_fifo;
	}

	if (int_status0 &
		(BIT_INT1_STATUS_EN_FIFO_THS | BIT_INT1_STATUS_EN_FIFO_FULL)) {
		result = inv_process_45600_data(indio_dev);
		if (result)
			goto err_reset_fifo;
	}
	mutex_unlock(&st->lock);

	if (st->wake_sensor_received)
#ifdef CONFIG_HAS_WAKELOCK
		wake_lock_timeout(&st->wake_lock, msecs_to_jiffies(200));
#else
		__pm_wakeup_event(st->wake_lock, 200); /* 200 msecs */
#endif
	goto exit_handled;

err_reset_fifo:
	if ((!st->chip_config.gyro_enable) &&
		(!st->chip_config.accel_enable) &&
		(!st->chip_config.slave_enable) &&
		(!inv_get_apex_enabled(st))) {
		mutex_unlock(&st->lock);
		goto exit_handled;
	}

	pr_err("error to reset fifo\n");
	inv_reset_fifo(st, true);
	mutex_unlock(&st->lock);

exit_handled:
	iio_trigger_notify_done(indio_dev->trig);
	return IRQ_HANDLED;
}

int inv_flush_batch_data(struct iio_dev *indio_dev, int data)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);
	int result;
	u8 int_status0, int_status1;

	if (st->chip_config.gyro_enable ||
		st->chip_config.accel_enable ||
		st->chip_config.slave_enable ||
		inv_get_apex_enabled(st)) {

	/* Ensure data ready status bit is set */
	result = inv_plat_read(st, REG_INT1_STATUS0_DREG_BANK1, 1, &int_status0);
	result |= inv_plat_read(st, REG_INT1_STATUS1_DREG_BANK1, 1, &int_status1);

		st->wake_sensor_received = false;
		inv_process_45600_data(indio_dev);
		if (st->wake_sensor_received)
#ifdef CONFIG_HAS_WAKELOCK
			wake_lock_timeout(&st->wake_lock, msecs_to_jiffies(200));
#else
			__pm_wakeup_event(st->wake_lock, 200); /* 200 msecs */
#endif
	}
	inv_push_marker_to_buffer(indio_dev, END_MARKER, data);

	return 0;
}
