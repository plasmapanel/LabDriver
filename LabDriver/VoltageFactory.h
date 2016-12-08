#pragma once

#include <string>


class Voltage
{
public:
	virtual void setVoltage(int) {};
	virtual void turnOn() {};
	virtual void turnOff() {};
	virtual void init(int) {};
	//~Voltage();
};

#include "VoltageControl.h"
#include "VoltageControlNI.h"

class VoltageFactory
{
public:
	static Voltage* newVolt(const std::string &description);
};



