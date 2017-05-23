#include "LabUtilities.h"
#include <iomanip>
#include <functional>
//#include "LabView.h"
#include "headers.h"


static const double NIM_MS_PER_CHANNEL_MEASUREMENT = 0.4;

//Function used for converting weiner counter bin value to a count value
//used in afterpulse tests
inline static void correctCount(int &count, int next);


static bool checkq(const Spsc_int &x);
static bool checkqg(const Spsc_int &x);
static bool checkqe(const Spsc_int &x);

void writeInfoAfterNa(vector<Spsc_int>& q, Spsc_time& t, atomic<bool>* done, string fileName, const HeaderInfoAfter& ha, const HeaderInfoGen& hg, const Messages& message){
  //assert(q.size() < 20);
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double, std::milli> elapsed;
  ofstream out;
  out.open(fileName + ".txt");
  out << hg << ha;
  out << " Time (ms)   ";
  for (int i = 0, leni = ha.readoutLines.size(); i < leni; ++i){
    out << "Count " << left << setw(13) << ha.readoutLines[i];
  }
  out << endl;

  //should use something like std bind here
  while (any_of(q.begin(), q.end(), checkq) || t.read_available() == 0){}

  this_thread::sleep_for(chrono::microseconds(1000));

  int count[20], prev[20];
  for (int i = 0, leni = q.size(); i < leni; ++i){ count[i] = prev[i] = q[i].front(); }
  for (int i = q.size(); i < 20; ++i){ count[i] = prev[i] = 0; }

  ////////////////////////////////////////////////////
  string tempst;
  tempst = fileName + ".root";
  TFile f(tempst.c_str(), "RECREATE");
  tempst = "TTree for panel " + hg.panelName + " filled with " + hg.gas + " at " + to_string(ha.voltage) + " (V) AP";
  TTree tr("ap", tempst.c_str());
  //add the count variables
  Double_t tstamp;
  tr.Branch("tstamp", &tstamp, "tstamp/D");
  tr.Branch("data", count, "data[20]/I");

  //add all info from the general header
  char tempPanel[200], tempSource[200], tempGas[200], tempSetup[200], tempRO[200], tempHV[200], tempTrigHV[200], tempTrigRO[200];
  Double_t tempPress, tempDiscThr, tempQuench, tempNumHv, tempNumRo, tempAttenRo, tempAttenHV;
  Long_t runNumber;
  strcpy(tempPanel, hg.panelName.c_str());
  tr.Branch("panel", tempPanel, "panel[200]/C");
  strcpy(tempSource, hg.sourceName.c_str());
  tr.Branch("source", tempSource, "source[200]/C");
  strcpy(tempSetup, hg.sourceConfig.c_str());
  tr.Branch("sourceSetup", tempSetup, "sourceSetup[200]/C");
  strcpy(tempGas, hg.gas.c_str());
  tr.Branch("gasmix", tempGas, "gasmix[200]/C");
  tempPress = hg.pressure;
  tr.Branch("press", &tempPress, "press/D");
  tempDiscThr = hg.discThresh;
  tr.Branch("disThr", &tempDiscThr, "disThr/D");
  tempQuench = hg.quench;
  tr.Branch("quench", &tempQuench, "quench/D");
  tempNumRo = hg.numRO;
  tr.Branch("nch_ro", &tempNumRo, "nch_ro/s");
  strcpy(tempRO, hg.roLines.c_str());
  tr.Branch("line_ro", tempRO, "line_ro[200]/C");
  strcpy(tempTrigRO, hg.triggerRO.c_str());
  tr.Branch("trg_ro", tempTrigRO, "trg_ro[200]/C");
  tempAttenRo = hg.attenRO;
  tr.Branch("dB_ro", &tempAttenRo, "dB_ro/s");
  tempNumHv = hg.numHV;
  tr.Branch("nch_hv", &tempNumHv, "nch_hv/s");
  strcpy(tempHV, hg.linesHV.c_str());
  tr.Branch("line_hv", tempHV, "line_hv[200]/C");
  strcpy(tempTrigHV, hg.triggerHV.c_str());
  tr.Branch("trg_hv", tempTrigHV, "trg_hv[200]/C");
  tempAttenHV = hg.attenHV;
  tr.Branch("dB_hv", &tempAttenHV, "dB_hv/s");
  runNumber = hg.runNumber;
  tr.Branch("runNumber", &runNumber, "runNumber/L");
  //add all info from the after-pulse header
  Double_t tempVolt = ha.voltage;
  Int_t tempPix = ha.numPixels;
  Int_t numReadings = ha.numReadings;
  Int_t readoutLines[20];
  for (int i = 0, leni = ha.readoutLines.size(); i < leni; ++i){
    readoutLines[i] = ha.readoutLines[i];
  }
  for (int i = ha.readoutLines.size(); i < 20; ++i){
    readoutLines[i] = 0;
  }
  tr.Branch("hvVal", &tempVolt, "hvVal/D");
  tr.Branch("num_pix", &tempPix, "num_pix/I");
  tr.Branch("readoutLines", readoutLines, "readoutLines[20]/I");
  tr.Branch("numReadings", numReadings, "numReadings/I");
  //add all info from the message  
  /*int voltage;
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

	std::vector<int> pixX, pixY;*/
  Int_t time, numPix, maxOffsetX, maxOffsetY, maxStepX, maxStepY, motorStepX, motorStepY, voltageStart, voltageStep, voltageEnd, row, column;
  char runType[200];
  time = message.time;
  tr.Branch("time", &time, "hvVal/I");
  numPix = message.numPix;
  tr.Branch("numPix", &numPix, "numPix/I");
  maxOffsetX = message.maxOffsetX;
  tr.Branch("maxOffsetX", &maxOffsetX, "maxOffsetX/I");
  maxOffsetY = message.maxOffsetY;
  tr.Branch("maxOffsetY", &maxOffsetY, "maxOffsetY/I");
  maxStepX = message.maxStepX;
  tr.Branch("maxStepX", &maxStepX, "maxStepX/I");
  maxStepY = message.maxStepY;
  tr.Branch("maxStepY", &maxStepY, "maxStepY/I");
  motorStepX = message.motorstepx;
  tr.Branch("motorStepX", &motorStepX, "motorStepX/I");
  motorStepY = message.motorstepy;
  tr.Branch("motorStepY", &motorStepY, "motorStepY/I");
  voltageStart = message.voltageStart;
  tr.Branch("voltageStart", &voltageStart, "voltageStart/I");
  voltageStep = message.voltageStep;
  tr.Branch("voltageStep", &voltageStep, "voltageStep/I");
  voltageEnd = message.voltageEnd;
  tr.Branch("voltageEnd", &voltageEnd, "voltageEnd/I");
  row = message.row;
  tr.Branch("row", &row, "row/I");
  column = message.column;
  tr.Branch("column", &column, "column/I");
  strcpy(runType, message.runtype.c_str());
  tr.Branch("runType", &runType, "runType[200]/C");
  /////////////////////////////////////////////////////
  HighResClock::time_point first = t.front();
  elapsed = t.front() - first;
  tstamp = elapsed.count();
  out << setw(9) << fixed << setprecision(2) << elapsed.count();
  for (int i = 0, leni = q.size(); i < leni; ++i){
    out << "    " << setw(13) << count[i];
  }
  out << endl;

  for (auto &x : q){ x.pop(); }
  t.pop();

  tr.Fill();
  //loop until data is done being taken
  while (!*done){
    this_thread::sleep_for(chrono::microseconds(10));
    while (all_of(q.begin(), q.end(), checkqg) && t.read_available() > 0){
      for (int i = 0, leni = q.size(); i < leni; ++i){
        prev[i] = count[i];
        correctCount(count[i], q[i].front());
      }
      for (int i = 0, leni = q.size(); i < leni; ++i){
        if (count[i] > prev[i]){
          ////////////above this is fine
          elapsed = t.front() - first;
          tstamp = elapsed.count();
          out << setw(9) << fixed << setprecision(2) << elapsed.count();
          for (int j = 0, lenj = q.size(); j < lenj; ++j){
            out << "    " << setw(13) << count[j];
          }
          out << endl;
          tr.Fill();
          break;

        }
      }
      for (auto &x : q){x.pop();}
      t.pop();
    }
  }
  //finish writing data
  this_thread::sleep_for(chrono::microseconds(1000));
  while (!t.empty() && !any_of(q.begin(), q.end(), checkqe)){
    for (int i = 0, leni = q.size(); i < q.size(); ++i){
      prev[i] = count[i];
      correctCount(count[i], q[i].front());
    }
    for (int i = 0, leni = q.size(); i < leni; ++i){
      if (count[i] > prev[i]){
        elapsed = t.front() - first;
        tstamp = elapsed.count();
        out << setw(9) << fixed << setprecision(2) << elapsed.count();
        for (int j = 0, lenj = q.size(); j < lenj; ++j){
          out << "    " << setw(13) << count[j];
        }
        out << endl;
        tr.Fill();
        break;
      }
      for (auto &x : q){ x.pop(); }
      t.pop();
    }
  }
  tr.Write();
  f.Save();

}

void readFromPixAfterN(const vector<int>& pix, atomic<bool>* done, atomic<bool> *control, vector<Spsc_int> &q, Spsc_time &t, WeinerCounter* nim, int numSamples){
	//assert(q->size() == pix.size());
	size_t size = pix.size();
	nim->resetAll();
	for (int i = 0; *control && i < numSamples; ++i){
		t.push(HighResClock::now());
		for (size_t j = 0; j < size; ++j){
			q[j].push(nim->readCounter(pix[j]));
		}
	}
	*done = true;
}

void readFromPixAfterNInf(const vector<int>& pix, atomic<bool>* done, atomic<bool> *control, vector<Spsc_int> &q, Spsc_time &t, WeinerCounter* nim){
	//assert(q->size() == pix.size());
    size_t size = pix.size();
	nim->resetAll();
	while(*control){
		t.push(HighResClock::now());
		for (size_t j = 0; j < size; ++j){
			q[j].push(nim->readCounter(pix[j]));
		}
	}
	*done = true;
}

static string initWeinerFile(HeaderInfoGen *header, string const & runType, string const & runName, double voltage){
  static const string DEFAULT_DIR = ".\\CollectedData\\";
  time_t tm = time(nullptr);
  stringstream sstream;
  sstream << fixed;
  sstream.precision(2);
  sstream << DEFAULT_DIR;
  CreateDirectory(sstream.str().c_str(), NULL);
  sstream << header->panelName << "\\";  
  CreateDirectory(sstream.str().c_str(), NULL);
  sstream << header->gas << "\\";
  CreateDirectory(sstream.str().c_str(), NULL);
  sstream << header->pressure << "torr\\";
  CreateDirectory(sstream.str().c_str(), NULL);
  sstream << runType << "\\";
  CreateDirectory(sstream.str().c_str(), NULL);
  if (runName != ""){
    sstream << runName << "\\";
    CreateDirectory(sstream.str().c_str(), NULL);
  }
  sstream << header->panelName << "_" << header->gas << "_" << header->pressure << "torr_" << voltage << "V" << "_" << tm << "_AP";
  return sstream.str();
}


void doWeinerCount(WeinerCounter *nim, string runName, HeaderInfoGen* header, Messages* message, Readout* readout, Voltage* volt, atomic<bool> *run){ 
  string runFullName = initWeinerFile(header, message->runtype, runName, message->voltage);
  vector<int> activeReadout;
  for (size_t i = 0; i < readout->active.size(); ++i){
    if (readout->active[i]){
      activeReadout.push_back(i + 1);
    }
  }
  int numSamples = message->time * 1000 / NIM_MS_PER_CHANNEL_MEASUREMENT / activeReadout.size();
  HeaderInfoAfter ha;
  ha.numPixels = activeReadout.size();
  ha.numReadings = numSamples;
  ha.voltage = message->voltage;
  ha.readoutLines = activeReadout;
  //get the number of samples for this number of lines
  vector <Spsc_int> q(activeReadout.size());
  Spsc_time t;
  atomic<bool> done = false;
  atomic<bool> control = false;
  volt->setVoltage(message->voltage);
  volt->turnOn();
  thread t2(writeInfoAfterNa, ref(q), ref(t), &done, runFullName, ha, *header, *message);
  readFromPixAfterN(activeReadout, &done, run, q, t, nim, numSamples);
  if (t2.joinable()){
    t2.join();
  }
  volt->turnOff();
}

void doWeinerCountInf(WeinerCounter *nim, string runName, HeaderInfoGen* header, Messages* message, Readout* readout, Voltage* volt, atomic<bool> *run){
  string runFullName = initWeinerFile(header, message->runtype, runName, message->voltage);
  vector<int> activeReadout;
  for (size_t i = 0; i < readout->active.size(); ++i){
    if (readout->active[i]){
      activeReadout.push_back(i + 1);
    }
  }
  int numSamples = -1 * 1000 / NIM_MS_PER_CHANNEL_MEASUREMENT / activeReadout.size();
  HeaderInfoAfter ha;
  ha.numPixels = activeReadout.size();
  ha.numReadings = numSamples;
  ha.voltage = message->voltage;
  ha.readoutLines = activeReadout;
  //get the number of samples for this number of lines
  vector <Spsc_int> q(activeReadout.size());
  Spsc_time t;
  atomic<bool> done = false;
  atomic<bool> control = false;
  volt->setVoltage(message->voltage);
  volt->turnOn();
  thread t2(writeInfoAfterNa, ref(q), ref(t), &done, runFullName, ha, *header, *message);
  readFromPixAfterNInf(activeReadout, &done, run, q, t, nim);
  if (t2.joinable()){
    t2.join();
  }
  volt->turnOff();
}

void measureLines(WeinerCounter* nim, double time, double& actualTime, vector<int>& count, double intervalLength){

  count.resize(20);
  for (int i = 0; i < 20; ++i){
    count[i] = 0;
  }
  int numSamps = ceil(time / intervalLength);
  chrono::duration<int, milli> dur((int)(intervalLength * 1000) - 29);
  HighResClock::time_point t, start;
  std::chrono::duration<double> elapsed;
  nim->resetAll();
  start = HighResClock::now();
  this_thread::sleep_for(dur);
  for (int i = 0; i < numSamps; ++i){
    t = HighResClock::now();
    count[0] = nim->readCounter(1);
    count[1] = nim->readCounter(2);
    count[2] = nim->readCounter(3);
    count[3] = nim->readCounter(4);
    count[4] = nim->readCounter(5);
    count[5] = nim->readCounter(6);
    count[6] = nim->readCounter(7);
    count[7] = nim->readCounter(8);
    count[8] = nim->readCounter(9);
    count[9] = nim->readCounter(10);
    count[10] = nim->readCounter(11);
    count[11] = nim->readCounter(12);
    count[12] = nim->readCounter(13);
    count[13] = nim->readCounter(14);
    count[14] = nim->readCounter(15);
    count[15] = nim->readCounter(16);
    count[16] = nim->readCounter(17);
    count[17] = nim->readCounter(18);
    count[18] = nim->readCounter(19);
    count[19] = nim->readCounter(20);
    this_thread::sleep_for(dur);
  }
  elapsed = t - start;
  actualTime = elapsed.count();
}

double findRate(WeinerCounter* nim, int lineNum, double time, double intervalLength){
  if (lineNum < 1 || lineNum > 20){
    return -1;
  }
  array<int, 20> count;
  for (int i = 0; i < 20; ++i){
    count[i] = 0;
  }
  int numSamps = ceil(time / intervalLength);
  chrono::duration<int, milli> dur((int)(intervalLength * 1000) - 29);
  HighResClock::time_point t, start;
  std::chrono::duration<double> elapsed;
  nim->resetAll();
  start = HighResClock::now();
  this_thread::sleep_for(dur);
  for (int i = 0; i < numSamps; ++i){
    t = HighResClock::now();
    count[0] = nim->readCounter(1);
    count[1] = nim->readCounter(2);
    count[2] = nim->readCounter(3);
    count[3] = nim->readCounter(4);
    count[4] = nim->readCounter(5);
    count[5] = nim->readCounter(6);
    count[6] = nim->readCounter(7);
    count[7] = nim->readCounter(8);
    count[8] = nim->readCounter(9);
    count[9] = nim->readCounter(10);
    count[10] = nim->readCounter(11);
    count[11] = nim->readCounter(12);
    count[12] = nim->readCounter(13);
    count[13] = nim->readCounter(14);
    count[14] = nim->readCounter(15);
    count[15] = nim->readCounter(16);
    count[16] = nim->readCounter(17);
    count[17] = nim->readCounter(18);
    count[18] = nim->readCounter(19);
    count[19] = nim->readCounter(20);
    this_thread::sleep_for(dur);
  }
  elapsed = t - start;
  return count[lineNum-1] / elapsed.count();
}

void doLineScan(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, Readout* readout, HeaderInfoGen* header, atomic<bool>* run){
	string path = ".\\CollectedData\\";
	string runName;
	ofstream log;
	vector<string> pix;
	pix.push_back("1");
	int motbeginy = 0, motendy = message->maxOffsetY, motstepy = message->maxStepY;
	int motbeginx = 0, motendx = message->maxOffsetX, motstepx = message->maxStepX;
	int starting = message->voltageStart;
	int stop = message->voltageEnd;
	int duration = message->time;
	//int num;
	//vector<int> x;
	//vector<int> y;
	//double freq;
	int step = message->voltageStep;
	char tempc = 25;
	string temp;
	//vector<string> pix;

	time_t t = time(nullptr);
	// TODO: add identifier to first directory, possibly panel name?
	CreateDirectory(path.c_str(), NULL);
	runName = path + "\\";
	runName += header->panelName + "_" + to_string(t) + "\\";// +"_" + header->gas + "_" + to_string((int)header->pressure) + "_" + to_string(t) + "\\";
	CreateDirectory(runName.c_str(), NULL);
	//runName = path + header->gas + "\\";
	//CreateDirectory(runName.c_str(), NULL);
	runName += to_string((int)header->pressure);
	runName += +"torr\\";
	CreateDirectory(runName.c_str(), NULL);
	//runName += header->panelName + "_" + to_string(t) + "\\";// +"_" + header->gas + "_" + to_string((int)header->pressure) + "_" + to_string(t) + "\\";
	//CreateDirectory(runName.c_str(), NULL);
	log.open(runName + "log.txt", ofstream::ate);
	runName += "LineScan\\";
	CreateDirectory(runName.c_str(), NULL);
	log << "Intitalized Line Scan Run" << endl;
	log << "Starting: " << starting << endl;
	log << "Stop: " << stop << endl;
	log << "Step Size: " << step << endl;
	log << "Interval Duration: " << message->time << endl;
	log << "Sampling Frequency: " << message->frequency << endl;
	
	log << "Turning On High Voltage" << endl;
	volt->setVoltage(0);
	volt->turnOn();
	string fullFile = "test.txt";
		if (header->sourceConfig == "Dynamic"){
			volt->setVoltage(starting);
			volt->turnOn();
			log << "Going to home" << endl;
			mot->goZero();
			//mot->stepMotor(2, -motstepy);
			if (motstepx != 0){
				mot->stepMotor(1, -motstepx);
			}
			//mot->stepMotor(2, motstep);
			//mot->mapPixel(fullFile, nim, 1, 1, duration, 0, motend, 0, motstep);
			if (motstepy == 0){
				motbeginy = motendy;
				step = 10000;
			}

			int stepsiny = 0;

			for (int i = motbeginx; i <= motendx && *run == true; i += motstepx){
				mot->stepMotor(2, -stepsiny*motendy);
				mot->stepMotor(2, -motstepy);
				mot->stepMotor(1, motstepx); 

				log << "At " << i << "steps x" << ", ";
        //loop over y
				for (int j = motbeginy; j <= motendy && *run == true; j += motstepy){	
					stepsiny=1;
					mot->stepMotor(2, motstepy);
					log << i << "steps y" << endl;

					for (int k = starting; k <= stop && *run == true; k += step){
						log << "Setting Voltage to: " << k << endl;
						log << "Begin Counting" << endl;
            time_t tm = time(nullptr);
            message->voltage = k;
            doWeinerCount(nim, message->runtype + "_" + to_string(tm), header, message, readout, volt, run);
            log << "Finished Counting" << endl;
					}
				}
			}
		}

	log << "Turning off High Voltage" << endl;
	volt->turnOff();
	mot->goZero();
	log << "Voltage Scan Completed" << endl;
	log.close();
	*run = false;
}

string createFileName(HeaderInfoGen *header, Messages* message, time_t t){
	string runName;
	runName = ".\\CollectedData\\";
	// TODO: add identifier to first directory, possibly panel name?
	CreateDirectory(runName.c_str(), NULL);
	//runName = path + header->gas + "\\";
	//CreateDirectory(runName.c_str(), NULL);
	runName += to_string((int)header->pressure);
	runName += +"Torr\\";
	CreateDirectory(runName.c_str(), NULL);
	runName += header->panelName + "_" + to_string(t) + "\\";// +"_" + header->gas + "_" + to_string((int)header->pressure) + "_" + to_string(t) + "\\";
	CreateDirectory(runName.c_str(), NULL);
	runName += message->runtype;
	CreateDirectory(runName.c_str(), NULL);
	return runName;
}

void doAfterScanGraphMultiFree(WeinerCounter *nim, HeaderInfoGen* header, Voltage *volt, Messages* message, Readout* readout, atomic<bool>* run){
  vector<int> activeReadout;
  for (size_t i = 0; i < readout->active.size(); ++i){
    if (readout->active[i]){
      activeReadout.push_back(i + 1);
    }
  }
  string scanName = "Scan_" + header->panelName + "_" + header->gas + "_" + to_string(header->pressure) + "torr_" + to_string(time(nullptr));
  for (double i = message->voltageStart; i <= message->voltageEnd && run; i += message->voltageStep){
    doWeinerCount(nim, scanName, header, message, readout, volt, run);
  }
  return;
}



void doHexScanX(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, Readout* readout, HeaderInfoGen* header, atomic<bool>* run){
	string path = ".\\CollectedData\\";
	string runName;
	ofstream log;
	vector<string> pix;
	pix.push_back("1");
	int motbeginy = 0, motendy = message->maxOffsetY, motstepy = message->maxStepY;
	int motbeginx = 0, motendx = message->maxOffsetX, motstepx = message->maxStepX;
	int starting = message->voltageStart;
	int stop = message->voltageEnd;
	int duration = message->time;

	int step = message->voltageStep;
	char tempc = 25;
	string temp;

	time_t t = time(nullptr);
	CreateDirectory(path.c_str(), NULL);
	runName = path + "\\";
	runName += header->panelName + "_" + to_string(t) + "\\";
	CreateDirectory(runName.c_str(), NULL);
	runName += to_string((int)header->pressure);
	runName += +"torr\\";
	CreateDirectory(runName.c_str(), NULL);
	log.open(runName + "log.txt", ofstream::ate);
	runName += "HexScanX\\";
	CreateDirectory(runName.c_str(), NULL);
	log << "Intitalized Line Scan Run" << endl;
	log << "Starting: " << starting << endl;
	log << "Stop: " << stop << endl;
	log << "Step Size: " << step << endl;
	log << "Interval Duration: " << message->time << endl;
	log << "Sampling Frequency: " << message->frequency << endl;

	log << "Turning On High Voltage" << endl;
	volt->setVoltage(0);
	volt->turnOn();
	string fullFile = "test.txt";
	if (header->sourceConfig == "Dynamic")
	{
		int row;
		int column = 0;
		volt->setVoltage(starting);
		volt->turnOn();
		log << "Going to home" << endl;
		mot->goZero();
		if (motstepx != 0)
		{
			mot->stepMotor(1, -motstepx);
		}
		if (motstepy == 0)
		{
			motbeginy = motendy;
			step = 10000;
		}

		int stepsiny = 0;

		for (int i = motbeginx; i <= motendx && *run == true; i += motstepx)
		{
			++column;
			//mot->stepMotor(2, -stepsiny*motendy);
			mot->goZeroY();
			mot->stepMotor(2, -motstepy);

			mot->stepMotor(1, motstepx);

			if (column % 2 == 0 && column != 1)
			{
				//mot->stepMotor(2, motstepy);
				mot->stepMotor(2, motstepy/2); // step motor on even columns to line up with hex
				//motendy = message->maxOffsetY;// -motstepy;
			}
			else if (column % 2 == 1 && column != 1)
			{
				motendy = message->maxOffsetY;
				//mot->stepMotor(2, -motstepy / 2);
				//mot->stepMotor(2, motstepy);
			}

			log << "At " << i << " steps x" << ", ";

			for (int j = motbeginy; j <= motendy && *run == true; j += motstepy) // loop y
			{
				stepsiny = 1;
				mot->stepMotor(2, motstepy);
				log << i << " steps y" << endl;

				for (int k = starting; k <= stop && *run == true; k += step)
				{

					log << "Setting Voltage to: " << k << endl;
					volt->setVoltage(k);
					log << "Begin Counting" << endl;
          time_t tm = time(nullptr);
          doWeinerCount(nim, "doHexScanX_" + to_string(tm), header, message, readout, volt, run);
          log << "Finished Counting" << endl;

				}
			}
		}
	}

	log << "Turning off High Voltage" << endl;
	volt->turnOff();
	mot->goZero();
	log << "Voltage Scan Completed" << endl;
	log.close();
	*run = false;
}

void doXYScan(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, Readout* readout, HeaderInfoGen* header, atomic<bool>* run){
	try{
		string path = ".\\CollectedData\\";
		string runName;
		ofstream log;
		vector<string> pix;
		pix.push_back("1");
		int motbeginy = 0, motendy = message->maxOffsetY, motstepy = message->maxStepY;
		int motbeginx = 0, motendx = message->maxOffsetX, motstepx = message->maxStepX;
		int starting = message->voltageStart;
		int stop = message->voltageEnd;
		int duration = message->time;

		int step = message->voltageStep;
		char tempc = 25;
		string temp;

		time_t t = time(nullptr);
		CreateDirectory(path.c_str(), NULL);
		runName = path + "\\";
		runName += header->panelName + "_" + to_string(t) + "\\";
		CreateDirectory(runName.c_str(), NULL);
		runName += to_string((int)header->pressure);
		runName += +"torr\\";
		CreateDirectory(runName.c_str(), NULL);
		log.open(runName + "log.txt", ofstream::ate);
		runName += "HexScanX\\";
		CreateDirectory(runName.c_str(), NULL);
		log << "Intitalized Line Scan Run" << endl;
		log << "Starting: " << starting << endl;
		log << "Stop: " << stop << endl;
		log << "Step Size: " << step << endl;
		log << "Interval Duration: " << message->time << endl;
		log << "Sampling Frequency: " << message->frequency << endl;

		log << "Turning On High Voltage" << endl;
		volt->setVoltage(0);
		volt->turnOn();
		string fullFile = "test.txt";
		if (header->sourceConfig == "Dynamic")
		{
			int row;
			int column = 0;
			volt->setVoltage(starting);
			volt->turnOn();
			log << "Going to home" << endl;
			mot->goZero(); 
			log << to_string(mot->getAbsolutePositionX()) << " abs X     " << to_string(mot->getAbsolutePositionY()) << " abs Y" << endl;
			//Sleep(4);
			mot->stepMotor(1, -motstepx);
			log << mot->getAbsolutePositionX() << " absolute X" << endl;
			if (motstepy == 0)
			{
				motbeginy = motendy;
				step = 10000;
			}

			int stepsiny = 0;
			bool firstLine = true;
			for (int i = motbeginx; i <= motendx && *run == true; i += motstepx)
			{

					mot->goZeroY();
					//mot->stepMotorNoWait(2, -motendy);
					//this_thread::sleep_for(chrono::milliseconds(10000));
					log << (int)mot->getAbsolutePositionY() << "abs Y" << endl;
					log << "returned to y 0" << endl;

				++column;
				//Sleep(4);

				mot->stepMotorNoWait(2, -motstepy);
				this_thread::sleep_for(chrono::milliseconds(1000));
				log << (int)mot->getAbsolutePositionY() << " abs Y" << endl;

				//Sleep(4);
				mot->stepMotorNoWait(1, motstepx);
				this_thread::sleep_for(chrono::milliseconds(1000));
				log << (int)mot->getAbsolutePositionX() << " abs X" << endl;

				log << "At " << i << " steps x" << ", ";
				

				for (int j = motbeginy; j <= motendy && *run == true; j += motstepy) // loop y
				{
					stepsiny = 1;
					mot->stepMotorNoWait(2, motstepy);
					this_thread::sleep_for(chrono::milliseconds(200));
					int posY = mot->getAbsolutePositionY();

					log << j << " steps y" << endl;
					log << posY << " abs Y" << endl;

					for (int k = starting; k <= stop && *run == true; k += step)
					{

						log << "Setting Voltage to: " << k << endl;
						//volt->setVoltage(k);
						log << "Begin Counting" << endl;
            time_t tm = time(nullptr);
            doWeinerCount(nim, "XYScan_" + to_string(tm), header, message, readout, volt, run);
            log << "Finished Counting" << endl;
					}
					//mot->stepMotor(2, -motendy);
				}
			}
		}

		log << "Turning off High Voltage" << endl;
		volt->turnOff();
		mot->goZero();
		log << "Voltage Scan Completed" << endl;
		log.close();
		*run = false;
	}
	catch (bad_alloc e){
		cout << "found exception " << e.what() << endl;
	}
}

static bool checkq(const Spsc_int &x){
  return x.read_available() == 0;
}
static bool checkqg(const Spsc_int &x){
  return x.read_available() > 0;
}
static bool checkqe(const Spsc_int &x){
  return x.read_available() == 0;
}
inline static void correctCount(int &count, int next){
  int temp = count % OVER;
  if (temp < next){
    count += next - temp;
  }
  else if (temp > next){
    count += OVER + next - temp;
  }
}