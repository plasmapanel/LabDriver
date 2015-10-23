/*
~22600 from 1 side 2 another
Notes Motor 1 is the x axis motor
Motor 2 is the y

baud rate is 9600 typically
*/
#ifndef MOT_CONT
#define MOT_CONT
#include "VxmDriver.h"
#include "WeinerCounter.h"
using namespace std;
class MotorController{
public:
  MotorController(long PortNumber, long BaudRate);
  MotorController(long PortNumber, long BaudRate, string filename);
  ~MotorController();
  void stepMotor(int num, int dist);
  void setZero();
  void setZeroX();
  void setZeroY();
  void setUpGrid(string filename);
  void goZero();
  void goTo(int x, int y);
  void goToCenter();
  void goToBackGround();
  void leaveBackGround();
  void moveToPix(int x, int y);
  int getNumPixActive();
  void moveToPix(int num);
  void align();
  void fineAlign(WeinerCounter *nim, double time, int xcor, int ycor);
  const vector<string>& getActivePixelString();
  int getAbsolutePositionX();
  int getAbsolutePositionY();

private:
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