#ifndef TtDiMuonKinSolAna_h
#define TtDiMuonKinSolAna_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class TH1F;
class TtDilepEvtSolution;
class edm::Event;

class TtDiMuonKinSolAna{

 public:

  explicit TtDiMuonKinSolAna(const edm::ParameterSet& cfg);
  ~TtDiMuonKinSolAna();

  void book(ofstream& file);
  void fill(const  edm::Event& evt, 
	    double weight=1.);	     
  void fithists();
    
 private:
 
  typedef std::vector<TtDilepEvtSolution> TtDilepEvtSolCollection;

  edm::InputTag solutions_;
  edm::InputTag muons_; 
  double leptonPtCut_;
  double jetPtCut_;
  double metCut_; 
  double DiMuonMassLowZCut_;
  double DiMuonMassHighZCut_;
  double DiMuonMassQCDCut_;  
      
  TH1F * mass_;
  TH1F * DiMuonmass_;
  TH1F * weightmax_;
  TH1F * maxweightmax_;
  TH1F * massBbW_;
  TH1F * massBbM_;
  
  TH1F * muPt_;
  TH1F * jetPt_;  
  TH1F * met_;    
  
  void fit(TH1F * hist);
};

#endif
