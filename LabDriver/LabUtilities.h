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
void doWeinerCount(WeinerCounter *nim, double time, double sampleLength,
                   double volt, const HeaderInfoGen &hg, const vector<string> &activePix, string fileName, int x, int y);
//interruptable version
void doWeinerCountInter(WeinerCounter *nim, double time, double sampleLength,
                        double volt, const HeaderInfoGen &hg, const vector<string> &activePix, string fileName);
//time independent verison
void doWeinerCountInf(WeinerCounter *nim, double sampleLength,
                      double volt, const HeaderInfoGen *hg, string fileName, atomic<bool> *run);

//IF YOU ARE USING THINS PACKAGE JUST FOR THE UTILITIES YOU DO NOT NEED TO BE CONCERNED WITH THE CODE BELOW
//ALL CODE BELOW IS HELPER FUNCTIONS OR CONSTANTS

//counter helper functions
static void writeWeinerCount(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q,
                             boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done,
                             string fileName, const HeaderInfoCounter &ha, const HeaderInfoGen &hg, int x, int y);

static void readWeinerCount(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q,
                            boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                            atomic<bool> *done, WeinerCounter *nim, double time, double intervalLength);

static void readWeinerCountInter(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q,
                                 boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                                 atomic<bool> *done, WeinerCounter *nim, double time, double intervalLength);

static void readWeinerCountInf(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q,
                               boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                               atomic<bool> *done, WeinerCounter *nim,double intervalLength, atomic<bool> *run);
//opens prompt for user interrupt
static void userInterrupt(atomic<bool> *t);
double findRate(WeinerCounter* nim, int lineNum, double time, double intervalLength = 1);
//measures all 20 lines and stores there times/ count in the vectors
void measureLines(WeinerCounter* nim, double time, double &actualTime, vector<int> &count,double intervalLength = 1);
const int OVER = 65536;

//for GUI
void doLineScan(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, HeaderInfoGen* header, atomic<bool>* run);

string createFileName(HeaderInfoGen *header, Messages* message, time_t t);

void doAfterScanGraphMultiGUI(MotorController *mot, WeinerCounter *nim, Voltage *volt, HeaderInfoGen* header, Messages* message, Readout* readout, atomic<bool>* run);
void doAfterPulseAny(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int voltage, Readout* readout, atomic<bool>* run);
void doAfterScanGraphMultiFree(WeinerCounter *nim, HeaderInfoGen* header, Voltage *volt, Messages* message, Readout* readout, atomic<bool>* run);

static void readFromPixAfterAny(atomic<bool> *done, boost::lockfree::spsc_queue<vector<int>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, WeinerCounter *nim, Readout* readout, atomic<bool>* run);
static void writeInfoAfterAny(boost::lockfree::spsc_queue<vector<int>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg, Readout* readout);


void doHexScanX(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, HeaderInfoGen* header, atomic<bool>* run);
void doXYScan(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, HeaderInfoGen* header, atomic<bool>* run);



#endif