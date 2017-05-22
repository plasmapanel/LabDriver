/*
This file contains the details for the various headers used in our lab files
and some of the methods that are used with these
created by: Michael Ausilio mausilio@umich.edu
*/

using namespace std;
#ifndef LAB_HEAD
#define LAB_HEAD
#include "stdafx.h"
//The general header that details the setup for all runs
struct HeaderInfoGen{
  string panelName = "MC";
  string sourceName = "RU";
  string sourceConfig = "Dynamic";
  string triggerSetup = "0"; //remove
  string gas = "TEST";
  double pressure = 740.0;
  double discThresh = 90;
  double quench = 1000;
  int numRO = 20;
  string roLines = "1-20";
  string triggerRO = "0";
  double attenRO = 20;
  int numHV = 20;
  string linesHV = "1-20";
  string triggerHV = "0"; //remove
  double attenHV = 0; //remove
  int motorstepx = 400;
  int motorstepy = 400;
  long int runNumber = 0;
};

//the header for after-pulse tests
struct HeaderInfoAfter{
  double voltage;
  int numPixels;
  vector<int> readoutLines;
  int numReadings;
};
struct HeaderInfoCounter{
  double voltage;
  vector<string> pixels;
  double timeLength;
  double samplingLength;
};
//These functions allow for the easy outputing of headers
ostream& operator<<(ostream& os, const HeaderInfoGen &h);
ostream& operator<<(ostream& os, const HeaderInfoAfter& h);
ostream& operator<<(ostream& os, const HeaderInfoCounter& h);
//this functions creates a command line prompt that will fill out the header
void makeGenHead(HeaderInfoGen &hg);
//this functions reads the header in from a template file
void makeGenHeadFile(HeaderInfoGen &hg, string file);
bool isHeaderValid(string filename);
//sets up the run parameters for a voltage scan from a file. Returns true if it is successful and false otherwise
bool makeVSRun(string file, int &start, int &stop, int &step, int &interval, double &freq, int &numPix, vector<int> &pixX, vector<int> &pixY);
#endif
