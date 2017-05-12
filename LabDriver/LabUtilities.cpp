#include "LabUtilities.h"
#include <iomanip>
#include <functional>
//#include "LabView.h"
#include "headers.h"


//extern atomic<bool> control;


//Dunction used for converting weiner counter bin value to a count value
//used in afterpulse tests
inline static void correctCount(int &count, int next);


static bool checkq(const Spsc_int &x){
  return x.read_available() == 0;
}
static bool checkqg(const Spsc_int &x){
  return x.read_available() > 0;
}
static bool checkqe(const Spsc_int &x){
  return x.read_available() == 0;
}
void writeInfoAfterN(vector<Spsc_int>& q, Spsc_time& t, atomic<bool>* done, atomic<bool> *control, string fileName, const HeaderInfoAfter& ha, const HeaderInfoGen& hg){
  //assert(q.size() < 20);
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double, std::milli> elapsed;
  ofstream out;
  out.open(fileName + ".txt");
  out << hg << ha;
  out << " Time (ms)   ";
  for (int i = 0, leni = ha.pixels.size(); i < leni; ++i){
    out <<"Count "<< left << setw(13) << ha.pixels[i];
  }
   out<<endl;
  
  //should use something like std bind here
  while (any_of(q.begin(), q.end(), checkq) || t.read_available() == 0){}
  
  this_thread::sleep_for(chrono::microseconds(1000));
  
  int count[20],prev[20];
  for (int i = 0, leni = q.size(); i < leni; ++i){ count[i] = prev[i] = q[i].front(); }
  for (int i = q.size(); i < 20; ++i){ count[i] = prev[i] = 0; }
  
  ////////////////////////////////////////////////////
  string tempst;
  tempst = fileName + ".root";
  TFile f(tempst.c_str(), "RECREATE");
  tempst = "TTree for panel " + hg.panelName + " filled with " + hg.gas + " at " + to_string(ha.voltage) + " (V) AP";
  TTree tr("ap", tempst.c_str());
  char  tempPanel[200], tempSource[200], tempGas[200], tempSetup[200], tempRO[200], tempHV[200], tempTrigHV[200], tempTrigRO[200];
  strcpy(tempPanel, hg.panelName.c_str());
  strcpy(tempSource, hg.sourceName.c_str());
  strcpy(tempGas, hg.gas.c_str());
  strcpy(tempSetup, hg.sourceConfig.c_str());
  strcpy(tempRO, hg.roLines.c_str());
  strcpy(tempHV, hg.linesHV.c_str());
  strcpy(tempTrigHV, hg.triggerHV.c_str());
  strcpy(tempTrigRO, hg.triggerRO.c_str());
  Double_t tstamp, tempPress, tempVolt, tempDiscThr, tempQuench, tempNumHv, tempNumRo, tempAttenRo, tempAttenHV;
  tempPress = hg.pressure;
  tempVolt = ha.voltage;
  tempDiscThr = hg.discThresh;
  tempQuench = hg.quench;
  tempNumHv = hg.numHV;
  tempNumRo = hg.numRO;
  tempAttenRo = hg.attenRO;
  tempAttenHV = hg.attenHV;
  Int_t pixX[20];
  Int_t pixY[20];
  char holding[30];
  for (int i = 0, len = ha.pixels.size(); i < len; ++i){
    strcpy(holding, ha.pixels[i].c_str());
    pixX[i] = atoi(strtok(holding, "-"));
    pixY[i] = atoi(strtok(nullptr, "-"));
  }
  for (int i = ha.pixels.size(); i < 20; ++i){
    pixX[i] = 0;
    pixY[i] = 0;
  }
  Int_t tempSamp = ha.numReadings;
  Int_t tempPix = ha.numPixels;
  tr.Branch("panel", tempPanel, "panel[200]/C");
  tr.Branch("source", tempSource, "source[200]/C");
  tr.Branch("sourceSetup", tempSetup, "sourceSetup[200]/C");
  tr.Branch("gasmix", tempGas, "gasmix[200]/C");
  tr.Branch("press", &tempPress, "press/D");
  tr.Branch("hvVal", &tempVolt, "hvVal/D");
  tr.Branch("disThr", &tempDiscThr, "disThr/D");
  tr.Branch("quench", &tempQuench, "quench/D");
  tr.Branch("trg_ro", tempTrigRO, "trg_ro[200]/C");
  tr.Branch("dB_ro", &tempAttenRo, "dB_ro/s");
  tr.Branch("nch_ro", &tempNumRo, "nch_ro/s");
  tr.Branch("line_ro", tempRO, "line_ro[200]/C");
  tr.Branch("trg_hv", tempTrigHV, "trg_hv[200]/C");
  tr.Branch("dB_hv", &tempAttenHV, "dB_hv/s");
  tr.Branch("nch_hv", &tempNumHv, "nch_hv/s");
  tr.Branch("line_hv", tempHV, "line_hv[200]/C");
  tr.Branch("tstamp", &tstamp, "tstamp/D");
  tr.Branch("data", count, "data[20]/i");
  tr.Branch("samps", &tempSamp, "samps/i");
  tr.Branch("num_pix", &tempPix, "num_pix/i");
  tr.Branch("pixX", pixX, "pixX[20]/i");
  tr.Branch("pixY", pixY, "pixY[20]/i");
  /////////////////////////////////////////////////////
  HighResClock::time_point first = t.front();
  elapsed = t.front() - first;
  tstamp = elapsed.count();
  out << setw(9) << fixed << setprecision(2) << elapsed.count();
  for (int i = 0, leni = q.size(); i < leni; ++i){
    out << "    " << setw(13) << count[i];
  }
  out << endl;
  
  //this should be changed to a for_each wtih memfn
  //for_each(q.begin(), q.end(), mem_fn(&Spsc_int::pop));
  for (auto &x : q){
    x.pop();
  }
  
  t.pop();
  tr.Fill();
  while (!*done){
    this_thread::sleep_for(chrono::microseconds(10));
    while (all_of(q.begin(), q.end(), checkqg)  && t.read_available() > 0){
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
      for (auto &x : q){
        x.pop();
      }
      t.pop();
    }
  }
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
      for (auto &x : q){
        x.pop();
      }
      t.pop();
    }
  }
  tr.Write();
  f.Save();
  
}

//////////////////////
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

/////////////////////////////

inline static void correctCount(int &count, int next){
  int temp = count % OVER;
  if (temp < next){
    count += next - temp;
  }
  else if (temp > next){
    count += OVER + next - temp;
  }
}
void doWeinerCount(WeinerCounter *nim, double time, double sampleLength, double volt, const HeaderInfoGen &hg, const vector<string> &activePix, string fileName, int x, int y){
  HeaderInfoCounter hc;
  hc.pixels = activePix;
  hc.samplingLength = sampleLength;
  hc.timeLength = time;
  hc.voltage = volt;
  boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> q;
  Spsc_time t;
  atomic<bool> done = false;
  thread t2(writeWeinerCount, &q, &t, &done, fileName, hc, hg, x, y);
  readWeinerCount(&q, &t, &done, nim, time, sampleLength);
  t2.join();
}
static void writeWeinerCount(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q, Spsc_time *t, atomic<bool> *done, string fileName, const HeaderInfoCounter &ha, const HeaderInfoGen &hg, int x, int y){
  //cimg_library::CImg<unsigned char> *img;
  //cimg_library::CImgDisplay disp;
  int imgnum = 0;
  HGraph gr;
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double, std::milli> elapsed;
  ofstream out;
  string outFileName = fileName + ".txt";
  out.open(outFileName.c_str());
  string temp;
  out << hg << ha;
  time_t tm = time(nullptr);
  string tmp;

  tmp = "Start run: " + to_string(tm);
  out << tmp << endl;
  out << "Time (s)    ";
  for (int i = 0; i < 20; ++i){
    temp = "channel " + to_string(i);
    out << left << setw(19) << temp;
  }
  out << endl;
  while (q->read_available() == 0 || t->read_available() == 0){}
  while (q->read_available() == 0 || t->read_available() == 0){}
  this_thread::sleep_for(chrono::microseconds(1000));
  int count[20];
  for (int i = 0; i < 20; ++i){
    count[i] = q->front()[i];
  }
  int prev[20];
  for (int i = 0; i < 20; ++i){
    prev[i] = count[i];
  }
  string tempst;
  tempst = fileName;
  tempst += ".root";
  TFile f(tempst.c_str(), "RECREATE");
  tempst = "TTree for panel " + hg.panelName + " filled with " + hg.gas + " at " + to_string(ha.voltage) + " (V) Weiner";
  TTree tr("w", tempst.c_str());
  char tempPanel[200], tempSource[200], tempGas[200], tempSetup[200], tempRO[200], tempHV[200], tempTrigHV[200], tempTrigRO[200];
  strcpy(tempPanel, hg.panelName.c_str());
  strcpy(tempSource, hg.sourceName.c_str());
  strcpy(tempGas, hg.gas.c_str());
  strcpy(tempSetup, hg.sourceConfig.c_str());
  strcpy(tempRO, hg.roLines.c_str());
  strcpy(tempHV, hg.linesHV.c_str());
  strcpy(tempTrigHV, hg.triggerHV.c_str());
  strcpy(tempTrigRO, hg.triggerRO.c_str());

  char tempMotX = x;
  char tempMotY = y;
  char startTime = tm;
  Double_t tstamp, tempPress, tempVolt, tempDiscThr, tempQuench, tempNumHv, tempNumRo, tempAttenRo, tempAttenHV;
  int tempPix = 20;
  int pixX[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  int pixY[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  tempPress = hg.pressure;
  tempVolt = ha.voltage;
  tempDiscThr = hg.discThresh;
  tempQuench = hg.quench;
  tempNumHv = hg.numHV;
  tempNumRo = hg.numRO;
  tempAttenRo = hg.attenRO;
  tempAttenHV = hg.attenHV;
  tr.Branch("panel", tempPanel, "panel[200]/C");
  tr.Branch("source", tempSource, "source[200]/C");
  tr.Branch("sourceSetup", tempSetup, "sourceSetup[200]/C");
  tr.Branch("gasmix", tempGas, "gasmix[200]/C");
  tr.Branch("press", &tempPress, "press/D");
  tr.Branch("hvVal", &tempVolt, "hvVal/D");
  tr.Branch("disThr", &tempDiscThr, "disThr/D");
  tr.Branch("quench", &tempQuench, "quench/D");
  tr.Branch("trg_ro", tempTrigRO, "trg_ro[200]/C");
  tr.Branch("dB_ro", &tempAttenRo, "dB_ro/s");
  tr.Branch("nch_ro", &tempNumRo, "nch_ro/s");
  tr.Branch("line_ro", tempRO, "line_ro[200]/C");
  tr.Branch("trg_hv", tempTrigHV, "trg_hv[200]/C");
  tr.Branch("dB_hv", &tempAttenHV, "dB_hv/s");
  tr.Branch("nch_hv", &tempNumHv, "nch_hv/s");
  tr.Branch("line_hv", tempHV, "line_hv[200]/C");
  //tr.Branch("Mot_X", tempMotX, "steps/C");
  //tr.Branch("Mot_Y", tempMotY, "steps/C");
  //tr.Branch("Time", startTime, "seconds/C");
  tr.Branch("tstamp", &tstamp, "tstamp/D");
  tr.Branch("data", count, "data[20]/i");
  tr.Branch("num_pix", &tempPix, "num_pix/i");
  tr.Branch("pixX", pixX, "pixX[20]/i");
  tr.Branch("pixY", pixY, "pixY[20]/i");
  tr.Branch("runNum", hg.runNumber, "runNum/L");
  /////////////////////////////////////////////////////
  HighResClock::time_point first = t->front();
  elapsed = t->front() - first;
  tstamp = elapsed.count();
  tr.Fill();
  out << setw(10) << fixed
    << setprecision(3) << elapsed.count() << "    ";
  for (int i = 0; i < 20; ++i){
    out << setw(13) << count[i] << "      ";
  }
  out << endl;
  //gr.makeGraphBmp(count);
  // img = new cimg_library::CImg<unsigned char>("c1.bmp");
  //disp.display(*img);
  q->pop();
  t->pop();
  while (!*done){
    this_thread::sleep_for(chrono::microseconds(10));
    while (q->read_available() > 0 && t->read_available() > 0){
      for (int i = 0; i < 20; ++i){
        prev[i] = count[i];
        correctCount(count[i], q->front()[i]);
      }
      elapsed = t->front() - first;
      tstamp = elapsed.count();
      tr.Fill();
      out << setw(10) << fixed
        << setprecision(3) << elapsed.count() << "    ";
      for (int i = 0; i < 20; ++i){
        out << setw(13) << count[i] << "      ";
      }
      out << endl;
     // gr.makeGraphBmp(count);
     // delete img;
     // img = new cimg_library::CImg<unsigned char>("c1.bmp");
     // disp.display(*img);
      q->pop();
      t->pop();
    }
  }
  this_thread::sleep_for(chrono::microseconds(1000));
  while (!t->empty() && !q->empty()){
    for (int i = 0; i < 20; ++i){
      prev[i] = count[i];
      correctCount(count[i], q->front()[i]);
    }
    elapsed = t->front() - first;
    tstamp = elapsed.count();
    tr.Fill();
    out << setw(10) << fixed
      << setprecision(3) << elapsed.count() << "    ";
    for (int i = 0; i < 20; ++i){
      out << setw(13) << count[i] << "      ";
    }
    out << endl;
   // gr.makeGraphBmp(count);
   // delete img;
   // img = new cimg_library::CImg<unsigned char>("c1.bmp");
   // disp.display(*img);
    q->pop();
    t->pop();
  }
  out.close();
  //char buffer[50];
  //sprintf(buffer, "hist%d.bmp", (int)elapsed.count());
 // CopyFileA("c1.bmp", buffer, false);
  //delete img;
  tr.Write();
  f.Save();
}
static void readWeinerCount(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q, Spsc_time *t, atomic<bool> *done, WeinerCounter *nim, double time, double intervalLength){
  array<int, 20> count;
  for (int i = 0; i < 20; ++i){
    count[i] = 0;
  }
  int numSamps = ceil(time / intervalLength);
  chrono::duration<int, milli> dur((int)(intervalLength * 1000) - 29);
  nim->resetAll();
  t->push(HighResClock::now());
  q->push(count);
  this_thread::sleep_for(dur);
  for (int i = 0; i < numSamps; ++i){
    t->push(HighResClock::now());
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
    q->push(count);
    this_thread::sleep_for(dur);
  }
  *done = true;
}
void doWeinerCountInf(WeinerCounter *nim, double sampleLength, double volt, const HeaderInfoGen *hg, string fileName, atomic<bool> *run){
	time_t tm = time(nullptr);
	string runName;
	runName = ".\\CollectedData\\";
	CreateDirectory(runName.c_str(), NULL);
	runName += hg->gas + "\\";
	CreateDirectory(runName.c_str(), NULL);
	runName += hg->panelName + "_" + to_string(tm);
	vector<int> x = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	vector<int> y = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	int numReadings = 10000;
	double voltage = 100;
	//assert(x.size() == y.size());
	HeaderInfoAfter ha;
	ha.numPixels = x.size();
	ha.numReadings = numReadings;
	ha.voltage = voltage;
	stringstream ss;
	string temp;
	for (int i = 0, leni = x.size(); i < leni; ++i){
		ss.str(std::string());
		ss.clear();
		ss << x[i] << "-" << y[i];
		ss >> temp;
		ha.pixels.push_back(temp);
	}
	vector < boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>> > q(x.size());
	boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
	atomic<bool> done = false;
	atomic<bool> control = false;
	thread t2(writeInfoAfterN, ref(q), ref(t), &done, run, runName, ha, *hg);
	readFromPixAfterNInf(x, &done, run, q, t, nim);
	if (t2.joinable()){
		t2.join();
	}
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

void doLineScan(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, HeaderInfoGen* header, atomic<bool>* run)
{
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
		if (header->sourceConfig == "Dynamic")
		{
			volt->setVoltage(starting);
			volt->turnOn();
			log << "Going to home" << endl;
			mot->goZero();
			//mot->stepMotor(2, -motstepy);
			if (motstepx != 0)
			{
				mot->stepMotor(1, -motstepx);
			}
			//mot->stepMotor(2, motstep);
			//mot->mapPixel(fullFile, nim, 1, 1, duration, 0, motend, 0, motstep);
			if (motstepy == 0)
			{
				motbeginy = motendy;
				step = 10000;
			}

			int stepsiny = 0;

			for (int i = motbeginx; i <= motendx && *run == true; i += motstepx)
			{
				mot->stepMotor(2, -stepsiny*motendy);
				mot->stepMotor(2, -motstepy);
				//mot->stepMotor(2, motstepy);
				mot->stepMotor(1, motstepx); 

				log << "At " << i << "steps x" << ", ";

				for (int j = motbeginy; j <= motendy && *run == true; j += motstepy) // loop y
				{	
					stepsiny=1;
					mot->stepMotor(2, motstepy);
					log << i << "steps y" << endl;

					for (int k = starting; k <= stop && *run == true; k += step)
					{
						//if (end == true)
						//break;
						log << "Setting Voltage to: " << k << endl;
						volt->setVoltage(k);
						log << "Begin Counting" << endl;
						temp = runName + to_string(k) + "_" + "volts" + "_" + to_string((long)i) + "_x" + to_string((long)j) + "_y" + ".txt";
						doWeinerCount(nim, message->time, message->frequency, k, *header, pix, temp,i,j);
						log << "Finished Counting" << endl;

					}
				}
			}
		}
	

	//if (header->sourceConfig == "Static" || header->sourceConfig == "Dynamic"){
	//	mot->goToBackGround();
	//	//------------------------------
	//	//--------WARNING--------------
	//	//----------------------------
	//	//when a the motor is moved to the background location it always needs to be moved out in order to be used again
	//	//aka always call leaveBackGround() when done with taking a background measure ment
	//}
	//header->sourceName = "bkg";
	//for (int i = starting; i <= stop; i += step){
	//	log << "Setting Voltage to: " << i << endl;
	//	volt->setVoltage(i);
	//	log << "Begin Counting" << endl;
	//	temp = runName + to_string(i) + "_bkg_vs.txt";
	//	doWeinerCount(nim, message->time, message->frequency, i, *header, pix, message->temp);
	//	log << "Finished Counting" << endl;
	//}
	//if (header->sourceConfig == "Static" || header->sourceConfig == "Dynamic"){
	//	mot->leaveBackGround();
	//}

	log << "Turning off High Voltage" << endl;
	volt->turnOff();
	mot->goZero();
	log << "Voltage Scan Completed" << endl;
	log.close();
	*run = false;
}

string createFileName(HeaderInfoGen *header, Messages* message, time_t t)
{
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

void doAfterScanGraphMultiGUI(MotorController *mot, WeinerCounter *nim, Voltage *volt, HeaderInfoGen* header, Messages* message, Readout* readout, atomic<bool>* run){

	//string path = ".\\CollectedData\\";
	string runName;
	ofstream log;
	int starting = message->voltageStart;
	int stop = message->voltageEnd;
	int step = message->voltageStep;
	int motbegin = 0;
	int motend = message->maxOffsetY;
	int motstep = message->maxStepY;
	int num;
	int numMeas = 1;
	int tempNum;
	int numSamples;
	int intLength;
	//vector<int> x;
	//vector<int> y;
	string temp;

	time_t t = time(nullptr);

	runName = createFileName(header, message, t);

	log.open(runName + "log.txt", ofstream::ate);
	log << "Intitalized After-Pulse Test" << endl;
	log << "Starting: " << starting << endl;
	log << "Stop: " << stop << endl;
	log << "Step Size: " << step << endl;
	log << "Number of Pixels: " << num << endl;
	log << "Interval Duration: " << message->time << endl;
	log << "Readout List: " << endl;
	for (int i = 0; i < num; ++i){
		//log << x[i] << "-" << y[i] << endl;
	}
	log << "Turning On High Voltage" << endl;
	volt->turnOn();
	volt->setVoltage(0);
	volt->turnOn();
	string fullFile = "test.txt";
	if (header->sourceConfig == "Dynamic")
	{
		volt->setVoltage(starting);
		volt->turnOn();
		log << "Going to home" << endl;
		mot->goZero();
		mot->stepMotor(2, -motstep);
		//mot->stepMotor(2, motstep);
		//mot->mapPixel(fullFile, nim, 1, 1, duration, 0, motend, 0, motstep);
		if (motstep == 0)
		{
			motbegin = motend;
			step = 10000;

		}
		for (int i = motbegin; i <= motend && *run == true; i += motstep)
		{
			mot->stepMotor(2, motstep);
			log << "At " << i << endl;

			for (int j = starting; j <= stop && *run == true; j += step)
			{
				//if (end == true)
				//break;
				log << "Setting Voltage to: " << j << endl;
				volt->setVoltage(j);
				log << "Begin Counting" << endl;
				temp = runName + "_" + to_string(j) + "_" + "volts" + "_" + to_string((long)i) + "_steps";
				doAfterPulseAny(temp, nim, *header, starting, readout, run);
				log << "Finished Counting" << endl;

			}

		}
		//log << "Creating Graphs" << endl;
	}
}

void doAfterScanGraphMultiFree(WeinerCounter *nim, HeaderInfoGen* header, Voltage *volt, Messages* message, Readout* readout, atomic<bool>* run){

		//string path = ".\\CollectedData\\";
		string runName;
		ofstream log;
		int starting = message->voltageStart;
		//int stop = message->voltageEnd;
		//int step = message->voltageStep;
		//int num;
		//int numMeas = 1;
		int tempNum;
		int numSamples;
		int intLength;
		//vector<int> x;
		//vector<int> y;
		string temp;

		time_t t = time(nullptr);

		runName = createFileName(header, message, t);
		readout->timeToSamples(message->time);

		log.open(runName + "log.txt", ofstream::ate);
		log << "Intitalized After-Pulse Test" << endl;
		log << "Starting: " << starting << endl;
		log << "Interval Duration: " << message->time << endl;
		log << "Readout List: " << endl;
		for (int i = 0; i < readout->numActive; ++i){
			log << readout->lines[i] << endl;
			//log << x[i] << "-" << y[i] << endl;
		}

		string fullFile = "test.txt";
		if (header->sourceConfig == "Dynamic")
		{	
			log << "Turning On High Voltage" << endl;
			volt->setVoltage(starting);
			volt->turnOn();
			
			while (*run == true)
			{
				log << "Begin Counting" << endl;
				temp = runName + "_" + to_string(starting) + "_" + "volts";
				doAfterPulseAny(temp, nim, *header, starting, readout, run);
				log << "Finished Counting" << endl;
			}

		}
		log << "Turning off High Voltage" << endl;
		volt->turnOff();
		log << "Creating Graphs" << endl;
	}

void doAfterPulseAny(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int voltage, Readout* readout, atomic<bool>* run){
	HeaderInfoAfter ha;
	ha.numPixels = readout->numActive;
	ha.numReadings = readout->samples;
	ha.voltage = voltage;
	stringstream ss;
	string temp;

	for (int i = 0; i < readout->numActive; i++)
	{
		ss.str(std::string());
		ss.clear();
		ss << readout->lines[i];
		ss >> temp;
		ha.pixels.push_back(temp);
	}
	
	//boost::lockfree::spsc_queue<array<int, 10>, boost::lockfree::capacity<10000>> q;
	boost::lockfree::spsc_queue<vector<int>, boost::lockfree::capacity<10000>> q;

	Spsc_time t;
	atomic<bool> done = false;
	thread t2(writeInfoAfterAny, &q, &t, &done, fileName, ha, hg, readout);
	readFromPixAfterAny(&done, &q, &t, nim, readout, run);
	t2.join();
}

static void readFromPixAfterAny(atomic<bool> *done, boost::lockfree::spsc_queue<vector<int>, boost::lockfree::capacity<10000>> *q, Spsc_time *t, WeinerCounter *nim, Readout* readout, atomic<bool>* run){
	const int total = readout->numActive;
	//array<int, 20> arr;
	vector<int> arr;
	nim->resetAll();
	t->push(HighResClock::now());

	for (int i = 0; i < readout->numActive; i++)
	{
		arr.push_back(nim->readCounter(readout->lines[i]));
	}

	q->push(arr);

	if (readout->samples == 0) // free run
	{
		for (int i = 0; *run == true; ++i){
			t->push(HighResClock::now());
			for (int i = 0; i < readout->numActive; i++)
			{
				arr[i] = nim->readCounter(readout->lines[i]);
			}
			q->push(arr);
		}
	}

	else
	{
		for (int i = 0; i < readout->samples && *run == true; ++i){
			t->push(HighResClock::now());
			for (int i = 0; i < readout->numActive; i++)
			{
				arr[i] = nim->readCounter(readout->lines[i]);
			}
			q->push(arr);
		}
	}
	*done = true;
}

static void writeInfoAfterAny(boost::lockfree::spsc_queue<vector<int>, boost::lockfree::capacity<10000>> *q, Spsc_time *t, atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg, Readout* readout){
	this_thread::sleep_for(chrono::microseconds(1000));
	std::chrono::duration<double, std::milli> elapsed;
	ofstream out;
	out.open(fileName);
	out << hg << ha;
	out << " Time (ms)   Count ";
	for (int i = 0; i < ha.numPixels; i++)
	{
		out << left << setw(13) << ha.pixels[i];
	}
	out << endl;

	while (q->read_available() == 0 || t->read_available() == 0){}
	this_thread::sleep_for(chrono::microseconds(1000));

	int prev[20];
	int count[20];

	for (int i = 0; i < readout->numActive; i++)
	{
		count[i] = q->front()[i];
	}


	for (int i = 0; i < readout->numActive; ++i){
		prev[i] = count[i];
	}
	//for (int i = 0; i < 10; ++i){
	//	prev[i + 10] = count[i + 10];
	//}


	////////////////////////////////////////////////////
	string tempst;
	tempst = fileName.substr(0, fileName.size() - 4);
	tempst += ".root";
	TFile f(tempst.c_str(), "RECREATE");
	tempst = "TTree for panel " + hg.panelName + " filled with " + hg.gas + " at " + to_string(ha.voltage) + " (V) AP";
	TTree tr("ap", tempst.c_str());
	char  tempPanel[200], tempSource[200], tempGas[200], tempSetup[200], tempRO[200], tempHV[200], tempTrigHV[200], tempTrigRO[200];
	strcpy(tempPanel, hg.panelName.c_str());
	strcpy(tempSource, hg.sourceName.c_str());
	strcpy(tempGas, hg.gas.c_str());
	strcpy(tempSetup, hg.sourceConfig.c_str());
	strcpy(tempRO, hg.roLines.c_str());
	strcpy(tempHV, hg.linesHV.c_str());
	strcpy(tempTrigHV, hg.triggerHV.c_str());
	strcpy(tempTrigRO, hg.triggerRO.c_str());
	Double_t tstamp, tempPress, tempVolt, tempDiscThr, tempQuench, tempNumHv, tempNumRo, tempAttenRo, tempAttenHV;
	tempPress = hg.pressure;
	tempVolt = ha.voltage;
	tempDiscThr = hg.discThresh;
	tempQuench = hg.quench;
	tempNumHv = hg.numHV;
	tempNumRo = hg.numRO;
	tempAttenRo = hg.attenRO;
	tempAttenHV = hg.attenHV;
	Int_t pixX[20];
	Int_t pixY[20];
	char holding[30];
	//for (int i = 0; i < 20; ++i){
	//	pixX[i] = 0;
	//	pixY[i] = 0;
	//}
	//for (int i = 0, len = ha.pixels.size(); i < len; ++i){
	//	strcpy(holding, ha.pixels[i].c_str());
	//	pixX[i] = atoi(strtok(holding, "-"));
	//	pixY[i] = atoi(strtok(NULL, "-"));
	//}
	Int_t tempSamp = ha.numReadings;
	Int_t tempPix = ha.numPixels;
	tr.Branch("panel", tempPanel, "panel[200]/C");
	tr.Branch("source", tempSource, "source[200]/C");
	tr.Branch("sourceSetup", tempSetup, "sourceSetup[200]/C");
	tr.Branch("gasmix", tempGas, "gasmix[200]/C");
	tr.Branch("press", &tempPress, "press/D");
	tr.Branch("hvVal", &tempVolt, "hvVal/D");
	tr.Branch("disThr", &tempDiscThr, "disThr/D");
	tr.Branch("quench", &tempQuench, "quench/D");
	tr.Branch("trg_ro", tempTrigRO, "trg_ro[200]/C");
	tr.Branch("dB_ro", &tempAttenRo, "dB_ro/s");
	tr.Branch("nch_ro", &tempNumRo, "nch_ro/s");
	tr.Branch("line_ro", tempRO, "line_ro[200]/C");
	tr.Branch("trg_hv", tempTrigHV, "trg_hv[200]/C");
	tr.Branch("dB_hv", &tempAttenHV, "dB_hv/s");
	tr.Branch("nch_hv", &tempNumHv, "nch_hv/s");
	tr.Branch("line_hv", tempHV, "line_hv[200]/C");
	tr.Branch("tstamp", &tstamp, "tstamp/D");
	tr.Branch("data", count, "data[20]/i");
	tr.Branch("samps", &tempSamp, "samps/i");
	tr.Branch("num_pix", &tempPix, "num_pix/i");
	tr.Branch("pixX", pixX, "pixX[20]/i");
	tr.Branch("pixY", pixY, "pixY[20]/i");
	/////////////////////////////////////////////////////
	HighResClock::time_point first = t->front();
	elapsed = t->front() - first;
	tstamp = elapsed.count();
	out << setw(9) << fixed << setprecision(2) << elapsed.count();
	
	for (int i = 0; i < readout->numActive; i++)
	{
		out << "    " << setw(13) << count[i];
	}
	out << endl;
	q->pop();
	t->pop();
	tr.Fill();
	while (!*done){
		this_thread::sleep_for(chrono::microseconds(1000));
		while (q->read_available() > 0 && t->read_available() > 0){
			for (int i = 0; i < readout->numActive; ++i){
				prev[i] = count[i];
				correctCount(count[i], q->front()[i]);
			}
			for (int i = 0; i < readout->numActive; ++i){
				if (count[i] > prev[i]){
					elapsed = t->front() - first;
					tstamp = elapsed.count();
					out << setw(9) << fixed << setprecision(2) << elapsed.count();
					for (int i = 0; i < readout->numActive; i++)
					{
						out << "    " << setw(13) << count[i];
					}
					out << endl;

					tr.Fill();
					break;

				}
			}
			q->pop();
			t->pop();
		}
		tr.Write();
		f.Save();

	}
	this_thread::sleep_for(chrono::microseconds(1000));
	while (!t->empty() && !q->empty()){
		for (int i = 0; i < readout->numActive; ++i){
			prev[i] = count[i];
			correctCount(count[i], q->front()[i]);
		}
		for (int i = 0; i < readout->numActive; ++i){
			if (count[i] > prev[i]){
				elapsed = t->front() - first;
				tstamp = elapsed.count();
				out << setw(9) << fixed << setprecision(2) << elapsed.count();
				for (int i = 0; i < readout->numActive; i++)
				{
					out << "    " << setw(13) << count[i];
				}
				out << endl;
				tr.Fill();
				break;
			}
			q->pop();
			t->pop();
		}
	}
	tr.Write();
	f.Save();
	out.close();
}

void doHexScanX(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, HeaderInfoGen* header, atomic<bool>* run)
{
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
					temp = runName + to_string(k) + "_" + "volts" + "_" + to_string((long)i) + "_x" + to_string((long)j) + "_y" + ".txt";
					doWeinerCount(nim, message->time, message->frequency, k, *header, pix, temp, i, j);
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

void doXYScan(MotorController *mot, WeinerCounter *nim, Voltage *volt, Messages* message, HeaderInfoGen* header, atomic<bool>* run)
{
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
						temp = runName + to_string(k) + "_" + "volts" + "_" + to_string(i) + "_x" + to_string(j) + "_y" + ".txt";
						doWeinerCount(nim, message->time, message->frequency, k, *header, pix, temp, i, j);
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