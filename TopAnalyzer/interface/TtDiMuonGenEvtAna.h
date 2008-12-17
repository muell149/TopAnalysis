#ifndef TtDiMuonGenEvtAna_h
#define TtDiMuonGenEvtAna_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class TH1F;
class TH2F;
class TtGenEvent;
class edm::Event;

class TtDiMuonGenEvtAna{

 public:

  explicit TtDiMuonGenEvtAna(const edm::ParameterSet& cfg);
  ~TtDiMuonGenEvtAna();

  void book(ofstream& file);
  void fill(const  edm::Event& evt, 
	    double weight=1.);
  void normSpectrum();
      
 private:
  edm::InputTag genEvt_;
   
  TH1F * genMass_;
  TH2F * genNuSpectrum_;
};



#endif
