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
        // serwer z ktorego pobieraam
        //web::http::client::http_client szyszki(U(xxxxx/time));
        //szyszki.request(methods::GET).then([=](http_response response))
            //{
            //if(response.status_code() == status_codes::OK)
            //{




            //}




            //}




            json::value val = task.get();


            message.reply(status_codes::OK);
        }
        catch(std::exception& e) {
            message.reply(status_codes::BadRequest);
        }
    });
}
