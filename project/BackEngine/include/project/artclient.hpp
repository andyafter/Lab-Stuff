#ifndef ARTCLIENT_HPP
#define ARTCLIENT_HPP

#include<string>

using namespace std;

class ARTClient{
protected:
    string rawData;
    string IPAddress;
    /* status could be:
       standalone;
       connected; */
    string status;

public:
    ARTClient(int port, string ip = "127.0.0.1");
    ~ARTClient();
    void run();
    string getRawData();
};
#endif

