#include "freeMode.h"



void doFreeMode(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
  printFreeModeWelcome();
  string command;
  bool isBack = false;

  int q;
  while (1){
    cout << ">> ";
    getline(cin, command);
    q = proccessCommand(command, isBack, mot, nim, volt);
    if (q == -1){
      cout << "exiting free mode" << endl;
      break;
    }
    else if (q == 1){
      cout << "Invalid command. Use commad \"?\" for command descriptions" << endl;
    }
  }
}

void printFreeModeWelcome(){
  cout << "Welcome to Free Mode" << endl;
  cout << "Type ? for help." << endl;

}

void printFreeModeHelp(){
  cout << "The potential commands are as follows:" << endl;
  cout << "rmv <#x> <#y> : Move arm <#x> steps in the x-direction and <#y> steps in the y" << endl;
  cout << "rmvx <#x>     : Move arm <#x> steps in the x-direction." << endl;
  cout << "rmvy <#y>     : Move arm <#y> steps in the y-direction." << endl;
  cout << "amv <#x> <#y> : Move arm to the absolute coordinate <#x>, <#y>. Note: origin here is defined by the pixel the motors were zeroed on." << endl;
  cout << "rz            : Move arm to the relative (0,0). Note: this should correspond to the 0th pixel." << endl;
  cout << "gp <#RO> <#HV>: Move arm to pixel with apprporiate readout and hv number." << endl;
  cout << "gback         : Moves arm behind lead shielding for background measurements. Note: no movments can be made until lback is called" << endl;
  cout << "lback         : Moves the arm from out behind the shielding. Note: This allows other movements." << endl;
  cout << "mc            : Moves arm to the center of the device." << endl;
  cout << "paco          : Prints the absolute coordinates that the arm is currently at." << endl;
  cout << "hvon          : Turns on the high voltage." << endl;
  cout << "hvoff         : Turns off the high voltage." << endl;
  cout << "hv <#vol>     : Sets the high voltage to <#vol>" << endl;
  cout << "dovs          : Initiates a Voltage Scan." << endl;
  cout << "doaps         : Initiates an After-pulse Scan." << endl;
  cout << "doapbs        : Initiates an After-pulse Scan that takes a background measurement." << endl;
  cout << "docount <time (seconds)> <y/n>: Initiates a counter for <time> seconds (if 0 then counter is infinite). if y is selected run is interruptable." << endl;
  cout << "quit          : Exits free mode." << endl;
}

int proccessCommand(string command, bool isBack, MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
  stringstream ss;
  string temp;
  int arg1, arg2;
  ss << command;

  if (!(ss >> temp)){
    return 1;
  }
  if (temp == "rmv"){
    ss >> arg1 >> arg2;
    mot->stepMotor(1, arg1);
    mot->stepMotor(2, arg2);
    return 0;
  }
  else if (temp == "rmvx"){
    ss >> arg1;
    mot->stepMotor(1, arg1);
    return 0;
  }
  else if (temp == "rmvy"){
    ss >> arg1;
    mot->stepMotor(2, arg1);
    return 0;
  }
  else if (temp == "amv"){
    ss >> arg1 >> arg2;
    mot->goTo(arg1, arg2);
  }
  else if (temp == "gp"){
    ss >> arg1 >> arg2;
    mot->moveToPix(arg1, arg2);
    return 0;
  }
  else if (temp == "rz"){
    mot->goZero();
    return 0;
  }
  else if (temp == "gback"){
    isBack = true;
    mot->goToBackGround();
    return 0;
  }
  else if (temp == "lback"){
    mot->leaveBackGround();
    return 0;
  }
  else if (temp == "gc"){
    mot->goToCenter();
    return 0;
  }
  else if (temp == "paco"){
    cout << "coords: (" << mot->getAbsolutePositionX() << " , " << mot->getAbsolutePositionY() << ")" << endl;
    return 0;
  }
  else if (temp == "hvon"){
    volt->turnOn();
    return 0;
  }
  else if (temp == "hvoff"){
    volt->turnOff();
    return 0;
  }
  else if (temp == "hv"){
    ss >> arg1;
    volt->setVoltage(arg1);
    return 0;
  }
  else if (temp == "dovs"){
    doVoltageScan(mot, nim, volt);
    return 0;
  }
  else if (temp == "doaps"){
    doAfterScanGraphMulti(mot, nim, volt);
    return 0;
  }
  else if (temp == "doapbs"){
    doAfterScanGraphMultiAndBack(mot, nim, volt);
    return 0;
  }
  else if (temp == "docount"){
    ss >> arg1 >> temp;
    HeaderInfoGen hg;
    HeaderInfoCounter hc;
    while (1){
      cout << "generate header manually or read from a file?(file/manual): ";
      cin >> temp;
      cin.clear();
      cin.ignore(10000, '\n');
      if (temp == "manual"){
        makeGenHead(hg);
        break;
      }
      else if (temp == "file"){
        cout << "What is the name of the file? ";
        getline(cin, temp);
        makeGenHeadFile(hg, temp);
        break;
      }
      else{
        cout << "Invalid option" << endl;
      }
    }
    cout << "Voltage (V): ";
    cin >> hc.voltage;
    cout << "Time Between Counts (s): ";
    cin >> hc.samplingLength;
    if (arg1 == 0 && temp == "y"){
      volt->setVoltage(hc.voltage);
      doWeinerCountInf(nim, hc.samplingLength, hc.voltage, hg, mot->getActivePixelString(), "freeWCout.txt");
    }
    else if (arg1 == 0 && temp == "n"){
      cout << "Infinite mode needs to be user interruptable." << endl;
      return 1;
    }
    else if (arg1 > 0 && temp == "y"){
      doWeinerCountInter(nim, arg1, hc.samplingLength, hc.voltage, hg, mot->getActivePixelString(), "freeWCout.txt");
    }
    else if (arg1 > 0 && temp == "n"){
      doWeinerCount(nim, arg1, hc.samplingLength, hc.voltage, hg, mot->getActivePixelString(), "freeWCout.txt");
    }
    else{
      return 1;
    }
    return 0;
  }
  else if (temp == "quit"){
    return -1;
  }
  else if (temp == "?"){
    printFreeModeHelp();
    return 0;
  }
  return 1;
}