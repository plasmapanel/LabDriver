#include "ni4882.h"
#include "string"
#include "sstream"
//#include <Windows.h>
#include "stdafx.h"
using namespace std;

class VoltageNI
{
public:
	VoltageNI();
	~VoltageNI();
	void turnOn();
	void setVoltage(int voltage);
	void turnOff();

private:
	const static int BUF_SIZE = 1024;
	const static int NUM_DEVICES = 2;
	Addr4882_t instruments[NUM_DEVICES];
	Addr4882_t result[NUM_DEVICES];
	int num_listeners;
	char buffer[BUF_SIZE];
	unsigned short address;
	//void gpib_error(int errnum, char *errmsg);
};