#include "TCanvas.h"
#include "TH1.h"
#include "TError.h"
#include "stdafx.h"
#include "TSystem.h"
#include "TLine.h"
#include "headers.h"
#include <queue>
#include <vector>
#include "TTree.h"
#include "TFile.h"
using namespace std;
#ifndef HIST_GRA
#define HIST_GRA
class HGraph{
public:
  HGraph();
  void makeGraphBmp(int arr[20]);
  ~HGraph();
private:
  TCanvas *c1;
  TH1I *gr;
};
void makeApGraphs1(string path, int intervalSize = 30);
void makeApGraphs1Adapt(string path, double rate, double prop = .01);
void makeApGraphsN(string path, int intervalSize = 30);
void makeApGraphsNAdapt(string path, double rate, double prop = .01);

void makeApIntGraph1(string path, int intervalSize = 30);
void makeApIntGraphN(string path, int intervalSize = 30);

void makeApDiffGraph1(string path);
void makeApDiffGraphN(string path);

int findInterval(double prop, double rate);


inline double pois(double rate, double inter);
const int MIN_INT_SIZE = 20;
const int NUM_PIX = 20;

void makeTChain(string path);
#endif