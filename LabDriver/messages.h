#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class Messages{

public:
	int voltage;
	std::string filename;
	std::string fullFile;
	
	int time;
  int numPixels; // numColumns*numRows
  int totalOffsetX;
  int totalOffsetY;
  int stepX;
	int stepY;
  int pixelDistanceX;
  int pixelDistanceY;
  int numRows;
  int numColumns;
	int motorstepx;
	int motorstepy;
	int voltageStart, voltageStep, voltageEnd;
	int frequency = 0;
	std::string temp = "";
	std::string runtype = "";
  std::string fileName = "";
  std::string fullName = "";

  float timeToGo;
  int numVoltageSteps;
  int currentPositionX;
  int currentPositionY;
  int currentColumn;
  int CurrentRow;
  int currentPixel;

	std::vector<int> pixX, pixY;

  void setNumberPixels();
  //void setCurrentPosition();
};

std::ostream& operator<<(std::ostream& os, const Messages& h);