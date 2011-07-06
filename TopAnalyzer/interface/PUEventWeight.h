#ifndef PUEventWeight_h
#define PUEventWeight_h

#include "FWCore/Framework/interface/Event.h"

double getPUEventWeight(const edm::Event& evt, const edm::InputTag& tag);

#endif
