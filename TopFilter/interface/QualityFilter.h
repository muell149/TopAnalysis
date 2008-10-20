#ifndef QualityFilter_h
#define QualityFilter_h

#include <memory>
#include <string>
#include <vector>

#include "DataFormats/TrackReco/interface/Track.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"


template <typename Collection> 
class QualityFilter {

 public:

  explicit QualityFilter(const edm::ParameterSet&);
  ~QualityFilter(){};

 public:
  
  bool operator()(edm::Event&, const std::vector<Collection>&, const double&);
  bool filter(const std::vector<Collection>&); 
  void summarize();

 private:

  std::string name_;             // cut name (for monitoring)
  std::vector<double> quality_;  // quality threshold(s)
  std::string muonType_;        // tracker, global or stand alone muon
  unsigned int mode_;           // choose 0: normalized chi^2
                                // choose 1: transverse impact parameter
			        // choose 2: number of valid hits

 private:

  unsigned int beforeCut_, afterCut_;
  double beforeCutWeighted_, afterCutWeighted_;
};

template <typename Collection> 
QualityFilter<Collection>::QualityFilter(const edm::ParameterSet& cfg):
  name_( cfg.getParameter<std::string> ("name") ),
  quality_ ( cfg.getParameter<std::vector<double> >( "quality" ) ),
  muonType_ ( cfg.getParameter<std::string>("type") ),
  mode_( cfg.getParameter<unsigned int>("mode") ),
  beforeCut_( 0 ), afterCut_( 0 ),
  beforeCutWeighted_( 0. ), afterCutWeighted_( 0. )
{
  // print applied cuts
  for(unsigned int idx=0; idx<quality_.size(); ++idx){
    std::cout << ::std::setw( 20 );
    if( idx  ==0 ) std::cout << name_;  else std::cout << " ";         
    std::cout << ": ";
    if( mode_==0 ) std::cout << "Norm Chi2";      
    if( mode_==1 ) std::cout << "abs(D0)"; 
    if( mode_==2 ) std::cout << "NValidHits";
    std::cout << " of " <<  muonType_;
    if( mode_<2 ) std::cout << " < "; else std::cout << " > "; 
    std::cout << quality_[idx] << std::endl;      
  }
}

template <typename Collection> 
bool QualityFilter<Collection>::operator()(edm::Event& evt, const std::vector<Collection>& objs, const double& weight)
{
  ++beforeCut_;
  beforeCutWeighted_ += weight;
  if( filter(objs) ) {
    ++afterCut_;
    afterCutWeighted_ += weight;
    return true;
  }
  return false;
}

template <typename Collection> 
bool QualityFilter<Collection>::filter(const std::vector<Collection>& objs)
{
  bool passedWeak=false, passedStrong=true;
  for(unsigned int jdx=0; jdx<objs.size(); ++jdx){
    bool passedOnce=true;
    // skip if this collection has less members than required
    // by the length of the vector quality_ 
    if( objs[jdx].size()<quality_.size() )
      passedOnce=false;
    
    unsigned int idx=0;
    for(typename Collection::const_iterator obj=objs[jdx].begin();
	obj!=objs[jdx].end(); ++obj) {
      if( idx<quality_.size() ){ // check for quality as long as vector is long enough
      
        // get the muon track
        reco::TrackRef trk;
	if( muonType_ == "trackerMuon" ) trk = obj->track();	  
	else if( muonType_ == "standAloneMuon" ) trk = obj->standAloneMuon();	
	else if( muonType_ == "globalMuon" ) trk = obj->combinedMuon();
	else edm::LogWarning ( "UnkownMuonType" ) << "Muon type: " << muonType_ << "is not known";
			
	if( mode_==0 ) { // track normalized chi2                         
 	  if( !(trk->normalizedChi2()<quality_[idx]) ) passedOnce=false;
	}
	if( mode_==1 ) { // track D0/D0Error
	  if( !(fabs(trk->d0())<quality_[idx]) ) passedOnce=false;
	}
	if( mode_==2 ) { // N valid hits
	  if( !(trk->numberOfValidHits()>=quality_[idx]) ) passedOnce=false;
	}		 
	if( !(mode_==0 || mode_==1 || mode_==2) ){
	  edm::LogWarning ( "UnknownQualityMode" ) << "Quality mode: " << mode_ << "is not known";
	  passedOnce=false;
	}
      }
      
      // break slope if both vector lengths are exceeded
      ++idx;
      if( idx>quality_.size() )
	break;
    }
    if(  passedOnce ) passedWeak=true;
    if( !passedOnce ) passedStrong=false;
  }
  return passedWeak;
}
template <typename Collection> 
void QualityFilter<Collection>::summarize()
{
  std::cout << ::std::setw( 20 ) << ::std::left  << name_ << " : "
	    << ::std::setw( 10 ) << ::std::right << afterCut_ << " (" 
	    << ::std::setw( 10 ) << ::std::right << afterCutWeighted_  << ") outof "
	    << ::std::setw( 10 ) << ::std::right << beforeCut_<< " (" 
	    << ::std::setw( 10 ) << ::std::right << beforeCutWeighted_ << ")" << std::endl;
}

#endif
  
