#pragma once

#include <vector>

class Readout
{
public:
	std::vector<bool> active;
	int numLines = 0;
	int numActive = 0;
	const double timeread = 0.005;
	int samples = 0;
	double totaltime = 0;

	Readout(int lines);
	Readout();
	~Readout();

	void timeToSamples(double time);



};

