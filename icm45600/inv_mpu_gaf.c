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
/*
 * inv_mpu_gaf_v2_dump.c — Comprehensive register dump for I2CM/mag debugging
 *
 * Append this function to inv_mpu_gaf.c, call as:
 *   gaf_dump_i2cm_state(st);
 * right after the GAF enable block in inv_mpu_gaf_init().
 */

static void gaf_dump_i2cm_state(struct inv_mpu_state *st)
{
	u8 d;

	pr_info("======== GAF I2CM/MAG REGISTER DUMP ========\n");

	/* ── IOC_PAD ── */
	inv_plat_read(st, REG_IOC_PAD_SCENARIO_AUX_OVRD_DREG_BANK1, 1, &d);
	pr_info("GAF_DBG: IOC_PAD_AUX_OVRD(0x30)=0x%02x "
		"(aux1_en=%d mode_ovrd=%d mode=%d)\n",
		d, !!(d & 0x01), !!(d & 0x10), (d >> 2) & 3);

	/* ── MISC1 (clock) ── */
	inv_plat_read(st, REG_REG_MISC1_DREG_BANK1, 1, &d);
	pr_info("GAF_DBG: MISC1(0x35)=0x%02x "
		"(osc_req: EDOSC=%d RCOSC=%d PLL=%d EXT=%d)\n",
		d, !!(d & 1), !!(d & 2), !!(d & 4), !!(d & 8));

	/* ── PWR_MGMT0 ── */
	inv_plat_read(st, REG_PWR_MGMT0_DREG_BANK1, 1, &d);
	pr_info("GAF_DBG: PWR_MGMT0(0x10)=0x%02x (accel=%d gyro=%d)\n",
		d, d & 3, (d >> 2) & 3);

	/* ── EDMP_APEX_EN0 ── */
	inv_plat_read(st, REG_EDMP_APEX_EN0_DREG_BANK1, 1, &d);
	pr_info("GAF_DBG: EDMP_APEX_EN0(0x29)=0x%02x\n", d);

	/* ── EDMP_APEX_EN1 ── */
	inv_plat_read(st, REG_EDMP_APEX_EN1_DREG_BANK1, 1, &d);
	pr_info("GAF_DBG: EDMP_APEX_EN1(0x2A)=0x%02x "
		"(si=%d gaf=%d pickup=%d edmp=%d)\n",
		d, !!(d & 0x01), !!(d & 0x10), !!(d & 0x20), !!(d & 0x40));

	/* ── DMP_EXT_SEN_ODR_CFG ── */
	inv_plat_read(st, REG_DMP_EXT_SEN_ODR_CFG_DREG_BANK1, 1, &d);
	pr_info("GAF_DBG: DMP_EXT_SEN_ODR_CFG(0x27)=0x%02x "
		"(apex_odr=%d ext_odr=%d ext_en=%d)\n",
		d, d & 7, (d >> 3) & 7, !!(d & 0x40));

	/* ── FIFO_CONFIG3 ── */
	inv_plat_read(st, REG_FIFO_CONFIG3_DREG_BANK1, 1, &d);
	pr_info("GAF_DBG: FIFO_CONFIG3(0x69)=0x%02x "
		"(acc=%d gyr=%d hires=%d es0=%d es1=%d fifo_en=%d)\n",
		d, !!(d & 1), !!(d & 2), !!(d & 4), !!(d & 8), !!(d & 0x10), !!(d & 0x40));

	/* ── FIFO_CONFIG4 ── */
	inv_plat_read(st, REG_FIFO_CONFIG4_DREG_BANK1, 1, &d);
	pr_info("GAF_DBG: FIFO_CONFIG4(0x6A)=0x%02x (es0_9B=%d)\n",
		d, !!(d & 1));

	/* ── STATUS_MASK_PIN_0_7 (EDMP INT0) ── */
	inv_ireg_read(st, REG_STATUS_MASK_PIN_0_7_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: STATUS_MASK_PIN_0_7(0xA271)=0x%02x "
		"(accel_drdy=%d on_demand=%d)\n",
		d, !!(d & 1), !!(d & 0x20));

	/* ── STATUS_MASK_PIN_8_15 (EDMP INT1) ── */
	inv_ireg_read(st, REG_STATUS_MASK_PIN_8_15_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: STATUS_MASK_PIN_8_15(0xA272)=0x%02x\n", d);

	/* ── HOST_MSG ── */
	inv_plat_read(st, REG_REG_HOST_MSG_DREG_BANK1, 1, &d);
	pr_info("GAF_DBG: HOST_MSG(0x2B)=0x%02x (on_demand=%d test=%d)\n",
		d, !!(d & 0x40), !!(d & 0x20));

	/* ═══════════════════════════════════════════
	 * I2CM CONFIGURATION
	 * ═══════════════════════════════════════════ */

	/* I2CM_CONTROL */
	inv_ireg_read(st, REG_I2CM_CONTROL_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM_CTRL(0xA216)=0x%02x (go=%d speed=%d restart=%d)\n",
		d, !!(d & 1), !!(d & 0x08), !!(d & 0x40));

	/* I2CM_STATUS */
	inv_ireg_read(st, REG_I2CM_STATUS_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM_STATUS(0xA218)=0x%02x "
		"(busy=%d done=%d to=%d srst=%d scl=%d sda=%d)\n",
		d,
		!!(d & 0x01), !!(d & 0x02),
		!!(d & 0x04), !!(d & 0x08),
		!!(d & 0x10), !!(d & 0x20));

	/* I2CM EXT_DEV_STATUS */
	inv_ireg_read(st, REG_I2CM_EXT_DEV_STATUS_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM_EXT_DEV(0xA21A)=0x%02x\n", d);

	/* I2CM DEV_PROFILE[0..3] */
	inv_ireg_read(st, REG_I2CM_DEV_PROFILE0_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM DEV_PROF0(0xA20E)=0x%02x (expect 0x06=STATUS_REG)\n", d);
	inv_ireg_read(st, REG_I2CM_DEV_PROFILE1_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM DEV_PROF1(0xA20F)=0x%02x (expect 0x1E=I2C_ADDR)\n", d);
	inv_ireg_read(st, REG_I2CM_DEV_PROFILE2_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM DEV_PROF2(0xA210)=0x%02x\n", d);
	inv_ireg_read(st, REG_I2CM_DEV_PROFILE3_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM DEV_PROF3(0xA211)=0x%02x\n", d);

	/* I2CM WR_DATA[0..5] */
	inv_ireg_read(st, REG_I2CM_WR_DATA0_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM WR_DATA0(0xA233)=0x%02x (expect 0x04)\n", d);
	inv_ireg_read(st, REG_I2CM_WR_DATA1_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM WR_DATA1(0xA234)=0x%02x (expect 0x02)\n", d);
	inv_ireg_read(st, REG_I2CM_WR_DATA2_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM WR_DATA2(0xA235)=0x%02x (expect 0x04)\n", d);
	inv_ireg_read(st, REG_I2CM_WR_DATA3_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM WR_DATA3(0xA236)=0x%02x (expect 0x00)\n", d);

	/* I2CM COMMAND[0..3] */
	inv_ireg_read(st, REG_I2CM_COMMAND_0_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM CMD0(0xA206)=0x%02x"
		" (end=%d ch=%d rw=%d len=%d)\n",
		d, !!(d & 0x80), !!(d & 0x40), (d>>4)&3, d & 0x0F);
	inv_ireg_read(st, REG_I2CM_COMMAND_1_IPREG_TOP1, 1, &d);
	pr_info("GAF_DBG: I2CM CMD1(0xA207)=0x%02x"
		" (end=%d ch=%d rw=%d len=%d expect 0x82)\n",
		d, !!(d & 0x80), !!(d & 0x40), (d>>4)&3, d & 0x0F);

	/* ═══════════════════════════════════════════
	 * ICT1531x register reads via I2CM
	 * (verify mag is reachable and responding)
	 * ═══════════════════════════════════════════ */

	/* Helper: do a 1-byte I2CM read from ICT1531x */
#define ICT1531X_I2C_ADDR    0x1E
#define ICT1531X_CHIP_ID_REG 0x01
#define ICT1531X_STATUS_REG  0x06

	/* Read CHIP_ID (WHOAMI) */
	{
		u8 who, ctrl;
		u8 cmd = 0x80 | 0x00 | 0x10 | 0x01; /* end,ch0,rd,len=1 */
		inv_ireg_single_write(st, REG_I2CM_DEV_PROFILE0_IPREG_TOP1,
			ICT1531X_CHIP_ID_REG);
		inv_ireg_single_write(st, REG_I2CM_DEV_PROFILE1_IPREG_TOP1,
			ICT1531X_I2C_ADDR);
		inv_ireg_single_write(st, REG_I2CM_COMMAND_0_IPREG_TOP1, cmd);
		inv_ireg_read(st, REG_I2CM_CONTROL_IPREG_TOP1, 1, &ctrl);
		ctrl |= REG_I2CM_CONTROL_I2CM_GO_MASK;
		ctrl &= ~REG_I2CM_CONTROL_I2CM_SPEED_MASK;
		inv_ireg_single_write(st, REG_I2CM_CONTROL_IPREG_TOP1, ctrl);
		{
			u8 sts; int to = 100;
			do { usleep_range(100,200);
			     inv_plat_read(st, REG_INT1_STATUS1_DREG_BANK1, 1, &sts);
			} while (--to && !(sts & 0x20));
		}
		inv_ireg_read(st, REG_I2CM_RD_DATA0_IPREG_TOP1, 1, &who);
		inv_ireg_read(st, REG_I2CM_STATUS_IPREG_TOP1, 1, &ctrl);
		pr_info("GAF_DBG: ICT1531x CHIP_ID(0x01)=0x%02x (expect 0x45) "
			"i2cm_sts=0x%02x\n", who, ctrl);
	}

	/* Read STATUS_REG + FRAME_CNT */
	{
		u8 buf[2], ctrl;
		u8 cmd = 0x80 | 0x00 | 0x10 | 0x02; /* end,ch0,rd,len=2 */
		inv_ireg_single_write(st, REG_I2CM_DEV_PROFILE0_IPREG_TOP1,
			ICT1531X_STATUS_REG);
		inv_ireg_single_write(st, REG_I2CM_DEV_PROFILE1_IPREG_TOP1,
			ICT1531X_I2C_ADDR);
		inv_ireg_single_write(st, REG_I2CM_COMMAND_0_IPREG_TOP1, cmd);
		inv_ireg_read(st, REG_I2CM_CONTROL_IPREG_TOP1, 1, &ctrl);
		ctrl |= REG_I2CM_CONTROL_I2CM_GO_MASK;
		ctrl &= ~REG_I2CM_CONTROL_I2CM_SPEED_MASK;
		inv_ireg_single_write(st, REG_I2CM_CONTROL_IPREG_TOP1, ctrl);
		{
			u8 sts; int to = 100;
			do { usleep_range(100,200);
			     inv_plat_read(st, REG_INT1_STATUS1_DREG_BANK1, 1, &sts);
			} while (--to && !(sts & 0x20));
		}
		inv_ireg_read(st, REG_I2CM_RD_DATA0_IPREG_TOP1, 2, buf);
		pr_info("GAF_DBG: ICT1531x STATUS(0x06)=0x%02x FRAME_CNT=0x%02x "
			"(expect STATUS.bit0=1 data_ready)\n", buf[0], buf[1]);
	}

	/* Read full 9-byte mag data block (STATUS through MAG_Z MSB) */
	{
		u8 buf[10], ctrl;
		u8 cmd = 0x80 | 0x00 | 0x10 | 0x0A; /* end,ch0,rd,len=10 */
		inv_ireg_single_write(st, REG_I2CM_DEV_PROFILE0_IPREG_TOP1,
			ICT1531X_STATUS_REG);
		inv_ireg_single_write(st, REG_I2CM_DEV_PROFILE1_IPREG_TOP1,
			ICT1531X_I2C_ADDR);
		inv_ireg_single_write(st, REG_I2CM_COMMAND_0_IPREG_TOP1, cmd);
		inv_ireg_read(st, REG_I2CM_CONTROL_IPREG_TOP1, 1, &ctrl);
		ctrl |= REG_I2CM_CONTROL_I2CM_GO_MASK;
		ctrl &= ~REG_I2CM_CONTROL_I2CM_SPEED_MASK;
		inv_ireg_single_write(st, REG_I2CM_CONTROL_IPREG_TOP1, ctrl);
		{
			u8 sts; int to = 100;
			do { usleep_range(100,200);
			     inv_plat_read(st, REG_INT1_STATUS1_DREG_BANK1, 1, &sts);
			} while (--to && !(sts & 0x20));
		}
		inv_ireg_read(st, REG_I2CM_RD_DATA0_IPREG_TOP1, 10, buf);
		pr_info("GAF_DBG: ICT1531x FULL_READ: "
			"sts=%02x fcnt=%02x "
			"temp=%02x%02x "
			"mag_x=%02x%02x y=%02x%02x z=%02x%02x "
			"[raw: %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x]\n",
			buf[0], buf[1],
			buf[2], buf[3],
			buf[4], buf[5], buf[6], buf[7], buf[8], buf[9],
			buf[0], buf[1], buf[2], buf[3], buf[4],
			buf[5], buf[6], buf[7], buf[8], buf[9]);
	}

	pr_info("======== END GAF I2CM/MAG DUMP ========\n");

#undef ICT1531X_I2C_ADDR
#undef ICT1531X_CHIP_ID_REG
#undef ICT1531X_STATUS_REG
}

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


		gaf_dump_i2cm_state(st);
	} else {
		pr_err("GAF: enable failed=%d\n", status);
	}

	return status;
}

