#include "Service.h"
#include <string>
#include "cpprest/http_client.h"


using std::string;
using std::to_string;

void Service::initRestOpHandlers() {
	_listener.support(methods::GET,std::bind(&Service::handleGet,this,std::placeholders::_1));
	//_listener.support(methods::PUT,std::bind(&Service::handlePut,this,std::placeholders::_1));
}



void Service::handleGet(http_request message) {
    vector<string> path = requestPath(message);

    if(path.empty()) {
        message.reply(status_codes::BadRequest);
    }
    else {




        if (path[0]=="T_pcob") {

        if (counter==0){
            //zapytanie o dzien tygodnia i czas symulacji
            web::http::client::http_client hour_time(U("https://closingtime.szyszki.de/api/details"));
            hour_time.request(methods::GET).then([=](http_response response2)
            {
                if(response2.status_code() == status_codes::OK)
                {
                    json::value jsonFromAPI_hour = response2.extract_json().get();
                    //std::cout << jsonFromAPI_hour<<std::endl;
                    dayOfWeek = jsonFromAPI_hour[U("dayOfWeek")].as_number().to_int32();
                    symSecs = jsonFromAPI_hour[U("symSec")].as_number().to_int32();

                    //std::cout << dayOfWeek<<symSecs<<std::endl;
                }
          });

            //Pytanie na server o godzine
            web::http::client::http_client hour(U("https://closingtime.szyszki.de/api/give_me_hour_my_lord"));
            hour.request(methods::GET).then([=](http_response response3)
            {
                if(response3.status_code() == status_codes::OK)
                {
                    json::value jsonFromAPI_hour = response3.extract_json().get();
                   // std::cout << jsonFromAPI_hour<<std::endl;

					symTimeHour = jsonFromAPI_hour[U("symTimeHour")].as_number().to_int32();
                    //std::cout << symTimeHour<<std::endl;
                }
          });




            //zapytanie do wymiennika o Tzco
			web::http::client::http_client wymiennik(U("https://selfcontrol.szyszki.de/controller/details"));
            wymiennik.request(methods::GET).then([=](http_response response)
            {
                if(response.status_code() == status_codes::OK)
                {
                    json::value jsonFromAPI = response.extract_json().get();
                    //std::cout << jsonFromAPI<<std::endl;


					Tzco = jsonFromAPI[U("actual_temp")].as_string();


                }
            });



            //zapytanie do dostawcy o temperature otoczeni
            web::http::client::http_client dostawca(U("https://ivegotthepower.szyszki.de/mpec/data"));
            dostawca.request(methods::GET).then([=](http_response response)
        {

                if(response.status_code() == status_codes::OK)
                {

                    json::value jsonFromAPI = response.extract_json().get();
                    //std::cout << jsonFromAPI<<std::endl;

					AirTemp = jsonFromAPI[U("AirTemp")].as_string();






                    std::cout<<symSecs<<std::endl;
					std::cout<<dayOfWeek<<std::endl;
                    std::cout<<symTimeHour<<std::endl;
                    std::cout<<Tzco<<std::endl;
                    std::cout<<AirTemp<<std::endl;

            // wyznaczenie temperatuty zadanej

					if (dayOfWeek!=0 and dayOfWeek!=6 and symTimeHour>=7 and symTimeHour<22){
					T_zadana = 20;

					}
					else{
						T_zadana = 15;
					}


					//int T_pcob = 12;

				// obliczenia

                    rtU.T_zCo=std::stod(Tzco);
                    rtU.T_otoczenia=std::stod(AirTemp);                  // '<Root>/T_otoczenia'
                    rtU.F_cob=std::stod(F_cob);
                    rtU.T_zadana=T_zadana;

                    this->step();

                    std::cout<<rtY.T_pco<<std::endl;
                    std::cout<<rtY.T_ref<<std::endl;
                    std::cout<<rtY.T_r<<std::endl;
                    std::cout<<rtY.Sterowanie<<std::endl;

                    double przeplyw = rtY.Sterowanie*40;
                    log_przeplyw = std::to_string(przeplyw);

                    log_Tpco = std::to_string(rtY.T_pco);
                    log_Tref = std::to_string(rtY.T_ref);
                    log_Tr = std::to_string(rtY.T_r*1.2);

                    string log_Sterowanie = std::to_string(rtY.Sterowanie);
                    log_timestamp = std::to_string(symSecs);
                //odesłanie Tpcob na zapytanie GET

                    web::json::value jsonTpcob;
                    jsonTpcob["T_pcob"] = json::value::string(log_Tpco);
                    jsonTpcob["T_ref"] = json::value::string(std::to_string(T_zadana));
                    jsonTpcob["T_pomieszczenia"] = json::value::string(log_Tr);
                    jsonTpcob["Sterowanie"] = json::value::string(log_przeplyw);
                    jsonTpcob["czas"] = json::value::string(log_timestamp);






                    message.reply(status_codes::OK,jsonTpcob);




                //wysłanie logów do bazy

                    web::json::value json_v ;
                    web::json::value json_return;
                    web::json::value json_return2;

					json_v["status"] = web::json::value::string("running");
					json_v["tag_name"] = web::json::value::string("Radek");
					json_v["water_intake_Fcob"]= web::json::value::string(log_przeplyw);
					json_v["return_water_temp_Tpcob"] = web::json::value::string(log_Tpco);
					json_v["radiator_temp_Th"] = web::json::value::string(log_Tpco);
					json_v["room_temp_Tr"] = web::json::value::string(log_Tr);
					json_v["timestamp"] = web::json::value::string(log_timestamp);
//https://jsonplaceholder.typicode.com/posts

//https://anoldlogcabinforsale.szyszki.de/building/log
					web::http::client::http_client Dominika(U("https://anoldlogcabinforsale.szyszki.de/building/log"));
					Dominika.request(web::http::methods::POST, U(""), json_v)
					.then([=](const web::http::http_response& response1) {
					return response1.extract_json();

					})
					.then([&json_return](const pplx::task<web::json::value>& task) {
					try {

						web::json::value json_return = task.get();
						std::cout << json_return<<std::endl;

						}
					catch (const web::http::http_exception& e) {
						std::cout << "error " << e.what() << std::endl;
					}
					})
					.wait();

					std::cout << json_return.serialize() << std::endl;


//https://layanotherlogonthefire.szyszki.de/building/log

                web::http::client::http_client Client2(U("https://layanotherlogonthefire.szyszki.de/building/log"));
					Client2.request(web::http::methods::POST, U("/"), json_v)
					.then([=](const web::http::http_response& response2) {
					return response2.extract_json();

					})
					.then([&json_return2](const pplx::task<web::json::value>& task) {
					try {

						web::json::value json_return2 = task.get();
						std::cout << json_return2<<std::endl;

						}
					catch (const web::http::http_exception& e) {
						std::cout << "error " << e.what() << std::endl;
					}
					})
					.wait();

					std::cout << json_return2.serialize() << std::endl;



                }

            }

            );
            counter=10;
        }

        else if (counter!=0){
            counter=counter-1;
            web::json::value jsonTpcob_last;
            jsonTpcob_last["T_pcob"] = json::value::string(log_Tpco);
            jsonTpcob_last["T_ref"] = json::value::string(std::to_string(T_zadana));
            jsonTpcob_last["T_pomieszczenia"] = json::value::string(log_Tr);
            jsonTpcob_last["Sterowanie"] = json::value::string(log_przeplyw);
            jsonTpcob_last["czas"] = json::value::string(log_timestamp);




           message.reply(status_codes::OK,jsonTpcob_last);

        }

        else {
            message.reply(status_codes::BadRequest);
        }
        }


    }
}

void Service::step()
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

