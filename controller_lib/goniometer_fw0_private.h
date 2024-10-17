/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: goniometer_fw0_private.h
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

#ifndef RTW_HEADER_goniometer_fw0_private_h_
#define RTW_HEADER_goniometer_fw0_private_h_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "goniometer_fw0_types.h"
#include "goniometer_fw0.h"

extern real_T rt_roundd_snf(real_T u);
extern real_T rt_remd_snf(real_T u0, real_T u1);
extern void goniometer_fw0_goniometer_fw_Init(void);
extern void goniometer_fw0_goniometer_fw(void);
extern void goniometer_fw0_goniometer_fw_Term(void);

#endif                                /* RTW_HEADER_goniometer_fw0_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
