#include "messages.h"



void printModeList() {
  cout << "vscan  - Initiates a Voltage Scan (setup needs to be entered)" << endl;
  cout << "apscan - Initiates a After-Pulse Scan (setup needs to be entered)" << endl;
  cout << "free   - Initiates free mode" << endl;

}
int handleModeOption(string option) {
  if (option == "vscan") {
    cout << "Initiating Voltage Scan" << endl;
    return 1;
  }
  else if (option == "apscan") {
    cout << "Initiating After-Pulse Scan" << endl;
    return 2;
  }
  else if (option == "free") {
    cout << "Initiating Free Mode" << endl;
    return 3;
  }
  else {
    cout << "Invalid input, please retry." << endl;
    return 0;
  }
}

void printVScanHelp(){
}