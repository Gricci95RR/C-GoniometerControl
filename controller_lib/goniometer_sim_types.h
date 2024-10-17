/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: goniometer_sim_types.h
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

#ifndef RTW_HEADER_goniometer_sim_types_h_
#define RTW_HEADER_goniometer_sim_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_ControlOutputs_
#define DEFINED_TYPEDEF_FOR_ControlOutputs_

typedef struct {
  real_T yaw_ref;
  real_T voltage_ref;
  real_T ol_voltage_cmd;
  real_T cl_voltage_cmd;
  real_T voltage_cmd;
} ControlOutputs;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_goniometer_sim_T RT_MODEL_goniometer_sim_T;

#endif                                 /* RTW_HEADER_goniometer_sim_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
