// -*- C++ -*-
//
// Package:    TriggerFilterFilter
// Class:      TriggerFilterFilter
//
/**\class TriggerFilterFilter TriggerFilterFilter.cc TopAnalysis/TriggerFilterFilter/src/TriggerFilterFilter.cc

Description: Make a cut on an L3 sub Trigger Filter (e.g. hltEle25CaloIdVTTrkIdTCaloIsoTTrkIsoTTrackIsolFilter):
             hltFilter

*/


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

class TriggerFilterFilter : public edm::EDFilter {
public:
  explicit TriggerFilterFilter(const edm::ParameterSet&);
  ~TriggerFilterFilter();

private:
  virtual void beginJob() ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data ---------------------------
  edm::InputTag triggerEvent_;
  std::string hltFilter_;
};


//
// constructors and destructor
//
TriggerFilterFilter::TriggerFilterFilter(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed

  triggerEvent_ = iConfig.getParameter<edm::InputTag>("trigger_event");
  hltFilter_         = iConfig.getParameter<std::string>("hltFilter");
  
  std::cout<<"Considered trigger filter:"<<std::endl;
  std::cout<<hltFilter_<<std::endl;

}


TriggerFilterFilter::~TriggerFilterFilter()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
TriggerFilterFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{


  edm::Handle<pat::TriggerEvent> triggerEvent;
  iEvent.getByLabel(triggerEvent_, triggerEvent);

  const pat::TriggerFilterCollection*      triggerFilters = triggerEvent->filters();
  
  //const pat::TriggerPathCollection*        triggerPaths   = triggerEvent->paths();
  //const pat::TriggerPath* hltPath = 0;
  
  for(unsigned iFilter=0; iFilter < triggerFilters->size(); iFilter++){
    
    const pat::TriggerFilter* L3filter = &triggerFilters->at(iFilter);
    
    if(L3filter->label()==hltFilter_ && L3filter->isL3() && L3filter->isFiring()){
      //std::cout<<hltFilter_<<" found and fired" <<std::endl;
     return true;
    }
    //if(L3filter->label()==hltFilter_) std::cout<<hltFilter_ << " found" <<std::endl
  }
  //std::cout<<hltFilter_ <<" NOOOOT found and firing" <<std::endl;
  return false;
  
//   for(pat::TriggerPathCollection::const_iterator trp = triggerPaths->begin(); trp!= triggerPaths->end(); ++trp) {
//     for(unsigned int iPath=0; iPath < paths_.size(); iPath++){
//       //std::cout<<trp->name() <<std::endl;
//       if(trp->name()==paths_[iPath]){
//       hltPath = &(*trp);
//       // fail if trigger has not fired, is offline or has an error
//       std::cout<<trp->name() << "hltPath " <<hltPath << std::endl;
//       if(!hltPath->wasRun()) std::cout<<"HLT not run" <<std::endl;
//       if(!hltPath->wasAccept()) std::cout<<"HLT not accepted" <<std::endl;
//       if(hltPath->wasError()) std::cout<<"HLT error" <<std::endl;
//       if(!hltPath->wasRun() || !hltPath->wasAccept() || hltPath->wasError()){
// 	std::cout<<"HLT trigger not fired" <<std::endl;
// 	//return false;
//       }
//       }
//     }
//   }
  
//   if(hltPath!=0){
//     std::cout<<"hltPath "<< hltPath->name() <<" found"<<std::endl;
// 
//     for(unsigned iFilter=0; iFilter < hltPath->l3Filters(); iFilter++){
//       unsigned iFilterKey = hltPath->filterIndices()[iFilter];
//       const pat::TriggerFilter* L3filter = &triggerFilters->at(iFilterKey);
//       std::cout<<"iFilter: " <<iFilter<< "; TriggerFilterName: "<<L3filter->label() <<"; isL3: "
// 	  <<L3filter->isL3() <<"; isFiring: " <<L3filter->isFiring() <<std::endl;
//     }
//     return false;
//   }
//   else std::cout<<"hltPaths not found"<<std::endl;
//   return false;
}

// ------------ method called once each job just before starting event loop  ------------
void
TriggerFilterFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TriggerFilterFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerFilterFilter);
