#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

#include<boost/thread.hpp>
#include<boost/bind.hpp>
#include<boost/asio.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<boost/algorithm/string.hpp>

#include "artclient.hpp"
#include "artdummy.hpp"

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

void testBoostAsio();
void client_session(socket_ptr sock);

io_service service;
ip::tcp::endpoint ep(ip::tcp::v4(), 2001); // listen on 2001
ip::tcp::acceptor acc(service, ep);

int main(int argc, char *argv[]){
  cout<< "Starting Main Project\n";

  ARTClient client(5002);
  client.run();

  ARTDummy dummy;
  dummy.startUDPServer();
  

  if(argc > 0){
    cout<< argv[1] << endl;
    testBoostAsio();
  }

  return 0;
}

void testBoostAsio(){
  while ( true) {
    socket_ptr sock(new ip::tcp::socket(service));
    acc.accept(*sock);
    boost::thread( boost::bind(client_session, sock));
  }

}

void client_session(socket_ptr sock) {
  while (true) {
    char data[512];
    size_t len = sock->read_some(buffer(data));
    if (len > 0)
      write(*sock, buffer("ok", 2));
  }
}
