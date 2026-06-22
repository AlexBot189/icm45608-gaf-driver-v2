/*
 * Copyright (c) [2023] by InvenSense, Inc.
 * Adapted for Linux inv_mpu driver.
 */

#ifndef _INV_ICT1531X_SERIF_H_
#define _INV_ICT1531X_SERIF_H_

#include <linux/types.h>

/* Error codes (mirrored from MCU InvError.h, used by Ict1531xSerif.h) */
enum inv_error {
	INV_ERROR_SUCCESS    = 0,
	INV_ERROR            = -1,
	INV_ERROR_NIMPL      = -2,
	INV_ERROR_TRANSPORT  = -3,
	INV_ERROR_TIMEOUT    = -4,
	INV_ERROR_SIZE       = -5,
	INV_ERROR_BAD_ARG    = -11,
};

struct inv_ict1531x_serif {
	void *context;
	int (*read_reg)(void *serif, u8 reg, u8 *buf, u32 len);
	int (*write_reg)(void *serif, u8 reg, const u8 *buf, u32 len);
	u32 max_read;
	u32 max_write;
	u8  is_first_transaction;
};

static inline u32 inv_ict1531x_serif_max_read(struct inv_ict1531x_serif *s)
{
	if (!s) return INV_ERROR;
	return s->max_read;
}

static inline u32 inv_ict1531x_serif_max_write(struct inv_ict1531x_serif *s)
{
	if (!s) return INV_ERROR;
	return s->max_write;
}

static inline int inv_ict1531x_serif_read_reg(struct inv_ict1531x_serif *s,
					      u8 reg, u8 *buf, u32 len)
{
	int rc;
	if (!s) return INV_ERROR;
	if (len > s->max_read) return INV_ERROR_SIZE;
	rc = s->read_reg(s->context, reg, buf, len);
	if (s->is_first_transaction) {
		s->is_first_transaction = 0;
		if (rc != 0)
			rc = s->read_reg(s->context, reg, buf, len);
	}
	if (rc != 0) return INV_ERROR_TRANSPORT;
	return 0;
}

static inline int inv_ict1531x_serif_write_reg(struct inv_ict1531x_serif *s,
					       u8 reg, const u8 *buf, u32 len)
{
	int rc;
	if (!s) return INV_ERROR;
	if (len > s->max_write) return INV_ERROR_SIZE;
	rc = s->write_reg(s->context, reg, buf, len);
	if (s->is_first_transaction) {
		s->is_first_transaction = 0;
		if (rc != 0)
			rc = s->write_reg(s->context, reg, buf, len);
	}
	if (rc != 0) return INV_ERROR_TRANSPORT;
	return 0;
}

#endif /* _INV_ICT1531X_SERIF_H_ */
