#include "MotorController.h"
#include "LabUtilities.h"
using namespace std;
static const int STEP_WAIT_TIME = 10000; //this is the timeout time for checking for '^' this stops the program from hanging if it is not found
//this should be set such that it is long enough where the motor waits for the longest possible move to complete
MotorController::MotorController(long PortNumber, long BaudRate){
  LPCSTR DriverPath = "C:\\Users\\plasmapanel\\Documents\\devlibs\\vxmdriver\\VxmDriver.dll";
  LoadDriver(DriverPath);
  PortOpen(PortNumber, BaudRate);
}
MotorController::MotorController(long PortNumber, long BaudRate, string filename){
  LPCSTR DriverPath = "C:\\Users\\plasmapanel\\Documents\\devlibs\\vxmdriver\\VxmDriver.dll";
  LoadDriver(DriverPath);
  PortOpen(PortNumber, BaudRate);
  setUpGrid(filename);
  setUpMaxAndCenter();
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
    return;
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
  //PortWaitForChar(d, 0);
  PortWaitForChar(d, STEP_WAIT_TIME);
  delete[] c;
  this_thread::sleep_for(chrono::microseconds(10000));
}
void MotorController::stepMotorNoWait(int num, int dist){
  if (num < 1 || num>2){
    throw;
  }
  if (num == 1){
    dist = -dist;
  }
  if (!dist){
    return;
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
  delete[] c;
}
void MotorController::setZeroX(){
  char *c = "F,C,IA1M-0,R";
  PortSendCommands(c);
  char *d = "^";
  PortWaitForChar(d, STEP_WAIT_TIME);
}
void MotorController::setZeroY(){
  char * c = "F,C,IA2M-0,R";
  PortSendCommands(c);
  char *d = "^";
  PortWaitForChar(d, STEP_WAIT_TIME);
}
void MotorController::setZero(){
  setZeroX();
  setZeroY();
 
}
void MotorController::goZero(){
  char *c = "F,C,IA1M0,R";
  PortSendCommands(c);
  char *d = "^";
  PortWaitForChar(d, STEP_WAIT_TIME);
  c = "F,C,IA2M0,R";
  PortSendCommands(c);
  PortWaitForChar(d, STEP_WAIT_TIME);
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
  //these are for debugging purposes
  PortSendCommands(c);
  char *d = "^";
  while (!PortSearchForChars(d)){
    cout << "searching" << endl;
  }
  //PortWaitForChar(d, STEP_WAIT_TIME);
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
  while (!PortSearchForChars(d)){
    cout << "searching" << endl;
  }
  //PortWaitForChar(d, STEP_WAIT_TIME);
  delete[] c;
}

void MotorController::goToNoWait(int x1, int y1){
  chrono::duration<int, milli> dur(STEP_WAIT_TIME);
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
  this_thread::sleep_for(dur);
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
  this_thread::sleep_for(dur);
  delete[] c;
}

void MotorController::goToCenter(){
  goToNoWait(centerX, centerY);
}

void MotorController::goToBackGround(){
  goTo(100000, 100000);
}

void MotorController::align(WeinerCounter* nim){
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
      if (cin.peek() == EOF || cin.peek() == '\n' || cin.peek() == '\t'){
        continue;
      }
      cin >> num;
      if (cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        continue;
      }
      stepMotor(2, num);
    }
    else if (cor == "x"){
      if (cin.peek() == EOF || cin.peek() == '\n'  || cin.peek() == '\t'){
        continue;
      }
      cin >> num;
      if (cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        continue;
      }
      stepMotor(1, num);
    }
    else{
      cout << "Invalid input" << endl;
    }
  }
  setZero();
  goTo(offsetx, offsetx);
  setZero();
  int px, py;
  double time;
  cout << "Beginning fine alignment. Please insert source and collimator and make sure voltage is set to an appropriate value." << endl;
  do{
    cout << "What is the RO line of the pixel you are zeroing on? ";
  } while (!(cin >> px) && cout << "Invalid input please retry" << endl);
  do{
    cout << "What is the HV line of the pixel you are zeroing on? ";
  } while (!(cin >> py) && cout << "Invalid input please retry" << endl);
  do{
    cout << "How long would you like to record data? ";
  } while (!(cin >> time) && cout << "Invalid input please retry" << endl);
  fineAlignZero(px, py, nim, time);
}

void MotorController::fineAlign(WeinerCounter* nim, string filename, double time){
  ofstream out(filename);
  out << maxX << endl;
  out << maxY << endl;
  out << offsetx << " " << offsety << endl;
  int pOffsetX, pOffsetY;
  //iterate over all pixels in grid
  for (int i = 0, leni = grid.size(); i < leni; ++i){
    for (int j = 0, lenj = grid[i].size(); j < lenj; ++j){
      if (i <= 0 || j <= 0 || ((grid[i][j].x == 0 && grid[i][j].y == 0) &&(i>1 || j>1))){
        continue;
      }
      else if (grid[i][j].active && !(grid[i][j].x == 0 && grid[i][j].y == 0)){
        findOffsetToMax(nim, i, j, pOffsetX, pOffsetY, time);
        out << i << "-" << j << " " << grid[i][j].x + pOffsetX << " " << grid[i][j].y + pOffsetY << " y" << endl;
      }
      else if (grid[i][j].x == 0 && grid[i][j].y == 0){
        out << i << "-" << j << " " << grid[i][j].x << " " << grid[i][j].y << " y" << endl;
      }
      else{
        out << i << "-" << j << " " << grid[i][j].x << " " << grid[i][j].y << " n" << endl;
      }
    }
  }
  out.close();
  setUpGrid(filename);
}

void MotorController::fineAlignZero(int pixX, int pixY,WeinerCounter* nim, double time){
  if (pixX  > maxX || pixX < 1 || pixY > maxY || pixY < 1){
    return;
  }
  if (!grid[pixX][pixX].active){
    return;
  }
  int offsetX, offsetY;
  findOffsetToMax(nim, pixX, pixY, offsetX, offsetY, time);
  moveToPix(pixX, pixY);
  stepMotor(1, offsetX);
  stepMotor(2, offsetY);
  setZero();

}

void MotorController::setUpMaxAndCenter(){
  int maxy, maxx, miny, minx;
  minx = maxx = grid[1][1].x;
  miny = maxy = grid[1][1].y;
  for (int i = 1, leni = grid.size(); i < leni; ++i){
    for (int j = 1, lenj = grid[i].size(); j < lenj; j++){

      if (grid[i][j].x > maxx){
        maxx = grid[i][j].x;
      }
      if (grid[i][j].y > maxy){
        maxy = grid[i][j].y;
      }
      if (grid[i][j].x < minx){
        minx = grid[i][j].x;
      }
      if (grid[i][j].y < miny){
        miny = grid[i][j].y;
      }

    }
  }
  centerX = static_cast<int>((maxx + minx) / 2.0);
  centerY = static_cast<int>((maxy + miny) / 2.0);
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
  list.clear();
  listStrings.clear();
  for (int i = 0, leni = grid.size(); i < leni; ++i){
    for (int j = 0, lenk = grid[i].size(); j < lenk; ++j){
      if (grid[i][j].active){
        list.push_back(grid[i][j]);
        temp = to_string(i) + "-" + to_string(j);
        listStrings.push_back(temp);
      }
    }
  }
}

void MotorController::leaveBackGround(){
  //goTo(centerX, centerY);
  stepMotor(2, -100000);
  goTo(centerX, centerY);
}

void MotorController::moveToPix(int x, int y){
  if (x < 1 || x > maxX || y < 1 || y > maxY){
    throw;
  }
  //goTo(grid[x][y].x, grid[x][y].y);
  goToNoWait(grid[x][y].x, grid[x][y].y);
}

void MotorController::test(){

  char * tempc = ""; //= PortReadReply();
  stringstream ss;
  string temp;
  ss << "F,C,I" << 1 << "M" << 1000 << ",R";
  ss >> temp;
  char *c = new char[temp.size()];
  for (int i = 0, len = temp.size(); i < len; ++i){
    c[i] = temp[i];
  }
  PortSendCommands(c);
  chrono::duration<int, milli> dur(200);
  this_thread::sleep_for(dur);
  do{
    tempc = PortReadReply();
    cout << tempc << endl;
    this_thread::sleep_for(dur);
  } while (strcmp(tempc, "^") != 0);
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
  char *r = MotorPosition(1);
  if (r[0] == '+'){
    r = &r[1];
  }
  return -atoi(r);
}

void MotorController::mapPixel(string filename, WeinerCounter *nim, int pixX, int pixY, double timeToMeasure,
                               int maxOffsetX, int maxOffsetY,
                               int maxStepX, int maxStepY){
  ofstream out(filename);
  out << pixX << "-" << pixY << endl;
  out << "timeToMeasure: " << timeToMeasure << endl;
  out << "maxOffsetX: " << maxOffsetX << endl;
  out << "maxOffsetY: " << maxOffsetY << endl;
  out << "maxStepX: " << maxStepX << endl;
  out << "maxStepY: " << maxStepY << endl;
  vector<int>count;
  double actualTime = 0;
  vector<tuple<int, int, double>> mapping;
  vector<int> xoffset, yoffset;
  chrono::duration<int, milli> dur(800);
  //fill out cordinate vector
  for (int i = -maxOffsetX; i <= maxOffsetX; i += maxStepX){
    xoffset.push_back(i);
  }
  for (int i = -maxOffsetY; i <= maxOffsetY; i += maxStepY){
    yoffset.push_back(i);
  }
  moveToPix(pixX, pixY);
  stepMotorNoWait(1, xoffset[0]);
  this_thread::sleep_for(dur);
  this_thread::sleep_for(dur);
  stepMotorNoWait(2, yoffset[0]);
  this_thread::sleep_for(dur);
  this_thread::sleep_for(dur);
  for (int i = 0, leni = xoffset.size(); i < leni; ++i){
    for (int j = 0, lenj = yoffset.size(); j < lenj; ++j){
      measureLines(nim, timeToMeasure, actualTime, count);
      out << xoffset[i] << " " << yoffset[j] << " " << actualTime;
      for (int k = 0; k < 20; ++k){
        out << " " << count[k];
      }
      out << endl;
      stepMotorNoWait(2, maxStepY);
      this_thread::sleep_for(dur);
    }
    stepMotorNoWait(2, (yoffset.size())*-maxStepY);
    this_thread::sleep_for(dur*3);
    stepMotorNoWait(1, maxStepX);
    this_thread::sleep_for(dur);
  }
}

void MotorController::mapPanel(string filename, WeinerCounter* nim, double timeToMeasure, int maxOffsetX, int maxOffsetY, int maxStepX, int maxStepY){
  ofstream out(filename);
  out <<"Whole Panel" << endl;
  out << "timeToMeasure: " << timeToMeasure << endl;
  out << "maxOffsetX: " << maxOffsetX << endl;
  out << "maxOffsetY: " << maxOffsetY << endl;
  out << "maxStepX: " << maxStepX << endl;
  out << "maxStepY: " << maxStepY << endl;
  vector<int>count;

  double actualTime = 0;
  vector<tuple<int, int, double>> mapping;
  vector<int> xoffset, yoffset;
  chrono::duration<int, milli> dur(800);
  //fill out cordinate vector
  for (int i = -maxOffsetX; i <= maxOffsetX; i += maxStepX){
    xoffset.push_back(i);
  }
  for (int i = -maxOffsetY; i <= maxOffsetY; i += maxStepY){
    yoffset.push_back(i);
  }
  goToCenter();
  this_thread::sleep_for(dur * 10);
  stepMotorNoWait(1, xoffset[0]);
  this_thread::sleep_for(dur*10);
  stepMotorNoWait(2, yoffset[0]);
  this_thread::sleep_for(dur*10);
  for (int i = 0, leni = xoffset.size(); i < leni; ++i){
    for (int j = 0, lenj = yoffset.size(); j < lenj; ++j){
      measureLines(nim, timeToMeasure, actualTime, count);
      out << xoffset[i] << " " << yoffset[j] << " " << actualTime;
      for (int k = 0; k < 20; ++k){
        out << " " << count[k];
      }
      out << endl;
      stepMotorNoWait(2, maxStepY);
      this_thread::sleep_for(dur);
    }
    stepMotorNoWait(2, (yoffset.size())*-maxStepY);
    this_thread::sleep_for(dur * 10);
    stepMotorNoWait(1, maxStepX);
    this_thread::sleep_for(dur);
  }
}

int MotorController::getAbsolutePositionY(){
  char *r = MotorPosition(2);
  if (r[0] == '+'){
    r = &r[1];
  } 
  return atoi(r);
}

vector<tuple<int, int, double>> MotorController::computePixelMap(WeinerCounter *nim, int pixX, int pixY, double timeToMeasure,
  int maxOffsetX, int maxOffsetY,
  int maxStepX, int maxStepY){
  vector<tuple<int, int, double>> mapping;
  vector<int> xoffset, yoffset;
  //fill out cordinate vector
  for (int i = -maxOffsetX; i <= maxOffsetX; i += maxStepX){
    xoffset.push_back(i);
  }
  for (int i = -maxOffsetY; i <= maxOffsetY; i += maxStepY){
    yoffset.push_back(i);
  }
  for (int i = 0, leni = xoffset.size(); i < leni; ++i){
    moveToPix(pixX, pixY);
    stepMotor(2, xoffset[i]);
    stepMotor(2, yoffset[0]);
    for (int j = 0, lenj = yoffset.size(); j < lenj; ++j){
      mapping.push_back(make_tuple(xoffset[i], yoffset[j], findRate(nim, pixX, timeToMeasure)));
      stepMotor(2, maxStepY);
    }
  }
  return mapping;

}

void MotorController::findOffsetToMax(WeinerCounter *nim, int pixX, int pixY, int &offsetX, int &offsetY, double timeToMeasure, int maxOffsetX, int maxOffsetY,
  int maxStepX, int maxStepY){
  //TODO: implement a more efficent search algo for finding the max
  //NEED TO add check to see if pixX, pixY is actually instrumented
  vector<int> xoffset, yoffset;
  //fill out cordinate vector
  for (int i = -maxOffsetX; i <= maxOffsetX; i += maxStepX){
    xoffset.push_back(i);
  }
  for (int i = -maxOffsetY; i <= maxOffsetY; i += maxStepY){
    yoffset.push_back(i);
  }
  vector<double> xRate(xoffset.size(), 0);
  vector<double> yRate(yoffset.size(), 0);
  moveToPix(pixX, pixY);
  stepMotor(2, yoffset[0]);
  for (int i = 0, len = yoffset.size(); i < len; ++i){
    yRate[i] = findRate(nim, pixX, timeToMeasure);
    //cout << yoffset[i] << " " << yRate[i] << endl;
    stepMotor(2, maxStepY);
  }
  moveToPix(pixX, pixY);
  stepMotor(1, xoffset[0]);
  for (int i = 0, len = xoffset.size(); i < len; ++i){
    xRate[i] = findRate(nim, pixX, timeToMeasure);
    //cout<<xoffset[i]<<" " << xRate[i] << endl;
    stepMotor(1, maxStepX);
  }
  
  double maxRateX = xRate[0];
  double maxRateY = yRate[0];
  double maxRateXi = 0;
  double maxRateYi = 0;
  for (int i = 1, len = xoffset.size(); i < len; ++i){
    if (maxRateX < xRate[i]){
      maxRateX = xRate[i];
      maxRateXi = i;
    }
  }
  for (int i = 1, len = yoffset.size(); i < len; ++i){
    if (maxRateY < yRate[i]){
      maxRateY = yRate[i];
      maxRateYi = i;
    }
  }
  offsetX = xoffset[maxRateXi];
  offsetY = yoffset[maxRateYi];
  ofstream out("//AlignmentData//"+to_string(pixX) + "-" + to_string(pixY) + "Align.txt");
  out << pixX << "-" << pixY << endl;
  for (int i = 1, len = xoffset.size(); i < len; ++i){
    out << xoffset[i] << " " << 0 << xRate[i] << endl;
  }
  for (int i = 1, len = yoffset.size(); i < len; ++i){
    out << 0 << " " << yoffset[i] << yRate[i] << endl;
  }
}