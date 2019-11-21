
//
// File: symulacja_budynku.cpp
//
// Code generated for Simulink model 'symulacja_budynku'.
//
// Model version                  : 1.10
// Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
// C/C++ source code generated on : Wed Nov 13 02:07:18 2019
//
// Target selection: ert.tlc

// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objective: Traceability
// Validation result: All passed
//
#include "budynek.h"
#include "budynek_private.h"

// Model step function
void symulacja_budynkuModelClass::step()
{
  double rtb_T_Tr;							//
  double rtb_Gain3;							//				double to double									
  double rtb_Gain1;							//
  double rtb_T_PCO;							//
  double rtb_IntegralGain;					//
  double rtb_Integrator;					//
  double rtb_Filter;						//
  double rtb_Gain4;							//

  // DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
  rtb_T_Tr = rtDW.DiscreteTimeIntegrator_DSTATE;

  // Sum: '<Root>/Sum1' incorporates:
  //   Inport: '<Root>/T_zadana'

  rtb_Gain3 = rtU.T_zadana - rtb_T_Tr;

  // Gain: '<S3>/Proportional Gain'
  rtb_Gain1 = rtCP_ProportionalGain_Gain * rtb_Gain3;

  // Gain: '<S3>/Derivative Gain'
  rtb_T_PCO = rtCP_DerivativeGain_Gain * rtb_Gain3;

  // Gain: '<S3>/Integral Gain'
  rtb_IntegralGain = rtCP_IntegralGain_Gain * rtb_Gain3;

  // Outport: '<Root>/T_r'
  rtY.T_r = rtb_T_Tr;

  // Sum: '<S1>/Sum1' incorporates:
  //   Inport: '<Root>/T_otoczenia'

  rtb_Gain3 = rtb_T_Tr - rtU.T_otoczenia;

  // Gain: '<S1>/Gain1'
  rtb_Gain3 *= rtCP_Gain1_Gain;

  // Gain: '<S1>/Gain'
  rtb_Gain3 *= rtCP_pooled2;

  // DiscreteIntegrator: '<S3>/Integrator'
  rtb_Integrator = rtDW.Integrator_DSTATE;

  // DiscreteIntegrator: '<S3>/Filter'
  rtb_Filter = rtDW.Filter_DSTATE;

  // Sum: '<S3>/SumD'
  rtb_T_PCO -= rtb_Filter;

  // Gain: '<S3>/Filter Coefficient'
  rtb_Filter = rtCP_FilterCoefficient_Gain * rtb_T_PCO;

  // Sum: '<S3>/Sum'
  rtb_Gain1 = rtb_Gain1 + rtb_Integrator + rtb_Filter;

  // Saturate: '<S3>/Saturate'
  rtb_T_PCO = T_PCO_initial_value;
  
  rtb_Integrator = rtCP_pooled1;
  if (rtb_Gain1 > rtb_Integrator) {
    rtb_Gain1 = rtb_Integrator;
  } else {
    if (rtb_Gain1 < rtb_T_PCO) {
      rtb_Gain1 = rtb_T_PCO;
    }
  }

  // End of Saturate: '<S3>/Saturate'

  // Outport: '<Root>/Sterowanie'
  rtY.Sterowanie = rtb_Gain1;

  // Product: '<Root>/Product' incorporates:
  //   Inport: '<Root>/F_cob'

  rtb_Gain1 *= rtU.F_cob;

  // Gain: '<S2>/Gain1'
  rtb_Gain1 *= rtCP_Gain1_Gain_h;

  // Outport: '<Root>/T_ref' incorporates:
  //   Inport: '<Root>/T_zadana'

  rtY.T_ref = rtU.T_zadana;

  // DiscreteIntegrator: '<S2>/Discrete-Time Integrator'
  rtb_T_PCO = rtDW.DiscreteTimeIntegrator_DSTATE_n;

  // Outport: '<Root>/T_pco '
  rtY.T_pco = rtb_T_PCO;

  // Sum: '<S1>/Sum2'
  rtb_Gain4 = rtb_T_PCO - rtb_T_Tr;

  // Gain: '<S1>/Gain2'
  rtb_Gain4 *= rtCP_pooled4;

  // Gain: '<S1>/Gain3'
  rtb_Gain4 *= rtCP_pooled2;

  // Sum: '<S1>/Sum'
  rtb_Integrator = rtb_Gain4 - rtb_Gain3;

  // Sum: '<S2>/Sum2'
  rtb_Gain4 = rtb_T_PCO - rtb_T_Tr;

  // Gain: '<S2>/Gain2'
  rtb_Gain4 *= rtCP_pooled4;

  // Gain: '<S2>/Gain4'
  rtb_Gain4 *= rtCP_pooled5;

  // Sum: '<S2>/Sum1' incorporates:
  //   Inport: '<Root>/T_zCo'

  rtb_Gain3 = rtU.T_zCo - rtb_T_PCO;

  // Product: '<S2>/Product'
  rtb_Gain3 *= rtb_Gain1;

  // Gain: '<S2>/Gain3'
  rtb_Gain3 *= rtCP_pooled5;

  // Sum: '<S2>/Sum'
  rtb_T_Tr = rtb_Gain3 - rtb_Gain4;

  // Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
  rtDW.DiscreteTimeIntegrator_DSTATE += rtCP_pooled1 * rtb_Integrator;

  // Update for DiscreteIntegrator: '<S3>/Integrator'
  rtDW.Integrator_DSTATE += rtCP_pooled1 * rtb_IntegralGain;

  // Update for DiscreteIntegrator: '<S3>/Filter'
  rtDW.Filter_DSTATE += rtCP_pooled1 * rtb_Filter;

  // Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator'
  rtDW.DiscreteTimeIntegrator_DSTATE_n += rtCP_pooled1 * rtb_T_Tr;
}

// Model initialize function
void symulacja_budynkuModelClass::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' 
  rtDW.DiscreteTimeIntegrator_DSTATE = rtCP_DiscreteTimeIntegrator_IC;
}

// Model terminate function
void symulacja_budynkuModelClass::terminate()
{
  // (no terminate code required)
}

// Constructor
symulacja_budynkuModelClass::symulacja_budynkuModelClass()
{
}

// Destructor
symulacja_budynkuModelClass::~symulacja_budynkuModelClass()
{
  // Currently there is no destructor body generated.
}



//
// File trailer for generated code.
//
// [EOF]
//
