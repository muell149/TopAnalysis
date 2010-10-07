#ifndef styleHelper_h
#define styleHelper_h

#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <iomanip>
#include <cmath>

#include <TH1F.h>
#include <TH2F.h>
#include <THStack.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TPaveLabel.h>
#include <TStyle.h>
#include <typeinfo>
#include <TF1.h>
#include <TBox.h>

enum styles {kSig, kBkg, kZjets, kWjets, kQCD, kData, kLepJets, kAllMC, kABCD, kGenSig, kGenBkg, kGenW};

// set values:           ( kSig,   kBkg,   kZjets,   kWjets,   kQCD,    kData,  kLepJets, 7,      8,     9,       10)
int color_      [ 11 ] = { kRed+1, kRed-7, kAzure-2, kGreen-3, kYellow, kBlack, kRed,     kRed,   kBlue, kBlack,  kRed};
int markerStyle_[ 11 ] = { 20,     22,     29,       23,       21,      20,     23,       21,     20,    23,      22};

void histogramStyle(TH1& hist, int sampleTyp, bool filled=true) 
{
  hist.SetStats(kFALSE);
  hist.SetLineWidth(1);
  hist.SetLineStyle(1);
  if(sampleTyp==kData || !filled){
    if(!filled)hist.SetLineWidth(3);
    hist.SetLineColor(color_[sampleTyp]);
    hist.SetMarkerColor(color_[sampleTyp]);  
    hist.SetMarkerStyle(markerStyle_[sampleTyp]);
    hist.SetMarkerSize(1.8);
    hist.SetFillStyle(0);
  }
  else{
    hist.SetLineColor(kBlack);
    hist.SetFillColor(color_[sampleTyp]);
    hist.SetFillStyle(1001);
  }
}

#endif
