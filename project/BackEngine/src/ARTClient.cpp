#include<iostream>
#include<string>

#include "artclient.hpp"

ARTClient::ARTClient(int port, string ip = "127.0.0.1"){
    rawData = "";
    IPAddress = ip;
    status = "standalone";
}

ARTClient::~ARTClient(){
    std::cout << "ARTClient Destructed!" << std::endl;
}

ARTClient::run(){
    std::cout << "ARTClient Started Running!" << std::endl;
    
}

string ARTClient::getRawData(){
    return rawData;
}

