/*
 * helicopter1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter1".
 *
 * Model version              : 11.11
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Wed Feb  4 14:28:16 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter1.h"
#include "helicopter1_private.h"

/* Block signals (default storage) */
B_helicopter1_T helicopter1_B;

/* Continuous states */
X_helicopter1_T helicopter1_X;

/* Block states (default storage) */
DW_helicopter1_T helicopter1_DW;

/* Real-time model */
static RT_MODEL_helicopter1_T helicopter1_M_;
RT_MODEL_helicopter1_T *const helicopter1_M = &helicopter1_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopter1_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter1_output(void)
{
  /* local block i/o variables */
  real_T rtb_Sum1_n[4];
  real_T rtb_Clock;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Gain1_idx_2;
  real_T rtb_Gain1_idx_3;
  real_T rtb_Sum;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    /* set solver stop time */
    if (!(helicopter1_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter1_M->solverInfo,
                            ((helicopter1_M->Timing.clockTickH0 + 1) *
        helicopter1_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter1_M->solverInfo,
                            ((helicopter1_M->Timing.clockTick0 + 1) *
        helicopter1_M->Timing.stepSize0 + helicopter1_M->Timing.clockTickH0 *
        helicopter1_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter1_M)) {
    helicopter1_M->Timing.t[0] = rtsiGetT(&helicopter1_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopter1_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter1/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(helicopter1_DW.HILReadEncoderTimebase_Task,
        1, &helicopter1_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter1_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter1_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter1_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *) helicopter1_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter1_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter1_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter1_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[180]) {
      currTimeIndex = 179;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter1_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Clock = pDataValues[currTimeIndex];
        } else {
          rtb_Clock = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Clock = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 181;
      }
    }
  }

  if (rtmIsMajorTimeStep(helicopter1_M)) {
    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter1_B.TravelCounttorad = helicopter1_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter1_P.TravelCounttorad_Gain;

    /* Gain: '<S13>/Gain' */
    helicopter1_B.Gain = helicopter1_P.Gain_Gain *
      helicopter1_B.TravelCounttorad;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter1_B.PitchCounttorad = helicopter1_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopter1_B.Gain_i = helicopter1_P.Gain_Gain_a *
      helicopter1_B.PitchCounttorad;

    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter1_B.ElevationCounttorad = helicopter1_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopter1_P.ElevationCounttorad_Gain;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     *  Gain: '<S8>/Gain'
     */
    helicopter1_B.Sum = helicopter1_P.Gain_Gain_lv *
      helicopter1_B.ElevationCounttorad +
      helicopter1_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S2>/Gain1' incorporates:
   *  Gain: '<S11>/Gain'
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  rtb_Gain1_idx_2 = helicopter1_P.Gain1_Gain * helicopter1_B.Gain_i;
  rtb_Gain1_idx_3 = (helicopter1_P.PitchTransferFcn_C *
                     helicopter1_X.PitchTransferFcn_CSTATE +
                     helicopter1_P.PitchTransferFcn_D *
                     helicopter1_B.PitchCounttorad) * helicopter1_P.Gain_Gain_ae
    * helicopter1_P.Gain1_Gain;

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *) helicopter1_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter1_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter1_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter1_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[180]) {
      currTimeIndex = 179;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter1_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Sum1_n[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 181;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Sum1_n[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 181;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 4; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Sum1_n[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 181;
          }
        }
      }
    }
  }

  /* Sum: '<S5>/Sum1' incorporates:
   *  Gain: '<S14>/Gain'
   *  Gain: '<S2>/Gain1'
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  rtb_Sum1_n[0] = helicopter1_P.Gain1_Gain * helicopter1_B.Gain - rtb_Sum1_n[0];
  rtb_Sum1_n[1] = (helicopter1_P.TravelTransferFcn_C *
                   helicopter1_X.TravelTransferFcn_CSTATE +
                   helicopter1_P.TravelTransferFcn_D *
                   helicopter1_B.TravelCounttorad) * helicopter1_P.Gain_Gain_l *
    helicopter1_P.Gain1_Gain - rtb_Sum1_n[1];
  rtb_Sum1_n[2] = rtb_Gain1_idx_2 - rtb_Sum1_n[2];
  rtb_Sum1_n[3] = rtb_Gain1_idx_3 - rtb_Sum1_n[3];

  /* Clock: '<S3>/Clock' incorporates:
   *  Gain: '<S5>/Multiply'
   *  Sum: '<S5>/Sum'
   *  Sum: '<S6>/Sum2'
   */
  rtb_Clock -= ((helicopter1_P.K[0] * rtb_Sum1_n[0] + helicopter1_P.K[1] *
                 rtb_Sum1_n[1]) + helicopter1_P.K[2] * rtb_Sum1_n[2]) +
    helicopter1_P.K[3] * rtb_Sum1_n[3];
  rtb_Clock -= rtb_Gain1_idx_2;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S6>/K_pd'
   *  Gain: '<S6>/K_pp'
   *  Sum: '<S6>/Sum3'
   */
  rtb_Gain1_idx_2 = (helicopter1_P.K_pp * rtb_Clock - helicopter1_P.K_pd *
                     rtb_Gain1_idx_3) + helicopter1_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter1_X.Integrator_CSTATE >= helicopter1_P.Integrator_UpperSat) {
    helicopter1_X.Integrator_CSTATE = helicopter1_P.Integrator_UpperSat;
  } else {
    if (helicopter1_X.Integrator_CSTATE <= helicopter1_P.Integrator_LowerSat) {
      helicopter1_X.Integrator_CSTATE = helicopter1_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/Constant'
   *  Gain: '<S2>/Gain1'
   */
  rtb_Sum = helicopter1_P.Constant_Value - helicopter1_P.Gain1_Gain *
    helicopter1_B.Sum;

  /* Clock: '<S3>/Clock' incorporates:
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S9>/Gain'
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  rtb_Clock = (helicopter1_P.ElevationTransferFcn_C *
               helicopter1_X.ElevationTransferFcn_CSTATE +
               helicopter1_P.ElevationTransferFcn_D *
               helicopter1_B.ElevationCounttorad) * helicopter1_P.Gain_Gain_n *
    helicopter1_P.Gain1_Gain * helicopter1_P.K_ed;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Gain1_idx_3 = ((helicopter1_P.K_ep * rtb_Sum +
                      helicopter1_X.Integrator_CSTATE) - rtb_Clock) +
    helicopter1_P.Vs_ff;

  /* Clock: '<S3>/Clock' */
  rtb_Clock = helicopter1_M->Timing.t[0];

  /* If: '<S3>/If' incorporates:
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S7>/In1'
   */
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    rtAction = (int8_T)!(rtb_Clock >= 2.0);
    helicopter1_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopter1_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    helicopter1_B.In1 = helicopter1_P.K_ei * rtb_Sum;

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Sum = (rtb_Gain1_idx_2 + rtb_Gain1_idx_3) * helicopter1_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Sum > helicopter1_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter1_B.FrontmotorSaturation =
      helicopter1_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Sum < helicopter1_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter1_B.FrontmotorSaturation =
      helicopter1_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter1_B.FrontmotorSaturation = rtb_Sum;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Sum = (rtb_Gain1_idx_3 - rtb_Gain1_idx_2) * helicopter1_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Sum > helicopter1_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter1_B.BackmotorSaturation =
      helicopter1_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Sum < helicopter1_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter1_B.BackmotorSaturation =
      helicopter1_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter1_B.BackmotorSaturation = rtb_Sum;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter1/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter1_DW.HILWriteAnalog_Buffer[0] =
        helicopter1_B.FrontmotorSaturation;
      helicopter1_DW.HILWriteAnalog_Buffer[1] =
        helicopter1_B.BackmotorSaturation;
      result = hil_write_analog(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILWriteAnalog_channels, 2,
        &helicopter1_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter1_update(void)
{
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter1_M->solverInfo);
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
  if (!(++helicopter1_M->Timing.clockTick0)) {
    ++helicopter1_M->Timing.clockTickH0;
  }

  helicopter1_M->Timing.t[0] = rtsiGetSolverStopTime(&helicopter1_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopter1_M->Timing.clockTick1)) {
      ++helicopter1_M->Timing.clockTickH1;
    }

    helicopter1_M->Timing.t[1] = helicopter1_M->Timing.clockTick1 *
      helicopter1_M->Timing.stepSize1 + helicopter1_M->Timing.clockTickH1 *
      helicopter1_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter1_derivatives(void)
{
  XDot_helicopter1_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopter1_T *) helicopter1_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter1_P.TravelTransferFcn_A *
    helicopter1_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter1_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter1_P.PitchTransferFcn_A *
    helicopter1_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter1_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter1_P.ElevationTransferFcn_A *
    helicopter1_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter1_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter1_X.Integrator_CSTATE <= helicopter1_P.Integrator_LowerSat);
  usat = (helicopter1_X.Integrator_CSTATE >= helicopter1_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter1_B.In1 > 0.0)) || (usat &&
       (helicopter1_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter1_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter1_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter1/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter1_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter1_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter1_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter1_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter1_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter1_M, _rt_error_message);
      return;
    }

    if ((helicopter1_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopter1_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter1_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopter1_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter1_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter1_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_AIChannels, 8U,
        &helicopter1_DW.HILInitialize_AIMinimums[0],
        &helicopter1_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopter1_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter1_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopter1_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter1_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter1_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_AOChannels, 8U,
        &helicopter1_DW.HILInitialize_AOMinimums[0],
        &helicopter1_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_AOStart && !is_switching) ||
        (helicopter1_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter1_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_AOChannels, 8U,
        &helicopter1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if (helicopter1_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter1_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter1_DW.HILInitialize_Card,
         helicopter1_P.HILInitialize_AOChannels, 8U,
         &helicopter1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopter1_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter1_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter1_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode *)
        &helicopter1_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_EIStart && !is_switching) ||
        (helicopter1_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter1_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter1_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_EIChannels, 8U,
        &helicopter1_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_POPStart && !is_switching) ||
        (helicopter1_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopter1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter1_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopter1_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopter1_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &helicopter1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopter1_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            helicopter1_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helicopter1_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopter1_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopter1_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helicopter1_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter1_DW.HILInitialize_Card,
          &helicopter1_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helicopter1_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter1_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter1_DW.HILInitialize_Card,
          &helicopter1_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter1_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter1_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopter1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter1_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &helicopter1_DW.HILInitialize_POAlignValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter1_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter1_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter1_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopter1_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter1_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter1_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helicopter1_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter1_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter1_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_POChannels, 8U,
        &helicopter1_DW.HILInitialize_POSortedFreqs[0],
        &helicopter1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_POStart && !is_switching) ||
        (helicopter1_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter1_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_POChannels, 8U,
        &helicopter1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if (helicopter1_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter1_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter1_DW.HILInitialize_Card,
         helicopter1_P.HILInitialize_POChannels, 8U,
         &helicopter1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter1/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(helicopter1_DW.HILInitialize_Card,
      helicopter1_P.HILReadEncoderTimebase_SamplesI,
      helicopter1_P.HILReadEncoderTimebase_Channels, 3,
      &helicopter1_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopter1_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopter1_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter1_M, _rt_error_message);
    }
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0, 37.25, 37.5, 37.75, 38.0, 38.25, 38.5, 38.75,
      39.0, 39.25, 39.5, 39.75, 40.0, 40.25, 40.5, 40.75, 41.0, 41.25, 41.5,
      41.75, 42.0, 42.25, 42.5, 42.75, 43.0, 43.25, 43.5, 43.75, 44.0, 44.25,
      44.5, 44.75, 45.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.52359877559948875, 0.52359877559908508, 0.52359877559923873,
      0.523598775598835, 0.523598775598694, 0.52359877559889212,
      0.52359877559896517, 0.52359877559911483, 0.52359877559650381,
      0.38309674437831021, 0.198828241250542, 0.06109842351382,
      -0.052197282420702984, -0.1454941515463033, -0.22017330369512306,
      -0.27747025100577211, -0.3189052589456487, -0.34622835741955915,
      -0.36130003919226206, -0.36598943466815209, -0.36210019023494189,
      -0.35132044985077793, -0.33519166358167507, -0.3150916017239464,
      -0.29222787926699118, -0.26763910251298856, -0.24220139596259826,
      -0.21663857613873888, -0.19153463867580051, -0.16734754009059155,
      -0.14442350459324071, -0.12301128359108782, -0.10327595188332528,
      -0.0853119483058527, -0.069155166249583622, -0.054793976064426264,
      -0.04217912088520176, -0.031232473074343514, -0.021854672852628987,
      -0.013931695895260443, -0.0073404144429500828, -0.0019532282552883196,
      0.0023581512854037312, 0.0057196774270499295, 0.00825261794067167,
      0.010071793973746801, 0.01128432690335146, 0.011988817145813346,
      0.012274884599720925, 0.01222300660021125, 0.011904595683218888,
      0.011382265894343546, 0.010710242667986702, 0.0099348773282594838,
      0.00909523293651504, 0.0082237134715380522, 0.00734671314060209,
      0.0064852669646072725, 0.0056556876551455693, 0.0048701772141765964,
      0.0041374046556443833, 0.0034630437970718519, 0.0028502672268730933,
      0.0023001943517287904, 0.0018122929014163791, 0.0013847344499989811,
      0.0010147054358725649, 0.00069867586140071047, 0.00043262835664437116,
      0.00021225062996932387, 3.309452781075084E-5, -0.00010929498908662794,
      -0.00021927765310925107, -0.00030103926158076, -0.00035853353003378885,
      -0.00039544152147319434, -0.00041514595180724978, -0.0004207178946499246,
      -0.00041491364005674658, -0.00040017969395156339, -0.00037866413197595872,
      -0.00035223273836193503, -0.00032248856336114518, -0.000290793718720761,
      -0.00025829239730434939, -0.00022593424825134711, -0.00019449736132493012,
      -0.00016461021159097644, -0.00013677198632211507, -0.00011137075760603299,
      -8.8698973677359128E-5, -6.8965717572311291E-5, -5.230513022136396E-5,
      -3.8780370574253986E-5, -2.8382767227164152E-5, -2.1027731433198582E-5,
      -1.6558704998281826E-5, -1.481625146015908E-5, -1.6041613928874376E-5, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter1_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter1_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter1_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0, 37.25, 37.5, 37.75, 38.0, 38.25, 38.5, 38.75,
      39.0, 39.25, 39.5, 39.75, 40.0, 40.25, 40.5, 40.75, 41.0, 41.25, 41.5,
      41.75, 42.0, 42.25, 42.5, 42.75, 43.0, 43.25, 43.5, 43.75, 44.0, 44.25,
      44.5, 44.75, 45.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1378421413625173, 3.1262155534579659, 3.1033093000298879,
      3.0666274151910358, 3.0144539223939288, 2.9456562771172319,
      2.8595077632930872, 2.7555515879645553, 2.6335051104895495,
      2.4942020151570858, 2.3399647596866804, 2.1740824099696532,
      2.0002819265848313, 1.8223363046127852, 1.6438033561537873,
      1.467865758716322, 1.2972450163193949, 1.1341677374455137,
      0.98036789417350967, 0.83711289663284516, 0.70524451094586427,
      0.58522807353382456, 0.47720529050686267, 0.38104729856611952,
      0.29640571026727219, 0.22276015237328797, 0.15946139248685892,
      0.10576958265645658, 0.0608874646686312, 0.023988607498671849,
      -0.00575909610763255, -0.029174343428808078, -0.04704735223532297,
      -0.060128381420318289, -0.069119405124364111, -0.0746685100845058,
      -0.077366604119974175, -0.077746049892797944, -0.076280869436752427,
      -0.07338819917723724, -0.069430710541207225, -0.064719746478817175,
      -0.059518958327773805, -0.054048259763233138, -0.048487944626289262,
      -0.042982842923689049, -0.03764641408954561, -0.032564698653232783,
      -0.027800068805317855, -0.023394735095735256, -0.019373980780058798,
      -0.015749107325526611, -0.012520084492035705, -0.0096779064179139031,
      -0.0072066614715516246, -0.0050853284803540049, -0.0032893155128756687,
      -0.0017917598527290729, -0.00056460933543718539, 0.00042049402079710941,
      0.0011915070299229186, 0.0017754343113888635, 0.0021979132987442404,
      0.00248291641640777, 0.0026525528216367602, 0.0027269535091455129,
      0.0027242250526430148, 0.002660458761576453, 0.0025497835229568331,
      0.002404452046184715, 0.0022349516096110485, 0.00205013170392098,
      0.0018573421675695929, 0.0016625765062976091, 0.0014706160788988609,
      0.001285171714683907, 0.0011090201067227308, 0.00094413300307789514,
      0.00079179780137495555, 0.00065272864668324752, 0.00052716754588717513,
      0.00041497535090619629, 0.00031571273570944226, 0.00022871150534708995,
      0.00015313673613502878, 8.8040361166005242E-5, 3.2406890384646215E-5,
      -1.4808005211214958E-5, -5.464530561793387E-5, -8.8116127057851024E-5,
      -0.00011618019779764883, -0.00013972870461442937, -0.00015957097412848162,
      -0.00017642455880888323, -0.00019090842258935413, -0.00020353904993401651,
      -0.0002147293485795667, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      -0.015002048909102519, -0.046506351618206244, -0.091625013712312173,
      -0.14672753935540864, -0.20869397118842556, -0.27519058110678812,
      -0.34459405529657949, -0.41582470131412747, -0.48818590990002381,
      -0.55721238132985351, -0.61694902188162337, -0.66352939886810969,
      -0.69520193353928683, -0.7117824878881831, -0.71413179383599268,
      -0.70375038974986137, -0.68248296958770771, -0.65230911549552506,
      -0.61519937308801587, -0.57301999016265825, -0.5274735427479238,
      -0.4800657496481589, -0.43209113210784733, -0.38463196776297265,
      -0.33856635319538941, -0.29458223157593683, -0.25319503954571615,
      -0.21476723932160938, -0.17952847195130153, -0.14759542867983741,
      -0.1189908144252176, -0.093660989284702109, -0.071492035226059569,
      -0.052324116739981281, -0.03596409481618329, -0.022196419840566785,
      -0.010792376141873498, -0.0015177830912950956, 0.0058607218241821133,
      0.011570681038060684, 0.015829954544120076, 0.01884385624956017,
      0.020803152604173505, 0.021882794258162676, 0.022241260547775477,
      0.022020406810400874, 0.021345715336573753, 0.020326861745251307,
      0.019058519391659725, 0.017621334838330387, 0.016083017262705831,
      0.014499493818128753, 0.012916091333963632, 0.011368712296487206,
      0.0098849797854491158, 0.0084853319647904754, 0.0071840518699133457,
      0.0059902226405863833, 0.00490860206916755, 0.0039404134249371794,
      0.0030840520365032365, 0.0023357091258637804, 0.0016899159494215079,
      0.0011400124706541172, 0.00067854562091596146, 0.0002976027500350098,
      -1.0913826009993601E-5, -0.00025506516426624613, -0.00044270095447848022,
      -0.00058132590708847285, -0.00067800174629466432, -0.00073927962276027512,
      -0.00077115814540554761, -0.00077906264508793475, -0.00076784170959499334,
      -0.00074177745685981625, -0.00070460643184470408, -0.0006595484145793429,
      -0.00060934080681175834, -0.0005562766187668318, -0.00050224440318428988,
      -0.00044876877992391522, -0.00039705046078701616, -0.0003480049214494093,
      -0.00030229907684824474, -0.0002603854998760941, -0.00022253388312543611,
      -0.00018885958238344471, -0.00015934920162687563, -0.00013388328575966859,
      -0.00011225628295919121, -9.4194027267122167E-5, -7.936907805620899E-5,
      -6.7414338721606456E-5, -5.7935455121883607E-5, -5.0522509378649492E-5,
      -4.4761194582200789E-5, -4.0241652060893686E-5, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.10602875205910545, 0.22266037932361016, 0.31888147181699056,
      0.38944360631206454, 0.43795507377735365, 0.46997264230443114,
      0.49051724877601222, 0.50343100141535191, 0.5114213858604354,
      0.48785273725494271, 0.42219576061089004, 0.3292123144139073,
      0.22384937858031151, 0.11718502564000932, 0.016603997185203556,
      -0.0733717991810478, -0.15031000318417048, -0.21325727662778127,
      -0.26227748626378089, -0.29810776923055593, -0.32190489508139353,
      -0.33506017549207223, -0.33906627415444712, -0.33542324783263916,
      -0.32557417023574853, -0.3108629730488302, -0.29250886653982544,
      -0.2715930155146315, -0.24905414926964703, -0.2256905538717805,
      -0.20216648878502158, -0.17902153004450538, -0.15668170044786028,
      -0.13547152718611855, -0.11562638668479336, -0.097304668532518179,
      -0.0805994253928734, -0.065549281498628542, -0.05214845471980456,
      -0.040355810957240168, -0.030102918424920688, -0.021301106174543616,
      -0.0138475583331652, -0.0076304948697046848, -0.0025335028279066529,
      0.0015609098670721355, 0.0047684616571497251, 0.007200868060102672,
      0.0089641593462684854, 0.010157471529257056, 0.010872241105788438,
      0.011191738922371575, 0.011190884020375047, 0.010936284057367684,
      0.010486454716585381, 0.0098921762388766155, 0.0091969507219691327,
      0.0084375290422388227, 0.0076444811032340132, 0.0068427875641509095,
      0.006052435229605746, 0.0052890018833177121, 0.0045642195281355713,
      0.0038865077674706816, 0.0032614714494935138, 0.0026923587209077837,
      0.0021804773302909197, 0.0017255684121790793, 0.0013261381032044772,
      0.00097974822140944884, 0.00068326790921280356, 0.00043308862786761715,
      0.0002253052233628372, 5.5865985299052845E-5, -7.9305286070141534E-5,
      -0.00018421218332842493, -0.00026271060786597911, -0.00031845285686238345,
      -0.00035484819578057714, -0.00037503741418298819, -0.00038187906310271913,
      -0.00037794528114099, -0.00036552532674716254, -0.0003466351399177281,
      -0.00032303145302259306, -0.00029622915377069958, -0.00026752077027669685,
      -0.00023799709613581133, -0.00020856809997105152, -0.00017998336680224991,
      -0.00015285139541088011, -0.000127657124302738, -0.00010477707849110285,
      -8.44915312798733E-5, -6.6993128527759183E-5, -5.2391868783696616E-5,
      -4.0718772044590068E-5, -3.1942399862705528E-5, -2.6067638126070491E-5,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4241150082355859, 0.4665265090588176,
      0.38488436997355907, 0.28224853798029564, 0.19404586986115635,
      0.12807027410830987, 0.082178425886127879, 0.051655010557035079,
      0.0319615377800157, -0.094274594422269556, -0.262627906576483,
      -0.37193378478817263, -0.42145174333459462, -0.42665741176138994,
      -0.40232411381937505, -0.35990318546513056, -0.30775281601259169,
      -0.251789093774522, -0.19608083854405736, -0.14332113186714152,
      -0.095188503403376271, -0.052621121642727288, -0.01602439464950042,
      0.014572105287240868, 0.03939631038757966, 0.058844788747697142,
      0.073416426036048407, 0.08366340410080951, 0.090155464979974773,
      0.093454381591505459, 0.094096260347076577, 0.092579834962106256,
      0.089359318386622352, 0.084840693047008364, 0.079380562005341548,
      0.073286872609140533, 0.066820972558617686, 0.060200575577016156,
      0.053603307115330935, 0.047170575050290806, 0.04101157012930904,
      0.0352072490015379, 0.029814191365540744, 0.024868253853867092,
      0.020387968167215029, 0.016377650779935853, 0.012830207160329579,
      0.0097296256118286576, 0.0070531651446792566, 0.0047732487319681431,
      0.0028590783061375334, 0.0012779912663433682, -3.4196079767506376E-6,
      -0.0010183998520212844, -0.0017993173631227065, -0.0023771139108292464,
      -0.0027809020676252709, -0.0030376867189174151, -0.0031721917560163463,
      -0.0032067741563302989, -0.00316140933817969, -0.0030537333851518278,
      -0.0028991294207290209, -0.0027108470426609938, -0.0025001452719103814,
      -0.0022764509143453869, -0.00204752556247048, -0.0018196356724513036,
      -0.0015977212359030955, -0.0013855595271850573, -0.0011859212487930143,
      -0.0010007171253874634, -0.00083113361802661606, -0.00067775695226370957,
      -0.00054068508548626157, -0.0004196275890435752, -0.00031399369816173468,
      -0.00022296899599785763, -0.00014558135568645242, -8.075687362402E-5,
      -2.7366595694703338E-5, 1.5735127830578504E-5, 4.9679817557792376E-5,
      7.5560747299339409E-5, 9.4414747560945609E-5, 0.00010720919698739726,
      0.00011483353395461395, 0.00011809469654121553, 0.00011771598463704672,
      0.00011433893265242057, 0.00010852788554262107, 0.00010077708441037087,
      9.1520183225113512E-5, 8.1142188824276083E-5, 6.9993610989439834E-5,
      5.8405038960198695E-5, 4.6692386942911319E-5, 3.5105488716428712E-5,
      2.349904693467266E-5, 2.8223249035590131E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0 } ;

    helicopter1_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter1_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter1_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S3>/If' */
  helicopter1_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter1_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter1_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter1_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter1_X.Integrator_CSTATE = helicopter1_P.Integrator_IC;
}

/* Model terminate function */
void helicopter1_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter1/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter1_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter1_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter1_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopter1_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter1_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopter1_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopter1_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter1_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter1_DW.HILInitialize_Card
                         , helicopter1_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopter1_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter1_DW.HILInitialize_AOVoltages[0]
                         , &helicopter1_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter1_DW.HILInitialize_Card,
            helicopter1_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopter1_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter1_DW.HILInitialize_Card,
            helicopter1_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopter1_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter1_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter1_DW.HILInitialize_Card);
    hil_close(helicopter1_DW.HILInitialize_Card);
    helicopter1_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopter1_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter1_update();
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
  helicopter1_initialize();
}

void MdlTerminate(void)
{
  helicopter1_terminate();
}

/* Registration function */
RT_MODEL_helicopter1_T *helicopter1(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter1_P.Integrator_UpperSat = rtInf;
  helicopter1_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter1_M, 0,
                sizeof(RT_MODEL_helicopter1_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter1_M->solverInfo,
                          &helicopter1_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter1_M->solverInfo, &rtmGetTPtr(helicopter1_M));
    rtsiSetStepSizePtr(&helicopter1_M->solverInfo,
                       &helicopter1_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter1_M->solverInfo, &helicopter1_M->derivs);
    rtsiSetContStatesPtr(&helicopter1_M->solverInfo, (real_T **)
                         &helicopter1_M->contStates);
    rtsiSetNumContStatesPtr(&helicopter1_M->solverInfo,
      &helicopter1_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter1_M->solverInfo,
      &helicopter1_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter1_M->solverInfo,
      &helicopter1_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter1_M->solverInfo,
      &helicopter1_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter1_M->solverInfo, (&rtmGetErrorStatus
      (helicopter1_M)));
    rtsiSetRTModelPtr(&helicopter1_M->solverInfo, helicopter1_M);
  }

  rtsiSetSimTimeStep(&helicopter1_M->solverInfo, MAJOR_TIME_STEP);
  helicopter1_M->intgData.f[0] = helicopter1_M->odeF[0];
  helicopter1_M->contStates = ((real_T *) &helicopter1_X);
  rtsiSetSolverData(&helicopter1_M->solverInfo, (void *)&helicopter1_M->intgData);
  rtsiSetSolverName(&helicopter1_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter1_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter1_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter1_M->Timing.sampleTimes = (&helicopter1_M->
      Timing.sampleTimesArray[0]);
    helicopter1_M->Timing.offsetTimes = (&helicopter1_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter1_M->Timing.sampleTimes[0] = (0.0);
    helicopter1_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter1_M->Timing.offsetTimes[0] = (0.0);
    helicopter1_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter1_M, &helicopter1_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter1_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter1_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter1_M, -1);
  helicopter1_M->Timing.stepSize0 = 0.002;
  helicopter1_M->Timing.stepSize1 = 0.002;
  helicopter1_M->solverInfoPtr = (&helicopter1_M->solverInfo);
  helicopter1_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter1_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter1_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter1_M->blockIO = ((void *) &helicopter1_B);

  {
    helicopter1_B.TravelCounttorad = 0.0;
    helicopter1_B.Gain = 0.0;
    helicopter1_B.PitchCounttorad = 0.0;
    helicopter1_B.Gain_i = 0.0;
    helicopter1_B.ElevationCounttorad = 0.0;
    helicopter1_B.Sum = 0.0;
    helicopter1_B.FrontmotorSaturation = 0.0;
    helicopter1_B.BackmotorSaturation = 0.0;
    helicopter1_B.In1 = 0.0;
  }

  /* parameters */
  helicopter1_M->defaultParam = ((real_T *)&helicopter1_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter1_X;
    helicopter1_M->contStates = (x);
    (void) memset((void *)&helicopter1_X, 0,
                  sizeof(X_helicopter1_T));
  }

  /* states (dwork) */
  helicopter1_M->dwork = ((void *) &helicopter1_DW);
  (void) memset((void *)&helicopter1_DW, 0,
                sizeof(DW_helicopter1_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter1_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter1_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* Initialize Sizes */
  helicopter1_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter1_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopter1_M->Sizes.numY = (0);     /* Number of model outputs */
  helicopter1_M->Sizes.numU = (0);     /* Number of model inputs */
  helicopter1_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter1_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter1_M->Sizes.numBlocks = (50);/* Number of blocks */
  helicopter1_M->Sizes.numBlockIO = (9);/* Number of block outputs */
  helicopter1_M->Sizes.numBlockPrms = (147);/* Sum of parameter "widths" */
  return helicopter1_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
