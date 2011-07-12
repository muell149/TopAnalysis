#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "DataFormats/Common/interface/Association.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/RefToBaseVector.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"


/// default constructor
TagAndProbeAnalyzer::TagAndProbeAnalyzer(const edm::ParameterSet& cfg):
  probes_( cfg.getParameter<edm::InputTag>("probes") ),
  tests_( cfg.getParameter<edm::InputTag>("tests") ),
  jets_( cfg.getParameter<edm::InputTag>("jets") ),
  ptCut_( cfg.getParameter<double>("ptCut") ),
  etaCut_( cfg.getParameter<double>("etaCut") ),
  //varBins_(cfg.getParameter<bool>("varBins")),
  nBinsPt_(cfg.getParameter<int>("nBinsPt")),
  nBinsEta_(cfg.getParameter<int>("nBinsEta")),
  nBinsPhi_(cfg.getParameter<int>("nBinsPhi")),
  nBinsMult_(cfg.getParameter<int>("nBinsMult")),
  nBinsRelIso_(cfg.getParameter<int>("nBinsRelIso")),
  nBinsMinDR_(cfg.getParameter<int>("nBinsMinDR")),
  nBinsLepMult_(cfg.getParameter<int>("nBinsLepMult")),
  binsPt_(cfg.getParameter<std::vector<double> >("binsPt")),
  binsEta_(cfg.getParameter<std::vector<double> >("binsEta")),
  binsPhi_(cfg.getParameter<std::vector<double> >("binsPhi")),
  binsMult_(cfg.getParameter<std::vector<double> >("binsMult")),
  binsRelIso_(cfg.getParameter<std::vector<double> >("binsRelIso")),
  binsMinDR_(cfg.getParameter<std::vector<double> >("binsMinDR")),
  binsLepMult_(cfg.getParameter<std::vector<double> >("binsLepMult")),
  pfRelIso_( cfg.getParameter<bool>("pfRelIso") )
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
  hists_.find("probeLepMult")->second->Fill(probes->size());
  hists_.find("testLepMult")->second->Fill(tests->size() );

  for(edm::View<reco::Candidate>::const_iterator probe=probes->begin(); probe!=probes->end(); ++probe){
    const pat::Muon*     probeMuon = dynamic_cast<const pat::Muon*>(&*probe);
    const pat::Electron* probeElec = dynamic_cast<const pat::Electron*>(&*probe);
    //     if(probeMuon) std::cout<<"probeMuon identified"<<std::endl;
    //     else std::cout<<"NO probeMuon identified"<<std::endl;
    //     if(probeElec) std::cout<<"probeElec identified"<<std::endl;
    //     else std::cout<<"NO probeElec identified"<<std::endl;
    double relIso = -1.;
    if(probeMuon){
        if(pfRelIso_) relIso = (probeMuon->chargedHadronIso() + probeMuon->neutralHadronIso() + 
                                probeMuon->photonIso()) / probeMuon->pt();
        else          relIso = (probeMuon->trackIso() + probeMuon->caloIso()) / probeMuon->pt();
    }
    if(probeElec){
        if(pfRelIso_) relIso = (probeElec->chargedHadronIso() + probeElec->neutralHadronIso() + 
	                        probeElec->photonIso()) / probeElec->pt();
        else	      relIso = (probeElec->dr03TkSumPt() + probeElec->dr03EcalRecHitSumEt()
	                       + probeElec->dr03HcalTowerSumEt() ) / probeElec->et();
    }

    if(fabs(probe->eta())<etaCut_) hists_.find("probePt"   )->second->Fill( probe->pt () );
    if(probe->pt()>ptCut_)         hists_.find("probeEta"  )->second->Fill( probe->eta() );
    if(probe->pt()>ptCut_ && fabs(probe->eta())<etaCut_) {
                                   hists_.find("probePhi"  )->second->Fill( probe->phi() );
                                   hists_.find("probeMult" )->second->Fill( jets->size() );
				   hists_.find("probeRelIso" )->second->Fill( relIso );
                                   hists_.find("probeMinDR")->second->Fill( minDR(jets->begin(), jets->end(), probe) );
                                   hists_.find("probeControl"   )->second->Fill(1);
    }

//     for(edm::View<reco::Candidate>::const_iterator test=tests->begin(); test!=tests->end(); ++test){
//       const pat::Muon*     testMuon = dynamic_cast<const pat::Muon*>(&*test);
//       const pat::Electron* testElec = dynamic_cast<const pat::Electron*>(&*test);
//       if(testMuon->originalObjectRef()==probeMuon->originalObjectRef()){
// 	if(fabs(test->eta())<etaCut_) hists_.find("testPt"   )->second->Fill( test->pt ()  );
// 	if(test->pt()>ptCut_)         hists_.find("testEta"  )->second->Fill( test->eta()  );
// 	if(test->pt()>ptCut_ && fabs(test->eta())<etaCut_) {
//                                        hists_.find("testPhi"  )->second->Fill( test->phi()  );
// 	                               hists_.find("testMult" )->second->Fill( jets->size() );
// 				       hists_.find("testRelIso" )->second->Fill( (testMuon->trackIso()+testMuon->caloIso())/testMuon->pt() );
// 	                               hists_.find("testMinDR")->second->Fill(  minDR(jets->begin(), jets->end(), test) );
// 	                               hists_.find("testControl"   )->second->Fill(1);
//          }
// 	// stop iterating once the probe candidate is found
// 	break;
//       } 
//     }
  }
  
    for(edm::View<reco::Candidate>::const_iterator test=tests->begin(); test!=tests->end(); ++test){
      const pat::Muon*     testMuon = dynamic_cast<const pat::Muon*>(&*test);
      const pat::Electron* testElec = dynamic_cast<const pat::Electron*>(&*test);
      double relIso = -1.;
      if(testMuon){
	if(pfRelIso_) relIso = (testMuon->chargedHadronIso() + testMuon->neutralHadronIso() + 
	                        testMuon->photonIso()) / testMuon->pt();
	else          relIso = (testMuon->trackIso() + testMuon->caloIso()) / testMuon->pt();
      }
      if(testElec){
	if(pfRelIso_) relIso = (testElec->chargedHadronIso() + testElec->neutralHadronIso() + 
	                        testElec->photonIso()) / testElec->pt();
	else	      relIso = (testElec->dr03TkSumPt() + testElec->dr03EcalRecHitSumEt()
	                        + testElec->dr03HcalTowerSumEt() ) / testElec->et();
      }
	if(fabs(test->eta())<etaCut_) hists_.find("testPt"   )->second->Fill( test->pt ()  );
	if(test->pt()>ptCut_)         hists_.find("testEta"  )->second->Fill( test->eta()  );
	if(test->pt()>ptCut_ && fabs(test->eta())<etaCut_) {
                                       hists_.find("testPhi"  )->second->Fill( test->phi()  );
	                               hists_.find("testMult" )->second->Fill( jets->size() );
				       hists_.find("testRelIso" )->second->Fill( relIso );
	                               hists_.find("testMinDR")->second->Fill(  minDR(jets->begin(), jets->end(), test) );
	                               hists_.find("testControl"   )->second->Fill(1);
         } 
    }
  
  
  
  // calculate efficiency histos by test/probe, including binomial errors
  hists_.find("effControl"   )->second->Divide(hists_.find("testControl")->second, hists_.find("probeControl")->second,1,1,"B");
  hists_.find("effPt"   )->second->Divide(hists_.find("testPt")->second, hists_.find("probePt")->second,1,1,"B");
  hists_.find("effEta"  )->second->Divide(hists_.find("testEta")->second, hists_.find("probeEta")->second,1,1,"B");
  hists_.find("effPhi"  )->second->Divide(hists_.find("testPhi")->second, hists_.find("probePhi")->second,1,1,"B");
  hists_.find("effMult" )->second->Divide(hists_.find("testMult")->second, hists_.find("probeMult" )->second,1,1,"B");
  hists_.find("effRelIso" )->second->Divide(hists_.find("testRelIso")->second, hists_.find("probeRelIso" )->second,1,1,"B");
  hists_.find("effMinDR")->second->Divide(hists_.find("testMinDR")->second, hists_.find("probeMinDR" )->second,1,1,"B");
  hists_.find("effLepMult" )->second->Divide(hists_.find("testLepMult")->second, hists_.find("probeLepMult" )->second,1,1,"B");
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
 /// RelIso (jet multiplicity)
 /// variable binning
 if(nBinsRelIso_==-1) {
   hists_["probeRelIso"    ] = fs->make<TH1F>( "probeRelIso"    , "probeRelIso"    ,  binsRelIso_.size()-1,     &binsRelIso_[0] );
   hists_["testRelIso"     ] = fs->make<TH1F>( "testRelIso"     , "testRelIso"     ,  binsRelIso_.size()-1,     &binsRelIso_[0] );
   hists_["effRelIso"      ] = fs->make<TH1F>( "effRelIso"      , "effRelIso"      ,  binsRelIso_.size()-1,     &binsRelIso_[0] );
  
 }
 /// fixed binning
 else if (nBinsRelIso_>0 && binsRelIso_.size()==2) {
   hists_["probeRelIso"    ] = fs->make<TH1F>( "probeRelIso"    , "probeRelIso"    ,  nBinsRelIso_,    binsRelIso_.at(0), binsRelIso_.at(1) );
   hists_["testRelIso"     ] = fs->make<TH1F>( "testRelIso"     , "testRelIso"     ,  nBinsRelIso_,    binsRelIso_.at(0), binsRelIso_.at(1) );
   hists_["effRelIso"      ] = fs->make<TH1F>( "effRelIso"      , "effRelIso"      ,  nBinsRelIso_,    binsRelIso_.at(0), binsRelIso_.at(1) );
 }
 else std::cout<<"Unable to book RelIso histogram. Bins not well-defined."<<std::endl;
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
 /// LepMult
 /// variable binning
 if(nBinsLepMult_==-1) {
  hists_["probeLepMult"    ] = fs->make<TH1F>( "probeLepMult"    , "probeLepMult"    ,  binsLepMult_.size()-1,     &binsLepMult_[0] );
  hists_["testLepMult"     ] = fs->make<TH1F>( "testLepMult"     , "testLepMult"     ,  binsLepMult_.size()-1,     &binsLepMult_[0] );
  hists_["effLepMult"      ] = fs->make<TH1F>( "effLepMult"      , "effLepMult"      ,  binsLepMult_.size()-1,     &binsLepMult_[0] );
 }
 /// fixed binning
 else if (nBinsLepMult_>0 && binsLepMult_.size()==2) {
  hists_["probeLepMult"    ] = fs->make<TH1F>( "probeLepMult"    , "probeLepMult"    ,  nBinsLepMult_,    binsLepMult_.at(0), binsLepMult_.at(1) );
  hists_["testLepMult"     ] = fs->make<TH1F>( "testLepMult"     , "testLepMult"     ,  nBinsLepMult_,    binsLepMult_.at(0), binsLepMult_.at(1) );
  hists_["effLepMult"      ] = fs->make<TH1F>( "effLepMult"      , "effLepMult"      ,  nBinsLepMult_,    binsLepMult_.at(0), binsLepMult_.at(1) );
 }
 else std::cout<<"Unable to book LepMult histogram. Bins not well-defined."<<std::endl;

// set errors
  hists_["testControl"]->Sumw2(); hists_["probeControl"]->Sumw2(); hists_["effControl"]->Sumw2(); 
  hists_["testPt"]->Sumw2(); hists_["probePt"]->Sumw2(); hists_["effPt"]->Sumw2(); 
  hists_["testEta"]->Sumw2(); hists_["probeEta"]->Sumw2(); hists_["effEta"]->Sumw2(); 
  hists_["testPhi"]->Sumw2(); hists_["probePhi"]->Sumw2(); hists_["effPhi"]->Sumw2(); 
  hists_["testMult"]->Sumw2(); hists_["probeMult"]->Sumw2(); hists_["effMult"]->Sumw2();
  hists_["testRelIso"]->Sumw2(); hists_["probeRelIso"]->Sumw2(); hists_["effRelIso"]->Sumw2();  
  hists_["testMinDR"]->Sumw2(); hists_["probeMinDR"]->Sumw2(); hists_["effMinDR"]->Sumw2(); 
  hists_["testLepMult"]->Sumw2(); hists_["probeLepMult"]->Sumw2(); hists_["effLepMult"]->Sumw2(); 
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
