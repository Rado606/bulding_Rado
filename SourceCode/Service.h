#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED
#include "BasicController.h"
#include <vector>
#include <string>
using std::vector;

class Service : public BasicController {
    public:
    Service(const std::string& address,const std::string& port) : BasicController(address,port) {}
    ~Service() {}
    void handleGet(http_request message);
    void handlePut(http_request message);
	void handlePost(http_request message);
    void initRestOpHandlers() override;
    private:
	
	string Time;
	int DayOfWeek;
	int symTime;
	
	double AirTemp;
	double Tzco;
	
	
	double T_pcob;
	double T_r;
	double T_ref;
	string status;
	int samples;
	double F_cob;

};


#endif // SERVICE_H_INCLUDED
