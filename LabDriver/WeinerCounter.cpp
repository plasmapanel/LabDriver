#include "WeinerCounter.h"
using namespace std;
WeinerCounter::WeinerCounter(int i){
  port = i;
  //get mem address of function
  //need 2 cast file name down 2 cstring
  hGetProcId = LoadLibrary(dllLoc.c_str());
  //check if dll is actually loaded
  if (hGetProcId == nullptr){
    throw;
  }
  //set up all functions
  closeDevice_ = (_CloseDevice)GetProcAddress(hGetProcId, "USBBoxCloseDevice");
  if (closeDevice_ == nullptr){
    throw;
  }
  countDevice_ = (_CountDevice)GetProcAddress(hGetProcId, "USBBoxCountDevices");
  if (countDevice_ == nullptr){
    throw;
  }
  freeProcess_ = (_FreeProcess)GetProcAddress(hGetProcId, "USBBoxFreeProcess");
  if (freeProcess_ == nullptr){
    throw;
  }
  getSerialNum_ = (_GetSerialNum)GetProcAddress(hGetProcId, "USBBoxGetDeviceSerialNumber");
  if (getSerialNum_ == nullptr){
    throw;
  }
  setPortDOut_ = (_SetPortDOut)GetProcAddress(hGetProcId, "USBBoxGetPortDOutputs");
  if (setPortDOut_ == nullptr){
    throw;
  }
  loadFirmware_ = (_LoadFirmware)GetProcAddress(hGetProcId, "USBBoxLoadFirmware");
  if (loadFirmware_ == nullptr){
    throw;
  }
  numBytesAva_ = (_NumBytesAva)GetProcAddress(hGetProcId, "USBBoxNumberOfBytesAvailable");
  if (numBytesAva_ == nullptr){
    throw;
  }
  openDevice_ = (_OpenDevice)GetProcAddress(hGetProcId, "USBBoxOpenDevice");
  if (openDevice_ == nullptr){
    throw;
  }
  openDeviceSerial_ = (_OpenDeviceSerial)GetProcAddress(hGetProcId, "USBBoxOpenDeviceWithSerial");
  if (openDeviceSerial_ == nullptr){
    throw;
  }

  readDevice_ = (_ReadDevice)GetProcAddress(hGetProcId, "USBBoxReadDevice");
  if (readDevice_ == nullptr){
    throw;
  }
  readEprom_ = (_ReadEprom)GetProcAddress(hGetProcId, "USBBoxReadEprom");
  if (readEprom_ == nullptr){
    throw;
  }
  setConfigFpga_ = (_SetConfigFpga)GetProcAddress(hGetProcId, "USBBoxSetConfFpgaMode");
  if (setConfigFpga_ == nullptr){
    throw;
  }
  setPortDOutEnable_ = (_SetPortDOutEnable)GetProcAddress(hGetProcId, "USBBoxSetPortDOutputEnable");
  if (setPortDOutEnable_ == nullptr){
    throw;
  }
  /*
  setPortDOutExt_ = (_SetPortDOutExt)GetProcAddress(hGetProcId, "USBBoxPortDOutputExt");
  if (setPortDOutExt_ == nullptr){
    throw;
  }
  */
  setStartUpCommand_ = (_SetStartUpCommand)GetProcAddress(hGetProcId, "USBBoxSetStartupCommand");
  if (setStartUpCommand_ == nullptr){
    throw;
  }
  setTimeOut_ = (_SetTimeOut)GetProcAddress(hGetProcId, "USBBoxSetTimeOut");
  if (setTimeOut_ == nullptr){
    throw;
  }
  writeDevice_ = (_WriteDevice)GetProcAddress(hGetProcId, "USBBoxWriteDevice");
  if (writeDevice_ == nullptr){
    throw;
  }
  writeEprom_ = (_WriteEprom)GetProcAddress(hGetProcId, "USBBoxWriteEprom");
  if (writeEprom_ == nullptr){
    throw;
  }
  //set up connection to device
  initBox(port);
  openBox();
  connectAllCounter();
  resetAllCounter();
  int trash;
  //set up read strings and count
  for (int i = 0; i < 20; ++i){
    countTrack[i] = 0;
    readString[i] = buildReadString(i + 1, trash);
  }
}
void WeinerCounter::initBox(int i){
  serialNum = getSerialNum(i);
}
WeinerCounter::~WeinerCounter(){
  closeDevice();
  //free library
  FreeLibrary(hGetProcId); 
  for (int i = 0; i < 20; ++i){
    delete[] readString[i];
  }
}
void WeinerCounter::resetAll(){
  resetAllCounter();
  for (int i = 0; i < 20; ++i){
    countTrack[i] = 0;
  }
}
void WeinerCounter::update(int arr[]){
  readAllCounter();
  for (int i = 0; i < 20; ++i){
    arr[i] = countTrack[i];
  }
}
void WeinerCounter::update(array<int, 20> &arr){
  readAllCounter();
  for (int i = 0; i < 20; ++i){
    arr[i] = countTrack[i];
  }
}
void WeinerCounter::updateFirstN(int n, array<int, 20> &arr){
  int read;
  int temp;
  for (int i = 1; i <= n; ++i){
    read = readCounter(i);
    temp = countTrack[i - 1] % OVER;
    if (temp < read){
      countTrack[i - 1] += read - temp;
    }
    else if (temp > read){
      countTrack[i - 1] += OVER + read - temp;
    }
    arr[i - 1] = countTrack[i - 1];
  }
}
void WeinerCounter::update(){
  readAllCounter();
}
void WeinerCounter::update(int i, int arr[]){
  int read = readCounter(i);
  int temp = countTrack[i - 1] % OVER;
  if (temp < read){
    countTrack[i - 1] += read - temp;
  }
  else if (temp > read){
    countTrack[i - 1] += OVER + read - temp;
  }
  arr[i - 1] = countTrack[i - 1];
}
void WeinerCounter::update(int i, array<int, 20> &arr){
  int read = readCounter(i);
  int temp = countTrack[i - 1] % OVER;
  if (temp < read){
    countTrack[i - 1] += read - temp;
  }
  else if (temp > read){
    countTrack[i - 1] += OVER + read - temp;
  }
  arr[i - 1] = countTrack[i - 1];
}
string WeinerCounter::getSerialNum(int i){
 char *temp = getSerialNum_((uint16_t)i);
 if (!temp){
   throw;
 }
 return temp;
}
void WeinerCounter::openDevice(){
  int temp;
  temp = openDeviceSerial_(serialNum.c_str(), &handle);
  if (temp < 0){
    //throw if device opening fails
    throw;
  }
}
void WeinerCounter::closeDevice(){
  int temp = closeDevice_(handle);
  if (temp < 0){
    //throw if device opening fails
    throw;
  }
}
void WeinerCounter::openBox(){
  openDevice();
}
int WeinerCounter::numBytesAva(){
  int32_t temp1;
  uint32_t temp2;
  temp1 = numBytesAva_(handle, &temp2);
  return (int)temp1;
}

void WeinerCounter::writeDevice(unsigned char* in, int size){
  //variable that handles the error code
  int32_t temp;
  //this is the number of bytes that are being sent (ie length of string)
  //1 char = 1 byt
  temp = writeDevice_(handle, size, in);
  if (temp < 0){
    throw;
  }
}

unsigned char* WeinerCounter::buildResetCounterString(int i, int &size){
  unsigned char *temp =  new unsigned char[11]{ 69, 71, unsigned char(i), 0, 83, 2, 76, 0, 0, 0, 0 };
  size = 11;
  return temp;
  }
void WeinerCounter::resetCounter(int i){
  if ( i<=0 || i >= 21){
    throw;
  }
  int size;
  unsigned char* c = buildResetCounterString(i, size);
  writeDevice(c,size);
  delete[] c;
}
void WeinerCounter::resetAllCounter(){
  for (int i = 1; i <= 20; ++i){
    resetCounter(i);
  }
}
void WeinerCounter::connectCounter(int i){
  if (i <= 0 || i >= 21){
    throw;
  }
  int size1;
  unsigned char* c1 = buildConnectCounterString1(i,size1);
  int size2;
  unsigned char* c2 = buildConnectCounterString2(i, size2);
  writeDevice(c1,size1);
  writeDevice(c2, size2);
  delete[] c1;
  delete[] c2;
}
unsigned char* WeinerCounter::buildConnectCounterString1(int i, int &size){
  unsigned char *temp = new unsigned char[14]{ 69, 84, unsigned char(i), 0, 66, 0, 83, 1, 66, 0, 83,2,66,3 };
  size = 14;
  return temp;
}
unsigned char* WeinerCounter::buildConnectCounterString2(int i, int &size){
  unsigned char *temp = new unsigned char[20]{ 69, 71, unsigned char(i), 0, 66, unsigned char(i), 83, 1, 76, 0, 0, 0, 1, 83,2,76,0,0,0,0 };
  size = 20;
  return temp;
}
void WeinerCounter::connectAllCounter(){
  for (int i = 1; i <= 20; ++i){
    connectCounter(i);
  }
}
int WeinerCounter::readCounter(int i){
  writeDevice(readString[i-1], 7);
  return readDevice(4);
}
inline void WeinerCounter::readAllCounter(){
  int read;
  for (int i = 1; i <= 20; ++i){
    read = readCounter(i);
    if (countTrack[i - 1] % OVER < read){
      countTrack[i - 1] += read - countTrack[i - 1] % OVER;
    }
    else if (countTrack[i - 1] % OVER > read){
      countTrack[i - 1] += OVER + read - countTrack[i - 1] % OVER;
    }
  }
}
unsigned char* WeinerCounter::buildReadString(int i, int &size){
  unsigned char *temp = new unsigned char[7]{ 69, 71, unsigned char(i), 0, 83, 3, 108 };
  size = 7;
  return temp;
}
int WeinerCounter::readDevice(int bytes){
  uint8_t temp[4];
  int check;
  check = readDevice_(handle, (uint32_t)bytes, temp);
  if (check < 0){
    throw;
  }
  int sum = temp[3] + temp[2] * 256;
  
  return sum;
}
