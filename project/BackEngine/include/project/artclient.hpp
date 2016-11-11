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
    int port;

public:
    ARTClient();
    ARTClient(int port, string ip = "127.0.0.1");
    ~ARTClient();
    void run();
    string getRawData();
    void decodeData();
    static void testThread();
    static void getARTData();
    static void dummyData();     // Move to unit testing later 
};
#endif

