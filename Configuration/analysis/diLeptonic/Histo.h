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

  Plotter AllDIM, InDIM, OutDIM, GenDIM;  

  Plotter h_HypTTbarMass;

  Plotter h_Met, h_jetMulti;

  Plotter h_Lep1pT, h_Lep2pT, h_Lep1Eta, h_Lep2Eta, h_Lep1E, h_Lep2E;

  Plotter h_HypToppT, h_HypAntiToppT, h_HypTopEta, h_HypAntiTopEta, h_HypTopE, h_HypAntiTopE, h_HypTopMass, h_HypAntiTopMass;
  Plotter h_HypLeptonpT, h_HypAntiLeptonpT, h_HypLeptonEta, h_HypAntiLeptonEta, h_HypLeptonE, h_HypAntiLeptonE;
  Plotter h_HypBpT, h_HypAntiBpT, h_HypBEta, h_HypAntiBEta, h_HypBE, h_HypAntiBE;
  Plotter h_HypNeutrinopT, h_HypAntiNeutrinopT, h_HypNeutrinoEta, h_HypAntiNeutrinoEta, h_HypNeutrinoE, h_HypAntiNeutrinoE;
  Plotter h_HypWMinuspT, h_HypWPluspT, h_HypWMinusEta, h_HypWPlusEta, h_HypWMinusE, h_HypWPlusE;

};

#endif
    
