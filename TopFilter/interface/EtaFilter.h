#ifndef EtaFilter_h
#define EtaFilter_h

#include <memory>
#include <string>
#include <vector>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "TopAnalysis/TopUtils/interface/CutMonitor.h"


template <typename Collection> 
class EtaFilter {

 public:

  explicit EtaFilter(const edm::ParameterSet&);
  ~EtaFilter(){};

 public:

  bool operator()(const Collection&);

 private:

  CutMonitor cut_;
  std::string name_;
  std::vector<double> minEta_;
  std::vector<double> maxEta_;
};

template <typename Collection> 
EtaFilter<Collection>::EtaFilter(const edm::ParameterSet& cfg):
  name_ ( cfg.getParameter<std::string>("name") ),
  minEta_( cfg.getParameter<std::vector<double> >( "minEta" ) ),
  maxEta_( cfg.getParameter<std::vector<double> >( "maxEta" ) )
{
  cut_.name( name_.c_str() );
  cut_.add("sample", Cut::Boolean, true);
  for(unsigned int idx=0; idx<minEta_.size(); ++idx)
    cut_.add("minEta", idx,  Cut::Greater, minEta_[idx]);
  for(unsigned int idx=0; idx<minEta_.size(); ++idx)
    cut_.add("maxEta", idx,  Cut::Lower,   maxEta_[idx]);
}

template <typename Collection> 
bool EtaFilter<Collection>::operator()(const Collection& objs)
{
  // start cut monitoring
  cut_.select("sample", true);  

  unsigned int idx=0;
  for(typename Collection::const_iterator obj=objs.begin();
      obj!=objs.end(); ++obj) {
    if( idx<minEta_.size() ) // check for minEta as long as vector is long enough
      if( !cut_.select("minEta", idx, obj->eta()) ) return false;
    if( idx<maxEta_.size() ) // check for maxEta as long as vector is long enough
      if( !cut_.select("maxEta", idx, obj->eta()) ) return false;

    // break slope if both vector lengths are exceeded
    ++idx;
    if( idx>minEta_.size() && idx>maxEta_.size())
      break;
  }
  return true;
}

#endif
  
