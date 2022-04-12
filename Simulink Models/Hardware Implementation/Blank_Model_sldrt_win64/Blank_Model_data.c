/*
 * Blank_Model_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Blank_Model".
 *
 * Model version              : 5.20
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Mon Apr 11 14:38:26 2022
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Blank_Model.h"

/* Block parameters (default storage) */
P_Blank_Model_T Blank_Model_P = {
  /* Mask Parameter: DiscreteDerivative1_ICPrevScaledInput
   * Referenced by: '<S3>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative_ICPrevScaledInput
   * Referenced by: '<S2>/UD'
   */
  0.0,

  /* Mask Parameter: StreamInput_MaxMissedTicks
   * Referenced by: '<S12>/Stream Input'
   */
  10.0,

  /* Mask Parameter: StreamOutput_MaxMissedTicks
   * Referenced by: '<S10>/Stream Output'
   */
  10.0,

  /* Mask Parameter: StreamInput_YieldWhenWaiting
   * Referenced by: '<S12>/Stream Input'
   */
  1.0,

  /* Mask Parameter: StreamOutput_YieldWhenWaiting
   * Referenced by: '<S10>/Stream Output'
   */
  0.0,

  /* Expression: pi/180
   * Referenced by: '<S13>/Gain1'
   */
  0.017453292519943295,

  /* Expression: pi/180
   * Referenced by: '<S14>/Gain1'
   */
  0.017453292519943295,

  /* Expression: pi/180
   * Referenced by: '<S15>/Gain1'
   */
  0.017453292519943295,

  /* Expression: pi/180
   * Referenced by: '<S16>/Gain1'
   */
  0.017453292519943295,

  /* Expression: 1/1000
   * Referenced by: '<S12>/Gain1'
   */
  0.001,

  /* Expression: 1/1000
   * Referenced by: '<S12>/Gain2'
   */
  0.001,

  /* Expression: 1/1000
   * Referenced by: '<S12>/Gain3'
   */
  0.001,

  /* Expression: 180/pi
   * Referenced by: '<S4>/Gain'
   */
  57.295779513082323,

  /* Expression: 180/pi
   * Referenced by: '<S7>/Gain'
   */
  57.295779513082323,

  /* Computed Parameter: TSamp_WtEt
   * Referenced by: '<S3>/TSamp'
   */
  200.0,

  /* Computed Parameter: TSamp_WtEt_f
   * Referenced by: '<S2>/TSamp'
   */
  200.0,

  /* Expression: 180/pi
   * Referenced by: '<S5>/Gain'
   */
  57.295779513082323,

  /* Expression: 180/pi
   * Referenced by: '<S6>/Gain'
   */
  57.295779513082323,

  /* Computed Parameter: DiscreteTimeIntegrator_gainval
   * Referenced by: '<S11>/Discrete-Time Integrator'
   */
  0.005,

  /* Expression: 0
   * Referenced by: '<S11>/Discrete-Time Integrator'
   */
  0.0,

  /* Expression: 180/pi
   * Referenced by: '<S8>/Gain'
   */
  57.295779513082323,

  /* Computed Parameter: DiscreteTimeIntegrator1_gainval
   * Referenced by: '<S11>/Discrete-Time Integrator1'
   */
  0.005,

  /* Expression: 0
   * Referenced by: '<S11>/Discrete-Time Integrator1'
   */
  0.0,

  /* Expression: 180/pi
   * Referenced by: '<S9>/Gain'
   */
  57.295779513082323,

  /* Expression: 0
   * Referenced by: '<S11>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S11>/Constant1'
   */
  0.0,

  /* Expression: -1*0.1134/.2499
   * Referenced by: '<S1>/Gear Ratio Assumption'
   */
  -0.453781512605042,

  /* Expression: 0.75
   * Referenced by: '<S1>/Saturation1'
   */
  0.75,

  /* Expression: -.75
   * Referenced by: '<S1>/Saturation1'
   */
  -0.75,

  /* Expression: [0; 0]
   * Referenced by: '<Root>/Constant'
   */
  { 0.0, 0.0 },

  /* Computed Parameter: Gain_Gain_h
   * Referenced by: '<S12>/Gain'
   */
  1099511628
};
