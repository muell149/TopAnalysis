#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"

/// default constructor
TagAndProbeAnalyzer::TagAndProbeAnalyzer(const edm::ParameterSet& cfg):
  muons_( cfg.getParameter<edm::InputTag>("muons") )
{ 
}

/// default destructor
TagAndProbeAnalyzer::~TagAndProbeAnalyzer()
{
}

/// ...
void 
TagAndProbeAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<edm::View<pat::Muon> > muons;
  evt.getByLabel(muons_, muons);

  //edm::Handle<edm::View<pat::Jet> > jets;
  //evt.getByLabel(jets_, jets);
  //...


  // only as an example
  for(edm::View<pat::Muon>::const_iterator muon=muons->begin(); muon!=muons->end(); ++muon){
    pt->Fill(muon->pt());
  }
}

/// ...
void 
TagAndProbeAnalyzer::beginJob()
{
  // laod TFile Service
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }

 /**
     tag and probe histograms
  **/
  
  // pt of the tag/probe objects
  pt = fs->make<TH1F>( "pt", "pt", 50, 0., 150.);
  // ...
}

/// ...
void 
TagAndProbeAnalyzer::endJob() 
{
}

//define plugin
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TagAndProbeAnalyzer);
