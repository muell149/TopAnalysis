#include "TopAnalysis/TopAnalyzer/interface/TopKinematicsGen.h"

/// default constructor for fw lite
TopKinematicsGen::TopKinematicsGen()
{
}

/// default constructor for full fw
TopKinematicsGen::TopKinematicsGen(const edm::ParameterSet& cfg)
{
}

/// histogram filling interface for rec level for access with fwlite or full framework
void
TopKinematicsGen::fill(const TtGenEvent& tops, const double& weight)
{
  if( tops.isSemiLeptonic(WDecay::kMuon) ){
    TopKinematics<TtGenEvent>::fill(tops.singleLepton()          , "muon"   , weight);
    TopKinematics<TtGenEvent>::fill(tops.leptonicDecayB()        , "bottom" , weight);
    TopKinematics<TtGenEvent>::fill(tops.leptonicDecayTop()      , "top"    , weight);
    TopKinematics<TtGenEvent>::fill(tops.hadronicDecayQuark()    , "light"  , weight);
    TopKinematics<TtGenEvent>::fill(tops.hadronicDecayQuarkBar() , "light"  , weight);
    TopKinematics<TtGenEvent>::fill(tops.hadronicDecayB()        , "bottom" , weight);
    TopKinematics<TtGenEvent>::fill(tops.hadronicDecayTop()      , "top"    , weight);
    TopKinematics<TtGenEvent>::fill(tops.hadronicDecayTop(), tops.leptonicDecayTop(), weight);
  }    
}
