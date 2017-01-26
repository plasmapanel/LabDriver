#pragma once

#include <vector>

class Readout
{
public:
	std::vector<bool> active;
	int numLines;
	int numActive;

	Readout();
	~Readout();


};

