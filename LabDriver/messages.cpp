#include "messages.h"



bool handleModeOption(string option, MotorController *mot, WeinerCounter *nim, VoltageControl *volt)) {
  if (option == "vscan") {
    cout << "Initiating Voltage Scan" << endl;
    executeVScan();
    return promptQuit();
  }
  else if (option == "apscan") {
    cout << "Initiating After-Pulse Scan" << endl;
    executeAPScan();
    return promptQuit();
  }
  else if (option == "free") {
    cout << "Initiating Free Mode" << endl;
    executeFree();
    return promptQuit();
  }
  else if (option == "combo"){
    cout << "Initiating Combo Scan" << endl;
    executeCombo();
    return promptQuit();
  }
  else if (option == "help"){
    cout << "Valid options are:" << endl;
    cout << "quit   - quits the lab station software" << endl;
    cout << "free   - initiates free mode. In free mode, user has (almost) unfettered control of all almost all lab station equipment." << endl;
    cout << "         Currently avaliable equipment: Bertran 225 High Voltage Power Supply, NIMBox, and the VXM Stepping Motor Controller." << endl;
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