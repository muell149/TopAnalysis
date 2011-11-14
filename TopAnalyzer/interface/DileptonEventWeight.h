#ifndef DileptonEventWeight_h
#define DileptonEventWeight_h

#include "FWCore/Framework/interface/Event.h"

double getDileptonEventWeight(const edm::Event& evt, 
                              const edm::InputTag& puweight_,
			      const edm::InputTag& lepweight_
			     );

double getPuWeight(const edm::Event& evt, 
                   const edm::InputTag& puweight_);


double getDileptonSFWeight(const edm::Event& evt, 
                           const edm::InputTag& lepweight_);

double getWeight(const edm::Event& evt, const edm::InputTag& tag_);

#endif
