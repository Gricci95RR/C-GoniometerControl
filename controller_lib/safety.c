/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: safety.c
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

#include "rtwtypes.h"
#include "safety.h"
#include "goniometer_fw0_types.h"
#include <math.h>
#include <string.h>
#include "goniometer_fw0.h"

/* Named constants for Chart: '<S4>/safety_chart' */
#define goniometer_fw0_IN_off          ((uint8_T)1U)
#define goniometer_fw0_IN_on           ((uint8_T)2U)

/* Forward declaration for local functions */
static void goniometer_fw0_SystemCore_setup
  (dsp_simulink_MovingVariance_goniometer_fw0_T *obj);

/* System initialize for atomic system: '<S4>/safety_chart' */
void goniometer_fw0_safety_chart_Init(uint32_T *rty_warning_level)
{
  *rty_warning_level = 0U;
}

/* Output and update for atomic system: '<S4>/safety_chart' */
void goniometer_fw0_safety_chart(real_T rtu_yaw_variance, boolean_T rtu_reset,
  real_T rtu_ctrl_variance, uint32_T *rty_warning_level,
  DW_safety_chart_goniometer_fw0_T *localDW)
{
  if (localDW->temporalCounter_i1 < MAX_uint32_T) {
    localDW->temporalCounter_i1++;
  }

  /* Chart: '<S4>/safety_chart' */
  if (localDW->is_active_c3_goniometer_fw0 == 0U) {
    localDW->is_active_c3_goniometer_fw0 = 1U;
    *rty_warning_level = 0U;
    localDW->is_wl0 = goniometer_fw0_IN_off;
    localDW->is_wl1 = goniometer_fw0_IN_off;
    localDW->temporalCounter_i1 = 0U;
  } else {
    if (localDW->is_wl0 == goniometer_fw0_IN_off) {
      if (rtu_reset) {
        localDW->is_wl0 = goniometer_fw0_IN_on;
        *rty_warning_level = 0U;
      }
    } else {
      /* case IN_on: */
      localDW->is_wl0 = goniometer_fw0_IN_off;
    }

    if (localDW->is_wl1 == goniometer_fw0_IN_off) {
      if ((rtu_ctrl_variance < min_ctrl_variance) || (rtu_ctrl_variance >
           max_ctrl_variance) || (rtu_yaw_variance < min_yaw_variance) ||
          (rtu_yaw_variance > max_yaw_variance)) {
        if (localDW->temporalCounter_i1 >= (uint32_T)ceil(warning_time_threshold
             / 0.0005 - 5.0000000000000005E-12)) {
          localDW->is_wl1 = goniometer_fw0_IN_on;
          if (*rty_warning_level < 1U) {
            *rty_warning_level = 1U;
          }
        } else if ((rtu_ctrl_variance >= min_ctrl_variance) &&
                   (rtu_ctrl_variance <= max_ctrl_variance) && (rtu_yaw_variance
                    >= min_yaw_variance) && (rtu_yaw_variance <=
                    max_yaw_variance)) {
          localDW->temporalCounter_i1 = 0U;
        }
      }

      /* case IN_on: */
    } else if ((rtu_ctrl_variance >= min_ctrl_variance) && (rtu_ctrl_variance <=
                max_ctrl_variance) && (rtu_yaw_variance >= min_yaw_variance) &&
               (rtu_yaw_variance <= max_yaw_variance)) {
      localDW->is_wl1 = goniometer_fw0_IN_off;
      localDW->temporalCounter_i1 = 0U;
    } else if (*rty_warning_level < 1U) {
      *rty_warning_level = 1U;
    }
  }

  /* End of Chart: '<S4>/safety_chart' */
}

static void goniometer_fw0_SystemCore_setup
  (dsp_simulink_MovingVariance_goniometer_fw0_T *obj)
{
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->NumChannels = 1;
  obj->FrameLength = 1;
  obj->_pobj0.isInitialized = 0;
  obj->_pobj0.isInitialized = 0;
  obj->pStatistic = &obj->_pobj0;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

/* System initialize for atomic system: */
void goniometer_fw0_voltage_variance_Init(DW_voltage_variance_goniometer_fw0_T
  *localDW)
{
  c_dsp_internal_SlidingWindowVarianceCG_goniometer_fw0_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<S4>/voltage_variance' */
  localDW->obj.isInitialized = 0;
  localDW->obj.NumChannels = -1;
  localDW->obj.FrameLength = -1;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  goniometer_fw0_SystemCore_setup(&localDW->obj);

  /* InitializeConditions for MATLABSystem: '<S4>/voltage_variance' */
  obj = localDW->obj.pStatistic;
  if (obj->isInitialized == 1) {
    for (i = 0; i < 200; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 200; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 200; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 1.0;
    obj->pModValueRev = 0.0;
  }

  /* End of InitializeConditions for MATLABSystem: '<S4>/voltage_variance' */
}

/* Output and update for atomic system: */
void goniometer_fw0_voltage_variance(real_T rtu_0,
  B_voltage_variance_goniometer_fw0_T *localB,
  DW_voltage_variance_goniometer_fw0_T *localDW)
{
  c_dsp_internal_SlidingWindowVarianceCG_goniometer_fw0_T *obj;
  real_T reverseS[200];
  real_T reverseSamples[200];
  real_T x[200];
  real_T M;
  real_T Mprev;
  real_T S;
  real_T T;
  real_T counter;
  real_T modValueRev;
  int32_T i;

  /* MATLABSystem: '<S4>/voltage_variance' */
  if (localDW->obj.TunablePropsChanged) {
    localDW->obj.TunablePropsChanged = false;
  }

  obj = localDW->obj.pStatistic;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    for (i = 0; i < 200; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 200; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 200; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 0.0;
    obj->pModValueRev = 0.0;
    obj->isSetupComplete = true;
    for (i = 0; i < 200; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 200; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 200; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 1.0;
    obj->pModValueRev = 0.0;
  }

  for (i = 0; i < 200; i++) {
    reverseSamples[i] = obj->pReverseSamples[i];
  }

  for (i = 0; i < 200; i++) {
    x[i] = obj->pReverseT[i];
  }

  for (i = 0; i < 200; i++) {
    reverseS[i] = obj->pReverseS[i];
  }

  T = obj->pT;
  S = obj->pS;
  M = obj->pM;
  counter = obj->pCounter;
  modValueRev = obj->pModValueRev;

  /* MATLABSystem: '<S4>/voltage_variance' */
  localB->voltage_variance = 0.0;

  /* MATLABSystem: '<S4>/voltage_variance' */
  T += rtu_0;
  Mprev = M;
  M += 1.0 / counter * (rtu_0 - M);
  Mprev = rtu_0 - Mprev;
  S += (counter - 1.0) * Mprev * Mprev / counter;
  if (modValueRev == 0.0) {
    Mprev = (200.0 - counter) / counter * T - x[(int32_T)(200.0 - counter) - 1];

    /* MATLABSystem: '<S4>/voltage_variance' */
    localB->voltage_variance = (counter / (((200.0 - counter) + counter) *
      (200.0 - counter)) * (Mprev * Mprev) + (reverseS[(int32_T)(200.0 - counter)
      - 1] + S)) / 199.0;
  }

  reverseSamples[(int32_T)(200.0 - counter) - 1] = rtu_0;
  if (counter < 199.0) {
    counter++;
  } else {
    counter = 1.0;
    memcpy(&x[0], &reverseSamples[0], 200U * sizeof(real_T));
    T = 0.0;
    S = 0.0;
    for (i = 0; i < 199; i++) {
      M = reverseSamples[i];
      x[i + 1] += x[i];
      Mprev = T;
      T += 1.0 / ((real_T)i + 1.0) * (M - T);
      M -= Mprev;
      S += (((real_T)i + 1.0) - 1.0) * M * M / ((real_T)i + 1.0);
      reverseS[i] = S;
    }

    T = 0.0;
    S = 0.0;
    M = 0.0;
  }

  for (i = 0; i < 200; i++) {
    obj->pReverseSamples[i] = reverseSamples[i];
  }

  for (i = 0; i < 200; i++) {
    obj->pReverseT[i] = x[i];
  }

  for (i = 0; i < 200; i++) {
    obj->pReverseS[i] = reverseS[i];
  }

  obj->pT = T;
  obj->pS = S;
  obj->pM = M;
  obj->pCounter = counter;
  if (modValueRev > 0.0) {
    obj->pModValueRev = modValueRev - 1.0;
  } else {
    obj->pModValueRev = 0.0;
  }
}

/* Termination for atomic system: */
void goniometer_fw0_voltage_variance_Term(DW_voltage_variance_goniometer_fw0_T
  *localDW)
{
  c_dsp_internal_SlidingWindowVarianceCG_goniometer_fw0_T *obj;

  /* Terminate for MATLABSystem: '<S4>/voltage_variance' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      obj = localDW->obj.pStatistic;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }

      localDW->obj.NumChannels = -1;
      localDW->obj.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<S4>/voltage_variance' */
}

/* System initialize for atomic system: '<S1>/safety' */
void safety_Init(void)
{
  /* SystemInitialize for Chart: '<S4>/safety_chart' */
  goniometer_fw0_safety_chart_Init(&goniometer_fw0_B.warning_level);
  goniometer_fw0_voltage_variance_Init(&goniometer_fw0_DW.yaw_variance);
  goniometer_fw0_voltage_variance_Init(&goniometer_fw0_DW.voltage_variance);
}

/* Outputs for atomic system: '<S1>/safety' */
void safety(void)
{
  /* local block i/o variables */
  real_T rtb_yaw_sim_delay;
  real_T rtb_voltage_cmd_delay;

  /* BusCreator generated from: '<S4>/safety_output_BusCreator' incorporates:
   *  Constant: '<S4>/Constant'
   *  Outport: '<Root>/safety_output'
   */
  goniometer_fw0_Y.safety_output.warning_level = 0U;

  /* Delay: '<S4>/yaw_sim_delay' */
  rtb_yaw_sim_delay = goniometer_fw0_Y.yaw;
  goniometer_fw0_voltage_variance(rtb_yaw_sim_delay,
    &goniometer_fw0_B.yaw_variance, &goniometer_fw0_DW.yaw_variance);

  /* Delay: '<S4>/voltage_cmd_delay' */
  rtb_voltage_cmd_delay = goniometer_fw0_DW.voltage_cmd_delay_DSTATE;
  goniometer_fw0_voltage_variance(rtb_voltage_cmd_delay,
    &goniometer_fw0_B.voltage_variance, &goniometer_fw0_DW.voltage_variance);

  /* Chart: '<S4>/safety_chart' incorporates:
   *  Delay: '<S4>/request_warn_reset_delay'
   */
  goniometer_fw0_safety_chart(goniometer_fw0_B.yaw_variance.voltage_variance,
    goniometer_fw0_DW.request_warn_reset_delay_DSTATE,
    goniometer_fw0_B.voltage_variance.voltage_variance,
    &goniometer_fw0_B.warning_level, &goniometer_fw0_DW.sf_safety_chart);
}

/* Update for atomic system: '<S1>/safety' */
void safety_Update(void)
{
  /* Update for Delay: '<S4>/voltage_cmd_delay' incorporates:
   *  Outport: '<Root>/control_output'
   */
  goniometer_fw0_DW.voltage_cmd_delay_DSTATE =
    goniometer_fw0_Y.control_output.voltage_cmd;
}

/* Termination for atomic system: '<S1>/safety' */
void safety_Term(void)
{
  goniometer_fw0_voltage_variance_Term(&goniometer_fw0_DW.yaw_variance);
  goniometer_fw0_voltage_variance_Term(&goniometer_fw0_DW.voltage_variance);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
