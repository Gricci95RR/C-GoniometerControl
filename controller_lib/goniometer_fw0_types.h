/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: goniometer_fw0_types.h
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

#ifndef RTW_HEADER_goniometer_fw0_types_h_
#define RTW_HEADER_goniometer_fw0_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_MachineStates_
#define DEFINED_TYPEDEF_FOR_MachineStates_

typedef uint8_T MachineStates;

/* enum MachineStates */
#define StandBy                        ((MachineStates)0U)       /* Default value */
#define OpenLoop                       ((MachineStates)1U)
#define ClosingTheLoop                 ((MachineStates)5U)
#define OpeningTheLoop                 ((MachineStates)3U)
#define Service                        ((MachineStates)4U)
#define ClosedLoop                     ((MachineStates)2U)
#endif

#ifndef DEFINED_TYPEDEF_FOR_MachineOutputs_
#define DEFINED_TYPEDEF_FOR_MachineOutputs_

typedef struct {
  MachineStates machine_state;
  boolean_T listening_control_mode_change;
  boolean_T listening_start_motion;
  boolean_T listening_stop_motion;
  boolean_T enable_closed_loop;
  boolean_T stop_motion;
  boolean_T reset_yaw;
  boolean_T follow_waveform;
  uint32_T waveform_idx;
} MachineOutputs;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MachineStateRequest_
#define DEFINED_TYPEDEF_FOR_MachineStateRequest_

typedef uint8_T MachineStateRequest;

/* enum MachineStateRequest */
#define StandByRequest                 ((MachineStateRequest)0U) /* Default value */
#define OpenLoopRequest                ((MachineStateRequest)1U)
#define ClosedLoopRequest              ((MachineStateRequest)2U)
#endif

#ifndef DEFINED_TYPEDEF_FOR_UserInputs_
#define DEFINED_TYPEDEF_FOR_UserInputs_

typedef struct {
  MachineStateRequest request_control_mode;
  boolean_T request_start_motion;
  boolean_T request_stop_motion;
  boolean_T request_start_waveform;
  boolean_T request_stop_waveform;
  boolean_T request_warn_reset;
  boolean_T request_hyst_comp;
  real_T voltage_ref;
  real_T yaw_ref;
  uint8_T waveform_number;
  real_T slope_ramp;
  real_T cycle_number;
} UserInputs;

#endif

#ifndef DEFINED_TYPEDEF_FOR_WaveformInfo_
#define DEFINED_TYPEDEF_FOR_WaveformInfo_

typedef struct {
  uint32_T waveform_length;
  real_T waveform_timeout;
  real_T waveform_vector[100000000];
} WaveformInfo;

#endif

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

#ifndef DEFINED_TYPEDEF_FOR_ClosedLoopOutput_
#define DEFINED_TYPEDEF_FOR_ClosedLoopOutput_

typedef struct {
  real_T yaw_error;
  real_T limited_yaw_error;
  real_T pid_output;
  real_T lead_output;
  real_T notch_output;
  real_T cl_voltage_cmd;
} ClosedLoopOutput;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SafetyOutputs_
#define DEFINED_TYPEDEF_FOR_SafetyOutputs_

typedef struct {
  uint32_T warning_level;
} SafetyOutputs;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SensorInputs_
#define DEFINED_TYPEDEF_FOR_SensorInputs_

typedef struct {
  real_T dist1;
  real_T dist2;
  int16_T error1;
  int16_T error2;
} SensorInputs;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ProcessedUserInputs_
#define DEFINED_TYPEDEF_FOR_ProcessedUserInputs_

typedef struct {
  MachineStateRequest control_mode;
  boolean_T control_change;
  boolean_T start_motion;
  boolean_T stop_motion;
  boolean_T start_waveform;
  boolean_T stop_waveform;
  boolean_T warn_reset;
  boolean_T ref_reached;
} ProcessedUserInputs;

#endif

#ifndef struct_tag_3ut1DzKZklvxwoQLASgJkG
#define struct_tag_3ut1DzKZklvxwoQLASgJkG

struct tag_3ut1DzKZklvxwoQLASgJkG
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T pReverseSamples[200];
  real_T pReverseT[200];
  real_T pReverseS[200];
  real_T pT;
  real_T pS;
  real_T pM;
  real_T pCounter;
  real_T pModValueRev;
};

#endif                                 /* struct_tag_3ut1DzKZklvxwoQLASgJkG */

#ifndef typedef_c_dsp_internal_SlidingWindowVarianceCG_goniometer_fw0_T
#define typedef_c_dsp_internal_SlidingWindowVarianceCG_goniometer_fw0_T

typedef struct tag_3ut1DzKZklvxwoQLASgJkG
  c_dsp_internal_SlidingWindowVarianceCG_goniometer_fw0_T;

#endif     /* typedef_c_dsp_internal_SlidingWindowVarianceCG_goniometer_fw0_T */

#ifndef struct_tag_BlgwLpgj2bjudmbmVKWwDE
#define struct_tag_BlgwLpgj2bjudmbmVKWwDE

struct tag_BlgwLpgj2bjudmbmVKWwDE
{
  uint32_T f1[8];
};

#endif                                 /* struct_tag_BlgwLpgj2bjudmbmVKWwDE */

#ifndef typedef_cell_wrap_goniometer_fw0_T
#define typedef_cell_wrap_goniometer_fw0_T

typedef struct tag_BlgwLpgj2bjudmbmVKWwDE cell_wrap_goniometer_fw0_T;

#endif                                 /* typedef_cell_wrap_goniometer_fw0_T */

#ifndef struct_tag_JUGOkHHXfPtTNa5Pbmw3aH
#define struct_tag_JUGOkHHXfPtTNa5Pbmw3aH

struct tag_JUGOkHHXfPtTNa5Pbmw3aH
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_goniometer_fw0_T inputVarSize;
  c_dsp_internal_SlidingWindowVarianceCG_goniometer_fw0_T *pStatistic;
  int32_T NumChannels;
  int32_T FrameLength;
  c_dsp_internal_SlidingWindowVarianceCG_goniometer_fw0_T _pobj0;
};

#endif                                 /* struct_tag_JUGOkHHXfPtTNa5Pbmw3aH */

#ifndef typedef_dsp_simulink_MovingVariance_goniometer_fw0_T
#define typedef_dsp_simulink_MovingVariance_goniometer_fw0_T

typedef struct tag_JUGOkHHXfPtTNa5Pbmw3aH
  dsp_simulink_MovingVariance_goniometer_fw0_T;

#endif                /* typedef_dsp_simulink_MovingVariance_goniometer_fw0_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_goniometer_fw0_T RT_MODEL_goniometer_fw0_T;

#endif                                 /* RTW_HEADER_goniometer_fw0_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
