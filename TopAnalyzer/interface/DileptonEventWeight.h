#ifndef DileptonEventWeight_h
#define DileptonEventWeight_h

#include "FWCore/Framework/interface/Event.h"

double getDileptonEventWeight(const edm::Event& evt, 
                              const edm::InputTag& puweight_,
			      const edm::InputTag& lepweight_
			     );

#endif
