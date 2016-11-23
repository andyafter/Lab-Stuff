#include "artdummy.hpp"


ARTDummy::ARTDummy(boost::asio::io_service& io_service, 
                   const std::string& host, 
                   const std::string& port) : io_service_(io_service), socket_(io_service, udp::endpoint(udp::v4(), 0)){
  udp::resolver resolver(io_service_);
  udp::resolver::query query(udp::v4(), host, port);
  udp::resolver::iterator iter = resolver.resolve(query);
  endpoint_ = *iter;
}

void ARTDummy::startUDPServer(){
  std::cout << "UDP Dummy Server Started!" << std::endl;
}

void ARTDummy::send(const std::string& msg){
  socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_);
  std::cout << "message sent!" << msg << std::endl;
}

ARTDummy::~ARTDummy(){
  socket_.close();
  
}