#ifndef NewTriggerTestFilter_h
#define NewTriggerTestFilter_h

#include <TString.h>
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class NewTriggerTestFilter : public edm::EDFilter {

 public:

  explicit NewTriggerTestFilter(const edm::ParameterSet&);
  ~NewTriggerTestFilter(){};
  
 private:

  virtual void beginJob();
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

 private:
  
  std::string whichTrigger_;
  bool useEventWeight_;
  edm::InputTag weight_;
  edm::InputTag patTriggerEvent_;

  unsigned int beforeCut_;
  unsigned int afterCut_;
  double beforeCutWeighted_;
  double afterCutWeighted_;
};

#endif
