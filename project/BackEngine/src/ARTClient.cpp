#include<iostream>
#include<string>

#include<artclient.hpp>

ARTClient::ARTClient(int port, string ip){
    std::cout << "ARTClient Initiated!" << std::endl;
    rawData = "";
    IPAddress = ip;
    status = "standalone";
}

ARTClient::ARTClient() : port(5000), IPAddress("127.0.0.1"){}

ARTClient::~ARTClient(){
    std::cout << "ARTClient Destructed!" << std::endl;
}

void ARTClient::run(){
    std::cout << "ARTClient Started Running!" << std::endl;
}

string ARTClient::getRawData(){
    return rawData;
}

