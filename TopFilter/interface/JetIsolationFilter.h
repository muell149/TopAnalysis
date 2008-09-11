#ifndef JetIsolationFilter_h
#define JetIsolationFilter_h

#include <memory>
#include <string>
#include <vector>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Jet.h"


template <typename Collection> 
class JetIsolationFilter {

 public:

  explicit JetIsolationFilter(const edm::ParameterSet&);
  ~JetIsolationFilter(){};

 public:

  bool operator()(edm::Event&, const std::vector<Collection>&, const double&);
  bool filter(edm::Handle<std::vector<pat::Jet> >& , const std::vector<Collection>&);  
  void summarize();
  
 private:
  
  edm::InputTag jets_;
  std::string name_;
  std::vector<double> iso_;
  std::vector<double> minJetPt_;
  
 private:
  
  unsigned int beforeCut_, afterCut_;
  double beforeCutWeighted_, afterCutWeighted_;
};

template <typename Collection> 
JetIsolationFilter<Collection>::JetIsolationFilter(const edm::ParameterSet& cfg):
  jets_     ( cfg.getParameter<edm::InputTag>       ("jets"      ) ),
  name_     ( cfg.getParameter<std::string>         ("name"      ) ),
  iso_      ( cfg.getParameter<std::vector<double> >("isolation" ) ),
  minJetPt_ ( cfg.getParameter<std::vector<double> >("minJetPt" ) ),
  beforeCut_( 0 ), afterCut_( 0 )
{
  if( iso_.size() != minJetPt_.size() )
    throw edm::Exception( edm::errors::Configuration,
			  "Length of vector 'isolation' is different from length of vector 'minJetPt'" );
  // print applied cuts
  for(unsigned int idx=0; idx<iso_.size(); ++idx) {
    std::cout << ::std::setw( 20 );
    if(idx==0) std::cout << name_; else std::cout << " ";
    std::cout << ": "
	      << "JetIsolation > " << iso_[idx] << std::endl
	      << ::std::setw( 20 ) << " "
	      << "   using jetPt > " << minJetPt_[idx] << std::endl;
  }
}

template <typename Collection> 
bool JetIsolationFilter<Collection>::operator()(edm::Event& evt, const std::vector<Collection>& objs, const double& weight)
{
  edm::Handle<std::vector<pat::Jet> > jets;
  evt.getByLabel(jets_, jets);
  ++beforeCut_;
  beforeCutWeighted_ += weight;
  if( filter(jets, objs) ){
    ++afterCut_;
   afterCutWeighted_ += weight;
   return true;
  }
  return false;
}

template <typename Collection> 
bool JetIsolationFilter<Collection>::filter(edm::Handle<std::vector<pat::Jet> >& jets, const std::vector<Collection>& objs)
{
  bool passedWeak=false, passedStrong=true;
  for(unsigned int jdx=0; jdx<objs.size(); ++jdx){
    bool passedOnce=true;
    // skip if this collection has less members than required
    // by the length of the vector iso_
    if( objs[jdx].size()<iso_.size() )
      passedOnce=false;
    
    unsigned int idx=0;
    for(typename Collection::const_iterator obj=objs[jdx].begin();
	obj!=objs[jdx].end(); ++obj) {
      if( idx<iso_.size() ){ // check for isolation as long as vector is long enough       
	double minDR=-1.;
	for(std::vector<pat::Jet>::const_iterator jet = jets->begin();
	    jet!=jets->end(); ++jet) {
	  if( jet->pt()<minJetPt_[idx] ) continue; // skip jet if too soft
	  double dR=deltaR(obj->eta(), obj->phi(), jet->eta(), jet->phi());
	  if( minDR<0 || dR<minDR ) minDR=dR;
	}
	if( minDR<0 ){
	  edm::LogWarning ( "NoJetFound" ) << "no jet nearest to object found";
	  minDR=999.;
	}
	if( !(minDR>iso_[idx]) ) passedOnce=false;
      }
      // break slope if both vector lengths are exceeded
      ++idx;
      if( idx>iso_.size() )
	break;
    }
    if(  passedOnce ) passedWeak=true;
    if( !passedOnce ) passedStrong=false;
  }
  return passedWeak;
}

template <typename Collection> 
void JetIsolationFilter<Collection>::summarize()
{
  std::cout << " " << name_ 
	    << ::std::setw( 10 ) << ::std::right << " : "
	    << ::std::setw( 10 ) << ::std::right << afterCut_ << " (" 
	    << ::std::setw( 10 ) << ::std::right << afterCutWeighted_  << ") outof "
	    << ::std::setw( 10 ) << ::std::right << beforeCut_<< " (" 
	    << ::std::setw( 10 ) << ::std::right << beforeCutWeighted_ << ")" << std::endl;
}

#endif
  
