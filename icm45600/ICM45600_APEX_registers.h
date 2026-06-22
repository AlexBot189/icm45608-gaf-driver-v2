// APEX config

// Power Management
#define power_save_time	0xC4
#define power_save_time_size	0x4

// Basic SMD parameters
#define basicSMD_updateWin	0x110
#define basicSMD_updateWin_size	0x4
#define basicSmd_updateWinWait	0x114
#define basicSmd_updateWinWait_size	0x4

// Freefall parameters
#define lowg_peak_th	0x13C
#define lowg_peak_th_size	0x2
#define lowg_peak_th_hyst	0x13E
#define lowg_peak_th_hyst_size	0x2
#define lowg_time_th	0x140
#define lowg_time_th_size	0x2
#define highg_peak_th	0x130
#define highg_peak_th_size	0x2
#define highg_peak_th_hyst	0x132
#define highg_peak_th_hyst_size	0x2
#define highg_time_th	0x134
#define highg_time_th_size	0x2
#define ff_min_duration	0x120
#define ff_min_duration_size	0x4
#define ff_max_duration	0x124
#define ff_max_duration_size	0x4
#define ff_debounce_duration 	0x128
#define ff_debounce_duration_size	0x4

// Tilt parameters
#define quat_reset_en	0x5C
#define quat_reset_en_size	0x1
#define tilt_reset_en	0x92
#define tilt_reset_en_size	0x1
#define tilt_wait_time	0x188
#define tilt_wait_time_size	0x2

// Tap parameters
#define tap_tmax 	0x190
#define tap_tmax_size	0x2
#define tap_tmin	0x192
#define tap_tmin_size	0x1
#define tap_smudge_reject_thr	0x194
#define tap_smudge_reject_thr_size	0x1
#define tap_tavg	0x196
#define tap_tavg_size	0x1
#define tap_min_jerk_thr	0x193
#define tap_min_jerk_thr_size	0x1
#define tap_max_peak_tol	0x195
#define tap_max_peak_tol_size	0x1

// Raise to Wake parameters
#define r2w_sleep_time_out 	0x21C
#define r2w_sleep_time_out_size	0x4
#define r2w_sleep_gesture_delay	0x220
#define r2w_sleep_gesture_delay_size	0x4
#define r2w_mounting_matrix	0x224
#define r2w_mounting_matrix_size	0x4
#define r2w_gravity_filter_gain 	0x22C
#define r2w_gravity_filter_gain_size	0x4
#define r2w_motion_thr_angle_cosine	0x230
#define r2w_motion_thr_angle_cosine_size	0x4
#define r2w_motion_thr_timer_fast	0x234
#define r2w_motion_thr_timer_fast_size	0x4
#define r2w_motion_thr_timer_slow	0x238
#define r2w_motion_thr_timer_slow_size	0x4
#define r2w_motion_prev_gravity_timeout	0x23C
#define r2w_motion_prev_gravity_timeout_size	0x4
#define r2w_last_gravity_motion_timer	0x240
#define r2w_last_gravity_motion_timer_size	0x4
#define r2w_last_gravity_timeout	0x244
#define r2w_last_gravity_timeout_size	0x4
#define r2w_gesture_validity_timeout	0x248
#define r2w_gesture_validity_timeout_size	0x4

// Pedometer parameters
#define ped_amp_th	0x3F0
#define ped_amp_th_size	0x4
#define ped_step_cnt_th	0x3DC
#define ped_step_cnt_th_size	0x2
#define ped_prev_step_cnt_th	0x352
#define ped_prev_step_cnt_th_size	0x2
#define ped_step_det_th	0x3DE
#define ped_step_det_th_size	0x2
#define ped_sb_timer_th	0x3E2
#define ped_sb_timer_th_size	0x2
#define ped_hi_en_th	0x3F8
#define ped_hi_en_th_size	0x4
#define ped_sensitivity_mode	0x3EC
#define ped_sensitivity_mode_size	0x1
#define ped_low_en_amp_th	0x3E8
#define ped_low_en_amp_th_size	0x4

// APEX SMD parameters
#define apexSMD_sensitivity 	0x412
#define apexSMD_sensitivity_size	0x1

// Soft/Hard Iron Correction parameters
#define soft_iron_sensitivity_matrix 	0x490
#define soft_iron_sensitivity_matrix_size	0x24
#define hard_iron_offset 	0x4B4
#define hard_iron_offset_size	0xC

// APEX data

// Freefall data
#define ff_dur_buf1	0x88
#define ff_dur_buf1_size	0x2
#define ff_dur_buf2	0x8A
#define ff_dur_buf2_size	0x2

// Tap data
#define Tap_num	0x8D
#define Tap_num_size	0x1
#define Tap_axis	0x8E
#define Tap_axis_size	0x1
#define Tap_dir	0x8F
#define Tap_dir_size	0x1
#define double_Tap_timing	0x90
#define double_Tap_timing_size	0x1

// Pedometer data
#define ped_step_cnt_buf1	0x9A
#define ped_step_cnt_buf1_size	0x2
#define ped_step_cnt_buf2	0x9C
#define ped_step_cnt_buf2_size	0x2
#define ped_step_cadence	0x9F
#define ped_step_cadence_size	0x1
#define ped_activity_class	0xA0
#define ped_activity_class_size	0x1

// APEX buffer management

// Freefall buffer management
#define ff_dur_wptr	0x8C
#define ff_dur_wptr_size	0x1

// Pedometer buffer management
#define ped_step_cnt_wptr	0x9E
#define ped_step_cnt_wptr_size	0x1

// External Sensor Support

#define es_RAM_image_en	0xB6
#define es_RAM_image_en_size	0x1
#define es0_compass_en	0xB9
#define es0_compass_en_size	0x1
#define es_power_mode	0xBA
#define es_power_mode_size	0x1

// Secure Authentication interface
//	Input
#define authen_inCipher	0x270
#define authen_inCipher_size	0x4
//	Output
#define authen_outCipher	0x274
#define authen_outCipher_size	0x4

// Self-test/Self_cal interface
//	ConfigParams
//		bit0:		self_testCal_init_en		// 0/1: Disabled/Enabled
//		bit1:		accel_self_test_en			// 0/1: Disabled/Enabled
//		bit2:		gyro_self_test_en			// 0/1: Disabled/Enabled
//		bit3:		accel_self_cal_en			// 0/1: Disabled/Enabled
//		bit4:		gyro_self_cal_en			// 0/1: Disabled/Enabled
//		bit5:		gyro_self_cal_method		// 0/1: Step-response/SC2V+ADC Gain
//		bit6:		ssom_en						// 0/1: Disabled/Enabled
//		bit7~9:		self_test_average_time		// 0/1/2/3/4/5: 10/20/40/80/160/320 ms -> 8/16/32/64/128/256 samples @ 800Hz
//		bit10~12:	accel_self_test_threshold	// 0/1/2/3/4/5/6/7: 5/10/15/20/25/30/40/50
//		bit13~15:	gyro_self_test_threshold	// 0/1/2/3/4/5/6/7: 5/10/15/20/25/30/40/50
//		bit16~31:	unused
#define selfTestCal_configParams	0x38
#define selfTestCal_configParams_size	0x4
//	Patch enable
//		bit0:		patch_en_self_test_accel_phase1		// 0/1: disabled/enabled
//		bit1:		patch_en_self_test_accel_phase2		// 0/1: disabled/enabled
//		bit2:		patch_en_self_test_gyro1_phase1		// 0/1: disabled/enabled
//		bit3:		patch_en_self_test_gyro1_phase2		// 0/1: disabled/enabled
//		bit4:		patch_en_self_cal_accel_ax_mems		// 0/1: disabled/enabled
//		bit5:		patch_en_self_cal_accel_ax_cmos		// 0/1: disabled/enabled
//		bit6:		patch_en_self_cal_accel_ay_mems		// 0/1: disabled/enabled
//		bit7:		patch_en_self_cal_accel_ay_cmos		// 0/1: disabled/enabled
//		bit8:		patch_en_self_cal_accel_az_mems1	// 0/1: disabled/enabled
//		bit9:		patch_en_self_cal_accel_az_mems2	// 0/1: disabled/enabled
//		bit10:		patch_en_self_cal_gyro2_phase1		// 0/1: disabled/enabled
//		bit11:		patch_en_self_cal_gyro2_phase2		// 0/1: disabled/enabled
//		bit12~31:	unused
#define selfTestCal_patch_en	0x3C
#define selfTestCal_patch_en_size	0x4
//	Debug stop points
//		debug_stop_point = SELF_TEST_PHASE_1
//		debug_stop_point = SELF_TEST_PHASE_2
//		debug_stop_point = SELF_CAL_ACCEL_AX_MEMS
//		debug_stop_point = SELF_CAL_ACCEL_AX_CMOS
//		debug_stop_point = SELF_CAL_ACCEL_AY_MEMS
//		debug_stop_point = SELF_CAL_ACCEL_AY_CMOS
//		debug_stop_point = SELF_CAL_ACCEL_AZ_MEMS1
//		debug_stop_point = SELF_CAL_ACCEL_AZ_MEMS2
//		debug_stop_point = SELF_CAL_GYRO1_PHASE_1
//		debug_stop_point = SELF_CAL_GYRO1_PHASE_2
//		debug_stop_point = SELF_CAL_GYRO2_PHASE_1
//		debug_stop_point = SELF_CAL_GYRO2_PHASE_2
#define selfTestCal_debug_stop_point	0x40
#define selfTestCal_debug_stop_point_size	0x4
//	Outputs
//		bit0:		accel_x_self_test_result	// 0/1: passed/failed
//		bit1:		accel_y_self_test_result	// 0/1: passed/failed
//		bit2:		accel_z_self_test_result	// 0/1: passed/failed
//		bit3:		gyro_x_self_test_result		// 0/1: passed/failed
//		bit4:		gyro_y_self_test_result		// 0/1: passed/failed
//		bit5:		gyro_z_self_test_result		// 0/1: passed/failed
//		bit6~7:		self_test_status			// 0/1/2: done/in-progress/error
//		bit8~9:		accel_self_cal_status		// 0/1/2: done/in-progress/error
//		bit10~11:	gyro_self_cal_status		// 0/1/2: done/in-progress/error
//		bit12~31:	unused
#define selfTestCal_results	0x44
#define selfTestCal_results_size	0x4
//	Accel measurements in s32.16 for accel self-test
#define accel_step_response_x	0x48
#define accel_step_response_x_size	0x4
#define accel_step_response_y	0x4C
#define accel_step_response_y_size	0x4
#define accel_step_response_z	0x50
#define accel_step_response_z_size	0x4
//	Accel measurements in s32.16 for accel self-cal
#define accel_sc_nout_meas_x	0x48
#define accel_sc_nout_meas_x_size	0x4
#define accel_sc_nout_meas_y	0x4C
#define accel_sc_nout_meas_y_size	0x4
#define accel_sc_nout1_meas_z	0x50
#define accel_sc_nout1_meas_z_size	0x4
//	Accel measurements in s32.16 for accel self-cal
#define accel_sc_cmos_meas_x	0x54
#define accel_sc_cmos_meas_x_size	0x4
#define accel_sc_cmos_meas_y	0x58
#define accel_sc_cmos_meas_y_size	0x4
#define accel_sc_nout2_meas_z	0x5C
#define accel_sc_nout2_meas_z_size	0x4
//	Gyro measurements in s32.16 for gyro self-test and gyro self-cal by step response
#define gyro_step_response_x	0x60
#define gyro_step_response_x_size	0x4
#define gyro_step_response_y	0x64
#define gyro_step_response_y_size	0x4
#define gyro_step_response_z	0x68
#define gyro_step_response_z_size	0x4
//	Gyro measurements in s32.16 for gyro self-cal by SC2V+ADC Gain
#define gain_gx	0x60
#define gain_gx_size	0x4
#define gain_gy	0x64
#define gain_gy_size	0x4
#define gain_gz	0x68
#define gain_gz_size	0x4
//	SSOM parameters
#define ssom_trigger_th_accel	0x154
#define ssom_trigger_th_accel_size	0x4
#define ssom_trigger_th_gyro	0x158
#define ssom_trigger_th_gyro_size	0x4

