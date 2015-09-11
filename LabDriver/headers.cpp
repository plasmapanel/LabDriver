#include "headers.h"
using namespace std;
ostream& operator<<(ostream& os, const HeaderInfoGen &h){

  os << "Panel Name   " << h.panelName << endl;
  os << "Source   " << h.sourceName << endl;
  os << "Source Config  " << h.sourceConfig << endl;
  os << "Gas Mixture   " << h.gas << endl;
  os << "Gas Pressure (Torr)   " << h.pressure << endl;
  os << "R-quench (MOhm)   " << h.quench << endl;
  os << "Trigger Setup   " << h.triggerSetup << endl;
  os << "Discriminator Thr (mV)   " << h.discThresh << endl;
  os << "Number RO lines   " << h.numRO << endl;
  os << "RO lines   " << h.roLines << endl;
  os << "Trigger RO   " << h.triggerRO << endl;
  os << "Attenuation RO (db)  " << h.attenRO << endl;
  os << "Number HV lines " << h.numHV << endl;
  os << "HV lines  " << h.linesHV << endl;
  os << "Trigger HV	 " << h.triggerHV << endl;
  os << "Attenuation HV (db)   " << h.attenHV << endl;
  return os;
}
ostream& operator<<(ostream& os, const HeaderInfoAfter& h){
  os << "After-Pulse Test" << endl;
  os << "Voltage   " << h.voltage << endl;
  os << "# Pixels Tested   " << h.numPixels << endl;
  os << "Pixels Tested   ";
  for (int i = 0, len = h.pixels.size(); i < len; ++i){
    os << h.pixels[i] << " ";
  }
  os << endl;
  os << "# Readings Taken " << h.numReadings << endl;
  return os;
}
ostream& operator<<(ostream& os, const HeaderInfoCounter& h){
  os << "Counter Test" << endl;
  os << "Voltage   " << h.voltage << endl;
  os << "Pixels Active   ";
  for (int i = 0, len = h.pixels.size(); i < len; ++i){
    os << h.pixels[i] << " ";
  }
  os << endl;
  os << "Sampling Period Size (s)   " << h.samplingLength << endl;
  return os;
}
void makeGenHead(HeaderInfoGen &hg){
  bool done = false;
  char temp;
  do{
    cout << "Please enter run information" << endl;
    cout << "Panel Name: ";
    getline(cin, hg.panelName);
    cout << "Source Name: ";
    getline(cin, hg.sourceName);
    while (1){
      cout << "Source Setup (Static/Dynamic/User): ";
      getline(cin, hg.sourceConfig);
      if (hg.sourceConfig == "Static" || hg.sourceConfig == "Dynamic" || hg.sourceConfig == "User"){
        break;
      }
      else{
        cout << "Invalid option please try again." << endl;
      }
    }
    cout << "Trigger Setup: ";
    getline(cin, hg.triggerSetup);
    cout << "Gas: ";
    getline(cin, hg.gas);
    cout << "Pressure: ";
    cin >> hg.pressure;
    cout << "Discriminator Threshold: ";
    cin >> hg.discThresh;
    cout << "Quench Resistance (MOhm): ";
    cin >> hg.quench;
    cout << "Number of Readout Lines: ";
    cin >> hg.numRO;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Readout Lines: ";
    getline(cin, hg.roLines);
    cout << "Readout Trigger: ";
    getline(cin, hg.triggerRO);
    cout << "Readout attenuation (db): ";
    cin >> hg.attenRO;
    cout << "Number of HV lines: ";
    cin >> hg.numHV;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "HV lines: ";
    getline(cin, hg.linesHV);
    cout << "HV Trigger: ";
    getline(cin, hg.triggerHV);
    cout << "HV attenuation (db): ";
    cin >> hg.attenHV;
    cout << endl << "The current header is: " << endl;
    cout << hg << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    while (1){
      cout << "Does this look correct? (y/n) :";
      cin.get(temp);
      if (temp == 'y' || temp == 'n'){
        if (temp == 'y'){
          done = true;
        }
        break;
      }
      else{
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid option please try again." << endl;
      }
    }
    cin.clear();
    cin.ignore(10000, '\n');
  } while (!done);
}
void makeGenHeadFile(HeaderInfoGen &hg, string file){
  ifstream in;
  in.open(file);
  if (!in.is_open()){
    cerr << "invalid file name" << endl;
    throw;
  }
  string trash;
  in >> trash >> trash;
  in >> ws;
  getline(in, hg.panelName);
  in >> trash;
  in >> ws;
  getline(in, hg.sourceName);
  in >> trash >> trash;
  in >> ws;
  getline(in, hg.sourceConfig);
  if (!(hg.sourceConfig == "Static" || hg.sourceConfig == "Dynamic" || hg.sourceConfig == "User")){
    cerr << "Invalid Source Configuation option give." << endl;
    throw;
  }
  in >> trash >> trash;
  in >> ws;
  getline(in, hg.gas);
  in >> trash >> trash >> trash;
  in >> ws;
  in >> hg.pressure;
  in >> trash >> trash;
  in >> ws;
  in >> hg.quench;
  in >> trash >> trash;
  in >> ws;
  getline(in, hg.triggerSetup);
  in >> trash >> trash >> trash>>ws;
  in >> hg.discThresh;
  in >> trash >> trash >> trash >> ws;
  in >> hg.numRO;
  in >> trash >> trash >> ws;
  getline(in, hg.roLines);
  in >> trash >> trash >> ws;
  getline(in, hg.triggerRO);
  in >> trash >> trash >> trash >> ws;
  in >> hg.attenRO;
  in >> trash >> trash >> trash >> ws;
  in >> hg.numHV;
  in >> trash >> trash >> ws;
  getline(in, hg.linesHV);
  in >> trash >> trash >> ws;
  in >> hg.triggerHV;
  in >> trash >> trash >> trash >> ws;
  in >> hg.attenHV;

}