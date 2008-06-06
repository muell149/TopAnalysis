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


template <typename Collection> 
class EtaFilter {

 public:

  explicit EtaFilter(const edm::ParameterSet&);
  ~EtaFilter(){};

 public:

  bool operator()(edm::Event&, const std::vector<Collection>&);
  bool filter(const std::vector<Collection>&);
  void summarize();
  
 private:

  std::string name_;
  std::vector<double> minEta_;
  std::vector<double> maxEta_;

 private:

  unsigned int beforeCut_, afterCut_;
};

template <typename Collection> 
EtaFilter<Collection>::EtaFilter(const edm::ParameterSet& cfg):
  name_ ( cfg.getParameter<std::string>("name") ),
  minEta_( cfg.getParameter<std::vector<double> >( "minEta" ) ),
  maxEta_( cfg.getParameter<std::vector<double> >( "maxEta" ) ),
  beforeCut_( 0 ), afterCut_( 0 )
{
}

template <typename Collection> 
bool EtaFilter<Collection>::operator()(edm::Event& evt, const std::vector<Collection>& objs)
{
   ++beforeCut_;
  if( filter(objs) ) {
    ++afterCut_;
    return true;
  }
  return false;
}

template <typename Collection> 
bool EtaFilter<Collection>::filter(const std::vector<Collection>& objs)
{
  bool passedWeak=false, passedStrong=true;
  for(unsigned int jdx=0; jdx<objs.size(); ++jdx){
    bool passedOnce=true;
    // skip if this collection has less members than required
    // by the length of the vectors of minEta_ or maxEta_ 
    if( objs[jdx].size()<minEta_.size() || objs[jdx].size()<maxEta_.size() )
      passedOnce=false;
    
    unsigned int idx=0;
    for(typename Collection::const_iterator obj=objs[jdx].begin();
	obj!=objs[jdx].end(); ++obj) {
      if( idx<minEta_.size() ) // check for minEta as long as vector is long enough
	if( !(obj->eta()>minEta_[idx]) ) passedOnce=false;
      if( idx<maxEta_.size() ) // check for maxEta as long as vector is long enough
	if( !(obj->eta()<maxEta_[idx]) ) passedOnce=false;
      
      // break slope if both vector lengths are exceeded
      ++idx;
      if( idx>minEta_.size() && idx>maxEta_.size())
	break;
    }
    if(  passedOnce ) passedWeak=true;
    if( !passedOnce ) passedStrong=false;
  }
  return passedWeak;
}

template <typename Collection> 
void EtaFilter<Collection>::summarize()
{
  using std::cout;
  using std::endl;

  unsigned int maxSize=minEta_.size();
  if(maxEta_.size()>maxSize) maxSize=maxEta_.size();
  cout << "******************************************************" << endl;
  for(unsigned int idx=0; idx<maxSize; ++idx){
    cout << ::std::setw( 20 );
    if(idx==0) cout << name_; else cout << "   ";  
    cout << ": ";
    if(idx<minEta_.size()) cout << minEta_[idx] << " < Eta"; else cout << "   Eta"; 
    if(idx<maxEta_.size()) cout << " < " << maxEta_[idx] << endl;
  }
  cout << "------------------------------------------------------" << endl 
       << "  Events Before Cut: " << ::std::setw( 10 ) << ::std::right << beforeCut_ << endl
       << "  Events After  Cut: " << ::std::setw( 10 ) << ::std::right << afterCut_  << endl;
}

#endif
  
