#include "TLorentzVector.h"
#include "TopAnalysis/TopAnalyzer/plugins/FullLepKinAnalyzer.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"

/// default constructor
FullLepKinAnalyzer::FullLepKinAnalyzer(const edm::ParameterSet& cfg):
  isSignalMC_      (cfg.getParameter<bool>         ("isSignalMC"  )),
  FullLepEvt_      (cfg.getParameter<edm::InputTag>("FullLepEvent")),
  hypoKey_         (cfg.getParameter<edm::InputTag>("hypoKey"     )),
  jets_            (cfg.getParameter<edm::InputTag>("jets"        ))
{
}

/// default destructor
FullLepKinAnalyzer::~FullLepKinAnalyzer()
{
}

/// everything that has to be done before the event loop: books histograms
void 
FullLepKinAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  bookKinHistos      (fs);
  bookQualityHistos  (fs);
  bookRecCorrelHistos(fs);
  if(isSignalMC_){
    bookGenHistos      (fs);  
    bookPullHistos     (fs);
    book2DHistos       (fs);
  }       
}

/// everything that has to be done during the event loop: filling plots
void
FullLepKinAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<TtFullLeptonicEvent> FullLepEvt;
  evt.getByLabel(FullLepEvt_, FullLepEvt);

  edm::Handle<int> hypoKeyHandle;
  evt.getByLabel(hypoKey_, hypoKeyHandle);
  TtEvent::HypoClassKey& hypoKey = (TtEvent::HypoClassKey&) *hypoKeyHandle;

  // -----------------------
  // check if hypothesis is valid in this event
  // and if it satisfies some quality criteria
  // -----------------------
         
  if( !FullLepEvt->isHypoAvailable(hypoKey) ){
    edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not available for this event";
    return;
  }
  
  edm::Handle<edm::View< pat::Jet > > jets;
  evt.getByLabel(jets_, jets);
  
  int nTCHEL  = 0;
  int nTCHEM  = 0;  
  int nSSVHEM = 0;
  
  for(edm::View<pat::Jet>::const_iterator jet = jets->begin();jet != jets->end(); ++jet) { 
    if(jet->bDiscriminator("trackCountingHighEffBJetTags")>1.7          && nTCHEL<2 ) ++nTCHEL;
    if(jet->bDiscriminator("trackCountingHighEffBJetTags")>3.3          && nTCHEM<2 ) ++nTCHEM;    
    if(jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags")>1.74 && nSSVHEM<2) ++nSSVHEM;
  }

  int y = 0;   
  if( FullLepEvt->isHypoValid(hypoKey) ) y = 1;
  
  kinTCHELcorrelation_ ->Fill(nTCHEL, y);
  kinTCHEMcorrelation_ ->Fill(nTCHEM, y);  
  kinSSVHEMcorrelation_->Fill(nSSVHEM,y);
  
  if( !FullLepEvt->isHypoValid(hypoKey) ){  
    edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not valid for this event";
    TopKin_[4]->SetBinContent(1,TopKin_[4]->GetBinContent(1)+1);
    return;  // return if any of the hypotheses is not valid
  }
 
  // -----------------------
  // fill histos related to quality of the TtFullLeptonicEvent
  // -----------------------
  fillQualityHistos(*FullLepEvt, hypoKey);

  // -----------------------
  // fill histos for basic kinematic variables
  // -----------------------
  const reco::Candidate* Top    = FullLepEvt->top(hypoKey);
  const reco::Candidate* Wplus  = FullLepEvt->wPlus(hypoKey);
  const reco::Candidate* B      = FullLepEvt->b(hypoKey);
  const reco::Candidate* LepBar = FullLepEvt->leptonBar(hypoKey);
  const reco::Candidate* Nu     = FullLepEvt->neutrino(hypoKey);
  
  const reco::Candidate* TopBar = FullLepEvt->topBar(hypoKey);
  const reco::Candidate* Wminus = FullLepEvt->wMinus(hypoKey);
  const reco::Candidate* BBar   = FullLepEvt->bBar(hypoKey);
  const reco::Candidate* Lep    = FullLepEvt->lepton(hypoKey);
  const reco::Candidate* NuBar  = FullLepEvt->neutrinoBar(hypoKey);

  AddFourMomenta addFourMomenta;
  
  // combined top pair object
  reco::CompositeCandidate* TtBar = new reco::CompositeCandidate();
  TtBar->addDaughter(*Top);
  TtBar->addDaughter(*TopBar);
  addFourMomenta.set(*TtBar);
  
  // combined lepton pair object 
  reco::CompositeCandidate* LepPair = new reco::CompositeCandidate();
  LepPair->addDaughter(*Lep);
  LepPair->addDaughter(*LepBar);
  addFourMomenta.set(*LepPair);
  
  // dijet pair object 
  reco::CompositeCandidate* JetPair = new reco::CompositeCandidate();
  JetPair->addDaughter(*B);
  JetPair->addDaughter(*BBar); 
  addFourMomenta.set(*JetPair); 

  fillKinHistos(TopKin_,    *Top    );
  fillKinHistos(WplusKin_,  *Wplus  );
  fillKinHistos(BKin_,      *B      );
  fillKinHistos(LepBarKin_, *LepBar );
  fillKinHistos(NuKin_,     *Nu     );

  fillKinHistos(TopBarKin_, *TopBar );
  fillKinHistos(WminusKin_, *Wminus );
  fillKinHistos(BBarKin_,   *BBar   );
  fillKinHistos(LepKin_,    *Lep    );
  fillKinHistos(NuBarKin_,  *NuBar  );
  
  fillKinHistos(TtBarKin_,     *TtBar );
  fillKinHistos(LepPairKin_, *LepPair );
  fillKinHistos(JetPairKin_, *JetPair );

  diLeptonMassVsLeptonPt_     ->Fill(LepPair->mass(), Lep->pt());
  diLeptonMassVsLeptonPt_     ->Fill(LepPair->mass(), LepBar->pt()); 
  diLeptonMassVsLeptonEta_    ->Fill(LepPair->mass(), Lep->eta());
  diLeptonMassVsLeptonEta_    ->Fill(LepPair->mass(), LepBar->eta());  
  diLeptonMassVsDiLeptonPt_   ->Fill(LepPair->mass(), LepPair->pt());
  diLeptonMassVsTopPt_	      ->Fill(LepPair->mass(), Top->pt()); 
  diLeptonMassVsTopPt_	      ->Fill(LepPair->mass(), TopBar->pt());   
  diLeptonMassVsTopRapidity_  ->Fill(LepPair->mass(), Top->rapidity()); 
  diLeptonMassVsTopRapidity_  ->Fill(LepPair->mass(), TopBar->rapidity());   
  diLeptonMassVsTtBarPt_      ->Fill(LepPair->mass(), TtBar->pt()); 
  diLeptonMassVsTtBarRapidity_->Fill(LepPair->mass(), TtBar->rapidity()); 
  diLeptonMassVsTtBarMass_    ->Fill(LepPair->mass(), TtBar->mass()); 

  nBtagsTCHELVsLeptonPt_     ->Fill(nTCHEL, Lep->pt());
  nBtagsTCHELVsLeptonPt_     ->Fill(nTCHEL, LepBar->pt()); 
  nBtagsTCHELVsLeptonEta_    ->Fill(nTCHEL, Lep->eta());
  nBtagsTCHELVsLeptonEta_    ->Fill(nTCHEL, LepBar->eta());  
  nBtagsTCHELVsDiLeptonPt_   ->Fill(nTCHEL, LepPair->pt());
  nBtagsTCHELVsDiLeptonMass_ ->Fill(nTCHEL, LepPair->mass());
  nBtagsTCHELVsTopPt_	     ->Fill(nTCHEL, Top->pt()); 
  nBtagsTCHELVsTopPt_	     ->Fill(nTCHEL, TopBar->pt());   
  nBtagsTCHELVsTopRapidity_  ->Fill(nTCHEL, Top->rapidity()); 	   
  nBtagsTCHELVsTopRapidity_  ->Fill(nTCHEL, TopBar->rapidity());
  nBtagsTCHELVsTtBarPt_	     ->Fill(nTCHEL, TtBar->pt()); 
  nBtagsTCHELVsTtBarRapidity_->Fill(nTCHEL, TtBar->rapidity()); 
  nBtagsTCHELVsTtBarMass_    ->Fill(nTCHEL, TtBar->mass()); 

  nBtagsTCHEMVsLeptonPt_     ->Fill(nTCHEM, Lep->pt());
  nBtagsTCHEMVsLeptonPt_     ->Fill(nTCHEM, LepBar->pt()); 
  nBtagsTCHEMVsLeptonEta_    ->Fill(nTCHEM, Lep->eta());
  nBtagsTCHEMVsLeptonEta_    ->Fill(nTCHEM, LepBar->eta());  
  nBtagsTCHEMVsDiLeptonPt_   ->Fill(nTCHEM, LepPair->pt());
  nBtagsTCHEMVsDiLeptonMass_ ->Fill(nTCHEM, LepPair->mass());
  nBtagsTCHEMVsTopPt_	     ->Fill(nTCHEM, Top->pt()); 
  nBtagsTCHEMVsTopPt_	     ->Fill(nTCHEM, TopBar->pt());   
  nBtagsTCHEMVsTopRapidity_  ->Fill(nTCHEM, Top->rapidity());	 
  nBtagsTCHEMVsTopRapidity_  ->Fill(nTCHEM, TopBar->rapidity());
  nBtagsTCHEMVsTtBarPt_	     ->Fill(nTCHEM, TtBar->pt()); 
  nBtagsTCHEMVsTtBarRapidity_->Fill(nTCHEM, TtBar->rapidity()); 
  nBtagsTCHEMVsTtBarMass_    ->Fill(nTCHEM, TtBar->mass()); 

  nBtagsSSVHEMVsLeptonPt_     ->Fill(nSSVHEM, Lep->pt());
  nBtagsSSVHEMVsLeptonPt_     ->Fill(nSSVHEM, LepBar->pt()); 
  nBtagsSSVHEMVsLeptonEta_    ->Fill(nSSVHEM, Lep->eta());
  nBtagsSSVHEMVsLeptonEta_    ->Fill(nSSVHEM, LepBar->eta());  
  nBtagsSSVHEMVsDiLeptonPt_   ->Fill(nSSVHEM, LepPair->pt());
  nBtagsSSVHEMVsDiLeptonMass_ ->Fill(nSSVHEM, LepPair->mass());
  nBtagsSSVHEMVsTopPt_	      ->Fill(nSSVHEM, Top->pt()); 
  nBtagsSSVHEMVsTopPt_	      ->Fill(nSSVHEM, TopBar->pt());   
  nBtagsSSVHEMVsTopRapidity_  ->Fill(nSSVHEM, Top->rapidity());    
  nBtagsSSVHEMVsTopRapidity_  ->Fill(nSSVHEM, TopBar->rapidity());
  nBtagsSSVHEMVsTtBarPt_      ->Fill(nSSVHEM, TtBar->pt()); 
  nBtagsSSVHEMVsTtBarRapidity_->Fill(nSSVHEM, TtBar->rapidity()); 
  nBtagsSSVHEMVsTtBarMass_    ->Fill(nSSVHEM, TtBar->mass()); 

  // -----------------------
  // fill generator and pull histos for kinematic variables
  // -----------------------
  if( !isSignalMC_ || !FullLepEvt->genEvent() || !FullLepEvt->genEvent()->isFullLeptonic()){
    delete TtBar;
    delete LepPair;
    delete JetPair;
    return;  
  }
  
  const reco::Candidate* genTop    = FullLepEvt->genTop();
  const reco::Candidate* genWplus  = FullLepEvt->genWPlus();
  const reco::Candidate* genB      = FullLepEvt->genB();
  const reco::Candidate* genLepBar = FullLepEvt->genLeptonBar();
  const reco::Candidate* genNu     = FullLepEvt->genNeutrino();

  const reco::Candidate* genTopBar = FullLepEvt->genTopBar();
  const reco::Candidate* genWminus = FullLepEvt->genWMinus();
  const reco::Candidate* genBBar   = FullLepEvt->genBBar();
  const reco::Candidate* genLep    = FullLepEvt->genLepton();
  const reco::Candidate* genNuBar  = FullLepEvt->genNeutrinoBar();

  // combined top pair object
  reco::CompositeCandidate* genTtBar = new reco::CompositeCandidate();
  genTtBar->addDaughter(*genTop);
  genTtBar->addDaughter(*genTopBar);  
  addFourMomenta.set(*genTtBar);
  
  // combined lepton pair object 
  reco::CompositeCandidate* genLepPair = new reco::CompositeCandidate();
  genLepPair->addDaughter(*genLep);
  genLepPair->addDaughter(*genLepBar);
  addFourMomenta.set(*genLepPair);
  
  // combined lepton pair object 
  reco::CompositeCandidate* genJetPair = new reco::CompositeCandidate();
  genJetPair->addDaughter(*genB);
  genJetPair->addDaughter(*genBBar);
  addFourMomenta.set(*genJetPair);

  // gen particle distributions
  fillKinHistos(TopGen_,    *genTop    );
  fillKinHistos(WplusGen_,  *genWplus  );
  fillKinHistos(BGen_,      *genB      );
  fillKinHistos(LepBarGen_, *genLepBar );
  fillKinHistos(NuGen_,     *genNu     );

  fillKinHistos(TopBarGen_, *genTopBar );
  fillKinHistos(WminusGen_, *genWminus );
  fillKinHistos(BBarGen_,   *genBBar   );
  fillKinHistos(LepGen_,    *genLep    );
  fillKinHistos(NuBarGen_,  *genNuBar  );
  
  fillKinHistos(TtBarGen_,   *genTtBar   );
  fillKinHistos(LepPairGen_, *genLepPair );
  fillKinHistos(JetPairGen_, *genJetPair );    
  
  // pull distributions
  fillPullHistos(TopPull_,    *TopPull2D_,    *Top,	*genTop    );
  fillPullHistos(WplusPull_,  *WplusPull2D_,  *Wplus,	*genWplus  );
  fillPullHistos(BPull_,      *BPull2D_,      *B,	*genB	   );
  fillPullHistos(LepBarPull_, *LepBarPull2D_, *LepBar,  *genLepBar );
  fillPullHistos(NuPull_,     *NuPull2D_,     *Nu,	*genNu     );

  fillPullHistos(TopBarPull_, *TopBarPull2D_, *TopBar,  *genTopBar );
  fillPullHistos(WminusPull_, *WminusPull2D_, *Wminus,  *genWminus );
  fillPullHistos(BBarPull_,   *BBarPull2D_,   *BBar,	*genBBar   );
  fillPullHistos(LepPull_,    *LepPull2D_,    *Lep,	*genLep    );
  fillPullHistos(NuBarPull_,  *NuBarPull2D_,  *NuBar,	*genNuBar  ); 
  
  fillPullHistos(TtBarPull_,   *TtBarPull2D_,	*TtBar,   *genTtBar   );
  fillPullHistos(LepPairPull_, *LepPairPull2D_, *LepPair, *genLepPair );
  fillPullHistos(JetPairPull_, *JetPairPull2D_, *JetPair, *genJetPair );
  
  // 2D distributions
  fill2DHistos(Top2D_,     *Top,     *genTop     );
  fill2DHistos(Wplus2D_,   *Wplus,   *genWplus   );
  fill2DHistos(B2D_,       *B,       *genB       );
  fill2DHistos(LepBar2D_,  *LepBar,  *genLepBar  );
  fill2DHistos(Nu2D_,      *Nu,      *genNu      );

  fill2DHistos(TopBar2D_,  *TopBar,  *genTopBar  );
  fill2DHistos(Wminus2D_,  *Wminus,  *genWminus  );
  fill2DHistos(BBar2D_,    *BBar,    *genBBar	 );
  fill2DHistos(Lep2D_,     *Lep,     *genLep	 );
  fill2DHistos(NuBar2D_,   *NuBar,   *genNuBar   ); 
  
  fill2DHistos(TtBar2D_,   *TtBar,   *genTtBar   );
  fill2DHistos(LepPair2D_, *LepPair, *genLepPair );
  fill2DHistos(JetPair2D_, *JetPair, *genJetPair );  
  
  delete TtBar;
  delete LepPair;
  delete JetPair;
  delete genTtBar;
  delete genLepPair;
  delete genJetPair;  
  
  // indices Hist
  const TtEvent::HypoClassKey genKey = TtEvent::HypoClassKey(3);
  const TtEvent::HypoClassKey kinKey = TtEvent::HypoClassKey(6);
   
  if(FullLepEvt->isHypoValid(genKey) && FullLepEvt->isHypoValid(kinKey)){
    compare_->Fill(FullLepEvt->jetLeptonCombination(genKey)[0]   , FullLepEvt->jetLeptonCombination(kinKey)[0]   );
    compare_->Fill(FullLepEvt->jetLeptonCombination(genKey)[1]+ 4, FullLepEvt->jetLeptonCombination(kinKey)[1]+ 4);
    compare_->Fill(FullLepEvt->jetLeptonCombination(genKey)[2]+ 8, FullLepEvt->jetLeptonCombination(kinKey)[2]+ 8);    
    compare_->Fill(FullLepEvt->jetLeptonCombination(genKey)[3]+12, FullLepEvt->jetLeptonCombination(kinKey)[3]+12);    
    compare_->Fill(FullLepEvt->jetLeptonCombination(genKey)[4]+16, FullLepEvt->jetLeptonCombination(kinKey)[4]+16);
    compare_->Fill(FullLepEvt->jetLeptonCombination(genKey)[5]+20, FullLepEvt->jetLeptonCombination(kinKey)[5]+20);
  }      
}

/// everything that has to be done after the event loop
void
FullLepKinAnalyzer::endJob() 
{
}

/// book histograms for reconstructed particles properties: Pt, E, Eta, rapidity, Phi, m
void
FullLepKinAnalyzer::bookKinHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("kin");

  TopKin_.push_back( fs->make<TH1D>(ns.name("TopPt"      ), "p_{t} (t) [GeV]",100,  0. , 500. ) );
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopEta"     ), "#eta (t)"       ,100, -5.0,   5.0) );
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopRapidity"), "rapidity (t)"   ,100, -5.0,   5.0) ); 
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopPhi"     ), "#phi (t)"       , 62, -3.1,   3.1) );
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopMass"    ), "M (top) [GeV]"  ,100,-50. , 450. ) );

  WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusPt"      ), "p_{t} (W^{+}) [GeV]",100,  0. , 500. ) );
  WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusEta"     ), "#eta (W^{+})"       ,100, -5.0,   5.0) );
  WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusRapidity"), "rapidity (W^{+})"   ,100, -5.0,   5.0) );  
  WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusPhi"     ), "#phi (W^{+})"       , 62, -3.1,   3.1) );
  WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusMass"    ), "M (W^{+}) [GeV]"    ,100,  0. , 500. ) );

  BKin_.push_back( fs->make<TH1D>(ns.name("BPt"      ), "p_{t} (b) [GeV]",100,  0. , 500. ) );
  BKin_.push_back( fs->make<TH1D>(ns.name("BEta"     ), "#eta (b)"       ,100, -5.0,   5.0) );
  BKin_.push_back( fs->make<TH1D>(ns.name("BRapidity"), "rapidity (b)"   ,100, -5.0,   5.0) );  
  BKin_.push_back( fs->make<TH1D>(ns.name("BPhi"     ), "#phi (b)"       , 62, -3.1,   3.1) );
  BKin_.push_back( fs->make<TH1D>(ns.name("BMass"    ), "M (b) [GeV]"    ,100,  0. , 500. ) );
    
  LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarPt"      ), "p_{t} (l^{+}) [GeV]",100,  0. , 500. ) );
  LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarEta"     ), "#eta (l^{+})"       ,100, -5.0,   5.0) );
  LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarRapidity"), "rapidity (l^{+})"   ,100, -5.0,   5.0) ); 
  LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarPhi"     ), "#phi (l^{+})"       , 62, -3.1,   3.1) );
  LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarMass"    ), "M (l^{+}) [GeV]"    ,100,  0. , 500. ) ); 

  NuKin_.push_back( fs->make<TH1D>(ns.name("NuPt"      ), "p_{t} (#nu^{-}) [GeV]",100,  0. , 500. ) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuEta"     ), "#eta (#nu^{-})"       ,100, -5.0,   5.0) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuRapidity"), "rapidity (#nu^{-})"   ,100, -5.0,   5.0) );  
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuPhi"     ), "#phi (#nu^{-})"       , 62, -3.1,   3.1) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuMass"    ), "M (#nu^{-}) [GeV]"    ,100,  0. , 500. ) );

  TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarPt"      ), "p_{t} (#bar{t}) [GeV]",100,  0. , 500. ) );
  TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarEta"     ), "#eta (#bar{t})"       ,100, -5.0,   5.0) );
  TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarRapidity"), "rapidity (#bar{t})"   ,100, -5.0,   5.0) );
  TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarPhi"     ), "#phi (#bar{t})"       , 62, -3.1,   3.1) );
  TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarMass"    ), "M (#bar{t}) [GeV]"    ,100,  0. , 500. ) );

  WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusPt"      ), "p_{t} (W^{-}) [GeV]",100,  0. , 500. ) );
  WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusEta"     ), "#eta (W^{-})"       ,100, -5.0,   5.0) );
  WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusRapidity"), "rapidity (W^{-})"   ,100, -5.0,   5.0) );  
  WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusPhi"     ), "#phi (W^{-})"       , 62, -3.1,   3.1) );
  WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusMass"    ), "M (W^{-}) [GeV]"    ,100,  0. , 500. ) );

  BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarPt"      ), "p_{t} (#bar{b}) [GeV]",100,  0. , 500. ) );
  BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarEta"     ), "#eta (#bar{b})"       ,100, -5.0,   5.0) );
  BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarRapidity"), "rapidity (#bar{b})"   ,100, -5.0,   5.0) );
  BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarPhi"     ), "#phi (#bar{b})"       , 62, -3.1,   3.1) );
  BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarMass"    ), "M (#bar{b}) [GeV]"    ,100,  0. , 500. ) ); 
  
  LepKin_.push_back( fs->make<TH1D>(ns.name("LepPt"      ), "p_{t} (l^{-}) [GeV]",100,  0. , 500. ) );
  LepKin_.push_back( fs->make<TH1D>(ns.name("LepEta"     ), "#eta (l^{-})"       ,100, -5.0,   5.0) );
  LepKin_.push_back( fs->make<TH1D>(ns.name("LepRapidity" ), "rapidity (l^{-})"   ,100, -5.0,   5.0) );
  LepKin_.push_back( fs->make<TH1D>(ns.name("LepPhi"     ), "#phi (l^{-})"       , 62, -3.1,   3.1) );
  LepKin_.push_back( fs->make<TH1D>(ns.name("LepMass"    ), "M (l^{-}) [GeV]"    ,100,  0. , 500. ) );
  
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarPt"      ), "p_{t} (#bar{#nu}^{-}) [GeV]",100,  0. , 500. ) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarEta"     ), "#eta (#bar{#nu}^{-})"       ,100, -5.0,   5.0) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarRapidity"), "rapidity (#bar{#nu}^{-})"   ,100, -5.0,   5.0) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarPhi"     ), "#phi (#bar{#nu}^{-})"       , 62, -3.1,   3.1) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarMass"    ), "M (#bar{#nu}^{-}) [GeV]"    ,100,  0. , 500. ) );
  
  TtBarKin_.push_back( fs->make<TH1D>(ns.name("TtBarPt"      ), "p_{t} (t#bar{t}) [GeV]",100,  0. , 500. ) );
  TtBarKin_.push_back( fs->make<TH1D>(ns.name("TtBarEta"     ), "#eta (t#bar{t})"       ,100, -5.0,   5.0) );
  TtBarKin_.push_back( fs->make<TH1D>(ns.name("TtBarRapidity"), "rapidity (t#bar{t})"   ,100, -5.0,   5.0) );
  TtBarKin_.push_back( fs->make<TH1D>(ns.name("TtBarPhi"     ), "#phi (t#bar{t})"       , 62, -3.1,   3.1) );
  TtBarKin_.push_back( fs->make<TH1D>(ns.name("TtBarMass"    ), "M (t#bar{t}) [GeV]"    ,100,  0. ,1000. ) );
  
  LepPairKin_.push_back( fs->make<TH1D>(ns.name("LepPairPt"      ), "p_{t} (l^{+}l^{-}) [GeV]",100,  0. , 500. ) );
  LepPairKin_.push_back( fs->make<TH1D>(ns.name("LepPairEta"     ), "#eta (l^{+}l^{-})"       ,100, -5.0,   5.0) );
  LepPairKin_.push_back( fs->make<TH1D>(ns.name("LepPairRapidity"), "rapidity (l^{+}l^{-})"   ,100, -5.0,   5.0) );
  LepPairKin_.push_back( fs->make<TH1D>(ns.name("LepPairPhi"     ), "#phi (l^{+}l^{-})"       , 62, -3.1,   3.1) );
  LepPairKin_.push_back( fs->make<TH1D>(ns.name("LepPairMass"    ), "M (l^{+}l^{-}) [GeV]"    ,200,  0. , 400. ) );  
  
  JetPairKin_.push_back( fs->make<TH1D>(ns.name("JetPairPt"      ), "p_{t} (jj) [GeV]",100,  0. , 500. ) );
  JetPairKin_.push_back( fs->make<TH1D>(ns.name("JetPairEta"     ), "#eta (jj)"       ,100, -5.0,   5.0) );
  JetPairKin_.push_back( fs->make<TH1D>(ns.name("JetPairRapidity"), "rapidity (jj)"   ,100, -5.0,   5.0) );
  JetPairKin_.push_back( fs->make<TH1D>(ns.name("JetPairPhi"     ), "#phi (jj)"       , 62, -3.1,   3.1) );
  JetPairKin_.push_back( fs->make<TH1D>(ns.name("JetPairMass"    ), "M (jj) [GeV]"    ,100,  0. , 500. ) );    
}



/// book histograms for generated particles properties: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::bookGenHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("gen");

  TopGen_.push_back( fs->make<TH1D>(ns.name("TopPt"      ), "p_{t} (t) [GeV]",100,  0. , 500. ) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopEta"     ), "#eta (t)"       ,100, -5.0,   5.0) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopRapidity"), "rapidity (t)"   ,100, -5.0,   5.0) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopPhi"     ), "#phi (t)"       , 62, -3.1,   3.1) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopMass"    ), "M (top) [GeV]"  ,100,  0. , 500. ) );

  WplusGen_.push_back( fs->make<TH1D>(ns.name("WplusPt"      ), "p_{t} (W^{+}) [GeV]",100,  0. , 500. ) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WplusEta"     ), "#eta (W^{+})"       ,100, -5.0,   5.0) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WplusRapidity"), "rapidity (W^{+})"   ,100, -5.0,   5.0) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WplusPhi"     ), "#phi (W^{+})"       , 62, -3.1,   3.1) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WplusMass"    ), "M (W^{+}) [GeV]"    ,100,  0. , 500. ) );

  BGen_.push_back( fs->make<TH1D>(ns.name("BPt"      ), "p_{t} (b) [GeV]",100,  0. , 500. ) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BEta"     ), "#eta (b)"       ,100, -5.0,   5.0) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BRapidity"), "rapidity (b)"   ,100, -5.0,   5.0) ); 
  BGen_.push_back( fs->make<TH1D>(ns.name("BPhi"     ), "#phi (b)"       , 62, -3.1,   3.1) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BMass"    ), "M (b) [GeV]"    ,100,  0. , 500. ) );
    
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarPt"      ), "p_{t} (l^{+}) [GeV]",100,  0. , 500. ) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarEta"     ), "#eta (l^{+})"       ,100, -5.0,   5.0) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarRapidity"), "rapidity (l^{+})"   ,100, -5.0,   5.0) ); 
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarPhi"     ), "#phi (l^{+})"       , 62, -3.1,   3.1) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarMass"    ), "M (l^{+}) [GeV]"    ,100,  0. , 500. ) );

  NuGen_.push_back( fs->make<TH1D>(ns.name("NuPt"      ), "p_{t} (#nu^{-}) [GeV]",100,  0. , 500. ) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuEta"     ), "#eta (#nu^{-})"	 ,100, -5.0,   5.0) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuRapidity"), "rapidity (#nu^{-})"   ,100, -5.0,   5.0) ); 
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuPhi"     ), "#phi (#nu^{-})"	 , 62, -3.1,   3.1) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuMass"    ), "M (#nu^{-}) [GeV]"	 ,100,  0. , 500. ) );

  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarPt"      ), "p_{t} (#bar{t}) [GeV]",100,  0. , 500. ) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarEta"     ), "#eta (#bar{t})"	 ,100, -5.0,   5.0) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarRapidity"), "rapidity (#bar{t})"   ,100, -5.0,   5.0) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarPhi"     ), "#phi (#bar{t})"	 , 62, -3.1,   3.1) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarMass"    ), "M (#bar{t}) [GeV]"	 ,100,  0. , 500. ) );

  WminusGen_.push_back( fs->make<TH1D>(ns.name("WminusPt"      ), "p_{t} (W^{-}) [GeV]",100,  0. , 500. ) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WminusEta"     ), "#eta (W^{-})"       ,100, -5.0,   5.0) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WminusRapidity"), "rapidity (W^{-})"   ,100, -5.0,   5.0) );  
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WminusPhi"     ), "#phi (W^{-})"       , 62, -3.1,   3.1) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WminusMass"    ), "M (W^{-}) [GeV]"    ,100,  0. , 500. ) );

  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarPt"	   ), "p_{t} (#bar{b}) [GeV]",100,  0. , 500. ) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarEta"     ), "#eta (#bar{b})"       ,100, -5.0,   5.0) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarRapidity"), "rapidity (#bar{b})"   ,100, -5.0,   5.0) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarPhi"     ), "#phi (#bar{b})"       , 62, -3.1,   3.1) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarMass"    ), "M (#bar{b}) [GeV]"    ,100,  0. , 500. ) );
  
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepPt"	 ), "p_{t} (l^{-}) [GeV]",100,  0. , 500. ) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepEta"	 ), "#eta (l^{-})"	 ,100, -5.0,   5.0) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepRapidity"), "rapidity (l^{-})"   ,100, -5.0,   5.0) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepPhi"	 ), "#phi (l^{-})"	 , 62, -3.1,   3.1) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepMass"	 ), "M (l^{-}) [GeV]"	 ,100,  0. , 500. ) );
  
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarPt"      ), "p_{t} (#bar{#nu}^{-}) [GeV]",100,  0. , 500. ) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarEta"     ), "#eta (#bar{#nu}^{-})"       ,100, -5.0,   5.0) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarRapidity"), "rapidity (#bar{#nu}^{-})"   ,100, -5.0,   5.0) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarPhi"     ), "#phi (#bar{#nu}^{-})"       , 62, -3.1,   3.1) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarMass"    ), "M (#bar{#nu}^{-}) [GeV]"    ,100,  0. , 500. ) );
  
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarPt"      ), "p_{t} (t#bar{t}) [GeV]",100,  0. , 500. ) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarEta"     ), "#eta (t#bar{t})"	,100, -5.0,   5.0) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarRapidity"), "rapidity (t#bar{t})"	,100, -5.0,   5.0) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarPhi"     ), "#phi (t#bar{t})"	, 62, -3.1,   3.1) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarMass"    ), "M (t#bar{t}) [GeV]"	,100,  0. ,1000. ) );
  
  LepPairGen_.push_back( fs->make<TH1D>(ns.name("LepPairPt"	 ), "p_{t} (l^{+}l^{-}) [GeV]",100,  0. , 500. ) );
  LepPairGen_.push_back( fs->make<TH1D>(ns.name("LepPairEta"	 ), "#eta (l^{+}l^{-})"       ,100, -5.0,   5.0) );
  LepPairGen_.push_back( fs->make<TH1D>(ns.name("LepPairRapidity"), "rapidity (l^{+}l^{-})"   ,100, -5.0,   5.0) );
  LepPairGen_.push_back( fs->make<TH1D>(ns.name("LepPairPhi"	 ), "#phi (l^{+}l^{-})"       , 62, -3.1,   3.1) );
  LepPairGen_.push_back( fs->make<TH1D>(ns.name("LepPairMass"	 ), "M (l^{+}l^{-}) [GeV]"    ,200,  0. , 400. ) );
  
  JetPairGen_.push_back( fs->make<TH1D>(ns.name("JetPairPt"	 ), "p_{t} (jj) [GeV]",100,  0. , 500. ) );
  JetPairGen_.push_back( fs->make<TH1D>(ns.name("JetPairEta"	 ), "#eta (jj)"       ,100, -5.0,   5.0) );
  JetPairGen_.push_back( fs->make<TH1D>(ns.name("JetPairRapidity"), "rapidity (jj)"   ,100, -5.0,   5.0) );  
  JetPairGen_.push_back( fs->make<TH1D>(ns.name("JetPairPhi"	 ), "#phi (jj)"       , 62, -3.1,   3.1) );
  JetPairGen_.push_back( fs->make<TH1D>(ns.name("JetPairMass"	 ), "M (jj) [GeV]"    ,100,  0. , 500. ) );	  
}



/// book histograms for pull distributions of particle properties: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::bookPullHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("pull");

  TopPull_.push_back( fs->make<TH1D>(ns.name("TopPt"	  ), "p_{t} (t) [GeV]", 100,  -1 , 1. ) );
  TopPull_.push_back( fs->make<TH1D>(ns.name("TopEta"	  ), "#eta (t)"       , 100,  -1 , 1. ) );
  TopPull_.push_back( fs->make<TH1D>(ns.name("TopRapidity"), "rapidity (t)"  ,  100,  -1 , 1. ) ); 
  TopPull_.push_back( fs->make<TH1D>(ns.name("TopPhi"	  ), "#phi (t)"       , 100,  -1 , 1. ) );
  TopPull_.push_back( fs->make<TH1D>(ns.name("TopMass"    ), "M (top) [GeV]"  , 100,  -1 , 1. ) );

  WplusPull_.push_back( fs->make<TH1D>(ns.name("WplusPt"      ), "p_{t} (W^{+}) [GeV]", 100,  -1 , 1. ) );
  WplusPull_.push_back( fs->make<TH1D>(ns.name("WplusEta"     ), "#eta (W^{+})"       , 100,  -1 , 1. ) );
  WplusPull_.push_back( fs->make<TH1D>(ns.name("WplusRapidity"), "rapidity (W^{+})"   , 100,  -1 , 1. ) );  
  WplusPull_.push_back( fs->make<TH1D>(ns.name("WplusPhi"     ), "#phi (W^{+})"       , 100,  -1 , 1. ) );
  WplusPull_.push_back( fs->make<TH1D>(ns.name("WplusMass"    ), "M (W^{+}) [GeV]"    , 100,  -1 , 1. ) );

  BPull_.push_back( fs->make<TH1D>(ns.name("BPt"      ), "p_{t} (b) [GeV]", 100,  -1 , 1. ) );
  BPull_.push_back( fs->make<TH1D>(ns.name("BEta"     ), "#eta (b)"	  , 100,  -1 , 1. ) );
  BPull_.push_back( fs->make<TH1D>(ns.name("BRapidity"), "rapidity (b)"   , 100,  -1 , 1. ) );  
  BPull_.push_back( fs->make<TH1D>(ns.name("BPhi"     ), "#phi (b)"	  , 100,  -1 , 1. ) );
  BPull_.push_back( fs->make<TH1D>(ns.name("BMass"    ), "M (b) [GeV]"    , 100,  -1 , 1. ) );
    
  LepBarPull_.push_back( fs->make<TH1D>(ns.name("LepBarPt"	), "p_{t} (l^{+}) [GeV]", 100,  -1 , 1. ) );
  LepBarPull_.push_back( fs->make<TH1D>(ns.name("LepBarEta"	), "#eta (l^{+})"	, 100,  -1 , 1. ) );
  LepBarPull_.push_back( fs->make<TH1D>(ns.name("LepBarRapidity"), "rapidity (l^{+})"	, 100,  -1 , 1. ) );  
  LepBarPull_.push_back( fs->make<TH1D>(ns.name("LepBarPhi"	), "#phi (l^{+})"	, 100,  -1 , 1. ) );
  LepBarPull_.push_back( fs->make<TH1D>(ns.name("LepBarMass"	), "M (l^{+}) [GeV]"	, 100,  -1 , 1. ) );

  NuPull_.push_back( fs->make<TH1D>(ns.name("NuPt"	), "p_{t} (#nu^{-}) [GeV]", 100,  -1 , 1. ) );
  NuPull_.push_back( fs->make<TH1D>(ns.name("NuEta"	), "#eta (#nu^{-})"	  , 100,  -1 , 1. ) );
  NuPull_.push_back( fs->make<TH1D>(ns.name("NuRapidity"), "#eta (#nu^{-})"	  , 100,  -1 , 1. ) );  
  NuPull_.push_back( fs->make<TH1D>(ns.name("NuPhi"	), "#phi (#nu^{-})"	  , 100,  -1 , 1. ) );
  NuPull_.push_back( fs->make<TH1D>(ns.name("NuMass"	), "M (#nu^{-}) [GeV]"    , 100,  -1 , 1. ) );

  TopBarPull_.push_back( fs->make<TH1D>(ns.name("TopBarPt"	), "p_{t} (#bar{t}) [GeV]", 100,  -1 , 1. ) );
  TopBarPull_.push_back( fs->make<TH1D>(ns.name("TopBarEta"	), "#eta (#bar{t})"	  , 100,  -1 , 1. ) );
  TopBarPull_.push_back( fs->make<TH1D>(ns.name("TopBarRapidity"), "rapidity (#bar{t})"   , 100,  -1 , 1. ) );  
  TopBarPull_.push_back( fs->make<TH1D>(ns.name("TopBarPhi"	), "#phi (#bar{t})"	  , 100,  -1 , 1. ) );
  TopBarPull_.push_back( fs->make<TH1D>(ns.name("TopBarMass"	), "M (#bar{t}) [GeV]"    , 100,  -1 , 1. ) );

  WminusPull_.push_back( fs->make<TH1D>(ns.name("WminusPt"	), "p_{t} (W^{-}) [GeV]", 100,  -1 , 1. ) ); 
  WminusPull_.push_back( fs->make<TH1D>(ns.name("WminusEta"	), "#eta (W^{-})"	, 100,  -1 , 1. ) );
  WminusPull_.push_back( fs->make<TH1D>(ns.name("WminusRapidity"), "rapidity (W^{-})"	, 100,  -1 , 1. ) );   
  WminusPull_.push_back( fs->make<TH1D>(ns.name("WminusPhi"	), "#phi (W^{-})"	, 100,  -1 , 1. ) ); 
  WminusPull_.push_back( fs->make<TH1D>(ns.name("WminusMass"	), "M (W^{-}) [GeV]"	, 100,  -1 , 1. ) ); 

  BBarPull_.push_back( fs->make<TH1D>(ns.name("BBarPt"      ), "p_{t} (#bar{b}) [GeV]", 100,  -1 , 1. ) ); 
  BBarPull_.push_back( fs->make<TH1D>(ns.name("BBarEta"     ), "#eta (#bar{b})"       , 100,  -1 , 1. ) );
  BBarPull_.push_back( fs->make<TH1D>(ns.name("BBarRapidity"), "rapidity (#bar{b})"   , 100,  -1 , 1. ) );  
  BBarPull_.push_back( fs->make<TH1D>(ns.name("BBarPhi"     ), "#phi (#bar{b})"       , 100,  -1 , 1. ) );
  BBarPull_.push_back( fs->make<TH1D>(ns.name("BBarMass"    ), "M (#bar{b}) [GeV]"    , 100,  -1 , 1. ) );
  
  LepPull_.push_back( fs->make<TH1D>(ns.name("LepPt"	  ), "p_{t} (l^{-}) [GeV]", 100,  -1 , 1. ) );
  LepPull_.push_back( fs->make<TH1D>(ns.name("LepEta"	  ), "#eta (l^{-})"	  , 100,  -1 , 1. ) );
  LepPull_.push_back( fs->make<TH1D>(ns.name("LepRapidity"), "rapidity (l^{-})"   , 100,  -1 , 1. ) );  
  LepPull_.push_back( fs->make<TH1D>(ns.name("LepPhi"	  ), "#phi (l^{-})"	  , 100,  -1 , 1. ) );
  LepPull_.push_back( fs->make<TH1D>(ns.name("LepMass"    ), "M (l^{-}) [GeV]"    , 100,  -1 , 1. ) );
  
  NuBarPull_.push_back( fs->make<TH1D>(ns.name("NuBarPt"      ), "p_{t} (#bar{#nu}^{-}) [GeV]", 100,  -1 , 1. ) );
  NuBarPull_.push_back( fs->make<TH1D>(ns.name("NuBarEta"     ), "#eta (#bar{#nu}^{-})"       , 100,  -1 , 1. ) );
  NuBarPull_.push_back( fs->make<TH1D>(ns.name("NuBarRapidity"), "rapidity (#bar{#nu}^{-})"   , 100,  -1 , 1. ) );  
  NuBarPull_.push_back( fs->make<TH1D>(ns.name("NuBarPhi"     ), "#phi (#bar{#nu}^{-})"       , 100,  -1 , 1. ) );
  NuBarPull_.push_back( fs->make<TH1D>(ns.name("NuBarMass"    ), "M (#bar{#nu}^{-}) [GeV]"    , 100,  -1 , 1. ) );
    
  TtBarPull_.push_back( fs->make<TH1D>(ns.name("TtBarPt"      ), "p_{t} (t#bar{t}) [GeV]", 100,  -1 , 1. ) );
  TtBarPull_.push_back( fs->make<TH1D>(ns.name("TtBarEta"     ), "#eta (t#bar{t})"	 , 100,  -1 , 1. ) );
  TtBarPull_.push_back( fs->make<TH1D>(ns.name("TtBarRapidity"), "rapidity (t#bar{t})"   , 100,  -1 , 1. ) );  
  TtBarPull_.push_back( fs->make<TH1D>(ns.name("TtBarPhi"     ), "#phi (t#bar{t})"	 , 100,  -1 , 1. ) );
  TtBarPull_.push_back( fs->make<TH1D>(ns.name("TtBarMass"    ), "M (t#bar{t}) [GeV]"	 , 100,  -1 , 1. ) );
  
  LepPairPull_.push_back( fs->make<TH1D>(ns.name("LepPairPt"	  ), "p_{t} (l^{+}l^{-}) [GeV]", 100,  -1 , 1. ) );
  LepPairPull_.push_back( fs->make<TH1D>(ns.name("LepPairEta"	  ), "#eta (l^{+}l^{-})"       , 100,  -1 , 1. ) );
  LepPairPull_.push_back( fs->make<TH1D>(ns.name("LepPairRapidity"), "rapidity (l^{+}l^{-})"   , 100,  -1 , 1. ) );  
  LepPairPull_.push_back( fs->make<TH1D>(ns.name("LepPairPhi"	  ), "#phi (l^{+}l^{-})"       , 100,  -1 , 1. ) );
  LepPairPull_.push_back( fs->make<TH1D>(ns.name("LepPairMass"    ), "M (l^{+}l^{-}) [GeV]"    , 100,  -1 , 1. ) );
  
  JetPairPull_.push_back( fs->make<TH1D>(ns.name("JetPairPt"	  ), "p_{t} (jj) [GeV]", 100,  -1 , 1. ) );
  JetPairPull_.push_back( fs->make<TH1D>(ns.name("JetPairEta"	  ), "#eta (jj)"       , 100,  -1 , 1. ) );
  JetPairPull_.push_back( fs->make<TH1D>(ns.name("JetPairRapidity"), "rapidity (jj)"   , 100,  -1 , 1. ) );  
  JetPairPull_.push_back( fs->make<TH1D>(ns.name("JetPairPhi"	  ), "#phi (jj)"       , 100,  -1 , 1. ) );
  JetPairPull_.push_back( fs->make<TH1D>(ns.name("JetPairMass"    ), "M (jj) [GeV]"    , 100,  -1 , 1. ) );  
    
  TopPull2D_     = fs->make<TH2D>(ns.name("TopPull2D"),    "TopPull2D",     50, -1, 1, 50, -1, 1);
  WplusPull2D_   = fs->make<TH2D>(ns.name("WplusPull2D"),  "WplusPull2D",   50, -1, 1, 50, -1, 1);
  BPull2D_       = fs->make<TH2D>(ns.name("BPull2D"),      "BPull2D",       50, -1, 1, 50, -1, 1);
  LepBarPull2D_  = fs->make<TH2D>(ns.name("LepBarPull2D"), "LepBarPull2D",  50, -1, 1, 50, -1, 1);
  NuPull2D_      = fs->make<TH2D>(ns.name("NuPull2D"),     "NuPull2D",      50, -1, 1, 50, -1, 1);
    
  TopBarPull2D_  = fs->make<TH2D>(ns.name("TopBarPull2D"), "TopBarPull2D", 50, -1, 1, 50, -1, 1);
  WminusPull2D_  = fs->make<TH2D>(ns.name("WminusPull2D"), "WminusPull2D", 50, -1, 1, 50, -1, 1);
  BBarPull2D_    = fs->make<TH2D>(ns.name("BBarPull2D"),   "BBarPull2D",   50, -1, 1, 50, -1, 1);
  LepPull2D_     = fs->make<TH2D>(ns.name("LepPull2D"),    "LepPull2D",    50, -1, 1, 50, -1, 1);
  NuBarPull2D_   = fs->make<TH2D>(ns.name("NuBarPull2D"),  "NuBarPull2D",  50, -1, 1, 50, -1, 1);
   
  TtBarPull2D_     = fs->make<TH2D>(ns.name("TtBarPull2D"),     "TtBarPull2D", 50, -1, 1, 50, -1, 1);  
  LepPairPull2D_ = fs->make<TH2D>(ns.name("LepPairPull2D"), "LepPairPull2D",   50, -1, 1, 50, -1, 1);
  JetPairPull2D_ = fs->make<TH2D>(ns.name("JetPairPull2D"), "JetPairPull2D",   50, -1, 1, 50, -1, 1);    
  	 
}



/// book histograms for 2D distributions of particle properties: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::book2DHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("2D");

  Top2D_.push_back( fs->make<TH2D>(ns.name("TopPt"	), "p_{t} (t) [GeV]",100,   0., 500. ,100,  0. , 500. ) );
  Top2D_.push_back( fs->make<TH2D>(ns.name("TopEta"	), "#eta (t)"	    ,100,  -5.,   5. ,100, -5. ,   5. ) );
  Top2D_.push_back( fs->make<TH2D>(ns.name("TopRapidity"), "rapidity (t)"   ,100,  -5.,   5. ,100, -5. ,   5. ) ); 
  Top2D_.push_back( fs->make<TH2D>(ns.name("TopPhi"	), "#phi (t)"	    , 62, -3.1,   3.1, 62, -3.1,   3.1) );   
  Top2D_.push_back( fs->make<TH2D>(ns.name("TopMass"	), "M (top) [GeV]"  , 50,   0., 500.,  50,  0. , 500. ) );

  Wplus2D_.push_back( fs->make<TH2D>(ns.name("WplusPt"      ), "p_{t} (W^{+}) [GeV]",100,   0., 500. ,100,  0. , 500. ) );
  Wplus2D_.push_back( fs->make<TH2D>(ns.name("WplusEta"     ), "#eta (W^{+})"	    ,100,  -5.,   5. ,100, -5. ,   5. ) );
  Wplus2D_.push_back( fs->make<TH2D>(ns.name("WplusRapidity"), "rapidity (W^{+})"   ,100,  -5.,   5. ,100, -5. ,   5. ) ); 
  Wplus2D_.push_back( fs->make<TH2D>(ns.name("WplusPhi"     ), "#phi (W^{+})"	    , 62, -3.1,   3.1, 62, -3.1,   3.1) ); 

  B2D_.push_back( fs->make<TH2D>(ns.name("BPt"      ), "p_{t} (b) [GeV]",100,	0., 500. ,100,  0. , 500. ) );
  B2D_.push_back( fs->make<TH2D>(ns.name("BEta"     ), "#eta (b)"	,100,  -5.,   5. ,100, -5. ,   5. ) );
  B2D_.push_back( fs->make<TH2D>(ns.name("BRapidity"), "rapidity (b)"	,100,  -5.,   5. ,100, -5. ,   5. ) ); 
  B2D_.push_back( fs->make<TH2D>(ns.name("BPhi"     ), "#phi (b)"	, 62, -3.1,   3.1, 62, -3.1,   3.1) );    
    
  LepBar2D_.push_back( fs->make<TH2D>(ns.name("LepBarPt"      ), "p_{t} (l^{+}) [GeV]",100,  0., 500. ,100,  0. , 500. ) );
  LepBar2D_.push_back( fs->make<TH2D>(ns.name("LepBarEta"     ), "#eta (l^{+})"       ,100, -5.,   5. ,100, -5. ,   5. ) );
  LepBar2D_.push_back( fs->make<TH2D>(ns.name("LepBarRapidity"), "rapidity (l^{+})"   ,100, -5.,   5. ,100, -5. ,   5. ) ); 
  LepBar2D_.push_back( fs->make<TH2D>(ns.name("LepBarPhi"     ), "#phi (l^{+})"       , 62, -3.1,  3.1, 62, -3.1,   3.1) ); 

  Nu2D_.push_back( fs->make<TH2D>(ns.name("NuPt"      ), "p_{t} (#nu^{-}) [GeV]",100,	0., 500. ,100,  0. , 500. ) );
  Nu2D_.push_back( fs->make<TH2D>(ns.name("NuEta"     ), "#eta (#nu^{-})"	,100,  -5.,   5. ,100, -5. ,   5. ) );
  Nu2D_.push_back( fs->make<TH2D>(ns.name("NuRapidity"), "rapidity (#nu^{-})"	,100,  -5.,   5. ,100, -5. ,   5. ) );
  Nu2D_.push_back( fs->make<TH2D>(ns.name("NuPhi"     ), "#phi (#nu^{-})"	, 62, -3.1,   3.1, 62, -3.1,   3.1) );

  TopBar2D_.push_back( fs->make<TH2D>(ns.name("TopBarPt"      ), "p_{t} (#bar{t}) [GeV]",100,	0., 500. ,100,  0. , 500. ) );
  TopBar2D_.push_back( fs->make<TH2D>(ns.name("TopBarEta"     ), "#eta (#bar{t})"	,100,  -5.,   5. ,100, -5. ,   5. ) );
  TopBar2D_.push_back( fs->make<TH2D>(ns.name("TopBarRapidity"), "rapidity (#bar{t})"	,100,  -5.,   5. ,100, -5. ,   5. ) ); 
  TopBar2D_.push_back( fs->make<TH2D>(ns.name("TopBarPhi"     ), "#phi (#bar{t})"	, 62, -3.1,   3.1, 62, -3.1,   3.1) );   
  TopBar2D_.push_back( fs->make<TH2D>(ns.name("TopBarMass"    ), "M (#bar{t}) [GeV]"	, 50,	0., 500.,  50,  0. , 500. ) );

  Wminus2D_.push_back( fs->make<TH2D>(ns.name("WminusPt"      ), "p_{t} (W^{-}) [GeV]",100,  0., 500. ,100,  0. , 500. ) );
  Wminus2D_.push_back( fs->make<TH2D>(ns.name("WminusEta"     ), "#eta (W^{-})"       ,100, -5.,   5. ,100, -5. ,   5. ) );
  Wminus2D_.push_back( fs->make<TH2D>(ns.name("WminusRapidity"), "rapidity (W^{-})"   ,100, -5.,   5. ,100, -5. ,   5. ) ); 
  Wminus2D_.push_back( fs->make<TH2D>(ns.name("WminusPhi"     ), "#phi (W^{-})"       , 62, -3.1,  3.1, 62, -3.1,   3.1) ); 

  BBar2D_.push_back( fs->make<TH2D>(ns.name("BBarPt"	  ), "p_{t} (#bar{b}) [GeV]",100,  0., 500. ,100,  0. , 500. ) );
  BBar2D_.push_back( fs->make<TH2D>(ns.name("BBarEta"	  ), "#eta (#bar{b})"	    ,100, -5.,   5. ,100, -5. ,   5. ) );
  BBar2D_.push_back( fs->make<TH2D>(ns.name("BBarRapidity"), "rapidity (#bar{b})"   ,100, -5.,   5. ,100, -5. ,   5. ) );   
  BBar2D_.push_back( fs->make<TH2D>(ns.name("BBarPhi"	  ), "#phi (#bar{b})"	    , 62, -3.1,  3.1, 62, -3.1,   3.1) );    
  
  Lep2D_.push_back( fs->make<TH2D>(ns.name("LepPt"	), "p_{t} (l^{-}) [GeV]",100,  0., 500. ,100,  0. , 500. ) );
  Lep2D_.push_back( fs->make<TH2D>(ns.name("LepEta"	), "#eta (l^{-})"	,100, -5.,   5. ,100, -5. ,   5. ) );
  Lep2D_.push_back( fs->make<TH2D>(ns.name("LepRapidity"), "rapidity (l^{-})"	,100, -5.,   5. ,100, -5. ,   5. ) );	
  Lep2D_.push_back( fs->make<TH2D>(ns.name("LepPhi"	), "#phi (l^{-})"	, 62, -3.1,  3.1, 62, -3.1,   3.1) );	
  
  NuBar2D_.push_back( fs->make<TH2D>(ns.name("NuBarPt"      ), "p_{t} (#bar{#nu}^{-}) [GeV]",100,  0., 500. ,100,  0. , 500. ) );
  NuBar2D_.push_back( fs->make<TH2D>(ns.name("NuBarEta"     ), "#eta (#bar{#nu}^{-})"	    ,100, -5.,   5. ,100, -5. ,   5. ) );
  NuBar2D_.push_back( fs->make<TH2D>(ns.name("NuBarRapidity"), "rapidity (#bar{#nu}^{-})"   ,100, -5.,   5. ,100, -5. ,   5. ) ); 
  NuBar2D_.push_back( fs->make<TH2D>(ns.name("NuBarPhi"     ), "#phi (#bar{#nu}^{-})"	    , 62, -3.1,  3.1, 62, -3.1,   3.1) );   
    
  TtBar2D_.push_back( fs->make<TH2D>(ns.name("TtBarPt"      ), "p_{t} (t#bar{t}) [GeV]",100,  0., 500. ,100,  0. , 500. ) );
  TtBar2D_.push_back( fs->make<TH2D>(ns.name("TtBarEta"     ), "#eta (t#bar{t})"       ,100, -5.,   5. ,100, -5. ,   5. ) );
  TtBar2D_.push_back( fs->make<TH2D>(ns.name("TtBarRapidity"), "rapidity (t#bar{t})"   ,100, -5.,   5. ,100, -5. ,   5. ) );  
  TtBar2D_.push_back( fs->make<TH2D>(ns.name("TtBarPhi"     ), "#phi (t#bar{t})"       , 62, -3.1,  3.1, 62, -3.1,   3.1) );	
  TtBar2D_.push_back( fs->make<TH2D>(ns.name("TtBarMass"    ), "M (t#bar{t}) [GeV]"    ,100,  0.,1000. ,100,  0. ,1000. ) );
  
  LepPair2D_.push_back( fs->make<TH2D>(ns.name("LepPairPt"	), "p_{t} (l^{+}l^{-}) [GeV]",100,  0., 500. ,100,  0. , 500. ) );
  LepPair2D_.push_back( fs->make<TH2D>(ns.name("LepPairEta"	), "#eta (l^{+}l^{-})"       ,100, -5.,   5. ,100, -5. ,   5. ) );
  LepPair2D_.push_back( fs->make<TH2D>(ns.name("LepPairRapidity"), "rapidity (l^{+}l^{-})"   ,100, -5.,   5. ,100, -5. ,   5. ) );
  LepPair2D_.push_back( fs->make<TH2D>(ns.name("LepPairPhi"	), "#phi (l^{+}l^{-})"       , 62, -3.1,  3.1, 62, -3.1,   3.1) ); 
  LepPair2D_.push_back( fs->make<TH2D>(ns.name("LepPairMass"	), "M (l^{+}l^{-}) [GeV]"    ,200,  0., 400. ,200,  0. , 400. ) );
  
  JetPair2D_.push_back( fs->make<TH2D>(ns.name("JetPairPt"	), "p_{t} (jj) [GeV]",100,  0., 500. ,100,  0. , 500. ) );
  JetPair2D_.push_back( fs->make<TH2D>(ns.name("JetPairEta"	), "#eta (jj)"       ,100, -5.,   5. ,100, -5. ,   5. ) );
  JetPair2D_.push_back( fs->make<TH2D>(ns.name("JetPairRapidity"), "rapidity (jj)"   ,100, -5.,   5. ,100, -5. ,   5. ) );
  JetPair2D_.push_back( fs->make<TH2D>(ns.name("JetPairPhi"	), "#phi (jj)"       , 62, -3.1,  3.1, 62, -3.1,   3.1) );    
  JetPair2D_.push_back( fs->make<TH2D>(ns.name("JetPairMass"	), "M (jj) [GeV]"    , 50,  0., 500. , 50,  0. , 500. ) );	       
}


/// book histograms for 2D correlations between reconstructed quantities
void
FullLepKinAnalyzer::bookRecCorrelHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("correlation");
  diLeptonMassVsLeptonPt_     = fs->make<TH2D>(ns.name("diLeptonMassVsLeptonPt"),     "", 200,  0. , 400. , 100,  0. , 500. );
  diLeptonMassVsLeptonEta_    = fs->make<TH2D>(ns.name("diLeptonMassVsLeptonEta"),    "", 200,  0. , 400. , 100, -5.0,   5.0);
  diLeptonMassVsDiLeptonPt_   = fs->make<TH2D>(ns.name("diLeptonMassVsDiLeptonPt"),   "", 200,  0. , 400. , 100,  0. , 500. );
  diLeptonMassVsTopPt_        = fs->make<TH2D>(ns.name("diLeptonMassVsTopPt"),        "", 200,  0. , 400. , 100,  0. , 500. );
  diLeptonMassVsTopRapidity_  = fs->make<TH2D>(ns.name("diLeptonMassVsTopRapidity"),  "", 200,  0. , 400. , 100, -5.0,   5.0);
  diLeptonMassVsTtBarPt_      = fs->make<TH2D>(ns.name("diLeptonMassVsTtBarPt"),      "", 200,  0. , 400. , 100,  0. , 500. );     
  diLeptonMassVsTtBarRapidity_= fs->make<TH2D>(ns.name("diLeptonMassVsTtBarRapidity"),"", 200,  0. , 400. , 100, -5.0,   5.0);
  diLeptonMassVsTtBarMass_    = fs->make<TH2D>(ns.name("diLeptonMassVsTtBarMass"),    "", 200,  0. , 400. , 100,  0. ,1000. );

  nBtagsTCHELVsLeptonPt_     = fs->make<TH2D>(ns.name("nBtagsTCHELVsLeptonPt"),       "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsTCHELVsLeptonEta_    = fs->make<TH2D>(ns.name("nBtagsTCHELVsLeptonEta"),      "", 5, -0.5, 4.5 , 100, -5.0,   5.0);
  nBtagsTCHELVsDiLeptonPt_   = fs->make<TH2D>(ns.name("nBtagsTCHELVsDiLeptonPt"),     "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsTCHELVsDiLeptonMass_ = fs->make<TH2D>(ns.name("nBtagsTCHELVsDiLeptonMass"),   "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsTCHELVsTopPt_        = fs->make<TH2D>(ns.name("nBtagsTCHELVsTopPt"),          "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsTCHELVsTopRapidity_  = fs->make<TH2D>(ns.name("nBtagsTCHELVsTopRapidity"),    "", 5, -0.5, 4.5 , 100, -5.0,   5.0);
  nBtagsTCHELVsTtBarPt_      = fs->make<TH2D>(ns.name("nBtagsTCHELVsTtBarPt"),        "", 5, -0.5, 4.5 , 100,  0. , 500. );   
  nBtagsTCHELVsTtBarRapidity_= fs->make<TH2D>(ns.name("nBtagsTCHELVsTtBarRapidity"),  "", 5, -0.5, 4.5 , 100, -5.0,   5.0);
  nBtagsTCHELVsTtBarMass_    = fs->make<TH2D>(ns.name("nBtagsTCHELVsTtBarMass"),      "", 5, -0.5, 4.5 , 100,  0. ,1000. );

  nBtagsTCHEMVsLeptonPt_     = fs->make<TH2D>(ns.name("nBtagsTCHEMVsLeptonPt"),       "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsTCHEMVsLeptonEta_    = fs->make<TH2D>(ns.name("nBtagsTCHEMVsLeptonEta"),      "", 5, -0.5, 4.5 , 100, -5.0,   5.0);
  nBtagsTCHEMVsDiLeptonPt_   = fs->make<TH2D>(ns.name("nBtagsTCHEMVsDiLeptonPt"),     "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsTCHEMVsDiLeptonMass_ = fs->make<TH2D>(ns.name("nBtagsTCHEMVsDiLeptonMass"),   "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsTCHEMVsTopPt_        = fs->make<TH2D>(ns.name("nBtagsTCHEMVsTopPt"),          "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsTCHEMVsTopRapidity_  = fs->make<TH2D>(ns.name("nBtagsTCHEMVsTopRapidity"),    "", 5, -0.5, 4.5 , 100, -5.0,   5.0);
  nBtagsTCHEMVsTtBarPt_      = fs->make<TH2D>(ns.name("nBtagsTCHEMVsTtBarPt"),        "", 5, -0.5, 4.5 , 100,  0. , 500. );	
  nBtagsTCHEMVsTtBarRapidity_= fs->make<TH2D>(ns.name("nBtagsTCHEMVsTtBarRapidity"),  "", 5, -0.5, 4.5 , 100, -5.0,   5.0);
  nBtagsTCHEMVsTtBarMass_    = fs->make<TH2D>(ns.name("nBtagsTCHEMVsTtBarMass"),      "", 5, -0.5, 4.5 , 100,  0. ,1000. );

  nBtagsSSVHEMVsLeptonPt_     = fs->make<TH2D>(ns.name("nBtagsSSVHEMVsLeptonPt"),     "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsSSVHEMVsLeptonEta_    = fs->make<TH2D>(ns.name("nBtagsSSVHEMVsLeptonEta"),    "", 5, -0.5, 4.5 , 100, -5.0,   5.0);
  nBtagsSSVHEMVsDiLeptonPt_   = fs->make<TH2D>(ns.name("nBtagsSSVHEMVsDiLeptonPt"),   "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsSSVHEMVsDiLeptonMass_ = fs->make<TH2D>(ns.name("nBtagsSSVHEMVsDiLeptonMass"), "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsSSVHEMVsTopPt_        = fs->make<TH2D>(ns.name("nBtagsSSVHEMVsTopPt"),        "", 5, -0.5, 4.5 , 100,  0. , 500. );
  nBtagsSSVHEMVsTopRapidity_  = fs->make<TH2D>(ns.name("nBtagsSSVHEMVsTopRapidity"),  "", 5, -0.5, 4.5 , 100, -5.0,   5.0);
  nBtagsSSVHEMVsTtBarPt_      = fs->make<TH2D>(ns.name("nBtagsSSVHEMVsTtBarPt"),      "", 5, -0.5, 4.5 , 100,  0. , 500. );  
  nBtagsSSVHEMVsTtBarRapidity_= fs->make<TH2D>(ns.name("nBtagsSSVHEMVsTtBarRapidity"),"", 5, -0.5, 4.5 , 100, -5.0,   5.0);
  nBtagsSSVHEMVsTtBarMass_    = fs->make<TH2D>(ns.name("nBtagsSSVHEMVsTtBarMass"),    "", 5, -0.5, 4.5 , 100,  0. ,1000. );
}


/// book histograms for hypothesis specific histos and correlations between hypotheses
void
FullLepKinAnalyzer::bookQualityHistos(edm::Service<TFileService>& fs)
{
  NameScheme ns("qual");
  
  kinSolWeight_        = fs->make<TH1D>(ns.name("kinSolWeight"        ), "Weight of kin solution",           50,  0. , 1. ); 
  bJetIdcs_            = fs->make<TH1D>(ns.name("bJetIdcs"            ), "b jet indices used for hypo"      , 4, -0.5, 3.5);
  bBarJetIdcs_         = fs->make<TH1D>(ns.name("bBarJetIdcs"         ), "bbar jet indices used for hypo"   , 4, -0.5, 3.5);
  deltaM_              = fs->make<TH1D>(ns.name("deltaM"              ), "M_{top}-M{#bar{t}}",               50, -25., 25.);
  kinTCHELcorrelation_ = fs->make<TH2D>(ns.name("kinTCHELcorrelation" ), "mass reco vs. TCHEL",        3, -0.5, 2.5, 2, -0.5, 1.5);
  kinTCHEMcorrelation_ = fs->make<TH2D>(ns.name("kinTCHEMcorrelation" ), "mass reco vs. TCHEM",        3, -0.5, 2.5, 2, -0.5, 1.5);  
  kinSSVHEMcorrelation_= fs->make<TH2D>(ns.name("kinSSVHEMcorrelation"), "mass reco vs. TCHEM",        3, -0.5, 2.5, 2, -0.5, 1.5); 
  compare_             = fs->make<TH2D>(ns.name("compare"             ), "Indices",                   24, -1.5,22.5,24, -1.5,22.5);
  
  for(int i=1; i<=24;++i){
    char label[2];
    int j = i%4-2;

    std::ostringstream oss;
    oss << j;
    strcpy(label, oss.str().c_str());

    compare_->GetXaxis()->SetBinLabel(i,label);
    compare_->GetYaxis()->SetBinLabel(i,label);
  }    
}


/// fill histograms for reconstructed or generated particle properties: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::fillKinHistos(std::vector<TH1D*>& histos, const reco::Candidate& candidate)
{
  histos[0]->Fill( candidate.pt()      ); 
  histos[1]->Fill( candidate.eta()     );
  histos[2]->Fill( candidate.rapidity());
  histos[3]->Fill( candidate.phi()     );
  histos[4]->Fill( candidate.mass()    );
}


/// fill pull histograms: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::fillPullHistos(std::vector<TH1D*>& histos, TH2D& hist2D, const reco::Candidate& candidate,  const reco::Candidate& gencandidate)
{
  histos[0]->Fill( ( candidate.pt()      - gencandidate.pt() )       / gencandidate.pt()      ); 
  histos[1]->Fill( ( candidate.eta()     - gencandidate.eta() )      / gencandidate.eta()     );
  histos[2]->Fill( ( candidate.rapidity()- gencandidate.rapidity() ) / gencandidate.rapidity());  
  histos[3]->Fill( ( candidate.phi()     - gencandidate.phi() )      / gencandidate.phi()     );
  histos[4]->Fill( ( candidate.mass()    - gencandidate.mass() )     / gencandidate.mass()    );
  
  hist2D.Fill((candidate.eta()-gencandidate.eta())/gencandidate.eta(),(candidate.phi()-gencandidate.phi())/gencandidate.phi());   
}


/// fill 2D histograms
void
FullLepKinAnalyzer::fill2DHistos(std::vector<TH2D*>& histos, const reco::Candidate& candidate,  const reco::Candidate& gencandidate)
{
  histos[0]->Fill( gencandidate.pt(),       candidate.pt()       );
  histos[1]->Fill( gencandidate.eta(),      candidate.eta()      );
  histos[2]->Fill( gencandidate.rapidity(), candidate.rapidity() );  
  histos[3]->Fill( gencandidate.phi(),      candidate.phi()      );  
  if(histos.size()>4){
    histos[4]->Fill( gencandidate.mass(),   candidate.mass()     );
  }   
}


/// fill histograms for hypothesis specific histos and correlations between hypotheses
void
FullLepKinAnalyzer::fillQualityHistos(const TtFullLeptonicEvent& FullLepEvt, 
                                             const TtEvent::HypoClassKey& hypoKey)
{
  bJetIdcs_   ->Fill(FullLepEvt.jetLeptonCombination(hypoKey)[0] );
  bBarJetIdcs_->Fill(FullLepEvt.jetLeptonCombination(hypoKey)[1] );   
  
  if( hypoKey==6 ) {
    deltaM_->Fill(FullLepEvt.top(hypoKey)->mass()-FullLepEvt.topBar(hypoKey)->mass()); 
    kinSolWeight_->Fill( FullLepEvt.solWeight() );
  } 
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( FullLepKinAnalyzer );
