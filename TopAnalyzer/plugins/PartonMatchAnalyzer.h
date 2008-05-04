#ifndef PartonMatchAnalyzer_h
#define PartonMatchAnalyzer_h

#include <memory>
#include <string>
#include <vector>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"

#include "TopAnalysis/TopUtils/interface/CutMonitor.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"

class PartonMatchAnalyzer : public edm::EDAnalyzer {

 public:

  explicit PartonMatchAnalyzer(const edm::ParameterSet&);
  ~PartonMatchAnalyzer(){};
  
 private:

  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  edm::InputTag jets_;
  std::string hist_;
  unsigned int nJets_;

  bool useDeltaR_;
  bool useMaxDist_;
  double maxDist_;

  CutMonitor cutmon;
};

#endif
