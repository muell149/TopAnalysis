#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "DataFormats/Common/interface/Association.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/RefToBaseVector.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

/// default constructor
TagAndProbeAnalyzer::TagAndProbeAnalyzer(const edm::ParameterSet& cfg):
  probes_( cfg.getParameter<edm::InputTag>("probes") ),
  tests_( cfg.getParameter<edm::InputTag>("tests") ),
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
  // get probe collection
  edm::Handle<edm::View<reco::Candidate> > probes;
  evt.getByLabel(probes_, probes);
  // get test collection
  edm::Handle<edm::View<reco::Candidate> > tests;
  evt.getByLabel(tests_, tests);
  // get jet collection
  edm::Handle<edm::View<reco::Candidate> > jets;
  evt.getByLabel(jets_, jets);
  
  for(edm::View<reco::Candidate>::const_iterator probe=probes->begin(); probe!=probes->end(); ++probe){
    const pat::Muon* probeMuon = dynamic_cast<const pat::Muon*>(&*probe); 
    hists_.find("probePt"   )->second->Fill( probe->pt () );
    hists_.find("probeEta"  )->second->Fill( probe->eta() );
    hists_.find("probePhi"  )->second->Fill( probe->phi() );
    hists_.find("probeMult" )->second->Fill( jets->size() );
    hists_.find("probeMinDR")->second->Fill( minDR(jets->begin(), jets->end(), probe) );

    for(edm::View<reco::Candidate>::const_iterator test=tests->begin(); test!=tests->end(); ++test){
      const pat::Muon* testMuon = dynamic_cast<const pat::Muon*>(&*test);
      if(testMuon->originalObjectRef()==probeMuon->originalObjectRef()){
	hists_.find("testPt"   )->second->Fill( test->pt ()  );
	hists_.find("testEta"  )->second->Fill( test->eta()  );
	hists_.find("testPhi"  )->second->Fill( test->phi()  );
	hists_.find("testMult" )->second->Fill( jets->size() );
	hists_.find("testMinDR")->second->Fill(  minDR(jets->begin(), jets->end(), test) );  
	// stop iterating once the 
	// probe candidate is found
	break;
      } 
    }
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
  /*
    
  booking of tag and probe histograms
  
  */  
  hists_["probePt"   ] = fs->make<TH1F>( "probePt"    , "probePt"    ,  50,   0.,  150. );
  hists_["probeEta"  ] = fs->make<TH1F>( "probeEta"   , "probeEta"   ,  50,  -5.,    5. );
  hists_["probePhi"  ] = fs->make<TH1F>( "probePhi"   , "probePhi"   ,  50,-3.14,  3.14 );
  hists_["probeMult" ] = fs->make<TH1F>( "probeMult"  , "probeMult"  ,  10,   0.,   10. );
  hists_["probeMinDR"] = fs->make<TH1F>( "probeMinDR" , "probeMinDR" ,  50,   0.,   10. );
  hists_["testPt"    ] = fs->make<TH1F>( "testPt"     , "testPt"     ,  50,   0.,  150. );
  hists_["testEta"   ] = fs->make<TH1F>( "testEta"    , "testEta"    ,  50,  -5.,    5. );
  hists_["testPhi"   ] = fs->make<TH1F>( "testPhi"    , "testPhi"    ,  50,-3.14,  3.14 );
  hists_["testMult"  ] = fs->make<TH1F>( "testMult"   , "testMult"   ,  10,   0.,   10. );
  hists_["testMinDR" ] = fs->make<TH1F>( "testMinDR"  , "testMinDR"  ,  50,   0.,   10. );
}

/// ...
void 
TagAndProbeAnalyzer::endJob() 
{
}

//define plugin
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TagAndProbeAnalyzer);
