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
#include "stdafx.h"
#include "headers.h"
#include "CImg-1.6.5_pre062415\CImg.h"
#include "TTree.h"
#include "TFile.h"
using namespace std;

//USER FUNCIONS
// after-pulse functions
//each on of these creates an afterpulse file  
//with the name fileName by looking at the channel of the listed pixels and query the counter as fast as possible
void doAfterPulse1(string fileName, WeinerCounter *nim, HeaderInfoGen const &hg,
                   int x1, int y1, int voltage, int numReadings = 100000);

void doAfterPulse2(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int x1,int y1,
                   int x2, int y2, int voltage, int numReadings = 100000);

void doAfterPulse3(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int x1, int y1,
                   int x2, int y2, int x3, int y3, int voltage, int numReadings = 100000);

void doAfterPulse4(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int x1, int y1,
                   int x2, int y2, int x3, int y3, int x4, int y4, int voltage, int numReadings = 100000);

void doAfterPulse5(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int x1, int y1,
                   int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5, int voltage, int numReadings = 100000);

void doAfterPulse10(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int x1, int y1,
                    int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5, int x6, int y6,
                    int x7, int y7, int x8, int y8, int x9, int y9, int x10, int y10, int voltage, int numReadings = 100000);
//uses the nim box to produce a counter file for the entire device saved in a file with the name fileName
//counter functions
//time-dependent non interruptable version
void doWeinerCount(WeinerCounter *nim, double time, double sampleLength,
                   double volt, const HeaderInfoGen &hg, const vector<string> &activePix, string fileName);
//interruptable version
void doWeinerCountInter(WeinerCounter *nim, double time, double sampleLength,
                        double volt, const HeaderInfoGen &hg, const vector<string> &activePix, string fileName);
//time independent verison
void doWeinerCountInf(WeinerCounter *nim, double sampleLength,
                      double volt, const HeaderInfoGen &hg, const vector<string> &activePix, string fileName);
//peforms a voltage scan
void doVoltageScan(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
//peforms an after pulse scan on maximum of 1 pixle at a time and produces no graphs
void doAfterScanNoGraph(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
//peforms an after pulse scan on maximum of 1 pixle at a time and produces graphs
void doAfterScanGraph(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
//peforms an after pulse scan on multiple pixles and produces graphs
void doAfterScanGraphMulti(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
void doAfterScanGraphMultiAndBack(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
//performs an after pulse scan on multiple pixels and produces graphs with adaptive time intervals based on a proportion
void doAfterScanGraphMultiAdapt(MotorController *mot, WeinerCounter *nim, VoltageControl *volt);
//initiates user free mode

//IF YOU ARE USING THINS PACKAGE JUST FOR THE UTILITIES YOU DO NOT NEED TO BE CONCERNED WITH THE CODE BELOW
//ALL CODE BELOW IS HELPER FUNCTIONS OR CONSTANTS
//read functions query the device and push ito a queue that can be handled in another thread
//write functions take the data generated in the read and turn it into a file
//NOTE: These should be run in 2 threads concurrently
//helper functions
static void readFromPixAfter1(int pix, atomic<bool> *done, boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>> *q,
                              boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                              WeinerCounter *nim, int readings);
static void writeInfoAfter1(boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>> *q,
                            boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                            atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg);

static void readFromPixAfter2(int pix1, int pix2, atomic<bool> *done, boost::lockfree::spsc_queue<array<int, 2>,
  boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
  WeinerCounter *nim, int readings);

static void writeInfoAfter2(boost::lockfree::spsc_queue<array<int, 2>, boost::lockfree::capacity<10000>> *q,
                            boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                            atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg);

static void readFromPixAfter3(int pix1, int pix2, int pix3, atomic<bool> *done,
                              boost::lockfree::spsc_queue<array<int, 3>, boost::lockfree::capacity<10000>> *q,
                              boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                              WeinerCounter *nim, int readings);
static void writeInfoAfter3(boost::lockfree::spsc_queue<array<int, 3>, boost::lockfree::capacity<10000>> *q,
                            boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                            atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg);

static void readFromPixAfter4(int pix1, int pix2, int pix3, int pix4, atomic<bool> *done,
                              boost::lockfree::spsc_queue<array<int, 4>, boost::lockfree::capacity<10000>> *q,
                              boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                              WeinerCounter *nim, int readings);

static void writeInfoAfter4(boost::lockfree::spsc_queue<array<int, 4>, boost::lockfree::capacity<10000>> *q,
                            boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                            atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg);

static void readFromPixAfter5(int pix1, int pix2, int pix3, int pix4, int pix5, atomic<bool> *done,
                              boost::lockfree::spsc_queue<array<int, 5>, boost::lockfree::capacity<10000>> *q,
                              boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                              WeinerCounter *nim, int readings);


static void writeInfoAfter5(boost::lockfree::spsc_queue<array<int, 5>, boost::lockfree::capacity<10000>> *q,
                            boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done,
                            string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg);

static void readFromPixAfter10(int pix1, int pix2, int pix3, int pix4, int pix5,int pix6, int pix7, int pix8,
                               int pix9, int pix10, atomic<bool> *done, boost::lockfree::spsc_queue<array<int, 10>,
                               boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point,
                               boost::lockfree::capacity<10000>> *t, WeinerCounter *nim, int readings);


static void writeInfoAfter10(boost::lockfree::spsc_queue<array<int, 10>, boost::lockfree::capacity<10000>> *q,
                             boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                             atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg);

//counter helper functions
static void writeWeinerCount(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q,
                             boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done,
                             string fileName, const HeaderInfoCounter &ha, const HeaderInfoGen &hg);

static void readWeinerCount(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q,
                            boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                            atomic<bool> *done, WeinerCounter *nim, double time, double intervalLength);

static void readWeinerCountInter(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q,
                                 boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                                 atomic<bool> *done, WeinerCounter *nim, double time, double intervalLength);

static void readWeinerCountInf(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q,
                               boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t,
                               atomic<bool> *done, WeinerCounter *nim,double intervalLength);
//opens prompt for user interrupt
static void userInterrupt(atomic<bool> *t);
int findLineWithLowestRate(WeinerCounter *nim, const vector<int> &lines);
double findHighestRate(WeinerCounter *nim, const vector<int> &lines);
const int OVER = 65536;
#endif