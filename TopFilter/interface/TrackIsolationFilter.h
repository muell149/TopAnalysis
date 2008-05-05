#ifndef TrackIsolationFilter_h
#define TrackIsolationFilter_h

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
class TrackIsolationFilter {

 public:

  explicit TrackIsolationFilter(const edm::ParameterSet&);
  ~TrackIsolationFilter(){};

 public:

  bool operator()(edm::Event&, const Collection&);
  void summarize(){cut_.print();};

 private:

  std::string name_;
  std::vector<double> iso_;

 private:

  CutMonitor cut_;
};

template <typename Collection> 
TrackIsolationFilter<Collection>::TrackIsolationFilter(const edm::ParameterSet& cfg):
  name_( cfg.getParameter<std::string>("name") ),
  iso_ ( cfg.getParameter<std::vector<double> >( "TrackIsolation" ) )
{
  cut_.name( name_.c_str() );
  cut_.add("sample", Cut::Boolean, true);
  for(unsigned int idx=0; idx<iso_.size(); ++idx)
    cut_.add("TrackIsolation", idx,  Cut::Lower, iso_[idx]);
}

template <typename Collection> 
bool TrackIsolationFilter<Collection>::operator()(edm::Event& evt, const Collection& objs)
{
  // start cut monitoring
  cut_.select("sample", true);  

  unsigned int idx=0;
  for(typename Collection::const_iterator obj=objs.begin();
      obj!=objs.end(); ++obj) {
    if( idx<iso_.size() ) // check for isolation as long as vector is long enough
      if( !cut_.select("TrackIsolation", idx, obj->trackIso()) ) return false;

    // break slope if both vector lengths are exceeded
    ++idx;
    if( idx>iso_.size() )
      break;
  }
  return true;
}

#endif
  
