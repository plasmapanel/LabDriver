#pragma once

#include <iostream>
#include <vector>

class Messages{

public:
	int voltage;
	std::string filename;
	std::string fullFile;
	
	int time;
	int numPix, maxOffsetX;
	int maxOffsetY, maxStepX;
	int maxStepY;
	int motorstepx;
	int motorstepy;
	int voltageStart, voltageStep, voltageEnd;
	int frequency;
	std::string temp = "";
	std::string runtype = "";
	int row;
	int column;

	std::vector<int> pixX, pixY;



};
