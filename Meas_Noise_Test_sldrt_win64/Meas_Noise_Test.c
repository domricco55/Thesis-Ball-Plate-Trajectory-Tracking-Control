/*
 * Meas_Noise_Test.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Meas_Noise_Test".
 *
 * Model version              : 5.39
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Mon Apr 25 15:10:00 2022
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Meas_Noise_Test.h"
#include <stdio.h>
#include "rtwtypes.h"
#include "Meas_Noise_Test_private.h"
#include "rt_nonfinite.h"
#include "Meas_Noise_Test_dt.h"

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
B_Meas_Noise_Test_T Meas_Noise_Test_B;

/* Block states (default storage) */
DW_Meas_Noise_Test_T Meas_Noise_Test_DW;

/* Real-time model */
static RT_MODEL_Meas_Noise_Test_T Meas_Noise_Test_M_;
RT_MODEL_Meas_Noise_Test_T *const Meas_Noise_Test_M = &Meas_Noise_Test_M_;

/* Model output function */
void Meas_Noise_Test_output(void)
{
  real_T rtb_Product1;
  real_T rtb_Sum;
  real_T rtb_Sum_m;
  real_T rtb_d;
  real_T rtb_d_b;
  real_T rtb_p;
  real_T rtb_p_b;
  real_T rtb_q;
  real_T rtb_q_a;
  real_T rtb_r;
  real_T rtb_r_g;
  real_T rtb_yvelTS;
  int32_T rtb_xposTS;

  /* S-Function (sldrtso): '<S1>/Stream Output' incorporates:
   *  Constant: '<Root>/Constant'
   */
  /* S-Function Block: <S1>/Stream Output */

  /* no code required */

  /* S-Function (sldrtsi): '<S2>/Stream Input' */
  /* S-Function Block: <S2>/Stream Input */
  {
    char indata[2321U];
    int status;
    const char* terminators = "\r\0\n\0";
    memset(indata, 0, sizeof(indata));
    status = RTBIO_DriverIO(0, STREAMINPUT, IOREADWITHRESET, 2320U, NULL,
      (double*) indata, terminators);
    if (status & 0x1) {
      int nscan = sscanf(indata, "%s %s %s %s %s %s %s %s %s",
                         &Meas_Noise_Test_B.StreamInput_o1[0],
                         &Meas_Noise_Test_B.StreamInput_o2[0],
                         &Meas_Noise_Test_B.StreamInput_o3[0],
                         &Meas_Noise_Test_B.StreamInput_o4[0],
                         &Meas_Noise_Test_B.StreamInput_o5[0],
                         &Meas_Noise_Test_B.StreamInput_o6[0],
                         &Meas_Noise_Test_B.StreamInput_o7[0],
                         &Meas_Noise_Test_B.StreamInput_o8[0],
                         &Meas_Noise_Test_B.StreamInput_o9[0]);
    }
  }

  /* ScanString: '<S2>/String to Double' */
  rtb_xposTS = 0;
  sscanf(&Meas_Noise_Test_B.StreamInput_o1[0], "%d", &rtb_xposTS);

  /* Gain: '<S2>/Gain' */
  Meas_Noise_Test_B.bx = (real_T)Meas_Noise_Test_P.Gain_Gain_e *
    9.0949470177292824E-13 * (real_T)rtb_xposTS;

  /* ScanString: '<S2>/String to Double4' */
  Meas_Noise_Test_B.IMUx = 0.0;

  /* ScanString: '<S2>/String to Double4' */
  sscanf(&Meas_Noise_Test_B.StreamInput_o3[0], "%lf", &Meas_Noise_Test_B.IMUx);

  /* Gain: '<S3>/Gain1' */
  Meas_Noise_Test_B.Gain1 = Meas_Noise_Test_P.Gain1_Gain *
    Meas_Noise_Test_B.IMUx;

  /* ScanString: '<S2>/String to Double5' */
  Meas_Noise_Test_B.GyroX = 0.0;

  /* ScanString: '<S2>/String to Double5' */
  sscanf(&Meas_Noise_Test_B.StreamInput_o4[0], "%lf", &Meas_Noise_Test_B.GyroX);

  /* Gain: '<S4>/Gain1' */
  Meas_Noise_Test_B.Gain1_i = Meas_Noise_Test_P.Gain1_Gain_f *
    Meas_Noise_Test_B.GyroX;

  /* ScanString: '<S2>/String to Double2' */
  rtb_Sum_m = 0.0;
  sscanf(&Meas_Noise_Test_B.StreamInput_o5[0], "%lf", &rtb_Sum_m);

  /* Gain: '<S2>/Gain2' */
  Meas_Noise_Test_B.by = Meas_Noise_Test_P.Gain2_Gain * rtb_Sum_m;

  /* ScanString: '<S2>/String to Double6' */
  Meas_Noise_Test_B.IMUy = 0.0;

  /* ScanString: '<S2>/String to Double6' */
  sscanf(&Meas_Noise_Test_B.StreamInput_o7[0], "%lf", &Meas_Noise_Test_B.IMUy);

  /* Gain: '<S5>/Gain1' */
  Meas_Noise_Test_B.Gain1_o = Meas_Noise_Test_P.Gain1_Gain_d *
    Meas_Noise_Test_B.IMUy;

  /* ScanString: '<S2>/String to Double7' */
  Meas_Noise_Test_B.GyroY = 0.0;

  /* ScanString: '<S2>/String to Double7' */
  sscanf(&Meas_Noise_Test_B.StreamInput_o8[0], "%lf", &Meas_Noise_Test_B.GyroY);

  /* Gain: '<S6>/Gain1' */
  Meas_Noise_Test_B.Gain1_c = Meas_Noise_Test_P.Gain1_Gain_dd *
    Meas_Noise_Test_B.GyroY;

  /* SignalConversion generated from: '<Root>/x actual1' */
  Meas_Noise_Test_B.MeasuredOutput[0] = Meas_Noise_Test_B.bx;
  Meas_Noise_Test_B.MeasuredOutput[1] = Meas_Noise_Test_B.Gain1;
  Meas_Noise_Test_B.MeasuredOutput[2] = Meas_Noise_Test_B.Gain1_i;
  Meas_Noise_Test_B.MeasuredOutput[3] = Meas_Noise_Test_B.by;
  Meas_Noise_Test_B.MeasuredOutput[4] = Meas_Noise_Test_B.Gain1_o;
  Meas_Noise_Test_B.MeasuredOutput[5] = Meas_Noise_Test_B.Gain1_c;

  /* SampleTimeMath: '<S7>/TSamp'
   *
   * About '<S7>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  Meas_Noise_Test_B.TSamp = Meas_Noise_Test_B.bx * Meas_Noise_Test_P.TSamp_WtEt;

  /* Sum: '<S7>/Diff' incorporates:
   *  UnitDelay: '<S7>/UD'
   */
  Meas_Noise_Test_B.Diff = Meas_Noise_Test_B.TSamp -
    Meas_Noise_Test_DW.UD_DSTATE;

  /* ToAsyncQueueBlock generated from: '<S2>/Discrete Derivative' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.Diff;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3618890570U, time, pData, size);
    }
  }

  /* Sum: '<S9>/Sum' incorporates:
   *  UnitDelay: '<S9>/Unit Delay1'
   */
  rtb_Sum_m = Meas_Noise_Test_B.Diff + Meas_Noise_Test_DW.UnitDelay1_DSTATE;

  /* Gain: '<S9>/tau' incorporates:
   *  Constant: '<S2>/Constant'
   */
  rtb_p = Meas_Noise_Test_P.tau_Gain * Meas_Noise_Test_P.Constant_Value_n;

  /* Product: '<S11>/Product2' */
  rtb_q = rtb_p * rtb_p;

  /* Sum: '<S11>/Add' incorporates:
   *  Constant: '<S11>/Constant'
   */
  rtb_r = rtb_q + Meas_Noise_Test_P.Constant_Value_j;

  /* Gain: '<S11>/Gain' */
  rtb_p *= Meas_Noise_Test_P.Gain_Gain;

  /* Sum: '<S11>/Add1' */
  rtb_d = rtb_r + rtb_p;

  /* Product: '<S9>/Product1' incorporates:
   *  Product: '<S11>/Product3'
   */
  rtb_Product1 = rtb_q / rtb_d * rtb_Sum_m;

  /* Sum: '<S10>/Sum' incorporates:
   *  UnitDelay: '<S10>/Unit Delay1'
   */
  rtb_Sum = rtb_Product1 + Meas_Noise_Test_DW.UnitDelay1_DSTATE_l;

  /* Gain: '<S10>/tau' incorporates:
   *  Constant: '<S2>/Constant'
   */
  rtb_p_b = Meas_Noise_Test_P.tau_Gain_p * Meas_Noise_Test_P.Constant_Value_n;

  /* Product: '<S12>/Product2' */
  rtb_q_a = rtb_p_b * rtb_p_b;

  /* Sum: '<S12>/Add' incorporates:
   *  Constant: '<S12>/Constant'
   */
  rtb_r_g = rtb_q_a + Meas_Noise_Test_P.Constant_Value_i;

  /* Gain: '<S12>/Gain' */
  rtb_p_b *= Meas_Noise_Test_P.Gain_Gain_b;

  /* Sum: '<S12>/Add1' */
  rtb_d_b = rtb_r_g + rtb_p_b;

  /* Product: '<S10>/Product1' incorporates:
   *  Product: '<S12>/Product3'
   */
  Meas_Noise_Test_B.Product1 = rtb_q_a / rtb_d_b * rtb_Sum;

  /* ToAsyncQueueBlock generated from: '<S2>/Discrete Varying Lowpass' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.Product1;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3281038974U, time, pData, size);
    }
  }

  /* ScanString: '<S2>/String to Double1' */
  rtb_yvelTS = 0.0;
  sscanf(&Meas_Noise_Test_B.StreamInput_o2[0], "%lf", &rtb_yvelTS);

  /* Gain: '<S2>/Gain1' */
  Meas_Noise_Test_B.bx_dot = Meas_Noise_Test_P.Gain1_Gain_o * rtb_yvelTS;

  /* ToAsyncQueueBlock generated from: '<S2>/Gain1' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.bx_dot;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(1724034819U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/Gain2' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.by;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(71344963U, time, pData, size);
    }
  }

  /* ScanString: '<S2>/String to Double3' */
  rtb_yvelTS = 0.0;
  sscanf(&Meas_Noise_Test_B.StreamInput_o6[0], "%lf", &rtb_yvelTS);

  /* Gain: '<S2>/Gain3' */
  Meas_Noise_Test_B.by_dot = Meas_Noise_Test_P.Gain3_Gain * rtb_yvelTS;

  /* ToAsyncQueueBlock generated from: '<S2>/Gain3' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.by_dot;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2862808503U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/Gain' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.bx;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(4043868324U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/String to Double4' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.IMUx;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3796146685U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/String to Double5' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.GyroX;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3014744630U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/String to Double6' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.IMUy;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2544910573U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/String to Double7' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.GyroY;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(4006663951U, time, pData, size);
    }
  }

  /* ScanString: '<S2>/String to Double8' */
  Meas_Noise_Test_B.TimingParity = 0.0;

  /* ScanString: '<S2>/String to Double8' */
  sscanf(&Meas_Noise_Test_B.StreamInput_o9[0], "%lf",
         &Meas_Noise_Test_B.TimingParity);

  /* ToAsyncQueueBlock generated from: '<S2>/String to Double8' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.TimingParity;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2723614207U, time, pData, size);
    }
  }

  /* Sum: '<S9>/Sum1' incorporates:
   *  Constant: '<S11>/Constant1'
   *  Gain: '<S9>/Gain1'
   *  Product: '<S11>/Product4'
   *  Product: '<S9>/Product5'
   *  Sum: '<S11>/Add2'
   *  Sum: '<S9>/Sum2'
   *  UnitDelay: '<S9>/Unit Delay2'
   */
  Meas_Noise_Test_B.Sum1 = ((Meas_Noise_Test_P.Constant1_Value - rtb_q) / rtb_d *
    rtb_Sum_m + Meas_Noise_Test_B.Diff) * Meas_Noise_Test_P.Gain1_Gain_n +
    Meas_Noise_Test_DW.UnitDelay2_DSTATE;

  /* Sum: '<S9>/Sum3' incorporates:
   *  Product: '<S11>/Product5'
   *  Product: '<S9>/Product2'
   *  Sum: '<S11>/Add3'
   */
  Meas_Noise_Test_B.Sum3 = Meas_Noise_Test_B.Diff - 1.0 / rtb_d * (rtb_r - rtb_p)
    * rtb_Sum_m;

  /* Sum: '<S10>/Sum1' incorporates:
   *  Constant: '<S12>/Constant1'
   *  Gain: '<S10>/Gain1'
   *  Product: '<S10>/Product5'
   *  Product: '<S12>/Product4'
   *  Sum: '<S10>/Sum2'
   *  Sum: '<S12>/Add2'
   *  UnitDelay: '<S10>/Unit Delay2'
   */
  Meas_Noise_Test_B.Sum1_m = ((Meas_Noise_Test_P.Constant1_Value_n - rtb_q_a) /
    rtb_d_b * rtb_Sum + rtb_Product1) * Meas_Noise_Test_P.Gain1_Gain_j +
    Meas_Noise_Test_DW.UnitDelay2_DSTATE_p;

  /* Sum: '<S10>/Sum3' incorporates:
   *  Product: '<S10>/Product2'
   *  Product: '<S12>/Product5'
   *  Sum: '<S12>/Add3'
   */
  Meas_Noise_Test_B.Sum3_j = rtb_Product1 - 1.0 / rtb_d_b * (rtb_r_g - rtb_p_b) *
    rtb_Sum;
}

/* Model update function */
void Meas_Noise_Test_update(void)
{
  /* Update for S-Function (sldrtso): '<S1>/Stream Output' incorporates:
   *  Constant: '<Root>/Constant'
   */

  /* S-Function Block: <S1>/Stream Output */
  {
    char_T outstring[650U];
    int n = snprintf(outstring, 650U, "%g %g\n", (real_T)
                     Meas_Noise_Test_P.Constant_Value[0], (real_T)
                     Meas_Noise_Test_P.Constant_Value[1]);
    RTBIO_DriverIO(0, STREAMOUTPUT, IOWRITE, n, NULL, (double*) outstring, NULL);
  }

  /* Update for UnitDelay: '<S7>/UD' */
  Meas_Noise_Test_DW.UD_DSTATE = Meas_Noise_Test_B.TSamp;

  /* Update for UnitDelay: '<S9>/Unit Delay1' */
  Meas_Noise_Test_DW.UnitDelay1_DSTATE = Meas_Noise_Test_B.Sum1;

  /* Update for UnitDelay: '<S10>/Unit Delay1' */
  Meas_Noise_Test_DW.UnitDelay1_DSTATE_l = Meas_Noise_Test_B.Sum1_m;

  /* Update for UnitDelay: '<S9>/Unit Delay2' */
  Meas_Noise_Test_DW.UnitDelay2_DSTATE = Meas_Noise_Test_B.Sum3;

  /* Update for UnitDelay: '<S10>/Unit Delay2' */
  Meas_Noise_Test_DW.UnitDelay2_DSTATE_p = Meas_Noise_Test_B.Sum3_j;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Meas_Noise_Test_M->Timing.clockTick0)) {
    ++Meas_Noise_Test_M->Timing.clockTickH0;
  }

  Meas_Noise_Test_M->Timing.t[0] = Meas_Noise_Test_M->Timing.clockTick0 *
    Meas_Noise_Test_M->Timing.stepSize0 + Meas_Noise_Test_M->Timing.clockTickH0 *
    Meas_Noise_Test_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Meas_Noise_Test_initialize(void)
{
  /* Start for S-Function (sldrtso): '<S1>/Stream Output' incorporates:
   *  Constant: '<Root>/Constant'
   */

  /* S-Function Block: <S1>/Stream Output */
  /* no initial value should be set */

  /* InitializeConditions for UnitDelay: '<S7>/UD' */
  Meas_Noise_Test_DW.UD_DSTATE =
    Meas_Noise_Test_P.DiscreteDerivative_ICPrevScaledInput;

  /* InitializeConditions for UnitDelay: '<S9>/Unit Delay1' */
  Meas_Noise_Test_DW.UnitDelay1_DSTATE =
    Meas_Noise_Test_P.UnitDelay1_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S10>/Unit Delay1' */
  Meas_Noise_Test_DW.UnitDelay1_DSTATE_l =
    Meas_Noise_Test_P.UnitDelay1_InitialCondition_n;

  /* InitializeConditions for UnitDelay: '<S9>/Unit Delay2' */
  Meas_Noise_Test_DW.UnitDelay2_DSTATE =
    Meas_Noise_Test_P.UnitDelay2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S10>/Unit Delay2' */
  Meas_Noise_Test_DW.UnitDelay2_DSTATE_p =
    Meas_Noise_Test_P.UnitDelay2_InitialCondition_n;
}

/* Model terminate function */
void Meas_Noise_Test_terminate(void)
{
  /* Terminate for S-Function (sldrtso): '<S1>/Stream Output' incorporates:
   *  Constant: '<Root>/Constant'
   */

  /* no final value should be set */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Meas_Noise_Test_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Meas_Noise_Test_update();
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
  Meas_Noise_Test_initialize();
}

void MdlTerminate(void)
{
  Meas_Noise_Test_terminate();
}

/* Registration function */
RT_MODEL_Meas_Noise_Test_T *Meas_Noise_Test(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Meas_Noise_Test_M, 0,
                sizeof(RT_MODEL_Meas_Noise_Test_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Meas_Noise_Test_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "Meas_Noise_Test_M points to
       static memory which is guaranteed to be non-NULL" */
    Meas_Noise_Test_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Meas_Noise_Test_M->Timing.sampleTimes =
      (&Meas_Noise_Test_M->Timing.sampleTimesArray[0]);
    Meas_Noise_Test_M->Timing.offsetTimes =
      (&Meas_Noise_Test_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Meas_Noise_Test_M->Timing.sampleTimes[0] = (0.005);

    /* task offsets */
    Meas_Noise_Test_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Meas_Noise_Test_M, &Meas_Noise_Test_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Meas_Noise_Test_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Meas_Noise_Test_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Meas_Noise_Test_M, 30.0);
  Meas_Noise_Test_M->Timing.stepSize0 = 0.005;

  /* External mode info */
  Meas_Noise_Test_M->Sizes.checksums[0] = (1600017397U);
  Meas_Noise_Test_M->Sizes.checksums[1] = (1475453995U);
  Meas_Noise_Test_M->Sizes.checksums[2] = (2992063876U);
  Meas_Noise_Test_M->Sizes.checksums[3] = (594787750U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    Meas_Noise_Test_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Meas_Noise_Test_M->extModeInfo,
      &Meas_Noise_Test_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Meas_Noise_Test_M->extModeInfo,
                        Meas_Noise_Test_M->Sizes.checksums);
    rteiSetTPtr(Meas_Noise_Test_M->extModeInfo, rtmGetTPtr(Meas_Noise_Test_M));
  }

  Meas_Noise_Test_M->solverInfoPtr = (&Meas_Noise_Test_M->solverInfo);
  Meas_Noise_Test_M->Timing.stepSize = (0.005);
  rtsiSetFixedStepSize(&Meas_Noise_Test_M->solverInfo, 0.005);
  rtsiSetSolverMode(&Meas_Noise_Test_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Meas_Noise_Test_M->blockIO = ((void *) &Meas_Noise_Test_B);
  (void) memset(((void *) &Meas_Noise_Test_B), 0,
                sizeof(B_Meas_Noise_Test_T));

  /* parameters */
  Meas_Noise_Test_M->defaultParam = ((real_T *)&Meas_Noise_Test_P);

  /* states (dwork) */
  Meas_Noise_Test_M->dwork = ((void *) &Meas_Noise_Test_DW);
  (void) memset((void *)&Meas_Noise_Test_DW, 0,
                sizeof(DW_Meas_Noise_Test_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Meas_Noise_Test_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 25;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Meas_Noise_Test_M->Sizes.numContStates = (0);/* Number of continuous states */
  Meas_Noise_Test_M->Sizes.numY = (0); /* Number of model outputs */
  Meas_Noise_Test_M->Sizes.numU = (0); /* Number of model inputs */
  Meas_Noise_Test_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Meas_Noise_Test_M->Sizes.numSampTimes = (1);/* Number of sample times */
  Meas_Noise_Test_M->Sizes.numBlocks = (81);/* Number of blocks */
  Meas_Noise_Test_M->Sizes.numBlockIO = (30);/* Number of block outputs */
  Meas_Noise_Test_M->Sizes.numBlockPrms = (31);/* Sum of parameter "widths" */
  return Meas_Noise_Test_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
