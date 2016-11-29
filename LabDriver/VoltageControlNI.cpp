#include "VoltageControlNI.h"

VoltageNI::VoltageNI()
{
	SendIFC(0);
	//if (ibsta & ERR)
		//gpib_error(1, "Could not send IFC");

	//for (int i = 0; i < NUM_DEVICES - 1; i++)
	//	instruments[i] = i + 1;
	//instruments[NUM_DEVICES - 1] = NOADDR;

	//FindLstn(0, instruments, result, NUM_DEVICES);

	//num_listeners = ibcnt;
	//result[num_listeners] = NOADDR;


};

VoltageNI::~VoltageNI()
{
	ibonl(0, 0);
};

void VoltageNI::setVoltage(int v)
{
	if (v >= 10000){
		throw;
	}

	std::string temp;
	std::stringstream ss;
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
		if (v % 1000 < 10){
			ss << v / 1000 << ".00" << v % 1000 << "KG";
		}
		if (v % 1000 < 100){
			ss << v / 1000 << ".0" << v % 1000 << "KG";
		}
		else{
			ss << v / 1000 << "." << v % 1000 << "KG";
		}
	}
	ss >> temp;
	char volt[256];
	sprintf_s(volt, "%s\r", temp.c_str(), 256);
	DWORD written = 0;

	Send(0, 0, volt, strlen(volt), NLend);
	this_thread::sleep_for(chrono::seconds(5));
}

void VoltageNI::voltageOff()
{
	char * off = "Z\r";
	Send(0, 0, off, strlen(off), NLend);
}

void VoltageNI::voltageOn()
{
	char * on = "R\r";
	Send(0, 0, on, strlen(on), NLend);
}