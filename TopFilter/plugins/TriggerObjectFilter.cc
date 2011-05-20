// -*- C++ -*-
//
// Package:    TriggerObjectFilter
// Class:      TriggerObjectFilter
//
/**\class TriggerObjectFilter TriggerObjectFilter.cc TopAnalysis/TriggerObjectFilter/src/TriggerObjectFilter.cc

Description: Make additional E_t and/or p_t cut on trigger objects on a certain path.
             To account for possibly different version numbers of a trigger, all possible versions
             can be passed in a string to hltPaths, e.g. hltPaths = ["HLT_Mu15", "HLT_Mu15_v1", ...]

Implementation:
In case an error occures while retrieving the trigger object, the event fails the selection. TO-DO: Throw exception instead.
*/
//
// Original Author:  Benjamin Lutz,,,DESY
//         Created:  Fri Dec 17 16:33:59 CET 2010
// $Id: TriggerObjectFilter.cc,v 1.1 2011/02/09 11:43:30 maldayam Exp $
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
  std::vector<std::string> paths_;
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
  paths_        = iConfig.getParameter<std::vector<std::string> >("hltPaths");

  nMin_         = iConfig.getParameter<unsigned int>("nMin");
  ptMin_        = iConfig.getParameter<double>("ptMin");
  etMin_        = iConfig.getParameter<double>("etMin");
  
  // if trigger path is only given as a normal string (hltPath, path_), it is converted to the vector hltPaths (paths_)
  // if trigger path is given as string vector hltPaths (paths_), the normal string (hltPath, path_) is ignored
  if( paths_.size()==0 ) paths_.push_back(path_);
  
  std::cout<<"Considered trigger path(s):"<<std::endl;
  for(unsigned int i=0; i<paths_.size(); i++) std::cout<<paths_[i]<<std::endl;

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
    for(unsigned int iPath=0; iPath < paths_.size(); iPath++){
      if(trp->name()==paths_[iPath]){
      hltPath = &(*trp);
      // fail if trigger has not fired, is offline or has an error
      if(!hltPath->wasRun() || !hltPath->wasAccept() || hltPath->wasError()) return false;
      }
    }
  }
  
  if(hltPath!=0){
    //std::cout<<"hltPath "<< hltPath->name() <<" found"<<std::endl;

  int L3filterIdx = hltPath->filterIndices().back();
  const pat::TriggerFilter* L3filter = &triggerFilters->at(L3filterIdx);

  std::vector<unsigned int> L3objectKeys = L3filter->objectKeys();

  unsigned int counter=0;

  for(size_t i=0; i<L3objectKeys.size();++i)
    if ( triggerObjects->at(L3objectKeys[i]).et() >= etMin_ &&  triggerObjects->at(L3objectKeys[i]).pt() >= ptMin_ ) ++counter;

  if (counter >= nMin_) return true;
  }
  else std::cout<<"hltPaths not found"<<std::endl;

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
