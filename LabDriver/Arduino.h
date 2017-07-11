#pragma once
#include "headers.h"
#include "Messages.h"
#include "TTree.h"
#include "TFile.h"
#include "ComPort.h"

#include <json/json.h>

class Arduino
{
public:
	Arduino();
	~Arduino();
	void doArduino(Messages* message, HeaderInfoGen* info, bool* run);
	void readArduino();

private:
	int port;
};

