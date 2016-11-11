#include "artclient.hpp"

#include<iostream>
#include<string>
#include <thread>


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
    std::thread t1(this->testThread);
    for(int i = 0; i<1000; i++){
      std::cout << i << std::endl;
    }
    t1.join();
}

string ARTClient::getRawData(){
    return rawData;
}

void ARTClient::decodeData(){
    std::cout << "Trying very hard to decode data!" << std::endl;
}

void ARTClient::testThread(){
  for(int i=0; i<1000; ++i){
    std::cout << i << std::endl;
  }
}

void ARTClient::getARTData(){
  std::cout << "Starting ART Data collection!" << std::endl;
}

void ARTClient::dummyData(){
    // this is for getting ART data testing, move to unit test later!!
    std::cout << "DummyData with UDP!" << std::endl;
}
