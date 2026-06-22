/*
 * Copyright (c) [2023] by InvenSense, Inc.
 * Adapted for Linux inv_mpu driver.
 */

#ifndef _INV_ICT1531X_H_
#define _INV_ICT1531X_H_

#include "Ict1531xSerif.h"

#define ICT1531X_WHOAMI 0x45

/* Register definitions */
#define ICT1531X_MANUF_ID_REG              0x00
#define ICT1531X_CHIP_ID_REG               0x01
#define ICT1531X_CHIP_CONFIG_REG           0x03
#define ICT1531X_CHIP_CONFIG_REG_TEMP_SEL_MASK  0x08
#define ICT1531X_CHIP_CONFIG_REG_TEMP_SEL_POS   3
#define ICT1531X_MODE_CTRL_REG             0x04
#define ICT1531X_MODE_CTRL_REG_ODR_MASK    0x70
#define ICT1531X_MODE_CTRL_REG_ODR_POS     4
#define ICT1531X_MODE_CTRL_REG_MODE_MASK   0x03
#define ICT1531X_MODE_CTRL_REG_MODE_POS    0
#define ICT1531X_MODE_STATUS_REG           0x05
#define ICT1531X_MODE_STATUS_REG_STATUS_MASK  0x03
#define ICT1531X_MODE_STATUS_REG_STATUS_POS   0
#define ICT1531X_STATUS_REG                0x06
#define ICT1531X_STATUS_REG_DATA_READY_MASK  0x01
#define ICT1531X_STATUS_REG_DATA_READY_POS   0
#define ICT1531X_FRAME_CNT_REG             0x07
#define ICT1531X_FRAME_CNT_REG_FRAME_COUNTER_MASK  0x07
#define ICT1531X_FRAME_CNT_REG_FRAME_COUNTER_POS   0
#define ICT1531X_TEMP_DATA_LSB             0x08
#define ICT1531X_TEMP_DATA_MSB             0x09
#define ICT1531X_MAG_DATA_X_LSB            0x0a
#define ICT1531X_MAG_DATA_X_MSB            0x0b
#define ICT1531X_MAG_DATA_Y_LSB            0x0c
#define ICT1531X_MAG_DATA_Y_MSB            0x0d
#define ICT1531X_MAG_DATA_Z_LSB            0x0e
#define ICT1531X_MAG_DATA_Z_MSB            0x0f
#define ICT1531X_CONF_CALIB_REG            0x21
#define ICT1531X_SEQUENCER_CTRL_REG        0x7c
#define ICT1531X_SEQUENCER_CTRL_REG_SOFT_RESET_MASK  0x80
#define ICT1531X_SEQUENCER_CTRL_REG_SOFT_RESET_POS   7
#define ICT1531X_GLOBAL_LOCK_REG           0x7f

typedef enum {
	ICT1531X_MODE_CTRL_REG_MODE_STANDBY     = 0,
	ICT1531X_MODE_CTRL_REG_MODE_PULSED      = 1,
	ICT1531X_MODE_CTRL_REG_MODE_SINGLE_SHOT = 2,
	ICT1531X_MODE_CTRL_REG_MODE_MRM         = 3
} inv_ict1531x_mode_t;

typedef enum {
	ICT1531X_MODE_STATUS_REG_MODE_STANDBY     = 0,
	ICT1531X_MODE_STATUS_REG_MODE_PULSED      = 1,
	ICT1531X_MODE_STATUS_REG_MODE_SINGLE_SHOT = 2,
	ICT1531X_MODE_STATUS_REG_MODE_MRM         = 3
} inv_ict1531x_mode_status_t;

typedef enum {
	ICT1531X_CHIP_CONFIG_REG_TEMP_SEL_FILTERED = 0 << ICT1531X_CHIP_CONFIG_REG_TEMP_SEL_POS,
	ICT1531X_CHIP_CONFIG_REG_TEMP_SEL_RAW      = 1 << ICT1531X_CHIP_CONFIG_REG_TEMP_SEL_POS
} inv_ict1531x_chip_config_temp_sel_t;

#define NUMBER_OF_SAMPLES_FOR_SELFTEST  100
#define ICT1531X_SELFTEST_SUCCESS        0
#define ICT1531X_SELFTEST_ERROR_PP_WIN_X (1 << 0)
#define ICT1531X_SELFTEST_ERROR_PP_WIN_Y (1 << 1)
#define ICT1531X_SELFTEST_ERROR_PP_WIN_Z (1 << 2)

typedef struct inv_ict1531x_selftest_status {
	int status;
	s16 max[3];
	s16 min[3];
	s32 pp[3];
} inv_ict1531x_selftest_status_t;

typedef struct inv_ict1531x {
	struct inv_ict1531x_serif serif;
	u8  compass_en;
	int frame_cnt;
} inv_ict1531x_t;

extern u64 inv_ict1531x_get_time_us(void);

void inv_ict1531x_reset_states(struct inv_ict1531x *s,
			       const struct inv_ict1531x_serif *serif);
int inv_ict1531x_poll_data(struct inv_ict1531x *s, s16 *compass_data_lsb,
			   s16 *temp_data_lsb);
int inv_ict1531x_get_whoami(struct inv_ict1531x *s, u8 *whoami);
int inv_ict1531x_soft_reset(struct inv_ict1531x *s);
int inv_ict1531x_set_mode(struct inv_ict1531x *s, inv_ict1531x_mode_t mode);
int inv_ict1531x_get_mode(struct inv_ict1531x *s, inv_ict1531x_mode_t *cur_mode);
int inv_ict1531x_set_temperature_mode(struct inv_ict1531x *s,
				      inv_ict1531x_chip_config_temp_sel_t temp_mode);
int inv_ict1531x_enable_sensor(struct inv_ict1531x *s, u8 en);
int inv_ict1531x_set_mrm(struct inv_ict1531x *s);
int inv_ict1531x_global_lock(struct inv_ict1531x *s, u8 lock);
int inv_ict1531x_selftest(struct inv_ict1531x *s,
			  inv_ict1531x_selftest_status_t *st_status);

#endif /* _INV_ICT1531X_H_ */
