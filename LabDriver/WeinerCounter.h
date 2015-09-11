//This file contains the class definition of WeinerCounter
//Author: Michael Ausilio mausilio@umich.edu
/*
 This code base is an attempt to port the functionallity of our Nimbox from labview to C++.
*/
#ifndef WEINER_H
#define WEINER_H
#include "stdafx.h"
using namespace std;
/*
How this device counts:
when the device is queried for its count it will return a 4 byte array
to convert this array use the formula temp[3] + temp[2] * 256 = total

Each bin on the counter holds 65536 counts this nessitates the need for role over
the math is
if (count  % 65536 < read){
count += read - count% 65536;
}
else if (count % 65536 > read){
count += OVER + read - count % 65536;
}

*/
class WeinerCounter{
private:
  //size of the counter's bin
  const int OVER = 65536;
  //array that holds the count
  int countTrack[20];
  //the full file name of our dll
  const string dllLoc = "C:\\Windows\\System32\\DL700_FX2.dll";
  //what nimbox number the device is
  //since we only have 1 atm this will always be 0
  //will need 2 change if we use more
  int port;
  //mem address of our dll DL700_FX2.dll
  HINSTANCE hGetProcId;
  //array that holds the count
  //unsigned long count[20];
  //serial number
  string serialNum;
  //the handle that the device uses to handle connections
  uint32_t handle;
  //arrays of strings that hold the strings required for various actions
  unsigned char* readString[20];
public:
  //effects: Creates a new instance of this class by opening and preparing the box in port i. Also configures functions from dll
  //Note: will throw errors if device is unable to be opened
  WeinerCounter(int i);
  ~WeinerCounter();
  //Requires: nothing
  //Modifies: countTrack, counter on device
  //Effects: resests count to 0
  void resetAll();
  //requires: arr is atleast a size 20 array
  //modifies: countTrack, arr
  //effects: updates the object's counter and copies its values into arr
  void update(int arr[]);
  //requires: arr is atleast a size 20 array
  //modifies: countTrack, arr
  //effects: updates the object's counter and copies its values into arr
  void update(array<int, 20> &arr);
  //requires: arr is atleast an n size array
  //modifies: countTrack, arr
  //effects: updates the object's 1st n counters and copies its values into arr
  void updateFirstN(int n, array<int, 20> &arr);
  //requires: nothing
  //modifies: countTrack
  //effects: updates the object's counters
  void update();
  //requires: arr is atleast a size i+1 array
  //modifies: countTrack, arr
  //effects: updates bin i and copies it value into arr[i-1] (its appropriate bin)
  void update(int i, int arr[]);
  //requires: arr is atleast a size i+1 array
  //modifies: countTrack, arr
  //effects: updates bin i and copies it value into arr[i-1] (its appropriate bin)
  void update(int i, array<int, 20> &arr);
  //requires:nothing
  //modifies: nothing
  //effects: read's the current content of the device's bin
  //Note: This gives a value in range [0, 65536), some computations needs to be done to get actual count
  //Note: This should be used only when sampling speed is important and roll over handling can be done
  //in another thread
  int readCounter(int i);
private:
  //requires: nothing
  //modifies nothing
  //effects: initializes box in port i
  void initBox(int i);
  //requires: devices has been initialized
  //modifies nothing
  //effects: opens device
  void openBox();
  //requires: i [1,20]
  //modifies count
  //effects: resets the count on channel i
  void resetCounter(int i);
  //requires: nothing
  //modifies count
  //effects: resets the count on all channels
  void resetAllCounter();
  //requires: device has been opened and intialized. i [1,20]
  //modifies: nothing
  //effects: connects the counter on line i
  void connectCounter(int i);
  //requires: device has been opened and intialized.
  //modifies: nothing
  //effects: connects the all counters
  void connectAllCounter();
  //requires device has been initialized properly
  //modifies: count
  //effects: reads device bins and stores new count in count
  inline void readAllCounter();
  //requires: nothing
  //modifies nothing
  //effects: closes the connection with the box
  void closeDevice();
private:
  //Requires: i is in range [0,20]
  //Modifies: nothing
  //Effects: returns a pointer to a dynamic c-string used to reset the counter on the nim box and sets size = to its size
  //WARNING: User must delete this array after use
  unsigned char* buildResetCounterString(int i, int &size);
  //Requires: i is in range [0,20]
  //Modifies: nothing
  //Effects: returns a pointer to a dynamic c-string used to connect the counter on the nim box and sets size = to its size
  //WARNING: User must delete this array after use
  unsigned char* buildConnectCounterString1(int i, int &size);
  //Requires: i is in range [0,20]
  //Modifies: nothing
  //Effects: returns a pointer to a dynamic c-string used to connect the counter on the nim box and sets size = to its size
  //WARNING: User must delete this array after use
  unsigned char* buildConnectCounterString2(int i, int &size);
  //Requires: i is in range [0,20]
  //Modifies: nothing
  //Effects: returns a pointer to a dynamic c-string used to prep the counter for reading on the nim box and sets size = to its size
  //WARNING: User must delete this array after use
  unsigned char* buildReadString(int i, int &size);
private:
  //Requires: nothing
  //Modifies: nothing
  //Effects: returns the Nim box in port i's serial number
  string getSerialNum(int i);
  //requires: nothing
  //modifies: nothing
  //effects: opens the device
  void openDevice();
  //requires: nothing
  //modifies: nothing
  //effects: returns the number of bytes waiting to be read
  int numBytesAva();
  //Requires: size = the size of the cstring given by in
  //Modifies: nothing
  //Effects: writes a string to the device
  void writeDevice(unsigned char* in, int size);
  //Requires: nothing
  //Modifies: nothing
  //Effects: reads bytes from device and converts it into the bin's count
  int readDevice(int bytes);
private:
  //WARNING THESE FUNCTION HEADERS MAY NO BE CORRECT, ones with ok before have been checked and are usable
  //NEED 2 SET BASED ON WHERE THEY ARE CALLED N LABVIEW
  //functions directly from the dlls
  //these will be wrapped into new functions that our more c++ style for ease of use
  //these are not documented, the documentation will take place in function wrappers
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