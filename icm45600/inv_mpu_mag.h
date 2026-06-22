/*
 * inv_mpu_mag.h - Magnetometer ICT1531x initialization for ICM-45608 eDMP GAF
 *
 * Ported from MCU invn_mag_ict1531x.c / invn_mag.h / inv_imu_edmp_mrm.c
 * Adapted for Linux inv_mpu IIO driver.
 *
 * The ICM-45608 DMP firmware reads magnetometer data autonomously via AUX I2CM
 * after initialization. Host-side code only needs to:
 *   1. Detect/reset ICT1531x via I2CM (inv_mpu_mag_init)
 *   2. Load MRM calibration image to EDMP SRAM (inv_mpu_mag_load_ram_image)
 *   3. Enable auto-MRM (inv_mpu_mag_enable_automrm)
 *
 * Once DMP is started, all mag data acquisition is handled by firmware.
 */
#ifndef _INV_MPU_MAG_H_
#define _INV_MPU_MAG_H_

#include <linux/types.h>

struct inv_mpu_state;

/* MRM usecase */
enum inv_mpu_mrm_usecase {
	INV_MPU_MRM_INIT_OVER_SIF = 0,
};

/* ─── Public API ─── */

/*
 * inv_mpu_mag_init() - Initialize I2CM, detect and reset ICT1531x magnetometer.
 * @st: IMU state
 * Returns 0 on success, negative on error.
 * On failure, caller should treat as "no magnetometer" and fall back to 6-axis.
 */
int inv_mpu_mag_init(struct inv_mpu_state *st);

/*
 * inv_mpu_mag_load_ram_image() - Load MRM calibration image into EDMP SRAM.
 * Must be called after inv_mpu_gaf_set_mode() and before inv_mpu_gaf_enable().
 */
int inv_mpu_mag_load_ram_image(struct inv_mpu_state *st, int usecase);

/*
 * inv_mpu_mag_enable_automrm() - Enable automatic MRM in GAF mode.
 */
int inv_mpu_mag_enable_automrm(struct inv_mpu_state *st);

/*
 * inv_mpu_mag_disable_automrm() - Disable automatic MRM.
 */
int inv_mpu_mag_disable_automrm(struct inv_mpu_state *st);

/*
 * inv_mpu_mag_set_soft_iron() - Set 3x3 soft-iron correction matrix in EDMP SRAM.
 * @soft_iron: Q30 format 3x3 matrix (typically identity << 30 for unit matrix)
 */
int inv_mpu_mag_set_soft_iron(struct inv_mpu_state *st,
			      const s32 soft_iron[3][3]);

#endif /* _INV_MPU_MAG_H_ */
