/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: controller.c
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

#include "controller.h"
#include "goniometer_fw0_types.h"
#include "rtwtypes.h"
#include "goniometer_fw0_private.h"
#include <math.h>
#include "rt_nonfinite.h"
#include <float.h>
#include "goniometer_fw0.h"
#include "zero_crossing_types.h"
#define goniometer_fw0_period          (0.0005)

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T q;
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    if (u1 < 0.0) {
      q = ceil(u1);
    } else {
      q = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != q)) {
      q = fabs(u0 / u1);
      if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
        y = 0.0 * u0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

/* System initialize for atomic system: '<S1>/controller' */
void controller_Init(DW_controller_T *localDW)
{
  /* SystemInitialize for Resettable SubSystem: '<S2>/cl_controller' */
  /* InitializeConditions for DiscreteTransferFcn: '<S6>/prefilter' */
  localDW->prefilter_icLoad = 1U;

  /* InitializeConditions for DiscreteTransferFcn: '<S6>/pid' */
  localDW->pid_icLoad = 1U;

  /* InitializeConditions for DiscreteTransferFcn: '<S6>/lead_filter' */
  localDW->lead_filter_icLoad = 1U;

  /* InitializeConditions for DiscreteTransferFcn: '<S6>/notch_filter' */
  localDW->notch_filter_icLoad = 1U;

  /* End of SystemInitialize for SubSystem: '<S2>/cl_controller' */
}

/* Output and update for atomic system: '<S1>/controller' */
void controller(const MachineOutputs *rtu_machine_output_Inport_1, real_T
                rtu_user_inputs_Inport_2, real_T rtu_user_inputs_Inport_2_d,
                real_T rtu_user_inputs_Inport_2_l, uint8_T
                rtu_user_inputs_Inport_2_e, const real_T
                rtu_waveform_info_Inport_3[100000000], real_T rtu_yaw, real_T
                *rty_closed_loop_out, real_T *rty_closed_loop_out_a, real_T
                *rty_closed_loop_out_d, real_T *rty_closed_loop_out_l, real_T
                *rty_closed_loop_out_e, real_T *rty_closed_loop_out_o,
                ControlOutputs *rty_control_output_Outport_2, B_controller_T
                *localB, DW_controller_T *localDW, ZCE_controller_T *localZCE)
{
  real_T Switch;
  real_T notch_filter_tmp;
  real_T rt;
  real_T rtb_deltafalllimit;
  real_T rtb_element;
  boolean_T rtb_Compare_c;
  boolean_T rtb_FixPtRelationalOperator_f;
  boolean_T rtb_FixPtRelationalOperator_m;

  /* MATLAB Function: '<S10>/compute_waveform_point' */
  if (rtu_user_inputs_Inport_2_e == 4) {
    rtb_element = 1.0 / (20.0 / rtu_user_inputs_Inport_2_l) * 6.2831853071795862
      * (rt_roundd_snf(1.0 / rtu_user_inputs_Inport_2_l + (real_T)
                       rtu_machine_output_Inport_1->waveform_idx) * 0.0005);
    rt = rt_remd_snf(rtb_element, 6.2831853071795862) * 0.15915494309189535;
    if (rt > 0.0) {
      if (rt > 0.5) {
        rt = (((-(real_T)(rtb_element < 0.0) - rt) + 1.0) - 0.25) * 4.0;
      } else {
        rt = (((real_T)(rtb_element < 0.0) + rt) - 0.25) * 4.0;
      }
    } else if (rt < 0.0) {
      if (rt < -0.5) {
        rt = (((real_T)(rtb_element < 0.0) + rt) - 0.25) * 4.0;
      } else {
        rt = (((-(real_T)(rtb_element < 0.0) - rt) + 1.0) - 0.25) * 4.0;
      }
    } else {
      rt = (rt - 0.25) * 4.0;
    }

    rtb_element = 5.0 * rt + 4.0;
  } else {
    rtb_element = rtu_waveform_info_Inport_3[(int32_T)
      rtu_machine_output_Inport_1->waveform_idx - 1];
  }

  /* End of MATLAB Function: '<S10>/compute_waveform_point' */

  /* Switch: '<S7>/transition_switch2' incorporates:
   *  Constant: '<S7>/Constant'
   *  Constant: '<S7>/standby_voltage_ref'
   *  RelationalOperator: '<S7>/Equal'
   *  Switch: '<S10>/transition_switch1'
   *  Switch: '<S12>/Switch1'
   */
  if (rtu_machine_output_Inport_1->machine_state == StandBy) {
    rtb_element = 0.0;
  } else if (rtu_machine_output_Inport_1->stop_motion) {
    /* Switch: '<S12>/Switch1' incorporates:
     *  Delay: '<S2>/Delay'
     */
    rtb_element = localDW->Delay_DSTATE;
  } else if (!rtu_machine_output_Inport_1->follow_waveform) {
    /* Switch: '<S12>/Switch1' incorporates:
     *  Switch: '<S10>/transition_switch1'
     */
    rtb_element = rtu_user_inputs_Inport_2_d;
  }

  /* End of Switch: '<S7>/transition_switch2' */

  /* RelationalOperator: '<S25>/Compare' incorporates:
   *  Constant: '<S25>/Constant'
   *  Logic: '<S9>/NOT'
   */
  rtb_Compare_c = !rtu_machine_output_Inport_1->enable_closed_loop;

  /* RelationalOperator: '<S23>/FixPt Relational Operator' incorporates:
   *  UnitDelay: '<S23>/Delay Input1'
   *
   * Block description for '<S23>/Delay Input1':
   *
   *  Store in Global RAM
   */
  rtb_FixPtRelationalOperator_f = ((int32_T)rtb_Compare_c > (int32_T)
    localDW->DelayInput1_DSTATE);

  /* Outputs for Enabled SubSystem: '<S14>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S16>/Enable'
   */
  /* RelationalOperator: '<S15>/FixPt Relational Operator' incorporates:
   *  RelationalOperator: '<S18>/Compare'
   *  UnitDelay: '<S15>/Delay Input1'
   *
   * Block description for '<S15>/Delay Input1':
   *
   *  Store in Global RAM
   */
  if ((int32_T)rtb_FixPtRelationalOperator_f > (int32_T)
      localDW->DelayInput1_DSTATE_a) {
    /* SignalConversion generated from: '<S16>/In1' incorporates:
     *  Delay: '<S8>/cl_voltage_cmd_delay'
     */
    localB->In1 = localDW->cl_voltage_cmd_delay_DSTATE;
  }

  /* End of RelationalOperator: '<S15>/FixPt Relational Operator' */
  /* End of Outputs for SubSystem: '<S14>/Enabled Subsystem' */

  /* Outputs for Resettable SubSystem: '<S14>/Subsystem' incorporates:
   *  ResetPort: '<S17>/Reset'
   */
  if (rtb_FixPtRelationalOperator_f && (localZCE->Subsystem_Reset_ZCE !=
       POS_ZCSIG)) {
    /* InitializeConditions for UnitDelay: '<S20>/Delay Input2'
     *
     * Block description for '<S20>/Delay Input2':
     *
     *  Store in Global RAM
     */
    localDW->DelayInput2_DSTATE = 0.0;
  }

  localZCE->Subsystem_Reset_ZCE = rtb_FixPtRelationalOperator_f;

  /* UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  *rty_closed_loop_out_e = localDW->DelayInput2_DSTATE;

  /* Sum: '<S20>/Difference Inputs1' incorporates:
   *  Sum: '<S19>/Sum1'
   *
   * Block description for '<S20>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rt = (rtb_element - localB->In1) - *rty_closed_loop_out_e;

  /* Product: '<S20>/delta rise limit' incorporates:
   *  Constant: '<S8>/Constant'
   *  SampleTimeMath: '<S20>/sample time'
   *
   * About '<S20>/sample time':
   *  y = K where K = ( w * Ts )
   */
  rtb_deltafalllimit = max_voltage_rate * 0.0005;

  /* Switch: '<S21>/Switch2' incorporates:
   *  RelationalOperator: '<S21>/LowerRelop1'
   */
  if (!(rt > rtb_deltafalllimit)) {
    /* Product: '<S20>/delta fall limit' incorporates:
     *  Constant: '<S8>/Constant1'
     *  SampleTimeMath: '<S20>/sample time'
     *
     * About '<S20>/sample time':
     *  y = K where K = ( w * Ts )
     */
    rtb_deltafalllimit = -max_voltage_rate * 0.0005;

    /* Switch: '<S21>/Switch' incorporates:
     *  RelationalOperator: '<S21>/UpperRelop'
     */
    if (!(rt < rtb_deltafalllimit)) {
      rtb_deltafalllimit = rt;
    }

    /* End of Switch: '<S21>/Switch' */
  }

  /* End of Switch: '<S21>/Switch2' */

  /* Sum: '<S20>/Difference Inputs2' incorporates:
   *  UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Difference Inputs2':
   *
   *  Add in CPU
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  localDW->DelayInput2_DSTATE = rtb_deltafalllimit + *rty_closed_loop_out_e;

  /* Sum: '<S19>/Sum' incorporates:
   *  UnitDelay: '<S20>/Delay Input2'
   *
   * Block description for '<S20>/Delay Input2':
   *
   *  Store in Global RAM
   */
  localDW->Delay_DSTATE = localDW->DelayInput2_DSTATE + localB->In1;

  /* End of Outputs for SubSystem: '<S14>/Subsystem' */

  /* Saturate: '<S8>/Saturation1' */
  if (localDW->Delay_DSTATE > max_voltage) {
    /* Sum: '<S19>/Sum' */
    localDW->Delay_DSTATE = max_voltage;
  } else if (localDW->Delay_DSTATE < min_voltage) {
    /* Sum: '<S19>/Sum' */
    localDW->Delay_DSTATE = min_voltage;
  }

  /* End of Saturate: '<S8>/Saturation1' */

  /* RelationalOperator: '<S22>/FixPt Relational Operator' incorporates:
   *  Constant: '<S24>/Constant'
   *  RelationalOperator: '<S24>/Compare'
   *  UnitDelay: '<S22>/Delay Input1'
   *
   * Block description for '<S22>/Delay Input1':
   *
   *  Store in Global RAM
   */
  rtb_FixPtRelationalOperator_m = ((int32_T)
    rtu_machine_output_Inport_1->enable_closed_loop > (int32_T)
    localDW->DelayInput1_DSTATE_l);

  /* Outputs for Resettable SubSystem: '<S2>/cl_controller' incorporates:
   *  ResetPort: '<S6>/Reset'
   */
  if (rtb_FixPtRelationalOperator_m && (localZCE->cl_controller_Reset_ZCE !=
       POS_ZCSIG)) {
    /* InitializeConditions for DiscreteTransferFcn: '<S6>/prefilter' */
    localDW->prefilter_icLoad = 1U;

    /* InitializeConditions for RateLimiter: '<S6>/yaw_rate_limiter' */
    localDW->PrevY = 0.0;

    /* InitializeConditions for DiscreteTransferFcn: '<S6>/pid' */
    localDW->pid_icLoad = 1U;

    /* InitializeConditions for DiscreteTransferFcn: '<S6>/lead_filter' */
    localDW->lead_filter_icLoad = 1U;

    /* InitializeConditions for DiscreteTransferFcn: '<S6>/notch_filter' */
    localDW->notch_filter_icLoad = 1U;

    /* InitializeConditions for Delay: '<S6>/ol_voltage_cmd_delay' */
    localDW->ol_voltage_cmd_delay_DSTATE = 0.0;
  }

  localZCE->cl_controller_Reset_ZCE = rtb_FixPtRelationalOperator_m;

  /* Gain: '<S6>/cl_gain' */
  rt = cl_gain * rtu_yaw;

  /* DiscreteTransferFcn: '<S6>/prefilter' */
  if (localDW->prefilter_icLoad != 0) {
    localDW->prefilter_states[0] = rt;
    localDW->prefilter_states[1] = rt;
  }

  *rty_closed_loop_out_e = localDW->prefilter_states[0] * prefilter_num[1] +
    localDW->prefilter_states[1] * prefilter_num[2];

  /* End of DiscreteTransferFcn: '<S6>/prefilter' */

  /* Sum: '<S6>/Sum' */
  *rty_closed_loop_out = *rty_closed_loop_out_e - rtu_yaw;

  /* RateLimiter: '<S6>/yaw_rate_limiter' */
  rtb_deltafalllimit = *rty_closed_loop_out - localDW->PrevY;
  if (rtb_deltafalllimit > max_yaw_rate * goniometer_fw0_period) {
    *rty_closed_loop_out_a = max_yaw_rate * goniometer_fw0_period +
      localDW->PrevY;
  } else {
    rt = -max_yaw_rate * goniometer_fw0_period;
    if (rtb_deltafalllimit < rt) {
      *rty_closed_loop_out_a = rt + localDW->PrevY;
    } else {
      *rty_closed_loop_out_a = *rty_closed_loop_out;
    }
  }

  localDW->PrevY = *rty_closed_loop_out_a;

  /* End of RateLimiter: '<S6>/yaw_rate_limiter' */

  /* DiscreteTransferFcn: '<S6>/pid' */
  if (localDW->pid_icLoad != 0) {
    localDW->pid_states = *rty_closed_loop_out;
  }

  rt = (*rty_closed_loop_out_a - pid_den[1] * localDW->pid_states) / pid_den[0];
  *rty_closed_loop_out_d = pid_num[0] * rt + pid_num[1] * localDW->pid_states;

  /* End of DiscreteTransferFcn: '<S6>/pid' */

  /* DiscreteTransferFcn: '<S6>/lead_filter' incorporates:
   *  Constant: '<S6>/Constant1'
   */
  if (localDW->lead_filter_icLoad != 0) {
    localDW->lead_filter_states[0] = 0.0;
    localDW->lead_filter_states[1] = 0.0;
  }

  rtb_deltafalllimit = ((*rty_closed_loop_out_d - localDW->lead_filter_states[0]
    * lead_filter_den[1]) - localDW->lead_filter_states[1] * lead_filter_den[2])
    / lead_filter_den[0];
  *rty_closed_loop_out_l = (lead_filter_num[0] * rtb_deltafalllimit +
    localDW->lead_filter_states[0] * lead_filter_num[1]) +
    localDW->lead_filter_states[1] * lead_filter_num[2];

  /* End of DiscreteTransferFcn: '<S6>/lead_filter' */

  /* DiscreteTransferFcn: '<S6>/notch_filter' incorporates:
   *  Constant: '<S6>/Constant1'
   */
  if (localDW->notch_filter_icLoad != 0) {
    localDW->notch_filter_states[0] = 0.0;
    localDW->notch_filter_states[1] = 0.0;
    localDW->notch_filter_states[2] = 0.0;
    localDW->notch_filter_states[3] = 0.0;
  }

  notch_filter_tmp = ((((*rty_closed_loop_out_l - localDW->notch_filter_states[0]
    * notch_filter_den[1]) - localDW->notch_filter_states[1] * notch_filter_den
                        [2]) - localDW->notch_filter_states[2] *
                       notch_filter_den[3]) - localDW->notch_filter_states[3] *
                      notch_filter_den[4]) / notch_filter_den[0];
  *rty_closed_loop_out_e = (((notch_filter_num[0] * notch_filter_tmp +
    localDW->notch_filter_states[0] * notch_filter_num[1]) +
    localDW->notch_filter_states[1] * notch_filter_num[2]) +
    localDW->notch_filter_states[2] * notch_filter_num[3]) +
    localDW->notch_filter_states[3] * notch_filter_num[4];

  /* End of DiscreteTransferFcn: '<S6>/notch_filter' */

  /* Switch: '<S6>/Switch' incorporates:
   *  Delay: '<S2>/Delay'
   *  Delay: '<S6>/ol_voltage_cmd_delay'
   */
  if (!(localDW->ol_voltage_cmd_delay_DSTATE > 0.0)) {
    localDW->ol_voltage_cmd_delay_DSTATE = localDW->Delay_DSTATE;
  }

  /* End of Switch: '<S6>/Switch' */

  /* Sum: '<S6>/Sum1' incorporates:
   *  Delay: '<S6>/ol_voltage_cmd_delay'
   */
  *rty_closed_loop_out_e += localDW->ol_voltage_cmd_delay_DSTATE;

  /* Saturate: '<S6>/Saturation' */
  if (*rty_closed_loop_out_e > max_voltage) {
    *rty_closed_loop_out_o = max_voltage;
  } else if (*rty_closed_loop_out_e < min_voltage) {
    *rty_closed_loop_out_o = min_voltage;
  } else {
    *rty_closed_loop_out_o = *rty_closed_loop_out_e;
  }

  /* End of Saturate: '<S6>/Saturation' */
  /* End of Outputs for SubSystem: '<S2>/cl_controller' */

  /* Delay: '<S11>/Delay' */
  *rty_closed_loop_out_e = localDW->Delay_DSTATE_m;

  /* Switch: '<S11>/Switch' */
  if (rtu_machine_output_Inport_1->stop_motion) {
    /* Switch: '<S11>/Switch' */
    Switch = *rty_closed_loop_out_e;
  } else {
    /* Switch: '<S11>/Switch' */
    Switch = rtu_user_inputs_Inport_2;
  }

  /* End of Switch: '<S11>/Switch' */

  /* BusCreator generated from: '<S2>/control_output_BusCreator' incorporates:
   *  Delay: '<S2>/Delay'
   */
  rty_control_output_Outport_2->yaw_ref = Switch;
  rty_control_output_Outport_2->voltage_ref = rtb_element;
  rty_control_output_Outport_2->ol_voltage_cmd = localDW->Delay_DSTATE;
  rty_control_output_Outport_2->cl_voltage_cmd = *rty_closed_loop_out_o;

  /* Switch: '<S2>/command_selector' */
  if (rtu_machine_output_Inport_1->enable_closed_loop) {
    /* BusCreator generated from: '<S2>/control_output_BusCreator' */
    rty_control_output_Outport_2->voltage_cmd = *rty_closed_loop_out_o;
  } else {
    /* BusCreator generated from: '<S2>/control_output_BusCreator' incorporates:
     *  Delay: '<S2>/Delay'
     */
    rty_control_output_Outport_2->voltage_cmd = localDW->Delay_DSTATE;
  }

  /* End of Switch: '<S2>/command_selector' */

  /* Update for UnitDelay: '<S23>/Delay Input1'
   *
   * Block description for '<S23>/Delay Input1':
   *
   *  Store in Global RAM
   */
  localDW->DelayInput1_DSTATE = rtb_Compare_c;

  /* Update for Delay: '<S8>/cl_voltage_cmd_delay' */
  localDW->cl_voltage_cmd_delay_DSTATE = *rty_closed_loop_out_o;

  /* Update for UnitDelay: '<S15>/Delay Input1' incorporates:
   *  RelationalOperator: '<S18>/Compare'
   *
   * Block description for '<S15>/Delay Input1':
   *
   *  Store in Global RAM
   */
  localDW->DelayInput1_DSTATE_a = rtb_FixPtRelationalOperator_f;

  /* Update for UnitDelay: '<S22>/Delay Input1' incorporates:
   *  Constant: '<S24>/Constant'
   *  RelationalOperator: '<S24>/Compare'
   *
   * Block description for '<S22>/Delay Input1':
   *
   *  Store in Global RAM
   */
  localDW->DelayInput1_DSTATE_l =
    rtu_machine_output_Inport_1->enable_closed_loop;

  /* Update for Resettable SubSystem: '<S2>/cl_controller' incorporates:
   *  ResetPort: '<S6>/Reset'
   */
  /* Update for DiscreteTransferFcn: '<S6>/prefilter' */
  localDW->prefilter_icLoad = 0U;
  rtb_element = (Switch - localDW->prefilter_states[0] * prefilter_den[1]) -
    localDW->prefilter_states[1] * prefilter_den[2];
  localDW->prefilter_states[1] = localDW->prefilter_states[0];
  localDW->prefilter_states[0] = rtb_element / prefilter_den[0];

  /* Update for DiscreteTransferFcn: '<S6>/pid' */
  localDW->pid_icLoad = 0U;
  localDW->pid_states = rt;

  /* Update for DiscreteTransferFcn: '<S6>/lead_filter' */
  localDW->lead_filter_icLoad = 0U;
  localDW->lead_filter_states[1] = localDW->lead_filter_states[0];
  localDW->lead_filter_states[0] = rtb_deltafalllimit;

  /* Update for DiscreteTransferFcn: '<S6>/notch_filter' */
  localDW->notch_filter_icLoad = 0U;
  localDW->notch_filter_states[3] = localDW->notch_filter_states[2];
  localDW->notch_filter_states[2] = localDW->notch_filter_states[1];
  localDW->notch_filter_states[1] = localDW->notch_filter_states[0];
  localDW->notch_filter_states[0] = notch_filter_tmp;

  /* End of Update for SubSystem: '<S2>/cl_controller' */

  /* Update for Delay: '<S11>/Delay' */
  localDW->Delay_DSTATE_m = rtu_yaw;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
