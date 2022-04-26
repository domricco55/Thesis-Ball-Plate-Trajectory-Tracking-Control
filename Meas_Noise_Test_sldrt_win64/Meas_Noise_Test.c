/*
 * Meas_Noise_Test.c
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
  Meas_Noise_Test_B.bx = (real_T)Meas_Noise_Test_P.Gain_Gain *
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
  rtb_yvelTS = 0.0;
  sscanf(&Meas_Noise_Test_B.StreamInput_o5[0], "%lf", &rtb_yvelTS);

  /* Gain: '<S2>/Gain2' */
  Meas_Noise_Test_B.by = Meas_Noise_Test_P.Gain2_Gain * rtb_yvelTS;

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

  /* SignalConversion generated from: '<Root>/To Workspace' */
  Meas_Noise_Test_B.MeasuredOutput[0] = Meas_Noise_Test_B.bx;
  Meas_Noise_Test_B.MeasuredOutput[1] = Meas_Noise_Test_B.Gain1;
  Meas_Noise_Test_B.MeasuredOutput[2] = Meas_Noise_Test_B.Gain1_i;
  Meas_Noise_Test_B.MeasuredOutput[3] = Meas_Noise_Test_B.by;
  Meas_Noise_Test_B.MeasuredOutput[4] = Meas_Noise_Test_B.Gain1_o;
  Meas_Noise_Test_B.MeasuredOutput[5] = Meas_Noise_Test_B.Gain1_c;

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
      sendToAsyncQueueTgtAppSvc(1902225879U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/Gain2' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.by;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(1220606827U, time, pData, size);
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
      sendToAsyncQueueTgtAppSvc(2049979188U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/Gain' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.bx;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2588074390U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/String to Double4' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.IMUx;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2500779819U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/String to Double5' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.GyroX;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2344077722U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/String to Double6' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.IMUy;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3536845101U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S2>/String to Double7' */
  {
    {
      double time = Meas_Noise_Test_M->Timing.t[0];
      void *pData = (void *)&Meas_Noise_Test_B.GyroY;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(1330161428U, time, pData, size);
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
      sendToAsyncQueueTgtAppSvc(1245043909U, time, pData, size);
    }
  }
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
  Meas_Noise_Test_M->Sizes.checksums[0] = (3249472711U);
  Meas_Noise_Test_M->Sizes.checksums[1] = (2862565719U);
  Meas_Noise_Test_M->Sizes.checksums[2] = (387383676U);
  Meas_Noise_Test_M->Sizes.checksums[3] = (1221103974U);

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
  Meas_Noise_Test_M->Sizes.numBlocks = (32);/* Number of blocks */
  Meas_Noise_Test_M->Sizes.numBlockIO = (23);/* Number of block outputs */
  Meas_Noise_Test_M->Sizes.numBlockPrms = (14);/* Sum of parameter "widths" */
  return Meas_Noise_Test_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
