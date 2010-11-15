#include "TopAnalysis/TopAnalyzer/interface/L1QuadJetTriggerAnalyzer.h"

#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

#include <map>

/// default constructor
L1QuadJetTriggerAnalyzer::L1QuadJetTriggerAnalyzer(const edm::ParameterSet& cfg)
{
  patTriggerEvent_ = cfg.getParameter<edm::InputTag>("patTriggerEvent");
}

/// initiate histograms
void
L1QuadJetTriggerAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  // pt's of first four L1 jets
  hists_["pt1"] = fs->make<TH1F>( "pt1", "pt1", 500, 0., 500. );
  hists_["pt2"] = fs->make<TH1F>( "pt2", "pt2", 500, 0., 500. );
  hists_["pt3"] = fs->make<TH1F>( "pt3", "pt3", 500, 0., 500. );
  hists_["pt4"] = fs->make<TH1F>( "pt4", "pt4", 500, 0., 500. );

  // Et's of first four L1 jets
  hists_["Et1"] = fs->make<TH1F>( "Et1", "Et1", 500, 0., 500. );
  hists_["Et2"] = fs->make<TH1F>( "Et2", "Et2", 500, 0., 500. );
  hists_["Et3"] = fs->make<TH1F>( "Et3", "Et3", 500, 0., 500. );
  hists_["Et4"] = fs->make<TH1F>( "Et4", "Et4", 500, 0., 500. );
 }

/// analyze triggers and fill histograms
void
L1QuadJetTriggerAnalyzer::analyze(const edm::Event& event, const edm::EventSetup&)
{
  edm::Handle<pat::TriggerEvent> triggerEvent;
  event.getByLabel(patTriggerEvent_, triggerEvent);

  std::multimap<unsigned int, pat::TriggerObject> triggerObjects;
  std::vector<pat::TriggerObject> sortedObjects;

  //pat::TriggerObjectRefVector objects = triggerEvent->filterObjects("hltL1sQuadJet15U");
  //for(pat::TriggerObjectRefVector::const_iterator obj = objects.begin(); obj != objects.end(); ++obj){
  //  std::cout << (*obj)->collection() << " :: " << (*obj)->pt() << std::endl;
  //}
  //std::cout << "-------------------------------------------------------------------------------" << std::endl;
  //pat::TriggerFilterRefVector filters = triggerEvent->acceptedFilters();
  //for(pat::TriggerFilterRefVector::const_iterator filter = filters.begin(); filter != filters.end(); ++filter){
  //  if((*filter)->label() == "hltL1sQuadJet15U") std::cout << "L1 triggered" << std::endl;
  //}
  for(pat::TriggerObjectCollection::const_iterator obj = triggerEvent->objects()->begin(); obj != triggerEvent->objects()->end(); ++obj){
    if( obj->hasFilterId(-84) || /*obj->hasFilterId(-85) ||*/ obj->hasFilterId(-86) ){
      //std::cout << obj->collection() << " :: " << obj->pt() << " :: " << obj->eta()  << " :: " << obj->phi() << std::endl;
      triggerObjects.insert( std::pair< unsigned int , pat::TriggerObject >( obj->pt() , (*obj) ) );
    }
  }
  //std::cout << "Map Content" << std::endl;
  for(std::multimap<unsigned int, pat::TriggerObject>::const_reverse_iterator obj = triggerObjects.rbegin(); obj != triggerObjects.rend(); ++obj){
    //std::cout << obj->second.collction() << " :: " << obj->second.pt() << " :: " << obj->second.eta()  << " :: " << obj->second.phi() << std::endl;
    sortedObjects.push_back(obj->second);
  }
  for(std::vector<pat::TriggerObject>::const_iterator obj = sortedObjects.begin(); obj != sortedObjects.end(); ++obj){
    if     (obj - sortedObjects.begin() == 0) { hists_.find("pt1")->second->Fill( obj->pt() ); hists_.find("Et1")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 1) { hists_.find("pt2")->second->Fill( obj->pt() ); hists_.find("Et2")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 2) { hists_.find("pt3")->second->Fill( obj->pt() ); hists_.find("Et3")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 3) { hists_.find("pt4")->second->Fill( obj->pt() ); hists_.find("Et4")->second->Fill( obj->et() ); }
  }
}

void
L1QuadJetTriggerAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( L1QuadJetTriggerAnalyzer );
