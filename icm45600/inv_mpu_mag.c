/*
 * inv_mpu_mag.c - Magnetometer ICT1531x init via I2CM + MRM for ICM-45608
 *
 * Ported from MCU:
 *   invn_mag_ict1531x.c → I2CM init + ICT1531x detection
 *   inv_imu_edmp_mrm.c  → MRM RAM image loading
 *   inv_imu_i2cm.c      → I2CM register operations (re-implemented)
 *
 * Register mapping: MCU SDK banked regs → Linux driver 16-bit IREG/plat regs
 *
 * I2CM registers (accessed via inv_ireg_*):
 *   MCU I2CM_DEV_PROFILE0  → REG_I2CM_DEV_PROFILE0_IPREG_TOP1  (0xa20e)
 *   MCU I2CM_WR_DATA0      → REG_I2CM_WR_DATA0_IPREG_TOP1      (0xa233)
 *   MCU I2CM_COMMAND_0     → REG_I2CM_COMMAND_0_IPREG_TOP1     (0xa206)
 *   MCU I2CM_CONTROL       → REG_I2CM_CONTROL_IPREG_TOP1       (0xa216)
 *   MCU I2CM_STATUS        → REG_I2CM_STATUS_IPREG_TOP1        (0xa218)
 *   MCU I2CM_RD_DATA0      → REG_I2CM_RD_DATA0_IPREG_TOP1      (0xa21b)
 *
 * Platform registers (accessed via inv_plat_*):
 *   MCU IOC_PAD_SCENARIO_AUX_OVRD → REG_IOC_PAD_SCENARIO_AUX_OVRD_DREG_BANK1
 */

#define pr_fmt(fmt) "inv_mpu: " fmt

#include "inv_mpu_mag.h"
#include "inv_mpu_gaf.h"
#include "../inv_mpu_iio.h"

#include "ICM45600_REG_External.h"
#include "inv_mpu_iio_reg_45600.h"

#include "Ict1531x.h"
#include "Ict1531xSerif.h"

#include <linux/delay.h>
#include <linux/ktime.h>
#include <linux/string.h>

/* ─── I2C address of ICT1531x on AUX I2CM bus ─── */
#define MAG_I2C_ADDR  0x1E

/* ─── MRM mode bit in GAF mode register (from MCU inv_imu_edmp_mrm.c) ─── */
#define GAF_MODE_BITMASK_MRM_ENABLE  0x4

/* ─── MRM RAM image addresses (from MCU inv_imu_edmp_defs.h) ─── */
#define RAM_MRM_IMG_DATA_BASE  0x9DC
#define RAM_MRM_IMG_PRGM_BASE  0xA24

/* ─── MRM patch point (from MCU inv_imu_edmp_patches_defs.h) ─── */
#define EDMP_INVN_ALGO_MRM_PATCH_POINT_DISPATCH  0xA8

/* ─── Soft iron matrix address in EDMP SRAM (from MCU inv_imu_edmp.c line 738) ─── */
#define EDMP_GAF_CONFIG_MAG_SOFTIRON_MATRIX  0x264 /* from MCU inv_imu_edmp_memmap.h */

/* ─── EDMP GAF mode SRAM address ─── */
#define EDMP_GAF_MODE  0x1be

/* ─── Static state for I2CM operations ─── */
static struct inv_mpu_state *mag_st;

/* ─── Write helper: IREG single write ─── */
static inline int ireg_write_u8(struct inv_mpu_state *st, int addr, u8 val)
{
	return inv_ireg_write(st, addr, 1, &val);
}

/* ─── Read helper: IREG single read ─── */
static inline int ireg_read_u8(struct inv_mpu_state *st, int addr, u8 *val)
{
	return inv_ireg_read(st, addr, 1, val);
}

/* ─── time_us for Ict1531x driver ─── */
u64 inv_ict1531x_get_time_us(void)
{
	return ktime_get_ns() / 1000;
}

/* ═══════════════════════════════════════════════════════════════════
 * I2CM low-level operations
 * Ported from MCU inv_imu_i2cm.c — re‑implemented using Linux inv_ireg_*
 * ═══════════════════════════════════════════════════════════════════ */

/*
 * Configure I2CM for a single read/write operation to an I2C slave.
 * Equivalent to MCU inv_imu_configure_i2cm() for a single slave.
 */
static int i2cm_configure_op(struct inv_mpu_state *st,
			     u8 slave_ch, u8 i2c_addr,
			     u8 r_n_w, u8 reg_addr, u8 len,
			     const u8 *wdata, int is_last)
{
	u8 cmd;
	int ret;

	/* Set I2C slave address — DEV_PROFILE1 (odd) = device ID */
	ret = ireg_write_u8(st, REG_I2CM_DEV_PROFILE1_IPREG_TOP1 + 2 * slave_ch,
			    i2c_addr);
	if (ret) return ret;

	if (r_n_w) {
		/* Read: set register address to read from */
		ret = ireg_write_u8(st,
			REG_I2CM_DEV_PROFILE0_IPREG_TOP1 + 2 * slave_ch,
			reg_addr);
		if (ret) return ret;
	} else if (len && wdata) {
		/* Write: load register address + data into WR_DATA */
		if (len > 5) return -1;
		ret = ireg_write_u8(st, REG_I2CM_WR_DATA0_IPREG_TOP1, reg_addr);
		if (ret) return ret;
		ret = inv_ireg_write(st, REG_I2CM_WR_DATA0_IPREG_TOP1 + 1, len,
				     wdata);
		if (ret) return ret;
		len++; /* burst size includes register address byte */
	}

	/* Build and write I2CM command */
	cmd = 0;
	cmd |= (is_last ? 0x80 : 0x00);          /* ENDFLAG */
	cmd |= (slave_ch << 6);                    /* CH_SEL */
	cmd |= (r_n_w ? 0x10 : 0x00);             /* R/W */
	cmd |= (len & 0x1F);                       /* BURSTLEN */

	ret = ireg_write_u8(st, REG_I2CM_COMMAND_0_IPREG_TOP1, cmd);

	return ret;
}

/*
 * Start I2CM operation. Equivalent to MCU inv_imu_start_i2cm_ops().
 */
static int i2cm_start(struct inv_mpu_state *st, int fast_mode)
{
	u8 ctrl;
	int ret;

	ret = ireg_read_u8(st, REG_I2CM_CONTROL_IPREG_TOP1, &ctrl);
	if (ret) return ret;

	ctrl |= REG_I2CM_CONTROL_I2CM_GO_MASK;
	if (fast_mode)
		ctrl &= ~REG_I2CM_CONTROL_I2CM_SPEED_MASK;
	else
		ctrl |= REG_I2CM_CONTROL_I2CM_SPEED_MASK;

	return ireg_write_u8(st, REG_I2CM_CONTROL_IPREG_TOP1, ctrl);
}

/*
 * Wait for I2CM completion and check status.
 * Equivalent to MCU check_end_of_i2c_master_ops().
 */
static int i2cm_wait_done(struct inv_mpu_state *st)
{
	u8 status_reg;
	u8 int_status;
	int ret;
	int timeout = 100;

	/* Poll I2CM_DONE in INT1_STATUS1 */
	while (timeout--) {
		ret = inv_plat_read(st, REG_INT1_STATUS1_DREG_BANK1, 1,
				    &int_status);
		if (ret) return ret;
		if (int_status & REG_INT1_STATUS1_INT1_STATUS_I2CM_DONE_MASK)
			break;
		usleep_range(100, 200);
	}
	if (timeout < 0) {
		pr_err("I2CM: timeout waiting for DONE\n");
		return -1;
	}

	/* Check I2CM_STATUS for errors */
	ret = ireg_read_u8(st, REG_I2CM_STATUS_IPREG_TOP1, &status_reg);
	if (ret) return ret;

	if (status_reg & (REG_I2CM_STATUS_I2CM_BUSY_MASK |
			  REG_I2CM_STATUS_I2CM_TIMEOUT_ERR_MASK |
			  REG_I2CM_STATUS_I2CM_SRST_ERR_MASK |
			  REG_I2CM_STATUS_I2CM_SCL_ERR_MASK |
			  REG_I2CM_STATUS_I2CM_SDA_ERR_MASK)) {
		pr_err("I2CM: error st=0x%02x (busy=%d to=%d srst=%d scl=%d sda=%d)\n",
		       status_reg,
		       !!(status_reg & REG_I2CM_STATUS_I2CM_BUSY_MASK),
		       !!(status_reg & REG_I2CM_STATUS_I2CM_TIMEOUT_ERR_MASK),
		       !!(status_reg & REG_I2CM_STATUS_I2CM_SRST_ERR_MASK),
		       !!(status_reg & REG_I2CM_STATUS_I2CM_SCL_ERR_MASK),
		       !!(status_reg & REG_I2CM_STATUS_I2CM_SDA_ERR_MASK));
		return -1;
	}

	return 0;
}

/*
 * Read data from I2CM read buffer.
 * Equivalent to MCU inv_imu_get_i2cm_data().
 */
static int i2cm_get_data(struct inv_mpu_state *st, u8 *buf, u8 len)
{
	return inv_ireg_read(st, REG_I2CM_RD_DATA0_IPREG_TOP1, len, buf);
}

/* ═══════════════════════════════════════════════════════════════════
 * Magnetometer register read/write via I2CM (serif callbacks)
 * These are the function pointers passed to Ict1531x driver.
 * Ported from MCU mag_read_reg() / mag_write_reg().
 * ═══════════════════════════════════════════════════════════════════ */

static int mag_read_reg(void *serif, u8 reg, u8 *buf, u32 len)
{
	struct inv_mpu_state *st = (struct inv_mpu_state *)serif;
	int ret;

	ret = i2cm_configure_op(st, 0, MAG_I2C_ADDR, 1/*read*/, reg, len,
				NULL, 1/*is_last*/);
	if (ret) return ret;

	ret = i2cm_start(st, 1/*fast_mode*/);
	if (ret) return ret;
	ret = i2cm_wait_done(st);
	if (ret) return ret;
	ret = i2cm_get_data(st, buf, len);

	return ret;
}

static int mag_write_reg(void *serif, u8 reg, const u8 *buf, u32 len)
{
	struct inv_mpu_state *st = (struct inv_mpu_state *)serif;
	int ret;

	ret = i2cm_configure_op(st, 0, MAG_I2C_ADDR, 0/*write*/, reg, len,
				buf, 1/*is_last*/);
	if (ret) return ret;
	ret = i2cm_start(st, 1/*fast_mode*/);
	if (ret) return ret;
	ret = i2cm_wait_done(st);

	return ret;
}

/* ═══════════════════════════════════════════════════════════════════
 * Public API — magnetometer initialization
 * ═══════════════════════════════════════════════════════════════════ */

/*
 * inv_mpu_mag_init()
 * Initialize AUX I2CM, detect and soft-reset ICT1531x, write I2CM profile
 * for DMP firmware to use during autonomous operation.
 *
 * Ported from MCU invn_mag_init() in invn_mag_ict1531x.c
 */
int inv_mpu_mag_init(struct inv_mpu_state *st)
{
	struct inv_ict1531x_serif mag_serif;
	inv_ict1531x_t mag_dev;
	u8 data;
	u8 int1_config1;
	int rc;

	mag_st = st;

	/* ── Step 1: Init I2CM hardware (configure AUX1 pads) ── */
	rc = inv_plat_read(st, REG_IOC_PAD_SCENARIO_AUX_OVRD_DREG_BANK1,
			   1, &data);
	if (rc) {
		pr_err("MAG: read IOC_PAD failed=%d\n", rc);
		return rc;
	}
	/* Only set AUX1 to I2CM master mode (identical to MCU inv_imu_init_i2cm).
	 * Do NOT force enable_ovrd bits — let factory defaults prevail. */
	data |= REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_MODE_OVRD_MASK |
		(1 << REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_MODE_OVRD_VAL_POS) |
		REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_MASK |
		REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_VAL_MASK;
	rc = inv_plat_single_write(st,
			REG_IOC_PAD_SCENARIO_AUX_OVRD_DREG_BANK1,
			data);
	if (rc) {
		pr_err("MAG: set IOC_PAD failed=%d\n", rc);
		return rc;
	}
	/* Verify write took effect */
	{
		u8 verify;
		rc = inv_plat_read(st,
			REG_IOC_PAD_SCENARIO_AUX_OVRD_DREG_BANK1, 1, &verify);
		if (rc == 0)
			pr_info("MAG: IOC_PAD w=0x%02x r=0x%02x\n", data, verify);
	}

	/* Enable I2CM restart (already done by init_i2cm_block, but safe) */
	{
		u8 i2cm_ctrl;
		rc = ireg_read_u8(st, REG_I2CM_CONTROL_IPREG_TOP1, &i2cm_ctrl);
		if (rc) return rc;
		i2cm_ctrl |= REG_I2CM_CONTROL_I2CM_RESTART_EN_MASK;
		rc = ireg_write_u8(st, REG_I2CM_CONTROL_IPREG_TOP1, i2cm_ctrl);
		if (rc) return rc;
		/* Verify */
		{
			u8 verify;
			ireg_read_u8(st, REG_I2CM_CONTROL_IPREG_TOP1, &verify);
			pr_info("MAG: I2CM_CTRL w=0x%02x r=0x%02x\n",
				i2cm_ctrl, verify);
		}
	}

	/* ── Step 1.5: Force RCOSC clock ON (required for I2CM when no sensor runs) ──
	 * Equivalent to MCU inv_imu_i2cm_clock_force(s, 1) */
	{
		u8 misc1;
		rc = inv_plat_read(st, REG_REG_MISC1_DREG_BANK1, 1, &misc1);
		if (rc) {
			pr_err("MAG: read MISC1 failed=%d\n", rc);
			return rc;
		}
		misc1 &= ~REG_REG_MISC1_OSC_ID_OVRD_MASK;
		misc1 |= REG_MISC1_OSC_ID_OVRD_RCOSC;
		rc = inv_plat_single_write(st, REG_REG_MISC1_DREG_BANK1, misc1);
		if (rc) {
			pr_err("MAG: force RCOSC failed=%d\n", rc);
			return rc;
		}
		usleep_range(5000, 6000); /* let RCOSC stabilize */
		/* Verify */
		{
			u8 verify;
			inv_plat_read(st, REG_REG_MISC1_DREG_BANK1, 1, &verify);
			pr_info("MAG: MISC1 w=0x%02x r=0x%02x\n", misc1, verify);
		}
	}

	/* ── Step 2: Enable I2CM_DONE interrupt on INT1 ── */
	rc = inv_plat_read(st, REG_INT1_CONFIG1_DREG_BANK1, 1, &int1_config1);
	if (rc) {
		pr_err("MAG: read INT1_CONFIG1 failed=%d\n", rc);
		return rc;
	}
	int1_config1 |= REG_INT1_CONFIG1_INT1_STATUS_EN_I2CM_DONE_MASK;
	rc = inv_plat_single_write(st, REG_INT1_CONFIG1_DREG_BANK1,
				   int1_config1);
	if (rc) {
		pr_err("MAG: set I2CM_DONE int failed=%d\n", rc);
		return rc;
	}

	/* ── Step 3: Set up Ict1531x serial interface ── */
	mag_serif.context   = st;
	mag_serif.read_reg  = mag_read_reg;
	mag_serif.write_reg = mag_write_reg;
	mag_serif.max_read  = 21;
	mag_serif.max_write = 6;

	inv_ict1531x_reset_states(&mag_dev, &mag_serif);

	/* ── Step 4: Soft-reset ICT1531x ── */
	pr_info("MAG: resetting ICT1531x\n");
	/* ── Step 4b: Standard Ict1531x init (identical to MCU invn_mag_init) ── */
	rc = inv_ict1531x_soft_reset(&mag_dev);
	if (rc) {
		pr_err("MAG: soft_reset failed=%d\n", rc);
		goto disable_i2cm_int;
	}
	/* Check WHOAMI */
	rc = inv_ict1531x_get_whoami(&mag_dev, &data);
	if (rc) {
		pr_err("MAG: read WHOAMI failed=%d\n", rc);
		goto disable_i2cm_int;
	}
	if (data != ICT1531X_WHOAMI) {
		pr_err("MAG: bad WHOAMI 0x%02x (expected 0x%02x)\n",
		       data, ICT1531X_WHOAMI);
		rc = -1;
		goto disable_i2cm_int;
	}
	pr_info("MAG: ICT1531x detected (WHOAMI=0x%02x)\n", data);

	/* ── Step 6: Read status register so last I2CM transaction is a read
	 *           (required by EDMP firmware for initial I2CM_RDATA content) ── */
	{
		u8 dummy;
		mag_serif.read_reg(mag_serif.context, ICT1531X_STATUS_REG,
				   &dummy, 1);
	}

	/* ── Step 7: Write I2CM profile for DMP autonomous operation ── */
	{
		/* DEV_PROFILE[0..1] = [Read addr=STATUS_REG, I2C_ADDR] */
		const u8 dev_prof[2] = { ICT1531X_STATUS_REG, MAG_I2C_ADDR };
		/* WR_DATA[0..3] = [SINGLE_SHOT cmd, STANDBY cmd] */
		const u8 wrb[4] = {
			ICT1531X_MODE_CTRL_REG,
			ICT1531X_MODE_CTRL_REG_MODE_SINGLE_SHOT,
			ICT1531X_MODE_CTRL_REG,
			ICT1531X_MODE_CTRL_REG_MODE_STANDBY
		};
		/* CMD_1: 2-byte write (reg_addr + 1 data byte), endflag=1 */
		const u8 cmd1 = 0x82;

		inv_ireg_write(st, REG_I2CM_DEV_PROFILE0_IPREG_TOP1,
			       sizeof(dev_prof), dev_prof);
		inv_ireg_write(st, REG_I2CM_WR_DATA0_IPREG_TOP1,
			       sizeof(wrb), wrb);
		ireg_write_u8(st, REG_I2CM_COMMAND_1_IPREG_TOP1, cmd1);

		pr_info("MAG: I2CM profile written for DMP\n");
	}

disable_i2cm_int:
	/* ── Release RCOSC clock force (let GAF manage clock) ── */
	{
		u8 misc1;
		int r3 = inv_plat_read(st, REG_REG_MISC1_DREG_BANK1, 1, &misc1);
		if (r3 == 0) {
			misc1 &= ~REG_REG_MISC1_OSC_ID_OVRD_MASK;
			inv_plat_single_write(st, REG_REG_MISC1_DREG_BANK1, misc1);
		}
	}

	/* ── Step 8: Disable I2CM_DONE interrupt (DMP takes over) ── */
	{
		u8 cfg;
		int r2 = inv_plat_read(st, REG_INT1_CONFIG1_DREG_BANK1, 1, &cfg);
		if (r2 == 0) {
			cfg &= ~REG_INT1_CONFIG1_INT1_STATUS_EN_I2CM_DONE_MASK;
			inv_plat_single_write(st, REG_INT1_CONFIG1_DREG_BANK1,
					      cfg);
		}
	}

	if (rc)
		pr_err("MAG: init FAILED (will fall back to 6-axis)\n");
	else
		pr_info("MAG: init SUCCESS\n");

	return rc;
}

/*
 * inv_mpu_mag_load_ram_image()
 * Load MRM calibration image into EDMP SRAM and set patch point.
 *
 * Ported from MCU inv_imu_edmp_mrm_init() in inv_imu_edmp_mrm.c
 */
int inv_mpu_mag_load_ram_image(struct inv_mpu_state *st, int usecase)
{
	static const u8 mrm_ram_img[] = {
#include "edmp_ram_mrm_image.h"
	};
	u32 ram_mrm_img_start_addr;
	int ret;

	(void)usecase;

	memcpy(&ram_mrm_img_start_addr,
	       &mrm_ram_img[RAM_MRM_IMG_PRGM_BASE - RAM_MRM_IMG_DATA_BASE],
	       sizeof(ram_mrm_img_start_addr));

	ret = inv_ireg_write(st, RAM_MRM_IMG_DATA_BASE,
			     sizeof(mrm_ram_img), mrm_ram_img);
	if (ret) {
		pr_err("MAG: write MRM image failed=%d\n", ret);
		return ret;
	}

	ret = inv_ireg_write(st, EDMP_INVN_ALGO_MRM_PATCH_POINT_DISPATCH,
			     4, (const u8 *)&ram_mrm_img_start_addr);
	if (ret)
		pr_err("MAG: write MRM patch point failed=%d\n", ret);
	else
		pr_info("MAG: MRM image loaded OK\n");

	return ret;
}

/*
 * inv_mpu_mag_enable_automrm()
 * Enable automatic MRM in GAF mode register.
 *
 * Ported from MCU inv_imu_edmp_mrm_enable_auto()
 */
int inv_mpu_mag_enable_automrm(struct inv_mpu_state *st)
{
	u8 gaf_mode;
	int ret;

	ret = inv_ireg_read(st, EDMP_GAF_MODE, 1, &gaf_mode);
	if (ret) return ret;

	gaf_mode |= GAF_MODE_BITMASK_MRM_ENABLE;
	ret = inv_ireg_write(st, EDMP_GAF_MODE, 1, &gaf_mode);

	return ret;
}

/*
 * inv_mpu_mag_disable_automrm()
 * Disable automatic MRM.
 */
int inv_mpu_mag_disable_automrm(struct inv_mpu_state *st)
{
	u8 gaf_mode;
	int ret;

	ret = inv_ireg_read(st, EDMP_GAF_MODE, 1, &gaf_mode);
	if (ret) return ret;

	gaf_mode &= ~GAF_MODE_BITMASK_MRM_ENABLE;
	ret = inv_ireg_write(st, EDMP_GAF_MODE, 1, &gaf_mode);

	return ret;
}

/*
 * inv_mpu_mag_set_soft_iron()
 * Set 3x3 soft-iron correction matrix in EDMP SRAM and enable it.
 *
 * Ported from MCU inv_imu_edmp_set_gaf_soft_iron_cor_matrix() +
 * inv_imu_edmp_enable_gaf_soft_iron_cor() in inv_imu_edmp.c
 */
int inv_mpu_mag_set_soft_iron(struct inv_mpu_state *st,
			      const s32 soft_iron[3][3])
{
	int i, j;
	int ret = 0;
	u8 buf[36];

	/* Write 9 elements as 12 bytes of packed s32 Q30 */
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			s32 val = soft_iron[i][j];
			memcpy(&buf[(i * 3 + j) * 4], &val, 4);
		}
	}

	/* Write to EDMP_GAF_CONFIG_MAG_SOFTIRON_MATRIX (optimized: single 12-byte write) */
	ret = inv_ireg_write(st, EDMP_GAF_CONFIG_MAG_SOFTIRON_MATRIX,
			     36, buf);
	if (ret) {
		pr_err("MAG: soft_iron write failed=%d\n", ret);
		return ret;
	}

	/* Enable soft iron correction in GAF config */
	{
		u8 en = 1;
		ret = inv_ireg_write(st, EDMP_GAF_CONFIG_MAG_SOFTIRON_MATRIX + 0x10,
				     1, &en);
	}

	pr_info("MAG: soft_iron matrix set OK\n");
	return ret;
}
