#ifndef ARTCLIENT_H
#define ARTCLIENT_H

#include<string>

using namespace std;

class artclient
{
public:
    artclient();
    ~artclient();
    udpListen();
protected:
    string rawData;
};

#endif // ARTCLIENT_H
