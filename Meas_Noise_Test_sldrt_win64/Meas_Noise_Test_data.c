/*
 * Meas_Noise_Test_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Meas_Noise_Test".
 *
 * Model version              : 5.46
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Tue Apr 26 12:13:44 2022
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Meas_Noise_Test.h"

/* Block parameters (default storage) */
P_Meas_Noise_Test_T Meas_Noise_Test_P = {
  /* Mask Parameter: StreamOutput_MaxMissedTicks
   * Referenced by: '<S1>/Stream Output'
   */
  10.0,

  /* Mask Parameter: StreamInput_MaxMissedTicks
   * Referenced by: '<S2>/Stream Input'
   */
  10.0,

  /* Mask Parameter: StreamOutput_YieldWhenWaiting
   * Referenced by: '<S1>/Stream Output'
   */
  0.0,

  /* Mask Parameter: StreamInput_YieldWhenWaiting
   * Referenced by: '<S2>/Stream Input'
   */
  1.0,

  /* Expression: [0,0]
   * Referenced by: '<Root>/Constant'
   */
  { 0.0, 0.0 },

  /* Expression: pi/180
   * Referenced by: '<S3>/Gain1'
   */
  0.017453292519943295,

  /* Expression: pi/180
   * Referenced by: '<S4>/Gain1'
   */
  0.017453292519943295,

  /* Expression: 1/1000
   * Referenced by: '<S2>/Gain2'
   */
  0.001,

  /* Expression: pi/180
   * Referenced by: '<S5>/Gain1'
   */
  0.017453292519943295,

  /* Expression: pi/180
   * Referenced by: '<S6>/Gain1'
   */
  0.017453292519943295,

  /* Expression: 1/1000
   * Referenced by: '<S2>/Gain1'
   */
  0.001,

  /* Expression: 1/1000
   * Referenced by: '<S2>/Gain3'
   */
  0.001,

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S2>/Gain'
   */
  1099511628
};
