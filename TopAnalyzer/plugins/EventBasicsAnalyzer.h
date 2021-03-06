#ifndef EventBasicsAnalyzer_h
#define EventBasicsAnalyzer_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

/**
   \class   EventBasicsAnalyzer EventBasicsAnalyzer.h "TopAnalysis/TopAnalyzer/interface/EventBasicsAnalyzer.h"
*/

class TH1;
class TH3;

class EventBasicsAnalyzer : public edm::EDAnalyzer {

public:
  /// default constructor
  explicit EventBasicsAnalyzer(const edm::ParameterSet&);
  /// default destructor
  ~EventBasicsAnalyzer(){};

  virtual void beginJob();
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  
protected:
  /// vertex
  edm::InputTag vertex_;
  /// tracks
  edm::InputTag tracks_;
  /// MET
  edm::InputTag met_;
  /// histogram container
  std::map<std::string, TH1*> hists_;
};

#endif
