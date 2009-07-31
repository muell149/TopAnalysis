#include "TopAnalysis/TopAnalyzer/interface/TopKinematicsMatch.h"

/// default constructor for fw lite
TopKinematicsMatch::TopKinematicsMatch(const int& hypoKey):TopKinematicsRec(hypoKey)
{
}

/// default constructor for full fw
TopKinematicsMatch::TopKinematicsMatch(const edm::ParameterSet& cfg):TopKinematicsRec(cfg)
{
}

/// histogram filling interface for rec level for access with fwlite or full framework
void
TopKinematicsMatch::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  if( tops.isHypoValid(hypoKey_) ){
    if( tops.hadronicTop(hypoKey_) && tops.leptonicTop(hypoKey_) ){
      if( tops.genEvent()->isTtBar() ){
	if( tops.genEvent()->hadronicDecayTop() && tops.genEvent()->leptonicDecayTop() ){	
	  TopKinematics<const TtSemiLeptonicEvent>::fill(tops.hadronicTop(hypoKey_), tops.leptonicTop(hypoKey_), 
							 tops.genEvent()->hadronicDecayTop(), tops.genEvent()->leptonicDecayTop(), weight);
	}
      }
    }
  }
}
