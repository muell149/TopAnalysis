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
    if( tops.genEvent()->isSemiLeptonic(WDecay::kMuon) ){
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.singleLepton     (hypoKey_)     , tops.singleLepton()         , "muon"   , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.leptonicDecayB   (hypoKey_)     , tops.leptonicDecayB()       , "bottom" , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.leptonicDecayTop (hypoKey_)     , tops.leptonicDecayTop()     , "top"    , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicDecayQuark(hypoKey_)    , tops.hadronicDecayQuark()   , "light"  , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicDecayQuarkBar(hypoKey_) , tops.hadronicDecayQuarkBar(), "light"  , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicDecayB   (hypoKey_)     , tops.hadronicDecayB()       , "bottom" , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicDecayTop (hypoKey_)     , tops.hadronicDecayTop()     , "top"    , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicDecayTop (hypoKey_)     , tops.hadronicDecayTop()     , tops.leptonicDecayTop(hypoKey_), tops.leptonicDecayTop(), weight);
    }
  }
}

