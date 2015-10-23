#include "messages.h"
#include "freeMode.h"


bool handleModeOption(string option, MotorController *mot, WeinerCounter *nim, VoltageControl *volt) {
  if (option == "vscan") {
    cout << "Initiating Voltage Scan" << endl;
    executeVScan(mot, nim, volt);
    return promptQuit();
  }
  else if (option == "apscan") {
    cout << "Initiating After-Pulse Scan" << endl;
    executeAPScan(mot, nim, volt);
    return promptQuit();
  }
  else if (option == "free") {
    cout << "Initiating Free Mode" << endl;
    executeFree(mot, nim, volt);
    return promptQuit();
  }
  else if (option == "combo"){
    cout << "Initiating Combo Scan" << endl;
    executeCombo(mot, nim, volt);
    return promptQuit();
  }
  else if (option == "help"){
    cout << "Valid options are:" << endl;
    cout << "quit   - quits the lab station software" << endl;
    cout << "free   - initiates free mode. In free mode, user has direct control of lab station equipment." << endl;
    cout << "         Currently avaliable equipment: " << endl;
    cout << "            Bertran 225 High Voltage Power Supply"<<endl;
    cout << "            NIMBox" << endl;
    cout << "            VXM Stepping Motor Controller." << endl;
    cout << "vscan  - initiates a voltage scan. Parameters for this test are set before running." << endl;
    cout << "apscan - initiates an after-pulse scan. Parameters for this test are set before running." << endl;
    cout << "combo  - initiates a combination voltage and after-pulse scan. Parameters for this run are set before running." << endl;
    return true;
  }
  else if (option == "quit"){
    cout << "Exiting lab system." << endl;
    return false;
  }
  else {
    cout << "Invalid input, please retry." << endl;
    cout << "type \"help\" for help." << endl;
    return true;
  }
}
void printVScanHelp(){
}


void executeVScan(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
  doVoltageScan(mot, nim, volt);
}
void executeAPScan(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
  doAfterScanGraphMulti(mot, nim, volt);
}
void executeFree(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
  doFreeMode(mot, nim, volt);
}
void executeCombo(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
  doAfterScanGraphMultiAndBack(mot, nim, volt);
}
bool promptQuit(){
  char temp;
  cout << "Would you like to quit? (y/n): ";
  while (1){
    cin.get(temp);
    cin.ignore(10000, '\n');
    cin.clear();
    if (temp == 'y'){
      return false;
    }
    else if (temp == 'n'){
      return true;
    }
    else{
      cout << "Invalid character." << endl;
      cout << "Would you like to quit? (y/n): ";
    }
  }
}