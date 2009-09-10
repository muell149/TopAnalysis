#ifndef JetOverlapEventFilter_h
#define JetOverlapEventFilter_h

#include "FWCore/Framework/interface/EDFilter.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

class JetOverlapEventFilter : public edm::EDFilter {

 public:

  explicit JetOverlapEventFilter(const edm::ParameterSet&);
  ~JetOverlapEventFilter(){};
  
 private:

  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

 private:
  
  edm::InputTag src_;
  double deltaR_;
  bool useEventWeight_;
  edm::InputTag weight_;

  unsigned int beforeCut_;
  unsigned int afterCut_;
  double beforeCutWeighted_;
  double afterCutWeighted_;
};

#endif
