#include "TopAnalysis/TopFilter/plugins/NewTriggerTestFilter.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
//#include "DataFormats/PatCandidates/interface/TriggerPath.h"

#include "FWCore/Framework/interface/Event.h"

NewTriggerTestFilter::NewTriggerTestFilter(const edm::ParameterSet& cfg):
  whichTrigger_   ( cfg.getParameter<std::string>  ("whichTrigger"   ) ),
  useEventWeight_ ( cfg.getParameter<bool>         ("useEventWeight" ) ),
  weight_         ( cfg.getParameter<edm::InputTag>("weight"         ) ),
  patTriggerEvent_( cfg.getParameter<edm::InputTag>("patTriggerEvent") ),
  beforeCut_( 0 ), afterCut_( 0 ), beforeCutWeighted_( 0. ), afterCutWeighted_( 0. )
{
}

bool NewTriggerTestFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{
  double weight = 1.;
  if(useEventWeight_) { 
    edm::Handle<double> weightHandle;
    event.getByLabel(weight_, weightHandle);
    weight = *weightHandle;
  }

  ++beforeCut_;
  beforeCutWeighted_ += weight;

  bool pass = false;

  edm::Handle<pat::TriggerEvent> triggerEvent;
  event.getByLabel(patTriggerEvent_, triggerEvent);
  
  bool L1Triggered = false;
  bool HLTriggered = false;
  /*
  pat::TriggerFilterRefVector filters = triggerEvent->acceptedFilters();
  for(pat::TriggerFilterRefVector::const_iterator filter = filters.begin(); filter != filters.end(); ++filter){
    std::cout << (*filter)->label() << std::endl;
    //if((*filter)->label() == "hltL1sQuadJet30") L1Triggered = true;
  }
  */
  /*
  pat::TriggerPathRefVector paths = triggerEvent->acceptedPaths();
  for(pat::TriggerPathRefVector::const_iterator path = paths.begin(); path != paths.end(); ++path){
    std::cout << (*path)->name() << std::endl;
  }
  */
  pat::TriggerObjectRefVector objects = triggerEvent->filterObjects("hlt4jet30");

  //bool oldPass = false;

  int l1TriggerJetCounter = 0;
  int hlTriggerJetCounter = 0;

  if(whichTrigger_ == "QuadJet80303030"){
    if(objects[0]->pt() >= 80){
      pass = true;
    }
  }
  else if(whichTrigger_ == "QuadJet40"){
    if(objects.size() >= 4){
      if(objects[0]->pt() >= 40){
	if(objects[1]->pt() >= 40){
	  if(objects[2]->pt() >= 40){
	    if(objects[3]->pt() >= 40){
	      pass = true;
	    }
	  }
	}
      }
    }
  }
  else if(whichTrigger_ == "FiveJet30"){
    if(objects.size() >= 5){
      if(objects[4]->pt() >= 30){
	pass = true;
      }
    }
  }
  else if(whichTrigger_ == "DiJet40"){
    pat::TriggerFilterRefVector filters = triggerEvent->acceptedFilters();
    for(pat::TriggerFilterRefVector::const_iterator filter = filters.begin(); filter != filters.end(); ++filter){
      if((*filter)->label() == "hlt1jet30") {
	objects = triggerEvent->filterObjects("hlt1jet30");
	if(objects[0]->pt() >= 40){
	  if(objects.size() >= 2){
	    if(objects[1]->pt() >= 40){
	      pass = true;
	    }
	  }
	}
      }
    }
  }
  else if(whichTrigger_ == "QuadJet15U"){

    for(pat::TriggerObjectCollection::const_iterator obj = triggerEvent->objects()->begin(); obj != triggerEvent->objects()->end(); ++obj){
      if( (obj->hasFilterId(-84) || obj->hasFilterId(-85) || obj->hasFilterId(-86)) && obj->pt() >= 8 )      { ++l1TriggerJetCounter; }
      if( obj->hasFilterId(85) && obj->pt() >= 15 && obj->collection() == "hltIterativeCone5CaloJets::HLT" ) { ++hlTriggerJetCounter; }
    }

    if( l1TriggerJetCounter >= 4 ){
      if( hlTriggerJetCounter >= 4 ){
	pass = true;
      }
    }
  }
  else if(whichTrigger_ == "QuadJet25U"){

    pat::TriggerObjectRefVector objects = triggerEvent->filterObjects("hltL1sQuadJet15U");

    if(objects.size() == 0) objects = triggerEvent->filterObjects("hltL1sL1QuadJet6U");
    if(objects.size() == 0) objects = triggerEvent->filterObjects("hltL1sL1QuadJet8U");

    for(pat::TriggerObjectRefVector::const_iterator obj = objects.begin(); obj != objects.end(); ++obj){
      if( (*obj)->pt() >= 8 ) ++l1TriggerJetCounter;
    }

    objects = triggerEvent->filterObjects("hlt4jet15U");

    if(objects.size() == 0) objects = triggerEvent->filterObjects("hlt4jet20U");
    if(objects.size() == 0) objects = triggerEvent->filterObjects("hlt4jet25U");

    for(pat::TriggerObjectRefVector::const_iterator obj = objects.begin(); obj != objects.end(); ++obj){
      if( (*obj)->pt() >= 25 ) ++hlTriggerJetCounter;
    }

    if( l1TriggerJetCounter >= 4 ){
      if( hlTriggerJetCounter >= 4 ){
	pass = true;
      }
    }

    /*    
    std::multimap<unsigned int, pat::TriggerObject> triggerObjects;
    std::vector<pat::TriggerObject> sortedObjects;

    for(pat::TriggerObjectRefVector::const_iterator obj = objects.begin(); obj != objects.end(); ++obj){
      triggerObjects.insert( std::pair< unsigned int , pat::TriggerObject >( (*obj->get()).pt() , (*obj->get()) ) );
    }
    for(std::multimap<unsigned int, pat::TriggerObject>::const_reverse_iterator obj = triggerObjects.rbegin(); obj != triggerObjects.rend(); ++obj){
      sortedObjects.push_back(obj->second);
    }

    if(sortedObjects.size() >= 4){
      if(sortedObjects[0].pt() >= 8){
	if(sortedObjects[1].pt() >= 8){
	  if(sortedObjects[2].pt() >= 8){
	    if(sortedObjects[3].pt() >= 8){
	      L1Triggered = true;
	    }
	  }
	}
      }
    }

    //if(triggerEvent->path("HLT_QuadJet15U")) std::cout << triggerEvent->path("HLT_QuadJet15U")->prescale() << std::endl;

    objects = triggerEvent->filterObjects("hlt4jet15U");

    triggerObjects.clear();
    sortedObjects.clear();

    for(pat::TriggerObjectRefVector::const_iterator obj = objects.begin(); obj != objects.end(); ++obj){
      triggerObjects.insert( std::pair< unsigned int , pat::TriggerObject >( (*obj->get()).pt() , (*obj->get()) ) );
    }
    for(std::multimap<unsigned int, pat::TriggerObject>::const_reverse_iterator obj = triggerObjects.rbegin(); obj != triggerObjects.rend(); ++obj){
      sortedObjects.push_back(obj->second);
    }

    if(sortedObjects.size() >= 4){
      if(sortedObjects[0].pt() >= 25){
	if(sortedObjects[1].pt() >= 25){
	  if(sortedObjects[2].pt() >= 25){
	    if(sortedObjects[3].pt() >= 25){
	      HLTriggered = true;
	    }
	  }
	}
      }
    }

    if(L1Triggered && HLTriggered){
      pass = true;
    }
    */
  }
  else if(whichTrigger_ == "Jet50U"){

    for(pat::TriggerObjectCollection::const_iterator obj = triggerEvent->objects()->begin(); obj != triggerEvent->objects()->end(); ++obj){
      if( obj->hasFilterId(-84) || obj->hasFilterId(-85) || obj->hasFilterId(-86) ){
	if( obj->pt() >= 30 ){
	  L1Triggered = true;
	}
      }
      if( obj->hasFilterId(85) ){
	if( obj->pt() >= 50 && obj->collection() == "hltIterativeCone5CaloJets::HLT") {
	  HLTriggered = true;
	}
      }
      if(L1Triggered && HLTriggered){
	pass = true;
	break;
      }
    }
  }
  return pass;
}

void NewTriggerTestFilter::beginJob()
{
}

void NewTriggerTestFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( NewTriggerTestFilter );
