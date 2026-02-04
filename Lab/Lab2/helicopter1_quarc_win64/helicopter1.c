/*
 * helicopter1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter1".
 *
 * Model version              : 11.5
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Wed Feb  4 13:04:36 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter1.h"
#include "helicopter1_private.h"
#include "helicopter1_dt.h"

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
  real_T rtb_Clock;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Backgain;
  real_T rtb_Clock_tmp;
  real_T rtb_Derivative;
  real_T rtb_Frontgain;
  real_T *lastU;
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

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopter1_DW.IfActionSubsystem_SubsysRanBC);
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
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
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
        pDataValues += 141;
      }
    }
  }

  if (rtmIsMajorTimeStep(helicopter1_M)) {
    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter1_B.TravelCounttorad = helicopter1_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter1_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    helicopter1_B.Gain = helicopter1_P.Gain_Gain *
      helicopter1_B.TravelCounttorad;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter1_B.PitchCounttorad = helicopter1_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    helicopter1_B.Gain_i = helicopter1_P.Gain_Gain_a *
      helicopter1_B.PitchCounttorad;
  }

  /* Gain: '<S13>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopter1_B.Gain_d = (helicopter1_P.TravelTransferFcn_C *
    helicopter1_X.TravelTransferFcn_CSTATE + helicopter1_P.TravelTransferFcn_D *
    helicopter1_B.TravelCounttorad) * helicopter1_P.Gain_Gain_l;

  /* Gain: '<S10>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter1_B.Gain_b = (helicopter1_P.PitchTransferFcn_C *
    helicopter1_X.PitchTransferFcn_CSTATE + helicopter1_P.PitchTransferFcn_D *
    helicopter1_B.PitchCounttorad) * helicopter1_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter1_B.ElevationCounttorad = helicopter1_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopter1_P.ElevationCounttorad_Gain;

    /* Gain: '<S7>/Gain' */
    helicopter1_B.Gain_e = helicopter1_P.Gain_Gain_lv *
      helicopter1_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter1_B.Sum = helicopter1_B.Gain_e +
      helicopter1_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter1_B.Gain_dg = (helicopter1_P.ElevationTransferFcn_C *
    helicopter1_X.ElevationTransferFcn_CSTATE +
    helicopter1_P.ElevationTransferFcn_D * helicopter1_B.ElevationCounttorad) *
    helicopter1_P.Gain_Gain_n;

  /* Clock: '<S3>/Clock' incorporates:
   *  Gain: '<S2>/Gain1'
   *  Sum: '<S5>/Sum2'
   */
  rtb_Clock -= helicopter1_P.Gain1_Gain * helicopter1_B.Gain_i;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Frontgain = (helicopter1_P.K_pp * rtb_Clock - helicopter1_P.Gain1_Gain *
                   helicopter1_B.Gain_b * helicopter1_P.K_pd) +
    helicopter1_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter1_X.Integrator_CSTATE >= helicopter1_P.Integrator_UpperSat) {
    helicopter1_X.Integrator_CSTATE = helicopter1_P.Integrator_UpperSat;
  } else {
    if (helicopter1_X.Integrator_CSTATE <= helicopter1_P.Integrator_LowerSat) {
      helicopter1_X.Integrator_CSTATE = helicopter1_P.Integrator_LowerSat;
    }
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  Integrator: '<S3>/Integrator'
   */
  rtb_Clock = helicopter1_X.Integrator_CSTATE;

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/Constant'
   *  Gain: '<S2>/Gain1'
   */
  rtb_Derivative = helicopter1_P.Constant_Value - helicopter1_P.Gain1_Gain *
    helicopter1_B.Sum;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Backgain = ((helicopter1_P.K_ep * rtb_Derivative + rtb_Clock) -
                  helicopter1_P.Gain1_Gain * helicopter1_B.Gain_dg *
                  helicopter1_P.K_ed) + helicopter1_P.Vs_ff;

  /* Clock: '<S3>/Clock' incorporates:
   *  Derivative: '<S4>/Derivative'
   */
  rtb_Clock_tmp = helicopter1_M->Timing.t[0];

  /* Clock: '<S3>/Clock' */
  rtb_Clock = rtb_Clock_tmp;

  /* If: '<S3>/If' incorporates:
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S6>/In1'
   */
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    rtAction = (int8_T)!(rtb_Clock >= 2.0);
    helicopter1_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopter1_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    helicopter1_B.In1 = helicopter1_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopter1_M)) {
      srUpdateBC(helicopter1_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopter1_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter1_DW.TimeStampA >= rtb_Clock_tmp) && (helicopter1_DW.TimeStampB
       >= rtb_Clock_tmp)) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Derivative = helicopter1_DW.TimeStampA;
    lastU = &helicopter1_DW.LastUAtTimeA;
    if (helicopter1_DW.TimeStampA < helicopter1_DW.TimeStampB) {
      if (helicopter1_DW.TimeStampB < rtb_Clock_tmp) {
        rtb_Derivative = helicopter1_DW.TimeStampB;
        lastU = &helicopter1_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter1_DW.TimeStampA >= rtb_Clock_tmp) {
        rtb_Derivative = helicopter1_DW.TimeStampB;
        lastU = &helicopter1_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter1_B.PitchCounttorad - *lastU) / (rtb_Clock_tmp -
      rtb_Derivative);
  }

  /* Gain: '<S11>/Gain' */
  helicopter1_B.Gain_l = helicopter1_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter1_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Derivative = (rtb_Backgain - rtb_Frontgain) * helicopter1_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Derivative > helicopter1_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter1_B.BackmotorSaturation =
      helicopter1_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter1_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter1_B.BackmotorSaturation =
      helicopter1_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter1_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter1_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (rtb_Frontgain + rtb_Backgain) * helicopter1_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > helicopter1_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter1_B.FrontmotorSaturation =
      helicopter1_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter1_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter1_B.FrontmotorSaturation =
      helicopter1_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter1_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
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
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter1_DW.TimeStampA == (rtInf)) {
    helicopter1_DW.TimeStampA = helicopter1_M->Timing.t[0];
    lastU = &helicopter1_DW.LastUAtTimeA;
  } else if (helicopter1_DW.TimeStampB == (rtInf)) {
    helicopter1_DW.TimeStampB = helicopter1_M->Timing.t[0];
    lastU = &helicopter1_DW.LastUAtTimeB;
  } else if (helicopter1_DW.TimeStampA < helicopter1_DW.TimeStampB) {
    helicopter1_DW.TimeStampA = helicopter1_M->Timing.t[0];
    lastU = &helicopter1_DW.LastUAtTimeA;
  } else {
    helicopter1_DW.TimeStampB = helicopter1_M->Timing.t[0];
    lastU = &helicopter1_DW.LastUAtTimeB;
  }

  *lastU = helicopter1_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
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
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559948875,
      0.52359877559908508, 0.52359877559923873, 0.523598775598835,
      0.523598775598694, 0.52359877559889212, 0.52359877559896517,
      0.52359877559911483, 0.52359877559650381, 0.38309674437831021,
      0.198828241250542, 0.06109842351382, -0.052197282420702984,
      -0.1454941515463033, -0.22017330369512306, -0.27747025100577211,
      -0.3189052589456487, -0.34622835741955915, -0.36130003919226206,
      -0.36598943466815209, -0.36210019023494189, -0.35132044985077793,
      -0.33519166358167507, -0.3150916017239464, -0.29222787926699118,
      -0.26763910251298856, -0.24220139596259826, -0.21663857613873888,
      -0.19153463867580051, -0.16734754009059155, -0.14442350459324071,
      -0.12301128359108782, -0.10327595188332528, -0.0853119483058527,
      -0.069155166249583622, -0.054793976064426264, -0.04217912088520176,
      -0.031232473074343514, -0.021854672852628987, -0.013931695895260443,
      -0.0073404144429500828, -0.0019532282552883196, 0.0023581512854037312,
      0.0057196774270499295, 0.00825261794067167, 0.010071793973746801,
      0.01128432690335146, 0.011988817145813346, 0.012274884599720925,
      0.01222300660021125, 0.011904595683218888, 0.011382265894343546,
      0.010710242667986702, 0.0099348773282594838, 0.00909523293651504,
      0.0082237134715380522, 0.00734671314060209, 0.0064852669646072725,
      0.0056556876551455693, 0.0048701772141765964, 0.0041374046556443833,
      0.0034630437970718519, 0.0028502672268730933, 0.0023001943517287904,
      0.0018122929014163791, 0.0013847344499989811, 0.0010147054358725649,
      0.00069867586140071047, 0.00043262835664437116, 0.00021225062996932387,
      3.309452781075084E-5, -0.00010929498908662794, -0.00021927765310925107,
      -0.00030103926158076, -0.00035853353003378885, -0.00039544152147319434,
      -0.00041514595180724978, -0.0004207178946499246, -0.00041491364005674658,
      -0.00040017969395156339, -0.00037866413197595872, -0.00035223273836193503,
      -0.00032248856336114518, -0.000290793718720761, -0.00025829239730434939,
      -0.00022593424825134711, -0.00019449736132493012, -0.00016461021159097644,
      -0.00013677198632211507, -0.00011137075760603299, -8.8698973677359128E-5,
      -6.8965717572311291E-5, -5.230513022136396E-5, -3.8780370574253986E-5,
      -2.8382767227164152E-5, -2.1027731433198582E-5, -1.6558704998281826E-5,
      -1.481625146015908E-5, -1.6041613928874376E-5, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0 } ;

    helicopter1_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter1_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter1_DW.FromWorkspace_IWORK.PrevIndex = 0;
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

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter1_DW.TimeStampA = (rtInf);
  helicopter1_DW.TimeStampB = (rtInf);
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

  /* External mode info */
  helicopter1_M->Sizes.checksums[0] = (3894756216U);
  helicopter1_M->Sizes.checksums[1] = (2251520845U);
  helicopter1_M->Sizes.checksums[2] = (2772437321U);
  helicopter1_M->Sizes.checksums[3] = (2303639630U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopter1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&helicopter1_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopter1_M->extModeInfo,
      &helicopter1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter1_M->extModeInfo,
                        helicopter1_M->Sizes.checksums);
    rteiSetTPtr(helicopter1_M->extModeInfo, rtmGetTPtr(helicopter1_M));
  }

  helicopter1_M->solverInfoPtr = (&helicopter1_M->solverInfo);
  helicopter1_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter1_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter1_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter1_M->blockIO = ((void *) &helicopter1_B);

  {
    helicopter1_B.TravelCounttorad = 0.0;
    helicopter1_B.Gain = 0.0;
    helicopter1_B.Gain_d = 0.0;
    helicopter1_B.PitchCounttorad = 0.0;
    helicopter1_B.Gain_i = 0.0;
    helicopter1_B.Gain_b = 0.0;
    helicopter1_B.ElevationCounttorad = 0.0;
    helicopter1_B.Gain_e = 0.0;
    helicopter1_B.Sum = 0.0;
    helicopter1_B.Gain_dg = 0.0;
    helicopter1_B.Gain_l = 0.0;
    helicopter1_B.BackmotorSaturation = 0.0;
    helicopter1_B.FrontmotorSaturation = 0.0;
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

  helicopter1_DW.TimeStampA = 0.0;
  helicopter1_DW.LastUAtTimeA = 0.0;
  helicopter1_DW.TimeStampB = 0.0;
  helicopter1_DW.LastUAtTimeB = 0.0;
  helicopter1_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter1_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter1_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter1_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter1_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopter1_M->Sizes.numY = (0);     /* Number of model outputs */
  helicopter1_M->Sizes.numU = (0);     /* Number of model inputs */
  helicopter1_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter1_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter1_M->Sizes.numBlocks = (57);/* Number of blocks */
  helicopter1_M->Sizes.numBlockIO = (14);/* Number of block outputs */
  helicopter1_M->Sizes.numBlockPrms = (144);/* Sum of parameter "widths" */
  return helicopter1_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
