#ifndef EventShapeFilter_h
#define EventShapeFilter_h

#include <TString.h>

#include "FWCore/Framework/interface/EDFilter.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "PhysicsTools/CandUtils/interface/EventShapeVariables.h"

class EventShapeFilter : public edm::EDFilter {

 public:

  explicit EventShapeFilter(const edm::ParameterSet&);
  ~EventShapeFilter(){};
  
 private:

  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

 private:
  
  edm::InputTag src_;
  double maxIsotropy_;
  double minIsotropy_;
  double maxCircularity_;
  double minCircularity_;
  double maxSphericity_;
  double minSphericity_;
  double maxAplanarity_;
  double minAplanarity_;
  double maxC_;
  double minC_;
  double maxD_;
  double minD_;
  bool useEventWeight_;
  edm::InputTag weight_;

  unsigned int beforeCut_;
  unsigned int afterCut_;
  double beforeCutWeighted_;
  double afterCutWeighted_;
};

#endif
