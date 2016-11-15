#include "ni4882.h"

class VoltageNI
{
public:
	VoltageNI();
	~VoltageNI();
	int voltageOn();
	int setVoltage(float voltage);
	int voltageOff();

private:
	const static int BUF_SIZE = 1024;
	const static int NUM_DEVICES = 2;
	Addr4882_t instruments[NUM_DEVICES];
	Addr4882_t result[NUM_DEVICES];
	int num_listeners;
};