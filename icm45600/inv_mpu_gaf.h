/*
 * Copyright (c) [2020] by InvenSense, Inc.
 * Adapted for Linux IIO inv_mpu driver.
 *
 * GAF (Gyro-Assisted Fusion) frame decoding and initialization
 * for ICM-45608 eDMP firmware.
 *
 * Reference: MCU inv_imu_edmp.c / inv_imu_edmp.h
 */
#ifndef _INV_MPU_GAF_H_
#define _INV_MPU_GAF_H_

#include <linux/types.h>

struct inv_mpu_state;

/*─── GAF EDMP SRAM memory map (from MCU inv_imu_edmp_memmap.h) ───*/
#define EDMP_GAF_MODE                                  0x1be
#define EDMP_GAF_MODE_SIZE                             1
#define EDMP_GAF_INIT_STATUS                           0x924
#define EDMP_GAF_INIT_STATUS_SIZE                      1
#define EDMP_GLOBAL_MOUNTING_MATRIX                    0x1ac
#define EDMP_GLOBAL_MOUNTING_MATRIX_SIZE               18
#define EDMP_GAF_SAVED_ACC_BIAS_1G_Q16                 0x8c8
#define EDMP_GAF_SAVED_ACC_BIAS_1G_Q16_SIZE            12
#define EDMP_GAF_SAVED_ACC_ACCURACY                    0x923
#define EDMP_GAF_SAVED_ACC_ACCURACY_SIZE               1
#define EDMP_GAF_GYR_BIAS_DPS_Q12                      0x6cc
#define EDMP_GAF_GYR_BIAS_DPS_Q12_SIZE                 12
#define EDMP_GAF_SAVED_GYR_ACCURACY                    0x5bc
#define EDMP_GAF_SAVED_GYR_ACCURACY_SIZE               4
#define EDMP_GAF_GYR_BIAS_TEMPERATURE_DEG_Q16          0x6a0
#define EDMP_GAF_GYR_BIAS_TEMPERATURE_DEG_Q16_SIZE     4
#define EDMP_DMP_ODR_LAST_INIT                         0x188
#define EDMP_DMP_ODR_LAST_INIT_SIZE                    4

/*─── EDMP GAF CONFIG SRAM addresses (from MCU inv_imu_edmp_memmap.h) ───*/
/* Core timing parameters */
#define EDMP_GAF_CONFIG_ACC_ODR_US                      0x288
#define EDMP_GAF_CONFIG_ACC_ODR_US_SIZE                 4
#define EDMP_GAF_CONFIG_GYR_ODR_US                      0x28c
#define EDMP_GAF_CONFIG_GYR_ODR_US_SIZE                 4
#define EDMP_GAF_CONFIG_ACC_PDR_US                      0x290
#define EDMP_GAF_CONFIG_ACC_PDR_US_SIZE                 4
#define EDMP_GAF_CONFIG_GYR_PDR_US                      0x294
#define EDMP_GAF_CONFIG_GYR_PDR_US_SIZE                 4
#define EDMP_GAF_CONFIG_PLL_CLOCK_VARIATION             0x2ac
#define EDMP_GAF_CONFIG_PLL_CLOCK_VARIATION_SIZE        1
#define EDMP_GAF_CONFIG_RUN_SPHERICAL                   0x2ae
#define EDMP_GAF_CONFIG_RUN_SPHERICAL_SIZE              1
/* Mag timing parameters */
#define EDMP_GAF_CONFIG_MAG_DT_US                       0x4a8
#define EDMP_GAF_CONFIG_MAG_DT_US_SIZE                  4
#define EDMP_GAF_CONFIG_MAGCAL_DT_US                    0x818
#define EDMP_GAF_CONFIG_MAGCAL_DT_US_SIZE               4

/* GAF mode bitmask */
#define GAF_MODE_BITMASK_MAG       0x1
#define GAF_MODE_BITMASK_GYRO      0x2
#define GAF_MODE_BITMASK_FIFO_PUSH 0x8

/* FIFO frame type IDs */
#define FRAME_ID_FRAME_A  0x1
#define FRAME_ID_FRAME_B  0x0

/* Default init temperature for GAF bias (-273 C in Q16) */
#define GAF_DEFAULT_TEMPERATURE_INIT_Q16  (-17891328)

/*─── FIFO frame status bytes (from MCU inv_imu_edmp.c) ───*/
typedef struct {
	u8 frame_id     : 1;
	u8 accuracy     : 2;
	u8 stationary   : 3;
	u8 rmag_valid   : 1;
	u8 hrc_nfusion  : 1;
} status_byte_frameA_t;

typedef struct {
	u8 frame_id     : 1;
	u8 accuracy     : 2;
	u8 mag_anom     : 2;
	u8 mrm_state    : 2;
	u8 hrc_nfusion  : 1;
} status_byte_frameB_t;

typedef struct {
	u8 gx           : 4;
	u8 gy           : 4;
} hr_gxy_t;

typedef struct {
	u8 reserved     : 4;
	u8 gz           : 4;
} hr_gz_t;

/*─── GAF frame type enum (from MCU inv_imu_edmp.h) ───*/
enum inv_mpu_gaf_frame_type {
	INV_MPU_GAF_QUAT_BIAS_GYR = 0,
	INV_MPU_GAF_QUAT_RAW_MAG,
	INV_MPU_GAF_QUAT_RAW_MAG_GYR_FLAGS,
	INV_MPU_GAF_BIAS_MAG_HEADING,
	INV_MPU_GAF_HRC_BIAS_GYR_RAW_MAG,
	INV_MPU_GAF_HRC_BIAS_GYR,
	INV_MPU_GAF_HRC_RAW_MAG,
	INV_MPU_GAF_HRC_BIAS_MAG,
};

/*─── GAF outputs struct (from MCU inv_imu_edmp_gaf_outputs_t) ───*/
struct inv_mpu_gaf_outputs {
	s16 grv_quat_q14[4];
	u8  grv_quat_valid;
	s16 gyr_bias_q12[3];
	u8  gyr_bias_valid;
	s8  gyr_accuracy_flag;
	s8  stationary_flag;
	u8  gyr_flags_valid;
	u8  hr_g[3];
	u8  hr_g_valid;
	s16 rmag[3];
	u8  rmag_valid;
	s32 mag_bias_q16[3];
	s8  mag_accuracy_flag;
	s8  mag_anomalies;
	u8  mag_bias_valid;
	s16 gmrv_quat_q14[4];
	u8  gmrv_quat_valid;
	s16 gmrv_heading_q11;
	u8  gmrv_heading_valid;
	s16 rv_quat_q14[4];
	u8  rv_quat_valid;
	s16 rv_heading_q11;
	u8  rv_heading_valid;
	u8  mrm_state;
	u8  mrm_state_valid;
	u8  frame_complete;
};

/*─── Public API ───*/
int inv_mpu_gaf_decode_fifo(struct inv_mpu_state *st,
			    const u8 es0[9], const u8 es1[6],
			    struct inv_mpu_gaf_outputs *out);

int inv_mpu_gaf_get_frame_type(struct inv_mpu_state *st,
			       const u8 es1[6],
			       enum inv_mpu_gaf_frame_type *frame_type);

int inv_mpu_gaf_set_mode(struct inv_mpu_state *st,
			 u8 gyro_is_on, u8 mag_is_on);

int inv_mpu_gaf_set_mounting_matrix(struct inv_mpu_state *st,
				    const s8 matrix[9]);

int inv_mpu_gaf_set_acc_bias(struct inv_mpu_state *st,
			     const s32 bias_q16[3]);

int inv_mpu_gaf_set_gyr_bias(struct inv_mpu_state *st,
			     const s16 bias_q12[3]);

int inv_mpu_gaf_start_fifo_push(struct inv_mpu_state *st);

int inv_mpu_gaf_stop_fifo_push(struct inv_mpu_state *st);

int inv_mpu_gaf_enable(struct inv_mpu_state *st);

int inv_mpu_gaf_set_config(struct inv_mpu_state *st,
			   u32 pdr_us, u8 run_spherical,
			   u32 mag_dt_us, u8 clock_variation);

int inv_mpu_gaf_init(struct inv_mpu_state *st, int mag_enabled);

#endif /* _INV_MPU_GAF_H_ */
