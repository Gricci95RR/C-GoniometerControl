/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: goniometer_fw0.h
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

#ifndef RTW_HEADER_goniometer_fw0_h_
#define RTW_HEADER_goniometer_fw0_h_
#ifndef goniometer_fw0_COMMON_INCLUDES_
#define goniometer_fw0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* goniometer_fw0_COMMON_INCLUDES_ */

#include "goniometer_fw0_types.h"
#include "state_machine.h"
#include "safety.h"
#include "controller.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "zero_crossing_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T vect[100000000];              /* '<S36>/select_waveform_vector' */
  uint32_T warning_level;              /* '<S4>/safety_chart' */
  B_state_machine_T state_machine_m;   /* '<S1>/state_machine' */
  B_voltage_variance_goniometer_fw0_T yaw_variance;/* '<S4>/voltage_variance' */
  B_voltage_variance_goniometer_fw0_T voltage_variance;/* '<S4>/voltage_variance' */
  B_controller_T controller_m;         /* '<S1>/controller' */
} B_goniometer_fw0_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  MachineOutputs Delay1_DSTATE;        /* '<S27>/Delay1' */
  real_T voltage_cmd_delay_DSTATE;     /* '<S4>/voltage_cmd_delay' */
  int32_T SFunction_DIMS3;             /* '<S36>/select_waveform_vector' */
  boolean_T request_warn_reset_delay_DSTATE;/* '<S4>/request_warn_reset_delay' */
  boolean_T DelayInput1_DSTATE;        /* '<S33>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_f;      /* '<S29>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_m;      /* '<S32>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_fv;     /* '<S31>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_i;      /* '<S30>/Delay Input1' */
  boolean_T icLoad;                    /* '<S27>/Delay1' */
  DW_state_machine_T state_machine_m;  /* '<S1>/state_machine' */
  DW_voltage_variance_goniometer_fw0_T yaw_variance;/* '<S4>/voltage_variance' */
  DW_voltage_variance_goniometer_fw0_T voltage_variance;/* '<S4>/voltage_variance' */
  DW_safety_chart_goniometer_fw0_T sf_safety_chart;/* '<S4>/safety_chart' */
  DW_controller_T controller_m;        /* '<S1>/controller' */
} DW_goniometer_fw0_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCE_controller_T controller_m;       /* '<S1>/controller' */
} PrevZCX_goniometer_fw0_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: machine_output_init
   * Referenced by: '<S27>/machine_output_init'
   */
  MachineOutputs machine_output_init_Value;

  /* Expression: waveform_1
   * Referenced by: '<S36>/waveform_1'
   */
  real_T waveform_1_Value[32767];

  /* Expression: waveform_2
   * Referenced by: '<S36>/waveform_2'
   */
  real_T waveform_2_Value[32767];

  /* Expression: waveform_3
   * Referenced by: '<S36>/waveform_3'
   */
  real_T waveform_3_Value[32767];
} ConstP_goniometer_fw0_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  MachineStateRequest request_control_mode;/* '<Root>/request_control_mode' */
  boolean_T request_start_motion;      /* '<Root>/request_start_motion' */
  boolean_T request_stop_motion;       /* '<Root>/request_stop_motion' */
  boolean_T request_start_waveform;    /* '<Root>/request_start_waveform' */
  boolean_T request_stop_waveform;     /* '<Root>/request_stop_waveform' */
  boolean_T request_warn_reset;        /* '<Root>/request_warn_reset' */
  boolean_T request_hyst_comp;         /* '<Root>/request_hyst_comp' */
  real_T voltage_ref;                  /* '<Root>/voltage_ref' */
  real_T yaw_ref;                      /* '<Root>/yaw_ref' */
  uint8_T waveform_number;             /* '<Root>/waveform_number' */
  real_T slope_ramp;                   /* '<Root>/slope_ramp' */
  real_T cycle_number;                 /* '<Root>/cycle_number' */
  SensorInputs sensor_input;           /* '<Root>/sensor_input' */
} ExtU_goniometer_fw0_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T yaw;                          /* '<Root>/yaw' */
  SafetyOutputs safety_output;         /* '<Root>/safety_output' */
  MachineOutputs machine_output;       /* '<Root>/machine_output' */
  ControlOutputs control_output;       /* '<Root>/control_output' */
} ExtY_goniometer_fw0_T;

/* Real-time Model Data Structure */
struct tag_RTM_goniometer_fw0_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_goniometer_fw0_T goniometer_fw0_B;

/* Block states (default storage) */
extern DW_goniometer_fw0_T goniometer_fw0_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_goniometer_fw0_T goniometer_fw0_PrevZCX;

/* External inputs (root inport signals with default storage) */
extern ExtU_goniometer_fw0_T goniometer_fw0_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_goniometer_fw0_T goniometer_fw0_Y;

/* Constant parameters (default storage) */
extern const ConstP_goniometer_fw0_T goniometer_fw0_ConstP;

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T cl_gain;                 /* Variable: cl_gain
                                        * Referenced by: '<S6>/cl_gain'
                                        * Gain of CL controller, K = 1/sum(prefilter_den)
                                        */
extern real_T lead_filter_den[3];      /* Variable: lead_filter_den
                                        * Referenced by: '<S6>/lead_filter'
                                        */
extern real_T lead_filter_num[3];      /* Variable: lead_filter_num
                                        * Referenced by: '<S6>/lead_filter'
                                        */
extern real_T max_ctrl_variance;       /* Variable: max_ctrl_variance
                                        * Referenced by: '<S4>/safety_chart'
                                        * maximum variance for the controller command voltage in open loop
                                          = (max_voltage_rate)^2 * Ts^2 * ((N/2 + 1) * (N/2 +2)) / 6
                                        */
extern real_T max_voltage;             /* Variable: max_voltage
                                        * Referenced by:
                                        *   '<S6>/Saturation'
                                        *   '<S8>/Saturation1'
                                        */
extern real_T max_voltage_rate;        /* Variable: max_voltage_rate
                                        * Referenced by:
                                        *   '<S8>/Constant'
                                        *   '<S8>/Constant1'
                                        */
extern real_T max_yaw_rate;            /* Variable: max_yaw_rate
                                        * Referenced by: '<S6>/yaw_rate_limiter'
                                        */
extern real_T max_yaw_variance;        /* Variable: max_yaw_variance
                                        * Referenced by: '<S4>/safety_chart'
                                        * maximum variance for the controller command angle in open loop
                                          = (max_yaw_rate)^2 * Ts^2 * ((N/2 + 1) * (N/2 +2)) / 6
                                        */
extern real_T min_ctrl_variance;       /* Variable: min_ctrl_variance
                                        * Referenced by: '<S4>/safety_chart'
                                        * minimum variance for the controller command voltage
                                        */
extern real_T min_voltage;             /* Variable: min_voltage
                                        * Referenced by:
                                        *   '<S6>/Saturation'
                                        *   '<S8>/Saturation1'
                                        */
extern real_T min_yaw_variance;        /* Variable: min_yaw_variance
                                        * Referenced by: '<S4>/safety_chart'
                                        * minimum variance for the controller command angle
                                        */
extern real_T notch_filter_den[5];     /* Variable: notch_filter_den
                                        * Referenced by: '<S6>/notch_filter'
                                        */
extern real_T notch_filter_num[5];     /* Variable: notch_filter_num
                                        * Referenced by: '<S6>/notch_filter'
                                        */
extern real_T pid_den[2];              /* Variable: pid_den
                                        * Referenced by: '<S6>/pid'
                                        */
extern real_T pid_num[2];              /* Variable: pid_num
                                        * Referenced by: '<S6>/pid'
                                        */
extern real_T prefilter_den[3];        /* Variable: prefilter_den
                                        * Referenced by: '<S6>/prefilter'
                                        */
extern real_T prefilter_num[3];        /* Variable: prefilter_num
                                        * Referenced by: '<S6>/prefilter'
                                        */
extern real_T voltage_ref_tol;         /* Variable: voltage_ref_tol
                                        * Referenced by: '<S35>/voltage_ref_tol'
                                        * input user
                                        */
extern real_T warning_time_threshold;  /* Variable: warning_time_threshold
                                        * Referenced by: '<S4>/safety_chart'
                                        */
extern real_T waveform_timeout;        /* Variable: waveform_timeout
                                        * Referenced by: '<S27>/waveform_timeout'
                                        */
extern real_T yaw_ref_tol;             /* Variable: yaw_ref_tol
                                        * Referenced by: '<S35>/yaw_ref_tol'
                                        * input user
                                        */

/* Model entry point functions */
extern void goniometer_fw0_initialize(void);
extern void goniometer_fw0_step(void);
extern void goniometer_fw0_terminate(void);

/* Real-time Model object */
extern RT_MODEL_goniometer_fw0_T *const goniometer_fw0_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Delay1' : Unused code path elimination
 * Block '<S20>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/Data Type Propagation' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('goniometer/goniometer_fw')    - opens subsystem goniometer/goniometer_fw
 * hilite_system('goniometer/goniometer_fw/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'goniometer'
 * '<S1>'   : 'goniometer/goniometer_fw'
 * '<S2>'   : 'goniometer/goniometer_fw/controller'
 * '<S3>'   : 'goniometer/goniometer_fw/input_processing'
 * '<S4>'   : 'goniometer/goniometer_fw/safety'
 * '<S5>'   : 'goniometer/goniometer_fw/state_machine'
 * '<S6>'   : 'goniometer/goniometer_fw/controller/cl_controller'
 * '<S7>'   : 'goniometer/goniometer_fw/controller/compute_ctrl_ref'
 * '<S8>'   : 'goniometer/goniometer_fw/controller/ol_controller'
 * '<S9>'   : 'goniometer/goniometer_fw/controller/reset_loops'
 * '<S10>'  : 'goniometer/goniometer_fw/controller/compute_ctrl_ref/compute_ol_voltage_ref'
 * '<S11>'  : 'goniometer/goniometer_fw/controller/compute_ctrl_ref/stop_motion_closed_loop'
 * '<S12>'  : 'goniometer/goniometer_fw/controller/compute_ctrl_ref/stop_motion_open_loop'
 * '<S13>'  : 'goniometer/goniometer_fw/controller/compute_ctrl_ref/compute_ol_voltage_ref/compute_waveform_point'
 * '<S14>'  : 'goniometer/goniometer_fw/controller/ol_controller/ol_rate_limiter'
 * '<S15>'  : 'goniometer/goniometer_fw/controller/ol_controller/ol_rate_limiter/Detect Rise Positive'
 * '<S16>'  : 'goniometer/goniometer_fw/controller/ol_controller/ol_rate_limiter/Enabled Subsystem'
 * '<S17>'  : 'goniometer/goniometer_fw/controller/ol_controller/ol_rate_limiter/Subsystem'
 * '<S18>'  : 'goniometer/goniometer_fw/controller/ol_controller/ol_rate_limiter/Detect Rise Positive/Positive'
 * '<S19>'  : 'goniometer/goniometer_fw/controller/ol_controller/ol_rate_limiter/Subsystem/mro_rate_limiter'
 * '<S20>'  : 'goniometer/goniometer_fw/controller/ol_controller/ol_rate_limiter/Subsystem/mro_rate_limiter/Rate Limiter Dynamic'
 * '<S21>'  : 'goniometer/goniometer_fw/controller/ol_controller/ol_rate_limiter/Subsystem/mro_rate_limiter/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S22>'  : 'goniometer/goniometer_fw/controller/reset_loops/Detect Rise Positive'
 * '<S23>'  : 'goniometer/goniometer_fw/controller/reset_loops/Detect Rise Positive1'
 * '<S24>'  : 'goniometer/goniometer_fw/controller/reset_loops/Detect Rise Positive/Positive'
 * '<S25>'  : 'goniometer/goniometer_fw/controller/reset_loops/Detect Rise Positive1/Positive'
 * '<S26>'  : 'goniometer/goniometer_fw/input_processing/input_conditioning'
 * '<S27>'  : 'goniometer/goniometer_fw/input_processing/input_validation'
 * '<S28>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Compare To Zero'
 * '<S29>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Detect Rise Positive'
 * '<S30>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Detect Rise Positive1'
 * '<S31>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Detect Rise Positive2'
 * '<S32>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Detect Rise Positive3'
 * '<S33>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Detect Rise Positive4'
 * '<S34>'  : 'goniometer/goniometer_fw/input_processing/input_validation/detect_control_mode_change'
 * '<S35>'  : 'goniometer/goniometer_fw/input_processing/input_validation/is_ref_reached'
 * '<S36>'  : 'goniometer/goniometer_fw/input_processing/input_validation/select_waveform'
 * '<S37>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Detect Rise Positive/Positive'
 * '<S38>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Detect Rise Positive1/Positive'
 * '<S39>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Detect Rise Positive2/Positive'
 * '<S40>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Detect Rise Positive3/Positive'
 * '<S41>'  : 'goniometer/goniometer_fw/input_processing/input_validation/Detect Rise Positive4/Positive'
 * '<S42>'  : 'goniometer/goniometer_fw/input_processing/input_validation/is_ref_reached/is_cl_ref_reached'
 * '<S43>'  : 'goniometer/goniometer_fw/input_processing/input_validation/is_ref_reached/is_ol_ref_reached'
 * '<S44>'  : 'goniometer/goniometer_fw/input_processing/input_validation/select_waveform/select_waveform_vector'
 * '<S45>'  : 'goniometer/goniometer_fw/safety/safety_chart'
 * '<S46>'  : 'goniometer/goniometer_fw/state_machine/machine_chart'
 */
#endif                                 /* RTW_HEADER_goniometer_fw0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
