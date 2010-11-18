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
  hists_["L1_pt1"] = fs->make<TH1F>( "L1_pt1", "pt1", 500, 0., 500. );
  hists_["L1_pt2"] = fs->make<TH1F>( "L1_pt2", "pt2", 500, 0., 500. );
  hists_["L1_pt3"] = fs->make<TH1F>( "L1_pt3", "pt3", 500, 0., 500. );
  hists_["L1_pt4"] = fs->make<TH1F>( "L1_pt4", "pt4", 500, 0., 500. );

  // Et's of first four L1 jets
  hists_["L1_Et1"] = fs->make<TH1F>( "L1_Et1", "Et1", 500, 0., 500. );
  hists_["L1_Et2"] = fs->make<TH1F>( "L1_Et2", "Et2", 500, 0., 500. );
  hists_["L1_Et3"] = fs->make<TH1F>( "L1_Et3", "Et3", 500, 0., 500. );
  hists_["L1_Et4"] = fs->make<TH1F>( "L1_Et4", "Et4", 500, 0., 500. );

  // pt's of first six HL jets
  hists_["HL_pt1"] = fs->make<TH1F>( "HL_pt1", "pt1", 500, 0., 500. );
  hists_["HL_pt2"] = fs->make<TH1F>( "HL_pt2", "pt2", 500, 0., 500. );
  hists_["HL_pt3"] = fs->make<TH1F>( "HL_pt3", "pt3", 500, 0., 500. );
  hists_["HL_pt4"] = fs->make<TH1F>( "HL_pt4", "pt4", 500, 0., 500. );
  hists_["HL_pt5"] = fs->make<TH1F>( "HL_pt5", "pt5", 500, 0., 500. );
  hists_["HL_pt6"] = fs->make<TH1F>( "HL_pt6", "pt6", 500, 0., 500. );

  // Et's of first six HL jets
  hists_["HL_Et1"] = fs->make<TH1F>( "HL_Et1", "Et1", 500, 0., 500. );
  hists_["HL_Et2"] = fs->make<TH1F>( "HL_Et2", "Et2", 500, 0., 500. );
  hists_["HL_Et3"] = fs->make<TH1F>( "HL_Et3", "Et3", 500, 0., 500. );
  hists_["HL_Et4"] = fs->make<TH1F>( "HL_Et4", "Et4", 500, 0., 500. );
  hists_["HL_Et5"] = fs->make<TH1F>( "HL_Et5", "Et5", 500, 0., 500. );
  hists_["HL_Et6"] = fs->make<TH1F>( "HL_Et6", "Et6", 500, 0., 500. );
}

/// analyze triggers and fill histograms
void
L1QuadJetTriggerAnalyzer::analyze(const edm::Event& event, const edm::EventSetup&)
{
  edm::Handle<pat::TriggerEvent> triggerEvent;
  event.getByLabel(patTriggerEvent_, triggerEvent);

  std::multimap<float, pat::TriggerObject> triggerObjects;
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
      triggerObjects.insert( std::pair< float , pat::TriggerObject >( obj->pt() , (*obj) ) );
    }
  }
  //std::cout << "Map Content" << std::endl;
  for(std::multimap<float, pat::TriggerObject>::const_reverse_iterator obj = triggerObjects.rbegin(); obj != triggerObjects.rend(); ++obj){
    //std::cout << obj->second.collction() << " :: " << obj->second.pt() << " :: " << obj->second.eta()  << " :: " << obj->second.phi() << std::endl;
    sortedObjects.push_back(obj->second);
  }
  for(std::vector<pat::TriggerObject>::const_iterator obj = sortedObjects.begin(); obj != sortedObjects.end(); ++obj){
    if     (obj - sortedObjects.begin() == 0) { hists_.find("L1_pt1")->second->Fill( obj->pt() ); hists_.find("L1_Et1")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 1) { hists_.find("L1_pt2")->second->Fill( obj->pt() ); hists_.find("L1_Et2")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 2) { hists_.find("L1_pt3")->second->Fill( obj->pt() ); hists_.find("L1_Et3")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 3) { hists_.find("L1_pt4")->second->Fill( obj->pt() ); hists_.find("L1_Et4")->second->Fill( obj->et() ); }
  }

  triggerObjects.clear();
  sortedObjects.clear();

  for(pat::TriggerObjectCollection::const_iterator obj = triggerEvent->objects()->begin(); obj != triggerEvent->objects()->end(); ++obj){
    if( obj->hasFilterId(85) ){
      //std::cout << obj->collection() << " :: " << obj->pt() << " :: " << obj->eta()  << " :: " << obj->phi() << std::endl;
      if(obj->collection().find("hltMCJetCorJetIcone5HF07")!=std::string::npos) triggerObjects.insert( std::pair< float , pat::TriggerObject >( obj->pt() , (*obj) ) );
    }
  }
  //std::cout << "Map Content" << std::endl;
  for(std::multimap<float, pat::TriggerObject>::const_reverse_iterator obj = triggerObjects.rbegin(); obj != triggerObjects.rend(); ++obj){
    //std::cout << obj->second.collction() << " :: " << obj->second.pt() << " :: " << obj->second.eta()  << " :: " << obj->second.phi() << std::endl;
    sortedObjects.push_back(obj->second);
  }
  for(std::vector<pat::TriggerObject>::const_iterator obj = sortedObjects.begin(); obj != sortedObjects.end(); ++obj){
    if     (obj - sortedObjects.begin() == 0) { hists_.find("HL_pt1")->second->Fill( obj->pt() ); hists_.find("HL_Et1")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 1) { hists_.find("HL_pt2")->second->Fill( obj->pt() ); hists_.find("HL_Et2")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 2) { hists_.find("HL_pt3")->second->Fill( obj->pt() ); hists_.find("HL_Et3")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 3) { hists_.find("HL_pt4")->second->Fill( obj->pt() ); hists_.find("HL_Et4")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 4) { hists_.find("HL_pt5")->second->Fill( obj->pt() ); hists_.find("HL_Et5")->second->Fill( obj->et() ); }
    else if(obj - sortedObjects.begin() == 5) { hists_.find("HL_pt6")->second->Fill( obj->pt() ); hists_.find("HL_Et6")->second->Fill( obj->et() ); }
  }

}

void
L1QuadJetTriggerAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( L1QuadJetTriggerAnalyzer );
