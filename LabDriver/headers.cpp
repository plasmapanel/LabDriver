#include "headers.h"
using namespace std;
ostream& operator<<(ostream& os, const HeaderInfoGen &h){
  os << h.version << endl;
  os << "Panel Name   " << h.panelName << endl;
  os << "Run Number  " << h.runNumber << endl;
  os << "Source   " << h.sourceName << endl;
  os << "Source Config  " << h.sourceConfig << endl;
  os << "Source Height  (mm)  " << h.sourceHeight << endl;
  os << "Collimator Size  (mm)  " << h.collimatorSize << endl;
  os << "Gas Mixture   " << h.gas << endl;
  os << "Gas Pressure (Torr)   " << h.pressure << endl;
  os << "R-quench (MOhm)   " << h.quench << endl;
  //os << "Trigger Setup   " << h.triggerSetup << endl;
  os << "Discriminator Thr (mV)   " << h.discThresh << endl;
  os << "Number RO lines   " << h.numRO << endl;
  os << "RO lines   " << h.roLines << endl;
  os << "Trigger RO   " << h.triggerRO << endl;
  os << "Attenuation RO (db)  " << h.attenRO << endl;
  os << "Number HV lines " << h.numHV << endl;
  os << "HV lines  " << h.linesHV << endl;
  os << "Trigger HV	 " << h.triggerHV << endl;
  os << "Discriminator Thr HV (mV)   " << h.discHV << endl;
  os << "Attenuation HV (db)   " << h.attenHV << endl;
  //os << "X Drive step/mm   " << h.motorstepx << endl;
 // os << "Y Drive step/mm   " << h.motorstepy << endl;
  os << "Run Start Time   " << h.runStartTime << endl;
  
  return os;
}
ostream& operator<<(ostream& os, const HeaderInfoAfter& h){
   os << "Voltage   " << h.voltage << endl;
 // os << "# Readout Lines Tested   " << h.numPixels << endl;
 // os << "Readout Lines Tested   ";
 // for (int i = 0, len = h.readoutLines.size(); i < len; ++i){
 //   os << h.readoutLines[i] << " ";
 // }
 // os << endl;
  os << "# Readings Taken " << h.numReadings << endl;
  return os;
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
  in >> ws >> hg.panelName;
  //getline(in, hg.panelName);
  in >> trash >> trash >> trash;
  in >> trash >> ws >> hg.sourceName;
  //getline(in, hg.sourceName);
  in >> trash >> trash >> trash;
  in >> trash >> trash >> trash;
  in >> ws >> hg.sourceHeight;
  in >> trash >> trash >> trash;
  in >> ws >> hg.collimatorSize;
   //getline(in, hg.sourceConfig);
  //if (!(hg.sourceConfig == "Static" || hg.sourceConfig == "Dynamic" || hg.sourceConfig == "User")){
  //  cerr << "Invalid Source Configuation option give." << endl;
  //  throw;
  //}
  in >> trash >> trash;
  in >> ws >> hg.gas;
  //getline(in, hg.gas);
  in >> trash >> trash >> trash;
  in >> ws >> hg.pressure;
  //in >> hg.pressure;
  in >> trash >> trash;
  in >> ws >> hg.quench;
  //in >> hg.quench;
   //getline(in, hg.triggerSetup);
  //in >> trash >> trash >> hg.triggerSetup;
  in >> trash >> trash >> trash>> ws >> hg.discThresh;
  //in >> hg.discThresh;
  in >> trash >> trash >> trash;
  in >> hg.numRO;
  in >> trash >> trash >> ws >> hg.roLines;
  //getline(in, hg.roLines);
  in >> trash >> trash >> ws >> hg.triggerRO;
    //getline(in, hg.triggerRO);
  in >> trash >> trash >> trash >> ws >> hg.attenRO;
  //in >> hg.attenRO;
  in >> trash >> trash >> trash >> ws >> hg.numHV;
  //in >> hg.numHV;
  in >> trash >> trash >> ws >> hg.linesHV;

  in >> trash >> trash >> ws >> hg.triggerHV;
  //getline(in, hg.linesHV);
  in >> trash >> trash >> trash >> trash >> ws >> hg.discHV;
  in >> trash >> trash >> trash >> ws;
  in >> hg.attenHV;
  in >> trash >> trash >> trash >> hg.runStartTime;
  in.close();

}
