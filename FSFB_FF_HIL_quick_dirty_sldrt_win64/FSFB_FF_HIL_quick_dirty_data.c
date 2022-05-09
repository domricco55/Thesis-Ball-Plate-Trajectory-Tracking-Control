/*
 * FSFB_FF_HIL_quick_dirty_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "FSFB_FF_HIL_quick_dirty".
 *
 * Model version              : 5.114
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Thu Apr 28 14:02:33 2022
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FSFB_FF_HIL_quick_dirty.h"

/* Block parameters (default storage) */
P_FSFB_FF_HIL_quick_dirty_T FSFB_FF_HIL_quick_dirty_P = {
  /* Variable: K1
   * Referenced by: '<S1>/Gain1'
   */
  { 0.0, 0.0, 0.0, -282.67803721045618, -44.4338131191797 },

  /* Variable: K2
   * Referenced by: '<S2>/Gain1'
   */
  { 0.0, 0.0, 0.0, -282.67803721045618, -44.4338131191797 },

  /* Variable: Tau
   * Referenced by:
   *   '<S4>/x dim stpt smoothing'
   *   '<S4>/y dim stpt smoothing'
   */
  0.5,

  /* Variable: Ts
   * Referenced by:
   *   '<Root>/Step'
   *   '<Root>/Step1'
   */
  0.005,

  /* Mask Parameter: StreamInput_MaxMissedTicks
   * Referenced by: '<S12>/Stream Input'
   */
  10.0,

  /* Mask Parameter: StreamOutput_MaxMissedTicks
   * Referenced by: '<S11>/Stream Output'
   */
  10.0,

  /* Mask Parameter: StreamInput_YieldWhenWaiting
   * Referenced by: '<S12>/Stream Input'
   */
  1.0,

  /* Mask Parameter: StreamOutput_YieldWhenWaiting
   * Referenced by: '<S11>/Stream Output'
   */
  0.0,

  /* Expression: initCond
   * Referenced by: '<S3>/ '
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Expression: 1/1000
   * Referenced by: '<S12>/Gain1'
   */
  0.001,

  /* Expression: pi/180
   * Referenced by: '<S13>/Gain1'
   */
  0.017453292519943295,

  /* Expression: pi/180
   * Referenced by: '<S14>/Gain1'
   */
  0.017453292519943295,

  /* Expression: 1/1000
   * Referenced by: '<S12>/Gain2'
   */
  0.001,

  /* Expression: 1/1000
   * Referenced by: '<S12>/Gain3'
   */
  0.001,

  /* Expression: pi/180
   * Referenced by: '<S15>/Gain1'
   */
  0.017453292519943295,

  /* Expression: pi/180
   * Referenced by: '<S16>/Gain1'
   */
  0.017453292519943295,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Step'
   */
  1.0,

  /* Computed Parameter: DiscreteTimeIntegrator_gainval
   * Referenced by: '<S1>/Discrete-Time Integrator'
   */
  0.005,

  /* Expression: 0
   * Referenced by: '<S1>/Discrete-Time Integrator'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S4>/Constant'
   */
  0.0,

  /* Computed Parameter: DiscreteTimeIntegrator_gainval_p
   * Referenced by: '<S2>/Discrete-Time Integrator'
   */
  0.005,

  /* Expression: 0
   * Referenced by: '<S2>/Discrete-Time Integrator'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Step1'
   */
  1.0,

  /* Expression: [0;0]
   * Referenced by: '<Root>/Constant'
   */
  { 0.0, 0.0 },

  /* Computed Parameter: DiscreteTimeIntegrator_gainval_c
   * Referenced by: '<S12>/Discrete-Time Integrator'
   */
  0.005,

  /* Expression: 0
   * Referenced by: '<S12>/Discrete-Time Integrator'
   */
  0.0,

  /* Expression: VDefs.l_carm/VDefs.lp
   * Referenced by: '<S5>/Gear Ratio Assumption'
   */
  0.453781512605042,

  /* Expression: 1.5
   * Referenced by: '<S5>/Saturation1'
   */
  1.5,

  /* Expression: -1.5
   * Referenced by: '<S5>/Saturation1'
   */
  -1.5,

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S12>/Gain'
   */
  1099511628,

  /* Computed Parameter: ManualSwitch_CurrentSetting
   * Referenced by: '<Root>/Manual Switch'
   */
  1U
};
