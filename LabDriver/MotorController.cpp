#include "MotorController.h"
using namespace std;
MotorController::MotorController(long PortNumber, long BaudRate){
  LPCSTR DriverPath = "C:\\Users\\plasmapanel\\Desktop\\newSetupStuff\\WORKINGLD\\LabDriver\\VxmDriver.dll";
  LoadDriver(DriverPath);
  PortOpen(PortNumber, BaudRate);
}
MotorController::MotorController(long PortNumber, long BaudRate, string filename){
  LPCSTR DriverPath = "C:\\Users\\plasmapanel\\Desktop\\newSetupStuff\\WORKINGLD\\LabDriver\\VxmDriver.dll";
  LoadDriver(DriverPath);
  PortOpen(PortNumber, BaudRate);
  setUpGrid(filename);
}

MotorController::~MotorController(){
  PortClose();
  try{
    ReleaseDriver();
  }
  catch (...){

  }
}
void MotorController::stepMotor(int num, int dist){
  if (num < 1 || num>2){
    throw;
  }
  if (num == 1){
    dist = -dist;
  }
  if (!dist){
    throw;
  }
  if (16777215 < dist && dist > 0){
    throw;
  }
  if (-16777215 > dist && dist < 0){
    throw;
  }
  stringstream ss;
  string temp;
  ss << "F,C,I" << num << "M" << dist << ",R";
  ss >> temp;
  char *c = new char[temp.size()];
  for (int i = 0, len = temp.size(); i < len; ++i){
    c[i] = temp[i];
  }
  PortSendCommands(c);
  char *d = "^";
  PortWaitForChar(d, 0);
  delete[] c;
  this_thread::sleep_for(chrono::microseconds(10000));
}
void MotorController::setZeroX(){
  char *c = "F,C,IA1M-0,R";
  PortSendCommands(c);
  char *d = "^";
  PortWaitForChar(d, 0);
}
void MotorController::setZeroY(){
  char * c = "F,C,IA2M-0,R";
  PortSendCommands(c);
  char *d = "^";
  PortWaitForChar(d, 0);
}
void MotorController::setZero(){
  setZeroX();
  setZeroY();
 
}
void MotorController::goZero(){
  char *c = "F,C,IA1M0,R";
  PortSendCommands(c);
  char *d = "^";
  PortWaitForChar(d, 0);
  c = "F,C,IA2M0,R";
  PortSendCommands(c);
  PortWaitForChar(d, 0);
}
void MotorController::goTo(int x1, int y1){
  stringstream ss;
  string temp;
  ss << "F,C,IA1M" << -x1 << ",R";
  ss >> temp;
  char *c = new char[temp.size()];
  for (int i = 0, len = temp.size(); i < len; ++i){
    c[i] = temp[i];
  }  
  PortSendCommands(c);
  char *d = "^";
  PortWaitForChar(d, 0);
  delete[] c;
  ss.clear();
  ss.str(std::string());
  ss << "F,C,IA2M" << y1 << ",R";
  ss >> temp;
  c = new char[temp.size()];
  for (int i = 0, len = temp.size(); i < len; ++i){
    c[i] = temp[i];
  }
  PortSendCommands(c);
  PortWaitForChar(d, 0);
  delete[] c;

}

void MotorController::goToCenter(){



}

void MotorController::goToBackGround(){
}

void MotorController::align(){
  cout << "Please align motor with zero point" << endl;
  cout << "Use commands x # and y # to move motor.(integers)" << endl;
  cout << "Enter g when motor is aligned." << endl;
  string cor;
  int num;
  while (1){
    cout << ">>";
    cin >> cor;
    if (cor == "g"){
      break;
    }
    else if (cor == "y"){
      cin >> num;
   
      stepMotor(2, num);
    }
    else if (cor == "x"){
      cin >> num;
      stepMotor(1, num);
    }
    else{
      cout << "Invalid input" << endl;
    }
  }
  setZero();
  goTo(offsetx, offsetx);
  setZero();
}

void MotorController::fineAlign(WeinerCounter* nim, double time){
  //find max 

}

void MotorController::setUpGrid(string filename){
  ifstream in(filename);
  int numX = 0;
  int numY = 0;
  char t;
  if (!(in>>maxX)){
    throw;
  }
  if (!(in >> maxY)){
    throw;
  }
  if (!(in >> offsetx)){
    throw;
  }
  if (!(in >> offsety)){
    throw;
  }
  //potential 2 clean up some memory here
  grid.resize(maxX+1);
  for (int i = 0; i < maxX+1; ++i){
    grid[i].resize(maxY+1);
  }
  while (in >> numX){
    in.ignore();
    if (!(in >> numY)){
      throw;
    }
    if (!(in >> grid[numX][numY].x)){
      throw;
    }
    if (!(in >> grid[numX][numY].y)){
      throw;
    }
    if (!(in >> t)){
      throw;
    }
    if (!(t == 'y' || t == 'n')){
      throw;
    }
    else if (t == 'y'){
      grid[numX][numY].active = true;
    }
    else{
      grid[numX][numY].active = false;
    }
  }
  string temp;
  for (int i = 0, leni = grid.size(); i < leni; ++i){
    for (int j = 0, lenk = grid[i].size(); j < lenk; ++j){
      if (grid[i][j].active){
        list.push_back(grid[i][j]);
        temp = to_string(grid[i][j].x) + "-" + to_string(grid[i][j].x);
        listStrings.push_back(temp);
      }
    }
  }
}

void MotorController::leaveBackGround(){
}

void MotorController::moveToPix(int x, int y){
  if (x < 1 || x > maxX || y < 1 || y > maxY){
    throw;
  }
  goTo(grid[x][y].x, grid[x][y].y);
}
int MotorController::getNumPixActive(){
  return list.size();
}
void MotorController::moveToPix(int num){
  if (num < 0 || num >= list.size()){
    throw;
  }
  goTo(list[num].x, list[num].y);
}


const vector<string>& MotorController::getActivePixelString(){
  return listStrings;
}

int MotorController::getAbsolutePositionX(){
  char *r = MotorPosition(2);
  if (r[0] == '+'){
    r = &r[1];
  }
  return atoi(r);
}
int MotorController::getAbsolutePositionY(){
  char *r = MotorPosition(2);
  if (r[0] == '+'){
    r = &r[1];
  } 
  return atoi(r);
}