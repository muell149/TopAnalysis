#ifndef MetAnalyzer_h
#define MetAnalyzer_h

#include "TH1D.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class MetAnalyzer : public edm::EDAnalyzer {

 public:

  explicit MetAnalyzer(const edm::ParameterSet&);
  ~MetAnalyzer();
  
 private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  edm::InputTag METs_;
  
  typedef std::vector<pat::MET> PatMETCollection; 

  TH1D* et_;
  TH1D* phi_;  
};

#endif
