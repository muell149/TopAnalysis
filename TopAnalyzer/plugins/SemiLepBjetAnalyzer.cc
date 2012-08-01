#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"

#include "TopAnalysis/TopAnalyzer/plugins/SemiLepBjetAnalyzer.h"

// default constructor
SemiLepBjetAnalyzer::SemiLepBjetAnalyzer(const edm::ParameterSet& cfg):
  semiLepEvt_(cfg.getParameter<edm::InputTag>("semiLepEvent")),
  hypoKey_   (cfg.getParameter<std::string>  ("hypoKey"     )),
  genJets_   (cfg.getParameter<edm::InputTag>("genJets"     )),
  bJetCollection_(cfg.getParameter<bool>   ("bJetCollection")),
  verbose    (cfg.getParameter<int>          ("output"      )),
  weight_    (cfg.getParameter<edm::InputTag>("weight"      )),
  genPlots_  (cfg.getParameter<bool>         ("genPlots"    )),
  recPlots_  (cfg.getParameter<bool>         ("recPlots"    )),
  bHadJetIdx_    (cfg.getParameter<edm::InputTag> ("BHadJetIndex"    )),
  antibHadJetIdx_(cfg.getParameter<edm::InputTag> ("AntiBHadJetIndex")),
  useTree_   (cfg.getParameter<bool>("useTree")),
  valueBqPtRec(0),
  valueBqPtGen(0),
  valueBqEtaRec(0),
  valueBqEtaGen(0),
  valueBqYRec(0),
  valueBqYGen(0),
  valueBbarqPtRec(0),
  valueBbarqPtGen(0),
  valueBbarqEtaRec(0),
  valueBbarqEtaGen(0),
  valueBbarqYRec(0),
  valueBbarqYGen(0)
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
  // c) get a handle for genjet collection
  if(verbose>1) std::cout << "c) genJetCollection" << std::endl;
  // get jet collection
  edm::Handle<reco::GenJetCollection> genJets;
  if(genPlots_) event.getByLabel(genJets_, genJets);
  // d) position of the jet identified as b-hadron jet
  if(verbose>1) std::cout << "d) b-jet indices produced by TopAnalysis/TopUtils/GenLevelBJetProducer" << std::endl;
  int bIX   =-1;
  int bbarIX=-1;
  if(genPlots_){
    // take leading two jets assuming that collection genJets consists of bjets only
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
  const reco::Candidate* b   = recBJets.first ;
  const reco::Candidate* bbar= recBJets.second;
  // fill rec histograms
  if(b&&bbar){
    if(useTree_){
      valueBqPtRec =b->pt();
      valueBqEtaRec=b->eta();
      valueBqYRec  =b->rapidity(); 
      valueBbarqPtRec =bbar->pt();
      valueBbarqEtaRec=bbar->eta();
      valueBbarqYRec  =bbar->rapidity();
    }
    if(verbose>1) std::cout << "do filling" << std::endl;
    bqPtRec ->Fill( b->pt()         , weight);
    bqPtRec ->Fill( bbar->pt()      , weight);
    bqEtaRec->Fill( b->eta()        , weight);
    bqEtaRec->Fill( bbar->eta()     , weight);
    bqYRec  ->Fill( b->rapidity()   , weight);
    bqYRec  ->Fill( bbar->rapidity(), weight);
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
  // get generator level b-Jets fromgen jet collection using indices from B Hadron identification procedure
  const reco::GenJet* genb    = genPlots_ ? getJetFromCollection(*genJets,bIX   ) : 0;
  const reco::GenJet* genbbar = genPlots_ ? getJetFromCollection(*genJets,bbarIX) : 0;
  // fill gen histograms
  if(genb&&genbbar){
    if(useTree_){
      valueBqPtGen =genb->pt();
      valueBqEtaGen=genb->eta();
      valueBqYGen  =genb->rapidity();
      valueBbarqPtGen =genbbar->pt();
      valueBbarqEtaGen=genbbar->eta();
      valueBbarqYGen  =genbbar->rapidity();
    }
    if(verbose>1) std::cout << "do filling" << std::endl;
    bqPtGen ->Fill( genb->pt()         , weight);
    bqPtGen ->Fill( genbbar->pt()      , weight);
    bqEtaGen->Fill( genb->eta()        , weight);
    bqEtaGen->Fill( genbbar->eta()     , weight);
    bqYGen  ->Fill( genb->rapidity()   , weight);
    bqYGen  ->Fill( genbbar->rapidity(), weight);
  }  
  else if(verbose>1) std::cout << "no filling done" << std::endl;

  // ---
  //     D: gen rec correlation plots
  // ---  
  if(verbose>0) std::cout << std::endl << "correlation plots" << std::endl;
  if(genb&&genbbar&&b&&bbar){
    if(verbose>1) std::cout << "do filling" << std::endl;
    // fill correlation histograms
    bqPt_ ->Fill( genb->pt()         , b->pt()         , weight);
    bqPt_ ->Fill( genbbar->pt()      , bbar->pt()      , weight);
    bqEta_->Fill( genb->eta()        , b->eta()        , weight);
    bqEta_->Fill( genbbar->eta()     , bbar->eta()     , weight);
    bqY_  ->Fill( genb->rapidity()   , b->rapidity()   , weight);
    bqY_  ->Fill( genbbar->rapidity(), bbar->rapidity(), weight);
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
  // pt
  if(recPlots_) bqPtRec  = fs->make<TH1F>("bqPtRec" , "p_{t}^{b and #bar{b}} (rec) [GeV]", 1200, 0., 1200.);
  if(genPlots_) bqPtGen  = fs->make<TH1F>("bqPtGen" , "p_{t}^{b and #bar{b}} (gen) [GeV]", 1200, 0., 1200.);
  // eta
  if(recPlots_) bqEtaRec = fs->make<TH1F>("bqEtaRec", "#eta^{b and #bar{b}} (rec)"       , 100, -5., 5.);
  if(genPlots_) bqEtaGen = fs->make<TH1F>("bqEtaGen", "#eta^{b and #bar{b}} (gen)"       , 100, -5., 5.);
  // rapidity
  if(recPlots_) bqYRec   = fs->make<TH1F>("bqYRec"  , "y^{b and #bar{b}} (rec)"          , 100, -5., 5.);
  if(genPlots_) bqYGen   = fs->make<TH1F>("bqYGen"  , "y^{b and #bar{b}} (gen)"          , 100, -5., 5.);
  // correlation
  if(recPlots_&&genPlots_){
    bqPt_  = fs->make<TH2F>("bqPt_" , "p_{t}^{b and #bar{b}} (gen vs rec) [GeV]", 1200,  0., 1200., 1200,  0., 1200.);
    bqEta_ = fs->make<TH2F>("bqEta_", "#eta^{b and #bar{b}} (gen vs rec)"       ,  100, -5.,    5.,  100, -5.,    5.);
    bqY_   = fs->make<TH2F>("bqY_"  , "y^{b and #bar{b}} (gen vs rec)"          ,  100, -5.,    5.,  100, -5.,    5.);
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
    if( !semiLepEvt->genEvent().isAvailable()                  || 
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
