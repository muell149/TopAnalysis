#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Candidate/interface/Candidate.h"
//#include "DataFormats/PatCandidates/interface/Jet.h"
//#include "DataFormats/PatCandidates/interface/Muon.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"

/// default constructor
TagAndProbeAnalyzer::TagAndProbeAnalyzer(const edm::ParameterSet& cfg):
  muons_( cfg.getParameter<edm::InputTag>("muons") ),
  jets_( cfg.getParameter<edm::InputTag>("jets") )
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
  edm::Handle<edm::View<reco::Candidate> > muons;
  evt.getByLabel(muons_, muons);

  edm::Handle<edm::View<reco::Candidate> > jets;
  evt.getByLabel(jets_, jets);
  //...

  double minDR=-1;
  // only as an example
  for(edm::View<reco::Candidate>::const_iterator muon=muons->begin(); muon!=muons->end(); ++muon)
  {
    pt_ ->Fill(muon->pt ());
    eta_->Fill(muon->eta());
    phi_->Fill(muon->phi());

    for (edm::View<reco::Candidate>::const_iterator jet=jets->begin(); jet!=jets->end(); ++jet){
      double dR = deltaR(jet->eta(), jet->phi(), muon->eta(), muon->phi());
      if(minDR<0 || dR<minDR){
	minDR=dR;
      }
    } 
  }
  mult_ ->Fill(jets->size());
  minDR_->Fill(minDR);
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
  pt_  	 = fs->make<TH1F>( "pt"    , "pt"   , 50,   0.   , 150.);
  eta_ 	 = fs->make<TH1F>( "eta"   , "eta"  , 50,  -5.   , 5.  );
  phi_	 = fs->make<TH1F>( "phi"   , "phi"  , 50,  -3.14 , 3.14);
  mult_  = fs->make<TH1F>( "mult"  ,"mult"  , 10,   0.   , 10. );
  minDR_ = fs->make<TH1F>( "minDR" , "minDelRMuJet" , 50,   0. , 10.);
}

/// ...
void 
TagAndProbeAnalyzer::endJob() 
{
}

//define plugin
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TagAndProbeAnalyzer);
