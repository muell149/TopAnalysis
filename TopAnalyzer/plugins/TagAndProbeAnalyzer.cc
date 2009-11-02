#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Candidate/interface/Candidate.h"
//#include "DataFormats/PatCandidates/interface/Jet.h"
//#include "DataFormats/PatCandidates/interface/Muon.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"

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

  /** 
      histogram filling
      
      filling: for all muons of all events : pt, eta, phi 
               for all events		   : number of jets (multiplicity)
               for all muons and all jets of all events: minimum of R between jet an muon
  **/	


  /**
     fill probe histograms and find closest test candidate
  **/
  double minDRProbeTest;
  const reco::Candidate* testCandidate;
  std::vector<double> minDRProbeTests; 
  std::vector<const reco::Candidate*> testCandidates;
  double probeMinDR=-1;
  // loop probe collection
  for(edm::View<reco::Candidate>::const_iterator probe=probes->begin(); probe!=probes->end(); ++probe){
    hists_.find("probePt" )->second->Fill( probe->pt () );
    hists_.find("probeEta")->second->Fill( probe->eta() );
    hists_.find("probePhi")->second->Fill( probe->phi() );
    // find closest jet
    for(edm::View<reco::Candidate>::const_iterator jet=jets->begin(); jet!=jets->end(); ++jet){
      double dR = deltaR(jet->eta(), jet->phi(), probe->eta(), probe->phi());
      if(probeMinDR<0 || dR<probeMinDR){
	probeMinDR=dR;
      }
    }
    // find closest test candidate
    minDRProbeTest=-1;
    for(edm::View<reco::Candidate>::const_iterator test=tests->begin(); test!=tests->end(); ++test){
      double dR = deltaR(test->eta(), test->phi(), probe->eta(), probe->phi());
      if(minDRProbeTest<0 || dR<minDRProbeTest){
	minDRProbeTest=dR;
	testCandidate=&(*test);
      }
    }
    testCandidates.push_back(testCandidate);
    minDRProbeTests.push_back(minDRProbeTest);
  }
  hists_.find("probeMult" )->second->Fill( jets->size() );
  hists_.find("probeMinDR")->second->Fill( probeMinDR );

  /**
     fill test histograms
  **/
  double testMinDR=-1;
  for(unsigned int idx=0; idx<testCandidates.size() && idx<minDRProbeTests.size(); ++idx){
    if( minDRProbeTests[idx]>0 ){
      hists_.find("minDR_" )->second->Fill( minDRProbeTests[idx] );
      if( minDRProbeTests[idx]<0.1 ){
	hists_.find("testPt" )->second->Fill( testCandidates[idx]->pt () );
	hists_.find("testEta")->second->Fill( testCandidates[idx]->eta() );
	hists_.find("testPhi")->second->Fill( testCandidates[idx]->phi() );
	// find closest jet
	for(edm::View<reco::Candidate>::const_iterator jet=jets->begin(); jet!=jets->end(); ++jet){
	  double dR = deltaR(jet->eta(), jet->phi(), testCandidates[idx]->eta(), testCandidates[idx]->phi());
	  if(testMinDR<0 || dR<testMinDR){
	    testMinDR=dR;
	  }
	}
	hists_.find("testMult" )->second->Fill( jets->size() );
	hists_.find("testMinDR")->second->Fill( testMinDR );
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
  /**
     booking of tag and probe histograms
  **/  
  // probe histograms
  hists_["probePt"   ] = fs->make<TH1F>( "probePt"    , "probePt"    ,  50,   0.,  150. );
  hists_["probeEta"  ] = fs->make<TH1F>( "probeEta"   , "probeEta"   ,  50,  -5.,    5. );
  hists_["probePhi"  ] = fs->make<TH1F>( "probePhi"   , "probePhi"   ,  50,-3.14,  3.14 );
  hists_["probeMult" ] = fs->make<TH1F>( "probeMult"  , "probeMult"  ,  10,   0.,   10. );
  hists_["probeMinDR"] = fs->make<TH1F>( "probeMinDR" , "probeMinDR" ,  50,   0.,   10. );
  // test histograms
  hists_["testPt"    ] = fs->make<TH1F>( "testPt"     , "testPt"     ,  50,   0.,  150. );
  hists_["testEta"   ] = fs->make<TH1F>( "testEta"    , "testEta"    ,  50,  -5.,    5. );
  hists_["testPhi"   ] = fs->make<TH1F>( "testPhi"    , "testPhi"    ,  50,-3.14,  3.14 );
  hists_["testMult"  ] = fs->make<TH1F>( "testMult"   , "testMult"   ,  10,   0.,   10. );
  hists_["testMinDR" ] = fs->make<TH1F>( "testMinDR"  , "testMinDR"  ,  50,   0.,   10. );

  /**
     booking of monitor histograms
  **/
  // distance between probe and closest test object
  hists_["minDR_"    ] = fs->make<TH1F>( "minDR_"     , "minDR_"     ,  50,   0.,    5. );
}

/// ...
void 
TagAndProbeAnalyzer::endJob() 
{
}

//define plugin
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TagAndProbeAnalyzer);
