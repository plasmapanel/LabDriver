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
/*
#include "TCanvas.h"
#include "TH1.h"
#include "TError.h"
#include "TSystem.h"
*/
#include "messages.h"
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

  //initialize lab hardware
  WeinerCounter *nim = nullptr;
  VoltageControl *volt = nullptr;
  MotorController *mot = nullptr;
  string pixFileName;
  cout << "What pixel config file should be used? ";
  cin >> pixFileName;
  cin.ignore(10000, '\n');
  cin.clear();
  cout << "Initializing Motor Controller." << endl;
  try{//again need 2 add more catching
    //also add some setup stuff about configuring panel
    mot = new MotorController(6, 9600, pixFileName);
  }
  catch(...){
    cout << "Unable to initialize Motor Controller. Please check that it is connected correctly and you are using a valid device config file\n";
    cout << "If you are unsure what constitutes a valid setup file please consult the README." << endl;
    exit(1);
  }
  cout << "Initializing NIMBox" << endl;
  try{
    nim = new WeinerCounter(0);
  }
  catch (...){ // add more catching later 2 handle things like issues with dll, wrong port, etc.
    cout << "Unable to initalize NIMBox. Please check that it is correctly connected and setup." << endl;
    exit(1);
  }
  try{//again need 2 add more catching
    volt = new VoltageControl(5);
  }
  catch (...){
    cout << "Unable to initalize Voltage Controller. Please check that it is correctly connected and setup" << endl;
    exit(1);
  }

  bool cont = true;
  string option;
  //NEED 2 ADD STUFF ABOUT SETTING UP THE VARIOUS PIECES OF LAB EQUIPMENT
  cout << "Welcome to our lab station." << endl;
  //out something about setting up pixel layout
  cout << "Please select your mode. (help for mode list)" << endl;
  while (cont){
    cout << ">> ";
    cin >> option;
    cont = handleModeOption(option, mot, nim, volt); //handle 
    cin.ignore(10000, '\n');
    cin.clear();

  }

}



