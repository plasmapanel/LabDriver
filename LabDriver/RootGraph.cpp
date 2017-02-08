#include "RootGraph.h"
HGraph::HGraph(){
  gErrorIgnoreLevel = kWarning;
  c1 = new TCanvas("c1", "Count So Far", 200, 10, 700, 500);
  gr = new TH1I("gr", "Count So Far", 20, .5, 20.5);
  gr->GetXaxis()->SetTitle("Channel");
  gr->GetXaxis()->SetRange(1, 19);
  gr->GetYaxis()->SetTitle("Count");
  gr->SetStats(0);
  gr->Draw();
}
void HGraph::makeGraphBmp(int arr[20]){
  for (int i = 0; i < 20; ++i){
    gr->SetBinContent(i + 1, arr[i]);
  }
  c1->Update();
  c1->SaveAs("c1.bmp");
}

void HGraph::makeGraphBmp(vector<int> arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		gr->SetBinContent(i + 1, arr[i]);
	}
	c1->Update();
	c1->SaveAs("c1.bmp");
}

HGraph::~HGraph(){
  delete c1;
  delete gr;
}
void makeApGraphs1(string path, int intervalSize){
  //path = '.' + path;
  ifstream file;
  string searchPat = "*AP.txt";
  string full = path + searchPat;
  WIN32_FIND_DATA find;
  HANDLE hand;
  hand = FindFirstFile(full.c_str(), &find);
  string nowdir = gSystem->WorkingDirectory();
  string temp;
  int prevCount;
  int firstC;
  double firstT;
  double tempd;
  int tempi;

  string gas;
  int press;
  int voltage;
  int pixX;
  int pixY;
  string trash;
  trash = path + find.cFileName;
  do{
    queue<double> time;
    queue<int> count;
    vector<int> events;
    vector<double> timeFromFirst;
    trash = path + find.cFileName;
    file.open(trash);
    //reading in file
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> trash;
    file.get();
    file.get();
    file.get();
    getline(file, gas);
    file >> trash;
    file >> trash;
    file >> trash;
    file >> press;
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> voltage;
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> trash;
    file >> pixX;
    file.get();
    file >> pixY;
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    while (file >> tempd >> tempi){
      time.push(tempd);
      count.push(tempi);
    }
    if (!time.empty() && !count.empty()){
      count.pop();
      time.pop();
    }
    prevCount = 0;
    while (!time.empty() && !count.empty()){
      firstC = count.front();
      firstT = time.front();
      count.pop();
      time.pop();
      for (int i = 0; i <firstC - prevCount - 1; ++i){
        timeFromFirst.push_back(0);
      }
      tempi = firstC;
      while (!time.empty() && !count.empty() && time.front() - firstT < intervalSize){
        tempi = count.front();
        tempd = time.front() - firstT;
        for (int i = 0; i < tempi - firstC; ++i){
          timeFromFirst.push_back(tempd);
        }
        count.pop();
        time.pop();
        firstC = tempi;
      }
      events.push_back(tempi - prevCount);
      prevCount = tempi;
    }
    
    gErrorIgnoreLevel = kWarning;
    TCanvas *c1 = nullptr;
    TH1D *gr = nullptr;
    string name;
    string title;
    if (!events.empty()){
      title = "After-Pulse #distribution for pixel " + to_string(pixX) + "-" + to_string(pixY) + " using " + gas + " at " + to_string(press) + "torr at " + to_string(voltage) + " V";
      name = to_string(pixX) + "-" + to_string(pixY) + "_" + to_string(voltage) + "_count_" + "AP";
      c1 = new TCanvas(name.c_str(), name.c_str(), 200, 10, 700, 500);
      gr = new TH1D("gr", title.c_str(), (*max_element(events.begin(), events.end())) + 1, -.5, *max_element(events.begin(), events.end()) + .5);
      for (int i = 0, len = events.size(); i < len; ++i){
        gr->Fill(events[i]-1);
      }
      gr->GetXaxis()->SetTitle("# of After-Pulses");
      gr->GetYaxis()->SetTitle("Count");
      //gr->SetStats(0);
      gr->Draw();
      temp = "%s" + path.substr(1, path.length() - 1) + name + ".png";
      c1->Print(Form(temp.c_str(), nowdir.c_str()));
      delete c1;
      delete gr;
    }
    if (!timeFromFirst.empty()){
      title = "After-Pulse time distribution for pixel " + to_string(pixX) + "-" + to_string(pixY) + " using " + gas + " at " + to_string(press) + "torr at " + to_string(voltage) + " V";
      name = to_string(pixX) + "-" + to_string(pixY) + "_" + to_string(voltage) + "_time_" + "AP";
      c1 = new TCanvas(name.c_str(), name.c_str(), 200, 10, 700, 500);
      gr = new TH1D("gr", title.c_str(), intervalSize + 2, 0, intervalSize);
      for (int i = 0, len = timeFromFirst.size(); i < len; ++i){
        gr->Fill(timeFromFirst[i]);
      }
      gr->GetXaxis()->SetTitle("Time after 1st pulse (ms)");
      gr->GetYaxis()->SetTitle("Count");
      //gr->SetStats(0);
      gr->Draw();
      temp = "%s" + path.substr(1, path.length() - 1) + name + ".png";
      c1->Print(Form(temp.c_str(), nowdir.c_str()));
      delete c1;
      delete gr;
    }

    file.close();
  } while (FindNextFile(hand, &find)>0);
}

void makeApGraphs1Adapt(string path,double rate, double prop){
  makeApGraphs1(path, findInterval(prop, rate));
}

void makeApGraphsN(string path, int intervalSize){
  int num = 1;
  //path = '.' + path;
  ifstream file;
  string searchPat = "*AP.txt";
  string full = path + searchPat;
  WIN32_FIND_DATA find;
  HANDLE hand;
  hand = FindFirstFile(full.c_str(), &find);
  string nowdir = gSystem->WorkingDirectory();
  string temp;
  int prevCount;
  int firstC;
  double firstT;
  double tempd;
  int tempi;

  string gas;
  int press;
  int voltage;
  string trash;
  trash = path + find.cFileName;
  do{

    trash = path + find.cFileName;
    file.open(trash);
    //reading in file
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> trash;
    file >> ws;
    getline(file, gas);
    file >> trash;
    file >> trash;
    file >> trash;
    file >> press;
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> voltage;
    getline(file, trash);
    file >> trash >> trash >> trash;
    file >> num;
    getline(file, trash);
    file >> trash;
    file >> trash;
    vector<int> pixX(num);
    vector<int> pixY(num);
    vector<queue<double>> time(num);
    vector<queue<int>> count(num);
    vector<vector<int>> events(num);
    vector<vector<double>> timeFromFirst(num);
    for (int i = 0; i < num; ++i){
      file >> pixX[i];
      file.get();
      file >> pixY[i];
    }
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    while (file >> tempd){
      for (int i = 0; i < num; ++i){
        file >> tempi;
        if (count[i].empty() || tempi > count[i].back()){
          time[i].push(tempd);
          count[i].push(tempi);
        }
      }

    }
    for (int i = 0; i < num; ++i){
      if (!time[i].empty() && !count[i].empty()){
        count[i].pop();
        time[i].pop();
      }
      prevCount = 0;
      while (!time[i].empty() && !count[i].empty()){
        firstC = count[i].front();
        firstT = time[i].front();
        count[i].pop();
        time[i].pop();
        for (int k = 0; k < firstC - prevCount - 1; ++k){
          timeFromFirst[i].push_back(0);
        }
        tempi = firstC;
        while (!time[i].empty() && !count[i].empty() && time[i].front() - firstT < intervalSize){
          tempi = count[i].front();
          tempd = time[i].front() - firstT;
          for (int k = 0; k < tempi - firstC; ++k){
            timeFromFirst[i].push_back(tempd);
          }
          count[i].pop();
          time[i].pop();
          firstC = tempi;
        }
        //cout << "tempi: " << tempi << " prevCount: " << prevCount << " tot: " << tempi - prevCount << endl;
        events[i].push_back(tempi - prevCount);
        prevCount = tempi;
      }
    }
    gErrorIgnoreLevel = kWarning;
    TCanvas *c1;
    TH1D *gr;
    string title;
    string name;
    for (int i = 0; i < num; ++i){
      c1 = nullptr;
      gr = nullptr;

      if (!events[i].empty()){
        name = to_string(pixX[i]) + "-" + to_string(pixY[i]) + "_" + to_string(voltage) + "_count_" + to_string(num) + "AP";
        title = "After-Pulse #distribution for pixel " + to_string(pixX[i]) + "-" + to_string(pixY[i]) + " using " + gas + " at " + to_string(press) + "torr at " + to_string(voltage) + " V with " + to_string(num) + "other pix";
        c1 = new TCanvas(name.c_str(), name.c_str(), 200, 10, 700, 500);
        gr = new TH1D("gr", title.c_str(), (*max_element(events[i].begin(), events[i].end())) + 1, -.5, *max_element(events[i].begin(), events[i].end()) + .5);
        for (int k = 0, len = events[i].size(); k < len; ++k){
          gr->Fill(events[i][k]-1);
        }
        gr->GetXaxis()->SetTitle("# of After-Pulses");
        gr->GetYaxis()->SetTitle("Count");
        gr->Draw();
        temp = "%s" + path.substr(1, path.length() - 1) + name + ".png";
        c1->Print(Form(temp.c_str(), nowdir.c_str()));
        delete c1;
        delete gr;
      }
      if (!timeFromFirst[i].empty()){
        title = "After-Pulse time distribution for pixel " + to_string(pixX[i]) + "-" + to_string(pixY[i]) + " using " + gas + " at " + to_string(press) + "torr at " + to_string(voltage) + " V with " + to_string(num) + "other pix";
        name = to_string(pixX[i]) + "-" + to_string(pixY[i]) + "_" + to_string(voltage) + "_time_" + to_string(num) + "AP";
        c1 = new TCanvas(name.c_str(), name.c_str(), 200, 10, 700, 500);
        gr = new TH1D("gr", title.c_str(), intervalSize + 2, 0, intervalSize);
        for (int k = 0, len = timeFromFirst[i].size(); k < len; ++k){
          gr->Fill(timeFromFirst[i][k]);
        }
        gr->GetXaxis()->SetTitle("Time after 1st pulse (ms)");
        gr->GetYaxis()->SetTitle("Count");
        //gr->SetStats(0);
        gr->Draw();
        temp = "%s" + path.substr(1, path.length() - 1) + name + ".png";
        c1->Print(Form(temp.c_str(), nowdir.c_str()));
        delete c1;
        delete gr;
      }
    }
    file.close();
  } while (FindNextFile(hand, &find)>0);
}

void makeApGraphsNAdapt(string path, double rate, double prop){
  makeApGraphsN(path, findInterval(prop, rate));
}

int findInterval(double prop, double rate){
  double epsilon = .0001;
  double a = 0;
  double b = 10000;
  while (abs(prop - pois((b + a) / 2, rate)) > epsilon) {
    if (prop - pois( (b + a) / 2,rate) < 0) {
      b += a;
      b /= 2;
    }
    else {
      a += b;
      a /= 2;
    }
  }
  return (int)((a + b) / 2);
}

double pois(double rate, double inter){
  return 1 - exp(rate*inter / 1000)*(1 - rate*inter / 1000);
}



void makeApIntGraph1(string path, int intervalSize){
  //path = '.' + path;
  ifstream file;
  string searchPat = "*AP.txt";
  string full = path + searchPat;
  WIN32_FIND_DATA find;
  HANDLE hand;
  hand = FindFirstFile(full.c_str(), &find);
  string nowdir = gSystem->WorkingDirectory();
  string temp;
  double firstT;
  double tempd;
  int tempi;
  double prevTime;
  string gas;
  int press;
  int voltage;
  int pixX;
  int pixY;
  string trash;
  trash = path + find.cFileName;
  do{
    queue<double> time;
    queue<int> count;
    vector<double> timeBetween;
    trash = path + find.cFileName;
    file.open(trash);
    //reading in file
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> trash;
    file.get();
    file.get();
    file.get();
    getline(file, gas);
    file >> trash;
    file >> trash;
    file >> trash;
    file >> press;
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> voltage;
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> trash;
    file >> pixX;
    file.get();
    file >> pixY;
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    while (file >> tempd >> tempi){
      time.push(tempd);
      count.push(tempi);
    }
    if (!time.empty() && !count.empty()){
      prevTime = time.front();
      firstT = time.front();
      count.pop();
      time.pop();
    }

    while (!time.empty() && !count.empty() && time.front() - firstT < intervalSize){
      count.pop();
      time.pop();
    }

    while (!time.empty() && !count.empty()){
      timeBetween.push_back(prevTime-time.front());
      firstT = time.front();
      count.pop();
      time.pop();
      while (!time.empty() && !count.empty() && time.front() - firstT < intervalSize){
        count.pop();
        time.pop();
      }
    }

    gErrorIgnoreLevel = kWarning;
    TCanvas *c1 = nullptr;
    TH1D *gr = nullptr;
    TLine *li = nullptr;
    string name;
    string title;
    if (!timeBetween.empty()){
      title = "Time Between triggers for pixel " + to_string(pixX) + "-" + to_string(pixY) + " using " + gas + " at " + to_string(press) + "torr at " + to_string(voltage) + " V";
      name = to_string(pixX) + "-" + to_string(pixY) + "_" + to_string(voltage) + "_trig_" + "AP";
      c1 = new TCanvas(name.c_str(), name.c_str(), 200, 10, 700, 500);
      gr = new TH1D("gr", title.c_str(), ((int)(*max_element(timeBetween.begin(), timeBetween.end())) + 1 - intervalSize + 1)/10,
                    intervalSize - 1, (int)(*max_element(timeBetween.begin(), timeBetween.end())) + 1);
      
      for (int i = 0, len = timeBetween.size(); i < len; ++i){
        gr->Fill(timeBetween[i]);
      }
      c1->SetLogx();
      gr->GetXaxis()->SetTitle("Time between trigger pulses (ms)");
      gr->GetYaxis()->SetTitle("Count");
      //gr->SetStats(0);
      gr->Draw();
      li = new TLine(intervalSize, 0, intervalSize, gr->GetMaximum()*1.05);
      li->SetLineColor(6);
      li->Draw();
      temp = "%s" + path.substr(1, path.length() - 1) + name + ".png";
      c1->Print(Form(temp.c_str(), nowdir.c_str()));
      delete c1;
      delete gr;
      delete li;
    }
    file.close();
  } while (FindNextFile(hand, &find)>0);
}
void makeApIntGraphN(string path, int intervalSize){
  int num = 1;
  //path = '.' + path;
  ifstream file;
  string searchPat = "*AP.txt";
  string full = path + searchPat;
  WIN32_FIND_DATA find;
  HANDLE hand;
  hand = FindFirstFile(full.c_str(), &find);
  string nowdir = gSystem->WorkingDirectory();
  string temp;
  double firstT;
  double tempd;
  int tempi;

  string gas;
  int press;
  int voltage;
  string trash;
  trash = path + find.cFileName;
  do{
    trash = path + find.cFileName;
    file.open(trash);
    //reading in file
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> trash;
    file >> ws;
    getline(file, gas);
    file >> trash;
    file >> trash;
    file >> trash;
    file >> press;
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> voltage;
    getline(file, trash);
    file >> trash >> trash >> trash;
    file >> num;
    getline(file, trash);
    file >> trash;
    file >> trash;
    vector<int> pixX(num);
    vector<int> pixY(num);
    vector<queue<double>> time(num);
    vector<queue<int>> count(num);
    vector<vector<double>> timeBetween(num);
    double prevTime = 0;
    for (int i = 0; i < num; ++i){
      file >> pixX[i];
      file.get();
      file >> pixY[i];
    }
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    while (file >> tempd){
      for (int i = 0; i < num; ++i){
        file >> tempi;
        if (count[i].empty() || tempi > count[i].back()){
          time[i].push(tempd);
          count[i].push(tempi);
        }
      }

    }
    for (int i = 0; i < num; ++i){
      if (!time[i].empty() && !count[i].empty()){
        count[i].pop();
        time[i].pop();
      }
      if (!time[i].empty() && !count[i].empty()){
        prevTime = time[i].front();
        firstT = time[i].front();
        count[i].pop();
        time[i].pop();
      }
      while (!time[i].empty() && !count[i].empty() && time[i].front() - firstT < intervalSize){
        count[i].pop();
        time[i].pop();
      }

      while (!time[i].empty() && !count[i].empty()){
        timeBetween[i].push_back(time[i].front() - prevTime);
        prevTime = time[i].front();
        firstT = time[i].front();
        while (!time[i].empty() && !count[i].empty() && time[i].front() - firstT < intervalSize){
          count[i].pop();
          time[i].pop();
        }
      } 
    }
    for (int i = 0; i < num; ++i){
      gErrorIgnoreLevel = kWarning;
      TCanvas *c1 = nullptr;
      TH1D *gr = nullptr;
      TLine *li = nullptr;
      string name;
      string title;
      if (!timeBetween[i].empty()){
        title = "Time Between triggers for pixel " + to_string(pixX[i]) + "-" + to_string(pixY[i]) + " using " + gas + " at " + to_string(press) + "torr at " + to_string(voltage) + " V";
        name = to_string(pixX[i]) + "-" + to_string(pixY[i]) + "_" + to_string(voltage) + "_trig_" + "AP";
        c1 = new TCanvas(name.c_str(), name.c_str(), 200, 10, 700, 500);
        gr = new TH1D("gr", title.c_str(), ((int)(*max_element(timeBetween[i].begin(), timeBetween[i].end())) + 1 - intervalSize + 1)/10,
                      intervalSize - 1, (int)(*max_element(timeBetween[i].begin(), timeBetween[i].end())) + 1);
        for (int j = 0, len = timeBetween[i].size(); j < len; ++j){
          gr->Fill(timeBetween[i][j]);
        }
        gr->GetXaxis()->SetTitle("Time between trigger pulses (ms)");
        gr->GetYaxis()->SetTitle("Count");
        c1->SetLogx();
        //gr->SetStats(0);
        gr->Draw();
        li = new TLine(intervalSize, 0, intervalSize, gr->GetMaximum()*1.05);
        li->SetLineColor(2);
        li->SetLineWidth(2);
        li->Draw();
        temp = "%s" + path.substr(1, path.length() - 1) + name + ".png";
        c1->Print(Form(temp.c_str(), nowdir.c_str()));
        delete c1;
        delete li;
        delete gr;
      }
    }
    file.close();
  } while (FindNextFile(hand, &find)>0);
}

void makeApDiffGraph1(string path){
  //path = '.' + path;
  ifstream file;
  string searchPat = "*AP.txt";
  string full = path + searchPat;
  WIN32_FIND_DATA find;
  HANDLE hand;
  hand = FindFirstFile(full.c_str(), &find);
  string nowdir = gSystem->WorkingDirectory();
  string temp;
  double tempd;
  int tempi;
  string gas;
  int press;
  int voltage;
  int pixX;
  int pixY;
  string trash;
  trash = path + find.cFileName;
  do {
    vector<double> time;
    vector<int> count;
    vector<double> timeBetween;
    trash = path + find.cFileName;
    file.open(trash);
    //reading in file
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> trash;
    file.get();
    file.get();
    file.get();
    getline(file, gas);
    file >> trash;
    file >> trash;
    file >> trash;
    file >> press;
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> voltage;
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> trash;
    file >> pixX;
    file.get();
    file >> pixY;
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    while (file >> tempd >> tempi) {
      time.push_back(tempd);
      count.push_back(tempi);
    }
    
    for (int i = 1, len = time.size(); i < len; ++i){
      if (count[i] - count[i - 1] > 1){
        for (int j = 0; j < count[i] - count[i - 1] - 1; ++j) {
        }
        timeBetween.push_back(0);
      }
      timeBetween.push_back(time[i] - time[i - 1]);
    }

    gErrorIgnoreLevel = kWarning;
    TCanvas *c1 = nullptr;
    TH1D *gr = nullptr;
    string name;
    string title;
    if (!timeBetween.empty()) {
      title = "Time between pulses for pixel " + to_string(pixX) + "-" + to_string(pixY) + " using " + gas + " at " + to_string(press) + "torr at " + to_string(voltage) + " V";
      name = to_string(pixX) + "-" + to_string(pixY) + "_" + to_string(voltage) + "_diff_" + "AP";
      c1 = new TCanvas(name.c_str(), name.c_str(), 200, 10, 700, 500);
      gr = new TH1D("gr", title.c_str(), ((int)(*max_element(timeBetween.begin(), timeBetween.end())) + 1)/10,
        0, (int)(*max_element(timeBetween.begin(), timeBetween.end())) + 1);

      for (int i = 0, len = timeBetween.size(); i < len; ++i) {
        gr->Fill(timeBetween[i]);
      }
      c1->SetLogx();
      gr->GetXaxis()->SetTitle("Time between pulses (ms)");
      gr->GetYaxis()->SetTitle("Count");
      //gr->SetStats(0);
      gr->Draw();
      temp = "%s" + path.substr(1, path.length() - 1) + name + ".png";
      c1->Print(Form(temp.c_str(), nowdir.c_str()));
      delete c1;
      delete gr;
    }
    file.close();
  } while (FindNextFile(hand, &find)>0);
}





void makeApDiffGraphN(string path){
  int num = 1;
  //path = '.' + path;
  ifstream file;
  string searchPat = "*AP.txt";
  string full = path + searchPat;
  WIN32_FIND_DATA find;
  HANDLE hand;
  hand = FindFirstFile(full.c_str(), &find);
  string nowdir = gSystem->WorkingDirectory();
  string temp;
  double tempd;
  int tempi;

  string gas;
  int press;
  int voltage;
  string trash;
  trash = path + find.cFileName;
  do {
    trash = path + find.cFileName;
    file.open(trash);
    //reading in file
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> trash;
    file >> ws;
    getline(file, gas);
    file >> trash;
    file >> trash;
    file >> trash;
    file >> press;
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    file >> trash;
    file >> voltage;
    getline(file, trash);
    file >> trash >> trash >> trash;
    file >> num;
    getline(file, trash);
    file >> trash;
    file >> trash;
    vector<int> pixX(num);
    vector<int> pixY(num);
    vector<vector<double>> time(num);
    vector<vector<int>> count(num);
    vector<vector<double>> timeBetween(num);
    double prevTime = 0;
    for (int i = 0; i < num; ++i) {
      file >> pixX[i];
      file.get();
      file >> pixY[i];
    }
    getline(file, trash);
    getline(file, trash);
    getline(file, trash);
    while (file >> tempd) {
      for (int i = 0; i < num; ++i) {
        file >> tempi;
        if (count[i].empty() || tempi > count[i].back()) {
          time[i].push_back(tempd);
          count[i].push_back(tempi);
        }
      }

    }
    for (int i = 0; i < num; ++i) {
      for (int j = 1, len = time[i].size(); j < len; ++j) {
        if (count[i][j] - count[i][j - 1] > 1) {
          for (int k = 0; k < count[i][j] - count[i][j - 1] - 1; ++k) {
            timeBetween[i].push_back(0);
          }
        }
        timeBetween[i].push_back(time[i][j] - time[i][j - 1]);
      }
    }
    for (int i = 0; i < num; ++i) {
      gErrorIgnoreLevel = kWarning;
      TCanvas *c1 = nullptr;
      TH1D *gr = nullptr;
      string name;
      string title;
      if (!timeBetween[i].empty()) {
        title = "Time between pulses for pixel " + to_string(pixX[i]) + "-" + to_string(pixY[i]) + " using " + gas + " at " + to_string(press) + "torr at " + to_string(voltage) + " V";
        name = to_string(pixX[i]) + "-" + to_string(pixY[i]) + "_" + to_string(voltage) + "_diff_" + "AP";
        c1 = new TCanvas(name.c_str(), name.c_str(), 200, 10, 700, 500);
        c1->SetLogx();
        gr = new TH1D("gr", title.c_str(), ((int)(*max_element(timeBetween[i].begin(), timeBetween[i].end())) + 1)/10,
          0, (int)(*max_element(timeBetween[i].begin(), timeBetween[i].end())) + 1);
        for (int j = 0, len = timeBetween[i].size(); j < len; ++j) {
          gr->Fill(timeBetween[i][j]);
        }
        gr->GetXaxis()->SetTitle("Time between pulses (ms)");
        gr->GetYaxis()->SetTitle("Count");
        //gr->SetStats(0);
        gr->Draw();
        temp = "%s" + path.substr(1, path.length() - 1) + name + ".png";
        c1->Print(Form(temp.c_str(), nowdir.c_str()));
        delete c1;
        delete gr;
      }
    }
    file.close();
  } while (FindNextFile(hand, &find)>0);
}


void makeTChain(string path){
}