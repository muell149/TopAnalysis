#ifndef PtHatFilter_h
#define PtHatFilter_h

#include <TString.h>

#include "FWCore/Framework/interface/EDFilter.h"

class PtHatFilter : public edm::EDFilter {

 public:

  explicit PtHatFilter(const edm::ParameterSet&);
  ~PtHatFilter(){};
  
 private:

  virtual void beginJob();
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

 private:
  
  double minPtHat_;
  double maxPtHat_;
  bool useEventWeight_;
  edm::InputTag weight_;

  unsigned int beforeCut_;
  unsigned int afterCut_;
  double beforeCutWeighted_;
  double afterCutWeighted_;
};

#endif
