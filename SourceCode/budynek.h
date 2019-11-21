//
// File: symulacja_budynku.h
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
#ifndef RTW_HEADER_symulacja_budynku_h_
#define RTW_HEADER_symulacja_budynku_h_
#ifndef symulacja_budynku_COMMON_INCLUDES_
# define symulacja_budynku_COMMON_INCLUDES_
#endif                                 // symulacja_budynku_COMMON_INCLUDES_

#include "budynek_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Block signals and states (auto storage) for system '<Root>'
typedef struct {
  double DiscreteTimeIntegrator_DSTATE;// '<S1>/Discrete-Time Integrator'
  double Integrator_DSTATE;            // '<S3>/Integrator'
  double Filter_DSTATE;                // '<S3>/Filter'
  double DiscreteTimeIntegrator_DSTATE_n;// '<S2>/Discrete-Time Integrator'
} DW;

// External inputs (root inport signals with auto storage)
typedef struct {
  double T_zadana;                     // '<Root>/T_zadana'
  double T_zCo;                        // '<Root>/T_zCo'
  double T_otoczenia;                  // '<Root>/T_otoczenia'
  double F_cob;                        // '<Root>/F_cob'
} ExtU;

// External outputs (root outports fed by signals with auto storage)
typedef struct {
  double Sterowanie;                   // '<Root>/Sterowanie'
  double T_ref;                        // '<Root>/T_ref'
  double T_r;                          // '<Root>/T_r'
  double T_pco;                        // '<Root>/T_pco '
} ExtY;



#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

// Class declaration for model symulacja_budynku
class symulacja_budynkuModelClass {
  // public data and function members
 public:
  // External inputs
  ExtU rtU;
  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  symulacja_budynkuModelClass();

  // Destructor
  ~symulacja_budynkuModelClass();

  // private data and function members
 private:
  // Block signals and states
  DW rtDW;

};

//  '<Root>' : 'symulacja_budynku'
//  '<S1>'   : 'symulacja_budynku/Budynek'
//  '<S2>'   : 'symulacja_budynku/Kaloryfer'
//  '<S3>'   : 'symulacja_budynku/PID Controller'

#endif  


