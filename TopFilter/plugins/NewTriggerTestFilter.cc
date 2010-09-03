#include "TopAnalysis/TopFilter/plugins/NewTriggerTestFilter.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

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
    if((*filter)->label() == "hltL1sQuadJet30") L1Triggered = true;
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
    if(objects[0]->pt() >= 40){
      if(objects[1]->pt() >= 40){
	if(objects[2]->pt() >= 40){
	  if(objects[3]->pt() >= 40){
	    pass = true;
	    //oldPass = true;
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
      if( obj->hasFilterId(-84) || obj->hasFilterId(-85) ){
	//std::cout << obj->collection() << " :: " << obj->eta() << std::endl;
	if( obj->pt() >= 6 ){
	  ++l1TriggerJetCounter;
	  if( l1TriggerJetCounter == 4 ){
	    L1Triggered = true;
	    //std::cout << "4 jets on L1" << std::endl;
	  }
	}
      }
      if( obj->hasFilterId(85) ){
	//std::cout << obj->collection() << std::endl;
	//if( obj->pt() >= 40 && obj->collection() == "hltMCJetCorJetIcone5::HLT") {
	if( obj->pt() >= 15 && obj->collection() == "hltIterativeCone5CaloJets::HLT") {
	  //std::cout << obj->pt() << " :: " << obj->eta() << std::endl;
	  ++hlTriggerJetCounter;
	  if( hlTriggerJetCounter == 4 ){
	    HLTriggered = true;
	    //std::cout << "4 jets on HL" << std::endl;
	  }
	}
      }
      if(L1Triggered && HLTriggered){
	pass = true;
	//std::cout << "trigger passed" << std::endl;
	break;
      }
    }
  }
  else if(whichTrigger_ == "Jet50U"){

    for(pat::TriggerObjectCollection::const_iterator obj = triggerEvent->objects()->begin(); obj != triggerEvent->objects()->end(); ++obj){
      if( obj->hasFilterId(-84) || obj->hasFilterId(-85) ){
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

  /*
  if( quadJet40Pass && !oldPass ){
    std::cout << "Passed     NEW but NOT OLD" << std::endl;
    std::cout << "   Pt   ::   eta   ::  phi" << std::endl;
    for(pat::TriggerObjectCollection::const_iterator obj = triggerEvent->objects()->begin(); obj != triggerEvent->objects()->end(); ++obj){
      if( obj->hasFilterId(85) ){
	std::cout << obj->pt() << " :: " << obj->eta() << " :: " << obj->phi()  << " :: " << obj->collection() << std::endl;
	//std::cout << obj->pdgId() << " :: " << obj->isJet()  << " :: " << obj->mass() << " :: " << obj->overlap(*triggerEvent->objects()->begin()) << std::endl;
	//std::cout << obj->numberOfMothers() << " :: " << obj->numberOfDaughters() << " :: " << obj->collection() << std::endl;

	for(std::vector< int >::const_iterator filt = obj->filterIds().begin(); filt != obj->filterIds().end(); ++filt){
	  std::cout << *filt << std::endl;
	}
      }
    }
  }
  if( !quadJet40Pass && oldPass ){
    std::cout << "Passed NOT NEW but     OLD" << std::endl;
  }
  */
  /*
  if(pass){
    std::cout << "-------------------" << std::endl;
    std::cout << "pt 1: " << objects[0]->pt() << std::endl;
    std::cout << "pt 2: " << objects[1]->pt() << std::endl;
    std::cout << "pt 3: " << objects[2]->pt() << std::endl;
    std::cout << "pt 4: " << objects[3]->pt() << std::endl;
  }
  */

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
