#ifndef MESSAGES_H
#define MESSAGES_H
#include <iostream>
#include "LabUtilities.h"
#include "VoltageControl.h"
#include "MotorController.h"
#include "WeinerCounter.h"
using namespace std;

//going to need 2 pass motorcontroller to these after having set it up in

//commands
bool handleModeOption(string option, MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
bool promptQuit();
void printVScanHelp();
void printAPScanHelp();
void printFreeHelp();
void printComboHelp();
void executeVScan(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
void executeVScanFile(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
void executeAPScan(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
void executeFree(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
void executeCombo(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
bool isPixValid(string filename);
#endif