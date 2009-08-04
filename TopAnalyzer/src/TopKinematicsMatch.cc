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
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.lepton     (hypoKey_) , tops.genLepton()      , "muon"   , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.leptonicB  (hypoKey_) , tops.genLeptonicB()   , "bottom" , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.leptonicTop(hypoKey_) , tops.genLeptonicTop() , "top"    , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.lightQuarkP(hypoKey_) , tops.genHadronicQ()   , "light"  , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.lightQuarkQ(hypoKey_) , tops.genHadronicP()   , "light"  , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicB  (hypoKey_) , tops.genHadronicB()   , "bottom" , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicTop(hypoKey_) , tops.genHadronicTop() , "top"    , weight);
      TopKinematics<TtSemiLeptonicEvent>::fill(tops.hadronicTop(hypoKey_) , tops.genHadronicTop() , tops.leptonicTop(hypoKey_), tops.genLeptonicTop(), weight);
    }
  }
}

