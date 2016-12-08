#pragma once

#include "ComPort.h"
#include "stdafx.h"
#include "VoltageFactory.h"

using namespace std;

class VoltageControl: public Voltage{
private:
  int comNum;
  const char* port;
public:
  void setVoltage(int v);
  void turnOn();
  void turnOff();
  void init(int);
};
