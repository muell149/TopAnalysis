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


template <typename Collection> 
class TrackIsolationFilter {

 public:

  explicit TrackIsolationFilter(const edm::ParameterSet&);
  ~TrackIsolationFilter(){};

 public:

  bool operator()(edm::Event&, const Collection&);
  void summarize();

 private:

  std::string name_;
  std::vector<double> iso_;

 private:

  unsigned int beforeCut_, afterCut_;
};

template <typename Collection> 
TrackIsolationFilter<Collection>::TrackIsolationFilter(const edm::ParameterSet& cfg):
  name_( cfg.getParameter<std::string>("name") ),
  iso_ ( cfg.getParameter<std::vector<double> >( "TrackIsolation" ) ),
  beforeCut_( 0 ), afterCut_( 0 )
{
}

template <typename Collection> 
bool TrackIsolationFilter<Collection>::operator()(edm::Event& evt, const Collection& objs)
{
  ++beforeCut_;
  bool passed=true;
  if( objs.size()<iso_.size() )
    passed=false;
  
  unsigned int idx=0;
  for(typename Collection::const_iterator obj=objs.begin();
      obj!=objs.end(); ++obj) {
    if( idx<iso_.size() ) // check for isolation as long as vector is long enough
      if( !(obj->trackIso()<iso_[idx]) ) passed=false;
    
    // break slope if both vector lengths are exceeded
    ++idx;
    if( idx>iso_.size() )
      break;
  }
  if( passed ) ++afterCut_;
  return passed;
}

template <typename Collection> 
void TrackIsolationFilter<Collection>::summarize()
{
  using std::cout;
  using std::endl;

  cout << "******************************************************" << endl;
  for(unsigned int idx=0; idx<iso_.size(); ++idx)
    if(idx==0) cout << ::std::setw( 20 ) 
		    << name_ << ": " 
		    << " TrackIsolation < " << iso_[idx] << endl;
    else       cout << ::std::setw( 20 ) 
		    << ": " 
		    << " TrackIsolation < " << iso_[idx] << endl;
  cout << "------------------------------------------------------" << endl 
       << "  Events Before Cut: " << ::std::setw( 10 ) << ::std::right << beforeCut_ << endl
       << "  Events After  Cut: " << ::std::setw( 10 ) << ::std::right << afterCut_  << endl;
}

#endif
  
