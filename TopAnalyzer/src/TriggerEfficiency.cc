#include "TopAnalysis/TopAnalyzer/interface/TriggerEfficiency.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

#include "TMath.h"

/// default constructor
TriggerEfficiency::TriggerEfficiency(const edm::ParameterSet& cfg)
{
  patTriggerEvent_   = cfg.getParameter<edm::InputTag>("patTriggerEvent");
}

/// initiate histograms
void
TriggerEfficiency::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  // efficiency of HLT_QuadJetXX trigger vs. pt
  hists_["effy_hlt"] = fs->make<TH1F>( "effy_hlt" , ";p_{t} [GeV];efficiency" , 100,  0. , 100. );
  // efficiency of L1_QuadJetX trigger vs. pt
  hists_["effy_l1" ] = fs->make<TH1F>( "effy_l1"  , ";p_{t} [GeV];efficiency" , 100,  0. , 100. );
 }

/// analyze triggers and fill histograms
void
TriggerEfficiency::analyze(const edm::Event& event, const edm::EventSetup&)
{
  edm::Handle<pat::TriggerEvent> triggerEvent;
  event.getByLabel(patTriggerEvent_, triggerEvent);

  if( !triggerEvent.failedToGet() ) {

    hists_.find("effy_hlt")->second->Fill(-1);

    pat::TriggerFilterRefVector filters = triggerEvent->acceptedFilters();
    for(pat::TriggerFilterRefVector::const_iterator filter = filters.begin(); filter != filters.end(); ++filter){
      if((*filter)->label() == "hlt4jet30") {

	pat::TriggerObjectRefVector objects = triggerEvent->filterObjects("hlt4jet30");
	
	if(objects.size() >= 4){
	  
	  for(int idx = 1; idx <= hists_.find("effy")->second->GetNbinsX(); ++idx){
	    
	    if(objects[3]->pt() >= idx){
	      hists_.find("effy_hlt")->second->Fill(idx);
	    }
	  }
	}
      }
    }

    std::multimap< double, pat::TriggerObject > sortedL1Jets;
    std::vector< pat::TriggerObject > objects = (*triggerEvent->objects());
    for(std::vector< pat::TriggerObject >::const_iterator object = objects.begin(); object != objects.end(); ++object){
      if( object->hasFilterId(-84) || object->hasFilterId(-85) || object->hasFilterId(-86) ){
	sortedL1Jets.insert(std::pair< double, pat::TriggerObject >(object->pt(),(*object)));
      }
    }
    if(sortedL1Jets.size() > 3) hists_.find("effy_l1")->second->Fill((--(--(--sortedL1Jets.rbegin())))->second.pt());
    else                        hists_.find("effy_l1")->second->Fill(-1.);
  }
}

void
TriggerEfficiency::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( TriggerEfficiency );
