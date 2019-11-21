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
            json::value number;
            number["Tpcob"] = json::value::number(T_pcob);
            message.reply(status_codes::OK, number);
        }
        if (path[0]=="T_r") {
            json::value number;
            number["Tr"] = json::value::number(T_r);
            message.reply(status_codes::OK, number);
        }
        if (path[0]=="T_ref") {
            json::value number;
            number["Tref"] = json::value::number(T_ref);
            message.reply(status_codes::OK, number);
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


void Service::handle_post(http_request request)
{
    TRACE("\nHandle POST\n");

    handle_request(
        request, 
        [](const json::value & jvalue, json::value & answer, bool bNull)
        {

            const utility::string_t sStatus("status");
            const utility::string_t sTag("tag_name");
            const utility::string_t sFcob("WaterIntakeFcob");
            const utility::string_t sTpcob("return_water_temp_Tpcob");
            const utility::string_t sTh("radiator_temp_Th");
            const utility::string_t sTr("room_temp_Tr");
			const utility::string_t sstamp("timestamp");


            if( bNull )
            {
                wcout << "jvalue must be null, setting some default values..." << endl;
                json::value group;              
                group[sStatus] = json::value::string("running");
                group[sTag] = json::value::string("Radek Halejus");
                group[sFcob] = json::value::string("100");
                group[sTpcob] = json::value::string("1200");
                group[sTh] = json::value::string("1000");
                group[sTr] = json::value::string("100");
                group[sstamp] = json::value::string("100");				
				
                answer[0] = group;
            }
            else
            {
                // To be written once the null case is sorted
            }
        }
    );
}