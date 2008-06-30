#ifndef SemiLepHypothesesAnalyzer_h
#define SemiLepHypothesesAnalyzer_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class SemiLepHypothesesAnalyzer : public edm::EDAnalyzer {

 public:

  explicit SemiLepHypothesesAnalyzer(const edm::ParameterSet&);
  ~SemiLepHypothesesAnalyzer(){};
  
 private:

  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  edm::InputTag semiEvt_;

};

#endif
