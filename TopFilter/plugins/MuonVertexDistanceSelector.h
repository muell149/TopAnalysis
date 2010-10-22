#ifndef MuonVertexDistanceSelector_h
#define MuonVertexDistanceSelector_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


class MuonVertexDistanceSelector : public edm::EDProducer {

 public:
  explicit MuonVertexDistanceSelector(const edm::ParameterSet&);
  ~MuonVertexDistanceSelector() {};
  
 private:
  virtual void produce(edm::Event&, const edm::EventSetup&);

 private:
  edm::InputTag src_;
  edm::InputTag primaryVertex_;

};

#endif
