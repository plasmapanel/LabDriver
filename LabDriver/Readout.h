#pragma once

#include <vector>

class Readout
{
public:
	std::vector<bool> active;
	int numLines;
	int numActive;
	const double timeread = 0.005;
	int samples;
	double totaltime;

	Readout(int lines);
	Readout();
	~Readout();

	void timeToSamples(double time);



};

