#include "messages.h"
#include <iostream>
#include <string>
using namespace std;
//#include "freeMode.h"



//bool handleModeOption(string option, MotorController *mot, WeinerCounter *nim, VoltageControl *volt) {
//  if (option == "vscan") {
//    cout << "Initiating Voltage Scan" << endl;
//    executeVScan(mot, nim, volt);
//    cin.ignore(10000, '\n');
//    cin.clear();
//    return promptQuit();
//  }
//  if (option == "vscanFile") {
//    cout << "Initiating File Driven Voltage Scan" << endl;
//    executeVScanFile(mot, nim, volt);
//    return promptQuit();
//  }
//  else if (option == "apscan") {
//    cout << "Initiating After-Pulse Scan" << endl;
//    executeAPScan(mot, nim, volt);
//    cin.ignore(10000, '\n');
//    cin.clear();
//    return promptQuit();
//  }
//  else if (option == "apscanCount") {
//    cout << "Initiating After-Pulse Count Scan" << endl;
//    executeAPScanCount(mot, nim, volt);
//    cin.ignore(10000, '\n');
//    cin.clear();
//    return promptQuit();
//  }
//  else if (option == "free") {
//    cout << "Initiating Free Mode" << endl;
//    executeFree(mot, nim, volt);
//    return promptQuit();
//  }
//  else if (option == "combo"){
//    cout << "Initiating Combo Scan" << endl;
//    executeCombo(mot, nim, volt);
//    cin.ignore(10000, '\n');
//    cin.clear();
//    return promptQuit();
//  }
//  else if (option == "falign"){
//    int voltage;
//    string filename;
//    double time;
//    cout << "What should this new .pix file be named? ";
//    getline(cin, filename);
//    cout << "How long should data be taken at each step (s)? ";
//    cin >> time;
//    cin.ignore(10000, '\n');
//    cin.clear();
//    cout << "What voltage should this be run at (V)? ";
//    cin >> voltage;
//    cin.ignore(10000, '\n');
//    cin.clear();
//    volt->setVoltage(voltage);
//    volt->turnOn();
//    mot->fineAlign(nim, filename, time);
//    volt->turnOff();
//    return promptQuit();
//  }
//  else if (option == "map"){
//    cout << "Intitiating Mapping" << endl;
//    executeMap(mot, nim, volt);
//    cin.ignore(10000, '\n');
//    cin.clear();
//    return promptQuit();
//  }
//  else if (option == "mapPanel"){
//    cout << "Intitiating Mapping" << endl;
//    executePanelMap(mot, nim, volt);
//    cin.ignore(10000, '\n');
//    cin.clear();
//    return promptQuit();
//  }
//  else if (option == "help"){
//    cout << "Valid options are:" << endl;
//    cout << "quit   - quits the lab station software" << endl;
//    cout << "free   - initiates free mode. In free mode, user has direct control of lab station equipment." << endl;
//    cout << "         Currently avaliable equipment: " << endl;
//    cout << "            Bertran 225 High Voltage Power Supply" << endl;
//    cout << "            NIMBox" << endl;
//    cout << "            VXM Stepping Motor Controller." << endl;
//    cout << "falign - initates the fine alignment of all non-zero active pixels. This modifies the grid currently being used and" << endl;
//    cout << "         creates a new .pix file to be used on this panel in the future" << endl;
//    cout << "vscan  - initiates a voltage scan. Parameters for this test are set before running." << endl;
//    cout << "vscanFile  - initiates a voltage scan. Parameters for this test are set before running." << endl;
//    cout << "apscan - initiates an after-pulse scan. Parameters for this test are set before running." << endl;
//    cout << "apscanCount - initiates an after-pulse scan that is limited by line count." << endl;
//    cout << "combo  - initiates a combination voltage and after-pulse scan. Parameters for this run are set before running." << endl;
//    cout << "map    - initiates a mapping of a pixel. This characterizes the rate over the area near the pixel" << endl;
//    cout << "mapPanel    - initiates a mapping of a pixel. This characterizes the rate over the entire panel" << endl;
//    return true;
//  }
//  else if (option == "quit"){
//    cout << "Exiting lab system." << endl;
//    return false;
//  }
//  else {
//    cout << "Invalid input, please retry." << endl;
//    cout << "type \"help\" for help." << endl;
//    return true;
//  }
//}
//void printVScanHelp(){
//}


//void Messages::executeVScan(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
//  doVoltageScan(mot, nim, volt);
//}

//void executeVScanFile(MotorController* mot, WeinerCounter* nim, VoltageControl* volt){
//  doVoltageScanFile(mot, nim, volt);
//}
//void executeAPScanCount(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
//  doAfterScanGraphMultiCount(mot, nim, volt);
//}
//void executeAPScan(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
//  doAfterScanGraphMulti(mot, nim, volt);
//}
//void executeFree(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
//  doFreeMode(mot, nim, volt);
//}
//void executeCombo(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
//  doAfterScanGraphMultiAndBack(mot, nim, volt);
//}

//void executeMap(MotorController* mot, WeinerCounter* nim, VoltageControl* volt){
//  string filename, fullFile;
//  int numPix, maxOffsetX, maxOffsetY, maxStepX, maxStepY, time, voltageStart, voltageStep, voltageEnd;
//  vector<int> pixX, pixY;
//  cout << "What is the base output file name?(no extensions)(ex map -> map.txt) ";
//  cin >> filename;
//  cout << "what Voltage should this be started at? (V) ";
//  cin >> voltageStart;
//  cout << "what Voltage should this run end at? (V) ";
//  cin >> voltageEnd;
//  cout << "how large should the step size be? (V) ";
//  cin >> voltageStep;
//  if (voltageStart > voltageEnd){
//    cout << "Invalid voltage range" << endl;
//    return;
//  }
//
//  cout << "How many pixels should be mapped? ";
//  cin >> numPix;
//  pixX.resize(numPix);
//  pixY.resize(numPix);
//  for (int i = 0; i < numPix; ++i){
//    cout << "What is the RO of pixel #" << i + 1 << " that should be mapped? ";
//    cin >> pixX[i];
//    cout << "What is the HV of the pixel #" << i + 1 << " that should be mapped? ";
//    cin >> pixY[i];
//  }
//
//  cout << "What is the max X offset? ";
//  cin >> maxOffsetX;
//  cout << "What is the max Y offset? ";
//  cin >> maxOffsetY;
//  cout << "What is the X step size? ";
//  cin >> maxStepX;
//  cout << "What is the Y step size? ";
//  cin >> maxStepY;
//  cout << "How long should each measurment last? ";
//  cin >> time;
//
//  for (int j = voltageStart; j <= voltageEnd; j += voltageStep){
//    volt->setVoltage(j);
//    for (int i = 0; i < numPix; ++i){
//      //fullFile = "//MappingData//"+filename + "_" + to_string(pixX[i]) + "-" + to_string(pixY[i]) + ".txt";
//      fullFile = filename+"_"+ to_string(j) + "_" + to_string(pixX[i]) + "-" + to_string(pixY[i])+ ".txt";
//      mot->mapPixel(fullFile, nim, pixX[i], pixY[i], time, maxOffsetX, maxOffsetY, maxStepX, maxStepY);
//    }
//  }
//  volt->turnOff();
//}
//
//void executePanelMap(MotorController* mot, WeinerCounter* nim, VoltageControl* volt){
//  string filename, fullFile;
//  int numPix, maxOffsetX, maxOffsetY, maxStepX, maxStepY, time, voltageStart, voltageStep, voltageEnd;
//  cout << "What is the base output file name?(no extensions)(ex map -> map.txt) ";
//  cin >> filename;
//  cout << "what Voltage should this be started at? (V) ";
//  cin >> voltageStart;
//  cout << "what Voltage should this run end at? (V) ";
//  cin >> voltageEnd;
//  cout << "how large should the step size be? (V) ";
//  cin >> voltageStep;
//  if (voltageStart > voltageEnd){
//    cout << "Invalid voltage range" << endl;
//    return;
//  }
//  cout << "What is the max X offset? ";
//  cin >> maxOffsetX;
//  cout << "What is the max Y offset? ";
//  cin >> maxOffsetY;
//  cout << "What is the X step size? ";
//  cin >> maxStepX;
//  cout << "What is the Y step size? ";
//  cin >> maxStepY;
//  cout << "How long should each measurment last? ";
//  cin >> time;
//
//  for (int j = voltageStart; j <= voltageEnd; j += voltageStep){
//   volt->setVoltage(j);
//   fullFile = filename + "_" + to_string(j) + "_panel.txt";
//   mot->mapPanel(fullFile, nim, time, maxOffsetX, maxOffsetY, maxStepX, maxStepY);
//  }
//  volt->turnOff();
//}
//
//bool isPixValid(string filename){
//  int ro, hv, holding;
//  char tempc;
//  ifstream in(filename);
//  //ro line
//  if (!(in >> ro)){
//    cout << "Invalid file" << endl;
//    return false;
//  }
//  //hv line
//  if (!(in >> hv)){
//    cout << "Invalid file" << endl;
//    return false;
//  }
//  //offset line
//  if (!(in >> holding)){
//    cout << "Invalid file" << endl;
//    return false;
//  }
//  if (!(in >> holding)){
//    cout << "Invalid file" << endl;
//    return false;
//  }
//  //start looking at pixel lines
//  while (in.peek() != EOF){
//    if (!(in >> holding) || holding > ro){
//      cout << "Invalid file" << endl;
//      return false;
//    }
//    if (!(in >> tempc) || tempc != '-'){
//      cout << "Invalid file" << endl;
//      return false;
//    }
//    if (!(in >> holding) || holding > hv){
//      cout << "Invalid file" << endl;
//      return false;
//    }
//    if (!(in >> holding)){
//      cout << "Invalid file" << endl;
//      return false;
//    }
//    if (!(in >> holding)){
//      cout << "Invalid file" << endl;
//      return false;
//    }
//    if (!(in >> tempc) || !(tempc == 'n' || tempc == 'y')){
//      cout << "Invalid file" << endl;
//      return false;
//    }
//  }
//  return true;
//}
//
//bool promptQuit(){
//  char temp;
//  cout << "Would you like to quit? (y/n): ";
//  while (1){
//    cin.get(temp);
//    cin.ignore(10000, '\n');
//    cin.clear();
//    if (temp == 'y'){
//      return false;
//    }
//    else if (temp == 'n'){
//      return true;
//    }
//    else{
//      cout << "Invalid character." << endl;
//      cout << "Would you like to quit? (y/n): ";
//    }
//  }
//}
std::ostream& operator<<(std::ostream& os, const Messages& h){
  int voltage;
  std::string filename;
  std::string fullFile;

  int time;
  int numPix, maxOffsetX;
  int maxOffsetY, maxStepX;
  int maxStepY;
  int motorstepx;
  int motorstepy;
  int voltageStart, voltageStep, voltageEnd;
  int frequency;
  std::string temp = "";
  std::string runtype = "";
  int row;
  int column;

  std::vector<int> pixX, pixY;


  os << "Message Header:" << endl;
  os << "Voltage  " << h.voltage << endl;
  os << "File Name   " << h.filename << endl;
  os << "Full File   " << h.fullFile << endl;
  os << "Time   " << h.time << endl;
  os << "Num Pix   " << h.numPix << endl;
  os << "Max Offset X   " << h.maxOffsetX << endl;
  os << "Max Offset X   " << h.maxOffsetY << endl;
  os << "Max Step X   " << h.maxStepX << endl;
  os << "Max Step Y   " << h.maxStepY << endl;
  os << "Motor Step X   " << h.motorstepx << endl;
  os << "Motor Step Y   " << h.motorstepy << endl;
  os << "Voltage Start   " << h.voltageStart << endl;
  os << "Voltage Step   " << h.voltageStep << endl;
  os << "Voltage End   " << h.voltageEnd << endl;
  os << "Run Typee   " << h.runtype << endl;
  os << "Row   " << h.row << endl;
  os << "Column   " << h.column << endl;
  return os;
}