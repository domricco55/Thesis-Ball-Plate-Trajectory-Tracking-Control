/*
 * Blank_Model.c
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
#include <stdio.h>
#include "rtwtypes.h"
#include "Blank_Model_private.h"
#include "rt_nonfinite.h"
#include "Blank_Model_dt.h"

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
  0.0001, 0.0,
};

/* list of Simulink Desktop Real-Time boards */
const int SLDRTBoardCount = 1;
SLDRTBOARD SLDRTBoards[1] = {
  { "Standard_Devices/Serial_Port", 6U, 8, SLDRTBoardOptions0 },
};

/* Block signals (default storage) */
B_Blank_Model_T Blank_Model_B;

/* Block states (default storage) */
DW_Blank_Model_T Blank_Model_DW;

/* Real-time model */
static RT_MODEL_Blank_Model_T Blank_Model_M_;
RT_MODEL_Blank_Model_T *const Blank_Model_M = &Blank_Model_M_;
static void rate_scheduler(void);

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Blank_Model_M->Timing.TaskCounters.TID[1])++;
  if ((Blank_Model_M->Timing.TaskCounters.TID[1]) > 49) {/* Sample time: [0.005s, 0.0s] */
    Blank_Model_M->Timing.TaskCounters.TID[1] = 0;
  }

  Blank_Model_M->Timing.sampleHits[1] = (Blank_Model_M->Timing.TaskCounters.TID
    [1] == 0) ? 1 : 0;
}

/* Model output function */
void Blank_Model_output(void)
{
  if (Blank_Model_M->Timing.TaskCounters.TID[1] == 0) {
    real_T rtb_DiscreteTimeIntegrator1;
    int32_T rtb_StringtoDouble;

    /* Outputs for Atomic SubSystem: '<Root>/Hardware (Real Plant)' */
    /* Outputs for Atomic SubSystem: '<S11>/Atomic Subsystem' */
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
                           &Blank_Model_B.StreamInput_o1[0],
                           &Blank_Model_B.StreamInput_o2[0],
                           &Blank_Model_B.StreamInput_o3[0],
                           &Blank_Model_B.StreamInput_o4[0],
                           &Blank_Model_B.StreamInput_o5[0],
                           &Blank_Model_B.StreamInput_o6[0],
                           &Blank_Model_B.StreamInput_o7[0],
                           &Blank_Model_B.StreamInput_o8[0],
                           &Blank_Model_B.StreamInput_o9[0]);
      }
    }

    /* ScanString: '<S12>/String to Double8' */
    Blank_Model_B.TimingParity = 0.0;

    /* ScanString: '<S12>/String to Double8' */
    sscanf(&Blank_Model_B.StreamInput_o9[0], "%lf", &Blank_Model_B.TimingParity);

    /* ToAsyncQueueBlock generated from: '<S12>/String to Double8' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.TimingParity;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(1366475681U, time, pData, size);
      }
    }

    /* ScanString: '<S12>/String to Double4' */
    rtb_DiscreteTimeIntegrator1 = 0.0;
    sscanf(&Blank_Model_B.StreamInput_o5[0], "%lf", &rtb_DiscreteTimeIntegrator1);

    /* Gain: '<S13>/Gain1' */
    Blank_Model_B.Gain1 = Blank_Model_P.Gain1_Gain * rtb_DiscreteTimeIntegrator1;

    /* ScanString: '<S12>/String to Double5' */
    rtb_DiscreteTimeIntegrator1 = 0.0;
    sscanf(&Blank_Model_B.StreamInput_o6[0], "%lf", &rtb_DiscreteTimeIntegrator1);

    /* Gain: '<S14>/Gain1' */
    Blank_Model_B.Gain1_c = Blank_Model_P.Gain1_Gain_i *
      rtb_DiscreteTimeIntegrator1;

    /* ScanString: '<S12>/String to Double6' */
    rtb_DiscreteTimeIntegrator1 = 0.0;
    sscanf(&Blank_Model_B.StreamInput_o7[0], "%lf", &rtb_DiscreteTimeIntegrator1);

    /* Gain: '<S15>/Gain1' */
    Blank_Model_B.Gain1_l = Blank_Model_P.Gain1_Gain_j *
      rtb_DiscreteTimeIntegrator1;

    /* ScanString: '<S12>/String to Double7' */
    rtb_DiscreteTimeIntegrator1 = 0.0;
    sscanf(&Blank_Model_B.StreamInput_o8[0], "%lf", &rtb_DiscreteTimeIntegrator1);

    /* Gain: '<S16>/Gain1' */
    Blank_Model_B.Gain1_j = Blank_Model_P.Gain1_Gain_iv *
      rtb_DiscreteTimeIntegrator1;

    /* ScanString: '<S12>/String to Double' */
    rtb_StringtoDouble = 0;
    sscanf(&Blank_Model_B.StreamInput_o1[0], "%d", &rtb_StringtoDouble);

    /* Gain: '<S12>/Gain' */
    Blank_Model_B.Gain_ny = (real_T)Blank_Model_P.Gain_Gain_h *
      9.0949470177292824E-13 * (real_T)rtb_StringtoDouble;

    /* ScanString: '<S12>/String to Double1' */
    rtb_DiscreteTimeIntegrator1 = 0.0;
    sscanf(&Blank_Model_B.StreamInput_o2[0], "%lf", &rtb_DiscreteTimeIntegrator1);

    /* Gain: '<S12>/Gain1' */
    Blank_Model_B.Gain1_ca = Blank_Model_P.Gain1_Gain_ip *
      rtb_DiscreteTimeIntegrator1;

    /* ScanString: '<S12>/String to Double2' */
    rtb_DiscreteTimeIntegrator1 = 0.0;
    sscanf(&Blank_Model_B.StreamInput_o3[0], "%lf", &rtb_DiscreteTimeIntegrator1);

    /* Gain: '<S12>/Gain2' */
    Blank_Model_B.Gain2 = Blank_Model_P.Gain2_Gain * rtb_DiscreteTimeIntegrator1;

    /* ScanString: '<S12>/String to Double3' */
    rtb_DiscreteTimeIntegrator1 = 0.0;
    sscanf(&Blank_Model_B.StreamInput_o4[0], "%lf", &rtb_DiscreteTimeIntegrator1);

    /* Gain: '<S12>/Gain3' */
    Blank_Model_B.Gain3 = Blank_Model_P.Gain3_Gain * rtb_DiscreteTimeIntegrator1;

    /* End of Outputs for SubSystem: '<S11>/Atomic Subsystem' */

    /* Gain: '<S4>/Gain' */
    Blank_Model_B.Gain = Blank_Model_P.Gain_Gain * Blank_Model_B.Gain1_c;

    /* Gain: '<S7>/Gain' */
    Blank_Model_B.Gain_n = Blank_Model_P.Gain_Gain_f * Blank_Model_B.Gain1_l;

    /* ToAsyncQueueBlock generated from: '<S1>/Demux' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Gain_ny;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(177757808U, time, pData, size);
      }
    }

    /* ToAsyncQueueBlock generated from: '<S1>/Demux' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Gain1_j;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(1310948565U, time, pData, size);
      }
    }

    /* ToAsyncQueueBlock generated from: '<S1>/Demux' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Gain2;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(1963527676U, time, pData, size);
      }
    }

    /* ToAsyncQueueBlock generated from: '<S1>/Demux' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Gain1_ca;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(1952706783U, time, pData, size);
      }
    }

    /* SampleTimeMath: '<S3>/TSamp'
     *
     * About '<S3>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     */
    Blank_Model_B.TSamp = Blank_Model_B.Gain2 * Blank_Model_P.TSamp_WtEt;

    /* Sum: '<S3>/Diff' incorporates:
     *  UnitDelay: '<S3>/UD'
     */
    Blank_Model_B.Diff = Blank_Model_B.TSamp - Blank_Model_DW.UD_DSTATE;

    /* ToAsyncQueueBlock generated from: '<S1>/Discrete Derivative1' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Diff;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(2550695630U, time, pData, size);
      }
    }

    /* SampleTimeMath: '<S2>/TSamp'
     *
     * About '<S2>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     */
    Blank_Model_B.TSamp_c = Blank_Model_B.Gain_ny * Blank_Model_P.TSamp_WtEt_f;

    /* Sum: '<S2>/Diff' incorporates:
     *  UnitDelay: '<S2>/UD'
     */
    Blank_Model_B.Diff_b = Blank_Model_B.TSamp_c - Blank_Model_DW.UD_DSTATE_h;

    /* ToAsyncQueueBlock generated from: '<S1>/Discrete Derivative' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Diff_b;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(1818993386U, time, pData, size);
      }
    }

    /* Gain: '<S5>/Gain' */
    Blank_Model_B.Gain_b = Blank_Model_P.Gain_Gain_j * Blank_Model_B.Gain3;

    /* ToAsyncQueueBlock generated from: '<S1>/Radians to Degrees1' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Gain_b;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(24636569U, time, pData, size);
      }
    }

    /* Gain: '<S6>/Gain' */
    Blank_Model_B.Gain_d = Blank_Model_P.Gain_Gain_n * Blank_Model_B.Gain1;

    /* ToAsyncQueueBlock generated from: '<S1>/Radians to Degrees2' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Gain_d;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(2811973514U, time, pData, size);
      }
    }

    /* ToAsyncQueueBlock generated from: '<S1>/Radians to Degrees3' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Gain_n;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(1418830038U, time, pData, size);
      }
    }

    /* Gain: '<S8>/Gain' incorporates:
     *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
     */
    Blank_Model_B.Gain_np = Blank_Model_P.Gain_Gain_jf *
      Blank_Model_DW.DiscreteTimeIntegrator_DSTATE;

    /* ToAsyncQueueBlock generated from: '<S1>/Radians to Degrees4' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Gain_np;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(4162024006U, time, pData, size);
      }
    }

    /* Gain: '<S9>/Gain' incorporates:
     *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator1'
     */
    Blank_Model_B.Gain_nn = Blank_Model_P.Gain_Gain_g *
      Blank_Model_DW.DiscreteTimeIntegrator1_DSTATE;

    /* ToAsyncQueueBlock generated from: '<S1>/Radians to Degrees5' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Gain_nn;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(2107326576U, time, pData, size);
      }
    }

    /* ToAsyncQueueBlock generated from: '<S1>/Radians to Degrees' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Gain;
        int32_T size = 1*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(1296903835U, time, pData, size);
      }
    }

    /* Sum: '<S11>/Sum' incorporates:
     *  Constant: '<S11>/Constant'
     */
    Blank_Model_B.Sum = Blank_Model_B.Gain3 - Blank_Model_P.Constant_Value;

    /* Sum: '<S11>/Sum1' incorporates:
     *  Constant: '<S11>/Constant1'
     */
    Blank_Model_B.Sum1 = Blank_Model_B.Gain1_l - Blank_Model_P.Constant1_Value;

    /* S-Function (sldrtso): '<S10>/Stream Output' */
    /* S-Function Block: <S10>/Stream Output */

    /* no code required */

    /* Gain: '<S1>/Gear Ratio Assumption' incorporates:
     *  Constant: '<Root>/Constant'
     */
    rtb_DiscreteTimeIntegrator1 = Blank_Model_P.GearRatioAssumption_Gain *
      Blank_Model_P.Constant_Value_e[0];

    /* Saturate: '<S1>/Saturation1' */
    if (rtb_DiscreteTimeIntegrator1 > Blank_Model_P.Saturation1_UpperSat) {
      /* Saturate: '<S1>/Saturation1' */
      Blank_Model_B.Torque_Sat[0] = Blank_Model_P.Saturation1_UpperSat;
    } else if (rtb_DiscreteTimeIntegrator1 < Blank_Model_P.Saturation1_LowerSat)
    {
      /* Saturate: '<S1>/Saturation1' */
      Blank_Model_B.Torque_Sat[0] = Blank_Model_P.Saturation1_LowerSat;
    } else {
      /* Saturate: '<S1>/Saturation1' */
      Blank_Model_B.Torque_Sat[0] = rtb_DiscreteTimeIntegrator1;
    }

    /* Gain: '<S1>/Gear Ratio Assumption' incorporates:
     *  Constant: '<Root>/Constant'
     */
    rtb_DiscreteTimeIntegrator1 = Blank_Model_P.GearRatioAssumption_Gain *
      Blank_Model_P.Constant_Value_e[1];

    /* Saturate: '<S1>/Saturation1' */
    if (rtb_DiscreteTimeIntegrator1 > Blank_Model_P.Saturation1_UpperSat) {
      /* Saturate: '<S1>/Saturation1' */
      Blank_Model_B.Torque_Sat[1] = Blank_Model_P.Saturation1_UpperSat;
    } else if (rtb_DiscreteTimeIntegrator1 < Blank_Model_P.Saturation1_LowerSat)
    {
      /* Saturate: '<S1>/Saturation1' */
      Blank_Model_B.Torque_Sat[1] = Blank_Model_P.Saturation1_LowerSat;
    } else {
      /* Saturate: '<S1>/Saturation1' */
      Blank_Model_B.Torque_Sat[1] = rtb_DiscreteTimeIntegrator1;
    }

    /* ToAsyncQueueBlock generated from: '<S1>/Saturation1' */
    {
      {
        double time = Blank_Model_M->Timing.t[1];
        void *pData = (void *)&Blank_Model_B.Torque_Sat[0];
        int32_T size = 2*sizeof(real_T);
        sendToAsyncQueueTgtAppSvc(335098161U, time, pData, size);
      }
    }

    /* End of Outputs for SubSystem: '<Root>/Hardware (Real Plant)' */
  }
}

/* Model update function */
void Blank_Model_update(void)
{
  if (Blank_Model_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update for Atomic SubSystem: '<Root>/Hardware (Real Plant)' */
    /* Update for UnitDelay: '<S3>/UD' */
    Blank_Model_DW.UD_DSTATE = Blank_Model_B.TSamp;

    /* Update for UnitDelay: '<S2>/UD' */
    Blank_Model_DW.UD_DSTATE_h = Blank_Model_B.TSamp_c;

    /* Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
    Blank_Model_DW.DiscreteTimeIntegrator_DSTATE +=
      Blank_Model_P.DiscreteTimeIntegrator_gainval * Blank_Model_B.Sum;

    /* Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator1' */
    Blank_Model_DW.DiscreteTimeIntegrator1_DSTATE +=
      Blank_Model_P.DiscreteTimeIntegrator1_gainval * Blank_Model_B.Sum1;

    /* Update for S-Function (sldrtso): '<S10>/Stream Output' */

    /* S-Function Block: <S10>/Stream Output */
    {
      char_T outstring[650U];
      int n = snprintf(outstring, 650U, "%g %g\n", (real_T)
                       Blank_Model_B.Torque_Sat[0], (real_T)
                       Blank_Model_B.Torque_Sat[1]);
      RTBIO_DriverIO(0, STREAMOUTPUT, IOWRITE, n, NULL, (double*) outstring,
                     NULL);
    }

    /* End of Update for SubSystem: '<Root>/Hardware (Real Plant)' */
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
  if (!(++Blank_Model_M->Timing.clockTick0)) {
    ++Blank_Model_M->Timing.clockTickH0;
  }

  Blank_Model_M->Timing.t[0] = Blank_Model_M->Timing.clockTick0 *
    Blank_Model_M->Timing.stepSize0 + Blank_Model_M->Timing.clockTickH0 *
    Blank_Model_M->Timing.stepSize0 * 4294967296.0;
  if (Blank_Model_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.005s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Blank_Model_M->Timing.clockTick1)) {
      ++Blank_Model_M->Timing.clockTickH1;
    }

    Blank_Model_M->Timing.t[1] = Blank_Model_M->Timing.clockTick1 *
      Blank_Model_M->Timing.stepSize1 + Blank_Model_M->Timing.clockTickH1 *
      Blank_Model_M->Timing.stepSize1 * 4294967296.0;
  }

  rate_scheduler();
}

/* Model initialize function */
void Blank_Model_initialize(void)
{
  /* Start for S-Function (sldrtso): '<S10>/Stream Output' */

  /* S-Function Block: <S10>/Stream Output */
  /* no initial value should be set */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Hardware (Real Plant)' */
  /* InitializeConditions for UnitDelay: '<S3>/UD' */
  Blank_Model_DW.UD_DSTATE = Blank_Model_P.DiscreteDerivative1_ICPrevScaledInput;

  /* InitializeConditions for UnitDelay: '<S2>/UD' */
  Blank_Model_DW.UD_DSTATE_h =
    Blank_Model_P.DiscreteDerivative_ICPrevScaledInput;

  /* InitializeConditions for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
  Blank_Model_DW.DiscreteTimeIntegrator_DSTATE =
    Blank_Model_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S11>/Discrete-Time Integrator1' */
  Blank_Model_DW.DiscreteTimeIntegrator1_DSTATE =
    Blank_Model_P.DiscreteTimeIntegrator1_IC;

  /* End of SystemInitialize for SubSystem: '<Root>/Hardware (Real Plant)' */
}

/* Model terminate function */
void Blank_Model_terminate(void)
{
  /* Terminate for S-Function (sldrtso): '<S10>/Stream Output' */

  /* no final value should be set */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Blank_Model_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Blank_Model_update();
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
  Blank_Model_initialize();
}

void MdlTerminate(void)
{
  Blank_Model_terminate();
}

/* Registration function */
RT_MODEL_Blank_Model_T *Blank_Model(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Blank_Model_M, 0,
                sizeof(RT_MODEL_Blank_Model_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Blank_Model_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "Blank_Model_M points to
       static memory which is guaranteed to be non-NULL" */
    Blank_Model_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Blank_Model_M->Timing.sampleTimes = (&Blank_Model_M->
      Timing.sampleTimesArray[0]);
    Blank_Model_M->Timing.offsetTimes = (&Blank_Model_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    Blank_Model_M->Timing.sampleTimes[0] = (0.0001);
    Blank_Model_M->Timing.sampleTimes[1] = (0.005);

    /* task offsets */
    Blank_Model_M->Timing.offsetTimes[0] = (0.0);
    Blank_Model_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(Blank_Model_M, &Blank_Model_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Blank_Model_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    Blank_Model_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Blank_Model_M, 500.0);
  Blank_Model_M->Timing.stepSize0 = 0.0001;
  Blank_Model_M->Timing.stepSize1 = 0.005;

  /* External mode info */
  Blank_Model_M->Sizes.checksums[0] = (1594619151U);
  Blank_Model_M->Sizes.checksums[1] = (611761312U);
  Blank_Model_M->Sizes.checksums[2] = (3257797441U);
  Blank_Model_M->Sizes.checksums[3] = (1775289076U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    Blank_Model_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Blank_Model_M->extModeInfo,
      &Blank_Model_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Blank_Model_M->extModeInfo,
                        Blank_Model_M->Sizes.checksums);
    rteiSetTPtr(Blank_Model_M->extModeInfo, rtmGetTPtr(Blank_Model_M));
  }

  Blank_Model_M->solverInfoPtr = (&Blank_Model_M->solverInfo);
  Blank_Model_M->Timing.stepSize = (0.0001);
  rtsiSetFixedStepSize(&Blank_Model_M->solverInfo, 0.0001);
  rtsiSetSolverMode(&Blank_Model_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Blank_Model_M->blockIO = ((void *) &Blank_Model_B);
  (void) memset(((void *) &Blank_Model_B), 0,
                sizeof(B_Blank_Model_T));

  /* parameters */
  Blank_Model_M->defaultParam = ((real_T *)&Blank_Model_P);

  /* states (dwork) */
  Blank_Model_M->dwork = ((void *) &Blank_Model_DW);
  (void) memset((void *)&Blank_Model_DW, 0,
                sizeof(DW_Blank_Model_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Blank_Model_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 25;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Blank_Model_M->Sizes.numContStates = (0);/* Number of continuous states */
  Blank_Model_M->Sizes.numY = (0);     /* Number of model outputs */
  Blank_Model_M->Sizes.numU = (0);     /* Number of model inputs */
  Blank_Model_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Blank_Model_M->Sizes.numSampTimes = (2);/* Number of sample times */
  Blank_Model_M->Sizes.numBlocks = (60);/* Number of blocks */
  Blank_Model_M->Sizes.numBlockIO = (31);/* Number of block outputs */
  Blank_Model_M->Sizes.numBlockPrms = (33);/* Sum of parameter "widths" */
  return Blank_Model_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
