#ifndef ARTDUMMY_HPP
#define ARTDUMMY_HPP

#include<string>
#include<boost/thread.hpp>
#include<boost/bind.hpp>
#include<boost/asio.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<boost/algorithm/string.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;


class ARTDummy{

public:
  ARTDummy();
  ~ARTDummy();
  void startUDPServer();
};


#endif
