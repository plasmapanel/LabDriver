#include "VoltageFactory.h"


Voltage* VoltageFactory::newVolt(const std::string &description)
{
	if (description == "Yellow")
		return new VoltageControl();
	else if (description == "NI")
		return new VoltageNI();
}


