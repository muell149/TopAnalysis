// -*- C++ -*-
//
// Package:    TriggerObjectFilter
// Class:      TriggerObjectFilter
//
/**\class TriggerObjectFilter TriggerObjectFilter.cc TopAnalysis/TriggerObjectFilter/src/TriggerObjectFilter.cc

Description: Make additional E_t and/or p_t cut on trigger objects on a certain path

Implementation:
In case an error occures while retrieving the trigger object, the event fails the selection. TO-DO: Throw exception instead.
*/
//
// Original Author:  Benjamin Lutz,,,DESY
//         Created:  Fri Dec 17 16:33:59 CET 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
//#include "DataFormats/PatCandidates/interface/TriggerObject.h"
//#include "DataFormats/PatCandidates/interface/TriggerFilter.h"
//#include "DataFormats/PatCandidates/interface/TriggerPath.h"



//
// class declaration
//

class TriggerObjectFilter : public edm::EDFilter {
public:
  explicit TriggerObjectFilter(const edm::ParameterSet&);
  ~TriggerObjectFilter();

private:
  virtual void beginJob() ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data ---------------------------
  edm::InputTag triggerEvent_;
  std::string path_;
  unsigned int nMin_;
  double ptMin_;
  double etMin_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerObjectFilter::TriggerObjectFilter(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed

  triggerEvent_ = iConfig.getParameter<edm::InputTag>("trigger_event");
  path_         = iConfig.getParameter<std::string>("hltPath");

  nMin_         = iConfig.getParameter<unsigned int>("nMin");
  ptMin_        = iConfig.getParameter<double>("ptMin");
  etMin_        = iConfig.getParameter<double>("etMin");

}


TriggerObjectFilter::~TriggerObjectFilter()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
TriggerObjectFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  edm::Handle<pat::TriggerEvent> triggerEvent;
  iEvent.getByLabel(triggerEvent_, triggerEvent);

  const pat::TriggerObjectCollection*      triggerObjects = triggerEvent->objects();
  const pat::TriggerFilterCollection*      triggerFilters = triggerEvent->filters();
  const pat::TriggerPathCollection*        triggerPaths   = triggerEvent->paths();

  const pat::TriggerPath* hltPath = 0;

  for(pat::TriggerPathCollection::const_iterator trp = triggerPaths->begin(); trp!= triggerPaths->end(); ++trp) {
    if(trp->name()==path_){
      hltPath = &(*trp);
      // fail if trigger has not fired, is offline or has an error
      if(!hltPath->wasRun() || !hltPath->wasAccept() || hltPath->wasError()) return false;
    }
  }

  int L3filterIdx = hltPath->filterIndices().back();
  const pat::TriggerFilter* L3filter = &triggerFilters->at(L3filterIdx);

  std::vector<unsigned int> L3objectKeys = L3filter->objectKeys();

  unsigned int counter=0;

  for(size_t i=0; i<L3objectKeys.size();++i)
    if ( triggerObjects->at(L3objectKeys[i]).et() >= etMin_ &&  triggerObjects->at(L3objectKeys[i]).pt() >= ptMin_ ) ++counter;

  if (counter >= nMin_) return true;

  return false;
}

// ------------ method called once each job just before starting event loop  ------------
void
TriggerObjectFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TriggerObjectFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerObjectFilter);
