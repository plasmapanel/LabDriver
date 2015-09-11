//This file contains the class definition of WeinerCounter
//Author: Michael Ausilio mausilio@umich.edu
/*
 This code base is an attempt to port the functionallity of our Nimbox from labview to C++.

 NOTE: lines are labeled 1 to 20


 NOTE: the way this device handles counting is fairly strange. An explanation of how this is done is provided below

 each counter on the device can only hold maximum 65536 counts (no idea where this is from mathemattically speaking, this is just a device quirk).
 This leads to the very real possibility that the counters may overflow in either a long term test (with a low rate), or a high rate environment. 
 (additionally this may limit this devices effectiveness)
 
 This nessitates 2 things:
 1. even if intermediate measurements are not required (i.e. on care about the 0 second and the 30 second count, not the counts at various steps in between)
 the counter frequently needs to be reupdated so as to not lose counts from overflow
 2. additional checks when updating the count needs to be applied.
 The math is as follows:

 if the read Number % 65536 < 


 read = number counted on device
 temp = previous count  % 65536;
 if (temp < read){
 current count += read - temp;
 }
 else if (temp > read){
 current count += 65536 + read - temp;
 }
 arr[i - 1] = countTrack[i - 1];


*/
#ifndef WEINER_H
#define WEINER_H
#include "stdafx.h"
using namespace std;

class WeinerCounter{
private:
  const int OVER = 65536;
  int countTrack[20];
  //the full file name of our dll
  const string dllLoc = "C:\\Windows\\System32\\DL700_FX2.dll";
  //what nimbox number the device is
  //since we only have 1 atm this will always be 0
  //will need 2 change if we use more
  int port;
  //mem address of our dll DL700_FX2.dll
  HINSTANCE hGetProcId;
  //array for counter
  unsigned long count[20];
  //serial number
  string serialNum;
  //the handle that the device uses to handle connections
  uint32_t handle;
public:
  //R: i is the nimbox number
  //M: entire object
  //E: sets up device so that it can be used 
  WeinerCounter(int i);
  //R: Nothing
  //M: entire device
  //E: frees dll, frees connection to device, and destructs object
  ~WeinerCounter();
  //R: Nothing
  //M: countTrack
  //E: resets this objects internal counter back to 0
  void resetAll();
  //R: Nothing
  //M: countTrack and arr
  //E: queries all lines on the device, updates countTrack to contain the correct count, then stores that into arr
  void update(int arr[]);
  //R: Nothing
  //M: countTrack and arr
  //E: queries all lines on the device, updates countTrack to contain the correct count, then stores that into arr
  //NOTE: same as above, but using a different array container
  void update(array<int, 20> &arr);
  //R: Nothing
  //M: countTrack and arr
  //E: queries the first n lines on the device, updates countTrack to contain the correct count, then stores that into arr
  void updateFirstN(int n, array<int, 20> &arr);
  //R: Nothing
  //M: countTrack 
  //E: queries all lines on the device, updates countTrack to contain the correct count
  void update();
  
  //NOTE: The following functions are used for when the user does not want to have the device maintain its own count.
  //Care should be advised so that integrity of count is maintained

  //R: i is in range [1,20] and arr contains the previous count
  //M: arr
  //E: queries the ith line on the box then store the correct count into arr
  void update(int i, int arr[]);
  //R: i is in range [1,20] and arr contains the previous count
  //M: arr
  //E: queries the ith line on the box then store the correct count into arr
  //NOTE: this is the same fucntion as above, just with a differnet array wrapper
  void update(int i, array<int, 20> &arr);



 //NOTE: this following function is to be used when user only wants the raw reading on each counter (i.e. user must handle overflow calculations)
  //R: i is in range[1,20]
  //M: nothing
  //E: queries the ith line on the box and returns the count
  int readCounter(int i);





  //IF YOU ARE AN END USER YOU SHOULD NOT BE CONCERNED WITH THE CODE BELOW
  //THESE ARE ESSENTIALLY REWRAPPED VERSIONS OF THE BASE DEVICE COMMANDS THAT CAN BE USED TO CREATE NEW COMMANDS
  //CHANCES ARE YOU SHOULD CONTACT ME AT mausilio@umich.edu IF YOU WOULD LIKE HELP ADDING FUNCTIONALLITY
private:
  void initBox(int i);
  void openBox();
  void resetCounter(int i);
  void resetAllCounter();
  void connectCounter(int i);
  void connectAllCounter();
  inline void readAllCounter();
  void closeDevice();
private:
  unsigned char* buildResetCounterString(int i, int &size);
  unsigned char* buildConnectCounterString1(int i, int &size);
  unsigned char* buildConnectCounterString2(int i, int &size);
  unsigned char* buildReadString(int i, int &size);
private:
  string getSerialNum(int i);
  void openDevice();
  int numBytesAva();
  void writeDevice(unsigned char* in, int size);
  int readDevice(int bytes);
private:
  //WARNING THESE FUNCTION HEADERS MAY NO BE CORRECT, ones with ok before have been checked and are usable
  //NEED 2 SET BASED ON WHERE THEY ARE CALLED N LABVIEW
  //functions directly from the dlls
  //these will be wrapped into new functions that our more c++ style for ease of use
  //these are not documented, the documentation will take place in function wrappers
  //if a function has an ok above it it has been wrapped and tested.
  //use others at your own risk
  //NOTE: these functions have been lifted directly from the functions from labview


  //OK
  typedef int32_t(*_CloseDevice)(uint32_t);
  _CloseDevice closeDevice_;
  typedef int32_t(*_CountDevice)(const char*, uint32_t*);
  _CountDevice countDevice_;
  typedef uint32_t(*_FreeProcess)(uint32_t, uint8_t);
  _FreeProcess freeProcess_;
  typedef char* (*_GetSerialNum)(uint16_t);
  //OK
  _GetSerialNum getSerialNum_;
  typedef uint32_t(*_SetPortDOut)(uint32_t, uint8_t);
  _SetPortDOut setPortDOut_;
  typedef uint32_t(*_LoadFirmware)(uint32_t, uint8_t);
  _LoadFirmware loadFirmware_;
  //ok
  typedef int32_t(*_NumBytesAva)(uint32_t, uint32_t*);
  _NumBytesAva numBytesAva_;
  typedef uint32_t(*_OpenDevice)(uint32_t, uint8_t);
  _OpenDevice openDevice_;
  //ok
  typedef int32_t(*_OpenDeviceSerial)(const char*, uint32_t*);
  _OpenDeviceSerial openDeviceSerial_;
  //ok
  typedef int32_t(*_ReadDevice)(uint32_t,uint32_t,const uint8_t*);
  _ReadDevice readDevice_;
  typedef uint32_t(*_ReadEprom)(uint32_t, uint8_t);
  _ReadEprom readEprom_;
  typedef uint32_t(*_SetConfigFpga)(uint32_t, uint8_t);
  _SetConfigFpga setConfigFpga_;
  typedef uint32_t(*_SetPortDOutEnable)(uint32_t, uint8_t);
  _SetPortDOutEnable setPortDOutEnable_;
 // typedef uint32_t(*_SetPortDOutExt)(uint32_t, uint8_t);
  //_SetPortDOutExt setPortDOutExt_;
  typedef uint32_t (*_SetStartUpCommand)(uint32_t, uint16_t, const uint8_t*);
  _SetStartUpCommand setStartUpCommand_;
  typedef uint32_t(*_SetTimeOut)(uint32_t, uint8_t);
  _SetTimeOut setTimeOut_;
  //ok
  typedef int32_t(*_WriteDevice)(uint32_t, uint32_t, const unsigned char*);
  _WriteDevice writeDevice_;
  typedef uint32_t(*_WriteEprom)(uint32_t, uint8_t);
  _WriteEprom writeEprom_;

};

#endif