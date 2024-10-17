/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: goniometer_sim.h
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

#ifndef RTW_HEADER_goniometer_sim_h_
#define RTW_HEADER_goniometer_sim_h_
#ifndef goniometer_sim_COMMON_INCLUDES_
#define goniometer_sim_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* goniometer_sim_COMMON_INCLUDES_ */

#include "goniometer_sim_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T model_states[7];              /* '<S1>/model' */
} DW_goniometer_sim_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  ControlOutputs control_output;       /* '<Root>/control_output' */
} ExtU_goniometer_sim_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T dist_1;                       /* '<Root>/dist_1' */
  real_T dist_2;                       /* '<Root>/dist_2' */
} ExtY_goniometer_sim_T;

/* Real-time Model Data Structure */
struct tag_RTM_goniometer_sim_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_goniometer_sim_T goniometer_sim_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_goniometer_sim_T goniometer_sim_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_goniometer_sim_T goniometer_sim_Y;

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T head_crystal_distance;   /* Variable: head_crystal_distance
                                        * Referenced by: '<S3>/head_cristal_distance'
                                        */
extern real_T model_den[8];            /* Variable: model_den
                                        * Referenced by: '<S1>/model'
                                        */
extern real_T model_num[8];            /* Variable: model_num
                                        * Referenced by: '<S1>/model'
                                        */

/* Model entry point functions */
extern void goniometer_sim_initialize(void);
extern void goniometer_sim_step(void);
extern void goniometer_sim_terminate(void);

/* Real-time Model object */
extern RT_MODEL_goniometer_sim_T *const goniometer_sim_M;

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
 * hilite_system('goniometer/goniometer_sim')    - opens subsystem goniometer/goniometer_sim
 * hilite_system('goniometer/goniometer_sim/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'goniometer'
 * '<S1>'   : 'goniometer/goniometer_sim'
 * '<S2>'   : 'goniometer/goniometer_sim/simulate_distances'
 * '<S3>'   : 'goniometer/goniometer_sim/simulate_distances/sim_conditioning'
 */
#endif                                 /* RTW_HEADER_goniometer_sim_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
