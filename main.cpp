#include <iostream>
#include "Service.h"
#include "BasicController.h"
#include <cpprest/http_client.h>


int main()
{
    Service serv("0.0.0.0","8080");
    serv.setEndpoint("/api");
    serv.accept().wait();
    std::cout<<"like"<<std::endl;




    while(1==1)
    {
        sleep(1000);
    }
    return 0;
}
