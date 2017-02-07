#include "Readout.h"


Readout::Readout(int lines)
{
	active.resize(lines);
}

Readout::Readout()
{
	active.resize(20);
	for (int i = 0; i < 20; i++)
	{
		active[i] = true;
	}

	lines.resize(20);
	for (int i = 0; i < 20; i++)
	{
		lines[i] = i;
	}
}


Readout::~Readout()
{
}

void Readout::timeToSamples(double time)
{
	samples = ceil(time / (timeread * numActive));
}