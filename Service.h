#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED
#include "BasicController.h"
#include <vector>
#include "budynek_private.h"
using std::string;
using std::vector;

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


class Service : public BasicController {
    public:
    Service(const std::string& address,const std::string& port) : BasicController(address,port) {

    rtDW.DiscreteTimeIntegrator_DSTATE = rtCP_DiscreteTimeIntegrator_IC;
    }
    ~Service() {}
    void handleGet(http_request message);
    void handlePut(http_request message);
    void initRestOpHandlers() override;
    void step();
    DW rtDW;
    // External inputs
    ExtU rtU;
    // External outputs
    ExtY rtY;

    private:

    string Tzco = "77";
    string AirTemp;
    string F_cob = "12";

    int symTimeHour;


    int dayOfWeek;
    int symSecs;
    double T_zadana;










};


#endif // SERVICE_H_INCLUDED
