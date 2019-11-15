#include "Service.h"
#include <string>
#include "BasicController.h"
using std::string;
void Service::initRestOpHandlers() {
	_listener.support(methods::GET,std::bind(&Service::handleGet,this,std::placeholders::_1));
	_listener.support(methods::PUT,std::bind(&Service::handlePut,this,std::placeholders::_1));
}


void Service::handleGet(http_request message) {
    vector<string> path = requestPath(message);

    if(path.empty()) {
        message.reply(status_codes::BadRequest);
    }
    else {
        if(path[0]=="T_pcob") {
            float Tpcob = 15.20;

            json::value number;
            number["Tpcob"] = json::value::number(Tpcob);
            message.reply(status_codes::OK,number);

            // gety obliczenua

        web::json::value json_v ;
        json_v["status"] = web::json::value::string("running");
        json_v["tag_name"] = web::json::value::string("Radek");
        json_v["water_intake_Fcob"] = web::json::value::string("500");
        json_v["return_water_temp_Tpcob"] = web::json::value::string("30");
        json_v["room_temp_Tr"] = web::json::value::string("20");
        json_v["timestamp"] = web::json::value::string("00:01:53");


        web::http::client::http_client client("https://anoldlogcabinforsale.szyszki.de/building/log");
        client.request(web::http::methods::POST, U("/"), json_v)
        .then([](const web::http::http_response& response) {
            return response.extract_json();
        })
        .then([&json_return](const pplx::task<web::json::value>& task) {
            try {
                json_return = task.get();
            }
            catch (const web::http::http_exception& e) {
                std::cout << "error " << e.what() << std::endl;
            }
        })
        .wait();

        std::cout << json_return.serialize() << std::endl;
        }


        if (path[0]=="T_r") {
            float Tr = 10;

            json::value number;
            number["Tr"] = json::value::number(Tr);
            message.reply(status_codes::OK,number);
        }
        if (path[0]=="T_ref") {
            float Tref = 25;

            json::value number;
            number["Tref"] = json::value::number(Tref);
            message.reply(status_codes::OK,number);
        }

        else {
            message.reply(status_codes::BadRequest);
        }
    }
}
void Service::handlePut(http_request message) {
    message.extract_json().then([=](pplx::task<json::value> task)
    {


        try
        {

        web::http::client::http_client szyszki(U("https://closingtime.szyszki.de/api/details"));
        szyszki.request(methods::GET).then([=](http_response response))
            {
                if(response.status_code() == status_codes::OK)
                {
                    json::value jsonFromAPI = response.extract_json().get();
                    std::cout << jsonFromAPI<<std::endl;

                    int dayOfWeek = jsonFromAPI[U("daydayOfWeek")].as_number().to_int32;  //Monday=1
                    int symSec = jsonFromAPI[U("symSec")].as_number().to_int32;
                    string symTime = [U"symTime"].as_string();
                    int speed = [U"speed"].as_number().to_int32;


                }




            }


            json::value val = task.get();


            message.reply(status_codes::OK);
        }
        catch(std::exception& e) {
            message.reply(status_codes::BadRequest);
        }
    });
}
