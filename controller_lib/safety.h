/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: safety.h
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

#ifndef RTW_HEADER_safety_h_
#define RTW_HEADER_safety_h_
#ifndef goniometer_fw0_COMMON_INCLUDES_
#define goniometer_fw0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* goniometer_fw0_COMMON_INCLUDES_ */

#include "goniometer_fw0_types.h"

/* Block states (default storage) for system '<S4>/safety_chart' */
typedef struct {
  uint32_T temporalCounter_i1;         /* '<S4>/safety_chart' */
  uint8_T is_wl0;                      /* '<S4>/safety_chart' */
  uint8_T is_wl1;                      /* '<S4>/safety_chart' */
  uint8_T is_active_c3_goniometer_fw0; /* '<S4>/safety_chart' */
} DW_safety_chart_goniometer_fw0_T;

/* Block signals for system '<S4>/voltage_variance' */
typedef struct {
  real_T voltage_variance;             /* '<S4>/voltage_variance' */
} B_voltage_variance_goniometer_fw0_T;

/* Block states (default storage) for system '<S4>/voltage_variance' */
typedef struct {
  dsp_simulink_MovingVariance_goniometer_fw0_T obj;/* '<S4>/voltage_variance' */
  boolean_T objisempty;                /* '<S4>/voltage_variance' */
} DW_voltage_variance_goniometer_fw0_T;

extern void goniometer_fw0_safety_chart_Init(uint32_T *rty_warning_level);
extern void goniometer_fw0_safety_chart(real_T rtu_yaw_variance, boolean_T
  rtu_reset, real_T rtu_ctrl_variance, uint32_T *rty_warning_level,
  DW_safety_chart_goniometer_fw0_T *localDW);
extern void goniometer_fw0_voltage_variance_Init
  (DW_voltage_variance_goniometer_fw0_T *localDW);
extern void goniometer_fw0_voltage_variance(real_T rtu_0,
  B_voltage_variance_goniometer_fw0_T *localB,
  DW_voltage_variance_goniometer_fw0_T *localDW);
extern void safety_Init(void);
extern void safety_Update(void);
extern void safety(void);
extern void goniometer_fw0_voltage_variance_Term
  (DW_voltage_variance_goniometer_fw0_T *localDW);
extern void safety_Term(void);

#endif                                 /* RTW_HEADER_safety_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
