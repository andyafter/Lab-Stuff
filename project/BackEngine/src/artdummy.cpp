#include "artdummy.hpp"

#include<iostream>
#include<string>
#include<thread>


ARTDummy::ARTClient(){
  std::cout << "ARTDummy Initialized!" << std::endl;
}

void ARTDummy::startUDPServer(){
  std::cout << "UDP Dummy Server Started!" << std::endl;
}
