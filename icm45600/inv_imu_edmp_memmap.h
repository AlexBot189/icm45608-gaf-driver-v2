/*
 * ________________________________________________________________________________________________________
 * Copyright © 2021 InvenSense Inc. All rights reserved.
 *
 * This software, related documentation and any modifications thereto (collectively “Software”) is subject
 * to InvenSense and its licensors' intellectual property rights under U.S. and international copyright
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
 * OF THE SOFTWARE.
 *
 * ________________________________________________________________________________________________________
 */

#ifndef __INV_IMU_EDMP_MEMMAP_H__
#define __INV_IMU_EDMP_MEMMAP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ped_amp_th
 *
 * Threshold on the absolute value of the filtered accelerometer, above which a valid step will be counted.
 * Unit: LSB with 1 LSB = 1 g/225 from accel filtered value.
 * Range: [1006632 - 3019898]
 * Default value: 2080374
 * Recommendation: at lower value, smoother steps can be detected.
 */
#define EDMP_PED_AMP_TH                                         0x3f0
#define EDMP_PED_AMP_TH_SIZE                                    4

/* ped_step_cnt_th
 *
 * Minimum number of steps needed to be buffered before starting to increment step count in real time.
 * Unit: number of steps
 * Range: [0-15] 
 * Default value: 5
 * Recommendation: for a better rejection rate the value can be increased. Keep in mind that if the user does less steps that the value, these steps will not be counted.
 */
#define EDMP_PED_STEP_CNT_TH                                    0x3dc
#define EDMP_PED_STEP_CNT_TH_SIZE                               2

/* ped_prev_step_cnt_th
 *
 * Intermediate number of steps needed to be buffered waiting the internal counting reached the ped_step_cnt_th (when ped_prev_step_cnt_th is lower than ped_step_cnt_th).
 * Note: as soon as ped_step_cnt_th is reached ped_prev_step_cnt_th value is set to ped_step_cnt_th.
 * Unit: number of steps
 * Range: [0-15]
 * Default value: 5
 * Recommendation: set same value as ped_step_cnt_th.
 */
#define EDMP_PED_PREV_STEP_CNT_TH                               0x352
#define EDMP_PED_PREV_STEP_CNT_TH_SIZE                          2

/* ped_step_det_th
 *
 * Minimum number of steps needed to be initially detected before starting to report instantaneous step events.
 * Unit: number of steps
 * Range: [0-7] 
 * Default value: 2
 * Recommendation: for a better rejection rate the value can be increased.
 */
#define EDMP_PED_STEP_DET_TH                                    0x3de
#define EDMP_PED_STEP_DET_TH_SIZE                               2

/* ped_sb_timer_th
 *
 * Maximum permitted time between two consecutive steps.
 * While in the step buffer state, the step buffer count resets to 0 if a new step isnâ€™t detected for this amount of time (user is considered to have "stopped walking")
 * Unit: time in samples number
 * Range: [0 - 225] 
 * Default value: 150 for ODR = 50 Hz
 * Recommendation: it is linked to stop and go use case to avoid seeing the impact of pedo_step_cnt_thr and pedo_step_det_thr
 */
#define EDMP_PED_SB_TIMER_TH                                    0x3e2
#define EDMP_PED_SB_TIMER_TH_SIZE                               2

/* ped_hi_en_th
 *
 * Threshold on signal's energy in frequency band corresponding to walking/running. 
 * Unit: LSB with 1 LSB = 1 g/225 from accel filtered value
 * Range: [2949120 - 5210112] 
 * Default value: 3506176
 * Recommendation: if some walking steps are classified as running, higher the value, if some running steps are classified as walking, lower the value
 */
#define EDMP_PED_HI_EN_TH                                       0x3f8
#define EDMP_PED_HI_EN_TH_SIZE                                  4

/* ped_sensitivity_mode
 *
 * Set the sensitivity to low energy, 0/1 value. 1 is more sensitive to low energy steps
 * Unit: no unit
 * Range: [0 - 1] 
 * Default value: 0
 * Recommendation: to detect very slow walk (with a frequency lower that 1 Hz), value can be set to 1, warning the false detection on no-walking use case may increase.
 */
#define EDMP_PED_SENSITIVITY_MODE                               0x3ec
#define EDMP_PED_SENSITIVITY_MODE_SIZE                          1

/* ped_low_en_amp_th
 *
 * Threshold on signal amplitude on filtered accelerometer to identify a valid step in slow walk mode.
 * Unit: LSB with 1 LSB = 1 g/225 from accel filtered value
 * Range: [1006632 - 3523215] 
 * Default value: 2684354
 * Recommendation: only used when sensitivity_mode is equal to 1 (slow walk), lower the value to detect smoother steps
 */
#define EDMP_PED_LOW_EN_AMP_TH                                  0x3e8
#define EDMP_PED_LOW_EN_AMP_TH_SIZE                             4

/* ped_step_cnt_buf1
 *
 * Number of steps done since the last init of the pedometer feature.
 * Filled in alternatively with ped_step_cnt_buf2.
 * Unit: number of steps
 */
#define EDMP_PED_STEP_CNT_BUF1                                  0x9a
#define EDMP_PED_STEP_CNT_BUF1_SIZE                             2

/* ped_step_cnt_buf2
 *
 * Number of steps done since the last init of the pedometer feature.
 * Filled in alternatively with ped_step_cnt_buf1.
 * Unit: number of steps
 */
#define EDMP_PED_STEP_CNT_BUF2                                  0x9c
#define EDMP_PED_STEP_CNT_BUF2_SIZE                             2

/* ped_step_cadence
 *
 * Instant step cadence measured by the algorithm
 * Unit: 4*number of samples between two consecutive steps. Cadency (step/s) = (ped_step_cadence / 4) / (pedometer_ ODR).
 */
#define EDMP_PED_STEP_CADENCE                                   0x9f
#define EDMP_PED_STEP_CADENCE_SIZE                              1

/* ped_activity_class
 *
 * Activity classification of step detected
 * Unit: Enum: unknown (0), walk(1), run(2)
 */
#define EDMP_PED_ACTIVITY_CLASS                                 0xa0
#define EDMP_PED_ACTIVITY_CLASS_SIZE                            1

/* tilt_wait_time
 *
 * The time during which the tilt gesture should be maintained to detect tilt. 
 * Unit: time in sample number
 * Range: [0 - 65536] 
 * Default value: 200 for ODR = 50 Hz, 100 for ODR = 25 Hz
 */
#define EDMP_TILT_WAIT_TIME                                     0x188
#define EDMP_TILT_WAIT_TIME_SIZE                                2

/* tilt_reset_en
 *
 * Set 1 to reset tilt prior to any further tilt processing on next sensor data.
 */
#define EDMP_TILT_RESET_EN                                      0x92
#define EDMP_TILT_RESET_EN_SIZE                                 1

/* quat_reset_en
 *
 * Set 1 to force reset 3-axis quaternion when next tilt reset is done. This is applicable only if tilt_reset_en is also set to 1.
 */
#define EDMP_QUAT_RESET_EN                                      0x5c
#define EDMP_QUAT_RESET_EN_SIZE                                 1

/* smd_sensitivity
 *
 * Bit shift of the initial threshold of low value variance, representing the algorithm robustness to rejection use case. 
 * Unit: enum no unit
 * Range: [0 - 4] 
 * Default value: 0
 * Recommendation: 0 is the value corresponding to the better good detection rate in biking and transport use case.
 * Higher the value will decrease the biking and transport good detection rate, but it will also improve the performance in rejection.
 */
#define EDMP_SMD_SENSITIVITY                                    0x412
#define EDMP_SMD_SENSITIVITY_SIZE                               1

/* basicsmd_win
 *
 * The window time in number of samples to wait continuous WOM before trigger SMD
 * Unit: time in sample number
 * Range: [25 - 500] 
 * Default value: 150
 * Recommended value at 50Hz = 150
 * Recommended value at 25Hz = 75
 */
#define EDMP_BASICSMD_WIN                                       0x110
#define EDMP_BASICSMD_WIN_SIZE                                  4

/* basicsmd_win_wait
 *
 * The window time in number of samples before stop trigger SMD after WOM stop reported motion
 * Unit: time in sample number
 * Range: [25 - 500] 
 * Default value: 50
 * Recommended value at 50Hz = 50
 * Recommended value at 25Hz = 25
 */
#define EDMP_BASICSMD_WIN_WAIT                                  0x114
#define EDMP_BASICSMD_WIN_WAIT_SIZE                             4

/* r2w_sleep_time_out
 *
 * Defines the duration after wake event to report sleep event no matter if position change or not 
 * Unit: time in ms (millisecond)
 * Range: [100 - 10000]
 * Default value: 640 (equivalent to 0.64s)
 */
#define EDMP_R2W_SLEEP_TIME_OUT                                 0x21c
#define EDMP_R2W_SLEEP_TIME_OUT_SIZE                            4

/* r2w_sleep_gesture_delay
 *
 * Defines the minimal duration of sleep position before trigger the sleep event
 * Unit: time in ms (millisecond)
 * Range: [0 - 256]
 * Default value: 96 (equivalent to 0.096 s)
 */
#define EDMP_R2W_SLEEP_GESTURE_DELAY                            0x220
#define EDMP_R2W_SLEEP_GESTURE_DELAY_SIZE                       4

/* r2w_mounting_matrix
 *
 * Mounting matrix to rotate data from chip frame to device frame
 * Unit: N/A
 * Range: 3 lower bits are use [b2 b1 b0]: when b2 = 1 swap X and Y, when b1 = 1 flip X sign, when b0 = 1 flip Y sign
 * Default value: 0 (chip frame aligned with android frame)
 */
#define EDMP_R2W_MOUNTING_MATRIX                                0x224
#define EDMP_R2W_MOUNTING_MATRIX_SIZE                           4

/* r2w_gravity_filter_gain
 *
 * Mounting matrix to rotate data from chip frame to device frame
 * Unit: N/A
 * Range: 3 lower bits are use [b2 b1 b0]: when b2 = 1 swap X and Y, when b1 = 1 flip X sign, when b0 = 1 flip Y sign
 * Default value: 0 (chip frame aligned with android frame)
 */
#define EDMP_R2W_GRAVITY_FILTER_GAIN                            0x22c
#define EDMP_R2W_GRAVITY_FILTER_GAIN_SIZE                       4

/* r2w_motion_thr_angle_cosine
 *
 * Set the minimal angle that needed to be applied to device to detect R2W
 * Unit: fixed point value q30 of cosine of the angle
 * Range: [130856211 - 1069655912], corresponding to angle between 5 and 85 degrees
 * Default value: 1046221864, corresponding to an angle of 13 degrees
 */
#define EDMP_R2W_MOTION_THR_ANGLE_COSINE                        0x230
#define EDMP_R2W_MOTION_THR_ANGLE_COSINE_SIZE                   4

/* r2w_motion_thr_timer_fast
 *
 * Timer relative to the rapidity of the algorithm to trigger wake up when the orientation before motion is Y axis up (with less than 30Â° of inclination).
 * Unit: ms (no dependency on ODR, it is managed internally by the algo)
 * Range: [100 - 500]
 * Default value: 240
 */
#define EDMP_R2W_MOTION_THR_TIMER_FAST                          0x234
#define EDMP_R2W_MOTION_THR_TIMER_FAST_SIZE                     4

/* r2w_motion_thr_timer_slow
 *
 * Timer relative to the rapidity of the algorithm to trigger wake up when the orientation before motion is over 30Â° on the Y axis
 * Unit: ms (no dependency on ODR, it is managed internally by the algo)
 * Range: [240- 1000]
 * Default value: 500
 */
#define EDMP_R2W_MOTION_THR_TIMER_SLOW                          0x238
#define EDMP_R2W_MOTION_THR_TIMER_SLOW_SIZE                     4

/* r2w_motion_prev_gravity_timeout
 *
 * Time delay to update internal value of previous gravity when no motion is detected, longer time enables detection motion during slower gesture.
 * Unit: ms (no dependency on ODR, it is managed internally by the algo)
 * Range: [100 - 1000]
 * Default value: 300
 */
#define EDMP_R2W_MOTION_PREV_GRAVITY_TIMEOUT                    0x23c
#define EDMP_R2W_MOTION_PREV_GRAVITY_TIMEOUT_SIZE               4

/* r2w_last_gravity_motion_timer
 *
 * Time delay to update the current gravity estimator when no motion is detected.
 * Unit: ms (no dependency on ODR, it is managed internally by the algo)
 * ODR dependency: No, despite it is a timer, the algorithm internally manages the ODR
 * Range: [100 - 1000]
 * Default value: 480
 */
#define EDMP_R2W_LAST_GRAVITY_MOTION_TIMER                      0x240
#define EDMP_R2W_LAST_GRAVITY_MOTION_TIMER_SIZE                 4

/* r2w_last_gravity_timeout
 *
 * Time delay to update gravity in case motion is detected all the time, force to update gravity estimator even if the device is not stable.
 * Unit: ms (no dependency on ODR, it is managed internally by the algo)
 * Range: [1000 - 10000]
 * Default value: 2600
 */
#define EDMP_R2W_LAST_GRAVITY_TIMEOUT                           0x244
#define EDMP_R2W_LAST_GRAVITY_TIMEOUT_SIZE                      4

/* r2w_gesture_validity_timeout
 *
 * Gesture validity timeout, if gesture is not completed in this timeout limit, gesture is invalid
 * Unit: ms (no dependency on ODR, it is managed internally by the algo)
 * Range: [100 - 1000]
 * Default value: 240
 */
#define EDMP_R2W_GESTURE_VALIDITY_TIMEOUT                       0x248
#define EDMP_R2W_GESTURE_VALIDITY_TIMEOUT_SIZE                  4

/* lowg_peak_th
 *
 * Sum of absolute accelerometer axis falls lowg_peak_th will potentially trigger the start of LowG state.
 * Unit: LSB with 1 LSB = 1g / 212
 * Range: [128 - 4096] 
 * Default value: 2048
 */
#define EDMP_LOWG_PEAK_TH                                       0x13c
#define EDMP_LOWG_PEAK_TH_SIZE                                  2

/* lowg_peak_th_hyst
 *
 * Hysteresis added to the lowg_peak_th threshold to confirm the triggering of the LowG state.
 * Unit: LSB with 1 LSB = 1g / 212  
 * Range: [128 - 1024]
 * Default value: 128
 */
#define EDMP_LOWG_PEAK_TH_HYST                                  0x13e
#define EDMP_LOWG_PEAK_TH_HYST_SIZE                             2

/* lowg_time_th
 *
 * The number of samples device should stay below (lowg_peak_th + lowg_peak_th_hyst) before LowG state is triggered.
 * Unit: time in samples number 
 * Range: [1 - 300]
 * Default value: 13 (set for default ODR = 400 Hz, equivalent to 32 ms)
 * Recommended value at 800Hz = 26
 * Recommended value at 400Hz = 13
 * Recommended value at 200Hz = 7
 */
#define EDMP_LOWG_TIME_TH                                       0x140
#define EDMP_LOWG_TIME_TH_SIZE                                  2

/* highg_peak_th
 *
 * Any of the absolute accelerometer axis surpasses highg_peak_th will potentially trigger the start of HighG state.
 * Unit : LSB with 1 LSB = 1g / 212 
 * Range: [1024 - 32768]
 * Default value: 29696
 */
#define EDMP_HIGHG_PEAK_TH                                      0x130
#define EDMP_HIGHG_PEAK_TH_SIZE                                 2

/* highg_peak_th_hyst
 *
 * Hysteresis subtracted to the high_peak_th to confirm the triggering of the HighG state.
 * Unit: LSB with 1 LSB = 1g /212 
 * Range: [128 - 1024]
 * Default value: 128
 */
#define EDMP_HIGHG_PEAK_TH_HYST                                 0x132
#define EDMP_HIGHG_PEAK_TH_HYST_SIZE                            2

/* highg_time_th
 *
 * The number of samples device should stay above (highg_peak_th + highg_peak_th_hyst) before HighG state is triggered.
 * Unit: time in samples number
 * Range: [1-300]
 * Default value: 1 (set for default ODR = 400 Hz, equivalent to 2.5 ms)
 * Recommended value at 800Hz = 1
 * Recommended value at 400Hz = 1
 * Recommended value at 200Hz = 1
 */
#define EDMP_HIGHG_TIME_TH                                      0x134
#define EDMP_HIGHG_TIME_TH_SIZE                                 2

/* ff_min_duration
 *
 * Minimum duration between a LowG and HighG event to trigger freefall.
 * Unit: time in samples number 
 * Range: [4 - 420]
 * Default value: 57 (set for default ODR = 400 Hz, equivalent to 142 ms)
 * Recommended value at 800Hz = 114
 * Recommended value at 400Hz = 57
 * Recommended value at 200Hz = 28
 */
#define EDMP_FF_MIN_DURATION                                    0x120
#define EDMP_FF_MIN_DURATION_SIZE                               4

/* ff_max_duration
 *
 * Maximum duration after LowG event to wait HighG event before reset freefall algorithm.
 * Unit: time in samples number 
 * Range: [12 - 1040]
 * Default value: 285 (set for default ODR = 400 Hz, equivalent to 712 ms)
 * Recommended value at 800Hz = 570
 * Recommended value at 400Hz = 255
 * Recommended value at 200Hz = 142
 */
#define EDMP_FF_MAX_DURATION                                    0x124
#define EDMP_FF_MAX_DURATION_SIZE                               4

/* ff_debounce_duration
 *
 * Wait duration after freefall event detected (to avoid false freefall event), algorithm is in "pause" during this time.
 * Unit: time in samples number
 * Range: [75 - 3000]
 * Default value: 800 (set for default ODR = 400 Hz, equivalent to 2 s)
 * Recommended value at 800Hz = 1600
 * Recommended value at 400Hz = 800
 * Recommended value at 200Hz = 400
 */
#define EDMP_FF_DEBOUNCE_DURATION                               0x128
#define EDMP_FF_DEBOUNCE_DURATION_SIZE                          4

/* ff_duration_buf1
 *
 * Duration of the freefall.
 * Filled in alternatively with ff_duration_buf2.
 * Unit: time in sample number
 */
#define EDMP_FF_DURATION_BUF1                                   0x88
#define EDMP_FF_DURATION_BUF1_SIZE                              2

/* ff_duration_buf2
 *
 * Duration of the freefall.
 * Filled in alternatively with ff_duration_buf1.
 * Unit: time in sample number
 */
#define EDMP_FF_DURATION_BUF2                                   0x8a
#define EDMP_FF_DURATION_BUF2_SIZE                              2

/* tap_min_jerk
 *
 * The minimal value of jerk to be considered as a tap candidate.
 * Unit: LSB with 1 LSB = 1g /26 (of the jerk value)
 * Range: [0 - 64]
 * Default value: 18 corresponding to 0.28 g
 */
#define EDMP_TAP_MIN_JERK                                       0x193
#define EDMP_TAP_MIN_JERK_SIZE                                  1

/* tap_tmax
 *
 * The minimal value of jerk to be considered as a tap candidate.
 * Unit: LSB with 1 LSB = 1g /26 (of the jerk value)
 * Range: [0 - 64]
 * Default value: 18 corresponding to 0.28 g
 */
#define EDMP_TAP_TMAX                                           0x190
#define EDMP_TAP_TMAX_SIZE                                      2

/* tap_tmin
 *
 * Single tap window, sub-windows within Tmax to detect single-tap event. For example:
 * 0.125 s: 24 for 200 Hz, 48 for 400 Hz, 96 for 800 Hz
 * 0.1406 s: 27 for 200 Hz, 54 for 400 Hz, 108 for 800 Hz
 * 0.1563 s: 30 for 200 Hz, 60 for 400 Hz, 120 for 800 Hz
 * 0.1719 s: 32 for 200 Hz, 66 for 400 Hz, 132 for 800 Hz
 * 0.18755 s: 37 for 200 Hz, 74 for 400 Hz, 148 for 800 Hz
 * 0.20319 s: 40 for 200 Hz, 80 for 400 Hz, 160 for 800 Hz
 * 0.21883 s: 43 for 200 Hz, 86 for 400 Hz, 172 for 800 Hz
 * 0.23447 s: 46 for 200 Hz, 92 for 400 Hz, 184 for 800 Hz
 * Unit: time in sample number
 * Default value: 132 at 800Hz, representing 0.1719 s
 */
#define EDMP_TAP_TMIN                                           0x192
#define EDMP_TAP_TMIN_SIZE                                      1

/* tap_max_peak_tol
 *
 * Maximum peak tolerance is the percentage of pulse amplitude to get the smudge threshold for rejection.
 * 1: 12.5 %
 * 2: 25.0 %
 * 3: 37.5 %
 * 4: 50.0 %
 * Unit: enum
 * Default value: 2
 */
#define EDMP_TAP_MAX_PEAK_TOL                                   0x195
#define EDMP_TAP_MAX_PEAK_TOL_SIZE                              1

/* tap_smudge_reject_thr
 *
 * Maximum peak tolerance is the percentage of pulse amplitude to get the smudge threshold for rejection.
 * 1: 12.5 %
 * 2: 25.0 %
 * 3: 37.5 %
 * 4: 50.0 %
 * Unit: enum
 * Default value: 2
 */
#define EDMP_TAP_SMUDGE_REJECT_THR                              0x194
#define EDMP_TAP_SMUDGE_REJECT_THR_SIZE                         1

/* tap_tavg
 *
 * Energy measurement window size to determine the tap axis associated with the 1st tap.
 * Unit: time in sample number
 * Range: [1 â€“ 2 â€“ 4 â€“ 8]
 * Default value: 8
 */
#define EDMP_TAP_TAVG                                           0x196
#define EDMP_TAP_TAVG_SIZE                                      1

/* tap_num
 *
 * Enum of the tap type.
 * Unit: enum,  0: no tap, 1: single tap, 2: double tap.
 */
#define EDMP_TAP_NUM                                            0x8d
#define EDMP_TAP_NUM_SIZE                                       1

/* tap_axis
 *
 * Indicate the axis of the tap in the device frame
 * Unit: enum, 0: ax, 1: ay, 2: az.
 */
#define EDMP_TAP_AXIS                                           0x8e
#define EDMP_TAP_AXIS_SIZE                                      1

/* tap_dir
 *
 * Indicate the direction of the tap in the device frame
 * Unit: enum, 0: positive, 1: negative
 */
#define EDMP_TAP_DIR                                            0x8f
#define EDMP_TAP_DIR_SIZE                                       1

/* double_tap_timing
 *
 * Indicate in case of double tap, the sample count of the second pulse detected in the detection window
 * Unit: time in sample number
 */
#define EDMP_DOUBLE_TAP_TIMING                                  0x90
#define EDMP_DOUBLE_TAP_TIMING_SIZE                             1

/* soft_iron_sensitivity_matrix
 *
 * Input 3x3 calibration matrix in q14 format applied to uncalib data.
 */
#define EDMP_SOFT_IRON_SENSITIVITY_MATRIX                       0x490
#define EDMP_SOFT_IRON_SENSITIVITY_MATRIX_SIZE                  36

/* hard_iron_offset
 *
 * 3-dimension vector that is removed to magnetometer data.
 */
#define EDMP_HARD_IRON_OFFSET                                   0x4b4
#define EDMP_HARD_IRON_OFFSET_SIZE                              12

/* es0_compass_en
 *
 * Set 1 for compass support with es0, for other external sensors with es0, set 0.
 */
#define EDMP_ES0_COMPASS_EN                                     0xb9
#define EDMP_ES0_COMPASS_EN_SIZE                                1

/* es_power_mode
 *
 * Set 1 for possibility of power savings when APEX features utilization is minimal.
 * Set 0 when APEX features utilization is at maximum.
 */
#define EDMP_ES_POWER_MODE                                      0xba
#define EDMP_ES_POWER_MODE_SIZE                                 1

/* es_ram_image_en
 *
 * Set 1 to load device specific RAM image for external sensor support, otherwise set 0
 */
#define EDMP_ES_RAM_IMAGE_EN                                    0xb6
#define EDMP_ES_RAM_IMAGE_EN_SIZE                               1

/* power_save_time
 *
 * The time (in sample number) after which eDMP goes in power save mode.
 * Unit: time in sample number
 * Range: [0 - 4294967295] 
 * Default value: 6400
 */
#define EDMP_POWER_SAVE_TIME                                    0xc4
#define EDMP_POWER_SAVE_TIME_SIZE                               4

/* stc_results
 *
 * Results/status from self-test/self-cal run
 * bit0: AX Self-test result (0:pass 1:fail)
 * bit1: AY Self-test result (0:pass 1:fail)
 * bit2: AZ Self-test result (0:pass 1:fail)
 * bit3: GX Self-test result (0:pass 1:fail)
 * bit4: GY Self-test result (0:pass 1:fail)
 * bit5: GZ Self-test result (0:pass 1:fail)
 * bit6: Accel self-cal status (0:Done 1:InProgress 2:Error)
 * bit7: Gyro self-cal status (0:Done 1:InProgress 2:Error)
 */
#define EDMP_STC_RESULTS                                        0x44
#define EDMP_STC_RESULTS_SIZE                                   4

/* stc_accel_sc_nout_meas_x
 *
 * Accel measurements for X axis in s32.16 for accel self-cal
 */
#define EDMP_STC_ACCEL_SC_NOUT_MEAS_X                           0x48
#define EDMP_STC_ACCEL_SC_NOUT_MEAS_X_SIZE                      4

/* stc_accel_sc_nout_meas_y
 *
 * Accel measurements for Y axis in s32.16 for accel self-cal
 */
#define EDMP_STC_ACCEL_SC_NOUT_MEAS_Y                           0x4c
#define EDMP_STC_ACCEL_SC_NOUT_MEAS_Y_SIZE                      4

/* stc_accel_sc_nout1_meas_z
 *
 * Accel measurements for Z axis in s32.16 for accel self-cal
 */
#define EDMP_STC_ACCEL_SC_NOUT1_MEAS_Z                          0x50
#define EDMP_STC_ACCEL_SC_NOUT1_MEAS_Z_SIZE                     4

/* stc_accel_sc_nout2_meas_z
 *
 * Accel measurements for Z axis in s32.16 for accel self-cal
 */
#define EDMP_STC_ACCEL_SC_NOUT2_MEAS_Z                          0x5c
#define EDMP_STC_ACCEL_SC_NOUT2_MEAS_Z_SIZE                     4

/* stc_accel_sc_cmos_meas_x
 *
 * Accel measurements for X axis in s32.16 for accel self-cal
 */
#define EDMP_STC_ACCEL_SC_CMOS_MEAS_X                           0x54
#define EDMP_STC_ACCEL_SC_CMOS_MEAS_X_SIZE                      4

/* stc_gain_gx
 *
 * Gyro measurements for X axis in s32.16 for gyro self-test and gyro self-cal by SC2V+ADC Gain
 */
#define EDMP_STC_GAIN_GX                                        0x60
#define EDMP_STC_GAIN_GX_SIZE                                   4

/* stc_gain_gy
 *
 * Gyro measurements for Y axis in s32.16 for gyro self-test and gyro self-cal by SC2V+ADC Gain
 */
#define EDMP_STC_GAIN_GY                                        0x64
#define EDMP_STC_GAIN_GY_SIZE                                   4

/* stc_gain_gz
 *
 * Gyro measurements for Z axis in s32.16 for gyro self-test and gyro self-cal by SC2V+ADC Gain
 */
#define EDMP_STC_GAIN_GZ                                        0x68
#define EDMP_STC_GAIN_GZ_SIZE                                   4

/* stc_configParams
 *
 * Self-test and self-cal input parameters
 * bit0: If set, enable self-test/self-cal init, must be set when any of accel or gyro self-test/self-cal enable bit is set (bits 4:1)
 * bit1: If set, enable accel self-test 
 * bit2: If set, enable gyro self-test
 * bit3: If set, enable accel self-cal  
 * bit4: If set, enable gyro self-cal
 * bit5: Method used to calculate the gyro calibration (0 for Step-response, 1 for SC2V+ADC Gain)
 * bit6: If set, enable SSOM for self-cal
 * bit7~9: Averaging time used to perform self-test (0/1/2/3/4/5: 10/20/40/80/160/320 ms)
 * bit10~12: Tolerance between factory trim and accel self-test response (0/1/2/3/4/5/6/7: 5/10/15/20/25/30/40/50%)
 * bit13~15: Tolerance between factory trim and gyro self-test response (0/1/2/3/4/5/6/7: 5/10/15/20/25/30/40/50%)
 */
#define EDMP_STC_CONFIGPARAMS                                   0x38
#define EDMP_STC_CONFIGPARAMS_SIZE                              4

/* stc_patch_en
 *
 * Mechanism for enabling patches execution in SRAM for self-test/self-cal operations
 * bit0: If set, enable SRAM patching for accel self-test phase 1
 * bit1: If set, enable SRAM patching for accel self-test phase 2
 * bit2: If set, enable SRAM patching for gyro self-test phase 1
 * bit3: If set, enable SRAM patching for gyro self-test phase 2
 * bit4: If set, enable SRAM patching for accel self-cal ax_mems
 * bit5: If set, enable SRAM patching for accel self-cal ax_cmos
 * bit6: If set, enable SRAM patching for accel self-cal ay_mems
 * bit7: If set, enable SRAM patching for accel self-cal ay_cmos
 * bit8: If set, enable SRAM patching for accel self-cal az_mems
 * bit9: If set, enable SRAM patching for accel self-cal az_cmos
 * bit10: If set, enable SRAM patching for gyro self-cal phase 1
 * bit11: If set, enable SRAM patching for gyro self-cal phase 2
 */
#define EDMP_STC_PATCH_EN                                       0x3c
#define EDMP_STC_PATCH_EN_SIZE                                  4

/* gyro_x_str_ft
 *
 * Self-test response for gyro X axis
 */
#define EDMP_GYRO_X_STR_FT                                      0x0
#define EDMP_GYRO_X_STR_FT_SIZE                                 2

/* gyro_y_str_ft
 *
 * Self-test response for gyro Y axis
 */
#define EDMP_GYRO_Y_STR_FT                                      0x2
#define EDMP_GYRO_Y_STR_FT_SIZE                                 2

/* gyro_z_str_ft
 *
 * Self-test response for gyro Z axis
 */
#define EDMP_GYRO_Z_STR_FT                                      0x4
#define EDMP_GYRO_Z_STR_FT_SIZE                                 2

/* gyro_x_cmos_gain_ft
 *
 * Gyro X axis SC2V+ADC gain measurement result
 */
#define EDMP_GYRO_X_CMOS_GAIN_FT                                0x6
#define EDMP_GYRO_X_CMOS_GAIN_FT_SIZE                           2

/* gyro_y_cmos_gain_ft
 *
 * Gyro Y axis SC2V+ADC gain measurement result
 */
#define EDMP_GYRO_Y_CMOS_GAIN_FT                                0x8
#define EDMP_GYRO_Y_CMOS_GAIN_FT_SIZE                           2

/* gyro_z_cmos_gain_ft
 *
 * Gyro Z axis SC2V+ADC gain measurement result
 */
#define EDMP_GYRO_Z_CMOS_GAIN_FT                                0xa
#define EDMP_GYRO_Z_CMOS_GAIN_FT_SIZE                           2

/* accel_x_sc_nout_ft
 *
 * Accel X factory Nout measurement for sensitivity calibration
 */
#define EDMP_ACCEL_X_SC_NOUT_FT                                 0x12
#define EDMP_ACCEL_X_SC_NOUT_FT_SIZE                            2

/* accel_y_sc_nout_ft
 *
 * Accel Y factory Nout measurement for sensitivity calibration
 */
#define EDMP_ACCEL_Y_SC_NOUT_FT                                 0x14
#define EDMP_ACCEL_Y_SC_NOUT_FT_SIZE                            2

/* accel_z_sc_nout_ft
 *
 * Accel Z factory Nout measurement for sensitivity calibration
 */
#define EDMP_ACCEL_Z_SC_NOUT_FT                                 0x16
#define EDMP_ACCEL_Z_SC_NOUT_FT_SIZE                            2

#ifdef __cplusplus
}
#endif

#endif // __INV_IMU_EDMP_MEMMAP_H__
