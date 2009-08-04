#include "TopAnalysis/TopAnalyzer/interface/TopKinematicsRec.h"

/// default constructor for fw lite
TopKinematicsRec::TopKinematicsRec(const int& hypoKey)
{
  // get hypothesis class key from the event
  hypoKey_ = (TtEvent::HypoClassKey) hypoKey;
}

/// default constructor for full fw
TopKinematicsRec::TopKinematicsRec(const edm::ParameterSet& cfg)
{
  // get hypothesis class key from the event; sorry the 
  // structure does not allow to dig it outof the event
  hypoKey_ = (TtEvent::HypoClassKey) cfg.getParameter<int>("hypoKey");
}

/// histogram filling interface for rec level for access with fwlite or full framework
void
TopKinematicsRec::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  if( tops.isHypoValid(hypoKey_) ){
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.lepton     (hypoKey_) , "muon"   , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.leptonicB  (hypoKey_) , "bottom" , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.leptonicTop(hypoKey_) , "top"    , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.lightQuarkP(hypoKey_) , "light"  , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.lightQuarkQ(hypoKey_) , "light"  , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicB  (hypoKey_) , "bottom" , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicTop(hypoKey_) , "top"    , weight);
    TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicTop(hypoKey_), tops.leptonicTop(hypoKey_), weight);
  }
}
