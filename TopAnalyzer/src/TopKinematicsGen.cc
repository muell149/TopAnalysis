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
  if( tops.isTtBar() ){
    if( tops.hadronicDecayTop() && tops.leptonicDecayTop() ){
      TopKinematics<const TtGenEvent>::fill(tops.hadronicDecayTop(), tops.leptonicDecayTop(), weight);
    }    
  }
}
