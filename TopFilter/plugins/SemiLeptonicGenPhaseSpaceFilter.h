#ifndef SemiLeptonicGenPhaseSpaceFilter_h
#define SemiLeptonicGenPhaseSpaceFilter_h

#include <TString.h>
#include <TH1.h>

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "DataFormats/Candidate/interface/Candidate.h"

/// This filter cuts on the pt and eta of the ttbar decay products using the TtGenEvent.


class SemiLeptonicGenPhaseSpaceFilter : public edm::EDFilter {

 public:

  explicit SemiLeptonicGenPhaseSpaceFilter(const edm::ParameterSet&);
  ~SemiLeptonicGenPhaseSpaceFilter(){};
  
 private:

  virtual void beginJob();
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

 private:
  
  edm::InputTag src_;
  double leptonMinPt_;
  double leptonMaxEta_; 
  double partonMinPt_;
  double partonMaxEta_; 
  bool   addHistos_;
  /// histogram container for histos
  std::map<std::string, TH1F*> hists_;

};

#endif
