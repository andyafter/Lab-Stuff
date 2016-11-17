#include<iostream>

#include "artframe.hpp"

ARTFrame::ARTFrame(){
  this->numMarkers = 0;
  this->timestamp = 0;
}

ARTFrame::ARTFrame(int num, long int time){
  this->numMarkers = num;
  this->timestamp = time;
}

ARTFrame::~ARTFrame(){
  
}

string ARTFrame::getSequence(){
  return "";
}

int ARTFrame::getNumMarkers(){
  return this->numMarkers;
}

long int ARTFrame::getTimeStamp(){
  return this->timestamp;
}
