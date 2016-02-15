/*
~22600 from 1 side 2 another
Notes Motor 1 is the x axis motor
Motor 2 is the y

baud rate is 9600 typically
*/
#ifndef MOT_CONT
#define MOT_CONT
//constants used for default values of find pixel center
#define TIME_TO_MEASURE 30
#define MAX_OFFSET_X 600
#define MAX_OFFSET_Y 1000
#define MAX_STEP_X 50
#define MAX_STEP_Y 50
#include "VxmDriver.h"
#include "WeinerCounter.h"
using namespace std;
class MotorController{
public:
  MotorController(long PortNumber, long BaudRate);
  MotorController(long PortNumber, long BaudRate, string filename);
  ~MotorController();
  void stepMotor(int num, int dist);
  //steps the motor but does not wait for the motor to send the completion signal
  //i.e. no waiting is done
  //NOTE: USER IS RESPONSIBLE FOR CONTROLLING THE WAITING FOR MOTOR
  void stepMotorNoWait(int num, int dist);
  void setZero();
  void setZeroX();
  void setZeroY();
  void setUpGrid(string filename);
  void goZero();
  void goTo(int x1, int y1);
  void goToNoWait(int x1, int y1);
  void goToCenter();
  void goToBackGround();
  void leaveBackGround();
  void moveToPix(int x, int y);
  //void moveToPix(int x, int y);
  int getNumPixActive();
  void moveToPix(int num);
  void align(WeinerCounter* nim);
  
  void fineAlign(WeinerCounter* nim,string filename, double time);
  const vector<string>& getActivePixelString();
  int getAbsolutePositionX();
  int getAbsolutePositionY();
  void mapPixel(string filename, WeinerCounter *nim, int pixX, int pixY, double timeToMeasure = TIME_TO_MEASURE,
    int maxOffsetX = MAX_OFFSET_X, int maxOffsetY = MAX_OFFSET_Y,
    int maxStepX = MAX_STEP_X, int maxStepY = MAX_STEP_Y);

  vector<tuple<int, int, double> > computePixelMap(WeinerCounter *nim, int pixX, int pixY, double timeToMeasure = TIME_TO_MEASURE,
    int maxOffsetX = MAX_OFFSET_X, int maxOffsetY = MAX_OFFSET_Y,
    int maxStepX = MAX_STEP_X, int maxStepY = MAX_STEP_Y);
  


private:
  //finds the offset from pixels current location that maximizes the rate 
  void findOffsetToMax(WeinerCounter *nim, int pixX, int pixY, int &offsetX, int &offsetY, double timeToMeasure = TIME_TO_MEASURE,
    int maxOffsetX = MAX_OFFSET_X,int maxOffsetY = MAX_OFFSET_Y,
    int maxStepX = MAX_STEP_X, int maxStepY = MAX_STEP_Y);
  void fineAlignZero(int pixX, int pixY, WeinerCounter* nim, double time);

  void setUpMaxAndCenter();
  //these are the values used for fine aligning the motor
  static const int X_OFFSET = 100;
  static const int Y_OFFSET = 200;
  //These are the coordinates of the zeroth pixel relative to the refrence point
  int offsetx;
  int offsety;
  int maxX = 0;
  int maxY = 0;
  int centerX;
  int centerY;
  struct Pixel{
    int x = 0;
    int y = 0;
    bool active = false;
  };
  vector<vector<Pixel>> grid;
  vector<Pixel> list;
  vector<string> listStrings;
};
#endif