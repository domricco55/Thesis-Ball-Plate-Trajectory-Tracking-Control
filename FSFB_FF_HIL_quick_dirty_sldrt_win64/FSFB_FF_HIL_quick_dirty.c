/*
 * FSFB_FF_HIL_quick_dirty.c
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
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rtwtypes.h"
#include "FSFB_FF_HIL_quick_dirty_private.h"
#include "zero_crossing_types.h"
#include "rt_nonfinite.h"
#include "FSFB_FF_HIL_quick_dirty_dt.h"

/* options for Simulink Desktop Real-Time board 0 */
static double SLDRTBoardOptions0[] = {
  115200.0,
  8.0,
  0.0,
  0.0,
  1.0,
  0.0,
  0.0,
  0.0,
};

/* list of Simulink Desktop Real-Time timers */
const int SLDRTTimerCount = 1;
const double SLDRTTimers[2] = {
  0.005, 0.0,
};

/* list of Simulink Desktop Real-Time boards */
const int SLDRTBoardCount = 1;
SLDRTBOARD SLDRTBoards[1] = {
  { "Standard_Devices/Serial_Port", 6U, 8, SLDRTBoardOptions0 },
};

/* Block signals (default storage) */
B_FSFB_FF_HIL_quick_dirty_T FSFB_FF_HIL_quick_dirty_B;

/* Block states (default storage) */
DW_FSFB_FF_HIL_quick_dirty_T FSFB_FF_HIL_quick_dirty_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_FSFB_FF_HIL_quick_dirty_T FSFB_FF_HIL_quick_dirty_PrevZCX;

/* Real-time model */
static RT_MODEL_FSFB_FF_HIL_quick_dirty_T FSFB_FF_HIL_quick_dirty_M_;
RT_MODEL_FSFB_FF_HIL_quick_dirty_T *const FSFB_FF_HIL_quick_dirty_M =
  &FSFB_FF_HIL_quick_dirty_M_;

/* Model output function */
void FSFB_FF_HIL_quick_dirty_output(void)
{
  real_T tmp[5];
  real_T tmp_0[5];
  real_T rtb_Step1;
  real_T rtb_yvelTS;
  real_T smoothed_x_tmp;
  real_T smoothed_x_tmp_0;
  real_T tmp_1;
  int32_T rtb_xposTS;
  ZCEventType zcEvent;

  /* Reset subsysRan breadcrumbs */
  srClearBC(FSFB_FF_HIL_quick_dirty_DW.SampleandHold_SubsysRanBC);

  /* MATLAB Function: '<Root>/u_FF' */
  FSFB_FF_HIL_quick_dirty_B.out1[0] = 0.0;
  FSFB_FF_HIL_quick_dirty_B.out1[1] = 0.0;

  /* S-Function (sldrtsi): '<S12>/Stream Input' */
  /* S-Function Block: <S12>/Stream Input */
  {
    char indata[2321U];
    int status;
    const char* terminators = "\r\0\n\0";
    memset(indata, 0, sizeof(indata));
    status = RTBIO_DriverIO(0, STREAMINPUT, IOREADWITHRESET, 2320U, NULL,
      (double*) indata, terminators);
    if (status & 0x1) {
      int nscan = sscanf(indata, "%s %s %s %s %s %s %s %s %s",
                         &FSFB_FF_HIL_quick_dirty_B.StreamInput_o1[0],
                         &FSFB_FF_HIL_quick_dirty_B.StreamInput_o2[0],
                         &FSFB_FF_HIL_quick_dirty_B.StreamInput_o3[0],
                         &FSFB_FF_HIL_quick_dirty_B.StreamInput_o4[0],
                         &FSFB_FF_HIL_quick_dirty_B.StreamInput_o5[0],
                         &FSFB_FF_HIL_quick_dirty_B.StreamInput_o6[0],
                         &FSFB_FF_HIL_quick_dirty_B.StreamInput_o7[0],
                         &FSFB_FF_HIL_quick_dirty_B.StreamInput_o8[0],
                         &FSFB_FF_HIL_quick_dirty_B.StreamInput_o9[0]);
    }
  }

  /* ScanString: '<S12>/String to Double' */
  rtb_xposTS = 0;
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o1[0], "%d", &rtb_xposTS);

  /* Gain: '<S12>/Gain' */
  FSFB_FF_HIL_quick_dirty_B.bx = (real_T)FSFB_FF_HIL_quick_dirty_P.Gain_Gain *
    9.0949470177292824E-13 * (real_T)rtb_xposTS;

  /* ScanString: '<S12>/String to Double1' */
  rtb_yvelTS = 0.0;
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o2[0], "%lf", &rtb_yvelTS);

  /* Gain: '<S12>/Gain1' */
  FSFB_FF_HIL_quick_dirty_B.bx_dot = FSFB_FF_HIL_quick_dirty_P.Gain1_Gain *
    rtb_yvelTS;

  /* ScanString: '<S12>/String to Double4' */
  FSFB_FF_HIL_quick_dirty_B.IMUx = 0.0;

  /* ScanString: '<S12>/String to Double4' */
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o3[0], "%lf",
         &FSFB_FF_HIL_quick_dirty_B.IMUx);

  /* Gain: '<S13>/Gain1' */
  FSFB_FF_HIL_quick_dirty_B.Gain1 = FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_g *
    FSFB_FF_HIL_quick_dirty_B.IMUx;

  /* ScanString: '<S12>/String to Double5' */
  FSFB_FF_HIL_quick_dirty_B.GyroX = 0.0;

  /* ScanString: '<S12>/String to Double5' */
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o4[0], "%lf",
         &FSFB_FF_HIL_quick_dirty_B.GyroX);

  /* Gain: '<S14>/Gain1' */
  FSFB_FF_HIL_quick_dirty_B.Gain1_k = FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_n *
    FSFB_FF_HIL_quick_dirty_B.GyroX;

  /* ScanString: '<S12>/String to Double2' */
  rtb_yvelTS = 0.0;
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o5[0], "%lf", &rtb_yvelTS);

  /* Gain: '<S12>/Gain2' */
  FSFB_FF_HIL_quick_dirty_B.by = FSFB_FF_HIL_quick_dirty_P.Gain2_Gain *
    rtb_yvelTS;

  /* ScanString: '<S12>/String to Double3' */
  rtb_yvelTS = 0.0;
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o6[0], "%lf", &rtb_yvelTS);

  /* Gain: '<S12>/Gain3' */
  FSFB_FF_HIL_quick_dirty_B.by_dot = FSFB_FF_HIL_quick_dirty_P.Gain3_Gain *
    rtb_yvelTS;

  /* ScanString: '<S12>/String to Double6' */
  FSFB_FF_HIL_quick_dirty_B.IMUy = 0.0;

  /* ScanString: '<S12>/String to Double6' */
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o7[0], "%lf",
         &FSFB_FF_HIL_quick_dirty_B.IMUy);

  /* Gain: '<S15>/Gain1' */
  FSFB_FF_HIL_quick_dirty_B.Gain1_l = FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_b *
    FSFB_FF_HIL_quick_dirty_B.IMUy;

  /* ScanString: '<S12>/String to Double7' */
  FSFB_FF_HIL_quick_dirty_B.GyroY = 0.0;

  /* ScanString: '<S12>/String to Double7' */
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o8[0], "%lf",
         &FSFB_FF_HIL_quick_dirty_B.GyroY);

  /* Gain: '<S16>/Gain1' */
  FSFB_FF_HIL_quick_dirty_B.Gain1_n = FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_k *
    FSFB_FF_HIL_quick_dirty_B.GyroY;

  /* Step: '<Root>/Step' incorporates:
   *  Step: '<Root>/Step1'
   */
  tmp_1 = FSFB_FF_HIL_quick_dirty_M->Timing.t[0];
  if (tmp_1 < 2.0 * FSFB_FF_HIL_quick_dirty_P.Ts) {
    /* Step: '<Root>/Step' */
    FSFB_FF_HIL_quick_dirty_B.Step = FSFB_FF_HIL_quick_dirty_P.Step_Y0;
  } else {
    /* Step: '<Root>/Step' */
    FSFB_FF_HIL_quick_dirty_B.Step = FSFB_FF_HIL_quick_dirty_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Outputs for Triggered SubSystem: '<Root>/Sample and Hold' incorporates:
   *  TriggerPort: '<S3>/Trigger'
   */
  zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                     &FSFB_FF_HIL_quick_dirty_PrevZCX.SampleandHold_Trig_ZCE,
                     (FSFB_FF_HIL_quick_dirty_B.Step));
  if (zcEvent != NO_ZCEVENT) {
    /* SignalConversion generated from: '<S3>/In' */
    FSFB_FF_HIL_quick_dirty_B.In[0] = FSFB_FF_HIL_quick_dirty_B.bx;
    FSFB_FF_HIL_quick_dirty_B.In[1] = FSFB_FF_HIL_quick_dirty_B.bx_dot;
    FSFB_FF_HIL_quick_dirty_B.In[2] = FSFB_FF_HIL_quick_dirty_B.Gain1;
    FSFB_FF_HIL_quick_dirty_B.In[3] = FSFB_FF_HIL_quick_dirty_B.Gain1_k;
    FSFB_FF_HIL_quick_dirty_B.In[4] = FSFB_FF_HIL_quick_dirty_B.by;
    FSFB_FF_HIL_quick_dirty_B.In[5] = FSFB_FF_HIL_quick_dirty_B.by_dot;
    FSFB_FF_HIL_quick_dirty_B.In[6] = FSFB_FF_HIL_quick_dirty_B.Gain1_l;
    FSFB_FF_HIL_quick_dirty_B.In[7] = FSFB_FF_HIL_quick_dirty_B.Gain1_n;
    FSFB_FF_HIL_quick_dirty_DW.SampleandHold_SubsysRanBC = 4;
  }

  /* End of Outputs for SubSystem: '<Root>/Sample and Hold' */
  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_B.integratederror =
    FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE;

  /* MATLAB Function: '<S4>/x dim stpt smoothing' incorporates:
   *  Clock: '<S4>/Clock1'
   *  Constant: '<S4>/Constant'
   *  MATLAB Function: '<S4>/x_Setpoint_Function'
   *  MATLAB Function: '<S4>/y dim stpt smoothing'
   *  SignalConversion generated from: '<S7>/ SFunction '
   */
  rtb_Step1 = exp(-FSFB_FF_HIL_quick_dirty_M->Timing.t[0] /
                  FSFB_FF_HIL_quick_dirty_P.Tau);
  smoothed_x_tmp = (1.0 - rtb_Step1) * 0.0;
  FSFB_FF_HIL_quick_dirty_B.smoothed_x[0] = FSFB_FF_HIL_quick_dirty_B.In[0] *
    rtb_Step1 + smoothed_x_tmp;
  FSFB_FF_HIL_quick_dirty_B.smoothed_x[1] = FSFB_FF_HIL_quick_dirty_B.In[2] *
    rtb_Step1 + smoothed_x_tmp;
  smoothed_x_tmp_0 = FSFB_FF_HIL_quick_dirty_P.Constant_Value * rtb_Step1 +
    smoothed_x_tmp;
  FSFB_FF_HIL_quick_dirty_B.smoothed_x[2] = smoothed_x_tmp_0;
  FSFB_FF_HIL_quick_dirty_B.smoothed_x[3] = smoothed_x_tmp_0;

  /* Sum: '<S1>/Sum' */
  FSFB_FF_HIL_quick_dirty_B.e_vec[0] = FSFB_FF_HIL_quick_dirty_B.smoothed_x[0] -
    FSFB_FF_HIL_quick_dirty_B.bx;
  FSFB_FF_HIL_quick_dirty_B.e_vec[1] = FSFB_FF_HIL_quick_dirty_B.smoothed_x[1] -
    FSFB_FF_HIL_quick_dirty_B.bx_dot;
  FSFB_FF_HIL_quick_dirty_B.e_vec[2] = FSFB_FF_HIL_quick_dirty_B.smoothed_x[2] -
    FSFB_FF_HIL_quick_dirty_B.Gain1;
  FSFB_FF_HIL_quick_dirty_B.e_vec[3] = FSFB_FF_HIL_quick_dirty_B.smoothed_x[3] -
    FSFB_FF_HIL_quick_dirty_B.Gain1_k;

  /* Gain: '<S1>/Gain1' incorporates:
   *  SignalConversion generated from: '<S1>/Gain1'
   */
  tmp[0] = FSFB_FF_HIL_quick_dirty_B.integratederror;
  tmp[1] = FSFB_FF_HIL_quick_dirty_B.e_vec[0];
  tmp[2] = FSFB_FF_HIL_quick_dirty_B.e_vec[1];
  tmp[3] = FSFB_FF_HIL_quick_dirty_B.e_vec[2];
  tmp[4] = FSFB_FF_HIL_quick_dirty_B.e_vec[3];
  rtb_yvelTS = 0.0;

  /* DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_B.integratederror_d =
    FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_b;

  /* MATLAB Function: '<S4>/y dim stpt smoothing' incorporates:
   *  SignalConversion generated from: '<S9>/ SFunction '
   */
  FSFB_FF_HIL_quick_dirty_B.smoothed_y[0] = FSFB_FF_HIL_quick_dirty_B.In[4] *
    rtb_Step1 + smoothed_x_tmp;
  FSFB_FF_HIL_quick_dirty_B.smoothed_y[1] = smoothed_x_tmp_0;
  FSFB_FF_HIL_quick_dirty_B.smoothed_y[2] = FSFB_FF_HIL_quick_dirty_B.In[6] *
    rtb_Step1 + smoothed_x_tmp;
  FSFB_FF_HIL_quick_dirty_B.smoothed_y[3] = smoothed_x_tmp_0;

  /* Sum: '<S2>/Sum' */
  FSFB_FF_HIL_quick_dirty_B.ey_vec[0] = FSFB_FF_HIL_quick_dirty_B.smoothed_y[0]
    - FSFB_FF_HIL_quick_dirty_B.by;
  FSFB_FF_HIL_quick_dirty_B.ey_vec[1] = FSFB_FF_HIL_quick_dirty_B.smoothed_y[1]
    - FSFB_FF_HIL_quick_dirty_B.by_dot;
  FSFB_FF_HIL_quick_dirty_B.ey_vec[2] = FSFB_FF_HIL_quick_dirty_B.smoothed_y[2]
    - FSFB_FF_HIL_quick_dirty_B.Gain1_l;
  FSFB_FF_HIL_quick_dirty_B.ey_vec[3] = FSFB_FF_HIL_quick_dirty_B.smoothed_y[3]
    - FSFB_FF_HIL_quick_dirty_B.Gain1_n;

  /* SignalConversion generated from: '<S2>/Gain1' */
  tmp_0[0] = FSFB_FF_HIL_quick_dirty_B.integratederror_d;
  tmp_0[1] = FSFB_FF_HIL_quick_dirty_B.ey_vec[0];
  tmp_0[2] = FSFB_FF_HIL_quick_dirty_B.ey_vec[1];
  tmp_0[3] = FSFB_FF_HIL_quick_dirty_B.ey_vec[2];
  tmp_0[4] = FSFB_FF_HIL_quick_dirty_B.ey_vec[3];

  /* Gain: '<S2>/Gain1' */
  smoothed_x_tmp = 0.0;
  for (rtb_xposTS = 0; rtb_xposTS < 5; rtb_xposTS++) {
    /* Gain: '<S1>/Gain1' */
    rtb_yvelTS += -FSFB_FF_HIL_quick_dirty_P.K1[rtb_xposTS] * tmp[rtb_xposTS];

    /* Gain: '<S2>/Gain1' */
    smoothed_x_tmp += -FSFB_FF_HIL_quick_dirty_P.K2[rtb_xposTS] *
      tmp_0[rtb_xposTS];
  }

  /* Step: '<Root>/Step1' */
  if (tmp_1 < 2.0 * FSFB_FF_HIL_quick_dirty_P.Ts) {
    rtb_Step1 = FSFB_FF_HIL_quick_dirty_P.Step1_Y0;
  } else {
    rtb_Step1 = FSFB_FF_HIL_quick_dirty_P.Step1_YFinal;
  }

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S2>/Gain1'
   *  Sum: '<Root>/Sum'
   */
  FSFB_FF_HIL_quick_dirty_B.Product[0] = (rtb_yvelTS +
    FSFB_FF_HIL_quick_dirty_B.out1[0]) * rtb_Step1;
  FSFB_FF_HIL_quick_dirty_B.Product[1] = (smoothed_x_tmp +
    FSFB_FF_HIL_quick_dirty_B.out1[1]) * rtb_Step1;

  /* ManualSwitch: '<Root>/Manual Switch' */
  if (FSFB_FF_HIL_quick_dirty_P.ManualSwitch_CurrentSetting == 1) {
    /* ManualSwitch: '<Root>/Manual Switch' */
    FSFB_FF_HIL_quick_dirty_B.ManualSwitch[0] =
      FSFB_FF_HIL_quick_dirty_B.Product[0];
    FSFB_FF_HIL_quick_dirty_B.ManualSwitch[1] =
      FSFB_FF_HIL_quick_dirty_B.Product[1];
  } else {
    /* ManualSwitch: '<Root>/Manual Switch' incorporates:
     *  Constant: '<Root>/Constant'
     */
    FSFB_FF_HIL_quick_dirty_B.ManualSwitch[0] =
      FSFB_FF_HIL_quick_dirty_P.Constant_Value_h[0];
    FSFB_FF_HIL_quick_dirty_B.ManualSwitch[1] =
      FSFB_FF_HIL_quick_dirty_P.Constant_Value_h[1];
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */
  /* DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_B.xb_int =
    FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_g;

  /* ToAsyncQueueBlock generated from: '<S12>/Discrete-Time Integrator' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.xb_int;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(1299784414U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S12>/Gain1' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.bx_dot;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3228401402U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S12>/Gain2' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.by;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3611628760U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S12>/Gain3' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.by_dot;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3704709920U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S12>/Gain' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.bx;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(872081594U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S12>/String to Double4' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.IMUx;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3389554455U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S12>/String to Double5' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.GyroX;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3844264298U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S12>/String to Double6' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.IMUy;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(460122515U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S12>/String to Double7' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.GyroY;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(391363080U, time, pData, size);
    }
  }

  /* ScanString: '<S12>/String to Double8' */
  FSFB_FF_HIL_quick_dirty_B.TimingParity = 0.0;

  /* ScanString: '<S12>/String to Double8' */
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o9[0], "%lf",
         &FSFB_FF_HIL_quick_dirty_B.TimingParity);

  /* ToAsyncQueueBlock generated from: '<S12>/String to Double8' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.TimingParity;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2154856287U, time, pData, size);
    }
  }

  /* Gain: '<S5>/Gear Ratio Assumption' */
  rtb_yvelTS = FSFB_FF_HIL_quick_dirty_P.GearRatioAssumption_Gain *
    FSFB_FF_HIL_quick_dirty_B.ManualSwitch[0];

  /* Saturate: '<S5>/Saturation1' */
  if (rtb_yvelTS > FSFB_FF_HIL_quick_dirty_P.Saturation1_UpperSat) {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[0] =
      FSFB_FF_HIL_quick_dirty_P.Saturation1_UpperSat;
  } else if (rtb_yvelTS < FSFB_FF_HIL_quick_dirty_P.Saturation1_LowerSat) {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[0] =
      FSFB_FF_HIL_quick_dirty_P.Saturation1_LowerSat;
  } else {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[0] = rtb_yvelTS;
  }

  /* Gain: '<S5>/Gear Ratio Assumption' */
  rtb_yvelTS = FSFB_FF_HIL_quick_dirty_P.GearRatioAssumption_Gain *
    FSFB_FF_HIL_quick_dirty_B.ManualSwitch[1];

  /* Saturate: '<S5>/Saturation1' */
  if (rtb_yvelTS > FSFB_FF_HIL_quick_dirty_P.Saturation1_UpperSat) {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[1] =
      FSFB_FF_HIL_quick_dirty_P.Saturation1_UpperSat;
  } else if (rtb_yvelTS < FSFB_FF_HIL_quick_dirty_P.Saturation1_LowerSat) {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[1] =
      FSFB_FF_HIL_quick_dirty_P.Saturation1_LowerSat;
  } else {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[1] = rtb_yvelTS;
  }

  /* S-Function (sldrtso): '<S11>/Stream Output' */
  /* S-Function Block: <S11>/Stream Output */

  /* no code required */

  /* ToAsyncQueueBlock generated from: '<S5>/Saturation1' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.Torque_Sat[0];
      int32_T size = 2*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3187288116U, time, pData, size);
    }
  }
}

/* Model update function */
void FSFB_FF_HIL_quick_dirty_update(void)
{
  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE +=
    FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_gainval *
    FSFB_FF_HIL_quick_dirty_B.e_vec[0];

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_b +=
    FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_gainval_p *
    FSFB_FF_HIL_quick_dirty_B.ey_vec[0];

  /* Update for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_g +=
    FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_gainval_c *
    FSFB_FF_HIL_quick_dirty_B.bx_dot;

  /* Update for S-Function (sldrtso): '<S11>/Stream Output' */

  /* S-Function Block: <S11>/Stream Output */
  {
    char_T outstring[650U];
    int n = snprintf(outstring, 650U, "%g %g\n", (real_T)
                     FSFB_FF_HIL_quick_dirty_B.Torque_Sat[0], (real_T)
                     FSFB_FF_HIL_quick_dirty_B.Torque_Sat[1]);
    RTBIO_DriverIO(0, STREAMOUTPUT, IOWRITE, n, NULL, (double*) outstring, NULL);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++FSFB_FF_HIL_quick_dirty_M->Timing.clockTick0)) {
    ++FSFB_FF_HIL_quick_dirty_M->Timing.clockTickH0;
  }

  FSFB_FF_HIL_quick_dirty_M->Timing.t[0] =
    FSFB_FF_HIL_quick_dirty_M->Timing.clockTick0 *
    FSFB_FF_HIL_quick_dirty_M->Timing.stepSize0 +
    FSFB_FF_HIL_quick_dirty_M->Timing.clockTickH0 *
    FSFB_FF_HIL_quick_dirty_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.005s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++FSFB_FF_HIL_quick_dirty_M->Timing.clockTick1)) {
      ++FSFB_FF_HIL_quick_dirty_M->Timing.clockTickH1;
    }

    FSFB_FF_HIL_quick_dirty_M->Timing.t[1] =
      FSFB_FF_HIL_quick_dirty_M->Timing.clockTick1 *
      FSFB_FF_HIL_quick_dirty_M->Timing.stepSize1 +
      FSFB_FF_HIL_quick_dirty_M->Timing.clockTickH1 *
      FSFB_FF_HIL_quick_dirty_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void FSFB_FF_HIL_quick_dirty_initialize(void)
{
  /* Start for S-Function (sldrtso): '<S11>/Stream Output' */

  /* S-Function Block: <S11>/Stream Output */
  /* no initial value should be set */
  FSFB_FF_HIL_quick_dirty_PrevZCX.SampleandHold_Trig_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE =
    FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_b =
    FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_IC_l;

  /* InitializeConditions for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_g =
    FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_IC_h;

  /* SystemInitialize for Triggered SubSystem: '<Root>/Sample and Hold' */
  /* SystemInitialize for SignalConversion generated from: '<S3>/In' incorporates:
   *  Outport: '<S3>/ '
   */
  memcpy(&FSFB_FF_HIL_quick_dirty_B.In[0], &FSFB_FF_HIL_quick_dirty_P._Y0[0],
         sizeof(real_T) << 3U);

  /* End of SystemInitialize for SubSystem: '<Root>/Sample and Hold' */
}

/* Model terminate function */
void FSFB_FF_HIL_quick_dirty_terminate(void)
{
  /* Terminate for S-Function (sldrtso): '<S11>/Stream Output' */

  /* no final value should be set */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  FSFB_FF_HIL_quick_dirty_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  FSFB_FF_HIL_quick_dirty_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  FSFB_FF_HIL_quick_dirty_initialize();
}

void MdlTerminate(void)
{
  FSFB_FF_HIL_quick_dirty_terminate();
}

/* Registration function */
RT_MODEL_FSFB_FF_HIL_quick_dirty_T *FSFB_FF_HIL_quick_dirty(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)FSFB_FF_HIL_quick_dirty_M, 0,
                sizeof(RT_MODEL_FSFB_FF_HIL_quick_dirty_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&FSFB_FF_HIL_quick_dirty_M->solverInfo,
                          &FSFB_FF_HIL_quick_dirty_M->Timing.simTimeStep);
    rtsiSetTPtr(&FSFB_FF_HIL_quick_dirty_M->solverInfo, &rtmGetTPtr
                (FSFB_FF_HIL_quick_dirty_M));
    rtsiSetStepSizePtr(&FSFB_FF_HIL_quick_dirty_M->solverInfo,
                       &FSFB_FF_HIL_quick_dirty_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&FSFB_FF_HIL_quick_dirty_M->solverInfo,
                          (&rtmGetErrorStatus(FSFB_FF_HIL_quick_dirty_M)));
    rtsiSetRTModelPtr(&FSFB_FF_HIL_quick_dirty_M->solverInfo,
                      FSFB_FF_HIL_quick_dirty_M);
  }

  rtsiSetSimTimeStep(&FSFB_FF_HIL_quick_dirty_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&FSFB_FF_HIL_quick_dirty_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = FSFB_FF_HIL_quick_dirty_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "FSFB_FF_HIL_quick_dirty_M points to
       static memory which is guaranteed to be non-NULL" */
    FSFB_FF_HIL_quick_dirty_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    FSFB_FF_HIL_quick_dirty_M->Timing.sampleTimes =
      (&FSFB_FF_HIL_quick_dirty_M->Timing.sampleTimesArray[0]);
    FSFB_FF_HIL_quick_dirty_M->Timing.offsetTimes =
      (&FSFB_FF_HIL_quick_dirty_M->Timing.offsetTimesArray[0]);

    /* task periods */
    FSFB_FF_HIL_quick_dirty_M->Timing.sampleTimes[0] = (0.0);
    FSFB_FF_HIL_quick_dirty_M->Timing.sampleTimes[1] = (0.005);

    /* task offsets */
    FSFB_FF_HIL_quick_dirty_M->Timing.offsetTimes[0] = (0.0);
    FSFB_FF_HIL_quick_dirty_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(FSFB_FF_HIL_quick_dirty_M,
             &FSFB_FF_HIL_quick_dirty_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = FSFB_FF_HIL_quick_dirty_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    FSFB_FF_HIL_quick_dirty_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(FSFB_FF_HIL_quick_dirty_M, 30.0);
  FSFB_FF_HIL_quick_dirty_M->Timing.stepSize0 = 0.005;
  FSFB_FF_HIL_quick_dirty_M->Timing.stepSize1 = 0.005;

  /* External mode info */
  FSFB_FF_HIL_quick_dirty_M->Sizes.checksums[0] = (2957840969U);
  FSFB_FF_HIL_quick_dirty_M->Sizes.checksums[1] = (608291789U);
  FSFB_FF_HIL_quick_dirty_M->Sizes.checksums[2] = (1731593454U);
  FSFB_FF_HIL_quick_dirty_M->Sizes.checksums[3] = (91589513U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    FSFB_FF_HIL_quick_dirty_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &FSFB_FF_HIL_quick_dirty_DW.SampleandHold_SubsysRanBC;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(FSFB_FF_HIL_quick_dirty_M->extModeInfo,
      &FSFB_FF_HIL_quick_dirty_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(FSFB_FF_HIL_quick_dirty_M->extModeInfo,
                        FSFB_FF_HIL_quick_dirty_M->Sizes.checksums);
    rteiSetTPtr(FSFB_FF_HIL_quick_dirty_M->extModeInfo, rtmGetTPtr
                (FSFB_FF_HIL_quick_dirty_M));
  }

  FSFB_FF_HIL_quick_dirty_M->solverInfoPtr =
    (&FSFB_FF_HIL_quick_dirty_M->solverInfo);
  FSFB_FF_HIL_quick_dirty_M->Timing.stepSize = (0.005);
  rtsiSetFixedStepSize(&FSFB_FF_HIL_quick_dirty_M->solverInfo, 0.005);
  rtsiSetSolverMode(&FSFB_FF_HIL_quick_dirty_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  FSFB_FF_HIL_quick_dirty_M->blockIO = ((void *) &FSFB_FF_HIL_quick_dirty_B);
  (void) memset(((void *) &FSFB_FF_HIL_quick_dirty_B), 0,
                sizeof(B_FSFB_FF_HIL_quick_dirty_T));

  /* parameters */
  FSFB_FF_HIL_quick_dirty_M->defaultParam = ((real_T *)
    &FSFB_FF_HIL_quick_dirty_P);

  /* states (dwork) */
  FSFB_FF_HIL_quick_dirty_M->dwork = ((void *) &FSFB_FF_HIL_quick_dirty_DW);
  (void) memset((void *)&FSFB_FF_HIL_quick_dirty_DW, 0,
                sizeof(DW_FSFB_FF_HIL_quick_dirty_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    FSFB_FF_HIL_quick_dirty_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 25;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  FSFB_FF_HIL_quick_dirty_M->Sizes.numContStates = (0);/* Number of continuous states */
  FSFB_FF_HIL_quick_dirty_M->Sizes.numY = (0);/* Number of model outputs */
  FSFB_FF_HIL_quick_dirty_M->Sizes.numU = (0);/* Number of model inputs */
  FSFB_FF_HIL_quick_dirty_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  FSFB_FF_HIL_quick_dirty_M->Sizes.numSampTimes = (2);/* Number of sample times */
  FSFB_FF_HIL_quick_dirty_M->Sizes.numBlocks = (77);/* Number of blocks */
  FSFB_FF_HIL_quick_dirty_M->Sizes.numBlockIO = (35);/* Number of block outputs */
  FSFB_FF_HIL_quick_dirty_M->Sizes.numBlockPrms = (49);/* Sum of parameter "widths" */
  return FSFB_FF_HIL_quick_dirty_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
