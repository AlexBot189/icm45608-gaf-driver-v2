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

#ifndef _INV_MPU_IIO_REG_45600_H_
#define _INV_MPU_IIO_REG_45600_H_

/* Comment out not to use lower power mode */
//#define SUPPORT_ACCEL_LPM
//#define SUPPORT_GYRO_LPM

#include "ICM45600_REG_External.h"
#include "ICM45600_APEX_registers.h"

/* TODO: to remove */
//#define FPGA_TEST

enum inv_icm45600_chip_rev {
	INV_ICM45600_CHIP_REV_A,
	INV_ICM45600_CHIP_REV_B,
	INV_ICM45600_CHIP_REV_C,
};

/* REG_GYRO_CONFIG0_DREG_BANK1/REG_ACCEL_CONFIG0_DREG_BANK1 */
#define SHIFT_GYRO_FS_SEL			4
#define SHIFT_ACCEL_FS_SEL			4
#define SHIFT_ODR_CONF				0
#define BIT_GYRO_FSR				0xF0
#define BIT_GYRO_ODR				0x0F
#define BIT_ACCEL_FSR				0x70
#define BIT_ACCEL_ODR				0x0F
#define BIT_SENSOR_ODR_1600HZ			0x05
#define BIT_SENSOR_ODR_800HZ			0x06
#define BIT_SENSOR_ODR_400HZ			0x07
#define BIT_SENSOR_ODR_200HZ			0x08
#define BIT_SENSOR_ODR_100HZ			0x09
#define BIT_SENSOR_ODR_50HZ			0x0A
#define BIT_SENSOR_ODR_25HZ			0x0B
#define BIT_SENSOR_ODR_12HZ			0x0C
#define BIT_SENSOR_ODR_6HZ			0x0D
#define BIT_SENSOR_ODR_3HZ			0x0E
#define BIT_SENSOR_ODR_1_5HZ			0x0F

/* REG_IPREG_SYS1_REG_170_IPREG_SYS1 */
#define BIT_GYR_LP_AVG_1X			(0 << 1)
#define BIT_GYR_LP_AVG_2X			(1 << 1)
#define BIT_GYR_LP_AVG_4X			(2 << 1)
#define BIT_GYR_LP_AVG_5X			(3 << 1)
#define BIT_GYR_LP_AVG_7X			(4 << 1)
#define BIT_GYR_LP_AVG_8X			(5 << 1)
#define BIT_GYR_LP_AVG_10X			(6 << 1)
#define BIT_GYR_LP_AVG_11X			(7 << 1)
#define BIT_GYR_LP_AVG_16X			(8 << 1)
#define BIT_GYR_LP_AVG_18X			(9 << 1)
#define BIT_GYR_LP_AVG_20X			(10 << 1)
#define BIT_GYR_LP_AVG_32X			(11 << 1)
#define BIT_GYR_LP_AVG_64X			(12 << 1)

/* REG_IPREG_SYS1_REG_172_IPREG_SYS1 */
#define BIT_GYR_UI_LPFBW_BYPASS			(0 << 0)
#define BIT_GYR_UI_LPFBW_ODR_4			(1 << 0)
#define BIT_GYR_UI_LPFBW_ODR_8			(2 << 0)
#define BIT_GYR_UI_LPFBW_ODR_16			(3 << 0)
#define BIT_GYR_UI_LPFBW_ODR_32			(4 << 0)
#define BIT_GYR_UI_LPFBW_ODR_64			(5 << 0)
#define BIT_GYR_UI_LPFBW_ODR_128		(6 << 0)

/* REG_IPREG_SYS2_REG_129_IPREG_SYS2 */
#define BIT_ACC_LP_AVG_1X			(0 << 0)
#define BIT_ACC_LP_AVG_2X			(1 << 0)
#define BIT_ACC_LP_AVG_4X			(2 << 0)
#define BIT_ACC_LP_AVG_5X			(3 << 0)
#define BIT_ACC_LP_AVG_7X			(4 << 0)
#define BIT_ACC_LP_AVG_8X			(5 << 0)
#define BIT_ACC_LP_AVG_10X			(6 << 0)
#define BIT_ACC_LP_AVG_11X			(7 << 0)
#define BIT_ACC_LP_AVG_16X			(8 << 0)
#define BIT_ACC_LP_AVG_18X			(9 << 0)
#define BIT_ACC_LP_AVG_20X			(10 << 0)
#define BIT_ACC_LP_AVG_32X			(11 << 0)
#define BIT_ACC_LP_AVG_64X			(12 << 0)

/* REG_IPREG_SYS2_REG_131_IPREG_SYS2 */
#define BIT_ACC_UI_LPFBW_BYPASS			(0 << 0)
#define BIT_ACC_UI_LPFBW_ODR_4			(1 << 0)
#define BIT_ACC_UI_LPFBW_ODR_8			(2 << 0)
#define BIT_ACC_UI_LPFBW_ODR_16			(3 << 0)
#define BIT_ACC_UI_LPFBW_ODR_32			(4 << 0)
#define BIT_ACC_UI_LPFBW_ODR_64			(5 << 0)
#define BIT_ACC_UI_LPFBW_ODR_128		(6 << 0)

/* REG_SMC_CONTROL_0_IPREG_TOP1 */
#define BIT_TMST_EN				0x01
#define BIT_TMST_FSYNC_EN			0x02
#define BIT_TMST_FORCE_AUX_FINE_EN		0x04
#define BIT_TEMP_DIS				0x08
#define BIT_ACCEL_LP_CLK_SEL			0x10
#define SMC_CONTROL_ACCEL_CLK_RCOSC  (0x01 << REG_SMC_CONTROL_0_ACCEL_LP_CLK_SEL_POS)
#define SMC_CONTROL_ACCEL_CLK_WUOSC  (0x00 << REG_SMC_CONTROL_0_ACCEL_LP_CLK_SEL_POS)

/* REG_TMST_WOM_CONFIG_DREG_BANK1 */
#define BIT_WOM_INT_MODE			0x04
#define BIT_WOM_MODE				0x08
#define BIT_WOM_EN				0x10
#define BIT_TMST_RESOL				0x20
#define BIT_TMST_DELTA_EN			0x40

/* REG_FIFO_CONFIG0_DREG_BANK1 */
#define BIT_FIFO_BYPASS				0x00
#define BIT_FIFO_STREAM				0x40
#define BIT_FIFO_STOPONFULL			0x80
#define BIT_FIFO_DEP_256			0x00
#define BIT_FIFO_DEP_512			0x01
#define BIT_FIFO_DEP_768			0x02
#define BIT_FIFO_DEP_1024			0x03
#define BIT_FIFO_DEP_1280			0x04
#define BIT_FIFO_DEP_1ES                        0x08
#define BIT_FIFO_DEP_2ES                        0x07
#define BIT_FIFO_DEP_4096			0x0f

/* REG_FIFO_CONFIG2_DREG_BANK1 */
#define BIT_FIFO_FLUSH				0x80
#define BIT_FIFO_BUS_INTF_SREG			0x00
#define BIT_FIFO_BUS_INTF_AHB			0x40
#define BIT_FIFO_ADDR_SPACE_LOCK		0x20
#define BIT_FIFO_INT_OVFL			0x10
#define BIT_FIFO_WR_WM_GT_TH			0x08
#define BIT_FIFO_FRAME_SIZE_8			0x00
#define BIT_FIFO_FRAME_SIZE_16			0x01
#define BIT_FIFO_FRAME_SIZE_20			0x02
#define BIT_FIFO_FRAME_SIZE_32			0x03
#define BIT_FIFO_FRAME_SIZE_64			0x04

/* REG_FIFO_CONFIG3_DREG_BANK1 */
#define BIT_FIFO_ES1_EN				0x20
#define BIT_FIFO_ES0_EN				0x10
#define BIT_FIFO_HIRES_EN			0x08
#define BIT_FIFO_GYRO_EN			0x04
#define BIT_FIFO_ACCEL_EN			0x02
#define BIT_FIFO_IF_EN				0x01

/* REG_INT1_CONFIG2_DREG_BANK1 */
#define SHIFT_INT1_MODE				0x01
#define SHIFT_INT1_POLARITY			0x00

/* REG_INT1_CONFIG0_DREG_BANK1 */
#define BIT_INT1_STATUS_EN_RESET_DONE		0x80
#define BIT_INT1_STATUS_EN_AUX1_AGC_RDY		0x40
#define BIT_INT1_STATUS_EN_AP_AGC_RDY		0x20
#define BIT_INT1_STATUS_EN_AP_FSYNC		0x10
#define BIT_INT1_STATUS_EN_AUX1_DRDY		0x08
#define BIT_INT1_STATUS_EN_DRDY			0x04
#define BIT_INT1_STATUS_EN_FIFO_THS		0x02
#define BIT_INT1_STATUS_EN_FIFO_FULL		0x01

/* REG_IOC_PADS_CONFIG1_IPREG_TOP1 */
#define BIT_AP_SDO_OD				0x80
#define BIT_AP_SDI_OD				0x40
#define BIT_INT2_OD				0x20
#define BIT_AUX_SDO_OD				0x10
#define BIT_AUX_CS_TP3_OD			0x08
#define BIT_AUX_SCLK_TP2_OD			0x04
#define BIT_AUX_SDI_TP1_OD			0x02
#define BIT_INT1_TP0_OD				0x01

/* fifo data packet header */
#define BIT_FIFO_HEAD_MSG			0x80
#define BIT_FIFO_HEAD_ACCEL			0x40
#define BIT_FIFO_HEAD_GYRO			0x20
#define BIT_FIFO_HEAD_20			0x10
#define BIT_FIFO_HEAD_TMSP_ODR			0x08
#define BIT_FIFO_HEAD_TMSP_NO_ODR		0x04
#define BIT_FIFO_HEAD_TMSP_FSYNC		0x0C
#define BIT_FIFO_HEAD_ODR_ACCEL			0x02
#define BIT_FIFO_HEAD_ODR_GYRO			0x01

/* REG_REG_MISC1_DREG_BANK1, shift position is 0*/
#define REG_MISC1_OSC_ID_OVRD_EDOSC             0x01
#define REG_MISC1_OSC_ID_OVRD_RCOSC             0x02
#define REG_MISC1_OSC_ID_OVRD_PLL               0x04
#define REG_MISC1_OSC_ID_OVRD_EXT               0x08

/* REG_REG_MISC2_DREG_BANK1 */
#define BIT_SOFT_RST				0x02
#define BIT_IREG_DONE				0x01

/* REG_PWR_MGMT0_DREG_BANK1 */
#define BIT_ACCEL_VER_SEL			0x10
#define BIT_GYRO_MODE_LN			0x0C
#define BIT_GYRO_MODE_LP			0x08
#define BIT_ACCEL_MODE_LN			0x03
#define BIT_ACCEL_MODE_LP			0x02
#define PWR_MGMT0_GYRO_MODE_OFF                 0
#define PWR_MGMT0_ACCEL_MODE_OFF                0
#define PWR_MGMT0_GYRO_MODE_STANDBY       (0x01 << REG_PWR_MGMT0_GYRO_MODE_POS)

/* REG_INTF_CONFIG0_DREG_BANK1 */
#define BIT_GLITCH_FILTER_DIS			0x40
#define BIT_VIR_ACCESS_AUX1_EN			0x20
#define BIT_AP_IREG_AUTO_ADDR_INC_DIS		0x10
#define BIT_I23C_TIMEOUT_EN			0x08

/* REG_INTF_CONFIG1_OVRD_DREG_BANK1 */
#define BIT_AP_SPI_34_MODE_OVRD			0x08
#define BIT_AP_SPI_34_MODE_OVRD_VAL_SPI3	0x00
#define BIT_AP_SPI_34_MODE_OVRD_VAL_SPI4	0x04
#define BIT_AP_SPI_MODE_OVRD			0x02
#define BIT_AP_SPI_MODE_OVRD_VAL_0_3		0x00
#define BIT_AP_SPI_MODE_OVRD_VAL_1_2		0x01

/* REG_SREG_CTRL_IPREG_TOP1 */
#define BIT_SREG_DEBUG_DATA_INJECT_EN		0x04
#define BIT_SREG_DATA_ENDIAN_SEL_LITTLE		0x00
#define BIT_SREG_DATA_ENDIAN_SEL_BIG		0x02
#define BIT_SREG_INVALID_IND_DIS		0x01


/* data definitions */
#define FIFO_PACKET_BYTE_SINGLE			8
#define FIFO_PACKET_BYTE_6X			16
#define FIFO_PACKET_BYTE_HIRES			20
#define FIFO_COUNT_BYTE				2

/* sensor startup time TODO */
#define INV_ICM45600_GYRO_START_TIME		30
#define INV_ICM45600_ACCEL_START_TIME		30

/* M-reg access wait tile TODO */
#define INV_ICM45600_IREG_ADDR_WAIT_US		10
#define INV_ICM45600_IREG_RW_WAIT_US		10

/* temperature sensor TODO */
#define TEMP_SCALE				100 /* scale by 100 */
#define TEMP_LSB_PER_DEG			2   /* 2LSB=1degC */
#define TEMP_OFFSET				25  /* 25 degC */

/* enum for sensor */
enum INV_SENSORS {
	SENSOR_ACCEL = 0,
	SENSOR_TEMP,
	SENSOR_GYRO,
	SENSOR_COMPASS,
	SENSOR_PRESSURE,
	SENSOR_NUM_MAX,
	SENSOR_INVALID,
};

#define BASE_SAMPLE_RATE		800
#define GESTURE_ACCEL_RATE		50
#define ESI_GYRO_RATE			800
#define MPU_INIT_SENSOR_RATE_LNM	12	/* min Hz in LNM */
#define MPU_INIT_SENSOR_RATE_LPM	3	/* min Hz in LPM */
#define MAX_FIFO_PACKET_READ		16
#define HARDWARE_FIFO_SIZE		((BIT_FIFO_DEP_4096 + 1)*256)
#define MAX_BATCH_FIFO_SIZE		(HARDWARE_FIFO_SIZE * 15 /16)
#define LEFT_OVER_BYTES			128
#define POWER_UP_TIME			100
#define REG_UP_TIME_USEC		100
#define IIO_BUFFER_BYTES		8
#define REG_FIFO_COUNT_H		REG_FIFO_COUNT_0_DREG_BANK1
#define BYTES_PER_SENSOR		6
#define BYTES_FOR_TEMP			1
#define FIRST_DROP_SAMPLES_ACC_800HZ	20
#define FIRST_DROP_SAMPLES_ACC_200HZ	10
#define FIRST_DROP_SAMPLES_GYR_800HZ	20
#define FIRST_DROP_SAMPLES_GYR_200HZ	10
#define WOM_THRESHOLD			13 /* 1000 / 256 * 13 = 50.7mg */

/* DMP ODR definition for register
 * REG_DMP_EXT_SEN_ODR_CFG_DREG_BANK1                           0x27 */
#define BIT_DMP_ODR_25HZ                0
#define BIT_DMP_ODR_50HZ                1
#define BIT_DMP_ODR_100HZ               2
#define BIT_DMP_ODR_200HZ               3
#define BIT_DMP_ODR_400HZ               4
#define BIT_DMP_ODR_800HZ               5

/* DMP start address */
#define EDMP_ROM_START_ADDR_IRQ0            0x4000
#define EDMP_ROM_START_ADDR_IRQ1            0x4004
#define EDMP_ROM_START_ADDR_IRQ2            0x4008
/* stack address is the same as DMP load address since it grow in opposite */
#define EDMP_STACK_ADDR                 0x0500
#define	EDMP_RAM_BASE               0x0000
#define	EDMP_RAM_REVA_SIZE          0x04C0 /* EDMP Data */
#define EDMP_RAM_REVB_SIZE          0x1800


/* TODO
 * INT configurations
 * Polarity: 0 -> Active Low, 1 -> Active High
 * Drive circuit: 0 -> Open Drain, 1 -> Push-Pull
 * Mode: 0 -> Pulse, 1 -> Latch
 */
#define INT_POLARITY			1
#define INT_DRIVE_CIRCUIT		1
#define INT_MODE			0

#define ACC_LPM_MAX_RATE		(400)
#define GYR_LPM_MAX_RATE		(400)

/*
typedef union {
	unsigned char Byte;
	struct {
		unsigned char g_odr_change_bit:1;
		unsigned char a_odr_change_bit:1;
		unsigned char timestamp_bit:2;
		unsigned char twentybits_bit:1;
		unsigned char gyro_bit:1;
		unsigned char accel_bit:1;
		unsigned char msg_bit:1;
	} bits;
} icm4x6xx_fifo_header_t;

*/
/** Describe the content of the FIFO header */
typedef union
{
	unsigned char Byte;
	struct
	{
		unsigned char s1_odr_different : 1;
		unsigned char s0_odr_different : 1;
		unsigned char fsync_bit : 1;
		unsigned char timestamp_bit : 1;
		unsigned char twentybits_bit : 1;
		unsigned char s1_bit : 1;
		unsigned char s0_bit : 1;
		unsigned char ext_header : 1;
	}bits;
} fifo_header_t;

typedef union
{
	unsigned char Byte;
	struct
	{
		unsigned char es0_en : 1;
		unsigned char es1_en : 1;
		unsigned char es0_vld : 1;
		unsigned char es1_vld : 1;
		unsigned char es0_6b_9b : 1;
		unsigned char unused1 : 1;
		unsigned char unused2 : 1;
		unsigned char unused3 : 1;
	}bits;
} fifo_header2_t;

/* chip specific functions */
struct inv_mpu_state;
int inv_get_45600_pedometer_steps(struct inv_mpu_state *st,
	int *ped, int *update);
int inv_imu_run_internal_stc(struct inv_mpu_state *st);
int inv_set_idle(struct inv_mpu_state *st);
int inv_reset_idle(struct inv_mpu_state *st);
int inv_ireg_write(struct inv_mpu_state *st, int addr, int size, const u8 *data);
static inline int inv_ireg_single_write(struct inv_mpu_state *st, int addr, u8 data)
{
	return inv_ireg_write(st, addr, 1, &data);
}
int inv_ireg_read(struct inv_mpu_state *st, int addr, int len, u8 *data);
bool inv_get_apex_enabled(struct inv_mpu_state *st);
int inv_get_apex_odr(struct inv_mpu_state *st);
int inv_mpu_setup_compass_slave(struct inv_mpu_state *st);
int inv_mpu_configure_dmp(struct inv_mpu_state *st);
int inv_power_up_sram(struct inv_mpu_state *st);
int inv_imu_edmp_init_apex(struct inv_mpu_state *st, int clean_sram);
int inv_imu_soft_reset(struct inv_mpu_state *st);
int inv_mpu_unlock_pressure_sensor(struct inv_mpu_state *st);

#endif /* _INV_MPU_IIO_REG_45600_H_ */
