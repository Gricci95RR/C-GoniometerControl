/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: goniometer_sim.c
 *
 * Code generated for Simulink model 'goniometer_sim'.
 *
 * Model version                  : 17.538
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Sep 20 06:51:03 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "goniometer_sim.h"
#include <math.h>
#include "rtwtypes.h"

/* Exported block parameters */
real_T head_crystal_distance = 1.0E+8; /* Variable: head_crystal_distance
                                        * Referenced by: '<S3>/head_cristal_distance'
                                        */
real_T model_den[8] = { 1.0, -2.91928142420295, 3.40119411626474,
  -0.848845344784298, -2.12805010543933, 2.48011029499451, -1.03931778557341,
  0.0791454743725678 } ;               /* Variable: model_den
                                        * Referenced by: '<S1>/model'
                                        */

real_T model_num[8] = { 0.0, 0.0, 0.645312511093494, -0.931664191199637,
  0.324457510477203, 0.431555842303372, -0.391614876447558, -0.038452063195772 }
;                                      /* Variable: model_num
                                        * Referenced by: '<S1>/model'
                                        */

/* Block states (default storage) */
DW_goniometer_sim_T goniometer_sim_DW;

/* External inputs (root inport signals with default storage) */
ExtU_goniometer_sim_T goniometer_sim_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_goniometer_sim_T goniometer_sim_Y;

/* Real-time model */
static RT_MODEL_goniometer_sim_T goniometer_sim_M_;
RT_MODEL_goniometer_sim_T *const goniometer_sim_M = &goniometer_sim_M_;

/* Model step function */
void goniometer_sim_step(void)
{
  real_T denAccum;
  real_T numAccum;
  int32_T denIdx;
  int32_T j;
  int32_T numIdx;

  /* DiscreteTransferFcn: '<S1>/model' */
  numAccum = 0.0;
  denIdx = 1;

  /* Update for DiscreteTransferFcn: '<S1>/model' incorporates:
   *  Inport: '<Root>/control_output'
   */
  denAccum = goniometer_sim_U.control_output.voltage_cmd;
  numIdx = 1;
  for (j = 0; j < 7; j++) {
    /* DiscreteTransferFcn: '<S1>/model' */
    numAccum += model_num[denIdx] * goniometer_sim_DW.model_states[j];
    denIdx++;

    /* Update for DiscreteTransferFcn: '<S1>/model' */
    denAccum -= model_den[numIdx] * goniometer_sim_DW.model_states[j];
    numIdx++;
  }

  /* Gain: '<S3>/Gain' incorporates:
   *  DiscreteTransferFcn: '<S1>/model'
   *  Gain: '<S3>/Gain1'
   *  Gain: '<S3>/mrad_rad_convert'
   *  Trigonometry: '<S3>/Tan'
   */
  numAccum = tan(0.001 * numAccum) * 2500.0;

  /* Outport: '<Root>/dist_1' incorporates:
   *  Constant: '<S3>/head_cristal_distance'
   *  Gain: '<S3>/Gain'
   *  Sum: '<S3>/Add'
   */
  goniometer_sim_Y.dist_1 = head_crystal_distance - numAccum;

  /* Outport: '<Root>/dist_2' incorporates:
   *  Constant: '<S3>/head_cristal_distance'
   *  Sum: '<S3>/Add1'
   */
  goniometer_sim_Y.dist_2 = numAccum + head_crystal_distance;

  /* Update for DiscreteTransferFcn: '<S1>/model' */
  denAccum /= model_den[0];
  for (j = 0; j < 6; j++) {
    goniometer_sim_DW.model_states[6 - j] = goniometer_sim_DW.model_states[5 - j];
  }

  goniometer_sim_DW.model_states[0] = denAccum;
}

/* Model initialize function */
void goniometer_sim_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void goniometer_sim_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
