#ifndef SemiLeptonicGenPhaseSpaceFilter_h
#define SemiLeptonicGenPhaseSpaceFilter_h

#include <TString.h>
#include <TH1.h>

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "DataFormats/Candidate/interface/Candidate.h"

/// This filter cuts on the kinematics of the ttbar event on gen level using the TtGenEvent:
/// 1) pt and eta of the ttbar decay products
/// 2) pt and Y of the tops
/// 3) pt and Y of the ttbar system


class SemiLeptonicGenPhaseSpaceFilter : public edm::EDFilter {

 public:

  explicit SemiLeptonicGenPhaseSpaceFilter(const edm::ParameterSet&);
  ~SemiLeptonicGenPhaseSpaceFilter(){};
  
 private:

  virtual void beginJob();
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  reco::GenParticle* getFinalStateLepton(const reco::GenParticle& particle);

 private:
  
  edm::InputTag src_;
  /// cut values
  double leptonMinPt_;
  double leptonMaxEta_; 
  double partonMinPt_;
  double partonMaxEta_;
  double topMinPt_;
  double topMaxPt_;      
  double topMaxY_;       
  double ttbarMinPt_;    
  double ttbarMaxPt_;    
  double ttbarMaxY_;     
  /// decision on which level cuts are made
  bool decayLevelCuts_;
  bool topLevelCuts_;  
  bool ttbarLevelCuts_;

};

#endif
