/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: controller.h
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

#ifndef RTW_HEADER_controller_h_
#define RTW_HEADER_controller_h_
#ifndef goniometer_fw0_COMMON_INCLUDES_
#define goniometer_fw0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* goniometer_fw0_COMMON_INCLUDES_ */

#include "goniometer_fw0_types.h"
#include "zero_crossing_types.h"

/* Block signals for system '<S1>/controller' */
typedef struct {
  real_T In1;                          /* '<S16>/In1' */
} B_controller_T;

/* Block states (default storage) for system '<S1>/controller' */
typedef struct {
  real_T Delay_DSTATE;                 /* '<S2>/Delay' */
  real_T cl_voltage_cmd_delay_DSTATE;  /* '<S8>/cl_voltage_cmd_delay' */
  real_T Delay_DSTATE_m;               /* '<S11>/Delay' */
  real_T DelayInput2_DSTATE;           /* '<S20>/Delay Input2' */
  real_T prefilter_states[2];          /* '<S6>/prefilter' */
  real_T pid_states;                   /* '<S6>/pid' */
  real_T lead_filter_states[2];        /* '<S6>/lead_filter' */
  real_T notch_filter_states[4];       /* '<S6>/notch_filter' */
  real_T ol_voltage_cmd_delay_DSTATE;  /* '<S6>/ol_voltage_cmd_delay' */
  real_T PrevY;                        /* '<S6>/yaw_rate_limiter' */
  boolean_T DelayInput1_DSTATE;        /* '<S23>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_a;      /* '<S15>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_l;      /* '<S22>/Delay Input1' */
  uint8_T prefilter_icLoad;            /* '<S6>/prefilter' */
  uint8_T pid_icLoad;                  /* '<S6>/pid' */
  uint8_T lead_filter_icLoad;          /* '<S6>/lead_filter' */
  uint8_T notch_filter_icLoad;         /* '<S6>/notch_filter' */
} DW_controller_T;

/* Zero-crossing (trigger) state for system '<S1>/controller' */
typedef struct {
  ZCSigState Subsystem_Reset_ZCE;      /* '<S14>/Subsystem' */
  ZCSigState cl_controller_Reset_ZCE;  /* '<S2>/cl_controller' */
} ZCE_controller_T;

extern void controller_Init(DW_controller_T *localDW);
extern void controller(const MachineOutputs *rtu_machine_output_Inport_1, real_T
  rtu_user_inputs_Inport_2, real_T rtu_user_inputs_Inport_2_d, real_T
  rtu_user_inputs_Inport_2_l, uint8_T rtu_user_inputs_Inport_2_e, const real_T
  rtu_waveform_info_Inport_3[100000000], real_T rtu_yaw, real_T
  *rty_closed_loop_out, real_T *rty_closed_loop_out_a, real_T
  *rty_closed_loop_out_d, real_T *rty_closed_loop_out_l, real_T
  *rty_closed_loop_out_e, real_T *rty_closed_loop_out_o, ControlOutputs
  *rty_control_output_Outport_2, B_controller_T *localB, DW_controller_T
  *localDW, ZCE_controller_T *localZCE);

#endif                                 /* RTW_HEADER_controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
