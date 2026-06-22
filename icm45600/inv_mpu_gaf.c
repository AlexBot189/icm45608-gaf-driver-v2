/*
 * Copyright (c) [2020] by InvenSense, Inc.
 * Adapted for Linux IIO inv_mpu driver.
 *
 * GAF frame decoding and initialization for ICM-45608 (6-axis / 9-axis).
 * All frame parsing logic is directly from MCU inv_imu_edmp.c.
 */

#include "inv_mpu_gaf.h"
#include "inv_mpu_mag.h"
#include "../inv_mpu_iio.h"
#include "inv_mpu_iio_reg_45600.h"

/* ─── Helper: read/write EDMP SRAM via IREG ─── */
static int gaf_ireg_write(struct inv_mpu_state *st, int addr,
			  int size, const u8 *data)
{
	return inv_ireg_write(st, addr, size, data);
}

static int gaf_ireg_read(struct inv_mpu_state *st, int addr,
			 int size, u8 *data)
{
	return inv_ireg_read(st, addr, size, data);
}

/* ─── GAF register direct access ─── */
/* EDMP_APEX_EN1 register (same in MCU and Linux driver) */
/* REG_EDMP_APEX_EN1_DREG_BANK1 from ICM45600_REG_External.h */
/* GAF_EN is bit 4 (0x10) - NOT defined in header, define locally */
#define REG_EDMP_APEX_EN1_GAF_EN_MASK        0x10

/* EDMP_APEX_EN0 register */
/* REG_EDMP_APEX_EN0_DREG_BANK1 from ICM45600_REG_External.h */

/* INT_APEX_CONFIG0 */
#define REG_INT_APEX_CONFIG0        0x21

/* REG_HOST_MSG */
/* REG_REG_HOST_MSG_DREG_BANK1 from ICM45600_REG_External.h */
/* IPREG_MISC */
//#define REG_IPREG_MISC              0x00E4
/* ─── Frame type detection (from MCU inv_imu_edmp.c:1376-1412) ─── */
int inv_mpu_gaf_get_frame_type(struct inv_mpu_state *st,
			       const u8 es1[6],
			       enum inv_mpu_gaf_frame_type *frame_type)
{
	status_byte_frameA_t *stA = (status_byte_frameA_t *)&es1[5];
	u8 gaf_mode = 0;
	int status;

	status = gaf_ireg_read(st, EDMP_GAF_MODE, 1, &gaf_mode);
	if (status)
		return status;

	if (stA->frame_id == FRAME_ID_FRAME_A) {
		if (stA->hrc_nfusion == 0) {
			switch (gaf_mode & (GAF_MODE_BITMASK_GYRO | GAF_MODE_BITMASK_MAG)) {
			case GAF_MODE_BITMASK_GYRO: /* AG mode */
				*frame_type = INV_MPU_GAF_QUAT_BIAS_GYR;
				break;
			case GAF_MODE_BITMASK_MAG: /* AM mode */
				*frame_type = INV_MPU_GAF_QUAT_RAW_MAG;
				break;
			case (GAF_MODE_BITMASK_GYRO | GAF_MODE_BITMASK_MAG): /* AGM */
				*frame_type = INV_MPU_GAF_QUAT_RAW_MAG_GYR_FLAGS;
				break;
			default:
				*frame_type = INV_MPU_GAF_QUAT_BIAS_GYR;
				break;
			}
		} else {
			switch (gaf_mode & (GAF_MODE_BITMASK_GYRO | GAF_MODE_BITMASK_MAG)) {
			case GAF_MODE_BITMASK_GYRO:
				*frame_type = INV_MPU_GAF_HRC_BIAS_GYR;
				break;
			case GAF_MODE_BITMASK_MAG:
				*frame_type = INV_MPU_GAF_HRC_RAW_MAG;
				break;
			case (GAF_MODE_BITMASK_GYRO | GAF_MODE_BITMASK_MAG):
				*frame_type = INV_MPU_GAF_HRC_BIAS_GYR_RAW_MAG;
				break;
			default:
				*frame_type = INV_MPU_GAF_HRC_BIAS_GYR;
				break;
			}
		}
	} else {
		if (stA->hrc_nfusion == 0)
			*frame_type = INV_MPU_GAF_BIAS_MAG_HEADING;
		else
			*frame_type = INV_MPU_GAF_HRC_BIAS_MAG;
	}

	return 0;
}

/* ─── FIFO decoder (from MCU inv_imu_edmp.c:1509-1689) ─── */
int inv_mpu_gaf_decode_fifo(struct inv_mpu_state *st,
			    const u8 es0[9], const u8 es1[6],
			    struct inv_mpu_gaf_outputs *out)
{
	enum inv_mpu_gaf_frame_type frame_type;
	status_byte_frameA_t *stA = (status_byte_frameA_t *)&es1[5];
	status_byte_frameB_t *stB = (status_byte_frameB_t *)&es1[5];
	hr_gxy_t *hr_gxy = (hr_gxy_t *)&es1[3];
	hr_gz_t  *hr_gz  = (hr_gz_t *)&es1[4];
	int status;

	status = inv_mpu_gaf_get_frame_type(st, es1, &frame_type);
	if (status)
		return status;

	switch (frame_type) {
	case INV_MPU_GAF_QUAT_BIAS_GYR:
		/* 6-axis GRV quaternion (Q14) */
		out->grv_quat_q14[0] = es0[0] + ((s32)es0[1] << 8);
		out->grv_quat_q14[1] = es0[2] + ((s32)es0[3] << 8);
		out->grv_quat_q14[2] = es0[4] + ((s32)es0[5] << 8);
		out->grv_quat_q14[3] = es0[6] + ((s32)es0[7] << 8);
		out->grv_quat_valid = 1;

		/* Gyro bias (Q12) */
		out->gyr_bias_q12[0] = es0[8] + ((s32)es1[0] << 8);
		out->gyr_bias_q12[1] = es1[1] + ((s32)es1[2] << 8);
		out->gyr_bias_q12[2] = es1[3] + ((s32)es1[4] << 8);
		out->gyr_bias_valid = 1;

		/* Accuracy and stationary */
		out->gyr_accuracy_flag = stA->accuracy;
		out->stationary_flag   = (s8)stA->stationary - 1;
		out->gyr_flags_valid   = 1;

		out->frame_complete = 1;
		break;

	case INV_MPU_GAF_QUAT_RAW_MAG:
		/* 6-axis GMRV quaternion (Q14) */
		out->gmrv_quat_q14[0] = es0[0] + ((s32)es0[1] << 8);
		out->gmrv_quat_q14[1] = es0[2] + ((s32)es0[3] << 8);
		out->gmrv_quat_q14[2] = es0[4] + ((s32)es0[5] << 8);
		out->gmrv_quat_q14[3] = es0[6] + ((s32)es0[7] << 8);
		out->gmrv_quat_valid = 1;

		/* Raw magnetometer */
		out->rmag[0] = es0[8] + ((s32)es1[0] << 8);
		out->rmag[1] = es1[1] + ((s32)es1[2] << 8);
		out->rmag[2] = es1[3] + ((s32)es1[4] << 8);
		out->rmag_valid = stA->rmag_valid;

		out->frame_complete = 1;
		break;

	case INV_MPU_GAF_QUAT_RAW_MAG_GYR_FLAGS:
		/* 9-axis RV quaternion (Q14) */
		out->rv_quat_q14[0] = es0[0] + ((s32)es0[1] << 8);
		out->rv_quat_q14[1] = es0[2] + ((s32)es0[3] << 8);
		out->rv_quat_q14[2] = es0[4] + ((s32)es0[5] << 8);
		out->rv_quat_q14[3] = es0[6] + ((s32)es0[7] << 8);
		out->rv_quat_valid = 1;

		/* Raw magnetometer + gyro flags */
		out->rmag[0] = es0[8] + ((s32)es1[0] << 8);
		out->rmag[1] = es1[1] + ((s32)es1[2] << 8);
		out->rmag[2] = es1[3] + ((s32)es1[4] << 8);
		out->rmag_valid = stA->rmag_valid;

		out->gyr_accuracy_flag = stA->accuracy;
		out->stationary_flag   = (s8)stA->stationary - 1;
		out->gyr_flags_valid   = 1;

		out->frame_complete = 1;
		break;

	case INV_MPU_GAF_BIAS_MAG_HEADING:
		/* RV heading (Q11) */
		out->rv_heading_q11 = es1[3] + ((s32)es1[4] << 8);
		out->rv_heading_valid = 1;

		/* MRM state */
		out->mrm_state = stB->mrm_state;
		out->mrm_state_valid = 1;

		/* Mag bias (Q16) */
		out->mag_bias_q16[0] = es0[0] + ((s32)es0[1] << 8) +
				       ((s32)es0[2] << 16) + ((s32)es0[3] << 24);
		out->mag_bias_q16[1] = es0[4] + ((s32)es0[5] << 8) +
				       ((s32)es0[6] << 16) + ((s32)es0[7] << 24);
		out->mag_bias_q16[2] = es0[8] + ((s32)es1[0] << 8) +
				       ((s32)es1[1] << 16) + ((s32)es1[2] << 24);
		out->mag_accuracy_flag = stB->accuracy;
		out->mag_anomalies     = stB->mag_anom;
		out->mag_bias_valid    = 1;

		out->frame_complete = 0;
		break;

	case INV_MPU_GAF_HRC_BIAS_GYR_RAW_MAG:
		out->rmag[0] = es0[6] + ((s32)es0[7] << 8);
		out->rmag[1] = es0[8] + ((s32)es1[0] << 8);
		out->rmag[2] = es1[1] + ((s32)es1[2] << 8);
		out->rmag_valid = stA->rmag_valid;

		out->gyr_bias_q12[0] = es0[0] + ((s32)es0[1] << 8);
		out->gyr_bias_q12[1] = es0[2] + ((s32)es0[3] << 8);
		out->gyr_bias_q12[2] = es0[4] + ((s32)es0[5] << 8);
		out->gyr_bias_valid = 1;

		out->gyr_accuracy_flag = stA->accuracy;
		out->stationary_flag   = (s8)stA->stationary - 1;
		out->gyr_flags_valid   = 1;

		out->hr_g[0] = hr_gxy->gx;
		out->hr_g[1] = hr_gxy->gy;
		out->hr_g[2] = hr_gz->gz;
		out->hr_g_valid = 1;

		out->frame_complete = 1;
		break;

	case INV_MPU_GAF_HRC_BIAS_GYR:
		out->gyr_bias_q12[0] = es0[0] + ((s32)es0[1] << 8);
		out->gyr_bias_q12[1] = es0[2] + ((s32)es0[3] << 8);
		out->gyr_bias_q12[2] = es0[4] + ((s32)es0[5] << 8);
		out->gyr_bias_valid = 1;

		out->gyr_accuracy_flag = stA->accuracy;
		out->stationary_flag   = (s8)stA->stationary - 1;
		out->gyr_flags_valid   = 1;

		out->hr_g[0] = hr_gxy->gx;
		out->hr_g[1] = hr_gxy->gy;
		out->hr_g[2] = hr_gz->gz;
		out->hr_g_valid = 1;

		out->frame_complete = 1;
		break;

	case INV_MPU_GAF_HRC_RAW_MAG:
		out->rmag[0] = es0[6] + ((s32)es0[7] << 8);
		out->rmag[1] = es0[8] + ((s32)es1[0] << 8);
		out->rmag[2] = es1[1] + ((s32)es1[2] << 8);
		out->rmag_valid = stA->rmag_valid;

		out->hr_g[0] = hr_gxy->gx;
		out->hr_g[1] = hr_gxy->gy;
		out->hr_g[2] = hr_gz->gz;
		out->hr_g_valid = 1;

		out->frame_complete = 1;
		break;

	case INV_MPU_GAF_HRC_BIAS_MAG:
		out->mag_bias_q16[0] = es0[0] + ((s32)es0[1] << 8) +
				       ((s32)es0[2] << 16) + ((s32)es0[3] << 24);
		out->mag_bias_q16[1] = es0[4] + ((s32)es0[5] << 8) +
				       ((s32)es0[6] << 16) + ((s32)es0[7] << 24);
		out->mag_bias_q16[2] = es0[8] + ((s32)es1[0] << 8) +
				       ((s32)es1[1] << 16) + ((s32)es1[2] << 24);
		out->mag_accuracy_flag = stB->accuracy;
		out->mag_anomalies     = stB->mag_anom;
		out->mag_bias_valid    = 1;

		out->mrm_state = stB->mrm_state;
		out->mrm_state_valid = 1;

		out->hr_g[0] = hr_gxy->gx;
		out->hr_g[1] = hr_gxy->gy;
		out->hr_g[2] = hr_gz->gz;
		out->hr_g_valid = 1;

		out->frame_complete = 0;
		break;

	default:
		return -1;
	}

	return 0;
}

/* ─── GAF mode set (from MCU inv_imu_edmp.c:859-878) ─── */
int inv_mpu_gaf_set_mode(struct inv_mpu_state *st,
			 u8 gyro_is_on, u8 mag_is_on)
{
	u8 gaf_mode = 0;
	int status;

	status = gaf_ireg_read(st, EDMP_GAF_MODE, 1, &gaf_mode);
	if (status)
		return status;

	/* Default is gyro ON */
	if (!gyro_is_on)
		gaf_mode &= ~GAF_MODE_BITMASK_GYRO;
	else
		gaf_mode |= GAF_MODE_BITMASK_GYRO;

	/* Default is mag ON */
	if (!mag_is_on)
		gaf_mode &= ~GAF_MODE_BITMASK_MAG;
	else
		gaf_mode |= GAF_MODE_BITMASK_MAG;

	status = gaf_ireg_write(st, EDMP_GAF_MODE, 1, &gaf_mode);

	return status;
}

/* ─── Mounting matrix (from MCU inv_imu_edmp.c:1012-1026) ─── */
int inv_mpu_gaf_set_mounting_matrix(struct inv_mpu_state *st,
				    const s8 matrix[9])
{
	const s16 edmp_matrix[9] = {
		(s16)matrix[0] << 14, (s16)matrix[1] << 14,
		(s16)matrix[2] << 14, (s16)matrix[3] << 14,
		(s16)matrix[4] << 14, (s16)matrix[5] << 14,
		(s16)matrix[6] << 14, (s16)matrix[7] << 14,
		(s16)matrix[8] << 14,
	};

	return gaf_ireg_write(st, EDMP_GLOBAL_MOUNTING_MATRIX,
			      sizeof(edmp_matrix), (const u8 *)edmp_matrix);
}

/* ─── Accel bias (from MCU inv_imu_edmp.c:847-857) ─── */
int inv_mpu_gaf_set_acc_bias(struct inv_mpu_state *st,
			     const s32 bias_q16[3])
{
	const u8 accuracy = 3;
	int status;

	status = gaf_ireg_write(st, EDMP_GAF_SAVED_ACC_BIAS_1G_Q16,
				12, (const u8 *)bias_q16);
	if (status)
		return status;
	status = gaf_ireg_write(st, EDMP_GAF_SAVED_ACC_ACCURACY,
				1, &accuracy);

	return status;
}

/* ─── Gyro bias (from MCU inv_imu_edmp.c:790-810) ─── */
int inv_mpu_gaf_set_gyr_bias(struct inv_mpu_state *st,
			     const s16 bias_q12[3])
{
	s32 gyr_bias[3] = { bias_q12[0], bias_q12[1], bias_q12[2] };
	s32 temperature_q16 = GAF_DEFAULT_TEMPERATURE_INIT_Q16;
	u32 accuracy = 0;
	int status;

	status = gaf_ireg_write(st, EDMP_GAF_GYR_BIAS_DPS_Q12,
				sizeof(gyr_bias), (const u8 *)gyr_bias);
	if (status)
		return status;
	status = gaf_ireg_write(st, EDMP_GAF_SAVED_GYR_ACCURACY,
				sizeof(accuracy), (const u8 *)&accuracy);
	if (status)
		return status;
	status = gaf_ireg_write(st, EDMP_GAF_GYR_BIAS_TEMPERATURE_DEG_Q16,
				sizeof(temperature_q16),
				(const u8 *)&temperature_q16);

	return status;
}

/* ─── FIFO push control (from MCU inv_imu_edmp.c:746-764) ─── */
int inv_mpu_gaf_start_fifo_push(struct inv_mpu_state *st)
{
	u8 gaf_mode;
	int status;

	status = gaf_ireg_read(st, EDMP_GAF_MODE, 1, &gaf_mode);
	if (status)
		return status;
	gaf_mode &= ~GAF_MODE_BITMASK_FIFO_PUSH;
	status = gaf_ireg_write(st, EDMP_GAF_MODE, 1, &gaf_mode);

	return status;
}

int inv_mpu_gaf_stop_fifo_push(struct inv_mpu_state *st)
{
	u8 gaf_mode;
	int status;

	status = gaf_ireg_read(st, EDMP_GAF_MODE, 1, &gaf_mode);
	if (status)
		return status;
	gaf_mode |= GAF_MODE_BITMASK_FIFO_PUSH;
	status = gaf_ireg_write(st, EDMP_GAF_MODE, 1, &gaf_mode);

	return status;
}

/* ─── GAF enable (from MCU inv_imu_edmp.c:1079-1103, 1216-1243) ─── */
int inv_mpu_gaf_enable(struct inv_mpu_state *st)
{
	u8 gaf_init = 0;
	u8 value;
	int i;
	int status;

	/* Reset GAF init status to force re-initialization with new params */
	status = gaf_ireg_write(st, EDMP_GAF_INIT_STATUS, 1, &gaf_init);
	if (status)
		return status;

	/* Enable GAF in APEX_EN1 */
	status = inv_plat_read(st, REG_EDMP_APEX_EN1_DREG_BANK1, 1, &value);
	if (status)
		return status;

	if (value & REG_EDMP_APEX_EN1_GAF_EN_MASK) {
		/* GAF already enabled, only re-set EDMP_ENABLE
		 * (EDMP may have been stopped by inv_stop_dmp) */
		value |= REG_EDMP_APEX_EN1_EDMP_ENABLE_MASK;
		status = inv_plat_single_write(st, REG_EDMP_APEX_EN1_DREG_BANK1, value);
		if (status)
			return status;
		pr_info("GAF: re-enabled EDMP_ENABLE\n");
		return 0;
	}

	value |= REG_EDMP_APEX_EN1_GAF_EN_MASK |
		 REG_EDMP_APEX_EN1_EDMP_ENABLE_MASK |
		 REG_EDMP_APEX_EN1_SOFT_HARD_IRON_CORR_EN_MASK;
	status = inv_plat_single_write(st, REG_EDMP_APEX_EN1_DREG_BANK1, value);
	if (status)
		return status;

	/* Unmask DRDY interrupts needed by GAF */
	{
		u8 host_msg;
		status = inv_plat_read(st, REG_REG_HOST_MSG_DREG_BANK1, 1, &host_msg);
		if (status)
			return status;

		/* EDMP interrupt sources: enable ACCEL_DRDY + GYRO_DRDY for EDMP */
		host_msg |= REG_REG_HOST_MSG_EDMP_ON_DEMAND_EN_MASK;
		status = inv_plat_single_write(st, REG_REG_HOST_MSG_DREG_BANK1, host_msg);
		if (status)
			return status;
	}

	/* Wait for EDMP idle (max 100 x 5ms = 500ms) */
	usleep_range(500, 1000);
	for (i = 0; i < 100; i++) {
		u8 ipreg_misc;
		status = gaf_ireg_read(st, REG_IPREG_MISC_IPREG_TOP1, 1, &ipreg_misc);
		if (status)
			return status;
		if (ipreg_misc & REG_IPREG_MISC_EDMP_IDLE_MASK)
			break;
		usleep_range(5000, 7000);
	}
	if (i >= 100) {
		pr_err("GAF: EDMP idle timeout after 500ms\n");
		return -1;
	}
	pr_info("GAF: EDMP idle OK after %d ms\n", i * 5 + 5);

	return 0;
}

/* ─── Read actual ODR from hardware and convert to us (MCU-compatible) ───
 * The sensor ODR is configured by inv_set_odr_and_filter() earlier in set_inv_enable().
 * We read the register bits and map to us, matching MCU get_accel/gyro_config_odr_us_from_hw().
 */
static u32 gaf_get_odr_us_from_hw(struct inv_mpu_state *st, int reg_addr)
{
	/* ODR bit encoding (ICM-45608 ODR bits [3:0]): code -> us */
	static const u32 odr_lut[16] = {
		[0x05] =   625, /* 1600 Hz */
		[0x06] =  1250, /*  800 Hz */
		[0x07] =  2500, /*  400 Hz */
		[0x08] =  5000, /*  200 Hz */
		[0x09] = 10000, /*  100 Hz */
		[0x0A] = 20000, /*   50 Hz */
		[0x0B] = 40000, /*   25 Hz */
		[0x0C] = 80000, /* 12.5 Hz */
		[0x0D] = 160000,/* 6.25 Hz */
		[0x0E] = 320000,/* 3.125 Hz */
	};
	u8 data;
	if (inv_plat_read(st, reg_addr, 1, &data))
		return 10000; /* default 100 Hz */
	data &= 0x0F;
	return odr_lut[data] ? odr_lut[data] : 10000;
}

/* ─── GAF config params (from MCU inv_imu_edmp.c:set_gaf_config) ───
 * Writes critical timing/control parameters to EDMP SRAM.
 * Other params remain at firmware defaults.
 */
int inv_mpu_gaf_set_config(struct inv_mpu_state *st,
			   u32 pdr_us, u8 run_spherical,
			   u32 mag_dt_us, u8 clock_variation)
{
	u32 acc_odr_us, gyr_odr_us;
	int status;

	/* Read actual ODR from hardware (written by inv_set_odr_and_filter).
	 * MCU reads ODR from hw registers, not from software running_rate. */
	acc_odr_us = gaf_get_odr_us_from_hw(st, REG_ACCEL_CONFIG0_DREG_BANK1);
	gyr_odr_us = gaf_get_odr_us_from_hw(st, REG_GYRO_CONFIG0_DREG_BANK1);

	pr_info("GAF: config acc_odr=%u us gyr_odr=%u us pdr=%u us fusion=%d mag_dt=%u us clk_var=%u\n",
		acc_odr_us, gyr_odr_us, pdr_us, run_spherical, mag_dt_us, clock_variation);

	/* Write core timing parameters */
	status  = gaf_ireg_write(st, EDMP_GAF_CONFIG_ACC_ODR_US,
				 EDMP_GAF_CONFIG_ACC_ODR_US_SIZE, (const u8 *)&acc_odr_us);
	status |= gaf_ireg_write(st, EDMP_GAF_CONFIG_GYR_ODR_US,
				 EDMP_GAF_CONFIG_GYR_ODR_US_SIZE, (const u8 *)&gyr_odr_us);
	status |= gaf_ireg_write(st, EDMP_GAF_CONFIG_ACC_PDR_US,
				 EDMP_GAF_CONFIG_ACC_PDR_US_SIZE, (const u8 *)&pdr_us);
	status |= gaf_ireg_write(st, EDMP_GAF_CONFIG_GYR_PDR_US,
				 EDMP_GAF_CONFIG_GYR_PDR_US_SIZE, (const u8 *)&pdr_us);
	status |= gaf_ireg_write(st, EDMP_GAF_CONFIG_PLL_CLOCK_VARIATION,
				 EDMP_GAF_CONFIG_PLL_CLOCK_VARIATION_SIZE, &clock_variation);
	status |= gaf_ireg_write(st, EDMP_GAF_CONFIG_RUN_SPHERICAL,
				 EDMP_GAF_CONFIG_RUN_SPHERICAL_SIZE, &run_spherical);

	/* Write mag timing (0 disables mag fusion) */
	status |= gaf_ireg_write(st, EDMP_GAF_CONFIG_MAG_DT_US,
				 EDMP_GAF_CONFIG_MAG_DT_US_SIZE, (const u8 *)&mag_dt_us);
	status |= gaf_ireg_write(st, EDMP_GAF_CONFIG_MAGCAL_DT_US,
				 EDMP_GAF_CONFIG_MAGCAL_DT_US_SIZE, (const u8 *)&mag_dt_us);

	return status;
}

/* ─── Full GAF init sequence (6-axis or 9-axis) ───
 * If mag_enabled==1, tries to detect ICT1531x magnetometer.
 * Falls back to 6-axis AG mode if mag detection fails.
 */
int inv_mpu_gaf_init(struct inv_mpu_state *st, int mag_enabled)
{
	pr_info("GAF: init start (mag=%d)\n", mag_enabled);
	/* Exoskeleton mounting matrix: X→-Z, Y→-Y, Z→-X */
	static const s8 exo_mounting[9] = {
		0,  0, -1,
		0, -1,  0,
		-1,  0,  0
	};
	/* Identity soft-iron matrix (Q30 format: 1 << 30 = 1073741824) */
	static const s32 ident_soft_iron[3][3] = {
		{ 1 << 30, 0,       0       },
		{ 0,       1 << 30, 0       },
		{ 0,       0,       1 << 30 },
	};
	/* Zero initial biases */
	const s32 zero_accel_bias[3] = { 0, 0, 0 };
	const s16 zero_gyro_bias[3] = { 0, 0, 0 };
	u32 pdr_us, mag_dt_us;
	u8 clock_variation = 0;
	int status;

	/* ── Step 0: Try to init magnetometer (if requested) ── */
		/* ── Step 0: Try to init magnetometer (if requested) ── */
	static int mag_done;
	if (mag_enabled && !mag_done) {
		status = inv_mpu_mag_init(st);
		if (status) {
			pr_warn("GAF: mag init failed, falling back to 6-axis\n");
			mag_enabled = 0;
		} else {
			mag_done = 1;
		}
	} else if (mag_enabled) {
		pr_info("GAF: mag already initialized, skip\n");
	}

	/* ── Step 1: Set GAF mode (6-axis AG or 9-axis AGM) ── */
	status = inv_mpu_gaf_set_mode(st, 1, mag_enabled);
	if (status) {
		pr_err("GAF: set_mode(gyro=1,mag=%d) failed=%d\n",
		       mag_enabled, status);
		return status;
	}
	pr_info("GAF: mode set OK (mag=%d)\n", mag_enabled);

	/* ── Step 2: Set zero initial biases ── */
	status = inv_mpu_gaf_set_acc_bias(st, zero_accel_bias);
	if (status) {
		pr_err("GAF: set_acc_bias failed=%d\n", status);
		return status;
	}
	status = inv_mpu_gaf_set_gyr_bias(st, zero_gyro_bias);
	if (status) {
		pr_err("GAF: set_gyr_bias failed=%d\n", status);
		return status;
	}
	pr_info("GAF: biases set OK\n");

	/* ── Step 3: Set GAF config params (align with MCU set_operation_mode + start_algo) ── */
	/* PDR = GAF processing period. MCU uses gaf_pdr_us from supported_cfg[]
	 * (typically 20000us = 50Hz). Use fixed value matching MCU default. */
	pdr_us = 20000; /* 50Hz, matches MCU modes 1,4,5,6,7,8,9 */

	/* Mag interval: 20000us = 50Hz default, 0 if mag disabled */
	mag_dt_us = mag_enabled ? 20000 : 0;

	/* Read clock variation from PLL trim register */
	{
		u8 pll_trim;
		inv_plat_read(st, 0xa2a2, 1, &pll_trim); /* SW_PLL1_TRIM */
		clock_variation = pll_trim;
	}

	status = inv_mpu_gaf_set_config(st, pdr_us, 1, mag_dt_us, clock_variation);
	if (status) {
		pr_err("GAF: set_config failed=%d\n", status);
		return status;
	}
	pr_info("GAF: config set OK\n");

	/* ── Step 4: Set mounting matrix ── */
	status = inv_mpu_gaf_set_mounting_matrix(st, exo_mounting);
	if (status) {
		pr_err("GAF: set_mounting_matrix failed=%d\n", status);
		return status;
	}
	pr_info("GAF: mounting matrix OK\n");

	/* ── Step 5: Soft-iron correction matrix (if mag enabled) ── */
	if (mag_enabled) {
		status = inv_mpu_mag_set_soft_iron(st, ident_soft_iron);
		if (status)
			pr_warn("GAF: soft_iron set failed=%d\n", status);
	}

	/* ── Step 6: Load MRM calibration image (if mag enabled) ── */
	if (mag_enabled) {
		status = inv_mpu_mag_load_ram_image(st,
						    INV_MPU_MRM_INIT_OVER_SIF);
		if (status) {
			pr_err("GAF: MRM image load failed=%d\n", status);
			return status;
		}
		status = inv_mpu_mag_enable_automrm(st);
		if (status)
			pr_warn("GAF: auto-MRM enable failed=%d\n", status);
	}

	/* ── Step 7: Start FIFO push ── */
	status = inv_mpu_gaf_start_fifo_push(st);
	if (status) {
		pr_err("GAF: start_fifo_push failed=%d\n", status);
		return status;
	}
	pr_info("GAF: FIFO push started OK\n");

	/* ── Step 7.5: Reset FIFO (MCU order: before GAF/eDMP enable) ── */
	inv_reset_fifo(st, false);

	/* ── Step 8: Enable GAF + eDMP ── */
	status = inv_mpu_gaf_enable(st);
	if (!status) {
		/* Keep STATUS_MASK_PIN_0_7 = 0x3C so eDMP receives ACCEL_DRDY
		 * Must be done every time — inv_stop_dmp() clears it to 0xFF */
		{
			u8 v = 0x3C;
			inv_ireg_single_write(st,
				REG_STATUS_MASK_PIN_0_7_IPREG_TOP1, v);
		}
		/* ES0/ES1 ODR and 9-byte mode */
		inv_plat_single_write(st,
			REG_DMP_EXT_SEN_ODR_CFG_DREG_BANK1, 0x01);
		inv_plat_single_write(st,
			REG_FIFO_CONFIG4_DREG_BANK1, 0x01);

		st->chip_config.gaf_enabled = 1;
		pr_info("GAF: enabled successfully (%d-axis)\n",
			mag_enabled ? 9 : 6);

		/* DEBUG: verify I2CM profile intact for eDMP autonomous mag read */
		{
			u8 dp0, dp1, wd0, wd1, cmd1, who;
			inv_ireg_read(st, REG_I2CM_DEV_PROFILE0_IPREG_TOP1, 1, &dp0);
			inv_ireg_read(st, REG_I2CM_DEV_PROFILE1_IPREG_TOP1, 1, &dp1);
			inv_ireg_read(st, REG_I2CM_WR_DATA0_IPREG_TOP1, 1, &wd0);
			inv_ireg_read(st, REG_I2CM_WR_DATA1_IPREG_TOP1, 1, &wd1);
			inv_ireg_read(st, REG_I2CM_COMMAND_1_IPREG_TOP1, 1, &cmd1);
			pr_info("GAF_DBG: I2CM dp=[0x%02x,0x%02x] wr=[0x%02x,0x%02x] cmd1=0x%02x (expect dp=[06,1e] wr=[04,02] cmd1=82)\n",
				dp0, dp1, wd0, wd1, cmd1);
			/* Check RCOSC clock: bit1=1 needed for I2CM */
			{
				u8 misc1;
				inv_plat_read(st, REG_REG_MISC1_DREG_BANK1, 1, &misc1);
				pr_info("GAF_DBG: MISC1=0x%02x (RCOSC=%d)
", misc1, !!(misc1 & 0x02));
			}
			/* Check I2CM_STATUS for errors */
			{
				u8 sts;
				inv_ireg_read(st, REG_I2CM_STATUS_IPREG_TOP1, 1, &sts);
				pr_info("GAF_DBG: I2CM_STATUS=0x%02x (busy=%d to=%d srst=%d scl=%d sda=%d)
",
					sts,
					!!(sts & 0x01), !!(sts & 0x04),
					!!(sts & 0x08), !!(sts & 0x10), !!(sts & 0x20));
			}
			/* Re-verify ICT1531x is still alive by reading WHOAMI via I2CM */
			{
				int r;
				u8 i2cm_cmd;
				/* Configure I2CM: read 1 byte from reg 0x01 (CHIP_ID) at addr 0x1E */
				inv_ireg_write(st, REG_I2CM_DEV_PROFILE0_IPREG_TOP1, 1,
					(u8[]){0x01});
				inv_ireg_write(st, REG_I2CM_DEV_PROFILE1_IPREG_TOP1, 1,
					(u8[]){0x1E});
				i2cm_cmd = 0x80 | 0x00 | 0x10 | 0x01; /* end=1,ch=0,rd,burst=1 */
				inv_ireg_write(st, REG_I2CM_COMMAND_0_IPREG_TOP1, 1, &i2cm_cmd);
				/* Start I2CM */
				{
					u8 ctrl;
					inv_ireg_read(st, REG_I2CM_CONTROL_IPREG_TOP1, 1, &ctrl);
					ctrl |= REG_I2CM_CONTROL_I2CM_GO_MASK;
					ctrl &= ~REG_I2CM_CONTROL_I2CM_SPEED_MASK;
					inv_ireg_write(st, REG_I2CM_CONTROL_IPREG_TOP1, 1, &ctrl);
				}
				/* Wait */
				r = 0;
				{
					int to = 100;
					u8 sts;
					while (to--) {
						usleep_range(100, 200);
						inv_plat_read(st, REG_INT1_STATUS1_DREG_BANK1, 1, &sts);
						if (sts & 0x20) break; /* I2CM_DONE */
					}
				}
				inv_ireg_read(st, REG_I2CM_RD_DATA0_IPREG_TOP1, 1, &who);
				pr_info("GAF_DBG: ICT1531x WHOAMI re-read=0x%02x (expect 0x45)\n", who);
			}
		}
	} else {
		pr_err("GAF: enable failed=%d\n", status);
	}

	return status;
}

