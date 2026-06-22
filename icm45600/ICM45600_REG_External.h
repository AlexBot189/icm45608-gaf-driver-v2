/*
 *________________________________________________________________________________________________________
 * Copyright (c) 2017 InvenSense Inc. All rights reserved.
 *
 * This software, related documentation and any modifications thereto (collectively "Software") is subject
 * to InvenSense and its licensors intellectual property rights under U.S. and international copyright
 * and other intellectual property rights laws.
 *
 * InvenSense and its licensors retain all intellectual property and proprietary rights in and to the Software
 * and any use, reproduction, disclosure or distribution of the Software without an express license agreement
 * from InvenSense is strictly prohibited.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE SOFTWARE IS
 * PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * INVENSENSE BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
   OF THE SOFTWARE.
 * ________________________________________________________________________________________________________
 */
#ifndef _REG_EXTERNAL_H_
#define _REG_EXTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @file REG.h
 * File exposing the device register map
 */

/* ----------------------------------------------------------------------------
 * Device Register map
 *
 * Next macros defines address for all reg registers as listed by device
 * datasheet.
 * Macros name is REG_<REGISTER_NAME> with REGISTER_NAME being the name of
 * the corresponding register in datasheet.
 * Note that macro name is REG_<REGISTER_NAME>_Bx with x being the bank
 * number for registers that are in bank 1 and further (suffix is ommitted for
 * bank 0 registers)
 * ---------------------------------------------------------------------------- */

/* IPREG_BAR */

/* IPREG_ANA */

/* DREG_TOP1 */

/* DREG_TOP2 */

/* IHREG_SREG */

/* IMEM_ROM */

/* IMEM_SRAM */

/* IPREG_FPGA */

/* IPREG_OTP */

/* IPREG_SYS1 */
#define REG_IPREG_SYS1_REG_42_IPREG_SYS1                                        0xa42a
#define REG_IPREG_SYS1_REG_43_IPREG_SYS1                                        0xa42b
#define REG_IPREG_SYS1_REG_56_IPREG_SYS1                                        0xa438
#define REG_IPREG_SYS1_REG_57_IPREG_SYS1                                        0xa439
#define REG_IPREG_SYS1_REG_70_IPREG_SYS1                                        0xa446
#define REG_IPREG_SYS1_REG_71_IPREG_SYS1                                        0xa447
#define REG_IPREG_SYS1_REG_166_IPREG_SYS1                                       0xa4a6
#define REG_IPREG_SYS1_REG_168_IPREG_SYS1                                       0xa4a8
#define REG_IPREG_SYS1_REG_170_IPREG_SYS1                                       0xa4aa
#define REG_IPREG_SYS1_REG_171_IPREG_SYS1                                       0xa4ab
#define REG_IPREG_SYS1_REG_172_IPREG_SYS1                                       0xa4ac
#define REG_IPREG_SYS1_REG_173_IPREG_SYS1                                       0xa4ad

/* IPREG_SYS2 */
#define REG_IPREG_SYS2_REG_24_IPREG_SYS2                                        0xa518
#define REG_IPREG_SYS2_REG_25_IPREG_SYS2                                        0xa519
#define REG_IPREG_SYS2_REG_32_IPREG_SYS2                                        0xa520
#define REG_IPREG_SYS2_REG_33_IPREG_SYS2                                        0xa521
#define REG_IPREG_SYS2_REG_40_IPREG_SYS2                                        0xa528
#define REG_IPREG_SYS2_REG_41_IPREG_SYS2                                        0xa529
#define REG_IPREG_SYS2_REG_123_IPREG_SYS2                                       0xa57b
#define REG_IPREG_SYS2_REG_129_IPREG_SYS2                                       0xa581
#define REG_IPREG_SYS2_REG_130_IPREG_SYS2                                       0xa582
#define REG_IPREG_SYS2_REG_131_IPREG_SYS2                                       0xa583
#define REG_IPREG_SYS2_REG_132_IPREG_SYS2                                       0xa584

/* IPREG_TOP1 */
#define REG_I2CM_COMMAND_0_IPREG_TOP1                                           0xa206
#define REG_I2CM_COMMAND_1_IPREG_TOP1                                           0xa207
#define REG_I2CM_COMMAND_2_IPREG_TOP1                                           0xa208
#define REG_I2CM_COMMAND_3_IPREG_TOP1                                           0xa209
#define REG_I2CM_DEV_PROFILE0_IPREG_TOP1                                        0xa20e
#define REG_I2CM_DEV_PROFILE1_IPREG_TOP1                                        0xa20f
#define REG_I2CM_DEV_PROFILE2_IPREG_TOP1                                        0xa210
#define REG_I2CM_DEV_PROFILE3_IPREG_TOP1                                        0xa211
#define REG_I2CM_CONTROL_IPREG_TOP1                                             0xa216
#define REG_I2CM_STATUS_IPREG_TOP1                                              0xa218
#define REG_I2CM_EXT_DEV_STATUS_IPREG_TOP1                                      0xa21a
#define REG_I2CM_RD_DATA0_IPREG_TOP1                                            0xa21b
#define REG_I2CM_RD_DATA1_IPREG_TOP1                                            0xa21c
#define REG_I2CM_RD_DATA2_IPREG_TOP1                                            0xa21d
#define REG_I2CM_RD_DATA3_IPREG_TOP1                                            0xa21e
#define REG_I2CM_RD_DATA4_IPREG_TOP1                                            0xa21f
#define REG_I2CM_RD_DATA5_IPREG_TOP1                                            0xa220
#define REG_I2CM_RD_DATA6_IPREG_TOP1                                            0xa221
#define REG_I2CM_RD_DATA7_IPREG_TOP1                                            0xa222
#define REG_I2CM_RD_DATA8_IPREG_TOP1                                            0xa223
#define REG_I2CM_RD_DATA9_IPREG_TOP1                                            0xa224
#define REG_I2CM_RD_DATA10_IPREG_TOP1                                           0xa225
#define REG_I2CM_RD_DATA11_IPREG_TOP1                                           0xa226
#define REG_I2CM_RD_DATA12_IPREG_TOP1                                           0xa227
#define REG_I2CM_RD_DATA13_IPREG_TOP1                                           0xa228
#define REG_I2CM_RD_DATA14_IPREG_TOP1                                           0xa229
#define REG_I2CM_RD_DATA15_IPREG_TOP1                                           0xa22a
#define REG_I2CM_RD_DATA16_IPREG_TOP1                                           0xa22b
#define REG_I2CM_RD_DATA17_IPREG_TOP1                                           0xa22c
#define REG_I2CM_RD_DATA18_IPREG_TOP1                                           0xa22d
#define REG_I2CM_RD_DATA19_IPREG_TOP1                                           0xa22e
#define REG_I2CM_RD_DATA20_IPREG_TOP1                                           0xa22f
#define REG_I2CM_WR_DATA0_IPREG_TOP1                                            0xa233
#define REG_I2CM_WR_DATA1_IPREG_TOP1                                            0xa234
#define REG_I2CM_WR_DATA2_IPREG_TOP1                                            0xa235
#define REG_I2CM_WR_DATA3_IPREG_TOP1                                            0xa236
#define REG_I2CM_WR_DATA4_IPREG_TOP1                                            0xa237
#define REG_I2CM_WR_DATA5_IPREG_TOP1                                            0xa238
#define REG_SIFS_IXC_ERROR_STATUS_IPREG_TOP1                                    0xa24b
#define REG_EDMP_PRGRM_IRQ0_0_IPREG_TOP1                                        0xa24f
#define REG_EDMP_PRGRM_IRQ0_1_IPREG_TOP1                                        0xa250
#define REG_EDMP_PRGRM_IRQ1_0_IPREG_TOP1                                        0xa251
#define REG_EDMP_PRGRM_IRQ1_1_IPREG_TOP1                                        0xa252
#define REG_EDMP_PRGRM_IRQ2_0_IPREG_TOP1                                        0xa253
#define REG_EDMP_PRGRM_IRQ2_1_IPREG_TOP1                                        0xa254
#define REG_EDMP_SP_START_ADDR_IPREG_TOP1                                       0xa255
#define REG_SMC_CONTROL_0_IPREG_TOP1                                            0xa258
#define REG_SMC_CONTROL_1_IPREG_TOP1                                            0xa259
#define REG_STC_CONFIG_IPREG_TOP1                                               0xa263
#define REG_SREG_CTRL_IPREG_TOP1                                                0xa267
#define REG_SIFS_I3C_STC_CFG_IPREG_TOP1                                         0xa268
#define REG_INT_PULSE_MIN_ON_INTF0_IPREG_TOP1                                   0xa269
#define REG_INT_PULSE_MIN_ON_INTF1_IPREG_TOP1                                   0xa26a
#define REG_INT_PULSE_MIN_OFF_INTF0_IPREG_TOP1                                  0xa26b
#define REG_INT_PULSE_MIN_OFF_INTF1_IPREG_TOP1                                  0xa26c
#define REG_ISR_0_7_IPREG_TOP1                                                  0xa26e
#define REG_ISR_8_15_IPREG_TOP1                                                 0xa26f
#define REG_ISR_16_23_IPREG_TOP1                                                0xa270
#define REG_STATUS_MASK_PIN_0_7_IPREG_TOP1                                      0xa271
#define REG_STATUS_MASK_PIN_8_15_IPREG_TOP1                                     0xa272
#define REG_STATUS_MASK_PIN_16_23_IPREG_TOP1                                    0xa273
#define REG_INT_I2CM_SOURCE_IPREG_TOP1                                          0xa274
#define REG_ACCEL_WOM_X_THR_IPREG_TOP1                                          0xa27e
#define REG_ACCEL_WOM_Y_THR_IPREG_TOP1                                          0xa27f
#define REG_ACCEL_WOM_Z_THR_IPREG_TOP1                                          0xa280
#define REG_SELFTEST_IPREG_TOP1                                                 0xa290
#define REG_IPREG_MISC_IPREG_TOP1                                               0xa297
#define REG_SW_PLL1_TRIM_IPREG_TOP1                                             0xa2a2
#define REG_FIFO_SRAM_SLEEP_IPREG_TOP1                                          0xa2a7

/* DREG_BANK1 */
#define REG_ACCEL_DATA_X1_UI_DREG_BANK1                                         0x00
#define REG_ACCEL_DATA_X0_UI_DREG_BANK1                                         0x01
#define REG_ACCEL_DATA_Y1_UI_DREG_BANK1                                         0x02
#define REG_ACCEL_DATA_Y0_UI_DREG_BANK1                                         0x03
#define REG_ACCEL_DATA_Z1_UI_DREG_BANK1                                         0x04
#define REG_ACCEL_DATA_Z0_UI_DREG_BANK1                                         0x05
#define REG_GYRO_DATA_X1_UI_DREG_BANK1                                          0x06
#define REG_GYRO_DATA_X0_UI_DREG_BANK1                                          0x07
#define REG_GYRO_DATA_Y1_UI_DREG_BANK1                                          0x08
#define REG_GYRO_DATA_Y0_UI_DREG_BANK1                                          0x09
#define REG_GYRO_DATA_Z1_UI_DREG_BANK1                                          0x0a
#define REG_GYRO_DATA_Z0_UI_DREG_BANK1                                          0x0b
#define REG_TEMP_DATA1_UI_DREG_BANK1                                            0x0c
#define REG_TEMP_DATA0_UI_DREG_BANK1                                            0x0d
#define REG_TMST_FSYNCH_DREG_BANK1                                              0x0e
#define REG_TMST_FSYNCL_DREG_BANK1                                              0x0f
#define REG_PWR_MGMT0_DREG_BANK1                                                0x10
#define REG_FIFO_COUNT_0_DREG_BANK1                                             0x12
#define REG_FIFO_COUNT_1_DREG_BANK1                                             0x13
#define REG_FIFO_DATA_DREG_BANK1                                                0x14
#define REG_INT1_CONFIG0_DREG_BANK1                                             0x16
#define REG_INT1_CONFIG1_DREG_BANK1                                             0x17
#define REG_INT1_CONFIG2_DREG_BANK1                                             0x18
#define REG_INT1_STATUS0_DREG_BANK1                                             0x19
#define REG_INT1_STATUS1_DREG_BANK1                                             0x1a
#define REG_ACCEL_CONFIG0_DREG_BANK1                                            0x1b
#define REG_GYRO_CONFIG0_DREG_BANK1                                             0x1c
#define REG_FIFO_CONFIG0_DREG_BANK1                                             0x1d
#define REG_FIFO_CONFIG1_0_DREG_BANK1                                           0x1e
#define REG_FIFO_CONFIG1_1_DREG_BANK1                                           0x1f
#define REG_FIFO_CONFIG2_DREG_BANK1                                             0x20
#define REG_FIFO_CONFIG3_DREG_BANK1                                             0x21
#define REG_FIFO_CONFIG4_DREG_BANK1                                             0x22
#define REG_TMST_WOM_CONFIG_DREG_BANK1                                          0x23
#define REG_FSYNC_CONFIG0_DREG_BANK1                                            0x24
#define REG_FSYNC_CONFIG1_DREG_BANK1                                            0x25
#define REG_RTC_CONFIG_DREG_BANK1                                               0x26
#define REG_DMP_EXT_SEN_ODR_CFG_DREG_BANK1                                      0x27
#define REG_ODR_DECIMATE_CONFIG_DREG_BANK1                                      0x28
#define REG_EDMP_APEX_EN0_DREG_BANK1                                            0x29
#define REG_EDMP_APEX_EN1_DREG_BANK1                                            0x2a
#define REG_APEX_BUFFER_MGMT_DREG_BANK1                                         0x2b
#define REG_INTF_CONFIG0_DREG_BANK1                                             0x2c
#define REG_INTF_CONFIG1_OVRD_DREG_BANK1                                        0x2d
#define REG_INTF_AUX_CONFIG_DREG_BANK1                                          0x2e
#define REG_IOC_PAD_SCENARIO_DREG_BANK1                                         0x2f
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_DREG_BANK1                                0x30
#define REG_IOC_PAD_SCENARIO_OVRD_DREG_BANK1                                    0x31
#define REG_DRIVE_CONFIG0_DREG_BANK1                                            0x32
#define REG_DRIVE_CONFIG1_DREG_BANK1                                            0x33
#define REG_DRIVE_CONFIG2_DREG_BANK1                                            0x34
#define REG_REG_MISC1_DREG_BANK1                                                0x35
#define REG_INT_APEX_CONFIG0_DREG_BANK1                                         0x39
#define REG_INT_APEX_CONFIG1_DREG_BANK1                                         0x3a
#define REG_INT_APEX_STATUS0_DREG_BANK1                                         0x3b
#define REG_INT_APEX_STATUS1_DREG_BANK1                                         0x3c
#define REG_INTF_CONFIG_OVRD_AUX1_DREG_BANK1                                    0x42
#define REG_ACCEL_DATA_X1_AUX1_DREG_BANK1                                       0x44
#define REG_ACCEL_DATA_X0_AUX1_DREG_BANK1                                       0x45
#define REG_ACCEL_DATA_Y1_AUX1_DREG_BANK1                                       0x46
#define REG_ACCEL_DATA_Y0_AUX1_DREG_BANK1                                       0x47
#define REG_ACCEL_DATA_Z1_AUX1_DREG_BANK1                                       0x48
#define REG_ACCEL_DATA_Z0_AUX1_DREG_BANK1                                       0x49
#define REG_GYRO_DATA_X1_AUX1_DREG_BANK1                                        0x4a
#define REG_GYRO_DATA_X0_AUX1_DREG_BANK1                                        0x4b
#define REG_GYRO_DATA_Y1_AUX1_DREG_BANK1                                        0x4c
#define REG_GYRO_DATA_Y0_AUX1_DREG_BANK1                                        0x4d
#define REG_GYRO_DATA_Z1_AUX1_DREG_BANK1                                        0x4e
#define REG_GYRO_DATA_Z0_AUX1_DREG_BANK1                                        0x4f
#define REG_TEMP_DATA1_AUX1_DREG_BANK1                                          0x50
#define REG_TEMP_DATA0_AUX1_DREG_BANK1                                          0x51
#define REG_TMST_FSYNCH_AUX1_DREG_BANK1                                         0x52
#define REG_TMST_FSYNCL_AUX1_DREG_BANK1                                         0x53
#define REG_PWR_MGMT_AUX1_DREG_BANK1                                            0x54
#define REG_FS_SEL_AUX1_DREG_BANK1                                              0x55
#define REG_INT2_CONFIG0_DREG_BANK1                                             0x56
#define REG_INT2_CONFIG1_DREG_BANK1                                             0x57
#define REG_INT2_CONFIG2_DREG_BANK1                                             0x58
#define REG_INT2_STATUS0_DREG_BANK1                                             0x59
#define REG_INT2_STATUS1_DREG_BANK1                                             0x5a
#define REG_INTF_CONFIG_OVRD_AUX2_DREG_BANK1                                    0x5c
#define REG_ACCEL_DATA_X1_AUX2_DREG_BANK1                                       0x5e
#define REG_ACCEL_DATA_X0_AUX2_DREG_BANK1                                       0x5f
#define REG_ACCEL_DATA_Y1_AUX2_DREG_BANK1                                       0x60
#define REG_ACCEL_DATA_Y0_AUX2_DREG_BANK1                                       0x61
#define REG_ACCEL_DATA_Z1_AUX2_DREG_BANK1                                       0x62
#define REG_ACCEL_DATA_Z0_AUX2_DREG_BANK1                                       0x63
#define REG_GYRO_DATA_X1_AUX2_DREG_BANK1                                        0x64
#define REG_GYRO_DATA_X0_AUX2_DREG_BANK1                                        0x65
#define REG_GYRO_DATA_Y1_AUX2_DREG_BANK1                                        0x66
#define REG_GYRO_DATA_Y0_AUX2_DREG_BANK1                                        0x67
#define REG_GYRO_DATA_Z1_AUX2_DREG_BANK1                                        0x68
#define REG_GYRO_DATA_Z0_AUX2_DREG_BANK1                                        0x69
#define REG_TEMP_DATA1_AUX2_DREG_BANK1                                          0x6a
#define REG_TEMP_DATA0_AUX2_DREG_BANK1                                          0x6b
#define REG_TMST_FSYNCH_AUX2_DREG_BANK1                                         0x6c
#define REG_TMST_FSYNCL_AUX2_DREG_BANK1                                         0x6d
#define REG_PWR_MGMT_AUX2_DREG_BANK1                                            0x6e
#define REG_FS_SEL_AUX2_DREG_BANK1                                              0x6f
#define REG_INT_AUX2_CONFIG_DREG_BANK1                                          0x70
#define REG_INT_AUX2_STATUS_DREG_BANK1                                          0x71
#define REG_WHO_AM_I_DREG_BANK1                                                 0x72
#define REG_REG_HOST_MSG_DREG_BANK1                                             0x73
#define REG_IREG_ADDR_15_8_DREG_BANK1                                           0x7c
#define REG_IREG_ADDR_7_0_DREG_BANK1                                            0x7d
#define REG_IREG_DATA_DREG_BANK1                                                0x7e
#define REG_REG_MISC2_DREG_BANK1                                                0x7f

/* DREG_BANK2 */


/* ---------------------------------------------------------------------------
 * register IPREG_BAR
 * ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------
 * register IPREG_ANA
 * ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------
 * register DREG_TOP1
 * ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------
 * register DREG_TOP2
 * ---------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------
 * register IHREG_SREG
 * ---------------------------------------------------------------------------*/



/* ---------------------------------------------------------------------------
 * register IMEM_ROM
 * ---------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------
 * register IMEM_SRAM
 * ---------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------
 * register IPREG_FPGA
 * ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------
 * register IPREG_OTP
 * ---------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------
 * register IPREG_SYS1
 * ---------------------------------------------------------------------------*/

/*
 * REG_IPREG_SYS1_REG_42
 * Register Name : IPREG_SYS1_REG_42
 */

/*
 * gyro_x_offuser
 * user correction range ±62.5 [dps], resolution 7.5 [mdps]
 */
#define REG_IPREG_SYS1_REG_42_GYRO_X_OFFUSER_POS      0x00
#define REG_IPREG_SYS1_REG_42_GYRO_X_OFFUSER_MASK     0xff



/*
 * REG_IPREG_SYS1_REG_43
 * Register Name : IPREG_SYS1_REG_43
 */

/*
 * gyro_x_offuser
 * user correction range ±62.5 [dps], resolution 7.5 [mdps]
 */
#define REG_IPREG_SYS1_REG_43_GYRO_X_OFFUSER_POS      0x00
#define REG_IPREG_SYS1_REG_43_GYRO_X_OFFUSER_MASK     0x3f



/*
 * REG_IPREG_SYS1_REG_56
 * Register Name : IPREG_SYS1_REG_56
 */

/*
 * gyro_y_offuser
 * user correction range ±62.5 [dps], resolution 7.5 [mdps]
 */
#define REG_IPREG_SYS1_REG_56_GYRO_Y_OFFUSER_POS      0x00
#define REG_IPREG_SYS1_REG_56_GYRO_Y_OFFUSER_MASK     0xff



/*
 * REG_IPREG_SYS1_REG_57
 * Register Name : IPREG_SYS1_REG_57
 */

/*
 * gyro_y_offuser
 * user correction range ±62.5 [dps], resolution 7.5 [mdps]
 */
#define REG_IPREG_SYS1_REG_57_GYRO_Y_OFFUSER_POS      0x00
#define REG_IPREG_SYS1_REG_57_GYRO_Y_OFFUSER_MASK     0x3f



/*
 * REG_IPREG_SYS1_REG_70
 * Register Name : IPREG_SYS1_REG_70
 */

/*
 * gyro_z_offuser
 * user correction range ±62.5 [dps], resolution 7.5 [mdps]
 */
#define REG_IPREG_SYS1_REG_70_GYRO_Z_OFFUSER_POS      0x00
#define REG_IPREG_SYS1_REG_70_GYRO_Z_OFFUSER_MASK     0xff



/*
 * REG_IPREG_SYS1_REG_71
 * Register Name : IPREG_SYS1_REG_71
 */

/*
 * gyro_z_offuser
 * user correction range ±62.5 [dps], resolution 7.5 [mdps]
 */
#define REG_IPREG_SYS1_REG_71_GYRO_Z_OFFUSER_POS      0x00
#define REG_IPREG_SYS1_REG_71_GYRO_Z_OFFUSER_MASK     0x3f



/*
 * REG_IPREG_SYS1_REG_166
 * Register Name : IPREG_SYS1_REG_166
 */

/*
 * gyro_afsr_mode
 * 00: disabled, use LOW; 01: disabled, use HIGH;
 * 10: enabled, starts LOW; 11: enabled, starts HIGH
 */
#define REG_IPREG_SYS1_REG_166_GYRO_AFSR_MODE_POS      0x03
#define REG_IPREG_SYS1_REG_166_GYRO_AFSR_MODE_MASK     (0x03 << REG_IPREG_SYS1_REG_166_GYRO_AFSR_MODE_POS)

/*
 * gyro_src_ctrl
 * SRC CTRL: 0x0: S4S and FIR filter off, 0x1: S4S off and FIR filter on, 0x2: S4S on and FIR filter on, 0x3: reserved (debug mode).
 */
#define REG_IPREG_SYS1_REG_166_GYRO_SRC_CTRL_POS      0x05
#define REG_IPREG_SYS1_REG_166_GYRO_SRC_CTRL_MASK     (0x03 << REG_IPREG_SYS1_REG_166_GYRO_SRC_CTRL_POS)



/*
 * REG_IPREG_SYS1_REG_168
 * Register Name : IPREG_SYS1_REG_168
 */

/*
 * gyro_afsr_shared
 * 1: all axis switch to high if just one is high;
 * 0: all axis are independently handling afsr
 */
#define REG_IPREG_SYS1_REG_168_GYRO_AFSR_SHARED_POS      0x00
#define REG_IPREG_SYS1_REG_168_GYRO_AFSR_SHARED_MASK     0x01

/*
 * gyro_ois_m6_byp
 * 0: ois notch enabled; 1: ois notch disabled
 */
#define REG_IPREG_SYS1_REG_168_GYRO_OIS_M6_BYP_POS      0x01
#define REG_IPREG_SYS1_REG_168_GYRO_OIS_M6_BYP_MASK     (0x01 << REG_IPREG_SYS1_REG_168_GYRO_OIS_M6_BYP_POS)

/*
 * REG_IPREG_SYS1_REG_170
 * Register Name : IPREG_SYS1_REG_170
 */

/*
 * gyro_lp_avg_sel
 * Gyro Low Power Mode Average Selection
 * 0:1  1:2   2:4   3:5  4:7   5:8  6:10  7:11  8:16  9:18  10:20  11:32  12-15: 64
 */
#define REG_IPREG_SYS1_REG_170_GYRO_LP_AVG_SEL_POS      0x01
#define REG_IPREG_SYS1_REG_170_GYRO_LP_AVG_SEL_MASK     (0x0f << REG_IPREG_SYS1_REG_170_GYRO_LP_AVG_SEL_POS)

/*
 * gyro_ois_hpfbw_sel
 * OIS HPF for gyro;
 * 0: bypass; 1: Reserved; 2:250mHz; 3:62mHz; 4:16mHz
 */
#define REG_IPREG_SYS1_REG_170_GYRO_OIS_HPFBW_SEL_POS      0x05
#define REG_IPREG_SYS1_REG_170_GYRO_OIS_HPFBW_SEL_MASK     (0x07 << REG_IPREG_SYS1_REG_170_GYRO_OIS_HPFBW_SEL_POS)



/*
 * REG_IPREG_SYS1_REG_171
 * Register Name : IPREG_SYS1_REG_171
 */

/*
 * gyro_ois_lpf1bw_sel
 * selects OIS1 low pass cut-off
 * 0: bypass; 1: 1100; 2:900, 3:600; 4:285; 5:139; 6,7:65 [Hz]
 */
#define REG_IPREG_SYS1_REG_171_GYRO_OIS_LPF1BW_SEL_POS      0x00
#define REG_IPREG_SYS1_REG_171_GYRO_OIS_LPF1BW_SEL_MASK     0x07

/*
 * gyro_ois_lpf2bw_sel
 * selects OIS2 low pass cut-off
 * 0: bypass; 1: 1100; 2:900, 3:600; 4:285; 5:139; 6,7:65 [Hz]
 */
#define REG_IPREG_SYS1_REG_171_GYRO_OIS_LPF2BW_SEL_POS      0x03
#define REG_IPREG_SYS1_REG_171_GYRO_OIS_LPF2BW_SEL_MASK     (0x07 << REG_IPREG_SYS1_REG_171_GYRO_OIS_LPF2BW_SEL_POS)



/*
 * REG_IPREG_SYS1_REG_172
 * Register Name : IPREG_SYS1_REG_172
 */

/*
 * gyro_ui_lpfbw_sel
 * Selects UI path low pass cut-off
 * 0:bypass; 1: ODR/4 2: ODR/8 3:ODR/16 4:ODR/32 5:ODR/64 6,7:ODR/128
 */
#define REG_IPREG_SYS1_REG_172_GYRO_UI_LPFBW_SEL_POS      0x00
#define REG_IPREG_SYS1_REG_172_GYRO_UI_LPFBW_SEL_MASK     0x07

/*
 * gyro_ois_hpf1_byp
 * 1: bypasses HPF for OIS1 path
 */
#define REG_IPREG_SYS1_REG_172_GYRO_OIS_HPF1_BYP_POS      0x07
#define REG_IPREG_SYS1_REG_172_GYRO_OIS_HPF1_BYP_MASK     (0x01 << REG_IPREG_SYS1_REG_172_GYRO_OIS_HPF1_BYP_POS)



/*
 * REG_IPREG_SYS1_REG_173
 * Register Name : IPREG_SYS1_REG_173
 */

/*
 * gyro_ois_hpf2_byp
 * 1: bypasses HPF for OIS2 path
 */
#define REG_IPREG_SYS1_REG_173_GYRO_OIS_HPF2_BYP_POS      0x00
#define REG_IPREG_SYS1_REG_173_GYRO_OIS_HPF2_BYP_MASK     0x01


/* ---------------------------------------------------------------------------
 * register IPREG_SYS2
 * ---------------------------------------------------------------------------*/

/*
 * REG_IPREG_SYS2_REG_24
 * Register Name : IPREG_SYS2_REG_24
 */

/*
 * accel_x_offuser
 * gos offset correction (user): range  ±1 [gee], resolution 0.125mgee
 */
#define REG_IPREG_SYS2_REG_24_ACCEL_X_OFFUSER_POS      0x00
#define REG_IPREG_SYS2_REG_24_ACCEL_X_OFFUSER_MASK     0xff



/*
 * REG_IPREG_SYS2_REG_25
 * Register Name : IPREG_SYS2_REG_25
 */

/*
 * accel_x_offuser
 * gos offset correction (user): range  ±1 [gee], resolution 0.125mgee
 */
#define REG_IPREG_SYS2_REG_25_ACCEL_X_OFFUSER_POS      0x00
#define REG_IPREG_SYS2_REG_25_ACCEL_X_OFFUSER_MASK     0x3f



/*
 * REG_IPREG_SYS2_REG_32
 * Register Name : IPREG_SYS2_REG_32
 */

/*
 * accel_y_offuser
 * gos offset correction (user): range  ±1 [gee], resolution 0.125mgee
 */
#define REG_IPREG_SYS2_REG_32_ACCEL_Y_OFFUSER_POS      0x00
#define REG_IPREG_SYS2_REG_32_ACCEL_Y_OFFUSER_MASK     0xff



/*
 * REG_IPREG_SYS2_REG_33
 * Register Name : IPREG_SYS2_REG_33
 */

/*
 * accel_y_offuser
 * gos offset correction (user): range  ±1 [gee], resolution 0.125mgee
 */
#define REG_IPREG_SYS2_REG_33_ACCEL_Y_OFFUSER_POS      0x00
#define REG_IPREG_SYS2_REG_33_ACCEL_Y_OFFUSER_MASK     0x3f



/*
 * REG_IPREG_SYS2_REG_40
 * Register Name : IPREG_SYS2_REG_40
 */

/*
 * accel_z_offuser
 * gos offset correction (user): range  ±1 [gee], resolution 0.125mgee
 */
#define REG_IPREG_SYS2_REG_40_ACCEL_Z_OFFUSER_POS      0x00
#define REG_IPREG_SYS2_REG_40_ACCEL_Z_OFFUSER_MASK     0xff



/*
 * REG_IPREG_SYS2_REG_41
 * Register Name : IPREG_SYS2_REG_41
 */

/*
 * accel_z_offuser
 * gos offset correction (user): range  ±1 [gee], resolution 0.125mgee
 */
#define REG_IPREG_SYS2_REG_41_ACCEL_Z_OFFUSER_POS      0x00
#define REG_IPREG_SYS2_REG_41_ACCEL_Z_OFFUSER_MASK     0x3f



/*
 * REG_IPREG_SYS2_REG_123
 * Register Name : IPREG_SYS2_REG_123
 */

/*
 * accel_src_ctrl
 * SRC CTRL: 0x0: S4S and FIR filter off, 0x1: S4S off and FIR filter on, 0x2: S4S on and FIR filter on, 0x3: reserved (debug mode).
 */
#define REG_IPREG_SYS2_REG_123_ACCEL_SRC_CTRL_POS      0x00
#define REG_IPREG_SYS2_REG_123_ACCEL_SRC_CTRL_MASK     0x03

/*
 * REG_IPREG_SYS2_REG_129
 * Register Name : IPREG_SYS2_REG_129
 */

/*
 * accel_lp_avg_sel
 * Accel Low Power Mode Average Selection
 * 0:1  1:2   2:4   3:5  4:7   5:8  6:10  7:11  8:16  9:18  10:20  11:32  12-15: 64
 */
#define REG_IPREG_SYS2_REG_129_ACCEL_LP_AVG_SEL_POS      0x00
#define REG_IPREG_SYS2_REG_129_ACCEL_LP_AVG_SEL_MASK     0x0f

/*
 * accel_ois_hpfbw_sel
 * OIS HPF for XL;
 * 0: bypass; 1: Reserved; 2:250mHz; 3:62mHz; 4:16mHz
 */
#define REG_IPREG_SYS2_REG_129_ACCEL_OIS_HPFBW_SEL_POS      0x04
#define REG_IPREG_SYS2_REG_129_ACCEL_OIS_HPFBW_SEL_MASK     (0x07 << REG_IPREG_SYS2_REG_129_ACCEL_OIS_HPFBW_SEL_POS)



/*
 * REG_IPREG_SYS2_REG_130
 * Register Name : IPREG_SYS2_REG_130
 */

/*
 * accel_ois_lpf1bw_sel
 * selects XL OIS1 low pass cut-off
 * 0: bypass; 1: 1100; 2:900, 3:600; 4:285; 5:139; 6,7:65 [Hz]
 */
#define REG_IPREG_SYS2_REG_130_ACCEL_OIS_LPF1BW_SEL_POS      0x00
#define REG_IPREG_SYS2_REG_130_ACCEL_OIS_LPF1BW_SEL_MASK     0x07

/*
 * accel_ois_lpf2bw_sel
 * selects XL OIS2 low pass cut-off
 * 0: bypass; 1: 1100; 2:900, 3:600; 4:285; 5:139; 6,7:65 [Hz]
 */
#define REG_IPREG_SYS2_REG_130_ACCEL_OIS_LPF2BW_SEL_POS      0x03
#define REG_IPREG_SYS2_REG_130_ACCEL_OIS_LPF2BW_SEL_MASK     (0x07 << REG_IPREG_SYS2_REG_130_ACCEL_OIS_LPF2BW_SEL_POS)



/*
 * REG_IPREG_SYS2_REG_131
 * Register Name : IPREG_SYS2_REG_131
 */

/*
 * accel_ui_lpfbw_sel
 * Selects UI path low pass cut-off
 * 0:bypass; 1: ODR/4 2: ODR/8 3:ODR/16 4:ODR/32 5:ODR/64 6,7:ODR/128
 */
#define REG_IPREG_SYS2_REG_131_ACCEL_UI_LPFBW_SEL_POS      0x00
#define REG_IPREG_SYS2_REG_131_ACCEL_UI_LPFBW_SEL_MASK     0x07

/*
 * REG_IPREG_SYS2_REG_132
 * Register Name : IPREG_SYS2_REG_132
 */

/*
 * accel_ois_hpf1_byp
 * 1: bypasses HPF for XL OIS1 path
 */
#define REG_IPREG_SYS2_REG_132_ACCEL_OIS_HPF1_BYP_POS      0x00
#define REG_IPREG_SYS2_REG_132_ACCEL_OIS_HPF1_BYP_MASK     0x01

/*
 * accel_ois_hpf2_byp
 * 1: bypasses HPF for XL OIS2 path
 */
#define REG_IPREG_SYS2_REG_132_ACCEL_OIS_HPF2_BYP_POS      0x01
#define REG_IPREG_SYS2_REG_132_ACCEL_OIS_HPF2_BYP_MASK     (0x01 << REG_IPREG_SYS2_REG_132_ACCEL_OIS_HPF2_BYP_POS)

/*
 * accel_ois_m6_byp
 * 0: ois notch enabled; 1: ois notch disabled (XL OIS)
 */
#define REG_IPREG_SYS2_REG_132_ACCEL_OIS_M6_BYP_POS      0x02
#define REG_IPREG_SYS2_REG_132_ACCEL_OIS_M6_BYP_MASK     (0x01 << REG_IPREG_SYS2_REG_132_ACCEL_OIS_M6_BYP_POS)


/* ---------------------------------------------------------------------------
 * register IPREG_TOP1
 * ---------------------------------------------------------------------------*/

/*
 * REG_I2CM_COMMAND_0
 * Register Name : I2CM_COMMAND_0
 */

/*
 * burstlen_0
 * Specifies the burst length of  I2C communication with the external slavedevice.
 *     For a read operation to the external device, the max burst length is 15-byte.
 *     For a write operation to the external device, the max burst length is 6-byte.
 *       0000: reserved.
 *       0001: burst length = 1 byte.
 *       0010: burst length = 2 bytes.
 *       …
 *       1111: burst length = 15 bytes.
 */
#define REG_I2CM_COMMAND_0_BURSTLEN_0_POS      0x00
#define REG_I2CM_COMMAND_0_BURSTLEN_0_MASK     0x0f

/*
 * r_w_0
 * I2C master read/write command.
 *
 * 00: Write operation
 * 01: Read operation with register address specified
 * 10: Read operation without register address specified
 * 11: Reserved
 */
#define REG_I2CM_COMMAND_0_R_W_0_POS      0x04
#define REG_I2CM_COMMAND_0_R_W_0_MASK     (0x03 << REG_I2CM_COMMAND_0_R_W_0_POS)

/*
 * ch_sel_0
 * Specifies the channel number for I2C master transaction.
 * Two external sensors are supported.
 * 0: specify one external sensor with the device ID1
 * 1: specify the other external sensor with the device ID2.
 * The ID1 and ID2 should be replaced by the real device ID numbers of the chosen external devices.
 */
#define REG_I2CM_COMMAND_0_CH_SEL_0_POS      0x06
#define REG_I2CM_COMMAND_0_CH_SEL_0_MASK     (0x01 << REG_I2CM_COMMAND_0_CH_SEL_0_POS)

/*
 * endflag_0
 * Indicate if the current entry is the last I2C communication with the external slave device.
 */
#define REG_I2CM_COMMAND_0_ENDFLAG_0_POS      0x07
#define REG_I2CM_COMMAND_0_ENDFLAG_0_MASK     (0x01 << REG_I2CM_COMMAND_0_ENDFLAG_0_POS)



/*
 * REG_I2CM_COMMAND_1
 * Register Name : I2CM_COMMAND_1
 */

/*
 * burstlen_1
 * Specifies the burst length of  I2C communication with the external slavedevice.
 *     For a read operation to the external device, the max burst length is 15-byte.
 *     For a write operation to the external device, the max burst length is 6-byte.
 *       0000: reserved.
 *       0001: burst length = 1 byte.
 *       0010: burst length = 2 bytes.
 *       …
 *       1111: burst length = 15 bytes.
 */
#define REG_I2CM_COMMAND_1_BURSTLEN_1_POS      0x00
#define REG_I2CM_COMMAND_1_BURSTLEN_1_MASK     0x0f

/*
 * r_w_1
 * I2C master read/write command.
 *
 * 00: Write operation
 * 01: Read operation with register address specified
 * 10: Read operation without register address specified
 * 11: Reserved
 */
#define REG_I2CM_COMMAND_1_R_W_1_POS      0x04
#define REG_I2CM_COMMAND_1_R_W_1_MASK     (0x03 << REG_I2CM_COMMAND_1_R_W_1_POS)

/*
 * ch_sel_1
 * Specifies the channel number for I2C master transaction.
 * Two external sensors are supported.
 * 0: specify one external sensor with the device ID1
 * 1: specify the other external sensor with the device ID2.
 * The ID1 and ID2 should be replaced by the real device ID numbers of the chosen external devices.
 */
#define REG_I2CM_COMMAND_1_CH_SEL_1_POS      0x06
#define REG_I2CM_COMMAND_1_CH_SEL_1_MASK     (0x01 << REG_I2CM_COMMAND_1_CH_SEL_1_POS)

/*
 * endflag_1
 * Indicate if the current entry is the last I2C communication with the external slave device.
 */
#define REG_I2CM_COMMAND_1_ENDFLAG_1_POS      0x07
#define REG_I2CM_COMMAND_1_ENDFLAG_1_MASK     (0x01 << REG_I2CM_COMMAND_1_ENDFLAG_1_POS)



/*
 * REG_I2CM_COMMAND_2
 * Register Name : I2CM_COMMAND_2
 */

/*
 * burstlen_2
 * Specifies the burst length of  I2C communication with the external slavedevice.
 *     For a read operation to the external device, the max burst length is 15-byte.
 *     For a write operation to the external device, the max burst length is 6-byte.
 *       0000: reserved.
 *       0001: burst length = 1 byte.
 *       0010: burst length = 2 bytes.
 *       …
 *       1111: burst length = 15 bytes.
 */
#define REG_I2CM_COMMAND_2_BURSTLEN_2_POS      0x00
#define REG_I2CM_COMMAND_2_BURSTLEN_2_MASK     0x0f

/*
 * r_w_2
 * I2C master read/write command.
 *
 * 00: Write operation
 * 01: Read operation with register address specified
 * 10: Read operation without register address specified
 * 11: Reserved
 */
#define REG_I2CM_COMMAND_2_R_W_2_POS      0x04
#define REG_I2CM_COMMAND_2_R_W_2_MASK     (0x03 << REG_I2CM_COMMAND_2_R_W_2_POS)

/*
 * ch_sel_2
 * Specifies the channel number for I2C master transaction.
 * Two external sensors are supported.
 * 0: specify one external sensor with the device ID1
 * 1: specify the other external sensor with the device ID2.
 * The ID1 and ID2 should be replaced by the real device ID numbers of the chosen external devices.
 */
#define REG_I2CM_COMMAND_2_CH_SEL_2_POS      0x06
#define REG_I2CM_COMMAND_2_CH_SEL_2_MASK     (0x01 << REG_I2CM_COMMAND_2_CH_SEL_2_POS)

/*
 * endflag_2
 * Indicate if the current entry is the last I2C communication with the external slave device.
 */
#define REG_I2CM_COMMAND_2_ENDFLAG_2_POS      0x07
#define REG_I2CM_COMMAND_2_ENDFLAG_2_MASK     (0x01 << REG_I2CM_COMMAND_2_ENDFLAG_2_POS)



/*
 * REG_I2CM_COMMAND_3
 * Register Name : I2CM_COMMAND_3
 */

/*
 * burstlen_3
 * Specifies the burst length of  I2C communication with the external slavedevice.
 *     For a read operation to the external device, the max burst length is 15-byte.
 *     For a write operation to the external device, the max burst length is 6-byte.
 *       0000: reserved.
 *       0001: burst length = 1 byte.
 *       0010: burst length = 2 bytes.
 *       …
 *       1111: burst length = 15 bytes.
 */
#define REG_I2CM_COMMAND_3_BURSTLEN_3_POS      0x00
#define REG_I2CM_COMMAND_3_BURSTLEN_3_MASK     0x0f

/*
 * r_w_3
 * I2C master read/write command.
 *
 * 00: Write operation
 * 01: Read operation with register address specified
 * 10: Read operation without register address specified
 * 11: Reserved
 */
#define REG_I2CM_COMMAND_3_R_W_3_POS      0x04
#define REG_I2CM_COMMAND_3_R_W_3_MASK     (0x03 << REG_I2CM_COMMAND_3_R_W_3_POS)

/*
 * ch_sel_3
 * Specifies the channel number for I2C master transaction.
 * Two external sensors are supported.
 * 0: specify one external sensor with the device ID1
 * 1: specify the other external sensor with the device ID2.
 * The ID1 and ID2 should be replaced by the real device ID numbers of the chosen external devices.
 */
#define REG_I2CM_COMMAND_3_CH_SEL_3_POS      0x06
#define REG_I2CM_COMMAND_3_CH_SEL_3_MASK     (0x01 << REG_I2CM_COMMAND_3_CH_SEL_3_POS)

/*
 * endflag_3
 * Indicate if the current entry is the last I2C communication with the external slave device.
 */
#define REG_I2CM_COMMAND_3_ENDFLAG_3_POS      0x07
#define REG_I2CM_COMMAND_3_ENDFLAG_3_MASK     (0x01 << REG_I2CM_COMMAND_3_ENDFLAG_3_POS)



/*
 * REG_I2CM_DEV_PROFILE0
 * Register Name : I2CM_DEV_PROFILE0
 */

/*
 * rd_address_0
 * Specifies the read address for the channel 0 I2C transaction
 */
#define REG_I2CM_DEV_PROFILE0_RD_ADDRESS_0_POS      0x00
#define REG_I2CM_DEV_PROFILE0_RD_ADDRESS_0_MASK     0xff



/*
 * REG_I2CM_DEV_PROFILE1
 * Register Name : I2CM_DEV_PROFILE1
 */

/*
 * dev_id_0
 * Specifies the slave ID for the channel 0 I2C transaction
 */
#define REG_I2CM_DEV_PROFILE1_DEV_ID_0_POS      0x00
#define REG_I2CM_DEV_PROFILE1_DEV_ID_0_MASK     0x7f



/*
 * REG_I2CM_DEV_PROFILE2
 * Register Name : I2CM_DEV_PROFILE2
 */

/*
 * rd_address_1
 * Specifies the read address for the channel 1 I2C transaction
 */
#define REG_I2CM_DEV_PROFILE2_RD_ADDRESS_1_POS      0x00
#define REG_I2CM_DEV_PROFILE2_RD_ADDRESS_1_MASK     0xff



/*
 * REG_I2CM_DEV_PROFILE3
 * Register Name : I2CM_DEV_PROFILE3
 */

/*
 * dev_id_1
 * Specifies the slave ID for the channel 1 I2C transaction
 */
#define REG_I2CM_DEV_PROFILE3_DEV_ID_1_POS      0x00
#define REG_I2CM_DEV_PROFILE3_DEV_ID_1_MASK     0x7f



/*
 * REG_I2CM_CONTROL
 * Register Name : I2CM_CONTROL
 */

/*
 * i2cm_go
 * 1  : kick off i2c operation.
 * Hardware clears this bit to 0 after i2c operation is done.
 * This bit is not programmable by MCU when i2cm_busy = 1.
 * This bit is not programmable by MCU if reg_aux_pin_configuration != 2’b01.
 */
#define REG_I2CM_CONTROL_I2CM_GO_POS      0x00
#define REG_I2CM_CONTROL_I2CM_GO_MASK     0x01

/*
 * i2cm_speed
 * 1: I2C Standard Mode, 0: I2C Fast Mode. Default is 0.  This bit is not programmable by MCU when i2cm_busy = 1.
 */
#define REG_I2CM_CONTROL_I2CM_SPEED_POS      0x03
#define REG_I2CM_CONTROL_I2CM_SPEED_MASK     (0x01 << REG_I2CM_CONTROL_I2CM_SPEED_POS)
/*
 * i2cm_restart_en
 *  0x0: No reSTART is used.
 *  0x1:  if R/W=1, the reSTART is used to bridge the register-address write transaction and register-data read transaction.
 *
 *  This bit is not programmable by MCU when i2cm_busy = 1.
 */
#define REG_I2CM_CONTROL_I2CM_RESTART_EN_POS      0x06
#define REG_I2CM_CONTROL_I2CM_RESTART_EN_MASK     (0x01 << REG_I2CM_CONTROL_I2CM_RESTART_EN_POS)

/*
 * REG_I2CM_STATUS
 * Register Name : I2CM_STATUS
 */

/*
 * i2cm_busy
 * 1: i2c operation is running. 0: no i2c operation is running.
 */
#define REG_I2CM_STATUS_I2CM_BUSY_POS      0x00
#define REG_I2CM_STATUS_I2CM_BUSY_MASK     0x01

/*
 * i2cm_done
 * 1: when i2c operation completes, with or without errors. This bit is cleared due to (a) MCU read or (b) when i2c_go is programmed to 1 c) ext_ODR is asserted
 */
#define REG_I2CM_STATUS_I2CM_DONE_POS      0x01
#define REG_I2CM_STATUS_I2CM_DONE_MASK     (0x01 << REG_I2CM_STATUS_I2CM_DONE_POS)

/*
 * i2cm_timeout_err
 * 1: if slave holds SDA low > 32 ms  This bit is cleared due to (a) MCU read or (b) when i2c_go is programmed to 1. c) ext_ODR is asserted .
 */
#define REG_I2CM_STATUS_I2CM_TIMEOUT_ERR_POS      0x02
#define REG_I2CM_STATUS_I2CM_TIMEOUT_ERR_MASK     (0x01 << REG_I2CM_STATUS_I2CM_TIMEOUT_ERR_POS)

/*
 * i2cm_srst_err
 * 1: if current i2c operation is terminated by MCU using i2cm_fsm_srst. This bit is cleared due to (a) MCU read or (b) when i2c_go is programmed to 1.  c) ext_ODR is asserted
 */
#define REG_I2CM_STATUS_I2CM_SRST_ERR_POS      0x03
#define REG_I2CM_STATUS_I2CM_SRST_ERR_MASK     (0x01 << REG_I2CM_STATUS_I2CM_SRST_ERR_POS)

/*
 * i2cm_scl_err
 * 1: if SCL is driven low by external device when I2CM tries to drives SCL from high to low.                   I2CM expects SCL is high before driving it to low, but SCL is low already before driven by I2CM. If the SCL is low at the time when i2cm_go is programmed to 1, I2CM waits for SCL is released (to 1) and then starts the I2C communication, and i2cm_scl_err  is not set. If the error occurs in the middle of a live I2C communication, I2CM terminates the current I2C communication without giving out I2C/STOP event, and i2cm_scl_err  is set.
 */
#define REG_I2CM_STATUS_I2CM_SCL_ERR_POS      0x04
#define REG_I2CM_STATUS_I2CM_SCL_ERR_MASK     (0x01 << REG_I2CM_STATUS_I2CM_SCL_ERR_POS)

/*
 * i2cm_sda_err
 * 1: if SDA is driven low by external device when I2CM has the ownership driving SDA line. During the time when I2CM owns SDA line and I2CM keeps SDA at high, but it is driven to low by external. If SDA is low at the time when i2cm_go is programmed to 1, I2CM waits for SDA is released (to 1) and then starts the I2C communication, and i2cm_sda_err is not set. If the error occurs in the middle of a live I2C communication, I2CM terminates the current I2C communication without giving out I2C/STOP event, and i2cm_sda_err is set.
 * This bit is cleared due to (a) MCU read or (b) when i2c_go is programmed to 1. c) ext_ODR is asserted
 */
#define REG_I2CM_STATUS_I2CM_SDA_ERR_POS      0x05
#define REG_I2CM_STATUS_I2CM_SDA_ERR_MASK     (0x01 << REG_I2CM_STATUS_I2CM_SDA_ERR_POS)



/*
 * REG_I2CM_EXT_DEV_STATUS
 * Register Name : I2CM_EXT_DEV_STATUS
 */

/*
 * i2cm_ext_dev_status
 * To indicate the ACK/NACK feedback from the external device per each entry of the command buffer. The i2cm_ext_dev_status[3:0] is set to 0xF whenever I2CM operation is kicked off.
 *
 * [0]: ACK/NACK feedback from the external device to the I2CM_COMMAND_0.
 *        0: ACK
 *        1: NACK
 * [1]: ACK/NACK feedback from the external device to the I2CM_COMMAND_1.
 *        0: ACK
 *        1: NACK
 * [2]: ACK/NACK feedback from the external device to the I2CM_COMMAND_2.
 *        0: ACK
 *        1: NACK
 * [3]: ACK/NACK feedback from the external device to the I2CM_COMMAND_3.
 *        0: ACK
 *        1: NACK
 */
#define REG_I2CM_EXT_DEV_STATUS_I2CM_EXT_DEV_STATUS_POS      0x00
#define REG_I2CM_EXT_DEV_STATUS_I2CM_EXT_DEV_STATUS_MASK     0x0f



/*
 * REG_I2CM_RD_DATA0
 * Register Name : I2CM_RD_DATA0
 */

/*
 * i2cm_rd_data0
 * The first  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA0_I2CM_RD_DATA0_POS      0x00
#define REG_I2CM_RD_DATA0_I2CM_RD_DATA0_MASK     0xff



/*
 * REG_I2CM_RD_DATA1
 * Register Name : I2CM_RD_DATA1
 */

/*
 * i2cm_rd_data1
 * The 2nd  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA1_I2CM_RD_DATA1_POS      0x00
#define REG_I2CM_RD_DATA1_I2CM_RD_DATA1_MASK     0xff



/*
 * REG_I2CM_RD_DATA2
 * Register Name : I2CM_RD_DATA2
 */

/*
 * i2cm_rd_data2
 * The 3nd  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA2_I2CM_RD_DATA2_POS      0x00
#define REG_I2CM_RD_DATA2_I2CM_RD_DATA2_MASK     0xff



/*
 * REG_I2CM_RD_DATA3
 * Register Name : I2CM_RD_DATA3
 */

/*
 * i2cm_rd_data3
 * The 4th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA3_I2CM_RD_DATA3_POS      0x00
#define REG_I2CM_RD_DATA3_I2CM_RD_DATA3_MASK     0xff



/*
 * REG_I2CM_RD_DATA4
 * Register Name : I2CM_RD_DATA4
 */

/*
 * i2cm_rd_data4
 * The 5th byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA4_I2CM_RD_DATA4_POS      0x00
#define REG_I2CM_RD_DATA4_I2CM_RD_DATA4_MASK     0xff



/*
 * REG_I2CM_RD_DATA5
 * Register Name : I2CM_RD_DATA5
 */

/*
 * i2cm_rd_data5
 * The 6th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA5_I2CM_RD_DATA5_POS      0x00
#define REG_I2CM_RD_DATA5_I2CM_RD_DATA5_MASK     0xff



/*
 * REG_I2CM_RD_DATA6
 * Register Name : I2CM_RD_DATA6
 */

/*
 * i2cm_rd_data6
 * The 7th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA6_I2CM_RD_DATA6_POS      0x00
#define REG_I2CM_RD_DATA6_I2CM_RD_DATA6_MASK     0xff



/*
 * REG_I2CM_RD_DATA7
 * Register Name : I2CM_RD_DATA7
 */

/*
 * i2cm_rd_data7
 * The 8th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA7_I2CM_RD_DATA7_POS      0x00
#define REG_I2CM_RD_DATA7_I2CM_RD_DATA7_MASK     0xff



/*
 * REG_I2CM_RD_DATA8
 * Register Name : I2CM_RD_DATA8
 */

/*
 * i2cm_rd_data8
 * The 9th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA8_I2CM_RD_DATA8_POS      0x00
#define REG_I2CM_RD_DATA8_I2CM_RD_DATA8_MASK     0xff



/*
 * REG_I2CM_RD_DATA9
 * Register Name : I2CM_RD_DATA9
 */

/*
 * i2cm_rd_data9
 * The 10th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA9_I2CM_RD_DATA9_POS      0x00
#define REG_I2CM_RD_DATA9_I2CM_RD_DATA9_MASK     0xff



/*
 * REG_I2CM_RD_DATA10
 * Register Name : I2CM_RD_DATA10
 */

/*
 * i2cm_rd_data10
 * The 11th byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA10_I2CM_RD_DATA10_POS      0x00
#define REG_I2CM_RD_DATA10_I2CM_RD_DATA10_MASK     0xff



/*
 * REG_I2CM_RD_DATA11
 * Register Name : I2CM_RD_DATA11
 */

/*
 * i2cm_rd_data11
 * The 12th byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA11_I2CM_RD_DATA11_POS      0x00
#define REG_I2CM_RD_DATA11_I2CM_RD_DATA11_MASK     0xff



/*
 * REG_I2CM_RD_DATA12
 * Register Name : I2CM_RD_DATA12
 */

/*
 * i2cm_rd_data12
 * The 13th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA12_I2CM_RD_DATA12_POS      0x00
#define REG_I2CM_RD_DATA12_I2CM_RD_DATA12_MASK     0xff



/*
 * REG_I2CM_RD_DATA13
 * Register Name : I2CM_RD_DATA13
 */

/*
 * i2cm_rd_data13
 * The 14th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertionof a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA13_I2CM_RD_DATA13_POS      0x00
#define REG_I2CM_RD_DATA13_I2CM_RD_DATA13_MASK     0xff



/*
 * REG_I2CM_RD_DATA14
 * Register Name : I2CM_RD_DATA14
 */

/*
 * i2cm_rd_data14
 * The 15th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA14_I2CM_RD_DATA14_POS      0x00
#define REG_I2CM_RD_DATA14_I2CM_RD_DATA14_MASK     0xff



/*
 * REG_I2CM_RD_DATA15
 * Register Name : I2CM_RD_DATA15
 */

/*
 * i2cm_rd_data15
 * The 16th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA15_I2CM_RD_DATA15_POS      0x00
#define REG_I2CM_RD_DATA15_I2CM_RD_DATA15_MASK     0xff



/*
 * REG_I2CM_RD_DATA16
 * Register Name : I2CM_RD_DATA16
 */

/*
 * i2cm_rd_data16
 * The 17th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA16_I2CM_RD_DATA16_POS      0x00
#define REG_I2CM_RD_DATA16_I2CM_RD_DATA16_MASK     0xff



/*
 * REG_I2CM_RD_DATA17
 * Register Name : I2CM_RD_DATA17
 */

/*
 * i2cm_rd_data17
 * The 18th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA17_I2CM_RD_DATA17_POS      0x00
#define REG_I2CM_RD_DATA17_I2CM_RD_DATA17_MASK     0xff



/*
 * REG_I2CM_RD_DATA18
 * Register Name : I2CM_RD_DATA18
 */

/*
 * i2cm_rd_data18
 * The 19th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA18_I2CM_RD_DATA18_POS      0x00
#define REG_I2CM_RD_DATA18_I2CM_RD_DATA18_MASK     0xff



/*
 * REG_I2CM_RD_DATA19
 * Register Name : I2CM_RD_DATA19
 */

/*
 * i2cm_rd_data19
 * The 20th  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA19_I2CM_RD_DATA19_POS      0x00
#define REG_I2CM_RD_DATA19_I2CM_RD_DATA19_MASK     0xff



/*
 * REG_I2CM_RD_DATA20
 * Register Name : I2CM_RD_DATA20
 */

/*
 * i2cm_rd_data20
 * The 21 st  byte received from i2c slave.   Contents of this register is automatically cleared to 0 when i2cm_go = 1  or  ext_ODR assertion of a read operation (not write operation).
 */
#define REG_I2CM_RD_DATA20_I2CM_RD_DATA20_POS      0x00
#define REG_I2CM_RD_DATA20_I2CM_RD_DATA20_MASK     0xff



/*
 * REG_I2CM_WR_DATA0
 * Register Name : I2CM_WR_DATA0
 */

/*
 * i2cm_wr_data0
 * The data/address byte for a Write transaction
 */
#define REG_I2CM_WR_DATA0_I2CM_WR_DATA0_POS      0x00
#define REG_I2CM_WR_DATA0_I2CM_WR_DATA0_MASK     0xff



/*
 * REG_I2CM_WR_DATA1
 * Register Name : I2CM_WR_DATA1
 */

/*
 * i2cm_wr_data1
 * The data/address byte for a Write transaction
 */
#define REG_I2CM_WR_DATA1_I2CM_WR_DATA1_POS      0x00
#define REG_I2CM_WR_DATA1_I2CM_WR_DATA1_MASK     0xff



/*
 * REG_I2CM_WR_DATA2
 * Register Name : I2CM_WR_DATA2
 */

/*
 * i2cm_wr_data2
 * The data/address byte for a Write transaction
 */
#define REG_I2CM_WR_DATA2_I2CM_WR_DATA2_POS      0x00
#define REG_I2CM_WR_DATA2_I2CM_WR_DATA2_MASK     0xff



/*
 * REG_I2CM_WR_DATA3
 * Register Name : I2CM_WR_DATA3
 */

/*
 * i2cm_wr_data3
 * The data/address byte for a Write transaction
 */
#define REG_I2CM_WR_DATA3_I2CM_WR_DATA3_POS      0x00
#define REG_I2CM_WR_DATA3_I2CM_WR_DATA3_MASK     0xff



/*
 * REG_I2CM_WR_DATA4
 * Register Name : I2CM_WR_DATA4
 */

/*
 * i2cm_wr_data4
 * The data/address byte for a Write transaction
 */
#define REG_I2CM_WR_DATA4_I2CM_WR_DATA4_POS      0x00
#define REG_I2CM_WR_DATA4_I2CM_WR_DATA4_MASK     0xff



/*
 * REG_I2CM_WR_DATA5
 * Register Name : I2CM_WR_DATA5
 */

/*
 * i2cm_wr_data5
 * The data/address byte for a Write transaction
 */
#define REG_I2CM_WR_DATA5_I2CM_WR_DATA5_POS      0x00
#define REG_I2CM_WR_DATA5_I2CM_WR_DATA5_MASK     0xff



/*
 * REG_SIFS_IXC_ERROR_STATUS
 * Register Name : SIFS_IXC_ERROR_STATUS
 */

/*
 * sifs_ixc_timeout_err
 * [Supports Dynamic Change] 1: indicates that an IxC timeout error occurred in SIFS. No clock toggle condition from host for 32 ms while an IxC transaction was ongoing(after START and before STOP).
 * 0: no timeout error or when SPI slave is selected for serial transfers.
 */
#define REG_SIFS_IXC_ERROR_STATUS_SIFS_IXC_TIMEOUT_ERR_POS      0x00
#define REG_SIFS_IXC_ERROR_STATUS_SIFS_IXC_TIMEOUT_ERR_MASK     0x01

/*
 * aux1_sifs_ixc_timeout_err
 * [Supports Dynamic Change] 1: indicates that an IxC timeout error occurred in AUX1 SIFS. No clock toggle condition from host for 32 ms while an IxC transaction was ongoing(after START and before STOP).
 * 0: no timeout error or when SPI slave is selected for serial transfers.
 */
#define REG_SIFS_IXC_ERROR_STATUS_AUX1_SIFS_IXC_TIMEOUT_ERR_POS      0x01
#define REG_SIFS_IXC_ERROR_STATUS_AUX1_SIFS_IXC_TIMEOUT_ERR_MASK     (0x01 << REG_SIFS_IXC_ERROR_STATUS_AUX1_SIFS_IXC_TIMEOUT_ERR_POS)



/*
 * REG_EDMP_PRGRM_IRQ0_0
 * Register Name : EDMP_PRGRM_IRQ0_0
 */

/*
 * prgrm_strt_addr_irq_0
 * [Supports Dynamic Change] start address of IRQ_0 vector
 */
#define REG_EDMP_PRGRM_IRQ0_0_PRGRM_STRT_ADDR_IRQ_0_POS      0x00
#define REG_EDMP_PRGRM_IRQ0_0_PRGRM_STRT_ADDR_IRQ_0_MASK     0xff



/*
 * REG_EDMP_PRGRM_IRQ0_1
 * Register Name : EDMP_PRGRM_IRQ0_1
 */

/*
 * prgrm_strt_addr_irq_0
 * [Supports Dynamic Change] start address of IRQ_0 vector
 */
#define REG_EDMP_PRGRM_IRQ0_1_PRGRM_STRT_ADDR_IRQ_0_POS      0x00
#define REG_EDMP_PRGRM_IRQ0_1_PRGRM_STRT_ADDR_IRQ_0_MASK     0xff



/*
 * REG_EDMP_PRGRM_IRQ1_0
 * Register Name : EDMP_PRGRM_IRQ1_0
 */

/*
 * prgrm_strt_addr_irq_1
 * [Supports Dynamic Change] start address of IRQ_1 vector
 */
#define REG_EDMP_PRGRM_IRQ1_0_PRGRM_STRT_ADDR_IRQ_1_POS      0x00
#define REG_EDMP_PRGRM_IRQ1_0_PRGRM_STRT_ADDR_IRQ_1_MASK     0xff



/*
 * REG_EDMP_PRGRM_IRQ1_1
 * Register Name : EDMP_PRGRM_IRQ1_1
 */

/*
 * prgrm_strt_addr_irq_1
 * [Supports Dynamic Change] start address of IRQ_1 vector
 */
#define REG_EDMP_PRGRM_IRQ1_1_PRGRM_STRT_ADDR_IRQ_1_POS      0x00
#define REG_EDMP_PRGRM_IRQ1_1_PRGRM_STRT_ADDR_IRQ_1_MASK     0xff



/*
 * REG_EDMP_PRGRM_IRQ2_0
 * Register Name : EDMP_PRGRM_IRQ2_0
 */

/*
 * prgrm_strt_addr_irq_2
 * [Supports Dynamic Change] start address of IRQ_2 vector
 */
#define REG_EDMP_PRGRM_IRQ2_0_PRGRM_STRT_ADDR_IRQ_2_POS      0x00
#define REG_EDMP_PRGRM_IRQ2_0_PRGRM_STRT_ADDR_IRQ_2_MASK     0xff



/*
 * REG_EDMP_PRGRM_IRQ2_1
 * Register Name : EDMP_PRGRM_IRQ2_1
 */

/*
 * prgrm_strt_addr_irq_2
 * [Supports Dynamic Change] start address of IRQ_2 vector
 */
#define REG_EDMP_PRGRM_IRQ2_1_PRGRM_STRT_ADDR_IRQ_2_POS      0x00
#define REG_EDMP_PRGRM_IRQ2_1_PRGRM_STRT_ADDR_IRQ_2_MASK     0xff



/*
 * REG_EDMP_SP_START_ADDR
 * Register Name : EDMP_SP_START_ADDR
 */

/*
 * edmp_sp_start_addr
 * [Supports Dynamic Change] bit [15:8] of AHB address of SRAM allocated for DMP stack
 */
#define REG_EDMP_SP_START_ADDR_EDMP_SP_START_ADDR_POS      0x00
#define REG_EDMP_SP_START_ADDR_EDMP_SP_START_ADDR_MASK     0xff



/*
 * REG_SMC_CONTROL_0
 * Register Name : SMC_CONTROL_0
 */

/*
 * tmst_en
 * Time Stamp register Enable
 */
#define REG_SMC_CONTROL_0_TMST_EN_POS      0x00
#define REG_SMC_CONTROL_0_TMST_EN_MASK     0x01

/*
 * tmst_fsync_en
 * Time Stamp register Fsync Enable . When set to 1, the contents of the Timestamp feature of  FSYNC  is enabled.
 */
#define REG_SMC_CONTROL_0_TMST_FSYNC_EN_POS      0x01
#define REG_SMC_CONTROL_0_TMST_FSYNC_EN_MASK     (0x01 << REG_SMC_CONTROL_0_TMST_FSYNC_EN_POS)

/*
 * tmst_force_aux_fine_en
 * If 1 forces Time Stamp fine counting also on OIS/AUX interfaces. Otherwise, if 0, Time Stamp fine counting is enabled only on UI/AP interfaces.
 */
#define REG_SMC_CONTROL_0_TMST_FORCE_AUX_FINE_EN_POS      0x02
#define REG_SMC_CONTROL_0_TMST_FORCE_AUX_FINE_EN_MASK     (0x01 << REG_SMC_CONTROL_0_TMST_FORCE_AUX_FINE_EN_POS)

/*
 * temp_dis
 * This bit disables the temp sensor analog IP
 */
#define REG_SMC_CONTROL_0_TEMP_DIS_POS      0x03
#define REG_SMC_CONTROL_0_TEMP_DIS_MASK     (0x01 << REG_SMC_CONTROL_0_TEMP_DIS_POS)

/*
 * accel_lp_clk_sel
 * [Supports Dynamic Change] This bit is applicable to the AP side's operation. This bit is effective when AP is in accel-only operation with AP/accel mode = LP.
 * (a) accel_lp_clk_sel = 1, the AP sensor operation is in ALP mode.
 * (b) accel_lp_clk_sel = 0, the AP sensor operation is in AULP mode.
 *
 * When the I3C Synchronous timing control function is enabled on the AP side, the accel_lp_clk_sel must be at a value of 1. When the I3C Synchronous timing control function is enabled, the chip supports AULP mode operation, but the power consumption is at the ALP level.
 */
#define REG_SMC_CONTROL_0_ACCEL_LP_CLK_SEL_POS      0x04
#define REG_SMC_CONTROL_0_ACCEL_LP_CLK_SEL_MASK     (0x01 << REG_SMC_CONTROL_0_ACCEL_LP_CLK_SEL_POS)

/*
 * REG_SMC_CONTROL_1
 * Register Name : SMC_CONTROL_1
 */

/*
 * sreg_aux_accel_only_en
 * 0: SREG does not support the sensor data register read from the AUX1 and AUX2 hosts if the gyro sensor is not enabled.   All the clocks to the synchronizers related to AUX1 and AUX2 host interface should be off completely to save power.
 *
 * 1: SREG supports the sensor data register read from the AUX1 and AUX2 host if the gyro sensor is not enabled.
 */
#define REG_SMC_CONTROL_1_SREG_AUX_ACCEL_ONLY_EN_POS      0x03
#define REG_SMC_CONTROL_1_SREG_AUX_ACCEL_ONLY_EN_MASK     (0x01 << REG_SMC_CONTROL_1_SREG_AUX_ACCEL_ONLY_EN_POS)



/*
 * REG_STC_CONFIG
 * Register Name : STC_CONFIG
 */

/*
 * stc_sensor_sel
 * [Supports Dynamic Change] 00,01: slowest ODR, 10: accel, 11: gyro
 */
#define REG_STC_CONFIG_STC_SENSOR_SEL_POS      0x02
#define REG_STC_CONFIG_STC_SENSOR_SEL_MASK     (0x03 << REG_STC_CONFIG_STC_SENSOR_SEL_POS)



/*
 * REG_SREG_CTRL
 * Register Name : SREG_CTRL
 */

/*
 * sreg_data_endian_sel
 * Select the endianess of the Sensor Data Registers and FIFO data
 * 0 : data to Sensor Registers and FIFO are in Little Endian format
 * 1 : data to Sensor Registers and FIFO are in Big Endian format
 */
#define REG_SREG_CTRL_SREG_DATA_ENDIAN_SEL_POS      0x01
#define REG_SREG_CTRL_SREG_DATA_ENDIAN_SEL_MASK     (0x01 << REG_SREG_CTRL_SREG_DATA_ENDIAN_SEL_POS)

/*
 * REG_SIFS_I3C_STC_CFG
 * Register Name : SIFS_I3C_STC_CFG
 */

/*
 * i3c_stc_mode
 * Enable the STC controller.
 * When set to 0 the parts will deliver ODR events with
 * uncorrected frequency and phase based on internal timebase.
 * When set to 1 the frequency and phase correction loops
 * will be activated.
 * Toggling it will make the correction loops restart as out of POR.
 * STC functionality can be enabled only if accel_lp_clk_sel is set to 1; otherwise device may not behave as expected.
 *
 * To enable STC in POR, otp trim value should be '1'
 */
#define REG_SIFS_I3C_STC_CFG_I3C_STC_MODE_POS      0x02
#define REG_SIFS_I3C_STC_CFG_I3C_STC_MODE_MASK     (0x01 << REG_SIFS_I3C_STC_CFG_I3C_STC_MODE_POS)

/*
 * REG_INT_PULSE_MIN_ON_INTF0
 * Register Name : INT_PULSE_MIN_ON_INTF0
 */

/*
 * int0_tpulse_duration
 * UI/AP Interface: Pulse Min "on" duration, indicates minimum interrupt assertion duration when in pulse mode.
 * 0: Interrupt pulse duration is 100us. Use only if ODR < 4KHz (Default).
 * 1:Interrupt pulse duration is 8us. Required if ODR >= 4KHz, optional for ODR < 4KHz.
 * 2,3,4,5,6,7 are reserved.
 */
#define REG_INT_PULSE_MIN_ON_INTF0_INT0_TPULSE_DURATION_POS      0x00
#define REG_INT_PULSE_MIN_ON_INTF0_INT0_TPULSE_DURATION_MASK     0x07



/*
 * REG_INT_PULSE_MIN_ON_INTF1
 * Register Name : INT_PULSE_MIN_ON_INTF1
 */

/*
 * int1_tpulse_duration
 * UI/AP Interface: Pulse Min "on" duration, indicates minimum interrupt assertion duration when in pulse mode.
 * 0: Interrupt pulse duration is 100us. Use only if ODR < 4KHz (Default).
 * 1:Interrupt pulse duration is 8us. Required if ODR >= 4KHz, optional for ODR < 4KHz.
 * 2,3,4,5,6,7 are reserved.
 */
#define REG_INT_PULSE_MIN_ON_INTF1_INT1_TPULSE_DURATION_POS      0x00
#define REG_INT_PULSE_MIN_ON_INTF1_INT1_TPULSE_DURATION_MASK     0x07



/*
 * REG_INT_PULSE_MIN_OFF_INTF0
 * Register Name : INT_PULSE_MIN_OFF_INTF0
 */

/*
 * int0_tdeassert_disable
 * Interface UI/AP: Min "off" duration, indicates Minimum interrupt de-assertion duration.
 * 0 is 100us [default],
 * 1 is 8us,
 * 2 is: No minimum interrupt de-assertion duration requirement. Two back-to-back interrupt assertions could be separated by at least one MCLK cycle. This option should be only used for MCU and IBI interface only.
 * 3,4,5,6,7 are reserved.
 */
#define REG_INT_PULSE_MIN_OFF_INTF0_INT0_TDEASSERT_DISABLE_POS      0x00
#define REG_INT_PULSE_MIN_OFF_INTF0_INT0_TDEASSERT_DISABLE_MASK     0x07



/*
 * REG_INT_PULSE_MIN_OFF_INTF1
 * Register Name : INT_PULSE_MIN_OFF_INTF1
 */

/*
 * int1_tdeassert_disable
 * Interface UI/AP: Min "off" duration, indicates Minimum interrupt de-assertion duration.
 * 0 is 100us [default],
 * 1 is 8us,
 * 2 is: No minimum interrupt de-assertion duration requirement. Two back-to-back interrupt assertions could be separated by at least one MCLK cycle. This option should be only used for MCU and IBI interface only.
 * 3,4,5,6,7 are reserved.
 */
#define REG_INT_PULSE_MIN_OFF_INTF1_INT1_TDEASSERT_DISABLE_POS      0x00
#define REG_INT_PULSE_MIN_OFF_INTF1_INT1_TDEASSERT_DISABLE_MASK     0x07



/*
 * REG_ISR_0_7
 * Register Name : ISR_0_7
 */

/*
 * int_status_accel_drdy_pin_0
 * For irq0 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of Accel drdy event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_ISR_0_7_INT_STATUS_ACCEL_DRDY_PIN_0_POS      0x00
#define REG_ISR_0_7_INT_STATUS_ACCEL_DRDY_PIN_0_MASK     0x01

/*
 * int_status_ext_odr_drdy_pin_0
 * For irq0 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of ext ODR drdy event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_ISR_0_7_INT_STATUS_EXT_ODR_DRDY_PIN_0_POS      0x03
#define REG_ISR_0_7_INT_STATUS_EXT_ODR_DRDY_PIN_0_MASK     (0x01 << REG_ISR_0_7_INT_STATUS_EXT_ODR_DRDY_PIN_0_POS)

/*
 * int_status_on_demand_pin_0
 * For irq0 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of on demand event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_ISR_0_7_INT_STATUS_ON_DEMAND_PIN_0_POS      0x05
#define REG_ISR_0_7_INT_STATUS_ON_DEMAND_PIN_0_MASK     (0x01 << REG_ISR_0_7_INT_STATUS_ON_DEMAND_PIN_0_POS)



/*
 * REG_ISR_8_15
 * Register Name : ISR_8_15
 */

/*
 * int_status_accel_drdy_pin_1
 * For irq1 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of Accel drdy event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_ISR_8_15_INT_STATUS_ACCEL_DRDY_PIN_1_POS      0x00
#define REG_ISR_8_15_INT_STATUS_ACCEL_DRDY_PIN_1_MASK     0x01

/*
 * int_status_ext_odr_drdy_pin_1
 * For irq1 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of ext ODR drdy event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_ISR_8_15_INT_STATUS_EXT_ODR_DRDY_PIN_1_POS      0x03
#define REG_ISR_8_15_INT_STATUS_EXT_ODR_DRDY_PIN_1_MASK     (0x01 << REG_ISR_8_15_INT_STATUS_EXT_ODR_DRDY_PIN_1_POS)

/*
 * int_status_on_demand_pin_1
 * For irq1 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of on demand event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_ISR_8_15_INT_STATUS_ON_DEMAND_PIN_1_POS      0x05
#define REG_ISR_8_15_INT_STATUS_ON_DEMAND_PIN_1_MASK     (0x01 << REG_ISR_8_15_INT_STATUS_ON_DEMAND_PIN_1_POS)



/*
 * REG_ISR_16_23
 * Register Name : ISR_16_23
 */

/*
 * int_status_accel_drdy_pin_2
 * For irq2 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of Accel drdy event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_ISR_16_23_INT_STATUS_ACCEL_DRDY_PIN_2_POS      0x00
#define REG_ISR_16_23_INT_STATUS_ACCEL_DRDY_PIN_2_MASK     0x01

/*
 * int_status_ext_odr_drdy_pin_2
 * For irq2 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of ext ODR drdy event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_ISR_16_23_INT_STATUS_EXT_ODR_DRDY_PIN_2_POS      0x03
#define REG_ISR_16_23_INT_STATUS_EXT_ODR_DRDY_PIN_2_MASK     (0x01 << REG_ISR_16_23_INT_STATUS_EXT_ODR_DRDY_PIN_2_POS)

/*
 * int_status_on_demand_pin_2
 * For irq2 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of on demand event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_ISR_16_23_INT_STATUS_ON_DEMAND_PIN_2_POS      0x05
#define REG_ISR_16_23_INT_STATUS_ON_DEMAND_PIN_2_MASK     (0x01 << REG_ISR_16_23_INT_STATUS_ON_DEMAND_PIN_2_POS)



/*
 * REG_STATUS_MASK_PIN_0_7
 * Register Name : STATUS_MASK_PIN_0_7
 */

/*
 * int_accel_drdy_pin_0_dis
 *
 * For irq0, accel drdy event, this is to enable the interrupt pin assertion when the int_status_accel_drdy_pin_0 status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_STATUS_MASK_PIN_0_7_INT_ACCEL_DRDY_PIN_0_DIS_POS      0x00
#define REG_STATUS_MASK_PIN_0_7_INT_ACCEL_DRDY_PIN_0_DIS_MASK     0x01

/*
 * int_ext_odr_drdy_pin_0_dis
 *
 * For irq0, ODR drdy event, this is to enable the interrupt pin assertion when the int_status_ext_odr_drdy_pin_0 status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_STATUS_MASK_PIN_0_7_INT_EXT_ODR_DRDY_PIN_0_DIS_POS      0x03
#define REG_STATUS_MASK_PIN_0_7_INT_EXT_ODR_DRDY_PIN_0_DIS_MASK     (0x01 << REG_STATUS_MASK_PIN_0_7_INT_EXT_ODR_DRDY_PIN_0_DIS_POS)

/*
 * int_on_demand_pin_0_dis
 *
 * For irq0, on-demand drdy event, this is to enable the interrupt pin assertion when the int_status_on_demand_pin_0 status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_STATUS_MASK_PIN_0_7_INT_ON_DEMAND_PIN_0_DIS_POS      0x05
#define REG_STATUS_MASK_PIN_0_7_INT_ON_DEMAND_PIN_0_DIS_MASK     (0x01 << REG_STATUS_MASK_PIN_0_7_INT_ON_DEMAND_PIN_0_DIS_POS)



/*
 * REG_STATUS_MASK_PIN_8_15
 * Register Name : STATUS_MASK_PIN_8_15
 */

/*
 * int_accel_drdy_pin_1_dis
 *
 * For irq1, accel drdy event, this is to enable the interrupt pin assertion when the int_status_accel_drdy_pin_1 status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_STATUS_MASK_PIN_8_15_INT_ACCEL_DRDY_PIN_1_DIS_POS      0x00
#define REG_STATUS_MASK_PIN_8_15_INT_ACCEL_DRDY_PIN_1_DIS_MASK     0x01

/*
 * int_ext_odr_drdy_pin_1_dis
 *
 * For irq1, ODR drdy event, this is to enable the interrupt pin assertion when the int_status_ext_odr_drdy_pin_1 status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_STATUS_MASK_PIN_8_15_INT_EXT_ODR_DRDY_PIN_1_DIS_POS      0x03
#define REG_STATUS_MASK_PIN_8_15_INT_EXT_ODR_DRDY_PIN_1_DIS_MASK     (0x01 << REG_STATUS_MASK_PIN_8_15_INT_EXT_ODR_DRDY_PIN_1_DIS_POS)

/*
 * int_on_demand_pin_1_dis
 *
 * For irq1, on-demand drdy event, this is to enable the interrupt pin assertion when the int_status_on_demand_pin_1 status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_STATUS_MASK_PIN_8_15_INT_ON_DEMAND_PIN_1_DIS_POS      0x05
#define REG_STATUS_MASK_PIN_8_15_INT_ON_DEMAND_PIN_1_DIS_MASK     (0x01 << REG_STATUS_MASK_PIN_8_15_INT_ON_DEMAND_PIN_1_DIS_POS)



/*
 * REG_STATUS_MASK_PIN_16_23
 * Register Name : STATUS_MASK_PIN_16_23
 */

/*
 * int_accel_drdy_pin_2_dis
 *
 * For irq2, accel drdy event, this is to enable the interrupt pin assertion when the int_status_accel_drdy_pin_2 status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_STATUS_MASK_PIN_16_23_INT_ACCEL_DRDY_PIN_2_DIS_POS      0x00
#define REG_STATUS_MASK_PIN_16_23_INT_ACCEL_DRDY_PIN_2_DIS_MASK     0x01

/*
 * int_ext_odr_drdy_pin_2_dis
 *
 * For irq2, ODR drdy event, this is to enable the interrupt pin assertion when the int_status_ext_odr_drdy_pin_2 status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_STATUS_MASK_PIN_16_23_INT_EXT_ODR_DRDY_PIN_2_DIS_POS      0x03
#define REG_STATUS_MASK_PIN_16_23_INT_EXT_ODR_DRDY_PIN_2_DIS_MASK     (0x01 << REG_STATUS_MASK_PIN_16_23_INT_EXT_ODR_DRDY_PIN_2_DIS_POS)

/*
 * int_on_demand_pin_2_dis
 *
 * For irq2, on-demand drdy event, this is to enable the interrupt pin assertion when the int_status_on_demand_pin_2 status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_STATUS_MASK_PIN_16_23_INT_ON_DEMAND_PIN_2_DIS_POS      0x05
#define REG_STATUS_MASK_PIN_16_23_INT_ON_DEMAND_PIN_2_DIS_MASK     (0x01 << REG_STATUS_MASK_PIN_16_23_INT_ON_DEMAND_PIN_2_DIS_POS)



/*
 * REG_INT_I2CM_SOURCE
 * Register Name : INT_I2CM_SOURCE
 */

/*
 * int_status_i2cm_ioc_ext_trig_en
 * For i2cm  interface, Enable interrupt status bit to flag the occurances of  ioc_ext_trg event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT_I2CM_SOURCE_INT_STATUS_I2CM_IOC_EXT_TRIG_EN_POS      0x00
#define REG_INT_I2CM_SOURCE_INT_STATUS_I2CM_IOC_EXT_TRIG_EN_MASK     0x01

/*
 * int_status_i2cm_smc_ext_odr_en
 * For i2cm  interface, Enable interrupt status bit to flag the occurances of  smc_ext_odr event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT_I2CM_SOURCE_INT_STATUS_I2CM_SMC_EXT_ODR_EN_POS      0x01
#define REG_INT_I2CM_SOURCE_INT_STATUS_I2CM_SMC_EXT_ODR_EN_MASK     (0x01 << REG_INT_I2CM_SOURCE_INT_STATUS_I2CM_SMC_EXT_ODR_EN_POS)



/*
 * REG_ACCEL_WOM_X_THR
 * Register Name : ACCEL_WOM_X_THR
 */

/*
 * wom_x_th
 * WoM thresholds are expressed in fixed “mg” independently of the selected full-scale (format <U,8,0>, range [0g : 1g], resolution 1g/256=~4mg).
 */
#define REG_ACCEL_WOM_X_THR_WOM_X_TH_POS      0x00
#define REG_ACCEL_WOM_X_THR_WOM_X_TH_MASK     0xff



/*
 * REG_ACCEL_WOM_Y_THR
 * Register Name : ACCEL_WOM_Y_THR
 */

/*
 * wom_y_th
 * WoM thresholds are expressed in fixed “mg” independently of the selected full-scale (format <U,8,0>, range [0g : 1g], resolution 1g/256=~4mg).
 */
#define REG_ACCEL_WOM_Y_THR_WOM_Y_TH_POS      0x00
#define REG_ACCEL_WOM_Y_THR_WOM_Y_TH_MASK     0xff



/*
 * REG_ACCEL_WOM_Z_THR
 * Register Name : ACCEL_WOM_Z_THR
 */

/*
 * wom_z_th
 * WoM thresholds are expressed in fixed “mg” independently of the selected full-scale (format <U,8,0>, range [0g : 1g], resolution 1g/256=~4mg).
 */
#define REG_ACCEL_WOM_Z_THR_WOM_Z_TH_POS      0x00
#define REG_ACCEL_WOM_Z_THR_WOM_Z_TH_MASK     0xff



/*
 * REG_SELFTEST
 * Register Name : SELFTEST
 */

/*
 * en_ax_st
 * [Supports Dynamic Change] Enable AX selftest
 */
#define REG_SELFTEST_EN_AX_ST_POS      0x00
#define REG_SELFTEST_EN_AX_ST_MASK     0x01

/*
 * en_ay_st
 * [Supports Dynamic Change] Enable AY selftest
 */
#define REG_SELFTEST_EN_AY_ST_POS      0x01
#define REG_SELFTEST_EN_AY_ST_MASK     (0x01 << REG_SELFTEST_EN_AY_ST_POS)

/*
 * en_az_st
 * [Supports Dynamic Change] Enable AZ selftest
 */
#define REG_SELFTEST_EN_AZ_ST_POS      0x02
#define REG_SELFTEST_EN_AZ_ST_MASK     (0x01 << REG_SELFTEST_EN_AZ_ST_POS)

/*
 * en_gx_st
 * [Supports Dynamic Change] Gyro x self test pin enable
 * 0: The self test electrode is biased for gyro operation
 * 1: The self test electrode is connected to the self test signal source
 */
#define REG_SELFTEST_EN_GX_ST_POS      0x03
#define REG_SELFTEST_EN_GX_ST_MASK     (0x01 << REG_SELFTEST_EN_GX_ST_POS)

/*
 * en_gy_st
 * [Supports Dynamic Change] Gyro y self test pin enable
 * 0: The self test electrode is biased for gyro operation
 * 1: The self test electrode is connected to the self test signal source
 */
#define REG_SELFTEST_EN_GY_ST_POS      0x04
#define REG_SELFTEST_EN_GY_ST_MASK     (0x01 << REG_SELFTEST_EN_GY_ST_POS)

/*
 * en_gz_st
 * [Supports Dynamic Change] Gyro z self test pin enable
 * 0: The self test electrode is biased for gyro operation
 * 1: The self test electrode is connected to the self test signal source
 */
#define REG_SELFTEST_EN_GZ_ST_POS      0x05
#define REG_SELFTEST_EN_GZ_ST_MASK     (0x01 << REG_SELFTEST_EN_GZ_ST_POS)



/*
 * REG_IPREG_MISC
 * Register Name : IPREG_MISC
 */

/*
 * edmp_idle
 * 1: Indicates eDMP is idle
 * 0 : Indicates eDMP is busy
 */
#define REG_IPREG_MISC_EDMP_IDLE_POS      0x01
#define REG_IPREG_MISC_EDMP_IDLE_MASK     (0x01 << REG_IPREG_MISC_EDMP_IDLE_POS)

/*
 * REG_SW_PLL1_TRIM
 * Register Name : SW_PLL1_TRIM
 */

/*
 * sw_pll1_trim
 * Stores variation of PLL frequency test measurement vs. target value, used for SW applications. Value to trim =(PLL_measurement – 6144000Hz) / 6144000Hz * 2540. 6144000Hz is the target PLL freq. 2540 is the resolution coefficient: max register range / max oscillator frequency error = (2^7 - 1) / 5%, with a sign bit.
 */
#define REG_SW_PLL1_TRIM_SW_PLL1_TRIM_POS      0x00
#define REG_SW_PLL1_TRIM_SW_PLL1_TRIM_MASK     0xff



/*
 * REG_FIFO_SRAM_SLEEP
 * Register Name : FIFO_SRAM_SLEEP
 */

/*
 * fifo_gsleep_shared_sram
 * Set selected SRAM bank global sleep mode (pwr_gsleep)
 *
 * 0: selected SRAM bank sleep mode is controlled by PSEQ, ps_fifo_gsleep_fifo_sram, if this bank contains FIFO data. Otherwise SRAM is in sleep  mode (SRAM bank pwr_gsleep=1).
 *
 * 1: selected SRAM bank remains in active mode (pwr_gsleep=0).
 *
 * Can be changed when FIFO is disabled (Bypass mode), AHB interface idle.
 */
#define REG_FIFO_SRAM_SLEEP_FIFO_GSLEEP_SHARED_SRAM_POS      0x00
#define REG_FIFO_SRAM_SLEEP_FIFO_GSLEEP_SHARED_SRAM_MASK     0x03


/* ---------------------------------------------------------------------------
 * register DREG_BANK1
 * ---------------------------------------------------------------------------*/

/*
 * REG_ACCEL_DATA_X1_UI
 * Register Name : ACCEL_DATA_X1_UI
 */

/*
 * accel_data_x_ui
 * Accel X axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_X1_UI_ACCEL_DATA_X_UI_POS      0x00
#define REG_ACCEL_DATA_X1_UI_ACCEL_DATA_X_UI_MASK     0xff



/*
 * REG_ACCEL_DATA_X0_UI
 * Register Name : ACCEL_DATA_X0_UI
 */

/*
 * accel_data_x_ui
 * Accel X axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_X0_UI_ACCEL_DATA_X_UI_POS      0x00
#define REG_ACCEL_DATA_X0_UI_ACCEL_DATA_X_UI_MASK     0xff



/*
 * REG_ACCEL_DATA_Y1_UI
 * Register Name : ACCEL_DATA_Y1_UI
 */

/*
 * accel_data_y_ui
 * Accel Y axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Y1_UI_ACCEL_DATA_Y_UI_POS      0x00
#define REG_ACCEL_DATA_Y1_UI_ACCEL_DATA_Y_UI_MASK     0xff



/*
 * REG_ACCEL_DATA_Y0_UI
 * Register Name : ACCEL_DATA_Y0_UI
 */

/*
 * accel_data_y_ui
 * Accel Y axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Y0_UI_ACCEL_DATA_Y_UI_POS      0x00
#define REG_ACCEL_DATA_Y0_UI_ACCEL_DATA_Y_UI_MASK     0xff



/*
 * REG_ACCEL_DATA_Z1_UI
 * Register Name : ACCEL_DATA_Z1_UI
 */

/*
 * accel_data_z_ui
 * Accel Z axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Z1_UI_ACCEL_DATA_Z_UI_POS      0x00
#define REG_ACCEL_DATA_Z1_UI_ACCEL_DATA_Z_UI_MASK     0xff



/*
 * REG_ACCEL_DATA_Z0_UI
 * Register Name : ACCEL_DATA_Z0_UI
 */

/*
 * accel_data_z_ui
 * Accel Z axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Z0_UI_ACCEL_DATA_Z_UI_POS      0x00
#define REG_ACCEL_DATA_Z0_UI_ACCEL_DATA_Z_UI_MASK     0xff



/*
 * REG_GYRO_DATA_X1_UI
 * Register Name : GYRO_DATA_X1_UI
 */

/*
 * gyro_data_x_ui
 * Gyro X axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_X1_UI_GYRO_DATA_X_UI_POS      0x00
#define REG_GYRO_DATA_X1_UI_GYRO_DATA_X_UI_MASK     0xff



/*
 * REG_GYRO_DATA_X0_UI
 * Register Name : GYRO_DATA_X0_UI
 */

/*
 * gyro_data_x_ui
 * Gyro X axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_X0_UI_GYRO_DATA_X_UI_POS      0x00
#define REG_GYRO_DATA_X0_UI_GYRO_DATA_X_UI_MASK     0xff



/*
 * REG_GYRO_DATA_Y1_UI
 * Register Name : GYRO_DATA_Y1_UI
 */

/*
 * gyro_data_y_ui
 * Gyro Y axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Y1_UI_GYRO_DATA_Y_UI_POS      0x00
#define REG_GYRO_DATA_Y1_UI_GYRO_DATA_Y_UI_MASK     0xff



/*
 * REG_GYRO_DATA_Y0_UI
 * Register Name : GYRO_DATA_Y0_UI
 */

/*
 * gyro_data_y_ui
 * Gyro Y axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Y0_UI_GYRO_DATA_Y_UI_POS      0x00
#define REG_GYRO_DATA_Y0_UI_GYRO_DATA_Y_UI_MASK     0xff



/*
 * REG_GYRO_DATA_Z1_UI
 * Register Name : GYRO_DATA_Z1_UI
 */

/*
 * gyro_data_z_ui
 * Gyro Z axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Z1_UI_GYRO_DATA_Z_UI_POS      0x00
#define REG_GYRO_DATA_Z1_UI_GYRO_DATA_Z_UI_MASK     0xff



/*
 * REG_GYRO_DATA_Z0_UI
 * Register Name : GYRO_DATA_Z0_UI
 */

/*
 * gyro_data_z_ui
 * Gyro Z axis data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Z0_UI_GYRO_DATA_Z_UI_POS      0x00
#define REG_GYRO_DATA_Z0_UI_GYRO_DATA_Z_UI_MASK     0xff



/*
 * REG_TEMP_DATA1_UI
 * Register Name : TEMP_DATA1_UI
 */

/*
 * temp_data_ui
 * Temperature data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TEMP_DATA1_UI_TEMP_DATA_UI_POS      0x00
#define REG_TEMP_DATA1_UI_TEMP_DATA_UI_MASK     0xff



/*
 * REG_TEMP_DATA0_UI
 * Register Name : TEMP_DATA0_UI
 */

/*
 * temp_data_ui
 * Temperature data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TEMP_DATA0_UI_TEMP_DATA_UI_POS      0x00
#define REG_TEMP_DATA0_UI_TEMP_DATA_UI_MASK     0xff



/*
 * REG_TMST_FSYNCH
 * Register Name : TMST_FSYNCH
 */

/*
 * tmst_fsync_data_ui
 * Timestamp/FSYNC data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TMST_FSYNCH_TMST_FSYNC_DATA_UI_POS      0x00
#define REG_TMST_FSYNCH_TMST_FSYNC_DATA_UI_MASK     0xff



/*
 * REG_TMST_FSYNCL
 * Register Name : TMST_FSYNCL
 */

/*
 * tmst_fsync_data_ui
 * Timestamp/FSYNC data for UI/AP path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TMST_FSYNCL_TMST_FSYNC_DATA_UI_POS      0x00
#define REG_TMST_FSYNCL_TMST_FSYNC_DATA_UI_MASK     0xff



/*
 * REG_PWR_MGMT0
 * Register Name : PWR_MGMT0
 */

/*
 * accel_mode
 * [Supports Dynamic Change] Accelerometer Power-Mode for the UI/AP FIFO:
 *   00: OFF
 *   01: OFF
 *   10: LP
 *   11: LN
 */
#define REG_PWR_MGMT0_ACCEL_MODE_POS      0x00
#define REG_PWR_MGMT0_ACCEL_MODE_MASK     0x03

/*
 * gyro_mode
 * [Supports Dynamic Change] Gyroscope Power-Mode for the UI/AP FIFO:
 *   00: OFF
 *   01: STANDBY
 *   10: LP
 *   11: LN
 */
#define REG_PWR_MGMT0_GYRO_MODE_POS      0x02
#define REG_PWR_MGMT0_GYRO_MODE_MASK     (0x03 << REG_PWR_MGMT0_GYRO_MODE_POS)

/*
 * REG_FIFO_COUNT_0
 * Register Name : FIFO_COUNT_0
 */

/*
 * fifo_data_cnt
 * [Supports Dynamic Change] FIFO data counter. It returns the number of unread frames inside the FIFO.
 * Can be read anytime.
 * For the case of a 16 bit FIFO data count, this register must be read in one 2-byte burst, or one hybrid count+data burst. Internally, FIFO locks the count when the data count register is read, so that MSB and LSB bytes are from the same snapshot. The lock is to prevent the count from changing if a new frame was written to FIFO during count read.
 *
 * For SPI serial interface mode: if SPI clock frequency is more than 10 MHz, a minimum tBUF (CS_n=1) of 500ns is needed, in order to correcly read fifo frame count immediately after reading complete data frames.
 */
#define REG_FIFO_COUNT_0_FIFO_DATA_CNT_POS      0x00
#define REG_FIFO_COUNT_0_FIFO_DATA_CNT_MASK     0xff



/*
 * REG_FIFO_COUNT_1
 * Register Name : FIFO_COUNT_1
 */

/*
 * fifo_data_cnt
 * [Supports Dynamic Change] FIFO data counter. It returns the number of unread frames inside the FIFO.
 * Can be read anytime.
 * For the case of a 16 bit FIFO data count, this register must be read in one 2-byte burst, or one hybrid count+data burst. Internally, FIFO locks the count when the data count register is read, so that MSB and LSB bytes are from the same snapshot. The lock is to prevent the count from changing if a new frame was written to FIFO during count read.
 *
 * For SPI serial interface mode: if SPI clock frequency is more than 10 MHz, a minimum tBUF (CS_n=1) of 500ns is needed, in order to correcly read fifo frame count immediately after reading complete data frames.
 */
#define REG_FIFO_COUNT_1_FIFO_DATA_CNT_POS      0x00
#define REG_FIFO_COUNT_1_FIFO_DATA_CNT_MASK     0xff



/*
 * REG_FIFO_DATA
 * Register Name : FIFO_DATA
 */

/*
 * fifo_data
 * FIFO data read by serial interface
 */
#define REG_FIFO_DATA_FIFO_DATA_POS      0x00
#define REG_FIFO_DATA_FIFO_DATA_MASK     0xff



/*
 * REG_INT1_CONFIG0
 * Register Name : INT1_CONFIG0
 */

/*
 * int1_status_en_fifo_full
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  FIFO full event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG0_INT1_STATUS_EN_FIFO_FULL_POS      0x00
#define REG_INT1_CONFIG0_INT1_STATUS_EN_FIFO_FULL_MASK     0x01

/*
 * int1_status_en_fifo_ths
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  fifo_data count ≥ fifo_wm_th event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG0_INT1_STATUS_EN_FIFO_THS_POS      0x01
#define REG_INT1_CONFIG0_INT1_STATUS_EN_FIFO_THS_MASK     (0x01 << REG_INT1_CONFIG0_INT1_STATUS_EN_FIFO_THS_POS)

/*
 * int1_status_en_drdy
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  DRDY event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG0_INT1_STATUS_EN_DRDY_POS      0x02
#define REG_INT1_CONFIG0_INT1_STATUS_EN_DRDY_MASK     (0x01 << REG_INT1_CONFIG0_INT1_STATUS_EN_DRDY_POS)

/*
 * int1_status_en_aux1_drdy
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  AUX1 DRDY event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG0_INT1_STATUS_EN_AUX1_DRDY_POS      0x03
#define REG_INT1_CONFIG0_INT1_STATUS_EN_AUX1_DRDY_MASK     (0x01 << REG_INT1_CONFIG0_INT1_STATUS_EN_AUX1_DRDY_POS)

/*
 * int1_status_en_ap_fsync
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  FSYNC event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG0_INT1_STATUS_EN_AP_FSYNC_POS      0x04
#define REG_INT1_CONFIG0_INT1_STATUS_EN_AP_FSYNC_MASK     (0x01 << REG_INT1_CONFIG0_INT1_STATUS_EN_AP_FSYNC_POS)

/*
 * int1_status_en_ap_agc_rdy
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  AGC Ready event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG0_INT1_STATUS_EN_AP_AGC_RDY_POS      0x05
#define REG_INT1_CONFIG0_INT1_STATUS_EN_AP_AGC_RDY_MASK     (0x01 << REG_INT1_CONFIG0_INT1_STATUS_EN_AP_AGC_RDY_POS)

/*
 * int1_status_en_aux1_agc_rdy
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  OIS1 AGC Ready event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG0_INT1_STATUS_EN_AUX1_AGC_RDY_POS      0x06
#define REG_INT1_CONFIG0_INT1_STATUS_EN_AUX1_AGC_RDY_MASK     (0x01 << REG_INT1_CONFIG0_INT1_STATUS_EN_AUX1_AGC_RDY_POS)

/*
 * int1_status_en_reset_done
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  Reset done event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG0_INT1_STATUS_EN_RESET_DONE_POS      0x07
#define REG_INT1_CONFIG0_INT1_STATUS_EN_RESET_DONE_MASK     (0x01 << REG_INT1_CONFIG0_INT1_STATUS_EN_RESET_DONE_POS)



/*
 * REG_INT1_CONFIG1
 * Register Name : INT1_CONFIG1
 */

/*
 * int1_status_en_pll_rdy
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  PLL ready event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG1_INT1_STATUS_EN_PLL_RDY_POS      0x00
#define REG_INT1_CONFIG1_INT1_STATUS_EN_PLL_RDY_MASK     0x01

/*
 * int1_status_en_wom_x
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  WOM on X-axis event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG1_INT1_STATUS_EN_WOM_X_POS      0x01
#define REG_INT1_CONFIG1_INT1_STATUS_EN_WOM_X_MASK     (0x01 << REG_INT1_CONFIG1_INT1_STATUS_EN_WOM_X_POS)

/*
 * int1_status_en_wom_y
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  WOM on Y-axis event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG1_INT1_STATUS_EN_WOM_Y_POS      0x02
#define REG_INT1_CONFIG1_INT1_STATUS_EN_WOM_Y_MASK     (0x01 << REG_INT1_CONFIG1_INT1_STATUS_EN_WOM_Y_POS)

/*
 * int1_status_en_wom_z
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  WOM on Z-axis event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG1_INT1_STATUS_EN_WOM_Z_POS      0x03
#define REG_INT1_CONFIG1_INT1_STATUS_EN_WOM_Z_MASK     (0x01 << REG_INT1_CONFIG1_INT1_STATUS_EN_WOM_Z_POS)

/*
 * int1_status_en_i3c_protocol_err
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  i3c protocol error event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG1_INT1_STATUS_EN_I3C_PROTOCOL_ERR_POS      0x04
#define REG_INT1_CONFIG1_INT1_STATUS_EN_I3C_PROTOCOL_ERR_MASK     (0x01 << REG_INT1_CONFIG1_INT1_STATUS_EN_I3C_PROTOCOL_ERR_POS)

/*
 * int1_status_en_i2cm_done
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  i2c master operation completed event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG1_INT1_STATUS_EN_I2CM_DONE_POS      0x05
#define REG_INT1_CONFIG1_INT1_STATUS_EN_I2CM_DONE_MASK     (0x01 << REG_INT1_CONFIG1_INT1_STATUS_EN_I2CM_DONE_POS)

/*
 * int1_status_en_apex_event
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of edmp event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT1_CONFIG1_INT1_STATUS_EN_APEX_EVENT_POS      0x06
#define REG_INT1_CONFIG1_INT1_STATUS_EN_APEX_EVENT_MASK     (0x01 << REG_INT1_CONFIG1_INT1_STATUS_EN_APEX_EVENT_POS)



/*
 * REG_INT1_CONFIG2
 * Register Name : INT1_CONFIG2
 */

/*
 * int1_polarity
 * UI/AP interface: Interrupt polarity.
 * 0: active low,
 * 1: active high,
 * Setting can be changed only when all interrupts of the corresponding serial interface are disabled.
 */
#define REG_INT1_CONFIG2_INT1_POLARITY_POS      0x00
#define REG_INT1_CONFIG2_INT1_POLARITY_MASK     0x01

/*
 * int1_mode
 * "UI/AP interface: Interrupt mode.
 * 0: pulse mode,
 * 1: latch mode,
 * Setting can be changed only when all interrupts of the corresponding serial interface are disabled."
 *
 */
#define REG_INT1_CONFIG2_INT1_MODE_POS      0x01
#define REG_INT1_CONFIG2_INT1_MODE_MASK     (0x01 << REG_INT1_CONFIG2_INT1_MODE_POS)

/*
 * int1_drive
 * Sets INT1 PAD in to Open-drain or Push-pull
 * 1 : Open-drain
 * 0 : Push-pull
 */
#define REG_INT1_CONFIG2_INT1_DRIVE_POS      0x02
#define REG_INT1_CONFIG2_INT1_DRIVE_MASK     (0x01 << REG_INT1_CONFIG2_INT1_DRIVE_POS)



/*
 * REG_INT1_STATUS0
 * Register Name : INT1_STATUS0
 */

/*
 * int1_status_fifo_full
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of FIFO full event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS0_INT1_STATUS_FIFO_FULL_POS      0x00
#define REG_INT1_STATUS0_INT1_STATUS_FIFO_FULL_MASK     0x01

/*
 * int1_status_fifo_ths
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of fifo_data_cnt ≥ fifo_wm_th event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS0_INT1_STATUS_FIFO_THS_POS      0x01
#define REG_INT1_STATUS0_INT1_STATUS_FIFO_THS_MASK     (0x01 << REG_INT1_STATUS0_INT1_STATUS_FIFO_THS_POS)

/*
 * int1_status_drdy
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of Data Ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS0_INT1_STATUS_DRDY_POS      0x02
#define REG_INT1_STATUS0_INT1_STATUS_DRDY_MASK     (0x01 << REG_INT1_STATUS0_INT1_STATUS_DRDY_POS)

/*
 * int1_status_aux1_drdy
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of AUX1 data ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS0_INT1_STATUS_AUX1_DRDY_POS      0x03
#define REG_INT1_STATUS0_INT1_STATUS_AUX1_DRDY_MASK     (0x01 << REG_INT1_STATUS0_INT1_STATUS_AUX1_DRDY_POS)

/*
 * int1_status_ap_fsync
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of FSYNC event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS0_INT1_STATUS_AP_FSYNC_POS      0x04
#define REG_INT1_STATUS0_INT1_STATUS_AP_FSYNC_MASK     (0x01 << REG_INT1_STATUS0_INT1_STATUS_AP_FSYNC_POS)

/*
 * int1_status_ap_agc_rdy
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of AGC Ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS0_INT1_STATUS_AP_AGC_RDY_POS      0x05
#define REG_INT1_STATUS0_INT1_STATUS_AP_AGC_RDY_MASK     (0x01 << REG_INT1_STATUS0_INT1_STATUS_AP_AGC_RDY_POS)

/*
 * int1_status_aux1_agc_rdy
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of AUX1 AGC Ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS0_INT1_STATUS_AUX1_AGC_RDY_POS      0x06
#define REG_INT1_STATUS0_INT1_STATUS_AUX1_AGC_RDY_MASK     (0x01 << REG_INT1_STATUS0_INT1_STATUS_AUX1_AGC_RDY_POS)

/*
 * int1_status_reset_done
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of Reset event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS0_INT1_STATUS_RESET_DONE_POS      0x07
#define REG_INT1_STATUS0_INT1_STATUS_RESET_DONE_MASK     (0x01 << REG_INT1_STATUS0_INT1_STATUS_RESET_DONE_POS)



/*
 * REG_INT1_STATUS1
 * Register Name : INT1_STATUS1
 */

/*
 * int1_status_pll_rdy
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of PLL ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS1_INT1_STATUS_PLL_RDY_POS      0x00
#define REG_INT1_STATUS1_INT1_STATUS_PLL_RDY_MASK     0x01

/*
 * int1_status_wom_x
 * For UI/AP interface,If this interrupt status bit is enabled, this bit is to flag the occurance of WOM event on X axis.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS1_INT1_STATUS_WOM_X_POS      0x01
#define REG_INT1_STATUS1_INT1_STATUS_WOM_X_MASK     (0x01 << REG_INT1_STATUS1_INT1_STATUS_WOM_X_POS)

/*
 * int1_status_wom_y
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of WOM event on Y axis.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS1_INT1_STATUS_WOM_Y_POS      0x02
#define REG_INT1_STATUS1_INT1_STATUS_WOM_Y_MASK     (0x01 << REG_INT1_STATUS1_INT1_STATUS_WOM_Y_POS)

/*
 * int1_status_wom_z
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of WOM event on Z axis.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS1_INT1_STATUS_WOM_Z_POS      0x03
#define REG_INT1_STATUS1_INT1_STATUS_WOM_Z_MASK     (0x01 << REG_INT1_STATUS1_INT1_STATUS_WOM_Z_POS)

/*
 * int1_status_i3c_protocol_err
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of I3C protocol error event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS1_INT1_STATUS_I3C_PROTOCOL_ERR_POS      0x04
#define REG_INT1_STATUS1_INT1_STATUS_I3C_PROTOCOL_ERR_MASK     (0x01 << REG_INT1_STATUS1_INT1_STATUS_I3C_PROTOCOL_ERR_POS)

/*
 * int1_status_i2cm_done
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of I2C Master done event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS1_INT1_STATUS_I2CM_DONE_POS      0x05
#define REG_INT1_STATUS1_INT1_STATUS_I2CM_DONE_MASK     (0x01 << REG_INT1_STATUS1_INT1_STATUS_I2CM_DONE_POS)

/*
 * int1_status_apex_event
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of edmp event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT1_STATUS1_INT1_STATUS_APEX_EVENT_POS      0x06
#define REG_INT1_STATUS1_INT1_STATUS_APEX_EVENT_MASK     (0x01 << REG_INT1_STATUS1_INT1_STATUS_APEX_EVENT_POS)



/*
 * REG_ACCEL_CONFIG0
 * Register Name : ACCEL_CONFIG0
 */

/*
 * accel_odr
 * [Supports Dynamic Change] Accelerometer Output Data Rate at the UI/AP FIFO. ODR frequency:
 *   0 -> 6.4k (LN only)
 *   1 -> 6.4k (LN only)
 *   2 -> 6.4k (LN only)
 *   3 -> 6.4k (LN only)
 *   4 -> 3.2k (LN only)
 *   5 -> 1.6k (LN only)
 *   6 -> 800 (default, LN only))
 *   7 -> 400
 *   8 -> 200
 *   9 -> 100
 *   10 -> 50
 *   11 -> 25
 *   12 -> 12.5
 *   13 -> 6.25      (LP only)
 *   14 -> 3.125    (LP only)
 *   15 -> 1.5625  (LP only)
 *
 * This field can be changed on-the-fly even if accel sensor is already on
 */
#define REG_ACCEL_CONFIG0_ACCEL_ODR_POS      0x00
#define REG_ACCEL_CONFIG0_ACCEL_ODR_MASK     0x0f

/*
 * accel_ui_fs_sel
 * [Supports Dynamic Change] Set the UI/AP signal path accel full scale
 * 0 : 32 gee
 * 1 : 16 gee
 * 2 : 8 gee
 * 3 :4 gee
 * 4 : 2 gee
 */
#define REG_ACCEL_CONFIG0_ACCEL_UI_FS_SEL_POS      0x04
#define REG_ACCEL_CONFIG0_ACCEL_UI_FS_SEL_MASK     (0x07 << REG_ACCEL_CONFIG0_ACCEL_UI_FS_SEL_POS)



/*
 * REG_GYRO_CONFIG0
 * Register Name : GYRO_CONFIG0
 */

/*
 * gyro_odr
 * [Supports Dynamic Change] Gyroscope Output Data Rate at the UI/AP FIFO. ODR frequency:
 *   0 -> 6.4k (LN only)
 *   1 -> 6.4k (LN only)
 *   2 -> 6.4k (LN only)
 *   3 -> 6.4k (LN only)
 *   4 -> 3.2k (LN only)
 *   5 -> 1.6k (LN only)
 *   6 -> 800 (default, LN only))
 *   7 -> 400
 *   8 -> 200
 *   9 -> 100
 *   10 -> 50
 *   11 -> 25
 *   12 -> 12.5
 *   13 -> 6.25      (LP only)
 *   14 -> 3.125    (LP only)
 *   15 -> 1.5625  (LP only)
 *
 * This field can be changed on-the-fly even if gyro sensor is already on
 */
#define REG_GYRO_CONFIG0_GYRO_ODR_POS      0x00
#define REG_GYRO_CONFIG0_GYRO_ODR_MASK     0x0f

/*
 * gyro_ui_fs_sel
 * [Supports Dynamic Change] Set the UI/AP signal path gyro full scale
 * 0 : 4000 dps
 * 1 : 2000 dps
 * 2 : 1000 dps
 * 3 : 500 dps
 * 4 : 250 dps
 * 5 : 125 dps
 * 6 : 62.5 dps
 * 7 : 31.25 dps
 * 8 : 15.625 dps
 */
#define REG_GYRO_CONFIG0_GYRO_UI_FS_SEL_POS      0x04
#define REG_GYRO_CONFIG0_GYRO_UI_FS_SEL_MASK     (0x0f << REG_GYRO_CONFIG0_GYRO_UI_FS_SEL_POS)



/*
 * REG_FIFO_CONFIG0
 * Register Name : FIFO_CONFIG0
 */

/*
 * fifo_depth
 * Set the FIFO depth in bytes. The minimum depth is 256 bytes, which is also the granularity of the FIFO space. The FIFO space start address is fixed and set to: fifo_phy_start_addr = (FIFO_IP_SRAM_NROW * 4) – ((fifo_depth+1) * 256)
 * The effective number of choices is capped by FIFO_MAX_DEPTH parameter. As an example, if FIFO_MAX_DEPTH=3 then fifo_depth[5:0] can assume the following values: 0, 1, 2, 3; the remaining choiches must be considered as reserved.
 * 0 : 256
 * 1 : 512
 * 2 : 768
 * 3 : 1024
 * 4 : 1280
 * ...
 * 62 : 16128
 * 63 : 16384
 * Can be changed when FIFO is disabled (Bypass mode).
 */
#define REG_FIFO_CONFIG0_FIFO_DEPTH_POS      0x00
#define REG_FIFO_CONFIG0_FIFO_DEPTH_MASK     0x3f

/*
 * fifo_mode
 * [Supports Dynamic Change] Set the FIFO operation mode.
 * 2’b00: Bypass (disabled)
 * 2’b01: Stream mode - Frames are overwritten when the FIFO full condition is reached. Supported only for 8, 16, 20 bytes frame size. Whether this mode is selected for 32 or 64 bytes frame sizes, FIFO remains in Bypass mode.
 * 2’b10: Stop-on-full mode - Frames are not stored in FIFO once the FIFO full condition is reached
 * 2’b11: Reserved
 */
#define REG_FIFO_CONFIG0_FIFO_MODE_POS      0x06
#define REG_FIFO_CONFIG0_FIFO_MODE_MASK     (0x03 << REG_FIFO_CONFIG0_FIFO_MODE_POS)



/*
 * REG_FIFO_CONFIG1_0
 * Register Name : FIFO_CONFIG1_0
 */

/*
 * fifo_wm_th
 * [Supports Dynamic Change] FIFO watermark threshold. When set to 0, the watermark is disabled.
 * When writing new threshold value, user must first write threshold LSByte (bits [7:0]), then MSByte (bits [15:8]). New threshold register value will take effect only when MSByte is written. MSByte write pulse is used to check watermark level and generate WM interrupt event.
 * Can be changed on-the-fly.
 */
#define REG_FIFO_CONFIG1_0_FIFO_WM_TH_POS      0x00
#define REG_FIFO_CONFIG1_0_FIFO_WM_TH_MASK     0xff



/*
 * REG_FIFO_CONFIG1_1
 * Register Name : FIFO_CONFIG1_1
 */

/*
 * fifo_wm_th
 * [Supports Dynamic Change] FIFO watermark threshold. When set to 0, the watermark is disabled.
 * When writing new threshold value, user must first write threshold LSByte (bits [7:0]), then MSByte (bits [15:8]). New threshold register value will take effect only when MSByte is written. MSByte write pulse is used to check watermark level and generate WM interrupt event.
 * Can be changed on-the-fly.
 */
#define REG_FIFO_CONFIG1_1_FIFO_WM_TH_POS      0x00
#define REG_FIFO_CONFIG1_1_FIFO_WM_TH_MASK     0xff



/*
 * REG_FIFO_CONFIG2
 * Register Name : FIFO_CONFIG2
 */

/*
 * fifo_wr_wm_gt_th
 * Set write watermark interrupt generating condition.
 * 0: write watermark interrupt generated when counter is equal to threshold
 * 1: write watermark interrupt generated when counter is greater than or equal to threshold
 * Can be changed when FIFO is disabled (Bypass mode).
 */
#define REG_FIFO_CONFIG2_FIFO_WR_WM_GT_TH_POS      0x03
#define REG_FIFO_CONFIG2_FIFO_WR_WM_GT_TH_MASK     (0x01 << REG_FIFO_CONFIG2_FIFO_WR_WM_GT_TH_POS)

/*
 * fifo_flush
 * [Supports Dynamic Change] FIFO flush command. When set high the FIFO is flushed, meaning the pointers and control logic is reset. Configuration registers are not reset. The register is auto-cleared by hardware.
 * Can be changed on-the-fly.
 */
#define REG_FIFO_CONFIG2_FIFO_FLUSH_POS      0x07
#define REG_FIFO_CONFIG2_FIFO_FLUSH_MASK     (0x01 << REG_FIFO_CONFIG2_FIFO_FLUSH_POS)



/*
 * REG_FIFO_CONFIG3
 * Register Name : FIFO_CONFIG3
 */

/*
 * fifo_if_en
 * [Supports Dynamic Change] Enable the SREG-FIFO interface. The SREG-FIFO interface should be enabled when the FIFO is also enabled (i.e., not in bypass mode), so a standard enable sequence is: 1) Enable FIFO. 2) Enable SREG-FIFO interface. The opposite for the disable sequence. To prevent power drain, sreg_fifo_if_en should be set to 0 if FIFO is in bypass mode.
 */
#define REG_FIFO_CONFIG3_FIFO_IF_EN_POS      0x00
#define REG_FIFO_CONFIG3_FIFO_IF_EN_MASK     0x01

/*
 * fifo_accel_en
 * Enable accel data insertion into FIFO frame
 */
#define REG_FIFO_CONFIG3_FIFO_ACCEL_EN_POS      0x01
#define REG_FIFO_CONFIG3_FIFO_ACCEL_EN_MASK     (0x01 << REG_FIFO_CONFIG3_FIFO_ACCEL_EN_POS)

/*
 * fifo_gyro_en
 * Enable gyro data insertion into FIFO frame
 */
#define REG_FIFO_CONFIG3_FIFO_GYRO_EN_POS      0x02
#define REG_FIFO_CONFIG3_FIFO_GYRO_EN_MASK     (0x01 << REG_FIFO_CONFIG3_FIFO_GYRO_EN_POS)

/*
 * fifo_hires_en
 * Enable high resolution accel and gyro data insertion into FIFO frame
 */
#define REG_FIFO_CONFIG3_FIFO_HIRES_EN_POS      0x03
#define REG_FIFO_CONFIG3_FIFO_HIRES_EN_MASK     (0x01 << REG_FIFO_CONFIG3_FIFO_HIRES_EN_POS)

/*
 * fifo_es0_en
 * Enable External Sensor 0 data insertion into FIFO frame
 */
#define REG_FIFO_CONFIG3_FIFO_ES0_EN_POS      0x04
#define REG_FIFO_CONFIG3_FIFO_ES0_EN_MASK     (0x01 << REG_FIFO_CONFIG3_FIFO_ES0_EN_POS)

/*
 * fifo_es1_en
 * Enable External Sensor 1 data insertion into FIFO frame
 */
#define REG_FIFO_CONFIG3_FIFO_ES1_EN_POS      0x05
#define REG_FIFO_CONFIG3_FIFO_ES1_EN_MASK     (0x01 << REG_FIFO_CONFIG3_FIFO_ES1_EN_POS)



/*
 * REG_FIFO_CONFIG4
 * Register Name : FIFO_CONFIG4
 */

/*
 * fifo_es0_6b_9b
 * Select how many valid bytes External Sensor 0 provides
 * 0 : 6 bytes
 * 1 : 9 bytes
 */
#define REG_FIFO_CONFIG4_FIFO_ES0_6B_9B_POS      0x00
#define REG_FIFO_CONFIG4_FIFO_ES0_6B_9B_MASK     0x01

/*
 * fifo_tmst_fsync_en
 * Enable the insertion of the Timestamp or FSYNC data into FIFO frame
 * 0 : No Timestamp/FSYNC data inserted into FIFO frame (timestamp fields are 0x0000). fsync_tag_en bit in FIFO header is 0
 * 1 : Timestamp/FSYNC data inserted into FIFO frame. fsync_tag_en bit in FIFO header is set on a FSYNC trigger event
 */
#define REG_FIFO_CONFIG4_FIFO_TMST_FSYNC_EN_POS      0x01
#define REG_FIFO_CONFIG4_FIFO_TMST_FSYNC_EN_MASK     (0x01 << REG_FIFO_CONFIG4_FIFO_TMST_FSYNC_EN_POS)

/*
 * fifo_comp_en
 * Enable the FIFO compression algorithm
 */
#define REG_FIFO_CONFIG4_FIFO_COMP_EN_POS      0x02
#define REG_FIFO_CONFIG4_FIFO_COMP_EN_MASK     (0x01 << REG_FIFO_CONFIG4_FIFO_COMP_EN_POS)

/*
 * fifo_comp_nc_flow_cfg
 * Configures the compression algorithm to write non-compressed frames at a certain rate
 * 0 : Non-compressed frame flow is disabled
 * 1 : Non-compressed frame every 8 frames
 * 2 : Non-compressed frame every 16 frames
 * 3 : Non-compressed frame every 32 frames
 * 4 : Non-compressed frame every 64 frames
 * 5 : Non-compressed frame every 128 frames
 */
#define REG_FIFO_CONFIG4_FIFO_COMP_NC_FLOW_CFG_POS      0x03
#define REG_FIFO_CONFIG4_FIFO_COMP_NC_FLOW_CFG_MASK     (0x07 << REG_FIFO_CONFIG4_FIFO_COMP_NC_FLOW_CFG_POS)



/*
 * REG_TMST_WOM_CONFIG
 * Register Name : TMST_WOM_CONFIG
 */

/*
 * wom_int_dur
 * Deglitch filter settings shared across Accel X,Y,Z.
 * 0: Wom interrupt asserted at first detected event.
 * 1: Wom interrupt asserted at second detected event.
 * 2: Wom interrupt asserted at third detected event.
 * 3: Wom interrupt asserted at forth detected event.
 */
#define REG_TMST_WOM_CONFIG_WOM_INT_DUR_POS      0x00
#define REG_TMST_WOM_CONFIG_WOM_INT_DUR_MASK     0x03

/*
 * wom_int_mode
 * 0: Interrupt generated if any of the axis X,Y,Z cross threshold.
 * 1: Interrupt generated if all axis X,Y,Z cross threshold.
 * This setting can be changed while reg_wom_en = 1.
 */
#define REG_TMST_WOM_CONFIG_WOM_INT_MODE_POS      0x02
#define REG_TMST_WOM_CONFIG_WOM_INT_MODE_MASK     (0x01 << REG_TMST_WOM_CONFIG_WOM_INT_MODE_POS)

/*
 * wom_mode
 * 0: First sample is used as reference to calculate the difference i.e Motion detected if (Curr_sample - first_sample) > threshold.
 * 1: Previous sample is used as reference to calculate the difference i.e Motion detected if (Curr_sample - prev_sample) > threshold.
 * Note, “threshold” refers to the reg_wom_x/y/z_th registers.
 * Note, this reg_wom_mode should not be change dynamically, or when reg_wom_mode = 1.
 */
#define REG_TMST_WOM_CONFIG_WOM_MODE_POS      0x03
#define REG_TMST_WOM_CONFIG_WOM_MODE_MASK     (0x01 << REG_TMST_WOM_CONFIG_WOM_MODE_POS)

/*
 * wom_en
 * 1: Wom feature is enabled.
 * 0: Wom feature is disabled.
 */
#define REG_TMST_WOM_CONFIG_WOM_EN_POS      0x04
#define REG_TMST_WOM_CONFIG_WOM_EN_MASK     (0x01 << REG_TMST_WOM_CONFIG_WOM_EN_POS)

/*
 * tmst_resol
 * Time Stamp resolution; When set to 0 (default), time stamp resolution is 1 us. When set to 1, resolution is 16us
 */
#define REG_TMST_WOM_CONFIG_TMST_RESOL_POS      0x05
#define REG_TMST_WOM_CONFIG_TMST_RESOL_MASK     (0x01 << REG_TMST_WOM_CONFIG_TMST_RESOL_POS)

/*
 * tmst_delta_en
 * Time Stamp delta Enable : When set to 1, the Time stamp field contains the  measurement of time since  the last occurrence of trigger event
 */
#define REG_TMST_WOM_CONFIG_TMST_DELTA_EN_POS      0x06
#define REG_TMST_WOM_CONFIG_TMST_DELTA_EN_MASK     (0x01 << REG_TMST_WOM_CONFIG_TMST_DELTA_EN_POS)



/*
 * REG_FSYNC_CONFIG0
 * Register Name : FSYNC_CONFIG0
 */

/*
 * ap_fsync_sel
 * Select the sensor that will carry the Fsync tagging
 *       0 : FSYNC tagging is disabled
 *       1 : Tag Fsync flag to TEMP_DATA LSB
 *       2 : Tag Fsync flag to GYRO_DATA_X LSB
 *       3 : Tag Fsync flag to GYRO_DATA_Y LSB
 *       4 : Tag Fsync flag to GYRO_DATA_Z LSB
 *       5 : Tag Fsync flag to ACCEL_DATA_X LSB
 *       6 : Tag Fsync flag to ACCEL_DATA_Y LSB
 *       7 : Tag Fsync flag to ACCEL_DATA_Z LSB
 */
#define REG_FSYNC_CONFIG0_AP_FSYNC_SEL_POS      0x00
#define REG_FSYNC_CONFIG0_AP_FSYNC_SEL_MASK     0x07

/*
 * ap_fsync_flag_clear_sel
 * Select the fsync flag clear policy
 * 0 : the fsync flag is cleared when UI/AP sensor reg is updated
 * 1 : the fsync flag is cleared when UI/AP serial interface reads the sensor register LSB of fsync tagged axis
 */
#define REG_FSYNC_CONFIG0_AP_FSYNC_FLAG_CLEAR_SEL_POS      0x03
#define REG_FSYNC_CONFIG0_AP_FSYNC_FLAG_CLEAR_SEL_MASK     (0x01 << REG_FSYNC_CONFIG0_AP_FSYNC_FLAG_CLEAR_SEL_POS)



/*
 * REG_FSYNC_CONFIG1
 * Register Name : FSYNC_CONFIG1
 */

/*
 * aux1_fsync_sel
 * Select the sensor that will carry the Fsync tagging
 *       0 : FSYNC tagging is disabled
 *       1 : Tag Fsync flag to TEMP_DATA_AUX1 LSB
 *       2 : Tag Fsync flag to GYRO_DATA_X_AUX1 LSB
 *       3 : Tag Fsync flag to GYRO_DATA_Y_AUX1 LSB
 *       4 : Tag Fsync flag to GYRO_DATA_Z_AUX1 LSB
 *       5 : Tag Fsync flag to ACCEL_DATA_X_AUX1 LSB
 *       6 : Tag Fsync flag to ACCEL_DATA_Y_AUX1 LSB
 *       7 : Tag Fsync flag to ACCEL_DATA_Z_AUX1 LSB
 */
#define REG_FSYNC_CONFIG1_AUX1_FSYNC_SEL_POS      0x00
#define REG_FSYNC_CONFIG1_AUX1_FSYNC_SEL_MASK     0x07

/*
 * aux1_fsync_flag_clear_sel
 * Select the fsync flag clear policy
 * 0 : the fsync flag is cleared when OIS1 sensor reg is updated
 * 1 : the fsync flag is cleared when AUX1 serial interface reads the sensor register LSB of fsync tagged axis
 */
#define REG_FSYNC_CONFIG1_AUX1_FSYNC_FLAG_CLEAR_SEL_POS      0x03
#define REG_FSYNC_CONFIG1_AUX1_FSYNC_FLAG_CLEAR_SEL_MASK     (0x01 << REG_FSYNC_CONFIG1_AUX1_FSYNC_FLAG_CLEAR_SEL_POS)



/*
 * REG_RTC_CONFIG
 * Register Name : RTC_CONFIG
 */

/*
 * rtc_mode
 * If set to 1 enables the RTC functionality: the external clock source CLK_IN is used to keep the time-base and generate precise ODR values.
 * If also the I3C Synchronous Mode functionality is enabled, then setting this bit to 1 will have no effects.
 * RTC functionality can be enabled only if accel_lp_clk_sel is set to 1; otherwise device may not behave as expected.
 */
#define REG_RTC_CONFIG_RTC_MODE_POS      0x05
#define REG_RTC_CONFIG_RTC_MODE_MASK     (0x01 << REG_RTC_CONFIG_RTC_MODE_POS)

/*
 * rtc_align
 * RTC align bit – re-align command is generated by writing this bit.
 */
#define REG_RTC_CONFIG_RTC_ALIGN_POS      0x06
#define REG_RTC_CONFIG_RTC_ALIGN_MASK     (0x01 << REG_RTC_CONFIG_RTC_ALIGN_POS)



/*
 * REG_DMP_EXT_SEN_ODR_CFG
 * Register Name : DMP_EXT_SEN_ODR_CFG
 */

/*
 * apex_odr
 * [Supports Dynamic Change] DMP Output Data Rate.
 * The dmp_odr needs to be smaller than or equal to both the accel_odr and gyro_odr. Also, all rates but 800Hz can be set if Accel UI/AP is in LP; in order to set the DMP ODR to 800Hz, the Accel UI/AP PM must be set in LN, otherwise the new rate will not be applied).
 *
 * 3'b000 -> 25Hz
 * 3'b001 -> 50Hz (default)
 * 3'b010 -> 100Hz
 * 3'b011 -> 200Hz
 * 3'b100 -> 400Hz
 * 3'b101 -> 800Hz      (LN-only)
 * 3'b110 -> reserved
 * 3'b111 -> reserved
 */
#define REG_DMP_EXT_SEN_ODR_CFG_APEX_ODR_POS      0x00
#define REG_DMP_EXT_SEN_ODR_CFG_APEX_ODR_MASK     0x07

/*
 * ext_odr
 * Internal external ODR for I2CM kickoff
 * 000: 3.125 Hz
 * 001: 6.25 Hz
 * 010: 12.5 Hz
 * 011: 25 Hz
 * 100: 50 Hz
 * 101: 100 Hz
 * 110: 200 Hz
 * 111: 400 Hz
 */
#define REG_DMP_EXT_SEN_ODR_CFG_EXT_ODR_POS      0x03
#define REG_DMP_EXT_SEN_ODR_CFG_EXT_ODR_MASK     (0x07 << REG_DMP_EXT_SEN_ODR_CFG_EXT_ODR_POS)

/*
 * ext_sensor_en
 * 1: To enable the SMC block to generate the ODR event for external snsor operation per the setting of ext_odr register.
 * 0: To disable the SMC block from generating the ODR event for the external sensor operation.
 *
 * This register is not used by any other blocks.
 */
#define REG_DMP_EXT_SEN_ODR_CFG_EXT_SENSOR_EN_POS      0x06
#define REG_DMP_EXT_SEN_ODR_CFG_EXT_SENSOR_EN_MASK     (0x01 << REG_DMP_EXT_SEN_ODR_CFG_EXT_SENSOR_EN_POS)



/*
 * REG_ODR_DECIMATE_CONFIG
 * Register Name : ODR_DECIMATE_CONFIG
 */

/*
 * accel_fifo_odr_dec
 * Decimation factor for the sreg_update rate at the Accel FIFO.
 * Decimation value is 2^(accel_fifo_down):
 *   - 4'b0000: 1 (as input ODR rate)
 *   - 4'b0001: 2
 *   - 4'b0010: 4
 *   - 4'b0011: 8
 *   - 4'b0100: 16
 *   - 4'b0101: 32
 *   - 4'b0110: 64
 *   - 4'b0111: 128
 *   - 4'b1000: 256
 *   - 4'b1001: 512
 *   - 4'b1010: 1024
 *   - 4'b1011: 2048
 *   - 4'b1100: 4096
 *   - 4'b1101: reserved
 *   - 4'b1110: reserved
 *   - 4'b1111: reserved
 *
 * The final sreg_update value will be accel_odr/2^(accel_fifo_odr_dec), with a minimum decimated rate equal to the minimum ODR value.
 */
#define REG_ODR_DECIMATE_CONFIG_ACCEL_FIFO_ODR_DEC_POS      0x00
#define REG_ODR_DECIMATE_CONFIG_ACCEL_FIFO_ODR_DEC_MASK     0x0f

/*
 * gyro_fifo_odr_dec
 * Decimation factor for the sreg_update rate at the Gyroscope FIFO.
 * Decimation value is 2^(gyro_fifo_down):
 *   - 4'b0000: 1 (as input ODR rate)
 *   - 4'b0001: 2
 *   - 4'b0010: 4
 *   - 4'b0011: 8
 *   - 4'b0100: 16
 *   - 4'b0101: 32
 *   - 4'b0110: 64
 *   - 4'b0111: 128
 *   - 4'b1000: 256
 *   - 4'b1001: 512
 *   - 4'b1010: 1024
 *   - 4'b1011: 2048
 *   - 4'b1100: 4096
 *   - 4'b1101: reserved
 *   - 4'b1110: reserved
 *   - 4'b1111: reserved
 *
 * The final sreg_update value will be gyro_odr/2^(gyro_fifo_odr_dec), with a minimum decimated rate equal to the minimum ODR value.
 */
#define REG_ODR_DECIMATE_CONFIG_GYRO_FIFO_ODR_DEC_POS      0x04
#define REG_ODR_DECIMATE_CONFIG_GYRO_FIFO_ODR_DEC_MASK     (0x0f << REG_ODR_DECIMATE_CONFIG_GYRO_FIFO_ODR_DEC_POS)



/*
 * REG_EDMP_APEX_EN0
 * Register Name : EDMP_APEX_EN0
 */

/*
 * tap_en
 * Set 1 to enable Tap algorithm
 */
#define REG_EDMP_APEX_EN0_TAP_EN_POS      0x00
#define REG_EDMP_APEX_EN0_TAP_EN_MASK     0x01

/*
 * reserved0
 * reserved
 */
#define REG_EDMP_APEX_EN0_RESERVED0_POS      0x01
#define REG_EDMP_APEX_EN0_RESERVED0_MASK     (0x01 << REG_EDMP_APEX_EN0_RESERVED0_POS)

/*
 * reserved1
 * reserved
 */
#define REG_EDMP_APEX_EN0_RESERVED1_POS      0x02
#define REG_EDMP_APEX_EN0_RESERVED1_MASK     (0x01 << REG_EDMP_APEX_EN0_RESERVED1_POS)

/*
 * tilt_en
 * Set 1 to enable Tilt algorithm
 */
#define REG_EDMP_APEX_EN0_TILT_EN_POS      0x03
#define REG_EDMP_APEX_EN0_TILT_EN_MASK     (0x01 << REG_EDMP_APEX_EN0_TILT_EN_POS)

/*
 * pedo_en
 * Set 1 to enable Pedometer algorithm
 */
#define REG_EDMP_APEX_EN0_PEDO_EN_POS      0x04
#define REG_EDMP_APEX_EN0_PEDO_EN_MASK     (0x01 << REG_EDMP_APEX_EN0_PEDO_EN_POS)

/*
 * ff_en
 * Set 1 to enable Freefall algorithm
 */
#define REG_EDMP_APEX_EN0_FF_EN_POS      0x05
#define REG_EDMP_APEX_EN0_FF_EN_MASK     (0x01 << REG_EDMP_APEX_EN0_FF_EN_POS)

/*
 * r2w_en
 * Set 1 to enable Raise to Wake algorithm
 */
#define REG_EDMP_APEX_EN0_R2W_EN_POS      0x06
#define REG_EDMP_APEX_EN0_R2W_EN_MASK     (0x01 << REG_EDMP_APEX_EN0_R2W_EN_POS)

/*
 * smd_en
 * Set 1 to enable SMD algorithm
 */
#define REG_EDMP_APEX_EN0_SMD_EN_POS      0x07
#define REG_EDMP_APEX_EN0_SMD_EN_MASK     (0x01 << REG_EDMP_APEX_EN0_SMD_EN_POS)



/*
 * REG_EDMP_APEX_EN1
 * Register Name : EDMP_APEX_EN1
 */

/*
 * soft_hard_iron_corr_en
 * Set 1 to enable soft iron hard iron correction
 */
#define REG_EDMP_APEX_EN1_SOFT_HARD_IRON_CORR_EN_POS      0x00
#define REG_EDMP_APEX_EN1_SOFT_HARD_IRON_CORR_EN_MASK     0x01

/*
 * init_en
 * This bit is set by the host to indicate: eDMP executes only the segment of code that initialize constants used by algorithms. The register is R/W by the external host through the direct register accessing path. The register is R/C by any AHB master when it is accessed via internal AHB/APB bus.
 */
#define REG_EDMP_APEX_EN1_INIT_EN_POS      0x01
#define REG_EDMP_APEX_EN1_INIT_EN_MASK     (0x01 << REG_EDMP_APEX_EN1_INIT_EN_POS)

/*
 * power_save_en
 * Set 1 to enable power save mode
 */
#define REG_EDMP_APEX_EN1_POWER_SAVE_EN_POS      0x02
#define REG_EDMP_APEX_EN1_POWER_SAVE_EN_MASK     (0x01 << REG_EDMP_APEX_EN1_POWER_SAVE_EN_POS)

/*
 * basic_smd_en
 * Set 1 to enable basic SMD algorithm
 */
#define REG_EDMP_APEX_EN1_BASIC_SMD_EN_POS      0x03
#define REG_EDMP_APEX_EN1_BASIC_SMD_EN_MASK     (0x01 << REG_EDMP_APEX_EN1_BASIC_SMD_EN_POS)

/*
 * feature3_en
 * Set 1 to enable reserved feature3
 */
#define REG_EDMP_APEX_EN1_FEATURE3_EN_POS      0x05
#define REG_EDMP_APEX_EN1_FEATURE3_EN_MASK     (0x01 << REG_EDMP_APEX_EN1_FEATURE3_EN_POS)

/*
 * edmp_enable
 * 0: mask out all eDMP input interrupts and freeze eDMP processing after eDMP is finished with current processing sample of all ISRs.
 * 1: Enable eDMP operation mode
 */
#define REG_EDMP_APEX_EN1_EDMP_ENABLE_POS      0x06
#define REG_EDMP_APEX_EN1_EDMP_ENABLE_MASK     (0x01 << REG_EDMP_APEX_EN1_EDMP_ENABLE_POS)



/*
 * REG_APEX_BUFFER_MGMT
 * Register Name : APEX_BUFFER_MGMT
 */

/*
 * step_count_edmp_wptr
 * LSB indicates SRAM address for eDMP to write
 * MSB indicates size 2 buffer wrap around
 * 00: eDMP writes to buffer 0
 * 01: eDMP writes to buffer 1
 * 10: eDMP writes to buffer 0
 * 11: eDMP writes to buffer 1
 */
#define REG_APEX_BUFFER_MGMT_STEP_COUNT_EDMP_WPTR_POS      0x00
#define REG_APEX_BUFFER_MGMT_STEP_COUNT_EDMP_WPTR_MASK     0x03

/*
 * step_count_host_rptr
 * LSB indicates SRAM address for host to read
 * MSB indicates size 2 buffer wrap around
 * 00: host reads buffer 0
 * 01: host reads buffer 1
 * 10: host reads buffer 0
 * 11: host reads buffer 1
 */
#define REG_APEX_BUFFER_MGMT_STEP_COUNT_HOST_RPTR_POS      0x02
#define REG_APEX_BUFFER_MGMT_STEP_COUNT_HOST_RPTR_MASK     (0x03 << REG_APEX_BUFFER_MGMT_STEP_COUNT_HOST_RPTR_POS)

/*
 * ff_duration_edmp_wptr
 * LSB indicates SRAM address for eDMP to write
 * MSB indicates size 2 buffer wrap around
 * 00: eDMP writes to buffer 0
 * 01: eDMP writes to buffer 1
 * 10: eDMP writes to buffer 0
 * 11: eDMP writes to buffer 1
 */
#define REG_APEX_BUFFER_MGMT_FF_DURATION_EDMP_WPTR_POS      0x04
#define REG_APEX_BUFFER_MGMT_FF_DURATION_EDMP_WPTR_MASK     (0x03 << REG_APEX_BUFFER_MGMT_FF_DURATION_EDMP_WPTR_POS)

/*
 * ff_duration_host_rptr
 * LSB indicates SRAM address for host to read
 * MSB indicates size 2 buffer wrap around
 * 00: host reads buffer 0
 * 01: host reads buffer 1
 * 10: host reads buffer 0
 * 11: host reads buffer 1
 */
#define REG_APEX_BUFFER_MGMT_FF_DURATION_HOST_RPTR_POS      0x06
#define REG_APEX_BUFFER_MGMT_FF_DURATION_HOST_RPTR_MASK     (0x03 << REG_APEX_BUFFER_MGMT_FF_DURATION_HOST_RPTR_POS)



/*
 * REG_INTF_CONFIG0
 * Register Name : INTF_CONFIG0
 */

/*
 * ap_spi_mode
 * SPI Mode based on CPOL and CPHA
 * 0 : spi_mode0 or spi_mode3
 * 1: spi_mode1 or spi_mode2
 */
#define REG_INTF_CONFIG0_AP_SPI_MODE_POS      0x00
#define REG_INTF_CONFIG0_AP_SPI_MODE_MASK     0x01

/*
 * ap_spi_34_mode
 * 1: SPI 4 mode, use SDO pad to send data out.
 * 0: SPI 3 mode, use SDA pad to send data out.
 */
#define REG_INTF_CONFIG0_AP_SPI_34_MODE_POS      0x01
#define REG_INTF_CONFIG0_AP_SPI_34_MODE_MASK     (0x01 << REG_INTF_CONFIG0_AP_SPI_34_MODE_POS)

/*
 * virtual_access_aux1_en
 * Virtual access DTP aux1 enable
 * 1 : UI/AP take control of AUX1 interface
 * When the aux1 virtual address mode is enabled, the accessing from the SIFS_AUX1 interface is not supported.
 */
#define REG_INTF_CONFIG0_VIRTUAL_ACCESS_AUX1_EN_POS      0x05
#define REG_INTF_CONFIG0_VIRTUAL_ACCESS_AUX1_EN_MASK     (0x01 << REG_INTF_CONFIG0_VIRTUAL_ACCESS_AUX1_EN_POS)

/*
 * REG_INTF_CONFIG1_OVRD
 * Register Name : INTF_CONFIG1_OVRD
 */

/*
 * ap_spi_mode_ovrd_val
 * Override value for SPI Mode based on CPOL and CPHA
 * 0 : spi_mode0 or spi_mode3
 * 1: spi_mode1 or spi_mode2
 * No change is expected from default mode when IxC slave is selected for host serial transfer.
 */
#define REG_INTF_CONFIG1_OVRD_AP_SPI_MODE_OVRD_VAL_POS      0x00
#define REG_INTF_CONFIG1_OVRD_AP_SPI_MODE_OVRD_VAL_MASK     0x01

/*
 * ap_spi_mode_ovrd
 * Override enable for spi_mode register value
 */
#define REG_INTF_CONFIG1_OVRD_AP_SPI_MODE_OVRD_POS      0x01
#define REG_INTF_CONFIG1_OVRD_AP_SPI_MODE_OVRD_MASK     (0x01 << REG_INTF_CONFIG1_OVRD_AP_SPI_MODE_OVRD_POS)

/*
 * ap_spi_34_mode_ovrd_val
 * Override value for SPI4/SPI3 modes
 * 1: SPI 4 mode, use SDO pad to send data out.
 * 0: SPI 3 mode, use SDA pad to send data out.
 */
#define REG_INTF_CONFIG1_OVRD_AP_SPI_34_MODE_OVRD_VAL_POS      0x02
#define REG_INTF_CONFIG1_OVRD_AP_SPI_34_MODE_OVRD_VAL_MASK     (0x01 << REG_INTF_CONFIG1_OVRD_AP_SPI_34_MODE_OVRD_VAL_POS)

/*
 * ap_spi_34_mode_ovrd
 * Override enable for SPI4/SPI3 modes
 */
#define REG_INTF_CONFIG1_OVRD_AP_SPI_34_MODE_OVRD_POS      0x03
#define REG_INTF_CONFIG1_OVRD_AP_SPI_34_MODE_OVRD_MASK     (0x01 << REG_INTF_CONFIG1_OVRD_AP_SPI_34_MODE_OVRD_POS)



/*
 * REG_INTF_AUX_CONFIG
 * Register Name : INTF_AUX_CONFIG
 */

/*
 * aux1_spi_mode
 * SPI Mode based on CPOL and CPHA
 * 0 for AUX1 : spi_mode0 or spi_mode3
 * 1: spi_mode1 or spi_mode2
 */
#define REG_INTF_AUX_CONFIG_AUX1_SPI_MODE_POS      0x00
#define REG_INTF_AUX_CONFIG_AUX1_SPI_MODE_MASK     0x01

/*
 * aux1_spi_34_mode
 * 1: SPI 4 mode, use SDO pad to send data out for OIS1
 * 0: SPI 3 mode, use SDA pad to send data out for OIS1
 */
#define REG_INTF_AUX_CONFIG_AUX1_SPI_34_MODE_POS      0x01
#define REG_INTF_AUX_CONFIG_AUX1_SPI_34_MODE_MASK     (0x01 << REG_INTF_AUX_CONFIG_AUX1_SPI_34_MODE_POS)

/*
 * aux2_spi_mode
 * SPI Mode based on CPOL and CPHA
 * 0 for AUX2 : spi_mode0 or spi_mode3
 * 1: spi_mode1 or spi_mode2
 */
#define REG_INTF_AUX_CONFIG_AUX2_SPI_MODE_POS      0x02
#define REG_INTF_AUX_CONFIG_AUX2_SPI_MODE_MASK     (0x01 << REG_INTF_AUX_CONFIG_AUX2_SPI_MODE_POS)



/*
 * REG_IOC_PAD_SCENARIO
 * Register Name : IOC_PAD_SCENARIO
 */

/*
 * aux1_enable
 * Aux1 enable :
 * 0: AUX1 disabled
 * 1: AUX1 enabled
 */
#define REG_IOC_PAD_SCENARIO_AUX1_ENABLE_POS      0x00
#define REG_IOC_PAD_SCENARIO_AUX1_ENABLE_MASK     0x01

/*
 * aux1_mode
 * Effective only when 'aux1_enable' is '1'
 * Selects modes at which AUX1 pads could be used
 * 0: AUX1in SPI Slave
 * 1: AUX1 in I2CM Master
 * 2: AUX1 in I2CM Bypass (Enable only when AP is not in SPI mode)
 */
#define REG_IOC_PAD_SCENARIO_AUX1_MODE_POS      0x01
#define REG_IOC_PAD_SCENARIO_AUX1_MODE_MASK     (0x03 << REG_IOC_PAD_SCENARIO_AUX1_MODE_POS)

/*
 * aux2_enable
 * Aux2 enable :
 * 0: AUX2 disabled
 * 1: AUX2 enabled
 */
#define REG_IOC_PAD_SCENARIO_AUX2_ENABLE_POS      0x03
#define REG_IOC_PAD_SCENARIO_AUX2_ENABLE_MASK     (0x01 << REG_IOC_PAD_SCENARIO_AUX2_ENABLE_POS)

/*
 * pads_int2_cfg
 * Effective only when 'aux2_enable' is 0.  Selects how INT2 pads are used
 * 0 : INT2 is selected
 * 1 : FSYNC is selected
 * 2 : CLKIN is selected
 * 3 : DRDY_INTR is selected
 */
#define REG_IOC_PAD_SCENARIO_PADS_INT2_CFG_POS      0x04
#define REG_IOC_PAD_SCENARIO_PADS_INT2_CFG_MASK     (0x03 << REG_IOC_PAD_SCENARIO_PADS_INT2_CFG_POS)

/*
 * REG_IOC_PAD_SCENARIO_AUX_OVRD
 * Register Name : IOC_PAD_SCENARIO_AUX_OVRD
 */

/*
 * aux1_enable_ovrd_val
 * Override value for Aux1 enable :
 * 0: AUX1 disabled
 * 1: AUX1 enabled
 */
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_VAL_POS      0x00
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_VAL_MASK     0x01

/*
 * aux1_enable_ovrd
 * Override enable for aux1_enable
 */
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_POS      0x01
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_MASK     (0x01 << REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_ENABLE_OVRD_POS)

/*
 * aux1_mode_ovrd_val
 * Override value: Effective only when 'aux1_enable' is '1'
 * Selects modes at which AUX1 pads could be used
 * 0: AUX1in SPI Slave
 * 1: AUX1 in I2CM Master
 * 2: AUX1 in I2CM Bypass (Enable only when AP is not in SPI mode)
 *
 * NOTE: When enabling the I2CM bypass, this register should be programmed individually, not a part of a burst transaction.
 */
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_MODE_OVRD_VAL_POS      0x02
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_MODE_OVRD_VAL_MASK     (0x03 << REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_MODE_OVRD_VAL_POS)

/*
 * aux1_mode_ovrd
 * Override enable for aux1_mode
 */
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_MODE_OVRD_POS      0x04
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_MODE_OVRD_MASK     (0x01 << REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX1_MODE_OVRD_POS)

/*
 * aux2_enable_ovrd_val
 * Override value: Aux2 enable :
 * 0: AUX2 disabled
 * 1: AUX2 enabled
 */
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX2_ENABLE_OVRD_VAL_POS      0x05
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX2_ENABLE_OVRD_VAL_MASK     (0x01 << REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX2_ENABLE_OVRD_VAL_POS)

/*
 * aux2_enable_ovrd
 * Override enable for aux2_enable
 */
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX2_ENABLE_OVRD_POS      0x06
#define REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX2_ENABLE_OVRD_MASK     (0x01 << REG_IOC_PAD_SCENARIO_AUX_OVRD_AUX2_ENABLE_OVRD_POS)



/*
 * REG_IOC_PAD_SCENARIO_OVRD
 * Register Name : IOC_PAD_SCENARIO_OVRD
 */

/*
 * pads_int2_cfg_ovrd_val
 * Override value: Effective only when 'aux2_enable' is 0.  Selects how INT2 pads are used
 * 0 : INT2 is selected
 * 1 : FSYNC is selected
 * 2 : CLKIN is selected
 * 3 : DRDY_INTR is selected
 */
#define REG_IOC_PAD_SCENARIO_OVRD_PADS_INT2_CFG_OVRD_VAL_POS      0x00
#define REG_IOC_PAD_SCENARIO_OVRD_PADS_INT2_CFG_OVRD_VAL_MASK     0x03

/*
 * pads_int2_cfg_ovrd
 * Override enable for ioc_pads_int2_cfg
 */
#define REG_IOC_PAD_SCENARIO_OVRD_PADS_INT2_CFG_OVRD_POS      0x02
#define REG_IOC_PAD_SCENARIO_OVRD_PADS_INT2_CFG_OVRD_MASK     (0x01 << REG_IOC_PAD_SCENARIO_OVRD_PADS_INT2_CFG_OVRD_POS)

/*
 * REG_DRIVE_CONFIG0
 * Register Name : DRIVE_CONFIG0
 */

/*
 * virtual_access_aux2_en
 * Virtual access DTP aux2 enable
 * 1 : UI/AP take control of AUX2 interface
 * When the aux2 virtual address mode is enabled, the accessing from the SIFS_AUX2 interface is not supported.
 */
#define REG_DRIVE_CONFIG0_VIRTUAL_ACCESS_AUX2_EN_POS      0x00
#define REG_DRIVE_CONFIG0_VIRTUAL_ACCESS_AUX2_EN_MASK     0x01

/*
 * pads_spi_slew
 * Slew when chip is in SPI protocol. After chip reset, the reg_pads_i2c_slew is used by default.
 * The register setting takes effect at 1.5us after the LSBit is received.
 */
#define REG_DRIVE_CONFIG0_PADS_SPI_SLEW_POS      0x01
#define REG_DRIVE_CONFIG0_PADS_SPI_SLEW_MASK     (0x07 << REG_DRIVE_CONFIG0_PADS_SPI_SLEW_POS)

/*
 * pads_i2c_slew
 * Slew when I2C Legacy slave is selected or when I3C is operating as I2C slave
 * Slew when chip is in I2C protocol. After chip reset, the pads_i2c_slew is used by default. If the 1st operation from host is a SPI transaction, then chip automatically switches to pads_spi_slew automatically. If I3C feature is enabled, chip automatically switches to use pads_sdr_slew after receiving 0x7E+W message (an I3C broadcast message).  The register setting takes effect at 1.5us after the LSBit is received.
 *
 */
#define REG_DRIVE_CONFIG0_PADS_I2C_SLEW_POS      0x04
#define REG_DRIVE_CONFIG0_PADS_I2C_SLEW_MASK     (0x07 << REG_DRIVE_CONFIG0_PADS_I2C_SLEW_POS)



/*
 * REG_DRIVE_CONFIG1
 * Register Name : DRIVE_CONFIG1
 */

/*
 * pads_i3c_sdr_slew
 * Slew when chip is in I3C SDR protocol. After chip reset, the reg_pads_i2c_slew is used by default. If I3C feature is enabled, chip automatically switches to use reg_pads_sdr_slew after receiving 0x7E+W message (an I3C broadcast message). The register setting takes effect at 1.5us after the LSBit is received.
 */
#define REG_DRIVE_CONFIG1_PADS_I3C_SDR_SLEW_POS      0x00
#define REG_DRIVE_CONFIG1_PADS_I3C_SDR_SLEW_MASK     0x07

/*
 * pads_i3c_ddr_slew
 * Slew when chip is in I3C DDR protocol. While in I3C operation, chip automatically switches to use reg_pads_ddr_slew after receiving ENTHDR0 ccc command from host. And chip automatically switches back to reg_pads_sdr_slew after host issues HDR_EXIT pattern. The register setting takes effect at 1.5us after the LSBit is received.
 */
#define REG_DRIVE_CONFIG1_PADS_I3C_DDR_SLEW_POS      0x03
#define REG_DRIVE_CONFIG1_PADS_I3C_DDR_SLEW_MASK     (0x07 << REG_DRIVE_CONFIG1_PADS_I3C_DDR_SLEW_POS)



/*
 * REG_DRIVE_CONFIG2
 * Register Name : DRIVE_CONFIG2
 */

/*
 * pads_slew
 * Slew in all modes (SPI3, SPI4, I2C, I3C) when chip is in OTP-copy operation. Whenever chip is in OTP copy operation, reg_pads_slew is used to control SDO/SDIO pad. After OTP copy is done, the reg_pads_i2c_slew is used by default . If the 1st operation from host is a SPI transaction, then chip switches to pads_spi_slew automatically. The register setting takes effect at 1.5us after the LSBit is received.
 */
#define REG_DRIVE_CONFIG2_PADS_SLEW_POS      0x00
#define REG_DRIVE_CONFIG2_PADS_SLEW_MASK     0x07



/*
 * REG_REG_MISC1
 * Register Name : REG_MISC1
 */

/*
 * osc_id_ovrd
 * Overrides the oscillator ID request (debug feature).  Use this register to select the external clock as the MCLK source.
 * [0] = 1: Requests the EDOSC.
 * [1] = 1: Requests the RCOSC.
 * [2] = 1: Requests the PLL, if it is enabled.
 * [3] = 1: Requests the external clock.
 * The selected clock source is the highest index that's requested and that is ready.
 */
#define REG_REG_MISC1_OSC_ID_OVRD_POS      0x00
#define REG_REG_MISC1_OSC_ID_OVRD_MASK     0x0f

/*
 * REG_INT_APEX_CONFIG0
 * Register Name : INT_APEX_CONFIG0
 */

/*
 * int_status_mask_pin_tap_detect
 *
 * For the tap detection event, this is to enable the interrupt pin assertion when the int_status_tap_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_TAP_DETECT_POS      0x00
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_TAP_DETECT_MASK     0x01

/*
 * int_status_mask_pin_high_g_det
 *
 * For the highG detection event, this is to enable the interrupt pin assertion when the int_status_highG_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_HIGH_G_DET_POS      0x01
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_HIGH_G_DET_MASK     (0x01 << REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_HIGH_G_DET_POS)

/*
 * int_status_mask_pin_low_g_det
 *
 * For the lowG detection event, this is to enable the interrupt pin assertion when the int_status_lowG_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_LOW_G_DET_POS      0x02
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_LOW_G_DET_MASK     (0x01 << REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_LOW_G_DET_POS)

/*
 * int_status_mask_pin_tilt_det
 *
 * For the tilt detection event, this is to enable the interrupt pin assertion when the int_status_tilt_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_TILT_DET_POS      0x03
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_TILT_DET_MASK     (0x01 << REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_TILT_DET_POS)

/*
 * int_status_mask_pin_step_cnt_ovfl
 *
 * For the step count overflow detection event, this is to enable the interrupt pin assertion when the int_status_step_cnt_ovfl_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_STEP_CNT_OVFL_POS      0x04
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_STEP_CNT_OVFL_MASK     (0x01 << REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_STEP_CNT_OVFL_POS)

/*
 * int_status_mask_pin_step_det
 *
 * For the step detection event, this is to enable the interrupt pin assertion when the int_status_step_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_STEP_DET_POS      0x05
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_STEP_DET_MASK     (0x01 << REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_STEP_DET_POS)

/*
 * int_status_mask_pin_ff_det
 *
 * For the freefall detection event, this is to enable the interrupt pin assertion when the int_status_ff_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_FF_DET_POS      0x06
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_FF_DET_MASK     (0x01 << REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_FF_DET_POS)

/*
 * int_status_mask_pin_r2w_wake_det
 *
 * For the wake detection event, this is to enable the interrupt pin assertion when the int_status_wake_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_R2W_WAKE_DET_POS      0x07
#define REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_R2W_WAKE_DET_MASK     (0x01 << REG_INT_APEX_CONFIG0_INT_STATUS_MASK_PIN_R2W_WAKE_DET_POS)



/*
 * REG_INT_APEX_CONFIG1
 * Register Name : INT_APEX_CONFIG1
 */

/*
 * int_status_mask_pin_r2w_sleep_det
 *
 * For the wake sleep detection event, this is to enable the interrupt pin assertion when the int_status_sleep_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_R2W_SLEEP_DET_POS      0x00
#define REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_R2W_SLEEP_DET_MASK     0x01

/*
 * int_status_mask_pin_smd_det
 *
 * For the motion detection event, this is to enable the interrupt pin assertion when the int_status_motion_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SMD_DET_POS      0x01
#define REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SMD_DET_MASK     (0x01 << REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SMD_DET_POS)

/*
 * int_status_mask_pin_selftest_done
 *
 * For the self test done event, this is to enable the interrupt pin assertion when the int_status_selftest_done status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SELFTEST_DONE_POS      0x02
#define REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SELFTEST_DONE_MASK     (0x01 << REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SELFTEST_DONE_POS)

/*
 * int_status_mask_pin_sa_done
 *
 * For the secure authentication done event, this is to enable the interrupt pin assertion when the int_status_sa_done status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SA_DONE_POS      0x04
#define REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SA_DONE_MASK     (0x01 << REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_SA_DONE_POS)

/*
 * int_status_mask_pin_basic_smd
 *
 * For the reserved1 event, this is to enable the interrupt pin assertion when the int_status_r1_detect status bit is 1.
 * 1: No Interrupt pin assertion.
 * 0: enable the Interrupt pin assertion.
 */
#define REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_BASIC_SMD_POS      0x05
#define REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_BASIC_SMD_MASK     (0x01 << REG_INT_APEX_CONFIG1_INT_STATUS_MASK_PIN_BASIC_SMD_POS)

/*
 * REG_INT_APEX_STATUS0
 * Register Name : INT_APEX_STATUS0
 */

/*
 * int_status_tap_det
 * If this interrupt status bit is enabled, this bit is to flag the occurance of Tap detection event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS0_INT_STATUS_TAP_DET_POS      0x00
#define REG_INT_APEX_STATUS0_INT_STATUS_TAP_DET_MASK     0x01

/*
 * int_status_high_g_det
 * If this interrupt status bit is enabled, this bit is to flag the occurance of highG detection event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS0_INT_STATUS_HIGH_G_DET_POS      0x01
#define REG_INT_APEX_STATUS0_INT_STATUS_HIGH_G_DET_MASK     (0x01 << REG_INT_APEX_STATUS0_INT_STATUS_HIGH_G_DET_POS)

/*
 * int_status_low_g_det
 * If this interrupt status bit is enabled, this bit is to flag the occurance of lowG detection event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS0_INT_STATUS_LOW_G_DET_POS      0x02
#define REG_INT_APEX_STATUS0_INT_STATUS_LOW_G_DET_MASK     (0x01 << REG_INT_APEX_STATUS0_INT_STATUS_LOW_G_DET_POS)

/*
 * int_status_tilt_det
 * If this interrupt status bit is enabled, this bit is to flag the occurance of tilt detection event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS0_INT_STATUS_TILT_DET_POS      0x03
#define REG_INT_APEX_STATUS0_INT_STATUS_TILT_DET_MASK     (0x01 << REG_INT_APEX_STATUS0_INT_STATUS_TILT_DET_POS)

/*
 * int_status_step_cnt_ovfl
 * If this interrupt status bit is enabled, this bit is to flag the occurance of stepcount overflow event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS0_INT_STATUS_STEP_CNT_OVFL_POS      0x04
#define REG_INT_APEX_STATUS0_INT_STATUS_STEP_CNT_OVFL_MASK     (0x01 << REG_INT_APEX_STATUS0_INT_STATUS_STEP_CNT_OVFL_POS)

/*
 * int_status_step_det
 * If this interrupt status bit is enabled, this bit is to flag the occurance of step detection event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS0_INT_STATUS_STEP_DET_POS      0x05
#define REG_INT_APEX_STATUS0_INT_STATUS_STEP_DET_MASK     (0x01 << REG_INT_APEX_STATUS0_INT_STATUS_STEP_DET_POS)

/*
 * int_status_ff_det
 * If this interrupt status bit is enabled, this bit is to flag the occurance of freefall event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS0_INT_STATUS_FF_DET_POS      0x06
#define REG_INT_APEX_STATUS0_INT_STATUS_FF_DET_MASK     (0x01 << REG_INT_APEX_STATUS0_INT_STATUS_FF_DET_POS)

/*
 * int_status_r2w_wake_det
 * If this interrupt status bit is enabled, this bit is to flag the occurance of wake wake detection event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS0_INT_STATUS_R2W_WAKE_DET_POS      0x07
#define REG_INT_APEX_STATUS0_INT_STATUS_R2W_WAKE_DET_MASK     (0x01 << REG_INT_APEX_STATUS0_INT_STATUS_R2W_WAKE_DET_POS)



/*
 * REG_INT_APEX_STATUS1
 * Register Name : INT_APEX_STATUS1
 */

/*
 * int_status_r2w_sleep_det
 * If this interrupt status bit is enabled, this bit is to flag the occurance of wake to sleep detection event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS1_INT_STATUS_R2W_SLEEP_DET_POS      0x00
#define REG_INT_APEX_STATUS1_INT_STATUS_R2W_SLEEP_DET_MASK     0x01

/*
 * int_status_smd_det
 * If this interrupt status bit is enabled, this bit is to flag the occurance of SMD event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS1_INT_STATUS_SMD_DET_POS      0x01
#define REG_INT_APEX_STATUS1_INT_STATUS_SMD_DET_MASK     (0x01 << REG_INT_APEX_STATUS1_INT_STATUS_SMD_DET_POS)

/*
 * int_status_selftest_done
 * If this interrupt status bit is enabled, this bit is to flag the occurance of Self test done event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS1_INT_STATUS_SELFTEST_DONE_POS      0x02
#define REG_INT_APEX_STATUS1_INT_STATUS_SELFTEST_DONE_MASK     (0x01 << REG_INT_APEX_STATUS1_INT_STATUS_SELFTEST_DONE_POS)

/*
 * int_status_sa_done
 * For edmp_out Interface. Indicates status register(ISR) for secure authentication done interrupt.
 *
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 */
#define REG_INT_APEX_STATUS1_INT_STATUS_SA_DONE_POS      0x04
#define REG_INT_APEX_STATUS1_INT_STATUS_SA_DONE_MASK     (0x01 << REG_INT_APEX_STATUS1_INT_STATUS_SA_DONE_POS)

/*
 * int_status_basic_smd
 * If this interrupt status bit is enabled, this bit is to flag the occurance of basic SMD event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_APEX_STATUS1_INT_STATUS_BASIC_SMD_POS      0x05
#define REG_INT_APEX_STATUS1_INT_STATUS_BASIC_SMD_MASK     (0x01 << REG_INT_APEX_STATUS1_INT_STATUS_BASIC_SMD_POS)

/*
 * REG_INTF_CONFIG_OVRD_AUX1
 * Register Name : INTF_CONFIG_OVRD_AUX1
 */

/*
 * aux1_spi_mode_ovrd_val
 * Override value for SPI Mode based on CPOL and CPHA
 * 0 for aux1 : spi_mode0 or spi_mode3
 * 1: spi_mode1 or spi_mode2
 * No change is expected from default mode when IxC slave is selected for host serial transfer.
 */
#define REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_MODE_OVRD_VAL_POS      0x00
#define REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_MODE_OVRD_VAL_MASK     0x01

/*
 * aux1_spi_mode_ovrd
 * Override enable for spi_mode register value for aux1
 */
#define REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_MODE_OVRD_POS      0x01
#define REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_MODE_OVRD_MASK     (0x01 << REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_MODE_OVRD_POS)

/*
 * aux1_spi_34_mode_ovrd_val
 * Override value for SPI4/SPI3 modes for OIS1
 * 1: SPI 4 mode, use SDO pad to send data out.
 * 0: SPI 3 mode, use SDA pad to send data out.
 */
#define REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_34_MODE_OVRD_VAL_POS      0x02
#define REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_34_MODE_OVRD_VAL_MASK     (0x01 << REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_34_MODE_OVRD_VAL_POS)

/*
 * aux1_spi_34_mode_ovrd
 * Override enable for SPI4/SPI3 modes for OIS1
 */
#define REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_34_MODE_OVRD_POS      0x03
#define REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_34_MODE_OVRD_MASK     (0x01 << REG_INTF_CONFIG_OVRD_AUX1_AUX1_SPI_34_MODE_OVRD_POS)

/*
 * aux1_ireg_auto_addr_inc_dis
 * This register controls the address auto-increment operation of the 32-bit indirect address when accessing reg_ireg_data from serial interface of AUX1
 * 0: Disable address auto-increment operation to the 32-bit address.
 * 1: Enable address auto-increment operation to the 32-bit address.
 *
 * In write operation, the 32-bit address is auto-incremented by 1 after write to ireg_data is completed.
 * In read operation, the 32-bit address is auto-incremented by 1 after ireg_data read return data is captured into SCLK-domain read-buffer residing in serial interface block.
 * The address auto increment operation stops when the 32-bit address = 0xFFFF_FFFF. Or when write to ireg_addr* occurs.
 */
#define REG_INTF_CONFIG_OVRD_AUX1_AUX1_IREG_AUTO_ADDR_INC_DIS_POS      0x04
#define REG_INTF_CONFIG_OVRD_AUX1_AUX1_IREG_AUTO_ADDR_INC_DIS_MASK     (0x01 << REG_INTF_CONFIG_OVRD_AUX1_AUX1_IREG_AUTO_ADDR_INC_DIS_POS)



/*
 * REG_ACCEL_DATA_X1_AUX1
 * Register Name : ACCEL_DATA_X1_AUX1
 */

/*
 * accel_data_x_aux1
 * Accel X axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_X1_AUX1_ACCEL_DATA_X_AUX1_POS      0x00
#define REG_ACCEL_DATA_X1_AUX1_ACCEL_DATA_X_AUX1_MASK     0xff



/*
 * REG_ACCEL_DATA_X0_AUX1
 * Register Name : ACCEL_DATA_X0_AUX1
 */

/*
 * accel_data_x_aux1
 * Accel X axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_X0_AUX1_ACCEL_DATA_X_AUX1_POS      0x00
#define REG_ACCEL_DATA_X0_AUX1_ACCEL_DATA_X_AUX1_MASK     0xff



/*
 * REG_ACCEL_DATA_Y1_AUX1
 * Register Name : ACCEL_DATA_Y1_AUX1
 */

/*
 * accel_data_y_aux1
 * Accel Y axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Y1_AUX1_ACCEL_DATA_Y_AUX1_POS      0x00
#define REG_ACCEL_DATA_Y1_AUX1_ACCEL_DATA_Y_AUX1_MASK     0xff



/*
 * REG_ACCEL_DATA_Y0_AUX1
 * Register Name : ACCEL_DATA_Y0_AUX1
 */

/*
 * accel_data_y_aux1
 * Accel Y axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Y0_AUX1_ACCEL_DATA_Y_AUX1_POS      0x00
#define REG_ACCEL_DATA_Y0_AUX1_ACCEL_DATA_Y_AUX1_MASK     0xff



/*
 * REG_ACCEL_DATA_Z1_AUX1
 * Register Name : ACCEL_DATA_Z1_AUX1
 */

/*
 * accel_data_z_aux1
 * Accel Z axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Z1_AUX1_ACCEL_DATA_Z_AUX1_POS      0x00
#define REG_ACCEL_DATA_Z1_AUX1_ACCEL_DATA_Z_AUX1_MASK     0xff



/*
 * REG_ACCEL_DATA_Z0_AUX1
 * Register Name : ACCEL_DATA_Z0_AUX1
 */

/*
 * accel_data_z_aux1
 * Accel Z axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Z0_AUX1_ACCEL_DATA_Z_AUX1_POS      0x00
#define REG_ACCEL_DATA_Z0_AUX1_ACCEL_DATA_Z_AUX1_MASK     0xff



/*
 * REG_GYRO_DATA_X1_AUX1
 * Register Name : GYRO_DATA_X1_AUX1
 */

/*
 * gyro_data_x_aux1
 * Gyro X axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_X1_AUX1_GYRO_DATA_X_AUX1_POS      0x00
#define REG_GYRO_DATA_X1_AUX1_GYRO_DATA_X_AUX1_MASK     0xff



/*
 * REG_GYRO_DATA_X0_AUX1
 * Register Name : GYRO_DATA_X0_AUX1
 */

/*
 * gyro_data_x_aux1
 * Gyro X axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_X0_AUX1_GYRO_DATA_X_AUX1_POS      0x00
#define REG_GYRO_DATA_X0_AUX1_GYRO_DATA_X_AUX1_MASK     0xff



/*
 * REG_GYRO_DATA_Y1_AUX1
 * Register Name : GYRO_DATA_Y1_AUX1
 */

/*
 * gyro_data_y_aux1
 * Gyro Y axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Y1_AUX1_GYRO_DATA_Y_AUX1_POS      0x00
#define REG_GYRO_DATA_Y1_AUX1_GYRO_DATA_Y_AUX1_MASK     0xff



/*
 * REG_GYRO_DATA_Y0_AUX1
 * Register Name : GYRO_DATA_Y0_AUX1
 */

/*
 * gyro_data_y_aux1
 * Gyro Y axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Y0_AUX1_GYRO_DATA_Y_AUX1_POS      0x00
#define REG_GYRO_DATA_Y0_AUX1_GYRO_DATA_Y_AUX1_MASK     0xff



/*
 * REG_GYRO_DATA_Z1_AUX1
 * Register Name : GYRO_DATA_Z1_AUX1
 */

/*
 * gyro_data_z_aux1
 * Gyro Z axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Z1_AUX1_GYRO_DATA_Z_AUX1_POS      0x00
#define REG_GYRO_DATA_Z1_AUX1_GYRO_DATA_Z_AUX1_MASK     0xff



/*
 * REG_GYRO_DATA_Z0_AUX1
 * Register Name : GYRO_DATA_Z0_AUX1
 */

/*
 * gyro_data_z_aux1
 * Gyro Z axis data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Z0_AUX1_GYRO_DATA_Z_AUX1_POS      0x00
#define REG_GYRO_DATA_Z0_AUX1_GYRO_DATA_Z_AUX1_MASK     0xff



/*
 * REG_TEMP_DATA1_AUX1
 * Register Name : TEMP_DATA1_AUX1
 */

/*
 * temp_data_aux1
 * Temperature data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TEMP_DATA1_AUX1_TEMP_DATA_AUX1_POS      0x00
#define REG_TEMP_DATA1_AUX1_TEMP_DATA_AUX1_MASK     0xff



/*
 * REG_TEMP_DATA0_AUX1
 * Register Name : TEMP_DATA0_AUX1
 */

/*
 * temp_data_aux1
 * Temperature data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TEMP_DATA0_AUX1_TEMP_DATA_AUX1_POS      0x00
#define REG_TEMP_DATA0_AUX1_TEMP_DATA_AUX1_MASK     0xff



/*
 * REG_TMST_FSYNCH_AUX1
 * Register Name : TMST_FSYNCH_AUX1
 */

/*
 * tmst_fsync_data_aux1
 * Timestamp/FSYNC data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TMST_FSYNCH_AUX1_TMST_FSYNC_DATA_AUX1_POS      0x00
#define REG_TMST_FSYNCH_AUX1_TMST_FSYNC_DATA_AUX1_MASK     0xff



/*
 * REG_TMST_FSYNCL_AUX1
 * Register Name : TMST_FSYNCL_AUX1
 */

/*
 * tmst_fsync_data_aux1
 * Timestamp/FSYNC data for OIS1 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TMST_FSYNCL_AUX1_TMST_FSYNC_DATA_AUX1_POS      0x00
#define REG_TMST_FSYNCL_AUX1_TMST_FSYNC_DATA_AUX1_MASK     0xff



/*
 * REG_PWR_MGMT_AUX1
 * Register Name : PWR_MGMT_AUX1
 */

/*
 * accel_aux1_en
 * [Supports Dynamic Change] Enable the OIS1 interface for the Accelerometer sensor.
 *   0: OFF
 *   1: ON
 */
#define REG_PWR_MGMT_AUX1_ACCEL_AUX1_EN_POS      0x00
#define REG_PWR_MGMT_AUX1_ACCEL_AUX1_EN_MASK     0x01

/*
 * gyro_aux1_en
 * [Supports Dynamic Change] Enable the OIS1 interface for the Gyroscope sensor.
 *   0: OFF
 *   1: ON
 */
#define REG_PWR_MGMT_AUX1_GYRO_AUX1_EN_POS      0x01
#define REG_PWR_MGMT_AUX1_GYRO_AUX1_EN_MASK     (0x01 << REG_PWR_MGMT_AUX1_GYRO_AUX1_EN_POS)

/*
 * REG_FS_SEL_AUX1
 * Register Name : FS_SEL_AUX1
 */

/*
 * accel_aux1_fs_sel
 * [Supports Dynamic Change] Set the OIS1 signal path accel full scale
 * 0 : 32 gee
 * 1 : 16 gee
 * 2 : 8 gee
 * 3 :4 gee
 * 4 : 2 gee
 */
#define REG_FS_SEL_AUX1_ACCEL_AUX1_FS_SEL_POS      0x00
#define REG_FS_SEL_AUX1_ACCEL_AUX1_FS_SEL_MASK     0x07

/*
 * gyro_aux1_fs_sel
 * [Supports Dynamic Change] Set the OIS1 signal path gyro full scale
 * 0 : 4000 dps
 * 1 : 2000 dps
 * 2 : 1000 dps
 * 3 : 500 dps
 * 4 : 250 dps
 * 5 : 125 dps
 * 6 : 62.5 dps
 * 7 : 31.25 dps
 * 8 : 15.625 dps
 */
#define REG_FS_SEL_AUX1_GYRO_AUX1_FS_SEL_POS      0x03
#define REG_FS_SEL_AUX1_GYRO_AUX1_FS_SEL_MASK     (0x0f << REG_FS_SEL_AUX1_GYRO_AUX1_FS_SEL_POS)



/*
 * REG_INT2_CONFIG0
 * Register Name : INT2_CONFIG0
 */

/*
 * int2_status_en_fifo_full
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  FIFO full event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG0_INT2_STATUS_EN_FIFO_FULL_POS      0x00
#define REG_INT2_CONFIG0_INT2_STATUS_EN_FIFO_FULL_MASK     0x01

/*
 * int2_status_en_fifo_ths
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  fifo_data count ≥ fifo_wm_th event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG0_INT2_STATUS_EN_FIFO_THS_POS      0x01
#define REG_INT2_CONFIG0_INT2_STATUS_EN_FIFO_THS_MASK     (0x01 << REG_INT2_CONFIG0_INT2_STATUS_EN_FIFO_THS_POS)

/*
 * int2_status_en_drdy
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  DRDY event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG0_INT2_STATUS_EN_DRDY_POS      0x02
#define REG_INT2_CONFIG0_INT2_STATUS_EN_DRDY_MASK     (0x01 << REG_INT2_CONFIG0_INT2_STATUS_EN_DRDY_POS)

/*
 * int2_status_en_aux1_drdy
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  AUX1 DRDY event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG0_INT2_STATUS_EN_AUX1_DRDY_POS      0x03
#define REG_INT2_CONFIG0_INT2_STATUS_EN_AUX1_DRDY_MASK     (0x01 << REG_INT2_CONFIG0_INT2_STATUS_EN_AUX1_DRDY_POS)

/*
 * int2_status_en_ap_fsync
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  FSYNC event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG0_INT2_STATUS_EN_AP_FSYNC_POS      0x04
#define REG_INT2_CONFIG0_INT2_STATUS_EN_AP_FSYNC_MASK     (0x01 << REG_INT2_CONFIG0_INT2_STATUS_EN_AP_FSYNC_POS)

/*
 * int2_status_en_ap_agc_rdy
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  AGC Ready event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG0_INT2_STATUS_EN_AP_AGC_RDY_POS      0x05
#define REG_INT2_CONFIG0_INT2_STATUS_EN_AP_AGC_RDY_MASK     (0x01 << REG_INT2_CONFIG0_INT2_STATUS_EN_AP_AGC_RDY_POS)

/*
 * int2_status_en_aux1_agc_rdy
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  OIS1 AGC Ready event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG0_INT2_STATUS_EN_AUX1_AGC_RDY_POS      0x06
#define REG_INT2_CONFIG0_INT2_STATUS_EN_AUX1_AGC_RDY_MASK     (0x01 << REG_INT2_CONFIG0_INT2_STATUS_EN_AUX1_AGC_RDY_POS)

/*
 * int2_status_en_reset_done
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  Reset done event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG0_INT2_STATUS_EN_RESET_DONE_POS      0x07
#define REG_INT2_CONFIG0_INT2_STATUS_EN_RESET_DONE_MASK     (0x01 << REG_INT2_CONFIG0_INT2_STATUS_EN_RESET_DONE_POS)



/*
 * REG_INT2_CONFIG1
 * Register Name : INT2_CONFIG1
 */

/*
 * int2_status_en_pll_rdy
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  PLL ready event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG1_INT2_STATUS_EN_PLL_RDY_POS      0x00
#define REG_INT2_CONFIG1_INT2_STATUS_EN_PLL_RDY_MASK     0x01

/*
 * int2_status_en_wom_x
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  WOM on X-axis event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG1_INT2_STATUS_EN_WOM_X_POS      0x01
#define REG_INT2_CONFIG1_INT2_STATUS_EN_WOM_X_MASK     (0x01 << REG_INT2_CONFIG1_INT2_STATUS_EN_WOM_X_POS)

/*
 * int2_status_en_wom_y
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  WOM on Y-axis event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG1_INT2_STATUS_EN_WOM_Y_POS      0x02
#define REG_INT2_CONFIG1_INT2_STATUS_EN_WOM_Y_MASK     (0x01 << REG_INT2_CONFIG1_INT2_STATUS_EN_WOM_Y_POS)

/*
 * int2_status_en_wom_z
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  WOM on Z-axis event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG1_INT2_STATUS_EN_WOM_Z_POS      0x03
#define REG_INT2_CONFIG1_INT2_STATUS_EN_WOM_Z_MASK     (0x01 << REG_INT2_CONFIG1_INT2_STATUS_EN_WOM_Z_POS)

/*
 * int2_status_en_i3c_protocol_err
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  i3c protocol error event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG1_INT2_STATUS_EN_I3C_PROTOCOL_ERR_POS      0x04
#define REG_INT2_CONFIG1_INT2_STATUS_EN_I3C_PROTOCOL_ERR_MASK     (0x01 << REG_INT2_CONFIG1_INT2_STATUS_EN_I3C_PROTOCOL_ERR_POS)

/*
 * int2_status_en_i2cm_done
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of  i2c master operation completed event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG1_INT2_STATUS_EN_I2CM_DONE_POS      0x05
#define REG_INT2_CONFIG1_INT2_STATUS_EN_I2CM_DONE_MASK     (0x01 << REG_INT2_CONFIG1_INT2_STATUS_EN_I2CM_DONE_POS)

/*
 * int2_status_en_apex_event
 * For UI/AP interface, Enable interrupt status bit to flag the occurances of edmp event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT2_CONFIG1_INT2_STATUS_EN_APEX_EVENT_POS      0x06
#define REG_INT2_CONFIG1_INT2_STATUS_EN_APEX_EVENT_MASK     (0x01 << REG_INT2_CONFIG1_INT2_STATUS_EN_APEX_EVENT_POS)



/*
 * REG_INT2_CONFIG2
 * Register Name : INT2_CONFIG2
 */

/*
 * int2_polarity
 * UI/AP interface: Interrupt polarity.
 * 0: active low,
 * 1: active high,
 * Setting can be changed only when all interrupts of the corresponding serial interface are disabled.
 */
#define REG_INT2_CONFIG2_INT2_POLARITY_POS      0x00
#define REG_INT2_CONFIG2_INT2_POLARITY_MASK     0x01

/*
 * int2_mode
 * "UI/AP interface: Interrupt mode.
 * 0: pulse mode,
 * 1: latch mode,
 * Setting can be changed only when all interrupts of the corresponding serial interface are disabled."
 *
 */
#define REG_INT2_CONFIG2_INT2_MODE_POS      0x01
#define REG_INT2_CONFIG2_INT2_MODE_MASK     (0x01 << REG_INT2_CONFIG2_INT2_MODE_POS)

/*
 * int2_drive
 * Sets INT1 PAD in to Open-drain or Push-pull
 * 1 : Open-drain
 * 0 : Push-pull
 */
#define REG_INT2_CONFIG2_INT2_DRIVE_POS      0x02
#define REG_INT2_CONFIG2_INT2_DRIVE_MASK     (0x01 << REG_INT2_CONFIG2_INT2_DRIVE_POS)



/*
 * REG_INT2_STATUS0
 * Register Name : INT2_STATUS0
 */

/*
 * int2_status_fifo_full
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of FIFO full event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS0_INT2_STATUS_FIFO_FULL_POS      0x00
#define REG_INT2_STATUS0_INT2_STATUS_FIFO_FULL_MASK     0x01

/*
 * int2_status_fifo_ths
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of fifo_data_cnt ≥ fifo_wm_th event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS0_INT2_STATUS_FIFO_THS_POS      0x01
#define REG_INT2_STATUS0_INT2_STATUS_FIFO_THS_MASK     (0x01 << REG_INT2_STATUS0_INT2_STATUS_FIFO_THS_POS)

/*
 * int2_status_drdy
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of Data Ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS0_INT2_STATUS_DRDY_POS      0x02
#define REG_INT2_STATUS0_INT2_STATUS_DRDY_MASK     (0x01 << REG_INT2_STATUS0_INT2_STATUS_DRDY_POS)

/*
 * int2_status_aux1_drdy
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of AUX1 data ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS0_INT2_STATUS_AUX1_DRDY_POS      0x03
#define REG_INT2_STATUS0_INT2_STATUS_AUX1_DRDY_MASK     (0x01 << REG_INT2_STATUS0_INT2_STATUS_AUX1_DRDY_POS)

/*
 * int2_status_ap_fsync
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of FSYNC event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS0_INT2_STATUS_AP_FSYNC_POS      0x04
#define REG_INT2_STATUS0_INT2_STATUS_AP_FSYNC_MASK     (0x01 << REG_INT2_STATUS0_INT2_STATUS_AP_FSYNC_POS)

/*
 * int2_status_ap_agc_rdy
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of AGC Ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS0_INT2_STATUS_AP_AGC_RDY_POS      0x05
#define REG_INT2_STATUS0_INT2_STATUS_AP_AGC_RDY_MASK     (0x01 << REG_INT2_STATUS0_INT2_STATUS_AP_AGC_RDY_POS)

/*
 * int2_status_aux1_agc_rdy
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of AUX1 AGC Ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS0_INT2_STATUS_AUX1_AGC_RDY_POS      0x06
#define REG_INT2_STATUS0_INT2_STATUS_AUX1_AGC_RDY_MASK     (0x01 << REG_INT2_STATUS0_INT2_STATUS_AUX1_AGC_RDY_POS)

/*
 * int2_status_reset_done
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of Reset event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS0_INT2_STATUS_RESET_DONE_POS      0x07
#define REG_INT2_STATUS0_INT2_STATUS_RESET_DONE_MASK     (0x01 << REG_INT2_STATUS0_INT2_STATUS_RESET_DONE_POS)



/*
 * REG_INT2_STATUS1
 * Register Name : INT2_STATUS1
 */

/*
 * int2_status_pll_rdy
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of PLL ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS1_INT2_STATUS_PLL_RDY_POS      0x00
#define REG_INT2_STATUS1_INT2_STATUS_PLL_RDY_MASK     0x01

/*
 * int2_status_wom_x
 * For UI/AP interface,If this interrupt status bit is enabled, this bit is to flag the occurance of WOM event on X axis.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS1_INT2_STATUS_WOM_X_POS      0x01
#define REG_INT2_STATUS1_INT2_STATUS_WOM_X_MASK     (0x01 << REG_INT2_STATUS1_INT2_STATUS_WOM_X_POS)

/*
 * int2_status_wom_y
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of WOM event on Y axis.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS1_INT2_STATUS_WOM_Y_POS      0x02
#define REG_INT2_STATUS1_INT2_STATUS_WOM_Y_MASK     (0x01 << REG_INT2_STATUS1_INT2_STATUS_WOM_Y_POS)

/*
 * int2_status_wom_z
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of WOM event on Z axis.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS1_INT2_STATUS_WOM_Z_POS      0x03
#define REG_INT2_STATUS1_INT2_STATUS_WOM_Z_MASK     (0x01 << REG_INT2_STATUS1_INT2_STATUS_WOM_Z_POS)

/*
 * int2_status_i3c_protocol_err
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of I3C protocol error event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS1_INT2_STATUS_I3C_PROTOCOL_ERR_POS      0x04
#define REG_INT2_STATUS1_INT2_STATUS_I3C_PROTOCOL_ERR_MASK     (0x01 << REG_INT2_STATUS1_INT2_STATUS_I3C_PROTOCOL_ERR_POS)

/*
 * int2_status_i2cm_done
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of I2C Master done event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS1_INT2_STATUS_I2CM_DONE_POS      0x05
#define REG_INT2_STATUS1_INT2_STATUS_I2CM_DONE_MASK     (0x01 << REG_INT2_STATUS1_INT2_STATUS_I2CM_DONE_POS)

/*
 * int2_status_apex_event
 * For UI/AP interface, If this interrupt status bit is enabled, this bit is to flag the occurance of edmp event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT2_STATUS1_INT2_STATUS_APEX_EVENT_POS      0x06
#define REG_INT2_STATUS1_INT2_STATUS_APEX_EVENT_MASK     (0x01 << REG_INT2_STATUS1_INT2_STATUS_APEX_EVENT_POS)



/*
 * REG_INTF_CONFIG_OVRD_AUX2
 * Register Name : INTF_CONFIG_OVRD_AUX2
 */

/*
 * aux2_spi_mode_ovrd_val
 * Override value for SPI Mode based on CPOL and CPHA
 * 0 for aux1 : spi_mode0 or spi_mode3
 * 1: spi_mode1 or spi_mode2
 * No change is expected from default mode when IxC slave is selected for host serial transfer.
 */
#define REG_INTF_CONFIG_OVRD_AUX2_AUX2_SPI_MODE_OVRD_VAL_POS      0x00
#define REG_INTF_CONFIG_OVRD_AUX2_AUX2_SPI_MODE_OVRD_VAL_MASK     0x01

/*
 * aux2_spi_mode_ovrd
 * Override enable for spi_mode register value for aux2
 */
#define REG_INTF_CONFIG_OVRD_AUX2_AUX2_SPI_MODE_OVRD_POS      0x01
#define REG_INTF_CONFIG_OVRD_AUX2_AUX2_SPI_MODE_OVRD_MASK     (0x01 << REG_INTF_CONFIG_OVRD_AUX2_AUX2_SPI_MODE_OVRD_POS)

/*
 * aux2_ireg_auto_addr_inc_dis
 * This register controls the address auto-increment operation of the 32-bit indirect address when accessing reg_ireg_data from serial interface of AUX1
 * 0: Disable address auto-increment operation to the 32-bit address.
 * 1: Enable address auto-increment operation to the 32-bit address.
 *
 * In write operation, the 32-bit address is auto-incremented by 1 after write to ireg_data is completed.
 * In read operation, the 32-bit address is auto-incremented by 1 after ireg_data read return data is captured into SCLK-domain read-buffer residing in serial interface block.
 * The address auto increment operation stops when the 32-bit address = 0xFFFF_FFFF. Or when write to ireg_addr* occurs.
 */
#define REG_INTF_CONFIG_OVRD_AUX2_AUX2_IREG_AUTO_ADDR_INC_DIS_POS      0x02
#define REG_INTF_CONFIG_OVRD_AUX2_AUX2_IREG_AUTO_ADDR_INC_DIS_MASK     (0x01 << REG_INTF_CONFIG_OVRD_AUX2_AUX2_IREG_AUTO_ADDR_INC_DIS_POS)



/*
 * REG_ACCEL_DATA_X1_AUX2
 * Register Name : ACCEL_DATA_X1_AUX2
 */

/*
 * accel_data_x_aux2
 * Accel X axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_X1_AUX2_ACCEL_DATA_X_AUX2_POS      0x00
#define REG_ACCEL_DATA_X1_AUX2_ACCEL_DATA_X_AUX2_MASK     0xff



/*
 * REG_ACCEL_DATA_X0_AUX2
 * Register Name : ACCEL_DATA_X0_AUX2
 */

/*
 * accel_data_x_aux2
 * Accel X axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_X0_AUX2_ACCEL_DATA_X_AUX2_POS      0x00
#define REG_ACCEL_DATA_X0_AUX2_ACCEL_DATA_X_AUX2_MASK     0xff



/*
 * REG_ACCEL_DATA_Y1_AUX2
 * Register Name : ACCEL_DATA_Y1_AUX2
 */

/*
 * accel_data_y_aux2
 * Accel Y axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Y1_AUX2_ACCEL_DATA_Y_AUX2_POS      0x00
#define REG_ACCEL_DATA_Y1_AUX2_ACCEL_DATA_Y_AUX2_MASK     0xff



/*
 * REG_ACCEL_DATA_Y0_AUX2
 * Register Name : ACCEL_DATA_Y0_AUX2
 */

/*
 * accel_data_y_aux2
 * Accel Y axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Y0_AUX2_ACCEL_DATA_Y_AUX2_POS      0x00
#define REG_ACCEL_DATA_Y0_AUX2_ACCEL_DATA_Y_AUX2_MASK     0xff



/*
 * REG_ACCEL_DATA_Z1_AUX2
 * Register Name : ACCEL_DATA_Z1_AUX2
 */

/*
 * accel_data_z_aux2
 * Accel Z axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Z1_AUX2_ACCEL_DATA_Z_AUX2_POS      0x00
#define REG_ACCEL_DATA_Z1_AUX2_ACCEL_DATA_Z_AUX2_MASK     0xff



/*
 * REG_ACCEL_DATA_Z0_AUX2
 * Register Name : ACCEL_DATA_Z0_AUX2
 */

/*
 * accel_data_z_aux2
 * Accel Z axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_ACCEL_DATA_Z0_AUX2_ACCEL_DATA_Z_AUX2_POS      0x00
#define REG_ACCEL_DATA_Z0_AUX2_ACCEL_DATA_Z_AUX2_MASK     0xff



/*
 * REG_GYRO_DATA_X1_AUX2
 * Register Name : GYRO_DATA_X1_AUX2
 */

/*
 * gyro_data_x_aux2
 * Gyro X axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_X1_AUX2_GYRO_DATA_X_AUX2_POS      0x00
#define REG_GYRO_DATA_X1_AUX2_GYRO_DATA_X_AUX2_MASK     0xff



/*
 * REG_GYRO_DATA_X0_AUX2
 * Register Name : GYRO_DATA_X0_AUX2
 */

/*
 * gyro_data_x_aux2
 * Gyro X axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_X0_AUX2_GYRO_DATA_X_AUX2_POS      0x00
#define REG_GYRO_DATA_X0_AUX2_GYRO_DATA_X_AUX2_MASK     0xff



/*
 * REG_GYRO_DATA_Y1_AUX2
 * Register Name : GYRO_DATA_Y1_AUX2
 */

/*
 * gyro_data_y_aux2
 * Gyro Y axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Y1_AUX2_GYRO_DATA_Y_AUX2_POS      0x00
#define REG_GYRO_DATA_Y1_AUX2_GYRO_DATA_Y_AUX2_MASK     0xff



/*
 * REG_GYRO_DATA_Y0_AUX2
 * Register Name : GYRO_DATA_Y0_AUX2
 */

/*
 * gyro_data_y_aux2
 * Gyro Y axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Y0_AUX2_GYRO_DATA_Y_AUX2_POS      0x00
#define REG_GYRO_DATA_Y0_AUX2_GYRO_DATA_Y_AUX2_MASK     0xff



/*
 * REG_GYRO_DATA_Z1_AUX2
 * Register Name : GYRO_DATA_Z1_AUX2
 */

/*
 * gyro_data_z_aux2
 * Gyro Z axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Z1_AUX2_GYRO_DATA_Z_AUX2_POS      0x00
#define REG_GYRO_DATA_Z1_AUX2_GYRO_DATA_Z_AUX2_MASK     0xff



/*
 * REG_GYRO_DATA_Z0_AUX2
 * Register Name : GYRO_DATA_Z0_AUX2
 */

/*
 * gyro_data_z_aux2
 * Gyro Z axis data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_GYRO_DATA_Z0_AUX2_GYRO_DATA_Z_AUX2_POS      0x00
#define REG_GYRO_DATA_Z0_AUX2_GYRO_DATA_Z_AUX2_MASK     0xff



/*
 * REG_TEMP_DATA1_AUX2
 * Register Name : TEMP_DATA1_AUX2
 */

/*
 * temp_data_aux2
 * Temperature data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TEMP_DATA1_AUX2_TEMP_DATA_AUX2_POS      0x00
#define REG_TEMP_DATA1_AUX2_TEMP_DATA_AUX2_MASK     0xff



/*
 * REG_TEMP_DATA0_AUX2
 * Register Name : TEMP_DATA0_AUX2
 */

/*
 * temp_data_aux2
 * Temperature data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TEMP_DATA0_AUX2_TEMP_DATA_AUX2_POS      0x00
#define REG_TEMP_DATA0_AUX2_TEMP_DATA_AUX2_MASK     0xff



/*
 * REG_TMST_FSYNCH_AUX2
 * Register Name : TMST_FSYNCH_AUX2
 */

/*
 * tmst_fsync_data_aux2
 * Timestamp/FSYNC data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TMST_FSYNCH_AUX2_TMST_FSYNC_DATA_AUX2_POS      0x00
#define REG_TMST_FSYNCH_AUX2_TMST_FSYNC_DATA_AUX2_MASK     0xff



/*
 * REG_TMST_FSYNCL_AUX2
 * Register Name : TMST_FSYNCL_AUX2
 */

/*
 * tmst_fsync_data_aux2
 * Timestamp/FSYNC data for OIS2 path. The POR default value is returned when chip is in idle mode, or in ULP mode with Accel sensor enabled only (or Accel ULP mode). Sensor data can only be retrieved from the FIFO when chip in Accel ULP mode.
 */
#define REG_TMST_FSYNCL_AUX2_TMST_FSYNC_DATA_AUX2_POS      0x00
#define REG_TMST_FSYNCL_AUX2_TMST_FSYNC_DATA_AUX2_MASK     0xff



/*
 * REG_PWR_MGMT_AUX2
 * Register Name : PWR_MGMT_AUX2
 */

/*
 * accel_aux2_en
 * [Supports Dynamic Change] Enable the OIS2 interface for the Accelerometer sensor.
 *   0: OFF
 *   1: ON
 */
#define REG_PWR_MGMT_AUX2_ACCEL_AUX2_EN_POS      0x00
#define REG_PWR_MGMT_AUX2_ACCEL_AUX2_EN_MASK     0x01

/*
 * gyro_aux2_en
 * [Supports Dynamic Change] Enable the OIS2 interface for the Gyroscope sensor.
 *   0: OFF
 *   1: ON
 */
#define REG_PWR_MGMT_AUX2_GYRO_AUX2_EN_POS      0x01
#define REG_PWR_MGMT_AUX2_GYRO_AUX2_EN_MASK     (0x01 << REG_PWR_MGMT_AUX2_GYRO_AUX2_EN_POS)

/*
 * REG_FS_SEL_AUX2
 * Register Name : FS_SEL_AUX2
 */

/*
 * accel_aux2_fs_sel
 * [Supports Dynamic Change] Set the OIS2 signal path accel full scale
 * 0 : 32 gee
 * 1 : 16 gee
 * 2 : 8 gee
 * 3 :4 gee
 * 4 : 2 gee
 */
#define REG_FS_SEL_AUX2_ACCEL_AUX2_FS_SEL_POS      0x00
#define REG_FS_SEL_AUX2_ACCEL_AUX2_FS_SEL_MASK     0x07

/*
 * gyro_aux2_fs_sel
 * [Supports Dynamic Change] Set the OIS2 signal path gyro full scale
 * 0 : 4000 dps
 * 1 : 2000 dps
 * 2 : 1000 dps
 * 3 : 500 dps
 * 4 : 250 dps
 * 5 : 125 dps
 * 6 : 62.5 dps
 * 7 : 31.25 dps
 * 8 : 15.625 dps
 */
#define REG_FS_SEL_AUX2_GYRO_AUX2_FS_SEL_POS      0x03
#define REG_FS_SEL_AUX2_GYRO_AUX2_FS_SEL_MASK     (0x0f << REG_FS_SEL_AUX2_GYRO_AUX2_FS_SEL_POS)



/*
 * REG_INT_AUX2_CONFIG
 * Register Name : INT_AUX2_CONFIG
 */

/*
 * int_en_aux2_agc_rdy
 * For AUX2 interface, Enable interrupt status bit to flag the occurances of  AGC ready event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT_AUX2_CONFIG_INT_EN_AUX2_AGC_RDY_POS      0x00
#define REG_INT_AUX2_CONFIG_INT_EN_AUX2_AGC_RDY_MASK     0x01

/*
 * int_en_aux2_reset_done
 * For AUX2 interface, Enable interrupt status bit to flag the occurances of  Reset done event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT_AUX2_CONFIG_INT_EN_AUX2_RESET_DONE_POS      0x01
#define REG_INT_AUX2_CONFIG_INT_EN_AUX2_RESET_DONE_MASK     (0x01 << REG_INT_AUX2_CONFIG_INT_EN_AUX2_RESET_DONE_POS)

/*
 * int_en_aux2_pll_rdy
 * For AUX2 interface, Enable interrupt status bit to flag the occurances of  PLL ready event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT_AUX2_CONFIG_INT_EN_AUX2_PLL_RDY_POS      0x02
#define REG_INT_AUX2_CONFIG_INT_EN_AUX2_PLL_RDY_MASK     (0x01 << REG_INT_AUX2_CONFIG_INT_EN_AUX2_PLL_RDY_POS)

/*
 * int_en_aux2_drdy
 * For AUX2 interface, Enable interrupt status bit to flag the occurances of  AUX2 AGC ready event.
 *
 * 1: Source enabled.
 * 0: Source disabled.
 *
 * [Reg block function] Setting can be changed by both UI/AP and the corresponding serial interface (AUX1 or AUX2 or MCU).   "
 *
 */
#define REG_INT_AUX2_CONFIG_INT_EN_AUX2_DRDY_POS      0x03
#define REG_INT_AUX2_CONFIG_INT_EN_AUX2_DRDY_MASK     (0x01 << REG_INT_AUX2_CONFIG_INT_EN_AUX2_DRDY_POS)



/*
 * REG_INT_AUX2_STATUS
 * Register Name : INT_AUX2_STATUS
 */

/*
 * int_status_aux2_agc_rdy
 * For AUX2 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of AUX2 AGC ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_AUX2_STATUS_INT_STATUS_AUX2_AGC_RDY_POS      0x00
#define REG_INT_AUX2_STATUS_INT_STATUS_AUX2_AGC_RDY_MASK     0x01

/*
 * int_status_aux2_reset_done
 * For AUX2 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of reset done event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_AUX2_STATUS_INT_STATUS_AUX2_RESET_DONE_POS      0x01
#define REG_INT_AUX2_STATUS_INT_STATUS_AUX2_RESET_DONE_MASK     (0x01 << REG_INT_AUX2_STATUS_INT_STATUS_AUX2_RESET_DONE_POS)

/*
 * int_status_aux2_pll_rdy
 * For AUX2 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of PLL ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_AUX2_STATUS_INT_STATUS_AUX2_PLL_RDY_POS      0x02
#define REG_INT_AUX2_STATUS_INT_STATUS_AUX2_PLL_RDY_MASK     (0x01 << REG_INT_AUX2_STATUS_INT_STATUS_AUX2_PLL_RDY_POS)

/*
 * int_status_aux2_drdy
 * For AUX2 interface, If this interrupt status bit is enabled, this bit is to flag the occurance of AUX2 Data ready event.
 *
 * 1: Interrupt occurred.
 * 0: Interrupt did not occur.
 *
 * “The interrupt pin de-assertion operation assumes the interrupt status registers assigned to consecutive addresses are read in one single burst transaction.”
 */
#define REG_INT_AUX2_STATUS_INT_STATUS_AUX2_DRDY_POS      0x03
#define REG_INT_AUX2_STATUS_INT_STATUS_AUX2_DRDY_MASK     (0x01 << REG_INT_AUX2_STATUS_INT_STATUS_AUX2_DRDY_POS)



/*
 * REG_WHO_AM_I
 * Register Name : WHO_AM_I
 */

/*
 * who_am_i
 * TDK Chip ID
 */
#define REG_WHO_AM_I_WHO_AM_I_POS      0x00
#define REG_WHO_AM_I_WHO_AM_I_MASK     0xff



/*
 * REG_REG_HOST_MSG
 * Register Name : REG_HOST_MSG
 */

/*
 * testopenable
 * [Supports Dynamic Change] 1: Enable test op, Read SRAM to know if the test op is for self-test(A/G) or for self-cal(A/G)
 */
#define REG_REG_HOST_MSG_TESTOPENABLE_POS      0x00
#define REG_REG_HOST_MSG_TESTOPENABLE_MASK     0x01

/*
 * edmp_on_demand_en
 * Set 1 to create pulse to set int_status_edmp_on_demand_pin_0,
 * int_status_edmp_on_demand_pin_1,
 * Int_status_edmp_on_demand_pin_2 to 1
 */
#define REG_REG_HOST_MSG_EDMP_ON_DEMAND_EN_POS      0x05
#define REG_REG_HOST_MSG_EDMP_ON_DEMAND_EN_MASK     (0x01 << REG_REG_HOST_MSG_EDMP_ON_DEMAND_EN_POS)

/*
 * REG_IREG_ADDR_15_8
 * Register Name : IREG_ADDR_15_8
 */

/*
 * ireg_addr_15_8
 * [Supports Dynamic Change] DREG register for holding indirect access of IREG . Bits [15:8]
 *
 * If (1) CS_N=1 when in SPI, or (2) STOP when in IxC, is followed after a write operation to this register, then a read-prefetching operation to IREG is kicked off with new address.
 *
 * Poll register ireg_ireg_done to confirm that it is '1' before writing to this register.
 */
#define REG_IREG_ADDR_15_8_IREG_ADDR_15_8_POS      0x00
#define REG_IREG_ADDR_15_8_IREG_ADDR_15_8_MASK     0xff



/*
 * REG_IREG_ADDR_7_0
 * Register Name : IREG_ADDR_7_0
 */

/*
 * ireg_addr_7_0
 * [Supports Dynamic Change] DREG register for holding indirect access of IREG . Bits [7:0]
 *
 * If (1) CS_N=1 when in SPI, or (2) STOP when in IxC, is followed after a write operation to this register, then a read-prefetching operation to IREG is kicked off with new address.
 *
 * Poll register ireg_ireg_done to confirm that it is '1' before writing to this register.
 */
#define REG_IREG_ADDR_7_0_IREG_ADDR_7_0_POS      0x00
#define REG_IREG_ADDR_7_0_IREG_ADDR_7_0_MASK     0xff



/*
 * REG_IREG_DATA
 * Register Name : IREG_DATA
 */

/*
 * ireg_data
 * [Supports Dynamic Change] DREG register for holding indirect access IREG data. Address bit LSB = 0
 *
 * A write operation to this register kicks off a write operation to IREG with the 32-bit indirect address, waiting for CS_N=1 (SPI) or STOP (IxC).
 * A read operation to this register kicks off a read-prefetching operation to IREG with the 32-bit indirect address, waiting for CS_N=1 (SPI) or STOP (I2C).
 *
 * In both write and read operations to IREG, whether auto-incremented 32-bit indirect address is used or not depends on the setting of reg_ireg_auto_addr_inc_dis register.
 *
 * A read to reg_ireg_data gets result from previous read-prefetching operation to IREG, not the value from previous write operation to reg_ireg_data.
 *
 * The DREG address auto increment stops when pointing to this register.
 *
 * Poll register ireg_ireg_done to confirm that it is '1' before writing/reading to/from this register.
 */
#define REG_IREG_DATA_IREG_DATA_POS      0x00
#define REG_IREG_DATA_IREG_DATA_MASK     0xff



/*
 * REG_REG_MISC2
 * Register Name : REG_MISC2
 */

/*
 * ireg_done
 * [Supports Dynamic Change] 0: Indicates an ongoing IREG operation using the indirect addressing scheme. A new IREG access should not be issued till the current one is completed.
 * 1: Indicates that the IREG operation has been completed. The chip is ready to service the next IREG access request.
 *
 * Register access is disabled when in any of the following conditions: (1) When in the reset state (2) During an OTP copy operation. (when 'otp_done' register field is de-asserted)
 *
 * To write to IREG, the ireg_addr_15_8, ireg_addr_7_0,  and ireg_data need to be programmed with one burst write operation. This is not to kick off an un-intentional read-prefetch operation.
 *
 * To read IREG, the ireg_addr_15_8, ireg_addr_7_0 needs to be programmed with one burst write operation, This is not to kick off an un-intentional read-prefetch operation. Users must then wait for 'ireg_done' to assert, before reading the pre-fetched data from the ireg_data register.
 *
 * The minimum time gap between two consecutive IREG accesses is 4us. Alternatively, instead of polling the ierg_data for the IREG access completion confirmation, users can choose to wait for a min of 4us between two consecutive back-to-back IREG access.
 *
 *
 */
#define REG_REG_MISC2_IREG_DONE_POS      0x00
#define REG_REG_MISC2_IREG_DONE_MASK     0x01

/*
 * soft_rst
 * [Supports Dynamic Change] Soft reset from Host.
 */
#define REG_REG_MISC2_SOFT_RST_POS      0x01
#define REG_REG_MISC2_SOFT_RST_MASK     (0x01 << REG_REG_MISC2_SOFT_RST_POS)


/* ---------------------------------------------------------------------------
 * register DREG_BANK2
 * ---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif  /*#ifndef _REG_EXTERNAL_H_*/
