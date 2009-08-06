#include "TopAnalysis/TopAnalyzer/interface/TopKinematicsRec.h"

/// default constructor for fw lite
TopKinematicsRec::TopKinematicsRec(const int& hypoKey)
{
  // get hypothesis class key from the event
  hypoKey_ = (TtEvent::HypoClassKey) hypoKey;
}

/// default constructor for full fw
TopKinematicsRec::TopKinematicsRec(const edm::ParameterSet& cfg):
  hypoKey_( cfg.getParameter<std::string>("hypoKey") )
{
}

/// histogram filling interface for rec level for access with fwlite or full framework
void
TopKinematicsRec::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  if( tops.isHypoValid(hypoKey_) ){
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.singleLepton      (hypoKey_)     , "muon"   , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.leptonicDecayB    (hypoKey_)     , "bottom" , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.leptonicDecayTop  (hypoKey_)     , "top"    , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicDecayQuark(hypoKey_)     , "light"  , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicDecayQuarkBar(hypoKey_)  , "light"  , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicDecayB    (hypoKey_)     , "bottom" , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicDecayTop  (hypoKey_)     , "top"    , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicDecayTop  (hypoKey_), tops.leptonicDecayTop(hypoKey_), weight);
  }
}
