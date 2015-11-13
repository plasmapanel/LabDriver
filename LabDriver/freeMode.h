#include <iostream>
#include <sstream>
#include "MotorController.h"
#include "WeinerCounter.h"
#include "LabUtilities.h"
#include "VoltageControl.h"
#include "headers.h"
void doFreeMode(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
void printFreeModeWelcome();
void printFreeModeHelp();
int proccessCommand(string command, bool &isBack, MotorController *mot, WeinerCounter *nim, VoltageControl *volt);