#pragma once

#include <iostream>
#include <vector>
//#include "LabUtilities.h"
//#include "VoltageControl.h"
//#include "MotorController.h"
//#include "WeinerCounter.h"
//using namespace std;

class Messages{
	//commands

public:
	//bool handleModeOption(string option, MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
	//bool promptQuit();
	//void printVScanHelp();
	//void printAPScanHelp();
	//void printFreeHelp();
	//void printComboHelp();
	//void executeVScan(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
	//void executeAPScanCount(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
	//void executeVScanFile(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
	//void executeAPScan(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
	//void executeFree(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
	//void executeCombo(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
	//void executeMap(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
	//void executePanelMap(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
	//bool isPixValid(string filename);
	int voltage;
	std::string filename;
	std::string fullFile;
	
	int time;
	int numPix, maxOffsetX;
	int maxOffsetY, maxStepX;
	int maxStepY;
	int voltageStart, voltageStep, voltageEnd;
	int frequency;
	std::string temp = "";

	std::vector<int> pixX, pixY;



};
