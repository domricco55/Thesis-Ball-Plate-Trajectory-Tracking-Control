/*
 * FSFB_FF_HIL_quick_dirty_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "FSFB_FF_HIL_quick_dirty".
 *
 * Model version              : 5.76
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Tue Apr 26 13:54:49 2022
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
  /* Variable: A
   * Referenced by:
   *   '<S11>/Gain5'
   *   '<S14>/Constant'
   */
  { 0.0, -1.8786, 0.0, 20.2622, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 4.1026, 0.0, 31.3281, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.8786, 0.0, -20.2622, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -4.1026, 0.0,
    31.3281, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 },

  /* Variable: B
   * Referenced by: '<S11>/Gain3'
   */
  { 0.0, -0.8511, 0.0, 9.1798, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.8511, 0.0, 9.1798 },

  /* Variable: H
   * Referenced by:
   *   '<S11>/Gain4'
   *   '<S14>/Constant3'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0 },

  /* Variable: K1
   * Referenced by: '<S1>/Gain1'
   */
  { -0.015389751279415529, -233.0754131630666, -170.77395793754869,
    -243.84905214136845, -28.598828232351483 },

  /* Variable: K2
   * Referenced by: '<S2>/Gain1'
   */
  { 0.015389751279396959, 233.07541316278287, 170.77395793743707,
    -243.84905214127272, -28.59882823234048 },

  /* Variable: Q_KF
   * Referenced by: '<S14>/Constant1'
   */
  { 1.0E-9, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-9, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0E-9, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-9,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-9, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0E-9, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-9, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-9 },

  /* Variable: R_KF
   * Referenced by: '<S14>/Constant2'
   */
  { 1.28E-7, 0.0, -4.0E-8, 1.0E-9, -0.0, -3.9E-8, 0.0, 0.0, -0.0, 0.0, -0.0, 0.0,
    -4.0E-8, -0.0, 1.343E-6, 7.0000000000000006E-9, 0.0, -2.63E-7, 1.0E-9, 0.0,
    7.0000000000000006E-9, 1.67E-7, -0.0, -4.100000000000001E-8, -0.0, -0.0, 0.0,
    -0.0, 0.0, -0.0, -3.9E-8, 0.0, -2.63E-7, -4.100000000000001E-8, -0.0,
    4.213E-6 },

  /* Variable: Tau
   * Referenced by:
   *   '<S4>/x dim stpt smoothing'
   *   '<S4>/y dim stpt smoothing'
   */
  0.5,

  /* Mask Parameter: DiscreteDerivative_ICPrevScaledInput
   * Referenced by: '<S20>/UD'
   */
  0.0,

  /* Mask Parameter: StreamInput_MaxMissedTicks
   * Referenced by: '<S13>/Stream Input'
   */
  10.0,

  /* Mask Parameter: StreamOutput_MaxMissedTicks
   * Referenced by: '<S12>/Stream Output'
   */
  10.0,

  /* Mask Parameter: StreamInput_YieldWhenWaiting
   * Referenced by: '<S13>/Stream Input'
   */
  1.0,

  /* Mask Parameter: StreamOutput_YieldWhenWaiting
   * Referenced by: '<S12>/Stream Output'
   */
  0.0,

  /* Expression: initCond
   * Referenced by: '<S3>/ '
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Expression: 1/1000
   * Referenced by: '<S13>/Gain1'
   */
  0.001,

  /* Expression: pi/180
   * Referenced by: '<S16>/Gain1'
   */
  0.017453292519943295,

  /* Expression: pi/180
   * Referenced by: '<S17>/Gain1'
   */
  0.017453292519943295,

  /* Expression: 1/1000
   * Referenced by: '<S13>/Gain2'
   */
  0.001,

  /* Expression: 1/1000
   * Referenced by: '<S13>/Gain3'
   */
  0.001,

  /* Expression: pi/180
   * Referenced by: '<S18>/Gain1'
   */
  0.017453292519943295,

  /* Expression: pi/180
   * Referenced by: '<S19>/Gain1'
   */
  0.017453292519943295,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

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

  /* Expression: zeros(8,1)
   * Referenced by: '<S11>/Unit Delay1'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Computed Parameter: DiscreteTimeIntegrator_gainval_p
   * Referenced by: '<S2>/Discrete-Time Integrator'
   */
  0.005,

  /* Expression: 0
   * Referenced by: '<S2>/Discrete-Time Integrator'
   */
  0.0,

  /* Expression: -1*VDefs.l_carm/VDefs.lp
   * Referenced by: '<S5>/Gear Ratio Assumption'
   */
  -0.453781512605042,

  /* Expression: 0.75
   * Referenced by: '<S5>/Saturation1'
   */
  0.75,

  /* Expression: -.75
   * Referenced by: '<S5>/Saturation1'
   */
  -0.75,

  /* Expression: zeros(8,8)
   * Referenced by: '<S14>/Unit Delay'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0 },

  /* Computed Parameter: TSamp_WtEt
   * Referenced by: '<S20>/TSamp'
   */
  200.0,

  /* Expression: 0
   * Referenced by: '<S22>/Unit Delay1'
   */
  0.0,

  /* Expression: 1/0.005
   * Referenced by: '<S13>/Constant'
   */
  200.0,

  /* Expression: tau
   * Referenced by: '<S22>/tau'
   */
  0.0025,

  /* Expression: 1
   * Referenced by: '<S24>/Constant'
   */
  1.0,

  /* Expression: 2*zeta
   * Referenced by: '<S24>/Gain'
   */
  0.76536686473017956,

  /* Expression: 0
   * Referenced by: '<S23>/Unit Delay1'
   */
  0.0,

  /* Expression: tau
   * Referenced by: '<S23>/tau'
   */
  0.0025,

  /* Expression: 1
   * Referenced by: '<S25>/Constant'
   */
  1.0,

  /* Expression: 2*zeta
   * Referenced by: '<S25>/Gain'
   */
  1.8477590650225735,

  /* Expression: 1
   * Referenced by: '<S24>/Constant1'
   */
  1.0,

  /* Expression: 2
   * Referenced by: '<S22>/Gain1'
   */
  2.0,

  /* Expression: 0
   * Referenced by: '<S22>/Unit Delay2'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S25>/Constant1'
   */
  1.0,

  /* Expression: 2
   * Referenced by: '<S23>/Gain1'
   */
  2.0,

  /* Expression: 0
   * Referenced by: '<S23>/Unit Delay2'
   */
  0.0,

  /* Computed Parameter: Gain_Gain_a
   * Referenced by: '<S13>/Gain'
   */
  1099511628
};
