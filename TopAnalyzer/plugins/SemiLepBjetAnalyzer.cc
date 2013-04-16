#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"

#include "TopAnalysis/TopAnalyzer/plugins/SemiLepBjetAnalyzer.h"
#include "DataFormats/Math/interface/deltaR.h"

// default constructor
SemiLepBjetAnalyzer::SemiLepBjetAnalyzer(const edm::ParameterSet& cfg):
  semiLepEvt_(cfg.getParameter<edm::InputTag>("semiLepEvent")),
  hypoKey_   (cfg.getParameter<std::string>  ("hypoKey"     )),
  genJets_   (cfg.getParameter<edm::InputTag>("genJets"     )),
  genLeptons_(cfg.getParameter<edm::InputTag>("genLeptons"  )),
  bJetCollection_(cfg.getParameter<bool>     ("bJetCollection")),
  recoJets_  (cfg.getParameter<edm::InputTag>("recoJets"    )),
  verbose    (cfg.getParameter<int>          ("output"      )),
  weight_    (cfg.getParameter<edm::InputTag>("weight"      )),
  genPlots_  (cfg.getParameter<bool>         ("genPlots"    )),
  recPlots_  (cfg.getParameter<bool>         ("recPlots"    )),
  preBjets   (cfg.getParameter<bool>         ("useRecBjetsKinematicsBeforeFit")),
  bHadJetIdx_    (cfg.getParameter<edm::InputTag> ("BHadJetIndex"    )),
  antibHadJetIdx_(cfg.getParameter<edm::InputTag> ("AntiBHadJetIndex")),
  useClosestDrBs_(cfg.getParameter<bool>   ("useClosestDrBs")),
  useTree_   (cfg.getParameter<bool>("useTree")),
  valueBqPtRec(-999),
  valueBqPtGen(-999),
  valueLeadBqPtRec(-999),
  valueLeadBqPtGen(-999),
  valueSubLeadBqPtRec(-999),
  valueSubLeadBqPtGen(-999),
  valueBqEtaRec(-999),
  valueBqEtaGen(-999),
  valueBqYRec(-999),
  valueBqYGen(-999),
  valueBbarqPtRec(-999),
  valueBbarqPtGen(-999),
  valueBbarqEtaRec(-999),
  valueBbarqEtaGen(-999),
  valueBbarqYRec(-999),
  valueBbarqYGen(-999),
  valueBbbarPtRec(-999),
  valueBbbarPtGen(-999),
  valueBbbarEtaRec(-999),
  valueBbbarEtaGen(-999),
  valueBbbarYRec(-999),
  valueBbbarYGen(-999),
  valueBbbarMassRec(-999),
  valueBbbarMassGen(-999),
  valueLbMassRec(-999),
  valueLbMassGen(-999),
  bbSwapBetter(false),
  valueAssignment(-999)
{
}

void
SemiLepBjetAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& setup)
{

  // ---
  //     Z: Event information
  // ---
  if(useTree_){
    edm::EventAuxiliary aux = event.eventAuxiliary();
    runNumber             = aux.run();
    luminosityBlockNumber = aux.luminosityBlock();
    eventNumber           = aux.event();
  }

  // ---
  //     A: configure input
  // ---
  if(verbose>0) std::cout << "prepare inputs" << std::endl;
  if(verbose>1) std::cout << "a) event weight" << std::endl;
   // a) prepare the event weight
  weight = 1;
  // get weight from the CMSSW event
  edm::Handle<double> wgt;
  event.getByLabel(weight_, wgt);
  // ignore non existing weights
  if(wgt.isValid()) weight=*wgt;
  else{
    if(verbose>0) std::cout << "eventWeight not found" << std::endl;
    edm::LogInfo("weightNotFound") << "eventWeight not found";
  }
  if(verbose>1) std::cout << "weight=" << weight << std::endl;
  // b) get a handle for the TtSemiLepEvent 
  if(verbose>1) std::cout << "b) TtSemiLepEvent" << std::endl;
  edm::Handle<TtSemiLeptonicEvent> semiLepEvt;
  if(recPlots_) event.getByLabel(semiLepEvt_, semiLepEvt);
  // c1) get a handle for genjet collection
  if(verbose>1) std::cout << "c1) genJetCollection" << std::endl;
  // get jet collection
  edm::Handle<reco::GenJetCollection> genJets;
  if(genPlots_) event.getByLabel(genJets_, genJets);
  // c2) get a handle for reco jet collection
  if(verbose>1) std::cout << "c2) recoJetCollection" << std::endl;
  if(!recPlots_) preBjets=false;
  edm::Handle<pat::JetCollection> recoJets;
  if(recPlots_) event.getByLabel(recoJets_, recoJets);
  // d) position of the jet within genjet collection identified as b-hadron jet
  if(verbose>1) std::cout << "d) b-jet indices produced by TopAnalysis/TopUtils/GenLevelBJetProducer" << std::endl;
  int bIX   =-1;
  int bbarIX=-1;
  // e) get lepton collection
  edm::Handle<std::vector<reco::GenParticle> > genLeptons;
  if(genPlots_) event.getByLabel(genLeptons_, genLeptons);

  if(genPlots_){
    // take leading two jets assuming that collection genJets consists of b-jets only in the order 1st entry: b-jet, 2nd entry: anti-bjet
    if(bJetCollection_==true){
      bIX   =0;
      bbarIX=1;
    }
    else{
      // get indices produced by TopAnalysis/TopUtils/GenLevelBJetProducer.cc
      std::vector<int> VBHadJetIdx, VAntiBHadJetIdx;
      edm::Handle<std::vector<int> > BHadJetIndex, AntiBHadJetIndex;
      event.getByLabel(bHadJetIdx_    , BHadJetIndex    );
      event.getByLabel(antibHadJetIdx_, AntiBHadJetIndex);
      // save them in vector
      for (int i=0; i<(int) BHadJetIndex->size()    ; ++i){  VBHadJetIdx    .push_back(BHadJetIndex->at(i)    );};
      for (int i=0; i<(int) AntiBHadJetIndex->size(); ++i){  VAntiBHadJetIdx.push_back(AntiBHadJetIndex->at(i));};
      // use leading vector entries finally 
      if(VBHadJetIdx    .size()>0) bIX   =VBHadJetIdx    [0];
      if(VAntiBHadJetIdx.size()>0) bbarIX=VAntiBHadJetIdx[0];
      // output for user information
      if(verbose>1){
	std::cout << "N(b jets): "    << VBHadJetIdx    .size() << std::endl;
	for(unsigned int idx=0; idx<VBHadJetIdx    .size(); ++idx){
	  if(idx==0) std::cout << "("; 
	  std::cout << VBHadJetIdx[idx];
	  if(idx<VBHadJetIdx.size()-1) std::cout << ", ";
	  else std::cout << ")" << std::endl;
	}
	std::cout << "N(bbar jets): " << VAntiBHadJetIdx.size() << std::endl;
	for(unsigned int idx=0; idx<VAntiBHadJetIdx.size(); ++idx){
	  if(idx==0) std::cout << "("; 
	  std::cout << VAntiBHadJetIdx[idx];
	  if(idx<VAntiBHadJetIdx.size()-1) std::cout << ", ";
	  else std::cout << ")" << std::endl;
	}
      }
    }
  }
  // ---
  //     B: rec level plots
  // ---
  if(verbose>0) std::cout << std::endl << "create rec level plots" << std::endl;
  // get rec b and bbar (from kinfit hypothesis)
  const reco::Candidate* zero=0;
  std::pair<const reco::Candidate*,const reco::Candidate*> recBJets = recPlots_ ? getbJets(semiLepEvt, hypoKey_) : std::make_pair(zero,zero);
  // get rec b and bbar (assignment from kinfit hypothesis but no shifted kinematics)
  if(preBjets) recBJets = recPlots_ ? getPreBJets(semiLepEvt, hypoKey_, recoJets) : std::make_pair(zero,zero);
  const reco::Candidate* b   = recBJets.first ;
  const reco::Candidate* bbar= recBJets.second;
  double reclbm=-1;
  // fill rec histograms
  if(b&&bbar){
    reclbm=(semiLepEvt->singleLepton(hypoKey_)->p4()+semiLepEvt->leptonicDecayB(hypoKey_)->p4()).mass();
    // fill tree variables   
    if(useTree_){
      valueBqPtRec =b->pt();
      valueLeadBqPtRec    = b->pt()>bbar->pt() ? b->pt() : bbar->pt();
      valueSubLeadBqPtRec = b->pt()<bbar->pt() ? b->pt() : bbar->pt();
      valueBqEtaRec=b->eta();
      valueBqYRec  =b->rapidity(); 
      valueBbarqPtRec =bbar->pt();
      valueBbarqEtaRec=bbar->eta();
      valueBbarqYRec  =bbar->rapidity();
      valueBbbarPtRec  =(b->p4()+bbar->p4()).pt();
      valueBbbarEtaRec =(b->p4()+bbar->p4()).eta();
      valueBbbarYRec   =(b->p4()+bbar->p4()).Rapidity();
      valueBbbarMassRec=(b->p4()+bbar->p4()).mass();
      valueLbMassRec   =reclbm;
    }
    // debug output
    if(verbose>1) std::cout << "do filling" << std::endl;
    // fill plots
    bqPtRec ->Fill( b->pt()         , weight);
    bqPtRec ->Fill( bbar->pt()      , weight);
    bqPtLeadRec    ->Fill( (b->pt()>bbar->pt() ? b->pt() : bbar->pt()), weight);
    bqPtSubLeadRec ->Fill( (b->pt()<bbar->pt() ? b->pt() : bbar->pt()), weight);
    bqEtaRec->Fill( b->eta()        , weight);
    bqEtaRec->Fill( bbar->eta()     , weight);
    bqYRec  ->Fill( b->rapidity()   , weight);
    bqYRec  ->Fill( bbar->rapidity(), weight);
    bbbarPtRec  ->Fill( (b->p4()+bbar->p4()).pt()      , weight);
    bbbarEtaRec ->Fill( (b->p4()+bbar->p4()).eta()     , weight);
    bbbarYRec   ->Fill( (b->p4()+bbar->p4()).Rapidity(), weight);
    bbbarMassRec->Fill( (b->p4()+bbar->p4()).mass()    , weight);
    lbMassRec->Fill(reclbm, weight);
  }
  else if(verbose>1) std::cout << "no filling done" << std::endl;
 
  // ---
  //     C: gen level plots
  // ---
  if(verbose>0) std::cout << std::endl << "create gen level plots" << std::endl;
  // ensure there are indices for both
  if(bIX<-1||bbarIX<-1){
    if(genPlots_&&verbose>0) std::cout << "WARNING: gen bjet indices incomplete!" << std::endl;
    genPlots_=false;
  }
  // get generator level b-Jets from gen jet collection using indices from B Hadron identification procedure
  const reco::GenJet* genb    = genPlots_ ? getJetFromCollection(*genJets,bIX   ) : 0;
  const reco::GenJet* genbbar = genPlots_ ? getJetFromCollection(*genJets,bbarIX) : 0;
  const reco::GenParticle* genLepton = genPlots_ ? &genLeptons->at(0) : 0;

  double genlbm=-1;
  double genlbm2=-1;
  // fill gen histograms
  if(genb&&genbbar){
    // identify jet coming from leptonic top: 
    //   b-jet and lepton must have opposite charges!!!
    double genLepCharge=genLepton->charge();
    if(verbose>2) std::cout << "charge lept: " << genLepCharge  << std::endl;
    genlbm = (genLepCharge<0) ? (genLepton->p4()+genbbar->p4()).mass() : (genLepton->p4()+genb   ->p4()).mass();
    genlbm2= (genLepCharge<0) ? (genLepton->p4()+   genb->p4()).mass() : (genLepton->p4()+genbbar->p4()).mass();
    // fill tree variables   
    if(useTree_){
      valueBqPtGen =genb->pt();
      valueLeadBqPtGen    = genb->pt()>genbbar->pt() ? genb->pt() : genbbar->pt();
      valueSubLeadBqPtGen = genb->pt()<genbbar->pt() ? genb->pt() : genbbar->pt();
      valueBqEtaGen   =genb->eta();
      valueBqYGen     =genb->rapidity();
      valueBbarqPtGen =genbbar->pt();
      valueBbarqEtaGen=genbbar->eta();
      valueBbarqYGen  =genbbar->rapidity();
      valueBbbarPtGen  =(genb->p4()+genbbar->p4()).pt();
      valueBbbarEtaGen =(genb->p4()+genbbar->p4()).eta();
      valueBbbarYGen   =(genb->p4()+genbbar->p4()).Rapidity();
      valueBbbarMassGen=(genb->p4()+genbbar->p4()).mass();
      valueLbMassGen   =genlbm;
    }
    // debug output
    if(!recPlots_&&valueBqPtGen>0&&valueBbarqPtGen>0&&verbose>1){ 
      std::cout << "gen truth filling" << std::endl;
      std::cout << "b(pt, eta)=(" << valueBqPtGen << "." << valueBqEtaGen << ")" << std::endl;
      std::cout << "bbar(pt, eta)=(" << valueBbarqPtGen << "." << valueBbarqEtaGen << ")" << std::endl;
    }
    if(verbose>1) std::cout << "do filling" << std::endl;
    // fill plots
    bqPtGen ->Fill( genb->pt()         , weight);
    bqPtGen ->Fill( genbbar->pt()      , weight);
    bqPtLeadGen    ->Fill( (genb->pt()>genbbar->pt() ? genb->pt() : genbbar->pt()), weight);
    bqPtSubLeadGen ->Fill( (genb->pt()<genbbar->pt() ? genb->pt() : genbbar->pt()), weight);
    bqEtaGen->Fill( genb->eta()        , weight);
    bqEtaGen->Fill( genbbar->eta()     , weight);
    bqYGen  ->Fill( genb->rapidity()   , weight);
    bqYGen  ->Fill( genbbar->rapidity(), weight);
    bbbarPtGen  ->Fill( (genb->p4()+genbbar->p4()).pt()      , weight);
    bbbarEtaGen ->Fill( (genb->p4()+genbbar->p4()).eta()     , weight);
    bbbarYGen   ->Fill( (genb->p4()+genbbar->p4()).Rapidity(), weight);
    bbbarMassGen->Fill( (genb->p4()+genbbar->p4()).mass()    , weight);
    lbMassGen   ->Fill( genlbm, weight);
  }
  else if(verbose>1) std::cout << "no filling done" << std::endl;

  // ---
  //     D: gen rec correlation plots
  // ---  
  if(verbose>0) std::cout << std::endl << "correlation plots" << std::endl;
  // check if gen and reco b-jets exist in the event
  if(genb&&genbbar&&b&&bbar){
    // parton level quark vs reco jet assignment
    valueAssignment=checkPartonAssignment(semiLepEvt, 5); // FIXME: N(jets) in KinFit hardcoded for the moment
    if(verbose>1){
      std::cout << "mlb(gen correct)=" << genlbm  << std::endl;
      std::cout << "mlb(gen bb swap)=" << genlbm2 << std::endl;
      std::cout << "mlb(rec KinFit )=" << reclbm  << std::endl;
      std::cout << "reco jet assignment (kinFit) wrt reco jet-quark matching: " << valueAssignment << std::endl;
    }
    if(verbose>1) std::cout << "do filling" << std::endl;
    // fill lead b-jet and bbbar correlation histograms 
    // (those have only one entry per event and are independend of the rec-gen b-jet association)
    bqPtLead_ ->Fill((genb->pt()>genbbar->pt() ? genb->pt() : genbbar->pt()), (b->pt()>bbar->pt() ? b->pt() : bbar->pt()), weight);
    bqPtSubLead_ ->Fill((genb->pt()<genbbar->pt() ? genb->pt() : genbbar->pt()), (b->pt()<bbar->pt() ? b->pt() : bbar->pt()), weight);
    bbbarPt_  ->Fill( (genb->p4()+genbbar->p4()).pt()      , (b->p4()+bbar->p4()).pt()      , weight);
    bbbarEta_ ->Fill( (genb->p4()+genbbar->p4()).eta()     , (b->p4()+bbar->p4()).eta()     , weight);
    bbbarY_   ->Fill( (genb->p4()+genbbar->p4()).Rapidity(), (b->p4()+bbar->p4()).Rapidity(), weight);
    bbbarMass_->Fill( (genb->p4()+genbbar->p4()).mass()    , (b->p4()+bbar->p4()).mass()    , weight);
    if(reclbm>=0&&genlbm>=0) lbMass_->Fill( genlbm, reclbm, weight );
    if(verbose>1){
      std::cout << "---" << std::endl;
      std::cout << "pt: genb   = " << genb->pt()    << "; recb   = " << b->pt()    << "-- eta: genb   = " << genb->eta()    << "; recb   = " << b->eta() << std::endl;
      std::cout << "pt: genbbar= " << genbbar->pt() << "; recbbar= " << bbar->pt() << "-- eta: genbbar= " << genbbar->eta() << "; recbbar= " << bbar->eta() << std::endl;
    }
    // for plots with combined b-jet and bbar-jet measurement:
    // take into account that both values end up in the same histogram
    // -> search for best gen-reco association based on minimal dR 

    // start with gen: association from B/AntiB, reco: association from KinFit
    double bpt    =b->pt();         
    double bbarpt =bbar->pt(); 
    double beta   =b->eta();        
    double bbareta=bbar->eta(); 
    double bY     =b->rapidity();   
    double bbarY  =bbar->rapidity();
    bool swapped = false;
    bbSwapBetter = false;
    // check if dR is smaller for swopping gen-rec assignment
    if(deltaR( b->eta(), b->phi(), genb->eta(), genb->phi())+ deltaR( bbar->eta(), bbar->phi(), genbbar->eta(), genbbar->phi()) > deltaR( bbar->eta(), bbar->phi(), genb->eta(), genb->phi())+ deltaR( b->eta(), b->phi(), genbbar->eta(), genbbar->phi())){
      swapped = true;
      if(useTree_) bbSwapBetter = true;
      // use the better dR combination only if parameter useClosestDrBs_ is true
      if(useClosestDrBs_){
	bY=bbar->rapidity(); 
	bbarY=b->rapidity();
	bpt=bbar->pt(); 
	bbarpt=b->pt();
	beta=bbar->eta(); 
	bbareta=b->eta();
      }
      if(verbose>1) std::cout << "dR unswapped = " << deltaR( b->eta(), b->phi(), genb->eta(), genb->phi())+ deltaR( bbar->eta(), bbar->phi(), genbbar->eta(), genbbar->phi()) << "; dR swapped = " << deltaR( bbar->eta(), bbar->phi(), genb->eta(), genb->phi())+ deltaR( b->eta(), b->phi(), genbbar->eta(), genbbar->phi()) << std::endl;
    }
    // fill combined b-jet and bbar-jet correlation histograms 
    // (those have both b-jets as entry per event and depend on rec-gen b-jet association)
    bqPt_ ->Fill( genb->pt()         , bpt    , weight);
    bqPt_ ->Fill( genbbar->pt()      , bbarpt , weight);
    bqEta_->Fill( genb->eta()        , beta   , weight);
    bqEta_->Fill( genbbar->eta()     , bbareta, weight);
    bqY_  ->Fill( genb->rapidity()   , bY     , weight);
    bqY_  ->Fill( genbbar->rapidity(), bbarY  , weight);
    // output
    if(verbose>1){
      std::cout << "swapped: " << swapped << "; bbSwapBetter: " << bbSwapBetter << std::endl;
      std::cout << "pt: genb   = " << genb->pt()    << "; recb   = " << bpt << "-- eta: genb   = " << genb->eta()    << "; recb   = " << beta << std::endl;
      std::cout << "pt: genbbar= " << genbbar->pt() << "; recbbar= " << bbarpt << "-- eta: genbbar= " << genbbar->eta()    << "; recbbar= " << bbareta << std::endl;
    }
    if(valueBqPtGen>0&&valueBbarqPtGen>0&&verbose>1){ 
      std::cout << "XXXXXXXXXXXX correlation filling XXXXXXXXXXXXXXXXX" << std::endl;
      std::cout << "b(pt, eta)=(" << valueBqPtGen << "." << valueBqEtaGen << ")" << std::endl;
      std::cout << "bbar(pt, eta)=(" << valueBbarqPtGen << "." << valueBbarqEtaGen << ")" << std::endl;
    }
  }
  else if(verbose>1) std::cout << "no filling done" << std::endl;

  if(useTree_) tree->Fill();
}

void 
SemiLepBjetAnalyzer::beginJob()
{
  // check file service 
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  // print information
  if(verbose>0){ 
    std::cout << "running SemiLepBjetAnalyzer" << std::endl;
    std::cout << "produce gen plots? " << genPlots_ << std::endl;
    std::cout << "produce rec plots? " << recPlots_ << std::endl;
  }
  
  //---
  //   book histograms
  //---
  // 1D rec und gen
  // A) b-quark quantities
  // pt
  if(recPlots_) bqPtRec  = fs->make<TH1F>("bqPtRec" , "p_{t}^{b and #bar{b}} (rec) [GeV]", 1200, 0., 1200.);
  if(genPlots_) bqPtGen  = fs->make<TH1F>("bqPtGen" , "p_{t}^{b and #bar{b}} (gen) [GeV]", 1200, 0., 1200.);
  if(recPlots_) bqPtLeadRec  = fs->make<TH1F>("bqPtLeadRec" , "p_{t}^{lead b} (rec) [GeV]", 1200, 0., 1200.);
  if(genPlots_) bqPtLeadGen  = fs->make<TH1F>("bqPtLeadGen" , "p_{t}^{lead b} (gen) [GeV]", 1200, 0., 1200.);
  if(recPlots_) bqPtSubLeadRec  = fs->make<TH1F>("bqPtSubLeadRec" , "p_{t}^{sublead b} (rec) [GeV]", 1200, 0., 1200.);
  if(genPlots_) bqPtSubLeadGen  = fs->make<TH1F>("bqPtSubLeadGen" , "p_{t}^{sublead b} (gen) [GeV]", 1200, 0., 1200.);
  // eta
  if(recPlots_) bqEtaRec = fs->make<TH1F>("bqEtaRec", "#eta^{b and #bar{b}} (rec)"       , 100, -5., 5.);
  if(genPlots_) bqEtaGen = fs->make<TH1F>("bqEtaGen", "#eta^{b and #bar{b}} (gen)"       , 100, -5., 5.);
  // rapidity
  if(recPlots_) bqYRec   = fs->make<TH1F>("bqYRec"  , "y^{b and #bar{b}} (rec)"          , 100, -5., 5.);
  if(genPlots_) bqYGen   = fs->make<TH1F>("bqYGen"  , "y^{b and #bar{b}} (gen)"          , 100, -5., 5.);
  // B) bbbar-system quantities
  // pt
  if(recPlots_) bbbarPtRec  = fs->make<TH1F>("bbbarPtRec"   , "p_{t}^{b#bar{b}} (rec) [GeV]", 1200,  0., 1200.);
  if(genPlots_) bbbarPtGen  = fs->make<TH1F>("bbbarPtGen"   , "p_{t}^{b#bar{b}} (gen) [GeV]", 1200,  0., 1200.);
  // eta
  if(recPlots_) bbbarEtaRec = fs->make<TH1F>("bbbarEtaRec"  , "#eta^{b#bar{b}} (rec)"       ,  100, -5.,    5.);
  if(genPlots_) bbbarEtaGen = fs->make<TH1F>("bbbarEtaGen"  , "#eta^{b#bar{b}} (gen)"       ,  100, -5.,    5.);
  // rapidity
  if(recPlots_) bbbarYRec   = fs->make<TH1F>("bbbarYRec"    , "y^{b#bar{b}} (rec)"          ,  100, -5.,    5.);
  if(genPlots_) bbbarYGen   = fs->make<TH1F>("bbbarYGen"    , "y^{b#bar{b}} (gen)"          ,  100, -5.,    5.);
  // mass
  if(recPlots_) bbbarMassRec= fs->make<TH1F>("bbbarMassRec" , "m^{b#bar{b}} (rec) [GeV]"    , 1200,  0., 1200.);
  if(genPlots_) bbbarMassGen= fs->make<TH1F>("bbbarMassGen" , "m^{b#bar{b}} (gen) [GeV]"    , 1200,  0., 1200.);
  // C) lb-system quantities
  if(recPlots_) lbMassRec= fs->make<TH1F>("lbMassRec" , "m^{lb} (rec) [GeV]"    , 500,  0., 500.);
  if(genPlots_) lbMassGen= fs->make<TH1F>("lbMassGen" , "m^{lb} (gen) [GeV]"    , 500,  0., 500.);

  // 2D correlation
  if(recPlots_&&genPlots_){
    // A) b-jet quantities
    bqPt_       = fs->make<TH2F>("bqPt_" , "p_{t}^{b and #bar{b}} (gen vs rec) [GeV]", 1200, 0., 1200., 1200, 0., 1200.);
    bqPtLead_   = fs->make<TH2F>("bqPtLead_" , "p_{t}^{lead b} (gen vs rec) [GeV]"   , 1200, 0., 1200., 1200, 0., 1200.);
    bqPtSubLead_= fs->make<TH2F>("bqPtSubLead_" , "p_{t}^{lead b} (gen vs rec) [GeV]", 1200, 0., 1200., 1200, 0., 1200.);
    bqEta_ = fs->make<TH2F>("bqEta_", "#eta^{b and #bar{b}} (gen vs rec)"       ,  100, -5.,    5.,  100, -5.,    5.);
    bqY_   = fs->make<TH2F>("bqY_"  , "y^{b and #bar{b}} (gen vs rec)"          ,  100, -5.,    5.,  100, -5.,    5.);
    // B) bbbar-system quantities
    bbbarPt_  = fs->make<TH2F>("bbbarPt_"   , "p_{t}^{b#bar{b}} (gen vs rec) [GeV]", 1200,  0., 1200., 1200,  0., 1200.);
    bbbarEta_ = fs->make<TH2F>("bbbarEta_"  , "#eta^{b#bar{b}} (gen vs rec)"       ,  100, -5.,    5.,  100, -5.,    5.);
    bbbarY_   = fs->make<TH2F>("bbbarY_"    , "y^{b#bar{b}} (gen vs rec)"          ,  100, -5.,    5.,  100, -5.,    5.);
    bbbarMass_= fs->make<TH2F>("bbbarMass_" , "m^{b#bar{b}} (gen vs rec) [GeV]"    , 1200,  0., 1200., 1200,  0., 1200.);
    // C) lb-system quantities
    lbMass_   = fs->make<TH2F>("lbMass_"    , "m^{lb} (gen vs rec) [GeV]"          ,  500,  0.,  500.,  500,  0.,  500.);
  }
  //---
  //   create branches
  //---
  if(useTree_){
    // define the tree and make it known to the TFileService
    tree = fs->make<TTree>("tree","tree",0);
    // weight
    tree->Branch("weight" , &weight , "weight/F" );
    // event identifiers
    runNumber = 0;
    tree->Branch("runNumber", &runNumber, "runNumber/i");
    luminosityBlockNumber = 0;
    tree->Branch("luminosityBlockNumber", &luminosityBlockNumber, "luminosityBlockNumber/i");
    eventNumber= 0;
    tree->Branch("eventNumber", &eventNumber, "eventNumber/i");
    // variables
    tree->Branch("bqPtRec" , &valueBqPtRec , "bqPtRec/F" );
    tree->Branch("bqPtGen" , &valueBqPtGen , "bqPtGen/F" );
    tree->Branch("bqEtaRec", &valueBqEtaRec, "bqEtaRec/F");
    tree->Branch("bqEtaGen", &valueBqEtaGen, "bqEtaGen/F");
    tree->Branch("bqYRec"  , &valueBqYRec  , "bqYRec/F"  );
    tree->Branch("bqYGen"  , &valueBqYGen  , "bqYGen/F"  );
    tree->Branch("bbarqPtRec" , &valueBbarqPtRec , "bbarqPtRec/F" );
    tree->Branch("bbarqPtGen" , &valueBbarqPtGen , "bbarqPtGen/F" );
    tree->Branch("bbarqEtaRec", &valueBbarqEtaRec, "bbarqEtaRec/F");
    tree->Branch("bbarqEtaGen", &valueBbarqEtaGen, "bbarqEtaGen/F");
    tree->Branch("bbarqYRec"  , &valueBbarqYRec  , "bbarqYRec/F"  );
    tree->Branch("bbarqYGen"  , &valueBbarqYGen  , "bbarqYGen/F"  );
    tree->Branch("bbbarMassRec", &valueBbbarMassRec, "bbbarMassRec/F");
    tree->Branch("bbbarMassGen", &valueBbbarMassGen, "bbbarMassGen/F");
    tree->Branch("lbMassRec"   , &valueLbMassRec   , "lbMassRec/F" );
    tree->Branch("lbMassGen"   , &valueLbMassGen   , "lbMassGen/F" );
    tree->Branch("bbbarPtRec"  , &valueBbbarPtRec  , "bbbarPtRec/F");
    tree->Branch("bbbarPtGen"  , &valueBbbarPtGen  , "bbbarPtGen/F");
    tree->Branch("bbbarYRec"   , &valueBbbarYRec   , "bbbarYRec/F" );
    tree->Branch("bbbarYGen"   , &valueBbbarYGen   , "bbbarYGen/F" );
    tree->Branch("bbbarEtaRec" , &valueBbbarEtaRec , "bbbarEtaRec/F");
    tree->Branch("bbbarEtaGen" , &valueBbbarEtaGen , "bbbarEtaGen/F");
    tree->Branch("bqPtLeadRec" , &valueLeadBqPtRec , "bqPtLeadRec/F");
    tree->Branch("bqPtLeadGen" , &valueLeadBqPtGen , "bqPtLeadGen/F");
    tree->Branch("bqPtSubLeadRec", &valueSubLeadBqPtRec, "bqPtSubLeadRec/F");
    tree->Branch("bqPtSubLeadGen", &valueSubLeadBqPtGen, "bqPtSubLeadGen/F");
    // boolean = true if swapping gives better results
    tree->Branch("bbSwapBetter"  , &bbSwapBetter  , "bbSwapBetter/O"  );
    // parton level quark vs reco jet assignment
    if(recPlots_&&genPlots_) tree->Branch("qAssignment" , &valueAssignment , "qAssignment/F" );
  }
}

void
SemiLepBjetAnalyzer::endJob() 
{
}

std::pair<const reco::Candidate*,const reco::Candidate*> 
SemiLepBjetAnalyzer::getbJets(const edm::Handle<TtSemiLeptonicEvent> semiLepEvt, const std::string hypoKey_){
  const reco::Candidate* zero=0;
  if(verbose>1) std::cout << "get b jet candidates from kinfit" << std::endl;
  // check if hypothesis is available and valid in this event
  if(!semiLepEvt->isHypoValid(hypoKey_)){
    if(verbose>0) std::cout << "Hypothesis not valid for this event" << std::endl;
  }
  else{
    // check if decay is semileptonic
    if(  semiLepEvt->genEvent().isAvailable()                    && 
	(semiLepEvt->genEvent()->isSemiLeptonic(WDecay::kMuon) || 
	 semiLepEvt->genEvent()->isSemiLeptonic(WDecay::kElec) ||
	 semiLepEvt->genEvent()->isSemiLeptonic(WDecay::kTau )   ) ){
      if(verbose>1) std::cout << "semilep. decay or no ttgenevent available" << std::endl;
      // get reconstructed b quarks (jets) from the hypothesis 
      const reco::Candidate* bhad  = semiLepEvt->hadronicDecayB(hypoKey_);
      const reco::Candidate* blep  = semiLepEvt->leptonicDecayB(hypoKey_);
      if(bhad&&blep){
	// destinguish b and bbar using the lepton charge
	// (tbar->W-&bbar, W- -> l- nu, therefore: l- -> bbar; l+ -> b)
	bool lminus = ((reco::LeafCandidate*)(semiLepEvt->singleLepton(hypoKey_)))->charge()<0 ? true : false;
	const reco::Candidate* b    = lminus ? bhad : blep;
	const reco::Candidate* bbar = lminus ? blep : bhad;   
	if(verbose>2) std::cout << "q(lepRec)<0? " << lminus << std::endl;
	// return b jets
	if(verbose>0) std::cout << "rec bjet candidates found!" << std::endl;
	return std::make_pair(b,bbar);
      }
    }
  }
  // otherwise: return NULL
  if(verbose>0) std::cout << "no rec bjets found" << std::endl;
  return std::make_pair(zero,zero);
}

std::pair<const reco::Candidate*,const reco::Candidate*> 
SemiLepBjetAnalyzer::getPreBJets(const edm::Handle<TtSemiLeptonicEvent> semiLepEvt, const std::string hypoKey_, const edm::Handle<std::vector<pat::Jet> > jets){
  const reco::Candidate* zero=0;
  if(verbose>1) std::cout << "get b jet candidate kinematics before KinFit" << std::endl;
  // check if kinfit information is available
  if(semiLepEvt.isValid()&&semiLepEvt->isHypoValid(hypoKey_)){
    if(verbose>0) std::cout << "Hypothesis is valid" << std::endl;
    // get indices
    int hadBIndex=semiLepEvt->jetLeptonCombination(hypoKey_)[TtSemiLepEvtPartons::HadB];
    int lepBIndex=semiLepEvt->jetLeptonCombination(hypoKey_)[TtSemiLepEvtPartons::LepB];
    if(verbose>1) std::cout << "recoLepBIX: " << lepBIndex << ", recoHadBIX: " << hadBIndex << std::endl;
    // get jets before the fit
    const reco::Candidate* bhad = &(jets->at(hadBIndex));
    const reco::Candidate* blep = &(jets->at(lepBIndex));
    // get charge of lepton 
    bool lminus = ((reco::LeafCandidate*)(semiLepEvt->singleLepton(hypoKey_)))->charge()<0 ? true : false;
    // return candidates
    if(bhad&&blep){
      if(verbose>0) std::cout << "rec bjet candidates before KinFit found!" << std::endl;
      return std::make_pair((lminus ? bhad : blep),(lminus ? blep : bhad));
    }
  }
  return std::make_pair(zero,zero);
}

const reco::GenJet* 
SemiLepBjetAnalyzer::getJetFromCollection(const reco::GenJetCollection& genJets, int IX)
{
  const reco::GenJet* zero=0;
  int index=0;
  // loop collection
  for (size_t iJet = 0; iJet < genJets.size(); ++iJet) {
    const reco::GenJet* thisJet = &(genJets[iJet]);
    // return jet with index "IX" 
    if(index==IX){
      if(verbose>1) std::cout << "jet with index " << IX << " found!" << std::endl;
      return thisJet;
    }
    ++ index;
  }
  // if not found: return NULL
  if(verbose>0){
    std::cout << "WARNING: index " << IX << " is larger than the size";
    std::cout << " of the jet collection (" << genJets.size() << ")" << std::endl;
  }
  return zero;
}

double  
SemiLepBjetAnalyzer::checkPartonAssignment(const edm::Handle<TtSemiLeptonicEvent> semiLepEvt, int maxNJets){
  double assignment=-1;
  // ---
  //    check quark assignment
  // ---
  // no parton jet parton match exists
  if(semiLepEvt->isHypoValid("kKinFit")&&(!semiLepEvt->isHypoValid("kGenMatch"))){
    assignment= 9.;
  }
  // if jet parton match exists:
  if(semiLepEvt->isHypoValid("kKinFit")&& semiLepEvt->isHypoValid("kGenMatch")){
    // indices for all quarks from Kinfit Hypothesis and genmatch
    int lepBIndex         = semiLepEvt->jetLeptonCombination("kKinFit"  )[TtSemiLepEvtPartons::LepB     ];
    int hadBIndex         = semiLepEvt->jetLeptonCombination("kKinFit"  )[TtSemiLepEvtPartons::HadB     ];
    int lightQIndex       = semiLepEvt->jetLeptonCombination("kKinFit"  )[TtSemiLepEvtPartons::LightQ   ];
    int lightQBarIndex    = semiLepEvt->jetLeptonCombination("kKinFit"  )[TtSemiLepEvtPartons::LightQBar];
    int lepBIndexGen      = semiLepEvt->jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LepB     ];
    int hadBIndexGen      = semiLepEvt->jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::HadB     ];
    int lightQIndexGen    = semiLepEvt->jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LightQ   ];
    int lightQBarIndexGen = semiLepEvt->jetLeptonCombination("kGenMatch")[TtSemiLepEvtPartons::LightQBar];
    // calculate permutation
    // 0: nothing wrong
    if((lepBIndex==lepBIndexGen)&&(hadBIndex==hadBIndexGen)&&
       (((lightQIndex==lightQIndexGen   )&&(lightQBarIndex==lightQBarIndexGen))||
	((lightQIndex==lightQBarIndexGen)&&(lightQBarIndex==lightQIndexGen   )))) assignment=0;
    else{
      // 1: b quarks switched
      if((lepBIndex==hadBIndexGen)&&(hadBIndex==lepBIndexGen)) assignment=1;
      // 2: leptonic b and light quark switched
      if(((lepBIndex==lightQIndexGen)||(lepBIndex==lightQBarIndexGen))&&
	 (((lightQIndex==lepBIndexGen)||(lightQBarIndex==lepBIndexGen)))) assignment=2;
      // 3: hadronic b and light quark switched/
      if(((hadBIndex==lightQIndexGen)||(hadBIndex==lightQBarIndexGen))&&
	 (((lightQIndex==hadBIndexGen)||(lightQBarIndex==hadBIndexGen)))) assignment=3;
      // 4: light quark->leptonic b & leptonic b->hadronic b & hadronic b-> light quark
      if(((lepBIndex==lightQIndexGen)||(lepBIndex==lightQBarIndexGen))&&(hadBIndex==lepBIndexGen)&&
	 ((lightQIndex==hadBIndexGen)||(lightQBarIndex==hadBIndexGen))) assignment=4;
      // 5: light quark->hadronic b & hadronic b->leptonic b & leptonic b-> light quark
      if(((hadBIndex==lightQIndexGen)||(hadBIndex==lightQBarIndexGen))&&(lepBIndex==hadBIndexGen)&&
	 ((lightQIndex==lepBIndexGen)||(lightQBarIndex==lepBIndexGen))) assignment=5;
      // 6: hadronic/leptonic b-> light quarks &  light quarks->hadronic/leptonic b
      if(((hadBIndex     ==lightQIndexGen)||(hadBIndex     ==lightQBarIndexGen))&&
	 ((lepBIndex     ==lightQIndexGen)||(lepBIndex     ==lightQBarIndexGen))&&
	 ((lightQIndex   ==lepBIndexGen  )||(lightQIndex   ==hadBIndexGen     ))&&
	 ((lightQBarIndex==lepBIndexGen  )||(lightQBarIndex==hadBIndexGen     ))) assignment=6;
      // make sure that no relevant jet is missing
      std::vector<int> genJets_, recoJets_;
      // list of genJets
      genJets_ .push_back(lepBIndexGen     );
      genJets_ .push_back(hadBIndexGen     );
      genJets_ .push_back(lightQIndexGen   );
      genJets_ .push_back(lightQBarIndexGen);
      std::sort( genJets_.begin(), genJets_.end());
      // list of recoJets
      recoJets_.push_back(lepBIndex);
      recoJets_.push_back(hadBIndex);
      recoJets_.push_back(lightQIndex);
      recoJets_.push_back(lightQBarIndex);
      std::sort( recoJets_.begin(), recoJets_.end());
      // compare recoJets and genJets
      for(unsigned int i=0; i<recoJets_.size(); ++i){
	if( recoJets_[i]!=genJets_[i] ){ 
	  if(maxNJets<4){
	    std::cout << "ERROR: number of conidered jets can not be smaller than 4" << std::endl;
	    exit(1);
	  }

	  // 7: jet is missing
	  if( genJets_.back()>maxNJets-1 ) assignment=7;
	  // 8: wrong jet chosen (only valid if kinFitTtSemiLepEventHypothesis.maxNJets>4)
	  // e.g. took the wrong 4 out of 5 jets 
	  else{
	    if(assignment<0) assignment=8;
	  }
	  break;
	}
      }
    }
  }
  return assignment;
}
