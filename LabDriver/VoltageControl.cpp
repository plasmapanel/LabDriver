#include "VoltageControl.h"
  void VoltageControl::init(int num){
    //set up port name
	  comNum = num;
	  string temp;
	  stringstream ss;
	  ss << "COM" << num;
	  ss >> temp;
	  port = temp.c_str();
	  //open port
	  DWORD error = 0;
	  error = PxSerialOpen(port);
	  if (error != 0){throw;}
}
//VoltageControl::~VoltageControl(){
//  DWORD error = 0;
//  error = PxSerialClose();
//  if (error != 0){
//    throw;
//  }
//}

void VoltageControl::setVoltage(int v){
  if (v >= 10000){
    throw;
  }
  DWORD error = 0;
  string temp;
  stringstream ss;
  ss << "P";
  if (v < 1000){
    if (v < 10){
      ss << "0.00" << v << "KG";
    }
    if (v < 100){
      ss << "0.0" << v << "KG";
    }
    else{
      ss << "0." << v << "KG";
    }
  }
  else{
    if (v%1000 < 10){
      ss << v / 1000 << ".00" << v % 1000 << "KG";
    }
    if (v%1000 < 100){
      ss << v / 1000 << ".0" << v % 1000 << "KG";
    }
    else{
      ss << v / 1000 << "." << v % 1000 << "KG";
    }
  }
  ss >> temp;
  char volt[256];
  sprintf_s(volt, "%s\r\n", temp.c_str(), 256);
  DWORD written = 0;
  error = PxSerialWrite(volt, (DWORD)strlen(volt), &written);
  if (error != 0){
    throw;
  }
  this_thread::sleep_for(chrono::seconds(5));
}
void VoltageControl::turnOn(){
  DWORD error = 0;
  char * on = "R\r\n";
  DWORD written = 0;
  error = PxSerialWrite(on, (DWORD)strlen(on), &written);
  if (error != 0){
    throw;
  }
  char buffer[256];
  DWORD bytesRead;
  error = PxSerialRead(buffer, sizeof(buffer) - 1, &bytesRead);
  if (error != 0){
    throw;
  }
  this_thread::sleep_for(chrono::seconds(2));
}
void VoltageControl::turnOff(){
  DWORD error = 0;
  char * off = "Z\r\n";
  DWORD written = 0;
  error = PxSerialWrite(off, (DWORD)strlen(off), &written);
  if (error != 0){
    throw;
  }
  char buffer[256];
  DWORD bytesRead;
  error = PxSerialRead(buffer, sizeof(buffer) - 1, &bytesRead);
  if (error != 0){
    throw;
  }
  this_thread::sleep_for(chrono::seconds(2));
}

void VoltageControl::end()
{
	  DWORD error = 0;
	  error = PxSerialClose();
	  if (error != 0){
	    throw;
	  }
}

