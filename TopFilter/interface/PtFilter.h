#ifndef PtFilter_h
#define PtFilter_h

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
class PtFilter {

 public:

  explicit PtFilter(const edm::ParameterSet&);
  ~PtFilter(){};

 public:

  bool operator()(edm::Event&, const Collection&);
  void summarize(){cut_.print();};

 private:

  std::string name_;
  std::vector<double> minPt_;
  std::vector<double> maxPt_;

 private:

  CutMonitor cut_;
};

template <typename Collection> 
PtFilter<Collection>::PtFilter(const edm::ParameterSet& cfg):
  name_ ( cfg.getParameter<std::string>("name") ),
  minPt_( cfg.getParameter<std::vector<double> >( "minPt" ) ),
  maxPt_( cfg.getParameter<std::vector<double> >( "maxPt" ) )
{
  cut_.name( name_.c_str() );
  cut_.add("sample", Cut::Boolean, true);
  for(unsigned int idx=0; idx<minPt_.size(); ++idx)
    cut_.add("minPt", idx,  Cut::Greater, minPt_[idx]);
  for(unsigned int idx=0; idx<maxPt_.size(); ++idx)
    cut_.add("maxPt", idx,  Cut::Lower,   maxPt_[idx]);
}

template <typename Collection> 
bool PtFilter<Collection>::operator()(edm::Event& evt, const Collection& objs)
{
  // start cut monitoring
  cut_.select("sample", true);  

  unsigned int idx=0;
  for(typename Collection::const_iterator obj=objs.begin();
      obj!=objs.end(); ++obj) {
    if( idx<minPt_.size() ) // check for minPt as long as vector is long enough
      if( !cut_.select("minPt", idx, obj->pt()) ) return false;
    if( idx<maxPt_.size() ) // check for maxPt as long as vector is long enough
      if( !cut_.select("maxPt", idx, obj->pt()) ) return false;

    // break slope if both vector lengths are exceeded
    ++idx;
    if( idx>minPt_.size() && idx>maxPt_.size())
      break;
  }
  return true;
}

#endif
  
