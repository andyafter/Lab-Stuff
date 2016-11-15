#ifndef ARTFRAME_HPP
#define ARTFRAME_HPP

#include<string>

using namespace std;
class ARTFrame{
protected:
  int numMarkers;
  long int timestamp;

public:
  ARTFrame();
  ARTFrame(int num, long int time);
  ~ARTFrame();
  string getSequence();
  int getNumMarkers();
  long int getTimeStamp();
};


#endif
