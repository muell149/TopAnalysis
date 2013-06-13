#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

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
  vertices_   (cfg.getParameter<edm::InputTag>( "vertices" )),
  tags_( cfg.getParameter<edm::InputTag>("tags") ),
  probes_( cfg.getParameter<edm::InputTag>("probes") ),
  tests_( cfg.getParameter<edm::InputTag>("tests") ),
  jets_( cfg.getParameter<edm::InputTag>("jets") ),
  mass_  ( cfg.getParameter< double >( "mass"   ) ),
  deltaM_( cfg.getParameter< double >( "deltaM" ) ),
  ptCut_( cfg.getParameter<double>("ptCut") ),
  etaCut_( cfg.getParameter<double>("etaCut") ),
  //varBins_(cfg.getParameter<bool>("varBins")),
  nBinsPt_(cfg.getParameter<int>("nBinsPt")),
  nBinsEta_(cfg.getParameter<int>("nBinsEta")),
  nBinsPhi_(cfg.getParameter<int>("nBinsPhi")),
  nBinsMult_(cfg.getParameter<int>("nBinsMult")),
  nBinsRelIso_(cfg.getParameter<int>("nBinsRelIso")),
  nBinsAbsIso_(cfg.getParameter<int>("nBinsAbsIso")),
  nBinsMinDR_(cfg.getParameter<int>("nBinsMinDR")),
  nBinsLepMult_(cfg.getParameter<int>("nBinsLepMult")),
  nBinsPVMult_(cfg.getParameter<int>("nBinsPVMult")),
  binsPt_(cfg.getParameter<std::vector<double> >("binsPt")),
  binsEta_(cfg.getParameter<std::vector<double> >("binsEta")),
  binsPhi_(cfg.getParameter<std::vector<double> >("binsPhi")),
  binsMult_(cfg.getParameter<std::vector<double> >("binsMult")),
  binsRelIso_(cfg.getParameter<std::vector<double> >("binsRelIso")),
  binsAbsIso_(cfg.getParameter<std::vector<double> >("binsAbsIso")),
  binsMinDR_(cfg.getParameter<std::vector<double> >("binsMinDR")),
  binsLepMult_(cfg.getParameter<std::vector<double> >("binsLepMult")),
  binsPVMult_(cfg.getParameter<std::vector<double> >("binsPVMult")),
  pfRelIso_( cfg.getParameter<bool>("pfRelIso") ),
  noWeightHisto_( cfg.getParameter<bool>("noWeightHisto") )
{
//  std::cout << "I'm in the contructor now!!!"  << std::endl;
//  std::cout << "tests  value is : " << tests_  << std::endl;
//  std::cout << "probes value is : " << probes_ << std::endl;
//  probes_ = cfg.getParameter<edm::InputTag>("probes");
//  std::cout << "probes value is now : " << probes_ << std::endl << std::endl;
  
// weight is an optional parameter; if not present 
// in the module the used weight will be 1.
//   if(cfg.exists("weight" )) weight_= cfg.getParameter<edm::InputTag>("weight" );
  if(cfg.exists("weightTags" )) weightTags_= cfg.getParameter< std::vector<edm::InputTag> >("weightTags" );


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

  // get vertex collection
  edm::Handle<std::vector<reco::Vertex> > vertices;
  evt.getByLabel(vertices_, vertices);


  // get tag collection
  edm::Handle<edm::View<reco::Candidate> > tags;
  evt.getByLabel(tags_, tags);
  // get probe collection
  edm::Handle<edm::View<reco::Candidate> > probes;
  evt.getByLabel(probes_, probes);
  // get test collection
  edm::Handle<edm::View<reco::Candidate> > tests;
  evt.getByLabel(tests_, tests);
  // get jet collection
  edm::Handle<edm::View<reco::Candidate> > jets;
  evt.getByLabel(jets_, jets);
  
  // prepare the event weights
  double weight = 1;
  std::vector<double> weights;
  // get weight from the CMSSW event
  // loop over all eventWeightTags and multiply weights
    for(unsigned iWeight=0; iWeight < weightTags_.size(); iWeight++){
    // get weight from the CMSSW event
      edm::Handle<double> wgt;
      evt.getByLabel(weightTags_[iWeight], wgt);
    // ignore non existing weights
      if(wgt.isValid()){
	//std::cout<<"  eventWeight "<<iWeight<<" "<< weightTags_[iWeight].label() << weightTags_[iWeight].instance() <<": "<<*wgt<<std::endl;
	weights.push_back(*wgt);
      }
      else{
	std::cout<< "eventWeight " << iWeight << " not found"<<std::endl;
	edm::LogInfo("weightNotFound") << "eventWeight " << iWeight << " not found";
      }
    }
  // use first weight in list for histos
  if(weights.size()>0) weight = weights[0];

  //std::cout << "probes size: " << probes->size() << std::endl;
  //std::cout << "tests  size: " << tests ->size() << std::endl;
  hists_.find("probeLepMult")->second->Fill(probes->size(), weight);
  hists_.find("testLepMult")->second->Fill(tests->size(), weight );

  for(edm::View<reco::Candidate>::const_iterator probe=probes->begin(); probe!=probes->end(); ++probe){
    const pat::Muon*     probeMuon = dynamic_cast<const pat::Muon*>(&*probe);
    const pat::Electron* probeElec = dynamic_cast<const pat::Electron*>(&*probe);
    //     if(probeMuon) std::cout<<"probeMuon identified"<<std::endl;
    //     else std::cout<<"NO probeMuon identified"<<std::endl;
    //     if(probeElec) std::cout<<"probeElec identified"<<std::endl;
    //     else std::cout<<"NO probeElec identified"<<std::endl;
    double relIso = -1., absIso = -1.;
    if(probeMuon){
      if(pfRelIso_){
	relIso = (probeMuon->chargedHadronIso() + 
	    TMath::Max((probeMuon->neutralHadronIso() + probeMuon->photonIso() - 0.5*probeMuon->puChargedHadronIso()),0.0)
		) / probeMuon->pt();
	absIso = probeMuon->chargedHadronIso() + 
	    TMath::Max((probeMuon->neutralHadronIso() + probeMuon->photonIso() - 0.5*probeMuon->puChargedHadronIso()),0.0);
      }
      else{
	relIso = (probeMuon->trackIso() + probeMuon->caloIso()) / probeMuon->pt();
	absIso = probeMuon->trackIso() + probeMuon->caloIso();
      }
    }
    if(probeElec){
      if(pfRelIso_){
	relIso = (probeElec->chargedHadronIso() + 
	    TMath::Max((probeElec->neutralHadronIso() + probeElec->photonIso() - 0.5*probeElec->puChargedHadronIso()),0.0)
		 ) / probeElec->pt();
	absIso = probeElec->chargedHadronIso() + 
	    TMath::Max((probeElec->neutralHadronIso() + probeElec->photonIso() - 0.5*probeElec->puChargedHadronIso()),0.0);
      }
      else{
        relIso = (probeElec->dr03TkSumPt() + probeElec->dr03EcalRecHitSumEt()
	                       + probeElec->dr03HcalTowerSumEt() ) / probeElec->et();
	absIso = probeElec->dr03TkSumPt() + probeElec->dr03EcalRecHitSumEt()
	    + probeElec->dr03HcalTowerSumEt();
      }
    }
    
    
    
    // trees and hist2D without pt and eta cut
    // initialize tree
    initializeTrees(-9999.);
    fillTree("run", (int)evt.id().run());
    // weight
    for(unsigned int iWeight=0; iWeight < weightTags_.size(); iWeight++){
      TString weightName = weightTags_[iWeight].label()+weightTags_[iWeight].instance();
      if(weightTags_.size() == weights.size()) fillTree(weightName, weights[iWeight]);
      else std::cout<< "ERROR!!! Size of weights ("<<weights.size()<<") != size of weight tags ("<<weightTags_.size()<<")!!! No weights are filled in tree!" <<std::endl;
    }
    fillTree("probeControl", 1 );
    fillTree("probePt"   , probe->pt () );
    fillTree("probeEta"  , probe->eta() );
    fillTree("probePhi"  , probe->phi() );
    fillTree("probeMult" , (int)jets->size());
    fillTree("probeRelIso" , relIso);
    fillTree("probeAbsIso" , absIso);
    fillTree("probeMinDR",  minDR(jets->begin(), jets->end(), probe));
    fillTree("probePVMult", (int) vertices->size());
    fillTree("probeCharge" , probe->charge());
    // check if probe muon is also test muon, i.e. if it passes the selection
    int testIsProbe = 0;
    for(edm::View<reco::Candidate>::const_iterator test=tests->begin(); test!=tests->end(); ++test){
      const pat::Muon*     testMuon = dynamic_cast<const pat::Muon*>(&*test);
      const pat::Electron* testElec = dynamic_cast<const pat::Electron*>(&*test);
      // check if test==probe
      if(probeMuon && testMuon && testMuon->originalObjectRef()==probeMuon->originalObjectRef()) testIsProbe=1;
      if(probeElec && testElec && testElec->originalObjectRef()==probeElec->originalObjectRef()) testIsProbe=1;
      // stop iterating once the probe candidate is found
      if(testIsProbe) break;
    }
    fillTree("pass"   , testIsProbe );
    //std::cout<<"testIsProbe="<<testIsProbe<<std::endl;
    // find the corresponding tag muon and the invariant tag-probe dimuon mass
    for(edm::View<reco::Candidate>::const_iterator tag=tags->begin(); tag!=tags->end(); ++tag){
      const pat::Muon*     tagMuon = dynamic_cast<const pat::Muon*>(&*tag);
      const pat::Electron* tagElec = dynamic_cast<const pat::Electron*>(&*tag);
      // check if tag!=probe
      bool tagIsNotProbe = false;
      if(probeMuon && tagMuon && tagMuon->originalObjectRef()!=probeMuon->originalObjectRef()) tagIsNotProbe=true;
      if(probeElec && tagElec && tagElec->originalObjectRef()!=probeElec->originalObjectRef()) tagIsNotProbe=true;
      if(tagIsNotProbe){
	double diLeptonMass = (tag->p4()+probe->p4()).mass();
	fillTree("lepLepMass"   , diLeptonMass );
	// check if in Z mass window and of opposite charge
	if( fabs(diLeptonMass - mass_)<deltaM_ && (tag->charge()*probe->charge())<0){
	  fillTree("tagPt"   , tag->pt() );
	  fillTree("tagEta"  , tag->eta() );
	  // calculate tagRelIso
	  double tagRelIso=-1.;
	  if(probeMuon){
	    if(pfRelIso_) tagRelIso = (tagMuon->chargedHadronIso() + 
		TMath::Max((tagMuon->neutralHadronIso() + tagMuon->photonIso() - 0.5*tagMuon->puChargedHadronIso()),0.0)
			) / tagMuon->pt();
	    else tagRelIso = (tagMuon->trackIso() + tagMuon->caloIso()) / tagMuon->pt();
	  }
	  if(tagElec){
	    if(pfRelIso_) tagRelIso = (tagElec->chargedHadronIso() + 
		TMath::Max((tagElec->neutralHadronIso() + tagElec->photonIso() - 0.5*tagElec->puChargedHadronIso()),0.0)
			) / tagElec->pt();
	    else tagRelIso = (tagElec->dr03TkSumPt() + tagElec->dr03EcalRecHitSumEt()
		  + tagElec->dr03HcalTowerSumEt() ) / tagElec->et();
	  }
	  fillTree("tagRelIso"   , tagRelIso );
	}
	else std::cout<<"WARNING!!! Tag-Probe muon pair not in resonance window or of same charge!!!"<<std::endl;
	// stop iterating once the probeTag pair is found
	break;
      }
    }
    // fill the tree, if any variable should be put in
    if(treeVarsFloat_.size() || treeVarsInt_.size()) tree->Fill();
    
    // set weight to 1 for histo filling if desired
    if(noWeightHisto_) weight=1.;
    hists2D_.find("probeEtaPt"  )->second->Fill( probe->eta(), probe->pt(), weight );
    // histos with pt and eta cuts
    if(fabs(probe->eta())<etaCut_) fillHisto("probePt", probe->pt (), weight );
    if(probe->pt()>ptCut_)         fillHisto("probeEta", probe->eta(), weight );
    if(probe->pt()>ptCut_ && fabs(probe->eta())<etaCut_) {
                                   fillHisto("probePhi", probe->phi(), weight );
				   fillHisto("probeMult", jets->size(), weight );
				   fillHisto("probeRelIso", relIso, weight );
				   fillHisto("probeAbsIso", absIso, weight );
				   fillHisto("probeMinDR", minDR(jets->begin(), jets->end(), probe), weight );
				   fillHisto("probePVMult", vertices->size(), weight );
				   hists_.find     ("probeControl" )->second->Fill(1, weight);
    }
  }

    for(edm::View<reco::Candidate>::const_iterator test=tests->begin(); test!=tests->end(); ++test){
      const pat::Muon*     testMuon = dynamic_cast<const pat::Muon*>(&*test);
      const pat::Electron* testElec = dynamic_cast<const pat::Electron*>(&*test);
      double relIso = -1., absIso = -1.;
      if(testMuon){
	if(pfRelIso_){
	   relIso = (testMuon->chargedHadronIso() + 
	       TMath::Max((testMuon->neutralHadronIso() + testMuon->photonIso() - 0.5*testMuon->puChargedHadronIso()),0.0)
		    ) / testMuon->pt();
	   absIso = testMuon->chargedHadronIso() + 
	       TMath::Max((testMuon->neutralHadronIso() + testMuon->photonIso() - 0.5*testMuon->puChargedHadronIso()),0.0);
	}
	else{
	   relIso = (testMuon->trackIso() + testMuon->caloIso()) / testMuon->pt();
	   absIso = testMuon->trackIso() + testMuon->caloIso();
	}
      }
      if(testElec){
	if(pfRelIso_){
	   relIso = (testElec->chargedHadronIso() + 
	       TMath::Max((testElec->neutralHadronIso() + testElec->photonIso() - 0.5*testElec->puChargedHadronIso()),0.0)
		    ) / testElec->pt();
	   absIso = testElec->chargedHadronIso() + 
	       TMath::Max((testElec->neutralHadronIso() + testElec->photonIso() - 0.5*testElec->puChargedHadronIso()),0.0);
	}
	else{
	  relIso = (testElec->dr03TkSumPt() + testElec->dr03EcalRecHitSumEt()
	                        + testElec->dr03HcalTowerSumEt() ) / testElec->et();
	  absIso = testElec->dr03TkSumPt() + testElec->dr03EcalRecHitSumEt()
	      + testElec->dr03HcalTowerSumEt();
	}
      }
	// set weight to 1 for histo filling if desired
	if(noWeightHisto_) weight=1.;
	hists2D_.find("testEtaPt"  )->second->Fill( test->eta(), test->pt(), weight );
	// histos with pt and eta cuts
	hists2D_.find("testEtaPt"  )->second->Fill( test->eta(), test->pt(), weight );
	if(fabs(test->eta())<etaCut_) fillHisto("testPt"   , test->pt (), weight  );
	if(test->pt()>ptCut_)         fillHisto("testEta"  , test->eta(), weight  );
	if(test->pt()>ptCut_ && fabs(test->eta())<etaCut_) {
                                       fillHisto("testPhi"  , test->phi(), weight  );
				       fillHisto("testMult" , jets->size(), weight );
				       fillHisto("testRelIso" , relIso, weight );
				       fillHisto("testAbsIso" , absIso, weight );
				       fillHisto("testMinDR",  minDR(jets->begin(), jets->end(), test), weight );
				       fillHisto("testPVMult", vertices->size(), weight );
				       hists_.find     ("testControl"   )->second->Fill(1, weight);
         } 
    }
  
  // calculate efficiency histos by test/probe, including binomial errors
  hists_.find("effControl"   )->second->Divide(hists_.find("testControl")->second, hists_.find("probeControl")->second,1,1,"B");
  hists_.find("effPt"   )->second->Divide(hists_.find("testPt")->second, hists_.find("probePt")->second,1,1,"B");
  hists_.find("effEta"  )->second->Divide(hists_.find("testEta")->second, hists_.find("probeEta")->second,1,1,"B");
  hists_.find("effPhi"  )->second->Divide(hists_.find("testPhi")->second, hists_.find("probePhi")->second,1,1,"B");
  hists_.find("effMult" )->second->Divide(hists_.find("testMult")->second, hists_.find("probeMult" )->second,1,1,"B");
  hists_.find("effRelIso" )->second->Divide(hists_.find("testRelIso")->second, hists_.find("probeRelIso" )->second,1,1,"B");
  hists_.find("effAbsIso" )->second->Divide(hists_.find("testAbsIso")->second, hists_.find("probeAbsIso" )->second,1,1,"B");
  hists_.find("effMinDR")->second->Divide(hists_.find("testMinDR")->second, hists_.find("probeMinDR" )->second,1,1,"B");
  hists_.find("effLepMult" )->second->Divide(hists_.find("testLepMult")->second, hists_.find("probeLepMult" )->second,1,1,"B");
  hists_.find("effPVMult" )->second->Divide(hists_.find("testPVMult")->second, hists_.find("probePVMult" )->second,1,1,"B");
  hists2D_.find("effEtaPt"  )->second->Divide(hists2D_.find("testEtaPt")->second, hists2D_.find("probeEtaPt")->second,1,1,"B");

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
  
  /// booking of tree
  tree = fs->make<TTree>("tree","tree",0);
  bookTree("run","/I");
  // weights: use variable name like weight tags label+instance
  for(unsigned iWeight=0; iWeight < weightTags_.size(); iWeight++){
    TString weightName = weightTags_[iWeight].label()+weightTags_[iWeight].instance();
    bookTree(weightName);
  }
  bookTree("probeControl", "/I");
  bookTree("probePt");
  bookTree("probeEta");
  bookTree("probePhi");
  bookTree("probeRelIso");
  bookTree("probeAbsIso");
  bookTree("probeMult", "/I");
  bookTree("probePVMult", "/I");
  bookTree("probeMinDR");
  bookTree("probeCharge", "/I");
  bookTree("pass","/I");
  bookTree("lepLepMass");
  bookTree("tagPt");
  bookTree("tagEta");
  bookTree("tagRelIso"); 
  
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
 else std::cout<<"Unable to book AbsIso histogram. Bins not well-defined."<<std::endl;
  /// AbsIso (jet multiplicity)
 /// variable binning
 if(nBinsAbsIso_==-1) {
   hists_["probeAbsIso"    ] = fs->make<TH1F>( "probeAbsIso"    , "probeAbsIso"    ,  binsAbsIso_.size()-1,     &binsAbsIso_[0] );
   hists_["testAbsIso"     ] = fs->make<TH1F>( "testAbsIso"     , "testAbsIso"     ,  binsAbsIso_.size()-1,     &binsAbsIso_[0] );
   hists_["effAbsIso"      ] = fs->make<TH1F>( "effAbsIso"      , "effAbsIso"      ,  binsAbsIso_.size()-1,     &binsAbsIso_[0] );
  
 }
 /// fixed binning
 else if (nBinsAbsIso_>0 && binsAbsIso_.size()==2) {
   hists_["probeAbsIso"    ] = fs->make<TH1F>( "probeAbsIso"    , "probeAbsIso"    ,  nBinsAbsIso_,    binsAbsIso_.at(0), binsAbsIso_.at(1) );
   hists_["testAbsIso"     ] = fs->make<TH1F>( "testAbsIso"     , "testAbsIso"     ,  nBinsAbsIso_,    binsAbsIso_.at(0), binsAbsIso_.at(1) );
   hists_["effAbsIso"      ] = fs->make<TH1F>( "effAbsIso"      , "effAbsIso"      ,  nBinsAbsIso_,    binsAbsIso_.at(0), binsAbsIso_.at(1) );
 }
 else std::cout<<"Unable to book AbsIso histogram. Bins not well-defined."<<std::endl;
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
  /// PVMult
 /// variable binning
 if(nBinsPVMult_==-1) {
   hists_["probePVMult"    ] = fs->make<TH1F>( "probePVMult"    , "probePVMult"    ,  binsPVMult_.size()-1,     &binsPVMult_[0] );
   hists_["testPVMult"     ] = fs->make<TH1F>( "testPVMult"     , "testPVMult"     ,  binsPVMult_.size()-1,     &binsPVMult_[0] );
   hists_["effPVMult"      ] = fs->make<TH1F>( "effPVMult"      , "effPVMult"      ,  binsPVMult_.size()-1,     &binsPVMult_[0] );
 }
 /// fixed binning
 else if (nBinsPVMult_>0 && binsPVMult_.size()==2) {
   hists_["probePVMult"    ] = fs->make<TH1F>( "probePVMult"    , "probePVMult"    ,  nBinsPVMult_,    binsPVMult_.at(0), binsPVMult_.at(1) );
   hists_["testPVMult"     ] = fs->make<TH1F>( "testPVMult"     , "testPVMult"     ,  nBinsPVMult_,    binsPVMult_.at(0), binsPVMult_.at(1) );
   hists_["effPVMult"      ] = fs->make<TH1F>( "effPVMult"      , "effPVMult"      ,  nBinsPVMult_,    binsPVMult_.at(0), binsPVMult_.at(1) );
 }
 else std::cout<<"Unable to book PVMult histogram. Bins not well-defined."<<std::endl;
  /// EtaPt 2D
 /// variable binning
 if(nBinsEta_==-1 && nBinsPt_==-1) {
   hists2D_["probeEtaPt"    ] = fs->make<TH2F>( "probeEtaPt"    , "probeEtaPt"    ,  binsEta_.size()-1,     &binsEta_[0],  binsPt_.size()-1,     &binsPt_[0] );
   hists2D_["testEtaPt"     ] = fs->make<TH2F>( "testEtaPt"     , "testEtaPt"     ,  binsEta_.size()-1,     &binsEta_[0],  binsPt_.size()-1,     &binsPt_[0]);
   hists2D_["effEtaPt"      ] = fs->make<TH2F>( "effEtaPt"      , "effEtaPt"      ,  binsEta_.size()-1,     &binsEta_[0],  binsPt_.size()-1,     &binsPt_[0] );
 }

// set errors
  hists_["testControl"]->Sumw2(); hists_["probeControl"]->Sumw2(); hists_["effControl"]->Sumw2(); 
  hists_["testPt"]->Sumw2(); hists_["probePt"]->Sumw2(); hists_["effPt"]->Sumw2(); 
  hists_["testEta"]->Sumw2(); hists_["probeEta"]->Sumw2(); hists_["effEta"]->Sumw2(); 
  hists_["testPhi"]->Sumw2(); hists_["probePhi"]->Sumw2(); hists_["effPhi"]->Sumw2(); 
  hists_["testMult"]->Sumw2(); hists_["probeMult"]->Sumw2(); hists_["effMult"]->Sumw2();
  hists_["testRelIso"]->Sumw2(); hists_["probeRelIso"]->Sumw2(); hists_["effRelIso"]->Sumw2();  
  hists_["testMinDR"]->Sumw2(); hists_["probeMinDR"]->Sumw2(); hists_["effMinDR"]->Sumw2(); 
  hists_["testLepMult"]->Sumw2(); hists_["probeLepMult"]->Sumw2(); hists_["effLepMult"]->Sumw2();
  hists_["testPVMult"]->Sumw2(); hists_["probePVMult"]->Sumw2(); hists_["effPVMult"]->Sumw2();  
  hists2D_["testEtaPt"]->Sumw2(); hists2D_["probeEtaPt"]->Sumw2(); hists2D_["effEtaPt"]->Sumw2();
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
