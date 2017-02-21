#include "LabUtilities.h"
#include <iomanip>
#include <functional>
//#include "LabView.h"
#include "headers.h"


//extern atomic<bool> control;

using Spsc = boost::lockfree::spsc_queue < int, boost::lockfree::capacity<10000> > ;
//Dunction used for converting weiner counter bin value to a count value
//used in afterpulse tests
inline static void correctCount(int &count, int next);
///_________________________________________
void doAfterPulse1(string fileName, WeinerCounter *nim, HeaderInfoGen const &hg, int x1, int y1, int voltage, int numReadings){
 //generate afterpulse header
  HeaderInfoAfter ha;
  ha.numPixels = 1;
  ha.numReadings = numReadings;
  ha.voltage = voltage;
  stringstream ss;
  string temp;
  ss.str(std::string());
  ss.clear();
  ss << x1 << "-" << y1;
  ss >> temp;
  ha.pixels.push_back(temp);
  boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>> q;
  boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
  atomic<bool> done = false;
  thread t2(writeInfoAfter1, &q, &t, &done, fileName, ha, hg);
  readFromPixAfter1(x1, &done, &q, &t, nim, numReadings);
  t2.join();
}
static void readFromPixAfter1(int pix, atomic<bool> *done,
  boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>> *q,
  boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, WeinerCounter *nim, int readings){
  nim->resetAll();
  t->push(HighResClock::now());
  q->push(nim->readCounter(pix));

  for (int i = 0; i < readings; ++i){
    t->push(HighResClock::now());
    q->push(nim->readCounter(pix));
  }
  *done = true;
}

static void writeInfoAfter1(boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>> *q,
  boost::lockfree::spsc_queue < HighResClock::time_point,
  boost::lockfree::capacity < 10000 >> *t, atomic<bool> *done,
  string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg){
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double, std::milli> elapsed;
  ofstream out;
  out.open(fileName);
  out << hg << ha;
  out << " Time (ms)   Count " << ha.pixels[0] << endl;
  while (q->read_available() == 0 || t->read_available() == 0){}
  this_thread::sleep_for(chrono::microseconds(1000));
  int count[20] = { q->front(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int prev[20];
  for (int i = 0; i < 20; ++i){
    prev[i] = count[i];
  }
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
  for (int i = 0; i < 20; ++i){
    pixX[i] = 0;
    pixY[i] = 0;
  }
  for (int i = 0, len = ha.pixels.size(); i < len; ++i){
    strcpy(holding, ha.pixels[i].c_str());
    pixX[i] = atoi(strtok(holding, "-"));
    pixY[i] = atoi(strtok(nullptr, "-"));
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


  HighResClock::time_point first = t->front();
  elapsed = t->front() - first;
  tstamp = elapsed.count();
  out << setw(9) << fixed
    << setprecision(2) << elapsed.count() << "     " << q->front() << endl;
  q->pop();
  t->pop();
  tr.Fill();
  while (!*done){
    this_thread::sleep_for(chrono::microseconds(10));
    while (q->read_available() > 0 && t->read_available() > 0){
      prev[0] = count[0];
      correctCount(count[0], q->front());
      if (count[0] > prev[0]){
        elapsed = t->front() - first;
        tstamp = elapsed.count();
        out << setw(9) << fixed
          << setprecision(2) << elapsed.count() << "     " << count[0] << endl;
      }
      q->pop();
      t->pop();
      tr.Fill();
    }
  }
  this_thread::sleep_for(chrono::microseconds(10000));
  while (!t->empty() && !q->empty()){
    prev[0] = count[0];
    correctCount(count[0], q->front());
    if (count[0] > prev[0]){
      elapsed = t->front() - first;
      tstamp = elapsed.count();
      out << setw(9) << fixed
        << setprecision(2) << elapsed.count() << "     " << count[0] << endl;
    }
    q->pop();
    t->pop();
    tr.Fill();
  }
  tr.Write();
  f.Save();

}
void doAfterPulse2(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int x1, int y1, int x2, int y2, int voltage, int numReadings){
  HeaderInfoAfter ha;
  ha.numPixels = 2;
  ha.numReadings = numReadings;
  ha.voltage = voltage;
  stringstream ss;
  string temp;
  ss.str(std::string());
  ss.clear();
  ss << x1 << "-" << y1;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x2 << "-" << y2;
  ss >> temp;
  ha.pixels.push_back(temp);
  boost::lockfree::spsc_queue<array<int, 2>, boost::lockfree::capacity<10000>> q;
  boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
  atomic<bool> done = false;
  thread t2(writeInfoAfter2, &q, &t, &done, fileName, ha, hg);
  readFromPixAfter2(x1, x2, &done, &q, &t, nim, numReadings);
  t2.join();
}
static void readFromPixAfter2(int pix1, int pix2, atomic<bool> *done, boost::lockfree::spsc_queue<array<int, 2>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, WeinerCounter *nim, int readings){
  array<int, 2> arr;
  nim->resetAll();
  t->push(HighResClock::now());
  arr[0] = nim->readCounter(pix1);
  arr[1] = nim->readCounter(pix2);
  q->push(arr);

  for (int i = 0; i < readings; ++i){
    t->push(HighResClock::now());
    arr[0] = nim->readCounter(pix1);
    arr[1] = nim->readCounter(pix2);
    q->push(arr);
  }
  *done = true;
}
static void writeInfoAfter2(boost::lockfree::spsc_queue<array<int, 2>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg){
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double, std::milli> elapsed;
  ofstream out;
  out.open(fileName);
  out << hg << ha;
  out << " Time (ms)   Count " << left << setw(13) << ha.pixels[0] << "Count " << left << setw(13) << ha.pixels[1] << endl;
  while (q->read_available() == 0 || t->read_available() == 0){}
  this_thread::sleep_for(chrono::microseconds(1000));
  int count[20] = { q->front()[0], q->front()[1], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int prev[20];
  for (int i = 0; i < 20; ++i){
    prev[i] = count[i];
  }
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
  for (int i = 0; i < 20; ++i){
    pixX[i] = 0;
    pixY[i] = 0;
  }
  for (int i = 0, len = ha.pixels.size(); i < len; ++i){
    strcpy(holding, ha.pixels[i].c_str());
    pixX[i] = atoi(strtok(holding, "-"));
    pixY[i] = atoi(strtok(nullptr, "-"));
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
  HighResClock::time_point first = t->front();
  elapsed = t->front() - first;
  tstamp = elapsed.count();
  out << setw(9) << fixed
    << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1] << endl;
  q->pop();
  t->pop();
  tr.Fill();
  while (!*done){
    this_thread::sleep_for(chrono::microseconds(10));
    while (q->read_available() > 0 && t->read_available() > 0){
      for (int i = 0; i < 2; ++i){
        prev[i] = count[i];
        correctCount(count[i], q->front()[i]);
      }
      for (int i = 0; i < 2; ++i){
        if (count[i] > prev[i]){
          elapsed = t->front() - first;
          tstamp = elapsed.count();
          out << setw(9) << fixed
            << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1] << endl;
          tr.Fill();
          break;
        }
      }
      q->pop();
      t->pop();
    }
  }
  this_thread::sleep_for(chrono::microseconds(1000));
  while (!t->empty() && !q->empty()){
    for (int i = 0; i < 2; ++i){
      prev[i] = count[i];
      correctCount(count[i], q->front()[i]);
    }
    for (int i = 0; i < 2; ++i){
      if (count[i] > prev[i]){
        elapsed = t->front() - first;
        tstamp = elapsed.count();
        out << setw(9) << fixed
          << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1] << endl;
        tr.Fill();
        break;
      }
      q->pop();
      t->pop();
    }
  }
  tr.Write();
  f.Save();
}
void doAfterPulse3(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int x1, int y1, int x2, int y2, int x3, int y3, int voltage, int numReadings){
  HeaderInfoAfter ha;
  ha.numPixels = 3;
  ha.numReadings = numReadings;
  ha.voltage = voltage;
  stringstream ss;
  string temp;
  ss.str(std::string());
  ss.clear();
  ss << x1 << "-" << y1;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x2 << "-" << y2;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x3 << "-" << y3;
  ss >> temp;
  ha.pixels.push_back(temp);
  boost::lockfree::spsc_queue<array<int, 3>, boost::lockfree::capacity<10000>> q;
  boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
  atomic<bool> done = false;
  thread t2(writeInfoAfter3, &q, &t, &done, fileName, ha, hg);
  readFromPixAfter3(x1, x2, x3, &done, &q, &t, nim, numReadings);
  t2.join();
}
static void readFromPixAfter3(int pix1, int pix2, int pix3, atomic<bool> *done, boost::lockfree::spsc_queue<array<int, 3>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, WeinerCounter *nim, int readings){
  array<int, 3> arr;
  nim->resetAll();
  t->push(HighResClock::now());
  arr[0] = nim->readCounter(pix1);
  arr[1] = nim->readCounter(pix2);
  arr[2] = nim->readCounter(pix3);
  q->push(arr);

  for (int i = 0; i < readings; ++i){
    t->push(HighResClock::now());
    arr[0] = nim->readCounter(pix1);
    arr[1] = nim->readCounter(pix2);
    arr[2] = nim->readCounter(pix3);
    q->push(arr);
  }
  *done = true;
}
static void writeInfoAfter3(boost::lockfree::spsc_queue<array<int, 3>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg){
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double, std::milli> elapsed;
  ofstream out;
  out.open(fileName);
  out << hg << ha;
  out << " Time (ms)   Count " << left << setw(13) << ha.pixels[0] << "Count "
    << left << setw(13) << ha.pixels[1] << "Count " << left << setw(13) << ha.pixels[2] << endl;
  while (q->read_available() == 0 || t->read_available() == 0){}
  this_thread::sleep_for(chrono::microseconds(1000));
  int count[20] = { q->front()[0], q->front()[1], q->front()[2], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int prev[20];
  for (int i = 0; i < 20; ++i){
    prev[i] = count[i];
  }
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
  for (int i = 0; i < 20; ++i){
    pixX[i] = 0;
    pixY[i] = 0;
  }
  for (int i = 0, len = ha.pixels.size(); i < len; ++i){
    strcpy(holding, ha.pixels[i].c_str());
    pixX[i] = atoi(strtok(holding, "-"));
    pixY[i] = atoi(strtok(nullptr, "-"));
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
  HighResClock::time_point first = t->front();
  elapsed = t->front() - first;
  tstamp = elapsed.count();
  out << setw(9) << fixed
    << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
    << "      " << setw(13) << count[2] << endl;
  q->pop();
  t->pop();
  tr.Fill();
  while (!*done){
    this_thread::sleep_for(chrono::microseconds(10));
    while (q->read_available() > 0 && t->read_available() > 0){
      for (int i = 0; i < 3; ++i){
        prev[i] = count[i];
        correctCount(count[i], q->front()[i]);
      }
      for (int i = 0; i < 3; ++i){
        if (count[i] > prev[i]){
          elapsed = t->front() - first;
          tstamp = elapsed.count();
          out << setw(9) << fixed
            << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
            << "      " << setw(13) << count[2] << endl;
          tr.Fill();
          break;
        }
      }
      q->pop();
      t->pop();
    }
  }
  this_thread::sleep_for(chrono::microseconds(1000));
  while (!t->empty() && !q->empty()){
    for (int i = 0; i < 3; ++i){
      prev[i] = count[i];
      correctCount(count[i], q->front()[i]);
    }
    for (int i = 0; i < 3; ++i){
      if (count[i] > prev[i]){
        elapsed = t->front() - first;
        tstamp = elapsed.count();
        out << setw(9) << fixed
          << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
          << "      " << setw(13) << count[2] << endl;
        tr.Fill();
        break;
      }
      q->pop();
      t->pop();
    }
  }
  tr.Write();
  f.Save();
}
void doAfterPulse4(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int voltage, int numReadings){
  HeaderInfoAfter ha;
  ha.numPixels = 4;
  ha.numReadings = numReadings;
  ha.voltage = voltage;
  stringstream ss;
  string temp;
  ss.str(std::string());
  ss.clear();
  ss << x1 << "-" << y1;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x2 << "-" << y2;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x3 << "-" << y3;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x4 << "-" << y4;
  ss >> temp;
  ha.pixels.push_back(temp);
  boost::lockfree::spsc_queue<array<int, 4>, boost::lockfree::capacity<10000>> q;
  boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
  atomic<bool> done = false;
  thread t2(writeInfoAfter4, &q, &t, &done, fileName, ha, hg);
  readFromPixAfter4(x1, x2, x3, x4, &done, &q, &t, nim, numReadings);
  t2.join();
}
void doAfterPulse5(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5, int voltage, int numReadings){
  HeaderInfoAfter ha;
  ha.numPixels = 5;
  ha.numReadings = numReadings;
  ha.voltage = voltage;
  stringstream ss;
  string temp;
  ss.str(std::string());
  ss.clear();
  ss << x1 << "-" << y1;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x2 << "-" << y2;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x3 << "-" << y3;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x4 << "-" << y4;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x5 << "-" << y5;
  ss >> temp;
  ha.pixels.push_back(temp);
  boost::lockfree::spsc_queue<array<int, 5>, boost::lockfree::capacity<10000>> q;
  boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
  atomic<bool> done = false;
  thread t2(writeInfoAfter5, &q, &t, &done, fileName, ha, hg);
  readFromPixAfter5(x1, x2, x3, x4, x5, &done, &q, &t, nim, numReadings);
  t2.join();
}
static void readFromPixAfter4(int pix1, int pix2, int pix3, int pix4, atomic<bool> *done, boost::lockfree::spsc_queue<array<int, 4>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, WeinerCounter *nim, int readings){
  array<int, 4> arr;
  nim->resetAll();
  t->push(HighResClock::now());
  arr[0] = nim->readCounter(pix1);
  arr[1] = nim->readCounter(pix2);
  arr[2] = nim->readCounter(pix3);
  arr[3] = nim->readCounter(pix4);
  q->push(arr);

  for (int i = 0; i < readings; ++i){
    t->push(HighResClock::now());
    arr[0] = nim->readCounter(pix1);
    arr[1] = nim->readCounter(pix2);
    arr[2] = nim->readCounter(pix3);
    arr[3] = nim->readCounter(pix4);
    q->push(arr);
  }
  *done = true;
}
static void writeInfoAfter4(boost::lockfree::spsc_queue<array<int, 4>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg){
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double, std::milli> elapsed;
  ofstream out;
  out.open(fileName);
  out << hg << ha;
  out << " Time (ms)   Count " << left << setw(13) << ha.pixels[0] << "Count "
    << left << setw(13) << ha.pixels[1] << "Count " << left << setw(13) << ha.pixels[2]
    << "Count " << left << setw(13) << ha.pixels[3] << endl;
  while (q->read_available() == 0 || t->read_available() == 0){}
  this_thread::sleep_for(chrono::microseconds(1000));
  int count[20] = { q->front()[0], q->front()[1], q->front()[2], q->front()[3], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int prev[20];
  for (int i = 0; i < 20; ++i){
    prev[i] = count[i];
  }
  ////////////////////////////////////////////////////
  string tempst;
  tempst = fileName.substr(0, fileName.size() - 4);
  tempst += ".root";
  TFile f(tempst.c_str(), "RECREATE");
  tempst = "TTree for panel " + hg.panelName + " filled with " + hg.gas + " at " + to_string(ha.voltage) + " (V) AP";
  TTree tr("ap" , tempst.c_str());
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
  for (int i = 0; i < 20; ++i){
    pixX[i] = 0;
    pixY[i] = 0;
  }
  for (int i = 0, len = ha.pixels.size(); i < len; ++i){
    strcpy(holding, ha.pixels[i].c_str());
    pixX[i] = atoi(strtok(holding, "-"));
    pixY[i] = atoi(strtok(nullptr, "-"));
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
  HighResClock::time_point first = t->front();
  elapsed = t->front() - first;
  tstamp = elapsed.count();
  out << setw(9) << fixed
    << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
    << "      " << setw(13) << count[2] << "      " << setw(13) << count[3] << endl;
  q->pop();
  t->pop();
  tr.Fill();
  while (!*done){
    this_thread::sleep_for(chrono::microseconds(10));
    while (q->read_available() > 0 && t->read_available() > 0){
      for (int i = 0; i < 4; ++i){
        prev[i] = count[i];
        correctCount(count[i], q->front()[i]);
      }
      for (int i = 0; i < 4; ++i){
        if (count[i] > prev[i]){
          elapsed = t->front() - first;
          tstamp = elapsed.count();
          out << setw(9) << fixed
            << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
            << "      " << setw(13) << count[2] << "      " << setw(13) << count[3] << endl;
          tr.Fill();
          break;
        }
      }
      q->pop();
      t->pop();
    }
  }
  this_thread::sleep_for(chrono::microseconds(1000));
  while (!t->empty() && !q->empty()){
    for (int i = 0; i < 4; ++i){
      prev[i] = count[i];
      correctCount(count[i], q->front()[i]);
    }
    for (int i = 0; i < 4; ++i){
      if (count[i] > prev[i]){
        elapsed = t->front() - first;
        tstamp = elapsed.count();
        out << setw(9) << fixed
          << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
          << "      " << setw(13) << count[2] << "      " << setw(13) << count[3] << endl;
        tr.Fill();
        break;
      }
      q->pop();
      t->pop();
    }
  }
}
static void readFromPixAfter5(int pix1, int pix2, int pix3, int pix4, int pix5, atomic<bool> *done, boost::lockfree::spsc_queue<array<int, 5>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, WeinerCounter *nim, int readings){
  array<int, 5> arr;
  nim->resetAll();
  t->push(HighResClock::now());
  arr[0] = nim->readCounter(pix1);
  arr[1] = nim->readCounter(pix2);
  arr[2] = nim->readCounter(pix3);
  arr[3] = nim->readCounter(pix4);
  arr[4] = nim->readCounter(pix5);
  q->push(arr);

  for (int i = 0; i < readings; ++i){
    t->push(HighResClock::now());
    arr[0] = nim->readCounter(pix1);
    arr[1] = nim->readCounter(pix2);
    arr[2] = nim->readCounter(pix3);
    arr[3] = nim->readCounter(pix4);
    arr[4] = nim->readCounter(pix5);
    q->push(arr);
  }
  *done = true;
}
static void writeInfoAfter5(boost::lockfree::spsc_queue<array<int, 5>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg){
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double, std::milli> elapsed;
  ofstream out;
  out.open(fileName);
  out << hg << ha;
  out << " Time (ms)   Count " << left << setw(13) << ha.pixels[0] << "Count "
    << left << setw(13) << ha.pixels[1] << "Count " << left << setw(13) << ha.pixels[2]
    << "Count " << left << setw(13) << ha.pixels[3] << "Count " << left << setw(13) << ha.pixels[4] << endl;
  while (q->read_available() == 0 || t->read_available() == 0){}
  this_thread::sleep_for(chrono::microseconds(1000));
  int count[20] = { q->front()[0], q->front()[1], q->front()[2], q->front()[3], q->front()[4],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
  int prev[20];
  for (int i = 0; i < 20; ++i){
    prev[i] = count[i];
  }
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
  for (int i = 0; i < 20; ++i){
    pixX[i] = 0;
    pixY[i] = 0;
  }
  for (int i = 0, len = ha.pixels.size(); i < len; ++i){
    strcpy(holding, ha.pixels[i].c_str());
    pixX[i] = atoi(strtok(holding, "-"));
    pixY[i] = atoi(strtok(nullptr, "-"));
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
  HighResClock::time_point first = t->front();
  elapsed = t->front() - first;
  tstamp = elapsed.count();
  out << setw(9) << fixed
    << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
    << "      " << setw(13) << count[2] << "      " << setw(13) << count[3] << "      " << setw(13) << count[4] << endl;
  q->pop();
  t->pop();
  tr.Fill();
  while (!*done){
    this_thread::sleep_for(chrono::microseconds(10));
    while (q->read_available() > 0 && t->read_available() > 0){
      for (int i = 0; i < 5; ++i){
        prev[i] = count[i];
        correctCount(count[i], q->front()[i]);
      }
      for (int i = 0; i < 5; ++i){
        if (count[i] > prev[i]){
          elapsed = t->front() - first;
          tstamp = elapsed.count();
          out << setw(9) << fixed
            << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
            << "      " << setw(13) << count[2] << "      " << setw(13) << count[3] << "      " << setw(13) << count[4] << endl;
          tr.Fill();
          break;
        }
      }
      q->pop();
      t->pop();
    }
  }
  this_thread::sleep_for(chrono::microseconds(1000));
  while (!t->empty() && !q->empty()){
    for (int i = 0; i < 5; ++i){
      prev[i] = count[i];
      correctCount(count[i], q->front()[i]);
    }
    for (int i = 0; i < 5; ++i){
      if (count[i] > prev[i]){
        elapsed = t->front() - first;
        tstamp = elapsed.count();
        out << setw(9) << fixed
          << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
          << "      " << setw(13) << count[2] << "      " << setw(13) << count[3] << "      " << setw(13) << count[4] << endl;
        tr.Fill();
        break;
      }
      q->pop();
      t->pop();
    }
  }
  tr.Write();
  f.Save();
}
void doAfterPulse10(string fileName, WeinerCounter *nim, const HeaderInfoGen &hg, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5, int x6, int y6, int x7, int y7, int x8, int y8, int x9, int y9, int x10, int y10, int voltage, int numReadings){
  HeaderInfoAfter ha;
  ha.numPixels = 10;
  ha.numReadings = numReadings;
  ha.voltage = voltage;
  stringstream ss;
  string temp;
  ss.str(std::string());
  ss.clear();
  ss << x1 << "-" << y1;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x2 << "-" << y2;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x3 << "-" << y3;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x4 << "-" << y4;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.str(std::string());
  ss.clear();
  ss << x5 << "-" << y5;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.clear();
  ss << x6 << "-" << y6;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.clear();
  ss << x7 << "-" << y7;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.clear();
  ss << x8 << "-" << y8;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.clear();
  ss << x9 << "-" << y9;
  ss >> temp;
  ha.pixels.push_back(temp);
  ss.clear();
  ss << x10 << "-" << y10;
  ss >> temp;
  ha.pixels.push_back(temp);
  boost::lockfree::spsc_queue<array<int, 10>, boost::lockfree::capacity<10000>> q;
  boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
  atomic<bool> done = false;
  thread t2(writeInfoAfter10, &q, &t, &done, fileName, ha, hg);
  readFromPixAfter10(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, &done, &q, &t, nim, numReadings);
  t2.join();
}

void doAfterPulseNCountStop(string fileName, WeinerCounter* nim, const HeaderInfoGen& hg, const vector<int>& x, const vector<int>& y, int voltage, int countStop, int numReadings){
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
  thread t2(writeInfoAfterN,ref(q), ref(t), &done, &control, fileName, ha, hg, countStop);
  readFromPixAfterNCountStop(x, &done, &control, q, t, nim, numReadings);
  if (t2.joinable()){
    t2.join();
  }
}

static void readFromPixAfter10(int pix1, int pix2, int pix3, int pix4, int pix5, int pix6, int pix7, int pix8, int pix9, int pix10, atomic<bool> *done, boost::lockfree::spsc_queue<array<int, 10>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, WeinerCounter *nim, int readings){
  array<int, 10> arr;
  nim->resetAll();
  t->push(HighResClock::now());
  arr[0] = nim->readCounter(pix1);
  arr[1] = nim->readCounter(pix2);
  arr[2] = nim->readCounter(pix3);
  arr[3] = nim->readCounter(pix4);
  arr[4] = nim->readCounter(pix5);
  arr[5] = nim->readCounter(pix6);
  arr[6] = nim->readCounter(pix7);
  arr[7] = nim->readCounter(pix8);
  arr[8] = nim->readCounter(pix9);
  arr[9] = nim->readCounter(pix10);
  q->push(arr);

  for (int i = 0; i < readings; ++i){
    t->push(HighResClock::now());
    arr[0] = nim->readCounter(pix1);
    arr[1] = nim->readCounter(pix2);
    arr[2] = nim->readCounter(pix3);
    arr[3] = nim->readCounter(pix4);
    arr[4] = nim->readCounter(pix5);
    arr[5] = nim->readCounter(pix6);
    arr[6] = nim->readCounter(pix7);
    arr[7] = nim->readCounter(pix8);
    arr[8] = nim->readCounter(pix9);
    arr[9] = nim->readCounter(pix10);
    q->push(arr);
  }
  *done = true;
}
static void writeInfoAfter10(boost::lockfree::spsc_queue<array<int, 10>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg){
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double, std::milli> elapsed;
  ofstream out;
  out.open(fileName);
  out << hg << ha;
  out << " Time (ms)   Count " << left << setw(13) << ha.pixels[0] << "Count "
    << left << setw(13) << ha.pixels[1] << "Count " << left << setw(13) << ha.pixels[2]
    << "Count " << left << setw(13) << ha.pixels[3] << "Count " << left << setw(13) << ha.pixels[4]
    << "Count " << left << setw(13) << ha.pixels[5] << "Count " << left << setw(13) << ha.pixels[6]
    << "Count " << left << setw(13) << ha.pixels[7] << "Count " << left << setw(13) << ha.pixels[8]
    << "Count " << left << setw(13) << ha.pixels[9] << endl;
  while (q->read_available() == 0 || t->read_available() == 0){}
  this_thread::sleep_for(chrono::microseconds(1000));
  int count[20] = { q->front()[0], q->front()[1], q->front()[2], q->front()[3], q->front()[4], q->front()[5], q->front()[6],
    q->front()[7], q->front()[8], q->front()[9], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int prev[20];
  for (int i = 0; i < 10; ++i){
    prev[i] = count[i];
  }
  for (int i = 0; i < 10; ++i){
    prev[i+10] = count[i+10];
  }
  ////////////////////////////////////////////////////
  string tempst;
  tempst = fileName.substr(0, fileName.size() - 4);
  tempst += ".root";
  TFile f(tempst.c_str(),"RECREATE");
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
  for (int i = 0; i < 20; ++i){
    pixX[i] = 0;
    pixY[i] = 0;
  }
  for (int i = 0, len = ha.pixels.size(); i < len; ++i){
    strcpy(holding,ha.pixels[i].c_str());
    pixX[i] = atoi(strtok(holding, "-"));
    pixY[i] = atoi(strtok(nullptr, "-"));
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
  HighResClock::time_point first = t->front();
  elapsed = t->front() - first;
  tstamp = elapsed.count();
  out << setw(9) << fixed
    << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
    << "      " << setw(13) << count[2] << "      " << setw(13) << count[3] << "      " << setw(13) << count[4]
    << "      " << setw(13) << count[5] << "      " << setw(13) << count[6] << "      " << setw(13) << count[7]
    << "      " << setw(13) << count[8] << "      " << setw(13) << count[9] << endl;
  q->pop();
  t->pop();
  tr.Fill();
  while (!*done){
    this_thread::sleep_for(chrono::microseconds(10));
    while (q->read_available() > 0 && t->read_available() > 0){
      for (int i = 0; i < 10; ++i){
        prev[i] = count[i];
        correctCount(count[i], q->front()[i]);
      }
      for (int i = 0; i < 10; ++i){
        if (count[i] > prev[i]){
          elapsed = t->front() - first;
          tstamp = elapsed.count();
          out << setw(9) << fixed
            << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
            << "      " << setw(13) << count[2] << "      " << setw(13) << count[3] << "      " << setw(13) << count[4]
            << "      " << setw(13) << count[5] << "      " << setw(13) << count[6] << "      " << setw(13) << count[7]
            << "      " << setw(13) << count[8] << "      " << setw(13) << count[9] << endl;
          tr.Fill();
          break;

        }
      }
      q->pop();
      t->pop();
    }
  }
  this_thread::sleep_for(chrono::microseconds(1000));
  while (!t->empty() && !q->empty()){
    for (int i = 0; i < 10; ++i){
      prev[i] = count[i];
      correctCount(count[i], q->front()[i]);
    }
    for (int i = 0; i < 10; ++i){
      if (count[i] > prev[i]){
        elapsed = t->front() - first;
        tstamp = elapsed.count();
        out << setw(9) << fixed
          << setprecision(2) << elapsed.count() << "    " << setw(13) << count[0] << "      " << setw(13) << count[1]
          << "      " << setw(13) << count[2] << "      " << setw(13) << count[3] << "      " << setw(13) << count[4]
          << "      " << setw(13) << count[5] << "      " << setw(13) << count[6] << "      " << setw(13) << count[7]
          << "      " << setw(13) << count[8] << "      " << setw(13) << count[9] << endl;
        tr.Fill();
        break;
      }
      q->pop();
      t->pop();
    }
  }
  tr.Write();
  f.Save();
}
void readFromPixAfterNCountStop(const vector<int>& pix, atomic<bool>* done, atomic<bool> *control, vector<boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>>> &q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> &t, WeinerCounter* nim, int readings){
  //assert(q->size() == pix.size());
  int size = pix.size();
  int readingCheck = 4 * 1000 / size / .5;
  nim->resetAll();
  t.push(HighResClock::now());
  for (int i = 0; i < readings && !*control; ++i){
    t.push(HighResClock::now());
    for (int j = 0; j < size; ++j){
      q[j].push(nim->readCounter(pix[j]));
    }
  }
  *done = true;
}
static bool checkq(const boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>> &x){
  return x.read_available() == 0;
}
static bool checkqg(const boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>> &x){
  return x.read_available() > 0;
}
static bool checkqe(const boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>> &x){
  return x.read_available() == 0;
}
void writeInfoAfterN(vector<boost::lockfree::spsc_queue<int, boost::lockfree::capacity<10000>>>& q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>>& t, atomic<bool>* done, atomic<bool> *control, string fileName, const HeaderInfoAfter& ha, const HeaderInfoGen& hg, int countStop){
  //assert(q.size() < 20);
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double, std::milli> elapsed;
  ofstream out;
  out.open(fileName);
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
  //for_each(q.begin(), q.end(), mem_fn(&Spsc::pop));
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
          bool countCheck = true;
          for (int j = 0, lenj = q.size(); j < lenj; ++j){
            out << "    " << setw(13) << count[j];
            if (count[j] < countStop){
              countCheck = false;
            }
            if (countCheck){
              *control = true;
            }
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


inline static void correctCount(int &count, int next){
  int temp = count % OVER;
  if (temp < next){
    count += next - temp;
  }
  else if (temp > next){
    count += OVER + next - temp;
  }
}
void doWeinerCount(WeinerCounter *nim, double time, double sampleLength, double volt, const HeaderInfoGen &hg, const vector<string> &activePix, string fileName){
  HeaderInfoCounter hc;
  hc.pixels = activePix;
  hc.samplingLength = sampleLength;
  hc.timeLength = time;
  hc.voltage = volt;
  boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> q;
  boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
  atomic<bool> done = false;
  thread t2(writeWeinerCount, &q, &t, &done, fileName, hc, hg);
  readWeinerCount(&q, &t, &done, nim, time, sampleLength);
  t2.join();
}
static void writeWeinerCount(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, string fileName, const HeaderInfoCounter &ha, const HeaderInfoGen &hg){
  cimg_library::CImg<unsigned char> *img;
  cimg_library::CImgDisplay disp;
  int imgnum = 0;
  HGraph gr;
  this_thread::sleep_for(chrono::microseconds(1000));
  std::chrono::duration<double> elapsed;
  ofstream out;
  out.open(fileName);
  string temp;
  out << hg << ha;
  time_t time(nullptr);
  string tmp;
  tmp = "Start time: " + to_string(time);
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
  tempst = fileName.substr(0, fileName.size() - 4);
  tempst += ".root";
  TFile f(tempst.c_str(), "RECREATE");
  tempst = "TTree for panel " + hg.panelName + " filled with " + hg.gas + " at " + to_string(ha.voltage) + " (V) Weiner";
  TTree tr("w", tempst.c_str());
  char  tempPanel[200], tempSource[200], tempGas[200], tempSetup[200], tempRO[200], tempHV[200], tempTrigHV[200], tempTrigRO[200];
  strcpy(tempPanel, hg.panelName.c_str());
  strcpy(tempSource, hg.sourceName.c_str());
  strcpy(tempGas, hg.gas.c_str());
  strcpy(tempSetup, hg.sourceConfig.c_str());
  strcpy(tempRO, hg.roLines.c_str());
  strcpy(tempHV, hg.linesHV.c_str());
  strcpy(tempTrigHV, hg.triggerHV.c_str());
  strcpy(tempTrigRO, hg.triggerRO.c_str());
  Double_t tstamp, tempPress, tempVolt, tempDiscThr, tempQuench, tempNumHv, tempNumRo, tempAttenRo, tempAttenHV, tempSamp;
  tempPress = hg.pressure;
  tempVolt = ha.voltage;
  tempDiscThr = hg.discThresh;
  tempQuench = hg.quench;
  tempNumHv = hg.numHV;
  tempNumRo = hg.numRO;
  tempAttenRo = hg.attenRO;
  tempAttenHV = hg.attenHV;
  tempSamp = ha.samplingLength;
  tr.Branch("samp_dur", &tempSamp, "samp_dur/D");
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
  gr.makeGraphBmp(count);
   img = new cimg_library::CImg<unsigned char>("c1.bmp");
  disp.display(*img);
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
      gr.makeGraphBmp(count);
      delete img;
      img = new cimg_library::CImg<unsigned char>("c1.bmp");
      disp.display(*img);
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
    gr.makeGraphBmp(count);
    delete img;
    img = new cimg_library::CImg<unsigned char>("c1.bmp");
    disp.display(*img);
    q->pop();
    t->pop();
  }
  out.close();
  char buffer[50];
  sprintf(buffer, "hist%d.bmp", (int)elapsed.count());
  CopyFileA("c1.bmp", buffer, false);
  delete img;
  tr.Write();
  f.Save();
}
static void readWeinerCount(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, WeinerCounter *nim, double time, double intervalLength){
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
static void readWeinerCountInter(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, WeinerCounter *nim, double time, double intervalLength){
  array<int, 20> count;
  for (int i = 0; i < 20; ++i){
    count[i] = 0;
  }
  int numSamps = ceil(time / intervalLength);
  atomic<bool> control = true;
  thread t1(userInterrupt, &control);
  chrono::duration<int, milli> dur((int)(intervalLength * 1000) - 29);
  nim->resetAll();
  t->push(HighResClock::now());
  q->push(count);
  this_thread::sleep_for(dur);
  for (int i = 0; i < numSamps && control; ++i){
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
  control = false;
  *done = true;
  t1.join();
}
void doWeinerCountInter(WeinerCounter *nim, double time, double sampleLength, double volt, const HeaderInfoGen &hg, const vector<string> &activePix, string fileName){
  HeaderInfoCounter hc;
  hc.pixels = activePix;
  hc.samplingLength = sampleLength;
  hc.timeLength = time;
  hc.voltage = volt;
  boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> q;
  boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
  atomic<bool> done = false;
  thread t2(writeWeinerCount, &q, &t, &done, fileName, hc, hg);
  readWeinerCountInter(&q, &t, &done, nim, time, sampleLength);
  t2.join();
}
static void userInterrupt(atomic<bool> *t){
  cout << "Press Any key to stop reading." << endl;
  while (!_kbhit() && *t){
    this_thread::sleep_for(chrono::seconds(1));
  }
  if (*t){
    cout << "Readings stopped.." << endl;
  }
  *t = false;
}
void doWeinerCountInf(WeinerCounter *nim, double sampleLength, double volt, const HeaderInfoGen *hg, string fileName, atomic<bool> *run){
  HeaderInfoCounter hc;
  time_t time(nullptr);
  hc.samplingLength = sampleLength;
  hc.timeLength = 0;
  hc.voltage = volt;
  string runName;
  runName = ".\\CollectedData\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += hg->gas + "\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += hg->panelName + "_" + to_string(time);
  boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> q;
  boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
  atomic<bool> done = false;
  thread t2(writeWeinerCount, &q, &t, &done, runName, hc, *hg);
  readWeinerCountInf(&q, &t, &done, nim, sampleLength, run);
  t2.join();
}
static void readWeinerCountInf(boost::lockfree::spsc_queue<array<int, 20>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, WeinerCounter *nim, double intervalLength, atomic<bool> *run){
  array<int, 20> count;
  for (int i = 0; i < 20; ++i){
    count[i] = 0;
  }
  //atomic<bool> control = true;
  //thread t1(userInterrupt, &control);
  chrono::duration<int, milli> dur((int)(intervalLength * 1000) - 29);
  nim->resetAll();
  t->push(HighResClock::now());
  q->push(count);
  this_thread::sleep_for(dur);
 // for (int i = 0; *run == true; ){
 while (*run == true)
  {
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
  //t1.join();
}
void doVoltageScan(MotorController *mot, WeinerCounter *nim, VoltageControl *volt, Messages* message){
 // WeinerCounter *nim = nullptr;
  //VoltageControl *volt = nullptr;
  string path = ".\\CollectedData\\";
  string runName;
  ofstream log;
  int starting;
  int stop;
  int duration;
  int num;
  vector<int> x;
  vector<int> y;
  double freq;
  int step;
  char tempc;
  string temp;
  vector<string> pix;
  //cout << "------------------------------------------" << endl;
  //cout << "------------Voltage Scan------------------" << endl;
  //cout << "------------------------------------------" << endl;
  HeaderInfoGen hg;
  //while (1){
  //  cout << "generate header manually or read from a file?(file/manual): ";
  //  cin >> temp;
  //  cin.clear();
  //  cin.ignore(10000, '\n');
  //  if (temp == "manual"){
  //    makeGenHead(hg);
  //    break;
  //  }
  //  else if (temp == "file"){
  //    cout << "What is the name of the file? ";
  //    getline(cin, temp);
  //    makeGenHeadFile(hg, temp);
  //    break;
  //  }
  //  else{
  //    cout << "Invalid option" << endl;
  //  }
  //}
  //cout << "Start Voltage (V): ";
  //cin >> starting;
  //cin.clear();
  //cin.ignore(10000, '\n');
  //cout << "End Voltage (V): ";
  //cin >> stop;
  //cin.clear();
  //cin.ignore(10000, '\n');
  //if (stop < starting){
  //  cerr << "Invalid Voltages" << endl;
  //  exit(0);
  //}
  //cout << "Step Size (V): ";
  //cin >> step;
  //cout << "Interval duration (s): ";
  //cin >> duration;
  //cout << "Sampling frequency (s): ";
  //cin >> freq;
  //cout << "Number of Pixels being tested: ";
  //cin >> num;
  //cin.clear();
  //cin.ignore(10000, '\n');
  //x.resize(num);
  //y.resize(num);
  //for (int i = 0; i < num; ++i){
  //  cout << "RO # of pixel " << i + 1 << ": ";
  //  cin >> x[i];
  //  cin.clear();
  //  cin.ignore(10000, '\n');
  //  cout << "HV # of pixel " << i + 1 << ": ";
  //  cin >> y[i];
  //  pix.push_back(to_string(x[i]) + "-" + to_string(x[i]));
  //}


  time_t t = time(nullptr);
  // TODO: add identifier to first directory, possibly panel name?
  CreateDirectory(path.c_str(), NULL);
  runName = path + hg.gas + "\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += to_string((int)hg.pressure);
  runName += +"torr\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += hg.panelName + "_" + hg.gas + "_" + to_string((int)hg.pressure) + "_" + to_string(t) + "\\";
  CreateDirectory(runName.c_str(), NULL);
  log.open(runName + "log.txt", ofstream::ate);
  runName += "VoltageScan\\";
  CreateDirectory(runName.c_str(), NULL);
  log << "Intitalized Voltage Scan Run" << endl;
  log << "Starting: " << starting << endl;
  log << "Stop: " << stop << endl;
  log << "Step Size: " << step << endl;
  log << "Interval Duration: " << duration << endl;
  log << "Sampling Frequency: " << freq << endl;
  log << "Number of Pixels: " << num << endl;
  log << "Pixel List: " << endl;
  for (int i = 0; i < num; ++i){
    log << x[i] << "-" << y[i] << endl;
  }
  log << "Turning On High Voltage" << endl;
  volt->turnOn();

  if (hg.sourceConfig == "Dynamic"){
    for (int k = 0; k < num; ++k){
      log << "Switching to pixel " << x[k] << "-" << y[k] << endl; 
      mot->moveToPix(x[k], y[k]);
      for (int i = starting; i <= stop; i += step){
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        temp = runName + to_string(x[k]) + "_" + to_string(y[k]) + "_" + to_string(i) + "_sor_vs.txt";
        doWeinerCount(nim, duration, freq, i, hg, pix, temp);
        log << "Finished Counting" << endl;
      }
    }
  }
  else if (hg.sourceConfig == "Static"){
    mot->goToCenter();
    for (int i = starting; i <= stop; i += step){
      log << "Setting Voltage to: " << i << endl;
      volt->setVoltage(i);
      log << "Begin Counting" << endl;
      temp = runName + "all_" + to_string(i) + "_sor_vs.txt";
      doWeinerCount(nim, duration, freq, i, hg, pix, temp);
      log << "Finished Counting" << endl;
    }
  }
  else if (hg.sourceConfig == "User"){
    for (int k = 0; k < num; ++k){
      log << "Switching to pixel " << x[k] << "-" << y[k] << endl;
      cout << "Please move source to pixel " << x[k] << "-" << y[k] << endl;
      while (1){
        cout << "Has the source been moved? ";
        cin.get(tempc);
        cin.clear();
        cin.ignore(10000, '\n');
        if (tempc == 'y'){
          break;
        }
      }
      for (int i = starting; i <= stop; i += step){
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        temp = runName + to_string(x[k]) + "_" + to_string(y[k]) + "_" + to_string(i) + "_sor_vs.txt";
        doWeinerCount(nim, duration, freq, i, hg, pix, temp);
        log << "Finished Counting" << endl;
      }
    }
  }
  log << "Switching to background" << endl;
    
  if (hg.sourceConfig == "User"){
    Beep(900, 3000);
    cout << "Please remove the source for background run." << endl;
    while (1){
      cout << "Has the source been removed? ";
      cin.get(tempc);
      cin.clear();
      cin.ignore(10000, '\n');
      if (tempc == 'y'){
        break;
      }
    }
  }
  if (hg.sourceConfig == "Static" || hg.sourceConfig == "Dynamic"){
    mot->goToBackGround();
    //------------------------------
    //--------WARNING--------------
    //----------------------------
    //when a the motor is moved to the background location it always needs to be moved out in order to be used again
    //aka always call leaveBackGround() when done with taking a background measure ment
  }
  hg.sourceName = "bkg";
  for (int i = starting; i <= stop; i += step){
    log << "Setting Voltage to: " << i << endl;
    volt->setVoltage(i);
    log << "Begin Counting" << endl;
    temp = runName + to_string(i) + "_bkg_vs.txt";
    doWeinerCount(nim, duration, freq, i, hg, pix, temp);
    log << "Finished Counting" << endl;
  }
  if (hg.sourceConfig == "Static" || hg.sourceConfig == "Dynamic"){
    mot->leaveBackGround();
  }
  
  log << "Turning off High Voltage" << endl;
  volt->turnOff();
  log << "Voltage Scan Completed" << endl;
  log.close();
}

void doVoltageScanFile(MotorController* mot, WeinerCounter* nim, VoltageControl* volt){
  string path = ".\\CollectedData\\";
  string runName;
  ofstream log;
  int starting;
  int stop;
  int duration;
  int num;
  vector<int> x;
  vector<int> y;
  double freq;
  int step;
  char tempc;
  string temp;
  vector<string> pix;
  cout << "------------------------------------------" << endl;
  cout << "------------Voltage Scan------------------" << endl;
  cout << "------------------------------------------" << endl;
  HeaderInfoGen hg;
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
  do{
    cout << "What is the name of your run setup file? ";
    getline(cin, temp);
  } while (!makeVSRun(temp, starting, stop, step, duration, freq, num, x, y) && cout << "Invalid file, see readme for for setup." << endl);
  for (int i = 0; i < num; ++i){
    pix.push_back(to_string(x[i]) + "-" + to_string(x[i]));
  }


  time_t t = time(nullptr);
  CreateDirectory(path.c_str(), NULL);
  runName = path + hg.gas + "\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += to_string((int)hg.pressure);
  runName += +"torr\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += hg.panelName + "_" + hg.gas + "_" + to_string((int)hg.pressure) + "_" + to_string(t) + "\\";
  CreateDirectory(runName.c_str(), NULL);
  log.open(runName + "log.txt", ofstream::ate);
  runName += "VoltageScan\\";
  CreateDirectory(runName.c_str(), NULL);
  log << "Intitalized Voltage Scan Run" << endl;
  /*
  log << "Starting: " << starting << endl;
  log << "Stop: " << stop << endl;
  log << "Step Size: " << step << endl;
  log << "Interval Duration: " << duration << endl;
  log << "Sampling Frequency: " << freq << endl;
  log << "Number of Pixels: " << num << endl;
  log << "Pixel List: " << endl;
  */
  for (int i = 0; i < num; ++i){
    log << x[i] << "-" << y[i] << endl;
  }
  log << "Turning On High Voltage" << endl;
  volt->turnOn();

  if (hg.sourceConfig == "Dynamic"){
    for (int k = 0; k < num; ++k){
      log << "Switching to pixel " << x[k] << "-" << y[k] << endl;
      mot->moveToPix(x[k], y[k]);
      for (int i = starting; i <= stop; i += step){
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        temp = runName + to_string(x[k]) + "_" + to_string(y[k]) + "_" + to_string(i) + "_sor_vs.txt";
        doWeinerCount(nim, duration, freq, i, hg, pix, temp);
        log << "Finished Counting" << endl;
      }
    }
  }
  else if (hg.sourceConfig == "Static"){
    mot->goToCenter();
    for (int i = starting; i <= stop; i += step){
      log << "Setting Voltage to: " << i << endl;
      volt->setVoltage(i);
      log << "Begin Counting" << endl;
      temp = runName + "all_" + to_string(i) + "_sor_vs.txt";
      doWeinerCount(nim, duration, freq, i, hg, pix, temp);
      log << "Finished Counting" << endl;
    }
  }
  else if (hg.sourceConfig == "User"){
    for (int k = 0; k < num; ++k){
      log << "Switching to pixel " << x[k] << "-" << y[k] << endl;
      cout << "Please move source to pixel " << x[k] << "-" << y[k] << endl;
      while (1){
        cout << "Has the source been moved? ";
        cin.get(tempc);
        cin.clear();
        cin.ignore(10000, '\n');
        if (tempc == 'y'){
          break;
        }
      }
      for (int i = starting; i <= stop; i += step){
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        temp = runName + to_string(x[k]) + "_" + to_string(y[k]) + "_" + to_string(i) + "_sor_vs.txt";
        doWeinerCount(nim, duration, freq, i, hg, pix, temp);
        log << "Finished Counting" << endl;
      }
    }
  }
  log << "Switching to background" << endl;

  if (hg.sourceConfig == "User"){
    Beep(900, 3000);
    cout << "Please remove the source for background run." << endl;
    while (1){
      cout << "Has the source been removed? ";
      cin.get(tempc);
      cin.clear();
      cin.ignore(10000, '\n');
      if (tempc == 'y'){
        break;
      }
    }
  }
  if (hg.sourceConfig == "Static" || hg.sourceConfig == "Dynamic"){
    mot->goToBackGround();
    //------------------------------
    //--------WARNING--------------
    //----------------------------
    //when a the motor is moved to the background location it always needs to be moved out in order to be used again
    //aka always call leaveBackGround() when done with taking a background measure ment
  }
  hg.sourceName = "bkg";
  for (int i = starting; i <= stop; i += step){
    log << "Setting Voltage to: " << i << endl;
    volt->setVoltage(i);
    log << "Begin Counting" << endl;
    temp = runName + to_string(i) + "_bkg_vs.txt";
    doWeinerCount(nim, duration, freq, i, hg, pix, temp);
    log << "Finished Counting" << endl;
  }
  if (hg.sourceConfig == "Static" || hg.sourceConfig == "Dynamic"){
    mot->leaveBackGround();
  }

  log << "Turning off High Voltage" << endl;
  volt->turnOff();
  log << "Voltage Scan Completed" << endl;
  log.close();


}

void doAfterScanNoGraph(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
  string path = ".\\CollectedData\\";
  string runName;
  ofstream log;
  int starting;
  int stop;
  int step;
  int num;
  char tempc;
  int numSamples;
  vector<int> x;
  vector<int> y;
  string temp;
  
  cout << "------------------------------------------" << endl;
  cout << "----------After-Pulse Test----------------" << endl;
  cout << "------------------------------------------" << endl;
  HeaderInfoGen hg;
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
  cout << "Start Voltage (V): ";
  cin >> starting;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "End Voltage (V): ";
  cin >> stop;
  cin.clear();
  cin.ignore(10000, '\n');
  if (stop < starting){
    cerr << "Invalid Voltages" << endl;
    exit(0);
  }
  cout << "Step Size (V): ";
  cin >> step;
  cout << "Number of Pixels being tested: ";
  cin >> num;
  cin.clear();
  cin.ignore(10000, '\n');
  x.resize(num);
  y.resize(num);
  for (int i = 0; i < num; ++i){
    cout << "x-coordinate of pixel " << i + 1 << ": ";
    cin >> x[i];
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "y-coordinate of pixel " << i + 1 << ": ";
    cin >> y[i];
  }
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "how many samples should be take at each voltage?(default = 10000) ";
  cin>>numSamples;
  time_t t = time(nullptr);
  CreateDirectory(path.c_str(), NULL);
  runName = path + hg.gas + "\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += to_string((int)hg.pressure);
  runName += "torr\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += hg.panelName + "_" + hg.gas + "_" + to_string((int)hg.pressure) + "_" + to_string(t) + "\\";
  CreateDirectory(runName.c_str(), NULL);
  log.open(runName + "log.txt", ofstream::app);
  runName += "AfterPulse\\";
  CreateDirectory(runName.c_str(), NULL);
  log << "Intitalized After-Pulse Test" << endl;
  log << "Starting: " << starting << endl;
  log << "Stop: " << stop << endl;
  log << "Step Size: " << step << endl;
  log << "Number of Pixels: " << num << endl;
  log << "Pixel List: " << endl;
  for (int i = 0; i < num; ++i){
    log << x[i] << "-" << y[i] << endl;
  }


  log << "Turning On High Voltage" << endl;
  volt->turnOn();
  for (int k = 0; k < num; ++k){
    if (hg.sourceConfig == "User"){
      Beep(900, 1000);
      cout << "Please configure source for pixel " << x[k] << "-" << y[k] << endl;
      while (1){
        cout << "Is source placed correctly? (y/n): ";
        cin.clear();
        cin.ignore(10000, '\n');
        tempc = cin.get();
        if (tempc == 'y'){
          break;
        }
        cin.clear();
        cin.ignore(10000, '\n');
      }
    }
    log << "Switching to pixel " << x[k] << "-" << y[k] << endl;
    for (int i = starting; i <= stop; i += step){
      log << "Setting Voltage to: " << i << endl;
      volt->setVoltage(i);
      log << "Begin Counting" << endl;
      temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "AP.txt";
      doAfterPulse1(temp, nim, hg, x[k], y[k], i, numSamples);
      log << "Finished Counting" << endl;
    }
  }
  log << "Turning Off High Voltage" << endl;
  volt->turnOff();

  log << "After-Pulse Scan Completed" << endl;
  log.close();
}
void doAfterScanGraph(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
  string path = ".\\CollectedData\\";
  string runName;
  ofstream log;
  int starting;
  int stop;
  int step;
  int num;
  int numSamples;
  vector<int> x;
  vector<int> y;
  string temp;
  char tempc;
  cout << "------------------------------------------" << endl;
  cout << "----------After-Pulse Test----------------" << endl;
  cout << "------------------------------------------" << endl;
  HeaderInfoGen hg;
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
  cout << "Start Voltage (V): ";
  cin >> starting;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "End Voltage (V): ";
  cin >> stop;
  cin.clear();
  cin.ignore(10000, '\n');
  if (stop < starting){
    cerr << "Invalid Voltages" << endl;
    exit(0);
  }
  cout << "Step Size (V): ";
  cin >> step;
  cout << "Number of Pixels being tested: ";
  cin >> num;
  cin.clear();
  cin.ignore(10000, '\n');
  x.resize(num);
  y.resize(num);
  for (int i = 0; i < num; ++i){
    cout << "x-coordinate of pixel " << i + 1 << ": ";
    cin >> x[i];
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "y-coordinate of pixel " << i + 1 << ": ";
    cin >> y[i];
  }
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "how many samples should be take at each voltage?(default = 10000) ";
  cin >> numSamples;
  /*
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "What interval length should be used (ms)?";
  cin >> intLength;
  */
  time_t t = time(nullptr);
  CreateDirectory(path.c_str(), NULL);
  runName = path + hg.gas + "\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += to_string((int)hg.pressure);
  runName += "torr\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += hg.panelName + "_" + hg.gas + "_" + to_string((int)hg.pressure) + "_" + to_string(t) + "\\";
  CreateDirectory(runName.c_str(), NULL);
  log.open(runName + "log.txt", ofstream::app);
  runName += "AfterPulse\\";
  CreateDirectory(runName.c_str(), NULL);
  log << "Intitalized After-Pulse Test" << endl;
  log << "Starting: " << starting << endl;
  log << "Stop: " << stop << endl;
  log << "Step Size: " << step << endl;
  log << "Number of Pixels: " << num << endl;
  log << "Pixel List: " << endl;
  for (int i = 0; i < num; ++i){
    log << x[i] << "-" << y[i] << endl;
  }
  log << "Turning On High Voltage" << endl;
  volt->turnOn();
  for (int k = 0; k < num; ++k){
    if (hg.sourceConfig == "User"){
      Beep(900, 1000);
      cout << "Please configure source for pixel " << x[k] << "-" << y[k] << endl;
      while (1){
        cout << "Is source placed correctly? (y/n): ";
        cin.clear();
        cin.ignore(10000, '\n');
        tempc = cin.get();
        if (tempc == 'y'){
          break;
        }
        cin.clear();
        cin.ignore(10000, '\n');
      }
    }
    log << "Switching to pixel " << x[k] << "-" << y[k] << endl;
    for (int i = starting; i <= stop; i += step){
      log << "Setting Voltage to: " << i << endl;
      volt->setVoltage(i);
      log << "Begin Counting" << endl;
      temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "AP.txt";
      doAfterPulse1(temp, nim, hg, x[k], y[k], i, numSamples);
      log << "Finished Counting" << endl;
    }
  }
  log << "Turning Off High Voltage" << endl;
  volt->turnOff();

  log << "After-Pulse Scan Completed" << endl;
  log << "Creating Graphs" << endl;
  //makeApGraphs1(runName, intLength);
  //makeApIntGraph1(runName, intLength);
  //makeApDiffGraph1(runName);
  log.close();
}

void doAfterScanGraphMulti(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){

  string path = ".\\CollectedData\\";
  string runName;
  ofstream log;
  int starting;
  int stop;
  int step;
  int num;
  int numMeas = 1;
  int tempNum;
  int numSamples;
  int intLength;
  vector<int> x;
  vector<int> y;
  string temp;
  char tempc;
  cout << "------------------------------------------" << endl;
  cout << "----------After-Pulse Test----------------" << endl;
  cout << "------------------------------------------" << endl;
  HeaderInfoGen hg;
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
  cout << "Start Voltage (V): ";
  cin >> starting;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "End Voltage (V): ";
  cin >> stop;
  cin.clear();
  cin.ignore(10000, '\n');
  if (stop < starting){
    cerr << "Invalid Voltages" << endl;
    exit(0);
  }
  cout << "Step Size (V): ";
  cin >> step;
  cout << "Number of Pixels being tested: ";
  cin >> num;
  cin.clear();
  cin.ignore(10000, '\n');
  x.resize(num);
  y.resize(num);
  for (int i = 0; i < num; ++i){
    cout << "RO # of pixel " << i + 1 << ": ";
    cin >> x[i];
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "HV # of pixel " << i + 1 << ": ";
    cin >> y[i];
  }
  if (hg.sourceConfig == "Static"){
    cout << "How many pixels should be measured at once? ";
    cin >> numMeas;
    if (numMeas > num){
      cout << "# measured at once > # pixels" << endl;
      cout << "measuring all pixels at once" << endl;
      numMeas = num;
    }

    if (!((numMeas > 0 && numMeas < 6) || (numMeas == 10))){
      cerr << "That number of measurement has not been implemented. Your measurements will be split" << endl;
      cerr << "Please contact mausilio@umich.edu for help" << endl;
    }
    else if (num % numMeas != 0){
      cout << "Warning Pixels will not be measured in the same number of sets" << endl;
    }
    mot->goToCenter();
  }
  else if (hg.sourceConfig == "Dynamic"){
    numMeas = 1;
  }
  else if (hg.sourceConfig == "User"){
    numMeas = 1;
  }
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "how many samples should be take at each voltage?(default = 10000) ";
  cin >> numSamples;
  /*
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "What interval length should be used (ms)?";
  cin >> intLength;
  */
  time_t t = time(nullptr);
  CreateDirectory(path.c_str(), NULL);
  runName = path + hg.gas + "\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += to_string((int)hg.pressure);
  runName += "torr\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += hg.panelName + "_" + hg.gas + "_" + to_string((int)hg.pressure) + "_" + to_string(t) + "\\";
  CreateDirectory(runName.c_str(), NULL);
  log.open(runName + "log.txt", ofstream::app);
  runName += "AfterPulse\\";
  CreateDirectory(runName.c_str(), NULL);
  log << "Intitalized After-Pulse Test" << endl;
  log << "Starting: " << starting << endl;
  log << "Stop: " << stop << endl;
  log << "Step Size: " << step << endl;
  log << "Number of Pixels: " << num << endl;
  log << "Pixel List: " << endl;
  for (int i = 0; i < num; ++i){
    log << x[i] << "-" << y[i] << endl;
  }
  log << "Turning On High Voltage" << endl;
  volt->turnOn();
  if (numMeas == 1){
    for (int k = 0; k < num; ++k){
      if (hg.sourceConfig == "User"){
        Beep(900, 1000);
        cout << "Please configure source for pixel " << x[k] << "-" << y[k] << endl;
        while (1){
          cout << "Is source placed correctly? (y/n): ";
          cin.clear();
          cin.ignore(10000, '\n');
          tempc = cin.get();
          if (tempc == 'y'){
            break;
          }
          cin.clear();
          cin.ignore(10000, '\n');
        }
      }
      if (hg.sourceConfig == "Dynamic"){
        mot->moveToPix(x[k], y[k]);
      }
      log << "Switching to pixel " << x[k] << "-" << y[k] << endl;
      for (int i = starting; i <= stop; i += step){
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "AP.txt";
        doAfterPulse1(temp, nim, hg, x[k], y[k], i, numSamples);
        log << "Finished Counting" << endl;
      }
    }
  }
  else{
    for (int k = 0; k < num; k += numMeas){
      for (int i = starting; i <= stop; i += step){
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        if (k + numMeas > num){
          tempNum = k - num;
        }
        else{
          tempNum = numMeas;
        }
        temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(k - num) + "AP.txt";
        switch (tempNum){
        case 1:
          doAfterPulse1(temp, nim, hg, x[k], y[k], i, numSamples);
          break;
        case 2:
          doAfterPulse2(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], i, numSamples);
          break;
        case 3:
          doAfterPulse3(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], i,numSamples);
          break;
        case 4:
          doAfterPulse4(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], i, numSamples);
          break;
        case 5:
          doAfterPulse5(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], x[k + 4], y[k + 4], i, numSamples);
          break;
        case 6:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(3) + "AP.txt";
          doAfterPulse3(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], i, numSamples);
          temp = runName + to_string(x[k + 3]) + "-" + to_string(y[k + 3]) + "_" + to_string(i) + "_" + to_string(3) + "AP.txt";
          doAfterPulse3(temp, nim, hg, x[k + 3], y[k + 3], x[k + 4], y[k + 4], x[k + 5], y[k + 5], i, numSamples);
          break;
        case 7:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], i, numSamples);
          temp = runName + to_string(x[k + 4]) + "-" + to_string(y[k + 4]) + "_" + to_string(i) + "_" + to_string(3) + "AP.txt";
          doAfterPulse3(temp, nim, hg, x[k + 4], y[k + 4], x[k + 5], y[k + 5], x[k + 6], y[k + 6], i, numSamples);
        case 8:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], i, numSamples);
          temp = runName + to_string(x[k + 4]) + "-" + to_string(y[k + 4]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k + 4], y[k + 4], x[k + 5], y[k + 5], x[k + 6], y[k + 6], x[k + 7], y[k + 7], i, numSamples);
        case 9:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(5) + "AP.txt";
          doAfterPulse5(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], x[k + 4], y[k + 4], i, numSamples);
          temp = runName + to_string(x[k + 5]) + "-" + to_string(y[k + 5]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k + 5], y[k + 5], x[k + 6], y[k + 6], x[k + 7], y[k + 7], x[k + 8], y[k + 8], i, numSamples);
        case 10:
          doAfterPulse10(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], x[k + 4], y[k + 4], x[k + 5], x[k + 5], x[k + 6], y[k + 6], x[k + 7], y[k + 7], x[k + 8], y[k + 8], x[k + 9], y[k + 9], i, numSamples);
          break;
        default:
          break;
        }
        log << "Finished Counting" << endl;
      }
    }
    log << "Creating Graphs" << endl;
  }



  log << "Turning Off High Voltage" << endl;
  volt->turnOff();
  log << "After-Pulse Scan Completed" << endl;
  log.close();
}
void doAfterScanGraphMultiAndBack(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){

  string path = ".\\CollectedData\\";
  string runName;
  ofstream log;
  int starting;
  int stop;
  int step;
  int num;
  int numMeas = 1;
  int tempNum;
  int numSamples;
  int intLength;
  vector<int> x;
  vector<int> y;
  string temp;
  char tempc;
  cout << "------------------------------------------" << endl;
  cout << "----------After-Pulse Test----------------" << endl;
  cout << "------------------------------------------" << endl;
  HeaderInfoGen hg;
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
  cout << "Start Voltage (V): ";
  cin >> starting;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "End Voltage (V): ";
  cin >> stop;
  cin.clear();
  cin.ignore(10000, '\n');
  if (stop < starting){
    cerr << "Invalid Voltages" << endl;
    exit(0);
  }
  cout << "Step Size (V): ";
  cin >> step;
  cout << "Number of Pixels being tested: ";
  cin >> num;
  cin.clear();
  cin.ignore(10000, '\n');
  x.resize(num);
  y.resize(num);
  for (int i = 0; i < num; ++i){
    cout << "RO # of pixel " << i + 1 << ": ";
    cin >> x[i];
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "HV # of pixel " << i + 1 << ": ";
    cin >> y[i];
  }
  if (hg.sourceConfig == "Static"){
    cout << "How many pixels should be measured at once? ";
    cin >> numMeas;
    if (numMeas > num){
      cout << "# measured at once > # pixels" << endl;
      cout << "measuring all pixels at once" << endl;
      numMeas = num;
    }

    if (!((numMeas > 0 && numMeas < 6) || (numMeas == 10))){
      cerr << "That number of measurement has not been implemented. Your measurements will be split" << endl;
      cerr << "Please contact mausilio@umich.edu for help" << endl;
    }
    else if (num % numMeas != 0){
      cout << "Warning Pixels will not be measured in the same number of sets" << endl;
    }
    mot->goToCenter();
  }
  else if (hg.sourceConfig == "Dynamic"){
    numMeas = 1;
  }
  else if (hg.sourceConfig == "User"){
    numMeas = 1;
  }
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "how many samples should be take at each voltage?(default = 10000) ";
  cin >> numSamples;
  /*
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "What interval length should be used (ms)?";
  cin >> intLength;
  */
  time_t t = time(nullptr);
  CreateDirectory(path.c_str(), NULL);
  runName = path + hg.gas + "\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += to_string((int)hg.pressure);
  runName += "torr\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += hg.panelName + "_" + hg.gas + "_" + to_string((int)hg.pressure) + "_" + to_string(t) + "\\";
  CreateDirectory(runName.c_str(), NULL);
  log.open(runName + "log.txt", ofstream::app);
  runName += "AfterPulse\\";
  CreateDirectory(runName.c_str(), NULL);
  log << "Intitalized After-Pulse Test" << endl;
  log << "Starting: " << starting << endl;
  log << "Stop: " << stop << endl;
  log << "Step Size: " << step << endl;
  log << "Number of Pixels: " << num << endl;
  log << "Pixel List: " << endl;
  for (int i = 0; i < num; ++i){
    log << x[i] << "-" << y[i] << endl;
  }
  log << "Turning On High Voltage" << endl;
  volt->turnOn();
  if (numMeas == 1){
    for (int k = 0; k < num; ++k){
      if (hg.sourceConfig == "User"){
        Beep(900, 1000);
        cout << "Please configure source for pixel " << x[k] << "-" << y[k] << endl;
        while (1){
          cout << "Is source placed correctly? (y/n): ";
          cin.clear();
          cin.ignore(10000, '\n');
          tempc = cin.get();
          if (tempc == 'y'){
            break;
          }
          cin.clear();
          cin.ignore(10000, '\n');
        }
      }
      if (hg.sourceConfig == "Dynamic"){
        mot->moveToPix(x[k], y[k]);
      }
      log << "Switching to pixel " << x[k] << "-" << y[k] << endl;
      for (int i = starting; i <= stop; i += step){
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "AP.txt";
        doAfterPulse1(temp, nim, hg, x[k], y[k], i, numSamples);
        log << "Finished Counting" << endl;
      }
    }
  }
  else{
    for (int k = 0; k < num; k += numMeas){
      for (int i = starting; i <= stop; i += step){
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        if (k + numMeas > num){
          tempNum = k - num;
        }
        else{
          tempNum = numMeas;
        }
        temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(k - num) + "AP.txt";
        switch (tempNum){
        case 1:
          doAfterPulse1(temp, nim, hg, x[k], y[k], i, numSamples);
          break;
        case 2:
          doAfterPulse2(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], i, numSamples);
          break;
        case 3:
          doAfterPulse3(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], i, numSamples);
          break;
        case 4:
          doAfterPulse4(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], i, numSamples);
          break;
        case 5:
          doAfterPulse5(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], x[k + 4], y[k + 4], i, numSamples);
          break;
        case 6:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(3) + "AP.txt";
          doAfterPulse3(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], i, numSamples);
          temp = runName + to_string(x[k + 3]) + "-" + to_string(y[k + 3]) + "_" + to_string(i) + "_" + to_string(3) + "AP.txt";
          doAfterPulse3(temp, nim, hg, x[k + 3], y[k + 3], x[k + 4], y[k + 4], x[k + 5], y[k + 5], i, numSamples);
          break;
        case 7:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], i, numSamples);
          temp = runName + to_string(x[k + 4]) + "-" + to_string(y[k + 4]) + "_" + to_string(i) + "_" + to_string(3) + "AP.txt";
          doAfterPulse3(temp, nim, hg, x[k + 4], y[k + 4], x[k + 5], y[k + 5], x[k + 6], y[k + 6], i, numSamples);
        case 8:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], i, numSamples);
          temp = runName + to_string(x[k + 4]) + "-" + to_string(y[k + 4]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k + 4], y[k + 4], x[k + 5], y[k + 5], x[k + 6], y[k + 6], x[k + 7], y[k + 7], i, numSamples);
        case 9:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(5) + "AP.txt";
          doAfterPulse5(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], x[k + 4], y[k + 4], i, numSamples);
          temp = runName + to_string(x[k + 5]) + "-" + to_string(y[k + 5]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k + 5], y[k + 5], x[k + 6], y[k + 6], x[k + 7], y[k + 7], x[k + 8], y[k + 8], i, numSamples);
        case 10:
          doAfterPulse10(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], x[k + 4], y[k + 4], x[k + 5], x[k + 5], x[k + 6], y[k + 6], x[k + 7], y[k + 7], x[k + 8], y[k + 8], x[k + 9], y[k + 9], i, numSamples);
          break;
        default:
          break;
        }
        log << "Finished Counting" << endl;
      }
    }
    log << "Creating Graphs" << endl;
  }
  log << "Switching to background" << endl;
  
  if (hg.sourceConfig == "User"){
    Beep(900, 3000);
    cout << "Please remove the source for background run." << endl;
    while (1){
      cout << "Has the source been removed? ";
      cin.get(tempc);
      cin.clear();
      cin.ignore(10000, '\n');
      if (tempc == 'y'){
        break;
      }
    }
  }
  
  else if (hg.sourceConfig == "Static" || hg.sourceConfig == "Dynamic"){
    mot->goToBackGround();
    //------------------------------
    //--------WARNING--------------
    //----------------------------
    //when a the motor is moved to the background location it always needs to be moved out in order to be used again
    //aka always call leaveBackGround() when done with taking a background measure ment
  }
  vector<string> pix;
  for (int i = 0; i < num; ++i){
    pix.push_back(to_string(x[i]) + "-" + to_string(y[i]));
  }
  hg.sourceName = "bkg";
  for (int i = starting; i <= stop; i += step){
    log << "Setting Voltage to: " << i << endl;
    volt->setVoltage(i);
    log << "Begin Counting" << endl;
    temp = runName + to_string(i) + "_bkg_vs.txt";
    doWeinerCount(nim, 10*60, 1, i, hg, pix, temp);
    log << "Finished Counting" << endl;
  }
  if (hg.sourceConfig == "Static" || hg.sourceConfig == "Dynamic"){
    mot->leaveBackGround();
  }


  log << "Turning Off High Voltage" << endl;
  volt->turnOff();
  log << "After-Pulse Scan Completed" << endl;
  log.close();
}
void doAfterScanGraphMultiAdapt(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){
  string path = ".\\CollectedData\\";
  string runName;
  ofstream log;
  int starting;
  int stop;
  int step;
  int num;
  double rate;
  int numMeas = 1;
  int tempNum;
  int numSamples;
  int prop;
  vector<int> x;
  vector<int> y;
  string temp;
  char tempc;
  cout << "------------------------------------------" << endl;
  cout << "----------After-Pulse Test----------------" << endl;
  cout << "------------------------------------------" << endl;
  HeaderInfoGen hg;
  while (1) {
    cout << "generate header manually or read from a file?(file/manual): ";
    cin >> temp;
    cin.clear();
    cin.ignore(10000, '\n');
    if (temp == "manual") {
      makeGenHead(hg);
      break;
    }
    else if (temp == "file") {
      cout << "What is the name of the file? ";
      getline(cin, temp);
      makeGenHeadFile(hg, temp);
      break;
    }
    else {
      cout << "Invalid option" << endl;
    }
  }
  cout << "Start Voltage (V): ";
  cin >> starting;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "End Voltage (V): ";
  cin >> stop;
  cin.clear();
  cin.ignore(10000, '\n');
  if (stop < starting) {
    cerr << "Invalid Voltages" << endl;
    exit(0);
  }
  cout << "Step Size (V): ";
  cin >> step;
  cout << "Number of Pixels being tested: ";
  cin >> num;
  cin.clear();
  cin.ignore(10000, '\n');
  x.resize(num);
  y.resize(num);
  for (int i = 0; i < num; ++i) {
    cout << "RO # of pixel " << i + 1 << ": ";
    cin >> x[i];
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "HV # of pixel " << i + 1 << ": ";
    cin >> y[i];
  }
  if (hg.sourceConfig == "Static") {
    cout << "How many pixels should be measured at once? ";
    cin >> numMeas;
    if (numMeas > num) {
      cout << "# measured at once > # pixels" << endl;
      cout << "measuring all pixels at once" << endl;
      numMeas = num;
    }

    if (!((numMeas > 0 && numMeas < 6) || (numMeas == 10))) {
      cerr << "That number of measurement has not been implemented. Your measurements will be split" << endl;
      cerr << "Please contact mausilio@umich.edu for help" << endl;
    }
    else if (num % numMeas != 0) {
      cout << "Warning Pixels will not be measured in the same number of sets" << endl;
    }
  }
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "how many samples should be take at each voltage?(default = 10000) ";
  cin >> numSamples;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "What proportion of accidentals is acceptable?(0,1) ";
  cin >> prop;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "What is the source rate (for an individual pixel)? ";
  cin >> rate;
  time_t t = time(nullptr);
  CreateDirectory(path.c_str(), NULL);
  runName = path + hg.gas + "\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += to_string((int)hg.pressure);
  runName += "torr\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += hg.panelName + "_" + hg.gas + "_" + to_string((int)hg.pressure) + "_" + to_string(t) + "\\";
  CreateDirectory(runName.c_str(), NULL);
  log.open(runName + "log.txt", ofstream::app);
  runName += "AfterPulse\\";
  CreateDirectory(runName.c_str(), NULL);
  log << "Intitalized After-Pulse Test" << endl;
  log << "Starting: " << starting << endl;
  log << "Stop: " << stop << endl;
  log << "Step Size: " << step << endl;
  log << "Number of Pixels: " << num << endl;
  log << "Pixel List: " << endl;
  for (int i = 0; i < num; ++i) {
    log << x[i] << "-" << y[i] << endl;
  }
  log << "Turning On High Voltage" << endl;
  volt->turnOn();
  if (numMeas == 1) {
    for (int k = 0; k < num; ++k) {
      if (hg.sourceConfig == "User") {
        Beep(900, 1000);
        cout << "Please configure source for pixel " << x[k] << "-" << y[k] << endl;
        while (1) {
          cout << "Is source placed correctly? (y/n): ";
          cin.clear();
          cin.ignore(10000, '\n');
          tempc = cin.get();
          if (tempc == 'y') {
            break;
          }
          cin.clear();
          cin.ignore(10000, '\n');
        }
      }
      log << "Switching to pixel " << x[k] << "-" << y[k] << endl;
      for (int i = starting; i <= stop; i += step) {
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "AP.txt";
        doAfterPulse1(temp, nim, hg, x[k], y[k], i, numSamples);
        log << "Finished Counting" << endl;
      }
    }
    log << "Creating Graphs" << endl;
    makeApGraphs1Adapt(runName,prop);
  }
  else {
    for (int k = 0; k < num; k += numMeas) {
      for (int i = starting; i <= stop; i += step) {
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        if (k + numMeas > num) {
          tempNum = k - num;
        }
        else {
          tempNum = numMeas;
        }
        temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(k - num) + "AP.txt";
        switch (tempNum) {
        case 1:
          doAfterPulse1(temp, nim, hg, x[k], y[k], i, numSamples);
          break;
        case 2:
          doAfterPulse2(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], i, numSamples);
          break;
        case 3:
          doAfterPulse3(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], i, numSamples);
          break;
        case 4:
          doAfterPulse4(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], i, numSamples);
          break;
        case 5:
          doAfterPulse5(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], x[k + 4], y[k + 4], i, numSamples);
          break;
        case 6:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(3) + "AP.txt";
          doAfterPulse3(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], i, numSamples);
          temp = runName + to_string(x[k + 3]) + "-" + to_string(y[k + 3]) + "_" + to_string(i) + "_" + to_string(3) + "AP.txt";
          doAfterPulse3(temp, nim, hg, x[k + 3], y[k + 3], x[k + 4], y[k + 4], x[k + 5], y[k + 5], i, numSamples);
          break;
        case 7:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], i, numSamples);
          temp = runName + to_string(x[k + 4]) + "-" + to_string(y[k + 4]) + "_" + to_string(i) + "_" + to_string(3) + "AP.txt";
          doAfterPulse3(temp, nim, hg, x[k + 4], y[k + 4], x[k + 5], y[k + 5], x[k + 6], y[k + 6], i, numSamples);
        case 8:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], i, numSamples);
          temp = runName + to_string(x[k + 4]) + "-" + to_string(y[k + 4]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k + 4], y[k + 4], x[k + 5], y[k + 5], x[k + 6], y[k + 6], x[k + 7], y[k + 7], i, numSamples);
        case 9:
          temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(5) + "AP.txt";
          doAfterPulse5(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], x[k + 4], y[k + 4], i, numSamples);
          temp = runName + to_string(x[k + 5]) + "-" + to_string(y[k + 5]) + "_" + to_string(i) + "_" + to_string(4) + "AP.txt";
          doAfterPulse4(temp, nim, hg, x[k + 5], y[k + 5], x[k + 6], y[k + 6], x[k + 7], y[k + 7], x[k + 8], y[k + 8], i, numSamples);
        case 10:
          doAfterPulse10(temp, nim, hg, x[k], y[k], x[k + 1], y[k + 1], x[k + 2], y[k + 2], x[k + 3], y[k + 3], x[k + 4], y[k + 4], x[k + 5], x[k + 5], x[k + 6], y[k + 6], x[k + 7], y[k + 7], x[k + 8], y[k + 8], x[k + 9], y[k + 9], i, numSamples);
          break;
        default:
          break;
        }
        log << "Finished Counting" << endl;
      }
    }
    log << "Creating Graphs" << endl;
    makeApGraphsNAdapt(runName, prop);
  }



  log << "Turning Off High Voltage" << endl;
  volt->turnOff();
  log << "After-Pulse Scan Completed" << endl;
  log.close();
}

void doAfterScanGraphMultiCount(MotorController *mot, WeinerCounter *nim, VoltageControl *volt){

  string path = ".\\CollectedData\\";
  string runName;
  ofstream log;
  int starting;
  int stop;
  int step;
  int num;
  int numMeas = 1;
  int tempNum;
  int numSamples;
  int intLength;
  int maxCount;
  vector<int> x;
  vector<int> y;
  string temp;
  char tempc;
  cout << "------------------------------------------" << endl;
  cout << "----------After-Pulse Test----------------" << endl;
  cout << "------------------------------------------" << endl;
  HeaderInfoGen hg;
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
  cout << "Start Voltage (V): ";
  cin >> starting;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "End Voltage (V): ";
  cin >> stop;
  cin.clear();
  cin.ignore(10000, '\n');
  if (stop < starting){
    cerr << "Invalid Voltages" << endl;
    exit(0);
  }
  cout << "Step Size (V): ";
  cin >> step;
  cout << "Number of Pixels being tested: ";
  cin >> num;
  cin.clear();
  cin.ignore(10000, '\n');
  x.resize(num);
  y.resize(num);
  for (int i = 0; i < num; ++i){
    cout << "RO # of pixel " << i + 1 << ": ";
    cin >> x[i];
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "HV # of pixel " << i + 1 << ": ";
    cin >> y[i];
  }
  if (hg.sourceConfig == "Static"){
    cout << "How many pixels should be measured at once? ";
    cin >> numMeas;
    if (numMeas > num){
      cout << "# measured at once > # pixels" << endl;
      cout << "measuring all pixels at once" << endl;
      numMeas = num;
    }
    else if (num % numMeas != 0){
      cout << "Warning Pixels will not be measured in the same number of sets" << endl;
    }
    mot->goToCenter();
  }
  else if (hg.sourceConfig == "Dynamic"){
    numMeas = 1;
  }
  else if (hg.sourceConfig == "User"){
    numMeas = 1;
  }
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "how many samples, at most, should be take at each voltage?(default = 10000) ";
  cin >> numSamples;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "What is the maximum number of counts each line should read? ";
  cin >> maxCount;
  /*
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "What interval length should be used (ms)?";
  cin >> intLength;
  */
  time_t t = time(nullptr);
  CreateDirectory(path.c_str(), NULL);
  runName = path + hg.gas + "\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += to_string((int)hg.pressure);
  runName += "torr\\";
  CreateDirectory(runName.c_str(), NULL);
  runName += hg.panelName + "_" + hg.gas + "_" + to_string((int)hg.pressure) + "_" + to_string(t) + "\\";
  CreateDirectory(runName.c_str(), NULL);
  log.open(runName + "log.txt", ofstream::app);
  runName += "AfterPulse\\";
  CreateDirectory(runName.c_str(), NULL);
  log << "Intitalized After-Pulse Test" << endl;
  log << "Starting: " << starting << endl;
  log << "Stop: " << stop << endl;
  log << "Step Size: " << step << endl;
  log << "Number of Pixels: " << num << endl;
  log << "Pixel List: " << endl;
  for (int i = 0; i < num; ++i){
    log << x[i] << "-" << y[i] << endl;
  }
  log << "Turning On High Voltage" << endl;
  volt->turnOn();
    for (int k = 0; k < num; k += numMeas){
      for (int i = starting; i <= stop; i += step){
        if (hg.sourceConfig == "User" && numMeas == 1){
          Beep(900, 1000);
          cout << "Please configure source for pixel " << x[k] << "-" << y[k] << endl;
          while (1){
            cout << "Is source placed correctly? (y/n): ";
            cin.clear();
            cin.ignore(10000, '\n');
            tempc = cin.get();
            if (tempc == 'y'){
              break;
            }
            cin.clear();
            cin.ignore(10000, '\n');
          }
          log << "Switching to pixel " << x[k] << "-" << y[k] << endl;
        }
        if (hg.sourceConfig == "Dynamic" && numMeas == 1){
          mot->moveToPix(x[k], y[k]);
          log << "Switching to pixel " << x[k] << "-" << y[k] << endl;
        }
        log << "Setting Voltage to: " << i << endl;
        volt->setVoltage(i);
        log << "Begin Counting" << endl;
        if (k + numMeas > num){
          tempNum = k - num;
        }
        else{
          tempNum = numMeas;
        }
        temp = runName + to_string(x[k]) + "-" + to_string(y[k]) + "_" + to_string(i) + "_" + to_string(k - num) + "AP.txt";
        vector<int> tempX(x.begin() + k, x.begin() + k + tempNum);
        vector<int> tempY(y.begin() + k, y.begin() + k + tempNum);
        doAfterPulseNCountStop(temp, nim, hg, tempX, tempY, i, maxCount, numSamples);
        log << "Finished Counting" << endl;
      }
    }
  log << "Turning Off High Voltage" << endl;
  volt->turnOff();
  log << "After-Pulse Scan Completed" << endl;
  log.close();
}

int findLineWithLowestRate(WeinerCounter *nim, const vector<int> &lines){
  array<int, 20> count;
  for (int i = 0; i < 20; ++i){
    count[i] = 0;
  }
  int numSamps = 60 * 1;
  chrono::duration<int, milli> dur((int)(1* 1000) - 29);
  nim->resetAll();
  HighResClock::time_point start = HighResClock::now();
  this_thread::sleep_for(dur);
  for (int i = 0; i < numSamps; ++i){
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
  HighResClock::time_point end = HighResClock::now();
  int minLine, minCount;
  minLine = lines[0];
  minCount = count[lines[0]-1];
  for (int i = 1, len = lines.size(); i < len; ++i){
    if (minCount > count[i] && count[i] > 0){
      minLine = lines[i];
      minCount = count[lines[i]-1];
    }
  }
  return minLine;
}
double findHighestRate(WeinerCounter *nim, const vector<int> &lines){
  array<int, 20> count;
  for (int i = 0; i < 20; ++i){
    count[i] = 0;
  }
  int numSamps = 60 * 1;
  chrono::duration<int, milli> dur((int)(1 * 1000) - 29);
  nim->resetAll();
  HighResClock::time_point start = HighResClock::now();
  this_thread::sleep_for(dur);
  for (int i = 0; i < numSamps; ++i){
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
  HighResClock::time_point end = HighResClock::now();
  int maxLine, maxCount;
  maxLine = lines[0];
  maxCount = count[lines[0] - 1];
  for (int i = 1, len = lines.size(); i < len; ++i){
    if (maxCount < count[i] && count[i] > 0){
      maxLine = lines[i];
      maxCount = count[lines[i] - 1];
    }
  }
  //double temp  = end.time_since_epoch-start.time_since_epoch();
  //return maxCount / temp;
  cout << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << endl;
  return maxCount / std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  return 0;
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
	int motbegin = 0, motend = message->maxOffsetY, motstep = message->maxStepY;
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
						doWeinerCount(nim, message->time, message->frequency, j, *header, pix, temp);
						log << "Finished Counting" << endl;

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

	boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> t;
	atomic<bool> done = false;
	thread t2(writeInfoAfterAny, &q, &t, &done, fileName, ha, hg, readout);
	readFromPixAfterAny(&done, &q, &t, nim, readout, run);
	t2.join();
}

static void readFromPixAfterAny(atomic<bool> *done, boost::lockfree::spsc_queue<vector<int>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, WeinerCounter *nim, Readout* readout, atomic<bool>* run){
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

static void writeInfoAfterAny(boost::lockfree::spsc_queue<vector<int>, boost::lockfree::capacity<10000>> *q, boost::lockfree::spsc_queue<HighResClock::time_point, boost::lockfree::capacity<10000>> *t, atomic<bool> *done, string fileName, const HeaderInfoAfter &ha, const HeaderInfoGen &hg, Readout* readout){
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