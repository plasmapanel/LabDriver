#include "WeinerCounter.h"
#include "stdafx.h"
#include <iostream>
#include "LabUtilities.h"
#include "MotorController.h"
#include "messages.h"
#include "windows.h"
#include "VxmDriver.h" //remove this
using namespace std;
int main(){
  //initialize lab hardware
  char ch;
  WeinerCounter *nim = nullptr;
  VoltageControl *volt = nullptr;
  MotorController *mot = nullptr;
  string pixFileName;
  do{
    cout << "What pixel config file should be used? ";
    cin >> pixFileName;
    cin.ignore(10000, '\n');
    cin.clear();
  } while (!isPixValid(pixFileName));
  cout << "Initializing NIMBox" << endl;
  try{
    nim = new WeinerCounter(0);
  }
  catch (...){ // add more catching later 2 handle things like issues with dll, wrong port, etc.
    cout << "Unable to initalize NIMBox. Please check that it is correctly connected and setup." << endl;
    exit(1);
  }
  cout << "Initializing Motor Controller." << endl;
  try{//again need 2 add more catching
    //also add some setup stuff about configuring panel
    mot = new MotorController(6, 9600, pixFileName);
    bool cont = true;
    while (cont){
      cout << "Does this device need to be zeroed? (y/n) ";
      ch = cin.get();
      cin.ignore(10000, '\n');
      cin.clear();
      if (ch == 'n'){
        cont = false;
        break;
      }
      if (ch == 'y'){
        while (1){
          cout << "Are you sure, this will unzero the current alignment? (y/n) ";
          ch = cin.get();
          cin.ignore(10000, '\n');
          cin.clear();
          if (ch == 'n'){
            break;
          }
          if (ch == 'y'){
            cont = false;
            mot->align(nim);
            break;
          }
          else{
            cout << "Invalid Input" << endl;
          }
        }
      }
      else{
        cout << "Invalid Input" << endl;
      }
    }
  }
  catch (...){
    cout << "Unable to initialize Motor Controller. Please check that it is connected correctly and you are using a valid device config file\n";
    cout << "If you are unsure what constitutes a valid setup file please consult the README." << endl;
    exit(1);
  }

  cout << "Initializing Voltage Controller" << endl;
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
  cout << "Please select your mode. (type help for help)" << endl;
  while (cont){
    cout << ">> ";

    cin >> option;
    cin.ignore(10000,'\n');
    cin.clear();
    cont = handleModeOption(option, mot, nim, volt); //handle 


  }
  delete mot;
  delete nim;
  delete volt;
  
  }
