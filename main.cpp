#include <iostream>
#include "Service.h"
#include "BasicController.h"

using namespace std;

int main()
{
    Service serv("0.0.0.0","8080");
    serv.setEndpoint("/api");
    serv.accept().wait();
    while(1==1)
    {
        sleep(1000);
    }
    return 0;
}
