/*
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, education, and research organizations only. Not
 * for commercial or industrial use.
 *
 * File: state_machine.c
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

#include "goniometer_fw0_types.h"
#include "rtwtypes.h"
#include "state_machine.h"
#include <math.h>

/* Named constants for Chart: '<S5>/machine_chart' */
#define goniometer_fw0_IN_ClosedLoop   ((uint8_T)1U)
#define goniometer_fw0_IN_ClosedLoopIdle ((uint8_T)1U)
#define goniometer_fw0_IN_ClosedLoopMoving ((uint8_T)2U)
#define goniometer_fw0_IN_ClosingTheLoop ((uint8_T)2U)
#define goniometer_fw0_IN_EnteringService ((uint8_T)1U)
#define goniometer_fw0_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define goniometer_fw0_IN_OpenLoop     ((uint8_T)3U)
#define goniometer_fw0_IN_OpenLoopIdle ((uint8_T)2U)
#define goniometer_fw0_IN_OpenLoopMoving ((uint8_T)3U)
#define goniometer_fw0_IN_OpeningTheLoop ((uint8_T)4U)
#define goniometer_fw0_IN_Service      ((uint8_T)4U)
#define goniometer_fw0_IN_Standby      ((uint8_T)5U)

/* Forward declaration for local functions */
static void goniometer_fw0_OpenLoop(boolean_T *listening_control_mode_change,
  boolean_T *listening_start_motion, boolean_T *listening_stop_motion,
  MachineStates *state, const SafetyOutputs *rtu_safety_output_Inport_1,
  MachineStateRequest rtu_validated_user_inputs_Inport_2, boolean_T
  rtu_validated_user_inputs_Inport_2_p, boolean_T
  rtu_validated_user_inputs_Inport_2_b, boolean_T
  rtu_validated_user_inputs_Inport_2_j, boolean_T
  rtu_validated_user_inputs_Inport_2_f, boolean_T
  rtu_validated_user_inputs_Inport_2_pm, boolean_T
  rtu_validated_user_inputs_Inport_2_a, uint32_T rtu_waveform_info_Inport_3,
  real_T rtu_waveform_info_Inport_3_p, B_state_machine_T *localB,
  DW_state_machine_T *localDW);

/* Function for Chart: '<S5>/machine_chart' */
static void goniometer_fw0_OpenLoop(boolean_T *listening_control_mode_change,
  boolean_T *listening_start_motion, boolean_T *listening_stop_motion,
  MachineStates *state, const SafetyOutputs *rtu_safety_output_Inport_1,
  MachineStateRequest rtu_validated_user_inputs_Inport_2, boolean_T
  rtu_validated_user_inputs_Inport_2_p, boolean_T
  rtu_validated_user_inputs_Inport_2_b, boolean_T
  rtu_validated_user_inputs_Inport_2_j, boolean_T
  rtu_validated_user_inputs_Inport_2_f, boolean_T
  rtu_validated_user_inputs_Inport_2_pm, boolean_T
  rtu_validated_user_inputs_Inport_2_a, uint32_T rtu_waveform_info_Inport_3,
  real_T rtu_waveform_info_Inport_3_p, B_state_machine_T *localB,
  DW_state_machine_T *localDW)
{
  uint32_T qY;
  boolean_T d_out;
  *state = OpenLoop;
  localB->enable_closed_loop = false;

  /* Chart: '<S5>/machine_chart' */
  if (rtu_validated_user_inputs_Inport_2_p &&
      (rtu_validated_user_inputs_Inport_2 == ClosedLoopRequest) &&
      (rtu_safety_output_Inport_1->warning_level == 0U)) {
    localDW->is_OpenLoop = goniometer_fw0_IN_NO_ACTIVE_CHILD;
    localDW->is_c9_goniometer_fw0 = goniometer_fw0_IN_ClosingTheLoop;
    localDW->temporalCounter_i1 = 0U;
    *state = ClosingTheLoop;
    *listening_control_mode_change = false;
    *listening_start_motion = false;
    *listening_stop_motion = false;
    localB->reset_yaw = true;
  } else if ((rtu_validated_user_inputs_Inport_2_p &&
              (rtu_validated_user_inputs_Inport_2 == StandByRequest)) ||
             (rtu_safety_output_Inport_1->warning_level > 0U)) {
    localDW->is_OpenLoop = goniometer_fw0_IN_NO_ACTIVE_CHILD;
    localDW->is_c9_goniometer_fw0 = goniometer_fw0_IN_Standby;
    *state = StandBy;
    *listening_control_mode_change = true;
    *listening_start_motion = false;
    *listening_stop_motion = false;
    localB->waveform_idx = 1U;
  } else {
    switch (localDW->is_OpenLoop) {
     case goniometer_fw0_IN_EnteringService:
      *listening_control_mode_change = false;
      *listening_start_motion = false;
      *listening_stop_motion = false;
      localB->follow_waveform = true;
      localB->stop_motion = false;
      if (rtu_validated_user_inputs_Inport_2_a) {
        localDW->is_OpenLoop = goniometer_fw0_IN_Service;
        localDW->temporalCounter_i1 = 0U;
        *listening_control_mode_change = false;
        *listening_start_motion = false;
        *listening_stop_motion = true;
        localB->waveform_idx = 1U;
      }
      break;

     case goniometer_fw0_IN_OpenLoopIdle:
      *listening_control_mode_change = true;
      *listening_start_motion = true;
      *listening_stop_motion = false;
      localB->follow_waveform = false;
      localB->stop_motion = true;
      if (rtu_validated_user_inputs_Inport_2_b) {
        localDW->is_OpenLoop = goniometer_fw0_IN_EnteringService;
        *listening_control_mode_change = false;
        *listening_start_motion = false;
        *listening_stop_motion = false;
        localB->follow_waveform = true;
        localB->stop_motion = false;
        localB->waveform_idx = 1U;
      } else if (rtu_validated_user_inputs_Inport_2_j) {
        localDW->is_OpenLoop = goniometer_fw0_IN_OpenLoopMoving;
        *listening_control_mode_change = false;
        *listening_start_motion = false;
        *listening_stop_motion = true;
        localB->stop_motion = false;
      }
      break;

     case goniometer_fw0_IN_OpenLoopMoving:
      *listening_control_mode_change = false;
      *listening_start_motion = false;
      *listening_stop_motion = true;
      localB->stop_motion = false;
      if (rtu_validated_user_inputs_Inport_2_a ||
          rtu_validated_user_inputs_Inport_2_f) {
        localDW->is_OpenLoop = goniometer_fw0_IN_OpenLoopIdle;
        *listening_control_mode_change = true;
        *listening_start_motion = true;
        *listening_stop_motion = false;
        localB->follow_waveform = false;
        localB->stop_motion = true;
      }
      break;

     default:
      /* case IN_Service: */
      *listening_control_mode_change = false;
      *listening_start_motion = false;
      *listening_stop_motion = true;
      localB->follow_waveform = true;
      if (localB->waveform_idx == rtu_waveform_info_Inport_3) {
        d_out = true;
      } else {
        d_out = ((localDW->temporalCounter_i1 >= (uint32_T)ceil
                  (rtu_waveform_info_Inport_3_p / 0.0005 -
                   5.0000000000000005E-12)) ||
                 (rtu_validated_user_inputs_Inport_2_pm ||
                  (rtu_safety_output_Inport_1->warning_level > 0U)));
      }

      if (d_out) {
        localDW->is_OpenLoop = goniometer_fw0_IN_OpenLoopIdle;
        *listening_control_mode_change = true;
        *listening_start_motion = true;
        *listening_stop_motion = false;
        localB->follow_waveform = false;
        localB->stop_motion = true;
      } else {
        qY = localB->waveform_idx + /*MW:OvSatOk*/ 1U;
        if (localB->waveform_idx + 1U < localB->waveform_idx) {
          qY = MAX_uint32_T;
        }

        localB->waveform_idx = qY;
      }
      break;
    }
  }

  /* End of Chart: '<S5>/machine_chart' */
}

/* Output and update for atomic system: '<S1>/state_machine' */
void state_machine(const SafetyOutputs *rtu_safety_output_Inport_1,
                   MachineStateRequest rtu_validated_user_inputs_Inport_2,
                   boolean_T rtu_validated_user_inputs_Inport_2_p, boolean_T
                   rtu_validated_user_inputs_Inport_2_b, boolean_T
                   rtu_validated_user_inputs_Inport_2_j, boolean_T
                   rtu_validated_user_inputs_Inport_2_f, boolean_T
                   rtu_validated_user_inputs_Inport_2_pm, boolean_T
                   rtu_validated_user_inputs_Inport_2_a, uint32_T
                   rtu_waveform_info_Inport_3, real_T
                   rtu_waveform_info_Inport_3_p, MachineOutputs
                   *rty_machine_output_Outport_1, B_state_machine_T *localB,
                   DW_state_machine_T *localDW)
{
  boolean_T listening_control_mode_change;
  boolean_T listening_start_motion;
  boolean_T listening_stop_motion;

  /* Chart: '<S5>/machine_chart' incorporates:
   *  Delay: '<S5>/yaw_reset_delay'
   */
  if (localDW->temporalCounter_i1 < MAX_uint32_T) {
    localDW->temporalCounter_i1++;
  }

  if (localDW->is_active_c9_goniometer_fw0 == 0U) {
    localDW->is_active_c9_goniometer_fw0 = 1U;
    localDW->is_c9_goniometer_fw0 = goniometer_fw0_IN_Standby;

    /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
    rty_machine_output_Outport_1->machine_state = StandBy;
    localB->enable_closed_loop = false;
    listening_control_mode_change = true;
    listening_start_motion = false;
    listening_stop_motion = false;
    localB->waveform_idx = 1U;
  } else {
    switch (localDW->is_c9_goniometer_fw0) {
     case goniometer_fw0_IN_ClosedLoop:
      /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
      rty_machine_output_Outport_1->machine_state = ClosedLoop;
      localB->enable_closed_loop = true;
      if ((rtu_validated_user_inputs_Inport_2_p &&
           (rtu_validated_user_inputs_Inport_2 == OpenLoopRequest)) ||
          (rtu_validated_user_inputs_Inport_2_p &&
           (rtu_validated_user_inputs_Inport_2 == StandByRequest)) ||
          (rtu_safety_output_Inport_1->warning_level > 0U)) {
        localDW->is_ClosedLoop = goniometer_fw0_IN_NO_ACTIVE_CHILD;
        localDW->is_c9_goniometer_fw0 = goniometer_fw0_IN_OpeningTheLoop;
        localDW->temporalCounter_i1 = 0U;

        /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
        rty_machine_output_Outport_1->machine_state = OpeningTheLoop;
        listening_control_mode_change = false;
        listening_start_motion = false;
        listening_stop_motion = false;
        localB->enable_closed_loop = false;
        localB->reset_yaw = true;
      } else if (localDW->is_ClosedLoop == goniometer_fw0_IN_ClosedLoopIdle) {
        listening_control_mode_change = true;
        listening_start_motion = true;
        listening_stop_motion = false;
        localB->stop_motion = true;
        if (rtu_validated_user_inputs_Inport_2_j) {
          localDW->is_ClosedLoop = goniometer_fw0_IN_ClosedLoopMoving;
          listening_control_mode_change = false;
          listening_start_motion = false;
          listening_stop_motion = true;
          localB->stop_motion = false;
        }
      } else {
        /* case IN_ClosedLoopMoving: */
        listening_control_mode_change = false;
        listening_start_motion = false;
        listening_stop_motion = true;
        localB->stop_motion = false;
        if (rtu_validated_user_inputs_Inport_2_a ||
            rtu_validated_user_inputs_Inport_2_f) {
          localDW->is_ClosedLoop = goniometer_fw0_IN_ClosedLoopIdle;
          listening_control_mode_change = true;
          listening_start_motion = true;
          listening_stop_motion = false;
          localB->stop_motion = true;
        }
      }
      break;

     case goniometer_fw0_IN_ClosingTheLoop:
      /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
      rty_machine_output_Outport_1->machine_state = ClosingTheLoop;
      listening_control_mode_change = false;
      listening_start_motion = false;
      listening_stop_motion = false;
      if (localDW->yaw_reset_delay_DSTATE) {
        localDW->is_c9_goniometer_fw0 = goniometer_fw0_IN_ClosedLoop;

        /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
        rty_machine_output_Outport_1->machine_state = ClosedLoop;
        localB->enable_closed_loop = true;
        localB->reset_yaw = false;
        localDW->is_ClosedLoop = goniometer_fw0_IN_ClosedLoopIdle;
        listening_control_mode_change = true;
        listening_start_motion = true;
        localB->stop_motion = true;
      } else if ((localDW->temporalCounter_i1 >= 2000U) ||
                 (rtu_safety_output_Inport_1->warning_level > 0U)) {
        localDW->is_c9_goniometer_fw0 = goniometer_fw0_IN_OpenLoop;

        /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
        rty_machine_output_Outport_1->machine_state = OpenLoop;
        localB->enable_closed_loop = false;
        localB->reset_yaw = false;
        localDW->is_OpenLoop = goniometer_fw0_IN_OpenLoopIdle;
        listening_control_mode_change = true;
        listening_start_motion = true;
        localB->follow_waveform = false;
        localB->stop_motion = true;
      } else {
        localB->reset_yaw = false;
      }
      break;

     case goniometer_fw0_IN_OpenLoop:
      /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
      goniometer_fw0_OpenLoop(&listening_control_mode_change,
        &listening_start_motion, &listening_stop_motion,
        &rty_machine_output_Outport_1->machine_state, rtu_safety_output_Inport_1,
        rtu_validated_user_inputs_Inport_2, rtu_validated_user_inputs_Inport_2_p,
        rtu_validated_user_inputs_Inport_2_b,
        rtu_validated_user_inputs_Inport_2_j,
        rtu_validated_user_inputs_Inport_2_f,
        rtu_validated_user_inputs_Inport_2_pm,
        rtu_validated_user_inputs_Inport_2_a, rtu_waveform_info_Inport_3,
        rtu_waveform_info_Inport_3_p, localB, localDW);
      break;

     case goniometer_fw0_IN_OpeningTheLoop:
      /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
      rty_machine_output_Outport_1->machine_state = OpeningTheLoop;
      listening_control_mode_change = false;
      listening_start_motion = false;
      listening_stop_motion = false;
      localB->enable_closed_loop = false;
      if (localDW->yaw_reset_delay_DSTATE || (localDW->temporalCounter_i1 >=
           2000U) || (rtu_safety_output_Inport_1->warning_level > 0U)) {
        localDW->is_c9_goniometer_fw0 = goniometer_fw0_IN_OpenLoop;

        /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
        rty_machine_output_Outport_1->machine_state = OpenLoop;
        localB->reset_yaw = false;
        localDW->is_OpenLoop = goniometer_fw0_IN_OpenLoopIdle;
        listening_control_mode_change = true;
        listening_start_motion = true;
        localB->follow_waveform = false;
        localB->stop_motion = true;
      } else {
        localB->reset_yaw = false;
      }
      break;

     default:
      /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
      /* case IN_Standby: */
      rty_machine_output_Outport_1->machine_state = StandBy;
      localB->enable_closed_loop = false;
      listening_control_mode_change = true;
      listening_start_motion = false;
      listening_stop_motion = false;
      if (((rtu_validated_user_inputs_Inport_2_p &&
            (rtu_validated_user_inputs_Inport_2 == OpenLoopRequest)) ||
           (rtu_validated_user_inputs_Inport_2_p &&
            (rtu_validated_user_inputs_Inport_2 == ClosedLoopRequest))) &&
          (rtu_safety_output_Inport_1->warning_level == 0U)) {
        localDW->is_c9_goniometer_fw0 = goniometer_fw0_IN_OpenLoop;

        /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
        rty_machine_output_Outport_1->machine_state = OpenLoop;
        localB->reset_yaw = false;
        localDW->is_OpenLoop = goniometer_fw0_IN_OpenLoopIdle;
        listening_start_motion = true;
        localB->follow_waveform = false;
        localB->stop_motion = true;
      }
      break;
    }
  }

  /* End of Chart: '<S5>/machine_chart' */

  /* BusCreator generated from: '<S5>/machine_output_BusCreator' */
  rty_machine_output_Outport_1->listening_control_mode_change =
    listening_control_mode_change;
  rty_machine_output_Outport_1->listening_start_motion = listening_start_motion;
  rty_machine_output_Outport_1->listening_stop_motion = listening_stop_motion;
  rty_machine_output_Outport_1->enable_closed_loop = localB->enable_closed_loop;
  rty_machine_output_Outport_1->stop_motion = localB->stop_motion;
  rty_machine_output_Outport_1->reset_yaw = localB->reset_yaw;
  rty_machine_output_Outport_1->follow_waveform = localB->follow_waveform;
  rty_machine_output_Outport_1->waveform_idx = localB->waveform_idx;

  /* Update for Delay: '<S5>/yaw_reset_delay' */
  localDW->yaw_reset_delay_DSTATE = localB->reset_yaw;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
