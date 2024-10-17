/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: state_machine.h
 *
 * Code generated for Simulink model 'goniometer_fw0'.
 *
 * Model version                  : 17.538
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Sep 20 06:55:09 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#ifndef RTW_HEADER_state_machine_h_
#define RTW_HEADER_state_machine_h_
#ifndef goniometer_fw0_COMMON_INCLUDES_
#define goniometer_fw0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* goniometer_fw0_COMMON_INCLUDES_ */

#include "goniometer_fw0_types.h"

/* Block signals for system '<S1>/state_machine' */
typedef struct {
  uint32_T waveform_idx;               /* '<S5>/machine_chart' */
  boolean_T enable_closed_loop;        /* '<S5>/machine_chart' */
  boolean_T stop_motion;               /* '<S5>/machine_chart' */
  boolean_T reset_yaw;                 /* '<S5>/machine_chart' */
  boolean_T follow_waveform;           /* '<S5>/machine_chart' */
} B_state_machine_T;

/* Block states (default storage) for system '<S1>/state_machine' */
typedef struct {
  uint32_T temporalCounter_i1;         /* '<S5>/machine_chart' */
  boolean_T yaw_reset_delay_DSTATE;    /* '<S5>/yaw_reset_delay' */
  uint8_T is_c9_goniometer_fw0;        /* '<S5>/machine_chart' */
  uint8_T is_OpenLoop;                 /* '<S5>/machine_chart' */
  uint8_T is_ClosedLoop;               /* '<S5>/machine_chart' */
  uint8_T is_active_c9_goniometer_fw0; /* '<S5>/machine_chart' */
} DW_state_machine_T;

extern void state_machine(const SafetyOutputs *rtu_safety_output_Inport_1,
  MachineStateRequest rtu_validated_user_inputs_Inport_2, boolean_T
  rtu_validated_user_inputs_Inport_2_p, boolean_T
  rtu_validated_user_inputs_Inport_2_b, boolean_T
  rtu_validated_user_inputs_Inport_2_j, boolean_T
  rtu_validated_user_inputs_Inport_2_f, boolean_T
  rtu_validated_user_inputs_Inport_2_pm, boolean_T
  rtu_validated_user_inputs_Inport_2_a, uint32_T rtu_waveform_info_Inport_3,
  real_T rtu_waveform_info_Inport_3_p, MachineOutputs
  *rty_machine_output_Outport_1, B_state_machine_T *localB, DW_state_machine_T
  *localDW);

#endif                                 /* RTW_HEADER_state_machine_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
