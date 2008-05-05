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
#include "TopAnalysis/TopUtils/interface/CutMonitor.h"


template <typename Collection> 
class JetIsolationFilter {

 public:

  explicit JetIsolationFilter(const edm::ParameterSet&);
  ~JetIsolationFilter(){};

 public:

  bool operator()(edm::Event&, const Collection&);
  void summarize(){cut_.print();};

 private:

  edm::InputTag jets_;
  std::string name_;
  std::vector<double> iso_;

 private:

  CutMonitor cut_;
};

template <typename Collection> 
JetIsolationFilter<Collection>::JetIsolationFilter(const edm::ParameterSet& cfg):
  jets_( cfg.getParameter<edm::InputTag>("jets") ),
  name_( cfg.getParameter<std::string>("name") ),
  iso_ ( cfg.getParameter<std::vector<double> >( "JetIsolation" ) )
{
  cut_.name( name_.c_str() );
  cut_.add("events checked", Cut::Boolean, true);
  cut_.add("events passed ", Cut::Boolean, true);
  for(unsigned int idx=0; idx<iso_.size(); ++idx)
    cut_.add("iso", idx,  Cut::Greater, iso_[idx]);
}

template <typename Collection> 
bool JetIsolationFilter<Collection>::operator()(edm::Event& evt, const Collection& objs)
{
  bool passed=true;
  cut_.select("events checked", passed);  

  edm::Handle<std::vector<pat::Jet> > jets; 
  evt.getByLabel(jets_, jets);

  if( objs.size()<iso_.size() )
    passed=false;
  
  unsigned int idx=0;
  for(typename Collection::const_iterator obj=objs.begin();
      obj!=objs.end(); ++obj) {
    if( idx<iso_.size() ){ // check for isolation as long as vector is long enough   
      double minDR=-1.;
      for(std::vector<pat::Jet>::const_iterator jet = jets->begin(); 
	  jet!=jets->end(); ++jet) {
	double dR=deltaR(obj->eta(), obj->phi(), jet->eta(), jet->phi());
	if( minDR<0 || dR<minDR ) minDR=dR;
      }
      if( minDR<0 ){
	edm::LogWarning ( "NoJetFound" ) << "no jet nearest to object found";
	minDR=999.;
      }
      if( !cut_.select("iso", idx, minDR) ) passed=false;
    }
    // break slope if both vector lengths are exceeded
    ++idx;
    if( idx>iso_.size() )
      break;
  }
  cut_.select("events passed ", passed);  
  return passed;
}

#endif
  
