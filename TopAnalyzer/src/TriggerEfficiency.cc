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

  // efficiency of QuadJetXX trigger vs. pt
  hists_["effy"] = fs->make<TH1F>( "effy" , "efficiency" , 100,  0. , 100. );
 }

/// analyze triggers and fill histograms
void
TriggerEfficiency::analyze(const edm::Event& event, const edm::EventSetup&)
{
  edm::Handle<pat::TriggerEvent> triggerEvent;
  event.getByLabel(patTriggerEvent_, triggerEvent);

  if( !triggerEvent.failedToGet() ) {

    hists_.find("effy")->second->Fill(-1);

    pat::TriggerFilterRefVector filters = triggerEvent->acceptedFilters();
    for(pat::TriggerFilterRefVector::const_iterator filter = filters.begin(); filter != filters.end(); ++filter){
      if((*filter)->label() == "hlt4jet30") {

	pat::TriggerObjectRefVector objects = triggerEvent->filterObjects("hlt4jet30");
	
	if(objects.size() >= 4){
	  
	  for(int idx = 1; idx <= hists_.find("effy")->second->GetNbinsX(); ++idx){
	    
	    if(objects[3]->pt() >= idx){
	      hists_.find("effy")->second->Fill(idx);
	    }
	  }
	}
      }
    }
  }
}

void
TriggerEfficiency::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( TriggerEfficiency );
