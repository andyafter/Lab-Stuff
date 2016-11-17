#ifndef ARTDUMMY_HPP
#define ARTDUMMY_HPP

#include <string>
#include <cstdlib>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/array.hpp>


using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using boost::asio::ip::udp;


class ARTDummy{
private:
  boost::asio::io_service& io_service_;
  udp::socket socket_;
  udp::endpoint endpoint_;
  
public:
  ARTDummy(boost::asio::io_service& io_service, 
           const std::string& host, 
           const std::string& port);
  ~ARTDummy();
  void startUDPServer();
  void send(const std::string& msg);
};


#endif
