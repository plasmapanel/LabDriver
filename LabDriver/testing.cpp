#include "WeinerCounter.h"
#include "headers.h"
#include "stdafx.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <fstream>
#include <queue>
#include <iostream>
#include "HighResClock.h"
#include "LabUtilities.h"
#include "VoltageControl.h"
#include "MotorController.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TError.h"
#include "TSystem.h"
using namespace std;

int main(){
  //doAfterScanGraphMulti();
  //doVoltageScan();
  //makeTChainN(".\\CollectedData\\Ne1Ar20CF4\\740torr\\MC02_Ne1Ar20CF4_740_1436473464\\AfterPulse\\");
  //makeApGraphsN(".\\CollectedData\\Ne1Ar20CF4\\740torr\\MC02_Ne1Ar20CF4_740_1436814619\\AfterPulse\\", 100);
  //makeApDiffGraphN(".\\CollectedData\\Ne1Ar20CF4\\740torr\\MC02_Ne1Ar20CF4_740_1436814619\\AfterPulse\\");
  //makeApIntGraphN(".\\CollectedData\\Ne1Ar20CF4\\740torr\\MC02_Ne1Ar20CF4_740_1436814619\\AfterPulse\\", 100);
  //WeinerCounter *nim = new WeinerCounter(0);
  //vector<string> lines = { "Asd" };
  //findLineWithLowestRate(nim, lines);
  //findHighestRate(nim, lines);
  //HeaderInfoGen hg;
  //doVoltageScan();
  //doWeinerCount(nim, 10 * 60, 1, 1080, hg, lines, "asd.txt");
  //doAfterPulse10("test.txt", nim, hg, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10,1000,10000);
  /*
  MotorController mot(6, 9600, "mc30.txt");
  //mot.stepMotor(1, 9000);
  mot.setZero();
  for (int i = 0; i < mot.getNumPixActive(); ++i){
    mot.moveToPix(i);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  mot.goZero();
  */
  //delete nim;
  int opt = 0;
  string option;
  cout << "Welcome to our lab station." << endl;
  //out something about setting up pixel layout
  cout << "Please select your mode. (help for mode list)" << endl;
  while (opt == 0){
    cin >> option;
    cin.ignore(10000, '\n');

  }

}



