#include "VoltageControlNI.h"

VoltageNI::VoltageNI()
{
	SendIFC(0);
	FindLstn(0, instruments, result, NUM_DEVICES);

	num_listeners = ibcnt;
	result[num_listeners] = NOADDR;


};

VoltageNI::~VoltageNI()
{
	ibonl(0, 0);
};