#ifndef Histo_h
#define Histo_h

#include "THStack.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH1F.h"
#include <vector>
#include <iostream>
#include "TCanvas.h"
#include "TLegend.h"
#include <sstream>
#include "plotterclass.h"
#include "HHStyle.h"
#include "basicFunctions.h"

class Histo {

 public:
  Histo();
  ~Histo();
  void MakePlots();

 private:

  //  Plotter h_generalPlot;
};

#endif
    
