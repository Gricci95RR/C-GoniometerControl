/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: goniometer_fw0.c
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

#include "goniometer_fw0.h"
#include "goniometer_fw0_private.h"
#include "safety.h"
#include "controller.h"
#include <string.h>
#include <math.h>
#include "state_machine.h"
#include "rtwtypes.h"
#include "goniometer_fw0_types.h"
#include "rt_nonfinite.h"

/* Exported block parameters */
real_T cl_gain = 325.4775;             /* Variable: cl_gain
                                        * Referenced by: '<S6>/cl_gain'
                                        * Gain of CL controller, K = 1/sum(prefilter_den)
                                        */
real_T lead_filter_den[3] = { 1.0, -1.68263258971657, 0.707813107994074 } ;/* Variable: lead_filter_den
                                                                      * Referenced by: '<S6>/lead_filter'
                                                                      */

real_T lead_filter_num[3] = { 4.41337750166005, -8.16002827415415,
  3.77183129077161 } ;                 /* Variable: lead_filter_num
                                        * Referenced by: '<S6>/lead_filter'
                                        */

real_T max_ctrl_variance = 1.0;        /* Variable: max_ctrl_variance
                                        * Referenced by: '<S4>/safety_chart'
                                        * maximum variance for the controller command voltage in open loop
                                          = (max_voltage_rate)^2 * Ts^2 * ((N/2 + 1) * (N/2 +2)) / 6
                                        */
real_T max_voltage = 9.0;              /* Variable: max_voltage
                                        * Referenced by:
                                        *   '<S6>/Saturation'
                                        *   '<S8>/Saturation1'
                                        */
real_T max_voltage_rate = 0.2;         /* Variable: max_voltage_rate
                                        * Referenced by:
                                        *   '<S8>/Constant'
                                        *   '<S8>/Constant1'
                                        */
real_T max_yaw_rate = 50.0;            /* Variable: max_yaw_rate
                                        * Referenced by: '<S6>/yaw_rate_limiter'
                                        */
real_T max_yaw_variance = 1.0;         /* Variable: max_yaw_variance
                                        * Referenced by: '<S4>/safety_chart'
                                        * maximum variance for the controller command angle in open loop
                                          = (max_yaw_rate)^2 * Ts^2 * ((N/2 + 1) * (N/2 +2)) / 6
                                        */
real_T min_ctrl_variance = 0.0;        /* Variable: min_ctrl_variance
                                        * Referenced by: '<S4>/safety_chart'
                                        * minimum variance for the controller command voltage
                                        */
real_T min_voltage = -1.0;             /* Variable: min_voltage
                                        * Referenced by:
                                        *   '<S6>/Saturation'
                                        *   '<S8>/Saturation1'
                                        */
real_T min_yaw_variance = 0.0;         /* Variable: min_yaw_variance
                                        * Referenced by: '<S4>/safety_chart'
                                        * minimum variance for the controller command angle
                                        */
real_T notch_filter_den[5] = { 1.0, -2.06139242170176, 2.00042593448237,
  -0.959862338140825, 0.151835801980649 } ;/* Variable: notch_filter_den
                                            * Referenced by: '<S6>/notch_filter'
                                            */

real_T notch_filter_num[5] = { 0.433357770193489, -1.22317813983168,
  1.71064771589682, -1.22317813983168, 0.433357770193489 } ;/* Variable: notch_filter_num
                                                             * Referenced by: '<S6>/notch_filter'
                                                             */

real_T pid_den[2] = { 1.0, -1.0 } ;    /* Variable: pid_den
                                        * Referenced by: '<S6>/pid'
                                        */

real_T pid_num[2] = { 0.0005935, 0.0005935 } ;/* Variable: pid_num
                                               * Referenced by: '<S6>/pid'
                                               */

real_T prefilter_den[3] = { 1.0, -1.92006988350367, 0.923142292886873 } ;/* Variable: prefilter_den
                                                                      * Referenced by: '<S6>/prefilter'
                                                                      */

real_T prefilter_num[3] = { 0.0, 0.0015362046915993, 0.0015362046915993 } ;/* Variable: prefilter_num
                                                                      * Referenced by: '<S6>/prefilter'
                                                                      */

real_T voltage_ref_tol = 0.0001;       /* Variable: voltage_ref_tol
                                        * Referenced by: '<S35>/voltage_ref_tol'
                                        * input user
                                        */
real_T warning_time_threshold = 2.0;   /* Variable: warning_time_threshold
                                        * Referenced by: '<S4>/safety_chart'
                                        */
real_T waveform_timeout = 1000.0;      /* Variable: waveform_timeout
                                        * Referenced by: '<S27>/waveform_timeout'
                                        */
real_T yaw_ref_tol = 0.5;              /* Variable: yaw_ref_tol
                                        * Referenced by: '<S35>/yaw_ref_tol'
                                        * input user
                                        */

/* Block signals (default storage) */
B_goniometer_fw0_T goniometer_fw0_B;

/* Block states (default storage) */
DW_goniometer_fw0_T goniometer_fw0_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_goniometer_fw0_T goniometer_fw0_PrevZCX;

/* External inputs (root inport signals with default storage) */
ExtU_goniometer_fw0_T goniometer_fw0_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_goniometer_fw0_T goniometer_fw0_Y;

/* Real-time model */
static RT_MODEL_goniometer_fw0_T goniometer_fw0_M_;
RT_MODEL_goniometer_fw0_T *const goniometer_fw0_M = &goniometer_fw0_M_;

/* System initialize for atomic system: '<Root>/goniometer_fw' */
void goniometer_fw0_goniometer_fw_Init(void)
{
  /* SystemInitialize for Atomic SubSystem: '<S1>/safety' */
  safety_Init();

  /* End of SystemInitialize for SubSystem: '<S1>/safety' */

  /* SystemInitialize for Atomic SubSystem: '<S1>/input_processing' */
  /* InitializeConditions for Delay: '<S27>/Delay1' */
  goniometer_fw0_DW.icLoad = true;

  /* End of SystemInitialize for SubSystem: '<S1>/input_processing' */

  /* SystemInitialize for Atomic SubSystem: '<S1>/controller' */
  controller_Init(&goniometer_fw0_DW.controller_m);

  /* End of SystemInitialize for SubSystem: '<S1>/controller' */
}

/* Output and update for atomic system: '<Root>/goniometer_fw' */
void goniometer_fw0_goniometer_fw(void)
{
  real_T rtb_Delay_j;
  real_T rtb_cl_coltage_cmd;
  real_T rtb_lead_output;
  real_T rtb_pid_output;
  real_T rtb_yaw_error;
  real_T vect_length;
  uint32_T tmp_0;
  boolean_T tmp;

  /* Outputs for Atomic SubSystem: '<S1>/safety' */
  safety();

  /* End of Outputs for SubSystem: '<S1>/safety' */

  /* Outputs for Atomic SubSystem: '<S1>/input_processing' */
  /* MATLAB Function: '<S36>/select_waveform_vector' incorporates:
   *  Constant: '<S36>/waveform_1'
   *  Constant: '<S36>/waveform_2'
   *  Constant: '<S36>/waveform_3'
   *  DataTypeConversion: '<S36>/Data Type Conversion'
   *  Inport: '<Root>/cycle_number'
   *  Inport: '<Root>/slope_ramp'
   *  Inport: '<Root>/waveform_number'
   */
  switch ((uint32_T)goniometer_fw0_U.waveform_number) {
   case 1U:
    goniometer_fw0_DW.SFunction_DIMS3 = 32767;
    memcpy(&goniometer_fw0_B.vect[0], &goniometer_fw0_ConstP.waveform_1_Value[0],
           32767U * sizeof(real_T));
    vect_length = 32767.0;
    break;

   case 2U:
    goniometer_fw0_DW.SFunction_DIMS3 = 32767;
    memcpy(&goniometer_fw0_B.vect[0], &goniometer_fw0_ConstP.waveform_2_Value[0],
           32767U * sizeof(real_T));
    vect_length = 32767.0;
    break;

   case 3U:
    goniometer_fw0_DW.SFunction_DIMS3 = 32767;
    memcpy(&goniometer_fw0_B.vect[0], &goniometer_fw0_ConstP.waveform_3_Value[0],
           32767U * sizeof(real_T));
    vect_length = 32767.0;
    break;

   case 4U:
    vect_length = rt_roundd_snf(20.0 / goniometer_fw0_U.slope_ramp *
      goniometer_fw0_U.cycle_number / 0.0005) - 1.0 /
      goniometer_fw0_U.slope_ramp;
    goniometer_fw0_DW.SFunction_DIMS3 = 1;
    goniometer_fw0_B.vect[0] = 0.0;
    break;

   default:
    goniometer_fw0_DW.SFunction_DIMS3 = 1;
    goniometer_fw0_B.vect[0] = 1.0;
    vect_length = 1.0;
    break;
  }

  /* Logic: '<S27>/Logical Operator3' incorporates:
   *  Constant: '<S28>/Constant'
   *  Delay: '<S4>/request_warn_reset_delay'
   *  Inport: '<Root>/request_warn_reset'
   *  Outport: '<Root>/safety_output'
   *  RelationalOperator: '<S28>/Compare'
   *  RelationalOperator: '<S33>/FixPt Relational Operator'
   *  UnitDelay: '<S33>/Delay Input1'
   *
   * Block description for '<S33>/Delay Input1':
   *
   *  Store in Global RAM
   */
  goniometer_fw0_DW.request_warn_reset_delay_DSTATE = (((int32_T)
    goniometer_fw0_U.request_warn_reset > (int32_T)
    goniometer_fw0_DW.DelayInput1_DSTATE) &&
    (goniometer_fw0_Y.safety_output.warning_level > 0U));

  /* Gain: '<S26>/rad_mrad_conv' incorporates:
   *  Constant: '<S26>/head_head_distance'
   *  Inport: '<Root>/sensor_input'
   *  Outport: '<Root>/yaw'
   *  Product: '<S26>/Divide'
   *  Sum: '<S26>/Sum'
   *  Trigonometry: '<S26>/Atan'
   */
  goniometer_fw0_Y.yaw = atan((goniometer_fw0_U.sensor_input.dist2 -
    goniometer_fw0_U.sensor_input.dist1) / 5000.0) * 1000.0;

  /* Delay: '<S27>/Delay1' incorporates:
   *  Constant: '<S27>/machine_output_init'
   */
  if (goniometer_fw0_DW.icLoad) {
    goniometer_fw0_DW.Delay1_DSTATE =
      goniometer_fw0_ConstP.machine_output_init_Value;
  }

  /* MATLAB Function: '<S36>/select_waveform_vector' */
  rtb_yaw_error = rt_roundd_snf(vect_length);

  /* Switch: '<S35>/Switch' incorporates:
   *  Constant: '<S35>/Constant1'
   *  Constant: '<S35>/voltage_ref_tol'
   *  Constant: '<S35>/yaw_ref_tol'
   *  Delay: '<S27>/Delay'
   *  Delay: '<S35>/Delay'
   *  MATLAB Function: '<S35>/is_cl_ref_reached'
   *  MATLAB Function: '<S35>/is_ol_ref_reached'
   *  Outport: '<Root>/yaw'
   *  RelationalOperator: '<S35>/GreaterThan1'
   */
  if (goniometer_fw0_Y.machine_output.machine_state == OpenLoop) {
    tmp = (fabs(goniometer_fw0_Y.control_output.voltage_cmd -
                goniometer_fw0_Y.control_output.voltage_ref) < voltage_ref_tol);
  } else {
    tmp = (fabs(goniometer_fw0_Y.yaw - goniometer_fw0_Y.control_output.yaw_ref) <
           yaw_ref_tol);
  }

  /* MATLAB Function: '<S36>/select_waveform_vector' */
  if (rtb_yaw_error < 4.294967296E+9) {
    if (rtb_yaw_error >= 0.0) {
      tmp_0 = (uint32_T)rtb_yaw_error;
    } else {
      tmp_0 = 0U;
    }
  } else {
    tmp_0 = MAX_uint32_T;
  }

  /* Outputs for Atomic SubSystem: '<S1>/state_machine' */
  /* Outport: '<Root>/safety_output' incorporates:
   *  Constant: '<S27>/waveform_timeout'
   *  Delay: '<S27>/Delay1'
   *  Inport: '<Root>/request_control_mode'
   *  Inport: '<Root>/request_start_motion'
   *  Inport: '<Root>/request_start_waveform'
   *  Inport: '<Root>/request_stop_motion'
   *  Inport: '<Root>/request_stop_waveform'
   *  Logic: '<S27>/Logical Operator'
   *  Logic: '<S27>/Logical Operator1'
   *  Logic: '<S27>/Logical Operator2'
   *  Logic: '<S27>/Logical Operator4'
   *  Logic: '<S34>/NOT1'
   *  MATLAB Function: '<S36>/select_waveform_vector'
   *  Outport: '<Root>/machine_output'
   *  RelationalOperator: '<S29>/FixPt Relational Operator'
   *  RelationalOperator: '<S30>/FixPt Relational Operator'
   *  RelationalOperator: '<S31>/FixPt Relational Operator'
   *  RelationalOperator: '<S32>/FixPt Relational Operator'
   *  RelationalOperator: '<S34>/GreaterThan'
   *  Switch: '<S35>/Switch'
   *  UnitDelay: '<S29>/Delay Input1'
   *  UnitDelay: '<S30>/Delay Input1'
   *  UnitDelay: '<S31>/Delay Input1'
   *  UnitDelay: '<S32>/Delay Input1'
   *
   * Block description for '<S29>/Delay Input1':
   *
   *  Store in Global RAM
   *
   * Block description for '<S30>/Delay Input1':
   *
   *  Store in Global RAM
   *
   * Block description for '<S31>/Delay Input1':
   *
   *  Store in Global RAM
   *
   * Block description for '<S32>/Delay Input1':
   *
   *  Store in Global RAM
   */
  state_machine(&goniometer_fw0_Y.safety_output,
                goniometer_fw0_U.request_control_mode,
                (goniometer_fw0_U.request_control_mode !=
                 goniometer_fw0_DW.Delay1_DSTATE.machine_state) &&
                goniometer_fw0_DW.Delay1_DSTATE.listening_control_mode_change,
                ((int32_T)goniometer_fw0_U.request_start_waveform > (int32_T)
                 goniometer_fw0_DW.DelayInput1_DSTATE_f) &&
                goniometer_fw0_DW.Delay1_DSTATE.listening_control_mode_change,
                ((int32_T)goniometer_fw0_U.request_start_motion > (int32_T)
                 goniometer_fw0_DW.DelayInput1_DSTATE_fv) &&
                goniometer_fw0_DW.Delay1_DSTATE.listening_start_motion,
                ((int32_T)goniometer_fw0_U.request_stop_motion > (int32_T)
                 goniometer_fw0_DW.DelayInput1_DSTATE_m) &&
                goniometer_fw0_DW.Delay1_DSTATE.listening_stop_motion, (int32_T)
                goniometer_fw0_U.request_stop_waveform > (int32_T)
                goniometer_fw0_DW.DelayInput1_DSTATE_i, tmp, tmp_0,
                waveform_timeout, &goniometer_fw0_Y.machine_output,
                &goniometer_fw0_B.state_machine_m,
                &goniometer_fw0_DW.state_machine_m);

  /* End of Outputs for SubSystem: '<S1>/state_machine' */
  /* End of Outputs for SubSystem: '<S1>/input_processing' */

  /* Outputs for Atomic SubSystem: '<S1>/controller' */
  /* Outport: '<Root>/machine_output' incorporates:
   *  Inport: '<Root>/slope_ramp'
   *  Inport: '<Root>/voltage_ref'
   *  Inport: '<Root>/waveform_number'
   *  Inport: '<Root>/yaw_ref'
   *  Outport: '<Root>/control_output'
   *  Outport: '<Root>/yaw'
   */
  controller(&goniometer_fw0_Y.machine_output, goniometer_fw0_U.yaw_ref,
             goniometer_fw0_U.voltage_ref, goniometer_fw0_U.slope_ramp,
             goniometer_fw0_U.waveform_number, goniometer_fw0_B.vect,
             goniometer_fw0_Y.yaw, &rtb_yaw_error, &vect_length, &rtb_pid_output,
             &rtb_lead_output, &rtb_Delay_j, &rtb_cl_coltage_cmd,
             &goniometer_fw0_Y.control_output, &goniometer_fw0_B.controller_m,
             &goniometer_fw0_DW.controller_m,
             &goniometer_fw0_PrevZCX.controller_m);

  /* End of Outputs for SubSystem: '<S1>/controller' */

  /* Update for Atomic SubSystem: '<S1>/safety' */
  safety_Update();

  /* End of Update for SubSystem: '<S1>/safety' */

  /* Update for Atomic SubSystem: '<S1>/input_processing' */
  /* Update for UnitDelay: '<S33>/Delay Input1' incorporates:
   *  Inport: '<Root>/request_warn_reset'
   *
   * Block description for '<S33>/Delay Input1':
   *
   *  Store in Global RAM
   */
  goniometer_fw0_DW.DelayInput1_DSTATE = goniometer_fw0_U.request_warn_reset;

  /* Update for UnitDelay: '<S29>/Delay Input1' incorporates:
   *  Inport: '<Root>/request_start_waveform'
   *
   * Block description for '<S29>/Delay Input1':
   *
   *  Store in Global RAM
   */
  goniometer_fw0_DW.DelayInput1_DSTATE_f =
    goniometer_fw0_U.request_start_waveform;

  /* Update for Delay: '<S27>/Delay1' incorporates:
   *  BusCreator generated from: '<S5>/machine_output_BusCreator'
   *  Outport: '<Root>/machine_output'
   */
  goniometer_fw0_DW.icLoad = false;
  goniometer_fw0_DW.Delay1_DSTATE = goniometer_fw0_Y.machine_output;

  /* Update for UnitDelay: '<S32>/Delay Input1' incorporates:
   *  Inport: '<Root>/request_stop_motion'
   *
   * Block description for '<S32>/Delay Input1':
   *
   *  Store in Global RAM
   */
  goniometer_fw0_DW.DelayInput1_DSTATE_m = goniometer_fw0_U.request_stop_motion;

  /* Update for UnitDelay: '<S31>/Delay Input1' incorporates:
   *  Inport: '<Root>/request_start_motion'
   *
   * Block description for '<S31>/Delay Input1':
   *
   *  Store in Global RAM
   */
  goniometer_fw0_DW.DelayInput1_DSTATE_fv =
    goniometer_fw0_U.request_start_motion;

  /* Update for UnitDelay: '<S30>/Delay Input1' incorporates:
   *  Inport: '<Root>/request_stop_waveform'
   *
   * Block description for '<S30>/Delay Input1':
   *
   *  Store in Global RAM
   */
  goniometer_fw0_DW.DelayInput1_DSTATE_i =
    goniometer_fw0_U.request_stop_waveform;

  /* End of Update for SubSystem: '<S1>/input_processing' */
}

/* Termination for atomic system: '<Root>/goniometer_fw' */
void goniometer_fw0_goniometer_fw_Term(void)
{
  /* Terminate for Atomic SubSystem: '<S1>/safety' */
  safety_Term();

  /* End of Terminate for SubSystem: '<S1>/safety' */
}

/* Model step function */
void goniometer_fw0_step(void)
{
  /* Outputs for Atomic SubSystem: '<Root>/goniometer_fw' */
  goniometer_fw0_goniometer_fw();

  /* End of Outputs for SubSystem: '<Root>/goniometer_fw' */
}

/* Model initialize function */
void goniometer_fw0_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  goniometer_fw0_PrevZCX.controller_m.cl_controller_Reset_ZCE = POS_ZCSIG;
  goniometer_fw0_PrevZCX.controller_m.Subsystem_Reset_ZCE = POS_ZCSIG;

  /* SystemInitialize for Atomic SubSystem: '<Root>/goniometer_fw' */
  goniometer_fw0_goniometer_fw_Init();

  /* End of SystemInitialize for SubSystem: '<Root>/goniometer_fw' */
}

/* Model terminate function */
void goniometer_fw0_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/goniometer_fw' */
  goniometer_fw0_goniometer_fw_Term();

  /* End of Terminate for SubSystem: '<Root>/goniometer_fw' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
