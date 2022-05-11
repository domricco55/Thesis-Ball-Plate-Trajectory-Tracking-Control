/*
 * FSFB_FF_HIL_quick_dirty_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "FSFB_FF_HIL_quick_dirty".
 *
 * Model version              : 5.120
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Tue May 10 19:01:26 2022
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(int32_T),
  sizeof(int64_T),
  sizeof(uint64_T),
  8,
  256,
  sizeof(int32_T),
  sizeof(uint64_T),
  sizeof(int64_T),
  sizeof(char_T),
  sizeof(uchar_T),
  sizeof(time_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "physical_connection",
  "int64_T",
  "uint64_T",
  "string",
  "char_T",
  "int32_T",
  "uint64_T",
  "int64_T",
  "char_T",
  "uchar_T",
  "time_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o1[0]), 18, 0, 256 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o2[0]), 18, 0, 256 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o3[0]), 18, 0, 256 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o4[0]), 18, 0, 256 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o5[0]), 18, 0, 256 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o6[0]), 18, 0, 256 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o7[0]), 18, 0, 256 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o8[0]), 18, 0, 256 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o9[0]), 18, 0, 256 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_B.bx), 0, 0, 49 }
  ,

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE), 0, 0,
    3 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_DW.Scope_PWORK.LoggedData), 11, 0, 29 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_DW.SampleandHold_SubsysRanBC), 2, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  13U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&FSFB_FF_HIL_quick_dirty_P.K1[0]), 0, 0, 47 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_P.Gain_Gain), 19, 0, 1 },

  { (char_T *)(&FSFB_FF_HIL_quick_dirty_P.ManualSwitch_CurrentSetting), 3, 0, 1
  }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  3U,
  rtPTransitions
};

/* [EOF] FSFB_FF_HIL_quick_dirty_dt.h */
