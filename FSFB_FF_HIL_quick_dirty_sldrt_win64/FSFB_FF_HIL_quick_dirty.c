/*
 * FSFB_FF_HIL_quick_dirty.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "FSFB_FF_HIL_quick_dirty".
 *
 * Model version              : 5.70
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Tue Apr 26 13:08:38 2022
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "FSFB_FF_HIL_quick_dirty.h"
#include <string.h>
#include "rtwtypes.h"
#include <emmintrin.h>
#include <stdio.h>
#include <math.h>
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
  __m128d tmp_5;
  __m128d tmp_6;
  real_T P_k_m[64];
  real_T b_I_0[64];
  real_T X[48];
  real_T X_tmp[48];
  real_T tmp_1[48];
  real_T A[36];
  real_T rtb_apriori[8];
  real_T tmp[8];
  real_T tmp_0[8];
  real_T rtb_Gain4[6];
  real_T tmp_2[6];
  real_T tmp_3[5];
  real_T tmp_4[5];
  real_T rtb_Sum_d;
  real_T rtb_q;
  real_T s;
  int32_T c_ix;
  int32_T ijA;
  int32_T ix;
  int32_T iy;
  int32_T jj;
  int32_T kBcol;
  int32_T rtb_xposTS;
  int8_T b_I[64];
  int8_T ipiv[6];
  ZCEventType zcEvent;

  /* Reset subsysRan breadcrumbs */
  srClearBC(FSFB_FF_HIL_quick_dirty_DW.SampleandHold_SubsysRanBC);

  /* MATLAB Function: '<Root>/u_FF' */
  FSFB_FF_HIL_quick_dirty_B.out1[0] = 0.0;
  FSFB_FF_HIL_quick_dirty_B.out1[1] = 0.0;
  for (rtb_xposTS = 0; rtb_xposTS <= 6; rtb_xposTS += 2) {
    /* Gain: '<S11>/Gain3' */
    tmp_6 = _mm_set1_pd(0.0);

    /* Gain: '<S11>/Gain5' incorporates:
     *  Gain: '<S11>/Gain3'
     */
    _mm_storeu_pd(&tmp_0[rtb_xposTS], tmp_6);

    /* Gain: '<S11>/Gain3' incorporates:
     *  Constant: '<S5>/Constant'
     */
    _mm_storeu_pd(&tmp[rtb_xposTS], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
      (&FSFB_FF_HIL_quick_dirty_P.B[rtb_xposTS + 8]), _mm_set1_pd
      (FSFB_FF_HIL_quick_dirty_P.Constant_Value[1])), _mm_add_pd(_mm_mul_pd
      (_mm_loadu_pd(&FSFB_FF_HIL_quick_dirty_P.B[rtb_xposTS]), _mm_set1_pd
       (FSFB_FF_HIL_quick_dirty_P.Constant_Value[0])), tmp_6)));
  }

  /* Gain: '<S11>/Gain5' incorporates:
   *  UnitDelay: '<S11>/Unit Delay1'
   */
  for (rtb_xposTS = 0; rtb_xposTS < 8; rtb_xposTS++) {
    for (jj = 0; jj <= 6; jj += 2) {
      tmp_6 = _mm_loadu_pd(&tmp_0[jj]);
      _mm_storeu_pd(&tmp_0[jj], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&FSFB_FF_HIL_quick_dirty_P.A[(rtb_xposTS << 3) + jj]), _mm_set1_pd
        (FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE[rtb_xposTS])), tmp_6));
    }
  }

  for (rtb_xposTS = 0; rtb_xposTS <= 6; rtb_xposTS += 2) {
    /* Sum: '<S11>/Sum3' */
    tmp_6 = _mm_loadu_pd(&tmp[rtb_xposTS]);
    tmp_5 = _mm_loadu_pd(&tmp_0[rtb_xposTS]);
    _mm_storeu_pd(&rtb_apriori[rtb_xposTS], _mm_add_pd(tmp_6, tmp_5));
  }

  /* S-Function (sldrtsi): '<S13>/Stream Input' */
  /* S-Function Block: <S13>/Stream Input */
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

  /* ScanString: '<S13>/String to Double' */
  rtb_xposTS = 0;
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o1[0], "%d", &rtb_xposTS);

  /* Gain: '<S13>/Gain' */
  FSFB_FF_HIL_quick_dirty_B.bx = (real_T)FSFB_FF_HIL_quick_dirty_P.Gain_Gain_a *
    9.0949470177292824E-13 * (real_T)rtb_xposTS;

  /* ScanString: '<S13>/String to Double4' */
  FSFB_FF_HIL_quick_dirty_B.IMUx = 0.0;

  /* ScanString: '<S13>/String to Double4' */
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o3[0], "%lf",
         &FSFB_FF_HIL_quick_dirty_B.IMUx);

  /* Gain: '<S16>/Gain1' */
  FSFB_FF_HIL_quick_dirty_B.Gain1 = FSFB_FF_HIL_quick_dirty_P.Gain1_Gain *
    FSFB_FF_HIL_quick_dirty_B.IMUx;

  /* ScanString: '<S13>/String to Double5' */
  FSFB_FF_HIL_quick_dirty_B.GyroX = 0.0;

  /* ScanString: '<S13>/String to Double5' */
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o4[0], "%lf",
         &FSFB_FF_HIL_quick_dirty_B.GyroX);

  /* Gain: '<S17>/Gain1' */
  FSFB_FF_HIL_quick_dirty_B.Gain1_k = FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_n *
    FSFB_FF_HIL_quick_dirty_B.GyroX;

  /* ScanString: '<S13>/String to Double2' */
  rtb_Sum_d = 0.0;
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o5[0], "%lf", &rtb_Sum_d);

  /* Gain: '<S13>/Gain2' */
  FSFB_FF_HIL_quick_dirty_B.by = FSFB_FF_HIL_quick_dirty_P.Gain2_Gain *
    rtb_Sum_d;

  /* ScanString: '<S13>/String to Double6' */
  FSFB_FF_HIL_quick_dirty_B.IMUy = 0.0;

  /* ScanString: '<S13>/String to Double6' */
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o7[0], "%lf",
         &FSFB_FF_HIL_quick_dirty_B.IMUy);

  /* Gain: '<S18>/Gain1' */
  FSFB_FF_HIL_quick_dirty_B.Gain1_l = FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_b *
    FSFB_FF_HIL_quick_dirty_B.IMUy;

  /* ScanString: '<S13>/String to Double7' */
  FSFB_FF_HIL_quick_dirty_B.GyroY = 0.0;

  /* ScanString: '<S13>/String to Double7' */
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o8[0], "%lf",
         &FSFB_FF_HIL_quick_dirty_B.GyroY);

  /* Gain: '<S19>/Gain1' */
  FSFB_FF_HIL_quick_dirty_B.Gain1_n = FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_k *
    FSFB_FF_HIL_quick_dirty_B.GyroY;

  /* Gain: '<S11>/Gain4' */
  for (rtb_xposTS = 0; rtb_xposTS < 6; rtb_xposTS++) {
    rtb_Gain4[rtb_xposTS] = 0.0;
  }

  for (jj = 0; jj < 8; jj++) {
    for (rtb_xposTS = 0; rtb_xposTS <= 4; rtb_xposTS += 2) {
      tmp_6 = _mm_loadu_pd(&rtb_Gain4[rtb_xposTS]);
      _mm_storeu_pd(&rtb_Gain4[rtb_xposTS], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&FSFB_FF_HIL_quick_dirty_P.H[6 * jj + rtb_xposTS]), _mm_set1_pd
        (rtb_apriori[jj])), tmp_6));
    }

    /* MATLAB Function: '<S14>/MATLAB Function' incorporates:
     *  Constant: '<S14>/Constant'
     *  UnitDelay: '<S14>/Unit Delay'
     */
    memset(&b_I_0[jj << 3], 0, sizeof(real_T) << 3U);
    for (kBcol = 0; kBcol < 8; kBcol++) {
      for (rtb_xposTS = 0; rtb_xposTS <= 6; rtb_xposTS += 2) {
        iy = (jj << 3) + rtb_xposTS;
        tmp_6 = _mm_loadu_pd(&b_I_0[iy]);
        _mm_storeu_pd(&b_I_0[iy], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&FSFB_FF_HIL_quick_dirty_P.A[(kBcol << 3) + rtb_xposTS]), _mm_set1_pd
          (FSFB_FF_HIL_quick_dirty_DW.UnitDelay_DSTATE[(jj << 3) + kBcol])),
          tmp_6));
      }
    }
  }

  /* End of Gain: '<S11>/Gain4' */

  /* MATLAB Function: '<S14>/MATLAB Function' incorporates:
   *  Constant: '<S14>/Constant'
   *  Constant: '<S14>/Constant1'
   *  Constant: '<S14>/Constant2'
   *  Constant: '<S14>/Constant3'
   */
  for (rtb_xposTS = 0; rtb_xposTS < 8; rtb_xposTS++) {
    for (jj = 0; jj < 8; jj++) {
      s = 0.0;
      for (kBcol = 0; kBcol < 8; kBcol++) {
        iy = kBcol << 3;
        s += b_I_0[iy + rtb_xposTS] * FSFB_FF_HIL_quick_dirty_P.A[iy + jj];
      }

      kBcol = (jj << 3) + rtb_xposTS;
      P_k_m[kBcol] = FSFB_FF_HIL_quick_dirty_P.Q_KF[kBcol] + s;
    }
  }

  for (rtb_xposTS = 0; rtb_xposTS < 6; rtb_xposTS++) {
    for (jj = 0; jj < 8; jj++) {
      kBcol = (rtb_xposTS << 3) + jj;
      X_tmp[kBcol] = FSFB_FF_HIL_quick_dirty_P.H[6 * jj + rtb_xposTS];
      X[kBcol] = 0.0;
    }

    for (jj = 0; jj < 8; jj++) {
      for (kBcol = 0; kBcol <= 6; kBcol += 2) {
        tmp_6 = _mm_loadu_pd(&P_k_m[(jj << 3) + kBcol]);
        iy = rtb_xposTS << 3;
        ix = iy + kBcol;
        tmp_5 = _mm_loadu_pd(&X[ix]);
        _mm_storeu_pd(&X[ix], _mm_add_pd(_mm_mul_pd(tmp_6, _mm_set1_pd(X_tmp[iy
          + jj])), tmp_5));
      }
    }
  }

  for (rtb_xposTS = 0; rtb_xposTS < 8; rtb_xposTS++) {
    for (jj = 0; jj < 6; jj++) {
      tmp_1[jj + 6 * rtb_xposTS] = 0.0;
    }

    for (kBcol = 0; kBcol < 8; kBcol++) {
      for (jj = 0; jj <= 4; jj += 2) {
        iy = 6 * rtb_xposTS + jj;
        tmp_6 = _mm_loadu_pd(&tmp_1[iy]);
        _mm_storeu_pd(&tmp_1[iy], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&FSFB_FF_HIL_quick_dirty_P.H[6 * kBcol + jj]), _mm_set1_pd(P_k_m
          [(rtb_xposTS << 3) + kBcol])), tmp_6));
      }
    }
  }

  for (rtb_xposTS = 0; rtb_xposTS < 6; rtb_xposTS++) {
    for (jj = 0; jj < 6; jj++) {
      s = 0.0;
      for (kBcol = 0; kBcol < 8; kBcol++) {
        s += tmp_1[6 * kBcol + rtb_xposTS] * X_tmp[(jj << 3) + kBcol];
      }

      iy = 6 * jj + rtb_xposTS;
      A[iy] = FSFB_FF_HIL_quick_dirty_P.R_KF[iy] + s;
    }

    ipiv[rtb_xposTS] = (int8_T)(rtb_xposTS + 1);
  }

  for (rtb_xposTS = 0; rtb_xposTS < 5; rtb_xposTS++) {
    jj = rtb_xposTS * 7;
    iy = 0;
    ix = jj;
    rtb_Sum_d = fabs(A[jj]);
    for (kBcol = 2; kBcol <= 6 - rtb_xposTS; kBcol++) {
      ix++;
      s = fabs(A[ix]);
      if (s > rtb_Sum_d) {
        iy = kBcol - 1;
        rtb_Sum_d = s;
      }
    }

    if (A[jj + iy] != 0.0) {
      if (iy != 0) {
        ix = rtb_xposTS + iy;
        ipiv[rtb_xposTS] = (int8_T)(ix + 1);
        for (kBcol = 0; kBcol < 6; kBcol++) {
          c_ix = kBcol * 6 + rtb_xposTS;
          rtb_Sum_d = A[c_ix];
          iy = kBcol * 6 + ix;
          A[c_ix] = A[iy];
          A[iy] = rtb_Sum_d;
        }
      }

      iy = (jj - rtb_xposTS) + 6;
      for (ix = jj + 1; ix < iy; ix++) {
        A[ix] /= A[jj];
      }
    }

    iy = jj;
    ix = jj + 6;
    for (kBcol = 0; kBcol <= 4 - rtb_xposTS; kBcol++) {
      if (A[ix] != 0.0) {
        int32_T c;
        rtb_Sum_d = -A[ix];
        c_ix = jj + 1;
        ijA = iy + 7;
        c = (iy - rtb_xposTS) + 12;
        while (ijA + 1 <= c) {
          A[ijA] += A[c_ix] * rtb_Sum_d;
          c_ix++;
          ijA++;
        }
      }

      ix += 6;
      iy += 6;
    }
  }

  for (rtb_xposTS = 0; rtb_xposTS < 6; rtb_xposTS++) {
    jj = rtb_xposTS << 3;
    iy = 6 * rtb_xposTS;
    for (ix = 0; ix < rtb_xposTS; ix++) {
      kBcol = ix << 3;
      if (A[ix + iy] != 0.0) {
        for (c_ix = 0; c_ix < 8; c_ix++) {
          ijA = c_ix + jj;
          X[ijA] -= A[ix + iy] * X[c_ix + kBcol];
        }
      }
    }

    rtb_Sum_d = 1.0 / A[rtb_xposTS + iy];
    for (iy = 0; iy <= 6; iy += 2) {
      tmp_6 = _mm_loadu_pd(&X[iy + jj]);
      _mm_storeu_pd(&X[iy + jj], _mm_mul_pd(tmp_6, _mm_set1_pd(rtb_Sum_d)));
    }
  }

  for (rtb_xposTS = 5; rtb_xposTS >= 0; rtb_xposTS--) {
    jj = rtb_xposTS << 3;
    iy = 6 * rtb_xposTS - 1;
    for (ix = rtb_xposTS + 2; ix < 7; ix++) {
      kBcol = (ix - 1) << 3;
      if (A[ix + iy] != 0.0) {
        for (c_ix = 0; c_ix < 8; c_ix++) {
          ijA = c_ix + jj;
          X[ijA] -= A[ix + iy] * X[c_ix + kBcol];
        }
      }
    }
  }

  for (rtb_xposTS = 4; rtb_xposTS >= 0; rtb_xposTS--) {
    int8_T ipiv_0;
    ipiv_0 = ipiv[rtb_xposTS];
    if (rtb_xposTS + 1 != ipiv_0) {
      for (iy = 0; iy < 8; iy++) {
        rtb_Sum_d = X[(rtb_xposTS << 3) + iy];
        ijA = ((ipiv_0 - 1) << 3) + iy;
        X[iy + (rtb_xposTS << 3)] = X[ijA];
        X[ijA] = rtb_Sum_d;
      }
    }
  }

  memset(&b_I[0], 0, sizeof(int8_T) << 6U);
  for (rtb_xposTS = 0; rtb_xposTS < 8; rtb_xposTS++) {
    b_I[rtb_xposTS + (rtb_xposTS << 3)] = 1;
  }

  for (rtb_xposTS = 0; rtb_xposTS < 8; rtb_xposTS++) {
    for (jj = 0; jj < 8; jj++) {
      s = 0.0;
      for (kBcol = 0; kBcol < 6; kBcol++) {
        s += X[(kBcol << 3) + rtb_xposTS] * FSFB_FF_HIL_quick_dirty_P.H[6 * jj +
          kBcol];
      }

      kBcol = (jj << 3) + rtb_xposTS;
      b_I_0[kBcol] = (real_T)b_I[kBcol] - s;
      FSFB_FF_HIL_quick_dirty_B.P_k[jj + (rtb_xposTS << 3)] = 0.0;
    }
  }

  /* Sum: '<S11>/Sum4' */
  tmp_2[0] = FSFB_FF_HIL_quick_dirty_B.bx - rtb_Gain4[0];
  tmp_2[1] = FSFB_FF_HIL_quick_dirty_B.Gain1 - rtb_Gain4[1];
  tmp_2[2] = FSFB_FF_HIL_quick_dirty_B.Gain1_k - rtb_Gain4[2];
  tmp_2[3] = FSFB_FF_HIL_quick_dirty_B.by - rtb_Gain4[3];
  tmp_2[4] = FSFB_FF_HIL_quick_dirty_B.Gain1_l - rtb_Gain4[4];
  tmp_2[5] = FSFB_FF_HIL_quick_dirty_B.Gain1_n - rtb_Gain4[5];
  for (rtb_xposTS = 0; rtb_xposTS < 8; rtb_xposTS++) {
    /* MATLAB Function: '<S14>/MATLAB Function' */
    for (jj = 0; jj < 8; jj++) {
      for (kBcol = 0; kBcol <= 6; kBcol += 2) {
        tmp_6 = _mm_loadu_pd(&b_I_0[(jj << 3) + kBcol]);
        iy = rtb_xposTS << 3;
        ix = iy + kBcol;
        tmp_5 = _mm_loadu_pd(&FSFB_FF_HIL_quick_dirty_B.P_k[ix]);
        _mm_storeu_pd(&FSFB_FF_HIL_quick_dirty_B.P_k[ix], _mm_add_pd(_mm_mul_pd
          (tmp_6, _mm_set1_pd(P_k_m[iy + jj])), tmp_5));
      }
    }

    /* Sum: '<S11>/Sum5' incorporates:
     *  MATLAB Function: '<S14>/MATLAB Function'
     */
    s = 0.0;
    for (jj = 0; jj < 6; jj++) {
      s += X[(jj << 3) + rtb_xposTS] * tmp_2[jj];
    }

    FSFB_FF_HIL_quick_dirty_B.aposteriori[rtb_xposTS] = rtb_apriori[rtb_xposTS]
      + s;

    /* End of Sum: '<S11>/Sum5' */
  }

  /* Step: '<Root>/Step' */
  if (FSFB_FF_HIL_quick_dirty_M->Timing.t[0] < 5.0 *
      FSFB_FF_HIL_quick_dirty_P.Ts) {
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
    memcpy(&FSFB_FF_HIL_quick_dirty_B.In[0],
           &FSFB_FF_HIL_quick_dirty_B.aposteriori[0], sizeof(real_T) << 3U);
    FSFB_FF_HIL_quick_dirty_DW.SampleandHold_SubsysRanBC = 4;
  }

  /* End of Outputs for SubSystem: '<Root>/Sample and Hold' */
  /* ScanString: '<S13>/String to Double1' */
  rtb_Sum_d = 0.0;
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o2[0], "%lf", &rtb_Sum_d);

  /* Gain: '<S13>/Gain1' */
  FSFB_FF_HIL_quick_dirty_B.bx_dot = FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_be *
    rtb_Sum_d;

  /* ScanString: '<S13>/String to Double3' */
  rtb_Sum_d = 0.0;
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o6[0], "%lf", &rtb_Sum_d);

  /* Gain: '<S13>/Gain3' */
  FSFB_FF_HIL_quick_dirty_B.by_dot = FSFB_FF_HIL_quick_dirty_P.Gain3_Gain *
    rtb_Sum_d;

  /* SignalConversion generated from: '<Root>/x measured' */
  FSFB_FF_HIL_quick_dirty_B.xmeasured[0] = FSFB_FF_HIL_quick_dirty_B.bx;
  FSFB_FF_HIL_quick_dirty_B.xmeasured[1] = FSFB_FF_HIL_quick_dirty_B.bx_dot;
  FSFB_FF_HIL_quick_dirty_B.xmeasured[2] = FSFB_FF_HIL_quick_dirty_B.Gain1;
  FSFB_FF_HIL_quick_dirty_B.xmeasured[3] = FSFB_FF_HIL_quick_dirty_B.Gain1_k;
  FSFB_FF_HIL_quick_dirty_B.xmeasured[4] = FSFB_FF_HIL_quick_dirty_B.by;
  FSFB_FF_HIL_quick_dirty_B.xmeasured[5] = FSFB_FF_HIL_quick_dirty_B.by_dot;
  FSFB_FF_HIL_quick_dirty_B.xmeasured[6] = FSFB_FF_HIL_quick_dirty_B.Gain1_l;
  FSFB_FF_HIL_quick_dirty_B.xmeasured[7] = FSFB_FF_HIL_quick_dirty_B.Gain1_n;

  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_B.integratederror =
    FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE;

  /* MATLAB Function: '<S4>/x dim stpt smoothing' incorporates:
   *  Clock: '<S4>/Clock1'
   *  MATLAB Function: '<S4>/y dim stpt smoothing'
   */
  s = exp(-FSFB_FF_HIL_quick_dirty_M->Timing.t[0] /
          FSFB_FF_HIL_quick_dirty_P.Tau);

  /* Gain: '<S1>/Gain1' incorporates:
   *  SignalConversion generated from: '<S1>/Gain1'
   */
  tmp_3[0] = FSFB_FF_HIL_quick_dirty_B.integratederror;

  /* MATLAB Function: '<S4>/x dim stpt smoothing' incorporates:
   *  MATLAB Function: '<S4>/x_Setpoint_Function'
   *  MATLAB Function: '<S4>/y dim stpt smoothing'
   */
  rtb_q = (1.0 - s) * 0.0;
  FSFB_FF_HIL_quick_dirty_B.smoothed_x[0] = FSFB_FF_HIL_quick_dirty_B.In[0] * s
    + rtb_q;

  /* Sum: '<S1>/Sum' */
  FSFB_FF_HIL_quick_dirty_B.e_vec[0] = FSFB_FF_HIL_quick_dirty_B.smoothed_x[0] -
    FSFB_FF_HIL_quick_dirty_B.aposteriori[0];

  /* Gain: '<S1>/Gain1' incorporates:
   *  SignalConversion generated from: '<S1>/Gain1'
   */
  tmp_3[1] = FSFB_FF_HIL_quick_dirty_B.e_vec[0];

  /* MATLAB Function: '<S4>/x dim stpt smoothing' */
  FSFB_FF_HIL_quick_dirty_B.smoothed_x[1] = FSFB_FF_HIL_quick_dirty_B.In[1] * s
    + rtb_q;

  /* Sum: '<S1>/Sum' */
  FSFB_FF_HIL_quick_dirty_B.e_vec[1] = FSFB_FF_HIL_quick_dirty_B.smoothed_x[1] -
    FSFB_FF_HIL_quick_dirty_B.aposteriori[1];

  /* Gain: '<S1>/Gain1' incorporates:
   *  SignalConversion generated from: '<S1>/Gain1'
   */
  tmp_3[2] = FSFB_FF_HIL_quick_dirty_B.e_vec[1];

  /* MATLAB Function: '<S4>/x dim stpt smoothing' */
  FSFB_FF_HIL_quick_dirty_B.smoothed_x[2] = FSFB_FF_HIL_quick_dirty_B.In[2] * s
    + rtb_q;

  /* Sum: '<S1>/Sum' */
  FSFB_FF_HIL_quick_dirty_B.e_vec[2] = FSFB_FF_HIL_quick_dirty_B.smoothed_x[2] -
    FSFB_FF_HIL_quick_dirty_B.aposteriori[2];

  /* Gain: '<S1>/Gain1' incorporates:
   *  SignalConversion generated from: '<S1>/Gain1'
   */
  tmp_3[3] = FSFB_FF_HIL_quick_dirty_B.e_vec[2];

  /* MATLAB Function: '<S4>/x dim stpt smoothing' */
  FSFB_FF_HIL_quick_dirty_B.smoothed_x[3] = FSFB_FF_HIL_quick_dirty_B.In[3] * s
    + rtb_q;

  /* Sum: '<S1>/Sum' */
  FSFB_FF_HIL_quick_dirty_B.e_vec[3] = FSFB_FF_HIL_quick_dirty_B.smoothed_x[3] -
    FSFB_FF_HIL_quick_dirty_B.aposteriori[3];

  /* Gain: '<S1>/Gain1' incorporates:
   *  SignalConversion generated from: '<S1>/Gain1'
   */
  tmp_3[4] = FSFB_FF_HIL_quick_dirty_B.e_vec[3];
  rtb_Sum_d = 0.0;

  /* DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_B.integratederror_d =
    FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_b;

  /* SignalConversion generated from: '<S2>/Gain1' */
  tmp_4[0] = FSFB_FF_HIL_quick_dirty_B.integratederror_d;

  /* MATLAB Function: '<S4>/y dim stpt smoothing' */
  FSFB_FF_HIL_quick_dirty_B.smoothed_y[0] = FSFB_FF_HIL_quick_dirty_B.In[4] * s
    + rtb_q;

  /* Sum: '<S2>/Sum' */
  FSFB_FF_HIL_quick_dirty_B.ey_vec[0] = FSFB_FF_HIL_quick_dirty_B.smoothed_y[0]
    - FSFB_FF_HIL_quick_dirty_B.aposteriori[4];

  /* SignalConversion generated from: '<S2>/Gain1' */
  tmp_4[1] = FSFB_FF_HIL_quick_dirty_B.ey_vec[0];

  /* MATLAB Function: '<S4>/y dim stpt smoothing' */
  FSFB_FF_HIL_quick_dirty_B.smoothed_y[1] = FSFB_FF_HIL_quick_dirty_B.In[5] * s
    + rtb_q;

  /* Sum: '<S2>/Sum' */
  FSFB_FF_HIL_quick_dirty_B.ey_vec[1] = FSFB_FF_HIL_quick_dirty_B.smoothed_y[1]
    - FSFB_FF_HIL_quick_dirty_B.aposteriori[5];

  /* SignalConversion generated from: '<S2>/Gain1' */
  tmp_4[2] = FSFB_FF_HIL_quick_dirty_B.ey_vec[1];

  /* MATLAB Function: '<S4>/y dim stpt smoothing' */
  FSFB_FF_HIL_quick_dirty_B.smoothed_y[2] = FSFB_FF_HIL_quick_dirty_B.In[6] * s
    + rtb_q;

  /* Sum: '<S2>/Sum' */
  FSFB_FF_HIL_quick_dirty_B.ey_vec[2] = FSFB_FF_HIL_quick_dirty_B.smoothed_y[2]
    - FSFB_FF_HIL_quick_dirty_B.aposteriori[6];

  /* SignalConversion generated from: '<S2>/Gain1' */
  tmp_4[3] = FSFB_FF_HIL_quick_dirty_B.ey_vec[2];

  /* MATLAB Function: '<S4>/y dim stpt smoothing' */
  FSFB_FF_HIL_quick_dirty_B.smoothed_y[3] = FSFB_FF_HIL_quick_dirty_B.In[7] * s
    + rtb_q;

  /* Sum: '<S2>/Sum' */
  FSFB_FF_HIL_quick_dirty_B.ey_vec[3] = FSFB_FF_HIL_quick_dirty_B.smoothed_y[3]
    - FSFB_FF_HIL_quick_dirty_B.aposteriori[7];

  /* SignalConversion generated from: '<S2>/Gain1' */
  tmp_4[4] = FSFB_FF_HIL_quick_dirty_B.ey_vec[3];

  /* Gain: '<S2>/Gain1' */
  s = 0.0;
  for (rtb_xposTS = 0; rtb_xposTS < 5; rtb_xposTS++) {
    /* Gain: '<S1>/Gain1' */
    rtb_Sum_d += -FSFB_FF_HIL_quick_dirty_P.K1[rtb_xposTS] * tmp_3[rtb_xposTS];

    /* Gain: '<S2>/Gain1' */
    s += -FSFB_FF_HIL_quick_dirty_P.K2[rtb_xposTS] * tmp_4[rtb_xposTS];
  }

  real_T rtb_Product1;
  real_T rtb_Sum;
  real_T rtb_d;
  real_T rtb_d_d;
  real_T rtb_p_c;
  real_T rtb_q_l;
  real_T rtb_r;
  real_T rtb_r_o;

  /* Sum: '<Root>/Sum' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S2>/Gain1'
   */
  FSFB_FF_HIL_quick_dirty_B.u_des[0] = rtb_Sum_d +
    FSFB_FF_HIL_quick_dirty_B.out1[0];
  FSFB_FF_HIL_quick_dirty_B.u_des[1] = s + FSFB_FF_HIL_quick_dirty_B.out1[1];

  /* S-Function (sldrtso): '<S12>/Stream Output' incorporates:
   *  Constant: '<S5>/Constant'
   */
  /* S-Function Block: <S12>/Stream Output */

  /* no code required */

  /* ToAsyncQueueBlock generated from: '<S5>/Kalman Filter' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.aposteriori[0];
      int32_T size = 8*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(1460631441U, time, pData, size);
    }
  }

  /* SampleTimeMath: '<S20>/TSamp'
   *
   * About '<S20>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  FSFB_FF_HIL_quick_dirty_B.TSamp = FSFB_FF_HIL_quick_dirty_B.bx *
    FSFB_FF_HIL_quick_dirty_P.TSamp_WtEt;

  /* Sum: '<S20>/Diff' incorporates:
   *  UnitDelay: '<S20>/UD'
   */
  FSFB_FF_HIL_quick_dirty_B.Diff = FSFB_FF_HIL_quick_dirty_B.TSamp -
    FSFB_FF_HIL_quick_dirty_DW.UD_DSTATE;

  /* ToAsyncQueueBlock generated from: '<S13>/Discrete Derivative' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.Diff;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2525711567U, time, pData, size);
    }
  }

  /* Sum: '<S22>/Sum' incorporates:
   *  UnitDelay: '<S22>/Unit Delay1'
   */
  rtb_Sum_d = FSFB_FF_HIL_quick_dirty_B.Diff +
    FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE_n;

  /* Gain: '<S22>/tau' incorporates:
   *  Constant: '<S13>/Constant'
   */
  s = FSFB_FF_HIL_quick_dirty_P.tau_Gain *
    FSFB_FF_HIL_quick_dirty_P.Constant_Value_a;

  /* Product: '<S24>/Product2' */
  rtb_q = s * s;

  /* Sum: '<S24>/Add' incorporates:
   *  Constant: '<S24>/Constant'
   */
  rtb_r = rtb_q + FSFB_FF_HIL_quick_dirty_P.Constant_Value_aa;

  /* Gain: '<S24>/Gain' */
  s *= FSFB_FF_HIL_quick_dirty_P.Gain_Gain;

  /* Sum: '<S24>/Add1' */
  rtb_d = rtb_r + s;

  /* Product: '<S22>/Product1' incorporates:
   *  Product: '<S24>/Product3'
   */
  rtb_Product1 = rtb_q / rtb_d * rtb_Sum_d;

  /* Sum: '<S23>/Sum' incorporates:
   *  UnitDelay: '<S23>/Unit Delay1'
   */
  rtb_Sum = rtb_Product1 + FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE_j;

  /* Gain: '<S23>/tau' incorporates:
   *  Constant: '<S13>/Constant'
   */
  rtb_p_c = FSFB_FF_HIL_quick_dirty_P.tau_Gain_h *
    FSFB_FF_HIL_quick_dirty_P.Constant_Value_a;

  /* Product: '<S25>/Product2' */
  rtb_q_l = rtb_p_c * rtb_p_c;

  /* Sum: '<S25>/Add' incorporates:
   *  Constant: '<S25>/Constant'
   */
  rtb_r_o = rtb_q_l + FSFB_FF_HIL_quick_dirty_P.Constant_Value_f;

  /* Gain: '<S25>/Gain' */
  rtb_p_c *= FSFB_FF_HIL_quick_dirty_P.Gain_Gain_g;

  /* Sum: '<S25>/Add1' */
  rtb_d_d = rtb_r_o + rtb_p_c;

  /* Product: '<S23>/Product1' incorporates:
   *  Product: '<S25>/Product3'
   */
  FSFB_FF_HIL_quick_dirty_B.Product1 = rtb_q_l / rtb_d_d * rtb_Sum;

  /* ToAsyncQueueBlock generated from: '<S13>/Discrete Varying Lowpass' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.Product1;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(634757125U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S13>/Gain1' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.bx_dot;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3832714216U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S13>/Gain2' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.by;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(991069379U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S13>/Gain3' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.by_dot;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(1253159944U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S13>/Gain' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.bx;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2944572654U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S13>/String to Double4' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.IMUx;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3369940540U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S13>/String to Double5' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.GyroX;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2880840045U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S13>/String to Double6' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.IMUy;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2322186679U, time, pData, size);
    }
  }

  /* ToAsyncQueueBlock generated from: '<S13>/String to Double7' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.GyroY;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(3891162284U, time, pData, size);
    }
  }

  /* ScanString: '<S13>/String to Double8' */
  FSFB_FF_HIL_quick_dirty_B.TimingParity = 0.0;

  /* ScanString: '<S13>/String to Double8' */
  sscanf(&FSFB_FF_HIL_quick_dirty_B.StreamInput_o9[0], "%lf",
         &FSFB_FF_HIL_quick_dirty_B.TimingParity);

  /* ToAsyncQueueBlock generated from: '<S13>/String to Double8' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.TimingParity;
      int32_T size = 1*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2792611647U, time, pData, size);
    }
  }

  /* Sum: '<S22>/Sum1' incorporates:
   *  Constant: '<S24>/Constant1'
   *  Gain: '<S22>/Gain1'
   *  Product: '<S22>/Product5'
   *  Product: '<S24>/Product4'
   *  Sum: '<S22>/Sum2'
   *  Sum: '<S24>/Add2'
   *  UnitDelay: '<S22>/Unit Delay2'
   */
  FSFB_FF_HIL_quick_dirty_B.Sum1 = ((FSFB_FF_HIL_quick_dirty_P.Constant1_Value -
    rtb_q) / rtb_d * rtb_Sum_d + FSFB_FF_HIL_quick_dirty_B.Diff) *
    FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_bv +
    FSFB_FF_HIL_quick_dirty_DW.UnitDelay2_DSTATE;

  /* Sum: '<S22>/Sum3' incorporates:
   *  Product: '<S22>/Product2'
   *  Product: '<S24>/Product5'
   *  Sum: '<S24>/Add3'
   */
  FSFB_FF_HIL_quick_dirty_B.Sum3 = FSFB_FF_HIL_quick_dirty_B.Diff - 1.0 / rtb_d *
    (rtb_r - s) * rtb_Sum_d;

  /* Sum: '<S23>/Sum1' incorporates:
   *  Constant: '<S25>/Constant1'
   *  Gain: '<S23>/Gain1'
   *  Product: '<S23>/Product5'
   *  Product: '<S25>/Product4'
   *  Sum: '<S23>/Sum2'
   *  Sum: '<S25>/Add2'
   *  UnitDelay: '<S23>/Unit Delay2'
   */
  FSFB_FF_HIL_quick_dirty_B.Sum1_b =
    ((FSFB_FF_HIL_quick_dirty_P.Constant1_Value_d - rtb_q_l) / rtb_d_d * rtb_Sum
     + rtb_Product1) * FSFB_FF_HIL_quick_dirty_P.Gain1_Gain_f +
    FSFB_FF_HIL_quick_dirty_DW.UnitDelay2_DSTATE_h;

  /* Sum: '<S23>/Sum3' incorporates:
   *  Product: '<S23>/Product2'
   *  Product: '<S25>/Product5'
   *  Sum: '<S25>/Add3'
   */
  FSFB_FF_HIL_quick_dirty_B.Sum3_b = rtb_Product1 - 1.0 / rtb_d_d * (rtb_r_o -
    rtb_p_c) * rtb_Sum;

  /* Gain: '<S5>/Gear Ratio Assumption' */
  rtb_Sum_d = FSFB_FF_HIL_quick_dirty_P.GearRatioAssumption_Gain *
    FSFB_FF_HIL_quick_dirty_B.u_des[0];

  /* Saturate: '<S5>/Saturation1' */
  if (rtb_Sum_d > FSFB_FF_HIL_quick_dirty_P.Saturation1_UpperSat) {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[0] =
      FSFB_FF_HIL_quick_dirty_P.Saturation1_UpperSat;
  } else if (rtb_Sum_d < FSFB_FF_HIL_quick_dirty_P.Saturation1_LowerSat) {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[0] =
      FSFB_FF_HIL_quick_dirty_P.Saturation1_LowerSat;
  } else {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[0] = rtb_Sum_d;
  }

  /* Gain: '<S5>/Gear Ratio Assumption' */
  rtb_Sum_d = FSFB_FF_HIL_quick_dirty_P.GearRatioAssumption_Gain *
    FSFB_FF_HIL_quick_dirty_B.u_des[1];

  /* Saturate: '<S5>/Saturation1' */
  if (rtb_Sum_d > FSFB_FF_HIL_quick_dirty_P.Saturation1_UpperSat) {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[1] =
      FSFB_FF_HIL_quick_dirty_P.Saturation1_UpperSat;
  } else if (rtb_Sum_d < FSFB_FF_HIL_quick_dirty_P.Saturation1_LowerSat) {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[1] =
      FSFB_FF_HIL_quick_dirty_P.Saturation1_LowerSat;
  } else {
    /* Saturate: '<S5>/Saturation1' */
    FSFB_FF_HIL_quick_dirty_B.Torque_Sat[1] = rtb_Sum_d;
  }

  /* ToAsyncQueueBlock generated from: '<S5>/Saturation1' */
  {
    {
      double time = FSFB_FF_HIL_quick_dirty_M->Timing.t[1];
      void *pData = (void *)&FSFB_FF_HIL_quick_dirty_B.Torque_Sat[0];
      int32_T size = 2*sizeof(real_T);
      sendToAsyncQueueTgtAppSvc(2427926711U, time, pData, size);
    }
  }
}

/* Model update function */
void FSFB_FF_HIL_quick_dirty_update(void)
{
  /* Update for UnitDelay: '<S11>/Unit Delay1' */
  memcpy(&FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE[0],
         &FSFB_FF_HIL_quick_dirty_B.aposteriori[0], sizeof(real_T) << 3U);

  /* Update for UnitDelay: '<S14>/Unit Delay' */
  memcpy(&FSFB_FF_HIL_quick_dirty_DW.UnitDelay_DSTATE[0],
         &FSFB_FF_HIL_quick_dirty_B.P_k[0], sizeof(real_T) << 6U);

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE +=
    FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_gainval *
    FSFB_FF_HIL_quick_dirty_B.e_vec[0];

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_b +=
    FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_gainval_p *
    FSFB_FF_HIL_quick_dirty_B.ey_vec[0];

  /* Update for S-Function (sldrtso): '<S12>/Stream Output' incorporates:
   *  Constant: '<S5>/Constant'
   */

  /* S-Function Block: <S12>/Stream Output */
  {
    char_T outstring[650U];
    int n = snprintf(outstring, 650U, "%g %g\n", (real_T)
                     FSFB_FF_HIL_quick_dirty_P.Constant_Value[0], (real_T)
                     FSFB_FF_HIL_quick_dirty_P.Constant_Value[1]);
    RTBIO_DriverIO(0, STREAMOUTPUT, IOWRITE, n, NULL, (double*) outstring, NULL);
  }

  /* Update for UnitDelay: '<S20>/UD' */
  FSFB_FF_HIL_quick_dirty_DW.UD_DSTATE = FSFB_FF_HIL_quick_dirty_B.TSamp;

  /* Update for UnitDelay: '<S22>/Unit Delay1' */
  FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE_n =
    FSFB_FF_HIL_quick_dirty_B.Sum1;

  /* Update for UnitDelay: '<S23>/Unit Delay1' */
  FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE_j =
    FSFB_FF_HIL_quick_dirty_B.Sum1_b;

  /* Update for UnitDelay: '<S22>/Unit Delay2' */
  FSFB_FF_HIL_quick_dirty_DW.UnitDelay2_DSTATE = FSFB_FF_HIL_quick_dirty_B.Sum3;

  /* Update for UnitDelay: '<S23>/Unit Delay2' */
  FSFB_FF_HIL_quick_dirty_DW.UnitDelay2_DSTATE_h =
    FSFB_FF_HIL_quick_dirty_B.Sum3_b;

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
  /* Start for S-Function (sldrtso): '<S12>/Stream Output' incorporates:
   *  Constant: '<S5>/Constant'
   */

  /* S-Function Block: <S12>/Stream Output */
  /* no initial value should be set */
  FSFB_FF_HIL_quick_dirty_PrevZCX.SampleandHold_Trig_ZCE = UNINITIALIZED_ZCSIG;

  {
    int32_T i;

    /* InitializeConditions for UnitDelay: '<S11>/Unit Delay1' */
    memcpy(&FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE[0],
           &FSFB_FF_HIL_quick_dirty_P.UnitDelay1_InitialCondition[0], sizeof
           (real_T) << 3U);

    /* InitializeConditions for UnitDelay: '<S14>/Unit Delay' */
    memcpy(&FSFB_FF_HIL_quick_dirty_DW.UnitDelay_DSTATE[0],
           &FSFB_FF_HIL_quick_dirty_P.UnitDelay_InitialCondition[0], sizeof
           (real_T) << 6U);

    /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
    FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE =
      FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_IC;

    /* InitializeConditions for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
    FSFB_FF_HIL_quick_dirty_DW.DiscreteTimeIntegrator_DSTATE_b =
      FSFB_FF_HIL_quick_dirty_P.DiscreteTimeIntegrator_IC_l;

    /* InitializeConditions for UnitDelay: '<S20>/UD' */
    FSFB_FF_HIL_quick_dirty_DW.UD_DSTATE =
      FSFB_FF_HIL_quick_dirty_P.DiscreteDerivative_ICPrevScaledInput;

    /* InitializeConditions for UnitDelay: '<S22>/Unit Delay1' */
    FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE_n =
      FSFB_FF_HIL_quick_dirty_P.UnitDelay1_InitialCondition_g;

    /* InitializeConditions for UnitDelay: '<S23>/Unit Delay1' */
    FSFB_FF_HIL_quick_dirty_DW.UnitDelay1_DSTATE_j =
      FSFB_FF_HIL_quick_dirty_P.UnitDelay1_InitialCondition_l;

    /* InitializeConditions for UnitDelay: '<S22>/Unit Delay2' */
    FSFB_FF_HIL_quick_dirty_DW.UnitDelay2_DSTATE =
      FSFB_FF_HIL_quick_dirty_P.UnitDelay2_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S23>/Unit Delay2' */
    FSFB_FF_HIL_quick_dirty_DW.UnitDelay2_DSTATE_h =
      FSFB_FF_HIL_quick_dirty_P.UnitDelay2_InitialCondition_p;

    /* SystemInitialize for Triggered SubSystem: '<Root>/Sample and Hold' */
    for (i = 0; i < 8; i++) {
      /* SystemInitialize for SignalConversion generated from: '<S3>/In' incorporates:
       *  Outport: '<S3>/ '
       */
      FSFB_FF_HIL_quick_dirty_B.In[i] = FSFB_FF_HIL_quick_dirty_P._Y0;
    }

    /* End of SystemInitialize for SubSystem: '<Root>/Sample and Hold' */
  }
}

/* Model terminate function */
void FSFB_FF_HIL_quick_dirty_terminate(void)
{
  /* Terminate for S-Function (sldrtso): '<S12>/Stream Output' incorporates:
   *  Constant: '<S5>/Constant'
   */

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

  rtmSetTFinal(FSFB_FF_HIL_quick_dirty_M, 2000.0);
  FSFB_FF_HIL_quick_dirty_M->Timing.stepSize0 = 0.005;
  FSFB_FF_HIL_quick_dirty_M->Timing.stepSize1 = 0.005;

  /* External mode info */
  FSFB_FF_HIL_quick_dirty_M->Sizes.checksums[0] = (4270060495U);
  FSFB_FF_HIL_quick_dirty_M->Sizes.checksums[1] = (2872185705U);
  FSFB_FF_HIL_quick_dirty_M->Sizes.checksums[2] = (2658821165U);
  FSFB_FF_HIL_quick_dirty_M->Sizes.checksums[3] = (305722332U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[8];
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
    systemRan[7] = &rtAlwaysEnabled;
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
  FSFB_FF_HIL_quick_dirty_M->Sizes.numBlocks = (138);/* Number of blocks */
  FSFB_FF_HIL_quick_dirty_M->Sizes.numBlockIO = (43);/* Number of block outputs */
  FSFB_FF_HIL_quick_dirty_M->Sizes.numBlockPrms = (353);/* Sum of parameter "widths" */
  return FSFB_FF_HIL_quick_dirty_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
