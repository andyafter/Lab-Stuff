#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <boost/asio.hpp>

#include "artclient.hpp"

using namespace std;

int main(){
    cout<< "Starting Main Project\n";
    ARTClient client(5002);
    client.run();
    cout<< "Finished Main Project!!" << endl;
    return 0;
}


