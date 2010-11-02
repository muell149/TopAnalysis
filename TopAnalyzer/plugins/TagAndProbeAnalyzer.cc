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
  jets_( cfg.getParameter<edm::InputTag>("jets") ),
  ptCut_( cfg.getParameter<double>("ptCut") ),
  etaCut_( cfg.getParameter<double>("etaCut"),
  //varBins_(cfg.getParameter<bool>("varBins")),
  nBinsPt_(cfg.getParameter<int>("nBinsPt")),
  nBinsEta_(cfg.getParameter<int>("nBinsEta")),
  nBinsPhi_(cfg.getParameter<int>("nBinsPhi")),
  nBinsMult_(cfg.getParameter<int>("nBinsMult")),
  nBinsMinDR_(cfg.getParameter<int>("nBinsMinDR")),
  nBinsMuMult_(cfg.getParameter<int>("nBinsMuMult")),
  binsPt_(cfg.getParameter<std::vector<double> >("binsPt")),
  binsEta_(cfg.getParameter<std::vector<double> >("binsEta")),
  binsPhi_(cfg.getParameter<std::vector<double> >("binsPhi")),
  binsMult_(cfg.getParameter<std::vector<double> >("binsMult")),
  binsMinDR_(cfg.getParameter<std::vector<double> >("binsMinDR")),
  binsMuMult_(cfg.getParameter<std::vector<double> >("binsMuMult"))
{
//  std::cout << "I'm in the contructor now!!!"  << std::endl;
//  std::cout << "tests  value is : " << tests_  << std::endl;
//  std::cout << "probes value is : " << probes_ << std::endl;
//  probes_ = cfg.getParameter<edm::InputTag>("probes");
//  std::cout << "probes value is now : " << probes_ << std::endl << std::endl;
}

/// default destructor
TagAndProbeAnalyzer::~TagAndProbeAnalyzer()
{
}

/// ...
void 
TagAndProbeAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  evtNum_++;
  // get probe collection
  edm::Handle<edm::View<reco::Candidate> > probes;
  evt.getByLabel(probes_, probes);
  // get test collection
  edm::Handle<edm::View<reco::Candidate> > tests;
  evt.getByLabel(tests_, tests);
  // get jet collection
  edm::Handle<edm::View<reco::Candidate> > jets;
  evt.getByLabel(jets_, jets);

  //std::cout << "probes size: " << probes->size() << std::endl;
  //std::cout << "tests  size: " << tests ->size() << std::endl;
  hists_.find("probeMuMult")->second->Fill(probes->size());
  hists_.find("testMuMult")->second->Fill(tests->size() );

  for(edm::View<reco::Candidate>::const_iterator probe=probes->begin(); probe!=probes->end(); ++probe){
    const pat::Muon* probeMuon = dynamic_cast<const pat::Muon*>(&*probe);
    if(fabs(probe->eta())<etaCut_) hists_.find("probePt"   )->second->Fill( probe->pt () );
    if(probe->pt()>ptCut_)         hists_.find("probeEta"  )->second->Fill( probe->eta() );
    if(probe->pt()>ptCut_ && fabs(probe->eta())<etaCut_) {
                                   hists_.find("probePhi"  )->second->Fill( probe->phi() );
                                   hists_.find("probeMult" )->second->Fill( jets->size() );
                                   hists_.find("probeMinDR")->second->Fill( minDR(jets->begin(), jets->end(), probe) );
                                   hists_.find("probeControl"   )->second->Fill(1);
    }

    for(edm::View<reco::Candidate>::const_iterator test=tests->begin(); test!=tests->end(); ++test){
      const pat::Muon* testMuon = dynamic_cast<const pat::Muon*>(&*test);
      if(testMuon->originalObjectRef()==probeMuon->originalObjectRef()){
	if(fabs(test->eta())<etaCut_) hists_.find("testPt"   )->second->Fill( test->pt ()  );
	if(test->pt()>ptCut_)         hists_.find("testEta"  )->second->Fill( test->eta()  );
	if(test->pt()>ptCut_ && fabs(test->eta())<etaCut_) {
                                       hists_.find("testPhi"  )->second->Fill( test->phi()  );
	                               hists_.find("testMult" )->second->Fill( jets->size() );
	                               hists_.find("testMinDR")->second->Fill(  minDR(jets->begin(), jets->end(), test) );
	                               hists_.find("testControl"   )->second->Fill(1);
         }
	// stop iterating once the probe candidate is found
	break;
      } 
    }
  }
  
  // calculate efficiency histos by test/probe, including binomial errors
  hists_.find("effControl"   )->second->Divide(hists_.find("testControl")->second, hists_.find("probeControl")->second,1,1,"B");
  hists_.find("effPt"   )->second->Divide(hists_.find("testPt")->second, hists_.find("probePt")->second,1,1,"B");
  hists_.find("effEta"  )->second->Divide(hists_.find("testEta")->second, hists_.find("probeEta")->second,1,1,"B");
  hists_.find("effPhi"  )->second->Divide(hists_.find("testPhi")->second, hists_.find("probePhi")->second,1,1,"B");
  hists_.find("effMult" )->second->Divide(hists_.find("testMult")->second, hists_.find("probeMult" )->second,1,1,"B");
  hists_.find("effMinDR")->second->Divide(hists_.find("testMinDR")->second, hists_.find("probeMinDR" )->second,1,1,"B");
  hists_.find("effMuMult" )->second->Divide(hists_.find("testMuMult")->second, hists_.find("probeMuMult" )->second,1,1,"B");
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
  
  /// Control Histos for overall number, efficiency (only one bin)
  hists_["probeControl"] = fs->make<TH1F>( "probeControl", "probeControl", 1, 0, 2 );
  hists_["testControl" ] = fs->make<TH1F>( "testControl" , "testControl" , 1, 0, 2 );
  hists_["effControl"  ] = fs->make<TH1F>( "effControl"  , "effControl"  , 1, 0, 2 );
 /// Pt
 /// variable binning
 if(nBinsPt_==-1) {
  hists_["probePt"    ] = fs->make<TH1F>( "probePt"    , "probePt"    ,  binsPt_.size()-1,     &binsPt_[0] );
  hists_["testPt"     ] = fs->make<TH1F>( "testPt"     , "testPt"     ,  binsPt_.size()-1,     &binsPt_[0] );
  hists_["effPt"      ] = fs->make<TH1F>( "effPt"      , "effPt"      ,  binsPt_.size()-1,     &binsPt_[0] );
 }
 /// fixed binning
 else if (nBinsPt_>0 && binsPt_.size()==2) {
  hists_["probePt"    ] = fs->make<TH1F>( "probePt"    , "probePt"    ,  nBinsPt_,    binsPt_.at(0), binsPt_.at(1) );
  hists_["testPt"     ] = fs->make<TH1F>( "testPt"     , "testPt"     ,  nBinsPt_,    binsPt_.at(0), binsPt_.at(1) );
  hists_["effPt"      ] = fs->make<TH1F>( "effPt"      , "effPt"      ,  nBinsPt_,    binsPt_.at(0), binsPt_.at(1) );
 }
 else std::cout<<"Unable to book Pt histogram. Bins not well-defined."<<std::endl;
 /// Eta
 /// variable binning
 if(nBinsEta_==-1) {
  hists_["probeEta"    ] = fs->make<TH1F>( "probeEta"    , "probeEta"    ,  binsEta_.size()-1,     &binsEta_[0] );
  hists_["testEta"     ] = fs->make<TH1F>( "testEta"     , "testEta"     ,  binsEta_.size()-1,     &binsEta_[0] );
  hists_["effEta"      ] = fs->make<TH1F>( "effEta"      , "effEta"      ,  binsEta_.size()-1,     &binsEta_[0] );
 }
 /// fixed binning
 else if (nBinsEta_>0 && binsEta_.size()==2) {
  hists_["probeEta"    ] = fs->make<TH1F>( "probeEta"    , "probeEta"    ,  nBinsEta_,    binsEta_.at(0), binsEta_.at(1) );
  hists_["testEta"     ] = fs->make<TH1F>( "testEta"     , "testEta"     ,  nBinsEta_,    binsEta_.at(0), binsEta_.at(1) );
  hists_["effEta"      ] = fs->make<TH1F>( "effEta"      , "effEta"      ,  nBinsEta_,    binsEta_.at(0), binsEta_.at(1) );
 }
 else std::cout<<"Unable to book Eta histogram. Bins not well-defined."<<std::endl;
 /// Phi
 /// variable binning
 if(nBinsPhi_==-1) {
  hists_["probePhi"    ] = fs->make<TH1F>( "probePhi"    , "probePhi"    ,  binsPhi_.size()-1,     &binsPhi_[0] );
  hists_["testPhi"     ] = fs->make<TH1F>( "testPhi"     , "testPhi"     ,  binsPhi_.size()-1,     &binsPhi_[0] );
  hists_["effPhi"      ] = fs->make<TH1F>( "effPhi"      , "effPhi"      ,  binsPhi_.size()-1,     &binsPhi_[0] );
 }
 /// fixed binning
 else if (nBinsPhi_>0 && binsPhi_.size()==2) {
  hists_["probePhi"    ] = fs->make<TH1F>( "probePhi"    , "probePhi"    ,  nBinsPhi_,    binsPhi_.at(0), binsPhi_.at(1) );
  hists_["testPhi"     ] = fs->make<TH1F>( "testPhi"     , "testPhi"     ,  nBinsPhi_,    binsPhi_.at(0), binsPhi_.at(1) );
  hists_["effPhi"      ] = fs->make<TH1F>( "effPhi"      , "effPhi"      ,  nBinsPhi_,    binsPhi_.at(0), binsPhi_.at(1) );
 }
 else std::cout<<"Unable to book Phi histogram. Bins not well-defined."<<std::endl;
 /// Mult (jet multiplicity)
 /// variable binning
 if(nBinsMult_==-1) {
  hists_["probeMult"    ] = fs->make<TH1F>( "probeMult"    , "probeMult"    ,  binsMult_.size()-1,     &binsMult_[0] );
  hists_["testMult"     ] = fs->make<TH1F>( "testMult"     , "testMult"     ,  binsMult_.size()-1,     &binsMult_[0] );
  hists_["effMult"      ] = fs->make<TH1F>( "effMult"      , "effMult"      ,  binsMult_.size()-1,     &binsMult_[0] );
  
 }
 /// fixed binning
 else if (nBinsMult_>0 && binsMult_.size()==2) {
  hists_["probeMult"    ] = fs->make<TH1F>( "probeMult"    , "probeMult"    ,  nBinsMult_,    binsMult_.at(0), binsMult_.at(1) );
  hists_["testMult"     ] = fs->make<TH1F>( "testMult"     , "testMult"     ,  nBinsMult_,    binsMult_.at(0), binsMult_.at(1) );
  hists_["effMult"      ] = fs->make<TH1F>( "effMult"      , "effMult"      ,  nBinsMult_,    binsMult_.at(0), binsMult_.at(1) );
 }
 else std::cout<<"Unable to book Mult histogram. Bins not well-defined."<<std::endl;
 /// MinDR
 /// variable binning
 if(nBinsMinDR_==-1) {
  hists_["probeMinDR"    ] = fs->make<TH1F>( "probeMinDR"    , "probeMinDR"    ,  binsMinDR_.size()-1,     &binsMinDR_[0] );
  hists_["testMinDR"     ] = fs->make<TH1F>( "testMinDR"     , "testMinDR"     ,  binsMinDR_.size()-1,     &binsMinDR_[0] );
  hists_["effMinDR"      ] = fs->make<TH1F>( "effMinDR"      , "effMinDR"      ,  binsMinDR_.size()-1,     &binsMinDR_[0] );
 }
 /// fixed binning
 else if (nBinsMinDR_>0 && binsMinDR_.size()==2) {
  hists_["probeMinDR"    ] = fs->make<TH1F>( "probeMinDR"    , "probeMinDR"    ,  nBinsMinDR_,    binsMinDR_.at(0), binsMinDR_.at(1) );
  hists_["testMinDR"     ] = fs->make<TH1F>( "testMinDR"     , "testMinDR"     ,  nBinsMinDR_,    binsMinDR_.at(0), binsMinDR_.at(1) );
  hists_["effMinDR"      ] = fs->make<TH1F>( "effMinDR"      , "effMinDR"      ,  nBinsMinDR_,    binsMinDR_.at(0), binsMinDR_.at(1) );
 }
 else std::cout<<"Unable to book MinDR histogram. Bins not well-defined."<<std::endl;
 /// MuMult
 /// variable binning
 if(nBinsMuMult_==-1) {
  hists_["probeMuMult"    ] = fs->make<TH1F>( "probeMuMult"    , "probeMuMult"    ,  binsMuMult_.size()-1,     &binsMuMult_[0] );
  hists_["testMuMult"     ] = fs->make<TH1F>( "testMuMult"     , "testMuMult"     ,  binsMuMult_.size()-1,     &binsMuMult_[0] );
  hists_["effMuMult"      ] = fs->make<TH1F>( "effMuMult"      , "effMuMult"      ,  binsMuMult_.size()-1,     &binsMuMult_[0] );
 }
 /// fixed binning
 else if (nBinsMuMult_>0 && binsMuMult_.size()==2) {
  hists_["probeMuMult"    ] = fs->make<TH1F>( "probeMuMult"    , "probeMuMult"    ,  nBinsMuMult_,    binsMuMult_.at(0), binsMuMult_.at(1) );
  hists_["testMuMult"     ] = fs->make<TH1F>( "testMuMult"     , "testMuMult"     ,  nBinsMuMult_,    binsMuMult_.at(0), binsMuMult_.at(1) );
  hists_["effMuMult"      ] = fs->make<TH1F>( "effMuMult"      , "effMuMult"      ,  nBinsMuMult_,    binsMuMult_.at(0), binsMuMult_.at(1) );
 }
 else std::cout<<"Unable to book MuMult histogram. Bins not well-defined."<<std::endl;

// set errors
  hists_["testControl"]->Sumw2(); hists_["probeControl"]->Sumw2(); hists_["effControl"]->Sumw2(); 
  hists_["testPt"]->Sumw2(); hists_["probePt"]->Sumw2(); hists_["effPt"]->Sumw2(); 
  hists_["testEta"]->Sumw2(); hists_["probeEta"]->Sumw2(); hists_["effEta"]->Sumw2(); 
  hists_["testPhi"]->Sumw2(); hists_["probePhi"]->Sumw2(); hists_["effPhi"]->Sumw2(); 
  hists_["testMult"]->Sumw2(); hists_["probeMult"]->Sumw2(); hists_["effMult"]->Sumw2(); 
  hists_["testMinDR"]->Sumw2(); hists_["probeMinDR"]->Sumw2(); hists_["effMinDR"]->Sumw2(); 
  hists_["testMuMult"]->Sumw2(); hists_["probeMuMult"]->Sumw2(); hists_["effMuMult"]->Sumw2(); 
  std::cout<<"evtNum="<<evtNum_<<"after Sumw2"<<std::endl;


  evtNum_=0;
}

/// ...
void 
TagAndProbeAnalyzer::endJob() 
{

}

//define plugin
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TagAndProbeAnalyzer);
