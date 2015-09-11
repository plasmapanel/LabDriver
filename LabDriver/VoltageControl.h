#include "ComPort.h"
#include "stdafx.h"
using namespace std;
#ifndef V_CONTROL
#define V_CONTROL
class VoltageControl{
private:
  int comNum;
  const char* port;
public:
  VoltageControl(int num);
  ~VoltageControl();
  void setVoltage(int v);
  void turnOn();
  void turnOff();
};
#endif