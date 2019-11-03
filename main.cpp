#include <iostream>
#include "Service.h"
#include "BasicController.h"

using namespace std;

int main()
{
    Service serv("192.168.0.242","8080");
    serv.setEndpoint("/api");
    serv.accept().wait();
    while(1==1)
    {
        sleep(1000);
    }
    return 0;
}
