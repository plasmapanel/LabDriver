/*
This file contains all of the utilities that will be used with our lab setup
*/
#ifndef LAB_UT
#define LAB_UT
#include "RootGraph.h"
#include "WeinerCounter.h"
#include "MotorController.h"
#include "HighResClock.h"
#include "VoltageControl.h"
#include "headers.h"
#include "stdafx.h"
#include "headers.h"
#include "CImg.h"
#include "TTree.h"
#include "TFile.h"
#include "Messages.h"
#include "VoltageFactory.h"
#include "Readout.h"
using namespace std;
using Spsc_int = boost::lockfree::spsc_queue < int, boost::lockfree::capacity<10000> >;
using Spsc_time = boost::lockfree::spsc_queue < HighResClock::time_point, boost::lockfree::capacity<10000> > ;

//uses the nim box to produce a counter file for the entire device saved in a file with the name fileName
//counter functions
//time-dependent non interruptable version
void doWeinerCount(WeinerCounter *nim, double volt, const HeaderInfoGen *hg, string runType, string runName, atomic<bool> *run, double measurementDuration,
  vector<int> activeReadout = {1, 2, 3, 4, 5, 6, 7, 8 , 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20});

void doWeinerCounta(WeinerCounter *nim, string runName, HeaderInfoGen* header, Messages* message, Readout* readout, atomic<bool> *run);
//time independent verison
void doWeinerCountInf(WeinerCounter *nim, double volt, const HeaderInfoGen *hg, string runType, string runName, atomic<bool> *run,
  vector<int> activeReadout = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 });

//IF YOU ARE USING THINS PACKAGE JUST FOR THE UTILITIES YOU DO NOT NEED TO BE CONCERNED WITH THE CODE BELOW
//ALL CODE BELOW IS HELPER FUNCTIONS OR CONSTANTS


double findRate(WeinerCounter* nim, int lineNum, double time, double intervalLength = 1);
//measures all 20 lines and stores there times/ count in the vectors
void measureLines(WeinerCounter* nim, double time, double &actualTime, vector<int> &count,double intervalLength = 1);
const int OVER = 65536;

//for GUI
void doLineScan(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, HeaderInfoGen* header, atomic<bool>* run);

string createFileName(HeaderInfoGen *header, Messages* message, time_t t);

void doAfterScanGraphMultiFree(WeinerCounter *nim, HeaderInfoGen* header, Voltage *volt, Messages* message, Readout* readout, atomic<bool>* run);



void doHexScanX(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, HeaderInfoGen* header, atomic<bool>* run);
void doXYScan(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, HeaderInfoGen* header, atomic<bool>* run);



#endif