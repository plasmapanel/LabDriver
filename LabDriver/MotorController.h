/*
~22600 from 1 side 2 another
Notes Motor 1 is the x axis motor
Motor 2 is the y

baud rate is 9600 typically
*/
#include "VxmDriver.h"
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
  void moveToPix(int x, int y);
  int getNumPixActive();
  void moveToPix(int num);
  void align();
  const vector<string>& getActivePixelString();
private:
  int maxX = 0;
  int maxY = 0;
  struct Pixel{
    int x = 0;
    int y = 0;
    bool active = false;
  };
  vector<vector<Pixel>> grid;
  vector<Pixel> list;
  vector<string> listStrings;
};