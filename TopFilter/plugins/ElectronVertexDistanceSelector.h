#ifndef ElectronVertexDistanceSelector_h
#define ElectronVertexDistanceSelector_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


class ElectronVertexDistanceSelector : public edm::EDProducer {

 public:
  explicit ElectronVertexDistanceSelector(const edm::ParameterSet&);
  ~ElectronVertexDistanceSelector() {};
  
 private:
  virtual void produce(edm::Event&, const edm::EventSetup&);

 private:
  edm::InputTag src_;
  edm::InputTag primaryVertex_;

};

#endif
