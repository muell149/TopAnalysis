#include "TLorentzVector.h"
#include "TopAnalysis/TopAnalyzer/plugins/FullLepHypothesesAnalyzer.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "AnalysisDataFormats/TopObjects/interface/TtEventPartons.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

/// default constructor
FullLepHypothesesAnalyzer::FullLepHypothesesAnalyzer(const edm::ParameterSet& cfg):
  FullLepEvt_      (cfg.getParameter<edm::InputTag>("FullLepEvent"    )),
  hypoKey_         (cfg.getParameter<edm::InputTag>("hypoKey"         )), 
  wgt_             (cfg.getParameter<edm::InputTag>("weight"          )),
  useEvtWgt_       ( cfg.getParameter<bool>        ( "useEventWeight" )),   
  useWrongCharge_  (cfg.getParameter<bool>         ("alsoWrongCharge" )),
  wantSummary_     (cfg.getParameter<bool>         ("wantSummary"     ))
{
  Nava = 0;
  Nval = 0;
}

/// default destructor
FullLepHypothesesAnalyzer::~FullLepHypothesesAnalyzer()
{
}

/// everything that has to be done before the event loop: books histograms
void 
FullLepHypothesesAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  bookKinHistos      (fs);
  bookKinGenHistos   (fs);  
  bookKinResHistos   (fs);
  bookQualityHistos  (fs);
   
  NameScheme ns("correlation"); 
      
  genRecoNuComparison_    = fs->make<TH2D>(ns.name("genRecoNuComparison"   ), "Nu Pt",    100, 0., 250., 100, 0., 250.);  
  genRecoNuBarComparison_ = fs->make<TH2D>(ns.name("genRecoNuBarComparison"), "NuBar Pt", 100, 0., 250., 100, 0., 250.); 
  genRecoNuPx_    = fs->make<TH2D>(ns.name("genRecoNuPx"   ), "Nu Px",    100, -100., 100., 100, -100., 100.);  
  genRecoNuBarPx_ = fs->make<TH2D>(ns.name("genRecoNuBarPx"), "NuBar Px", 100, -100., 100., 100, -100., 100.);  
  genRecoNuPy_    = fs->make<TH2D>(ns.name("genRecoNuPy"   ), "Nu Py",    100, -100., 100., 100, -100., 100.);  
  genRecoNuBarPy_ = fs->make<TH2D>(ns.name("genRecoNuBarPy"), "NuBar Py", 100, -100., 100., 100, -100., 100.);      
}

/// everything that has to be done during the event loop: filling plots
void
FullLepHypothesesAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{

  edm::Handle<TtFullLeptonicEvent> FullLepEvt;
  evt.getByLabel(FullLepEvt_, FullLepEvt);

  edm::Handle<int> hypoKeyHandle;
  evt.getByLabel(hypoKey_, hypoKeyHandle);
  TtEvent::HypoClassKey& hypoKey = (TtEvent::HypoClassKey&) *hypoKeyHandle;

  // get weight when indicated, else weight is 1               
  double weight = 1.;
  if(useEvtWgt_){ 
    edm::Handle<double> wgt;
    evt.getByLabel(wgt_, wgt);
    weight = *wgt;
  }

  // -----------------------
  // check if hypothesis is valid in this event
  // and if it satisfies some quality criteria
  // -----------------------
         
  if( !FullLepEvt->isHypoAvailable(hypoKey) ){
    edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not available for this event";
    return;
  }
  else Nava++;
  
  if( !FullLepEvt->isHypoValid(hypoKey) )  {
    goodHypo_->Fill(0., weight); // not a good hypothesis
  }
  else goodHypo_->Fill(1., weight); // good hypothesis

  if( !FullLepEvt->isHypoValid(hypoKey) ){
     edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not valid for this event";
     return;  // return if any of the hypotheses is not valid
   }
  else Nval++;  

  // -----------------------
  // fill histos related to quality of the TtFullLeptonicEvent
  // -----------------------
  fillQualityHistos(*FullLepEvt, hypoKey, weight);

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
  
  // print run, ls and evt number as well as some kinematics
  edm::LogInfo log( "FullLepKinematics" );
  log << "Found Event\n";
  log << "-------------------------------------------\n"; 
  log << "      Run: " << evt.id().run()            << "\n";
  log << "LumiBlock: " << evt.id().luminosityBlock()<< "\n";
  log << "    Event: " << evt.id().event()          << "\n";	
  log << "-------------------------------------------\n";  
  log << " top mass: " << Top->mass()            << "\n";
  log << " top pt  : " << Top->pt()              << "\n";
  log << " top eta : " << Top->eta()             << "\n";  
  log << " top phi : " << Top->phi()             << "\n";  
  log << " tbar pt : " << TopBar->pt()           << "\n";
  log << " tbar    : " << TopBar->eta()          << "\n";  
  log << " tbar    : " << TopBar->phi()          << "\n"; 
  log << "-------------------------------------------\n"; 	 
  log << " lep+ eta: " << LepBar->eta()          << "\n";
  log << " lep+ phi: " << LepBar->phi()          << "\n";
  log << " lep+ pt : " << LepBar->pt()           << "\n";  
  log << " lep- eta: " << Lep->eta()             << "\n";
  log << " lep- phi: "  << Lep->phi()            << "\n";
  log << " lep- pt : "  << Lep->pt()             << "\n";	   
  log << "-------------------------------------------\n";  
  
  // calculate dimass    
  TLorentzVector diLepLVector = TLorentzVector(Lep->px()+LepBar->px(), Lep->py()+LepBar->py(), 
                                               Lep->pz()+LepBar->pz(), Lep->energy()+LepBar->energy());   
  double dilepMass = (diLepLVector).M(); 
  log << "dilepmass : "  << dilepMass            << "\n";      
  log << "-------------------------------------------\n";       
  log << "    b eta: " << B->eta()               << "\n";
  log << "    b phi: " << B->phi()               << "\n";
  log << "    b pt : " << B->pt()                << "\n";  
  log << " bbar eta: " << BBar->eta()            << "\n";
  log << " bbar phi: " << BBar->phi()            << "\n";
  log << " bbar pt : " << BBar->pt()             << "\n";      
  log << "-------------------------------------------\n"; 
  
      
  // re-calculate MET from neutrino pt
  double met = sqrt((Nu->momentum()+NuBar->momentum()).x()*(Nu->momentum()+NuBar->momentum()).x()
               +(Nu->momentum()+NuBar->momentum()).y()*(Nu->momentum()+NuBar->momentum()).y());
  log << " met : " << met << "\n";  
       
  if(!FullLepEvt->isWrongCharge()){
    fillKinHistos(TopKin_,    *Top,    weight);
    fillKinHistos(WplusKin_,  *Wplus,  weight);
    fillKinHistos(BKin_,      *B,      weight);
    fillKinHistos(LepBarKin_, *LepBar, weight);
    fillKinHistos(NuKin_,     *Nu,     weight);

    fillKinHistos(TopBarKin_, *TopBar, weight);
    fillKinHistos(WminusKin_, *Wminus, weight);
    fillKinHistos(BBarKin_,   *BBar,   weight);
    fillKinHistos(LepKin_,    *Lep,    weight);
    fillKinHistos(NuBarKin_,  *NuBar,  weight);
  }
  else{
    fillWrongChargeKinHistos(TopKin_,    *Top,    weight);
    fillWrongChargeKinHistos(WplusKin_,  *Wplus,  weight);
    fillWrongChargeKinHistos(BKin_,      *B,      weight);
    fillWrongChargeKinHistos(LepBarKin_, *LepBar, weight);
    fillWrongChargeKinHistos(NuKin_,     *Nu,     weight);

    fillWrongChargeKinHistos(TopBarKin_, *TopBar, weight);
    fillWrongChargeKinHistos(WminusKin_, *Wminus, weight);
    fillWrongChargeKinHistos(BBarKin_,   *BBar,   weight);
    fillWrongChargeKinHistos(LepKin_,    *Lep,    weight);
    fillWrongChargeKinHistos(NuBarKin_,  *NuBar,  weight);  
  }
  // -----------------------
  // fill resolution histos for kinematic variables
  // with respect to the generator particles
  // -----------------------
  if( !FullLepEvt->genEvent() ) return;
  if( !FullLepEvt->genEvent()->isFullLeptonic() ) return;

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


  genRecoNuComparison_   ->Fill(Nu->pt(),   genNu->pt());
  genRecoNuBarComparison_->Fill(NuBar->pt(),genNuBar->pt());  
  genRecoNuPx_           ->Fill(Nu->px(),   genNu->px());
  genRecoNuBarPx_        ->Fill(NuBar->px(),genNuBar->px());  
  genRecoNuPy_           ->Fill(Nu->py(),   genNu->py());
  genRecoNuBarPy_        ->Fill(NuBar->py(),genNuBar->py());   



  if(genTop)    fillKinGenHistos(TopKinGen_,    *genTop,    weight);
  if(genWplus)  fillKinGenHistos(WplusKinGen_,  *genWplus,  weight);
  if(genB)      fillKinGenHistos(BKinGen_,      *genB,      weight);
  if(genLepBar) fillKinGenHistos(LepBarKinGen_, *genLepBar, weight);
  if(genNu)     fillKinGenHistos(NuKinGen_,     *genNu,     weight);   

  if(genTopBar) fillKinGenHistos(TopBarKinGen_, *genTopBar, weight);
  if(genWminus) fillKinGenHistos(WminusKinGen_, *genWminus, weight);
  if(genBBar)   fillKinGenHistos(BBarKinGen_,   *genBBar,   weight);
  if(genLep)    fillKinGenHistos(LepKinGen_,    *genLep,    weight);
  if(genNuBar)  fillKinGenHistos(NuBarKinGen_,  *genNuBar,  weight);      

  if(!FullLepEvt->isWrongCharge()){
    if(genTop)    fillKinResHistos(TopKinRes_,    *Top,   *genTop,    weight);
    if(genWplus)  fillKinResHistos(WplusKinRes_,  *Wplus, *genWplus,  weight);
    if(genB)      fillKinResHistos(BKinRes_,      *B,     *genB,      weight);
    if(genLepBar) fillKinResHistos(LepBarKinRes_, *LepBar,*genLepBar, weight);
    if(genNu)     fillKinResHistos(NuKinRes_,     *Nu,    *genNu,     weight);

    if(genTopBar) fillKinResHistos(TopBarKinRes_, *TopBar,*genTopBar, weight);
    if(genWminus) fillKinResHistos(WminusKinRes_, *Wminus,*genWminus, weight);
    if(genBBar)   fillKinResHistos(BBarKinRes_,   *BBar,  *genBBar,   weight);
    if(genLep)    fillKinResHistos(LepKinRes_,    *Lep,   *genLep,    weight);
    if(genNuBar)  fillKinResHistos(NuBarKinRes_,  *NuBar, *genNuBar,  weight); 
  }
  else{ //should never be the case: right charge reconstructed as wrong charge
    if(genTop)    fillWrongChargeKinResHistos(TopKinRes_,    *Top,   *genTop,    weight);
    if(genWplus)  fillWrongChargeKinResHistos(WplusKinRes_,  *Wplus, *genWplus,  weight);
    if(genB)      fillWrongChargeKinResHistos(BKinRes_,      *B,     *genB,      weight);
    if(genLepBar) fillWrongChargeKinResHistos(LepBarKinRes_, *LepBar,*genLepBar, weight);
    if(genNu)     fillWrongChargeKinResHistos(NuKinRes_,     *Nu,    *genNu,     weight);

    if(genTopBar) fillWrongChargeKinResHistos(TopBarKinRes_, *TopBar,*genTopBar, weight);
    if(genWminus) fillWrongChargeKinResHistos(WminusKinRes_, *Wminus,*genWminus, weight);
    if(genBBar)   fillWrongChargeKinResHistos(BBarKinRes_,   *BBar,  *genBBar,   weight);
    if(genLep)    fillWrongChargeKinResHistos(LepKinRes_,    *Lep,   *genLep,    weight);
    if(genNuBar)  fillWrongChargeKinResHistos(NuBarKinRes_,  *NuBar, *genNuBar,  weight);   
  }
}

/// everything that has to be done after the event loop: summarizes if wantSummary_ is true
void
FullLepHypothesesAnalyzer::endJob() 
{
  if(!wantSummary_) return;
  
  std::cout << "++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << "Summary for Hypothese " << hypoKey_ << std::endl;
  std::cout << "number of available events is " << Nava << std::endl;
  std::cout << "number of valid events is " << Nval << std::endl;
  std::cout << "++++++++++++++++++++++++++++++++" << std::endl;
}

/// book histograms for reconstructed particles properties: Pt, E, Eta, Phi, m
/// append wrong charge histos if chosen in config
void
FullLepHypothesesAnalyzer::bookKinHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("kin");

  TopKin_.push_back( fs->make<TH1D>(ns.name("TopPt"    ), "p_{t} (t) [GeV]", 50,  0. , 500. ) );
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopEnergy"), "E (t) [GeV]"    , 50,  0. , 500. ) );  
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopEta"   ), "#eta (t)"       , 34, -3.4,   3.4) );
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopPhi"   ), "#phi (t)"       , 34, -3.4,   3.4) );
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopMass"  ), "M (top) [GeV]"  , 40,  0. , 400. ) );

  WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusPt"    ), "p_{t} (W^{+}) [GeV]", 50,  0. , 500. ) );
  WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusEnergy"), "E (W^{+}) [GeV]"    , 50,  0. , 500. ) );
  WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusEta"   ), "#eta (W^{+})"       , 34, -3.4,   3.4) );
  WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusPhi"   ), "#phi (W^{+})"       , 34, -3.4,   3.4) );
  WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusMass"  ), "M (W^{+}) [GeV]"    , 30,  0. , 600. ) );

  BKin_.push_back( fs->make<TH1D>(ns.name("BPt"    ), "p_{t} (b) [GeV]", 50,  0. , 500. ) );
  BKin_.push_back( fs->make<TH1D>(ns.name("BEnergy"), "E (b) [GeV]"    , 50,  0. , 500. ) );
  BKin_.push_back( fs->make<TH1D>(ns.name("BEta"   ), "#eta (b)"       , 34, -3.4,   3.4) );
  BKin_.push_back( fs->make<TH1D>(ns.name("BPhi"   ), "#phi (b)"       , 34, -3.4,   3.4) );
  BKin_.push_back( fs->make<TH1D>(ns.name("BMass"  ), "M (b) [GeV]"    , 30,  0. , 600. ) );
    
  LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarPt"    ), "p_{t} (l^{+}) [GeV]", 50,  0. , 500. ) );
  LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarEnergy"), "E (l^{+}) [GeV]"    , 50,  0. , 500. ) );
  LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarEta"   ), "#eta (l^{+})"       , 34, -3.4,   3.4) );
  LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarPhi"   ), "#phi (l^{+})"       , 34, -3.4,   3.4) );
  LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarMass"  ), "M (l^{+}) [GeV]"    , 30,  0. , 600. ) ); 

  NuKin_.push_back( fs->make<TH1D>(ns.name("NuPt"    ), "p_{t} (#nu^{-}) [GeV]", 50,  0. , 500. ) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuEnergy"), "E (#nu^{-}) [GeV]"    , 50,  0. , 500. ) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuEta"   ), "#eta (#nu^{-})"       , 34, -3.4,   3.4) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuPhi"   ), "#phi (#nu^{-})"       , 34, -3.4,   3.4) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuMass"  ), "M (#nu^{-}) [GeV]"    , 30,  0. , 600. ) );

  TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarPt"    ), "p_{t} (#bar{t}) [GeV]", 50,  0. , 500. ) );
  TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarEnergy"), "E (#bar{t}) [GeV]"    , 50,  0. , 500. ) );
  TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarEta"   ), "#eta (#bar{t})"       , 34, -3.4,   3.4) );
  TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarPhi"   ), "#phi (#bar{t})"       , 34, -3.4,   3.4) );
  TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarMass"  ), "M (#bar{t}) [GeV]"    , 40,  0. , 400. ) );

  WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusPt"    ), "p_{t} (W^{-}) [GeV]", 50,  0. , 500. ) );
  WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusEnergy"), "E (W^{-}) [GeV]"    , 50,  0. , 500. ) );
  WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusEta"   ), "#eta (W^{-})"       , 34, -3.4,   3.4) );
  WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusPhi"   ), "#phi (W^{-})"       , 34, -3.4,   3.4) );
  WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusMass"  ), "M (W^{-}) [GeV]"    , 30,  0. , 600. ) );

  BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarPt"    ), "p_{t} (#bar{b}) [GeV]", 50,  0. , 500. ) );
  BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarEnergy"), "E (#bar{b}) [GeV]"    , 50,  0. , 500. ) );
  BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarEta"   ), "#eta (#bar{b})"       , 34, -3.4,   3.4) );
  BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarPhi"   ), "#phi (#bar{b})"       , 34, -3.4,   3.4) );
  BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarMass"  ), "M (#bar{b}) [GeV]"    , 30,  0. , 600. ) ); 
  
  LepKin_.push_back( fs->make<TH1D>(ns.name("LepPt"    ), "p_{t} (l^{-}) [GeV]", 50,  0. , 500. ) );
  LepKin_.push_back( fs->make<TH1D>(ns.name("LepEnergy"), "E (l^{-}) [GeV]"    , 50,  0. , 500. ) );
  LepKin_.push_back( fs->make<TH1D>(ns.name("LepEta"   ), "#eta (l^{-})"       , 34, -3.4,   3.4) );
  LepKin_.push_back( fs->make<TH1D>(ns.name("LepPhi"   ), "#phi (l^{-})"       , 34, -3.4,   3.4) );
  LepKin_.push_back( fs->make<TH1D>(ns.name("LepMass"  ), "M (l^{-}) [GeV]"    , 30,  0. , 600. ) );
  
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarPt"    ), "p_{t} (#bar{#nu}^{-}) [GeV]", 50,  0. , 500. ) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarEnergy"), "E (#bar{#nu}^{-}) [GeV]"    , 50,  0. , 500. ) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarEta"   ), "#eta (#bar{#nu}^{-})"       , 34, -3.4,   3.4) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarPhi"   ), "#phi (#bar{#nu}^{-})"       , 34, -3.4,   3.4) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarMass"  ), "M (#bar{#nu}^{-}) [GeV]"    , 30,  0. , 600. ) );  
  
  // push back the same histograms for wrong charge event solutions if demanded
  if(useWrongCharge_){
    TopKin_.push_back( fs->make<TH1D>(ns.name("TopPtWrong"    ), "p_{t} (t) [GeV]", 50,  0. , 500. ) );
    TopKin_.push_back( fs->make<TH1D>(ns.name("TopEnergyWrong"), "E (t) [GeV]"    , 50,  0. , 500. ) );  
    TopKin_.push_back( fs->make<TH1D>(ns.name("TopEtaWrong"   ), "#eta (t)"       , 34, -3.4,   3.4) );
    TopKin_.push_back( fs->make<TH1D>(ns.name("TopPhiWrong"   ), "#phi (t)"       , 34, -3.4,   3.4) );
    TopKin_.push_back( fs->make<TH1D>(ns.name("TopMassWrong"  ), "M (top) [GeV]"  , 40,  0. , 400. ) );

    WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusPtWrong"    ), "p_{t} (W^{+}) [GeV]", 50,  0. , 500. ) );
    WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusEnergyWrong"), "E (W^{+}) [GeV]"    , 50,  0. , 500. ) );
    WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusEtaWrong"   ), "#eta (W^{+})"       , 34, -3.4,   3.4) );
    WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusPhiWrong"   ), "#phi (W^{+})"       , 34, -3.4,   3.4) );
    WplusKin_.push_back( fs->make<TH1D>(ns.name("WplusMassWrong"  ), "M (W^{+}) [GeV]"    , 30,  0. , 600. ) );

    BKin_.push_back( fs->make<TH1D>(ns.name("BPtWrong"    ), "p_{t} (b) [GeV]", 50,  0. , 500. ) );
    BKin_.push_back( fs->make<TH1D>(ns.name("BEnergyWrong"), "E (b) [GeV]"    , 50,  0. , 500. ) );
    BKin_.push_back( fs->make<TH1D>(ns.name("BEtaWrong"   ), "#eta (b)"       , 34, -3.4,   3.4) );
    BKin_.push_back( fs->make<TH1D>(ns.name("BPhiWrong"   ), "#phi (b)"       , 34, -3.4,   3.4) );
    BKin_.push_back( fs->make<TH1D>(ns.name("BMassWrong"  ), "M (b) [GeV]"    , 30,  0. , 600. ) );

    LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarPtWrong"    ), "p_{t} (l^{+}) [GeV]", 50,  0. , 500. ) );
    LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarEnergyWrong"), "E (l^{+}) [GeV]"    , 50,  0. , 500. ) );
    LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarEtaWrong"   ), "#eta (l^{+})"       , 34, -3.4,   3.4) );
    LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarPhiWrong"   ), "#phi (l^{+})"       , 34, -3.4,   3.4) );
    LepBarKin_.push_back( fs->make<TH1D>(ns.name("LepBarMassWrong"  ), "M (l^{+}) [GeV]"    , 30,  0. , 600. ) ); 

    NuKin_.push_back( fs->make<TH1D>(ns.name("NuPtWrong"    ), "p_{t} (#nu^{-}) [GeV]", 50,  0. , 500. ) );
    NuKin_.push_back( fs->make<TH1D>(ns.name("NuEnergyWrong"), "E (#nu^{-}) [GeV]"    , 50,  0. , 500. ) );
    NuKin_.push_back( fs->make<TH1D>(ns.name("NuEtaWrong"   ), "#eta (#nu^{-})"       , 34, -3.4,   3.4) );
    NuKin_.push_back( fs->make<TH1D>(ns.name("NuPhiWrong"   ), "#phi (#nu^{-})"       , 34, -3.4,   3.4) );
    NuKin_.push_back( fs->make<TH1D>(ns.name("NuMassWrong"  ), "M (#nu^{-}) [GeV]"    , 30,  0. , 600. ) );

    TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarPtWrong"    ), "p_{t} (#bar{t}) [GeV]", 50,  0. , 500. ) );
    TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarEnergyWrong"), "E (#bar{t}) [GeV]"    , 50,  0. , 500. ) );
    TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarEtaWrong"   ), "#eta (#bar{t})"       , 34, -3.4,   3.4) );
    TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarPhiWrong"   ), "#phi (#bar{t})"       , 34, -3.4,   3.4) );
    TopBarKin_.push_back( fs->make<TH1D>(ns.name("TopBarMassWrong"  ), "M (#bar{t}) [GeV]"    , 40,  0. , 400. ) );

    WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusPtWrong"    ), "p_{t} (W^{-}) [GeV]", 50,  0. , 500. ) );
    WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusEnergyWrong"), "E (W^{-}) [GeV]"    , 50,  0. , 500. ) );
    WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusEtaWrong"   ), "#eta (W^{-})"       , 34, -3.4,   3.4) );
    WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusPhiWrong"   ), "#phi (W^{-})"       , 34, -3.4,   3.4) );
    WminusKin_.push_back( fs->make<TH1D>(ns.name("WminusMassWrong"  ), "M (W^{-}) [GeV]"    , 30,  0. , 600. ) );

    BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarPtWrong"    ), "p_{t} (#bar{b}) [GeV]", 50,  0. , 500. ) );
    BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarEnergyWrong"), "E (#bar{b}) [GeV]"    , 50,  0. , 500. ) );
    BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarEtaWrong"   ), "#eta (#bar{b})"       , 34, -3.4,   3.4) );
    BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarPhiWrong"   ), "#phi (#bar{b})"       , 34, -3.4,   3.4) );
    BBarKin_.push_back( fs->make<TH1D>(ns.name("BBarMassWrong"  ), "M (#bar{b}) [GeV]"    , 30,  0. , 600. ) ); 

    LepKin_.push_back( fs->make<TH1D>(ns.name("LepPtWrong"    ), "p_{t} (l^{-}) [GeV]", 50,  0. , 500. ) );
    LepKin_.push_back( fs->make<TH1D>(ns.name("LepEnergyWrong"), "E (l^{-}) [GeV]"    , 50,  0. , 500. ) );
    LepKin_.push_back( fs->make<TH1D>(ns.name("LepEtaWrong"   ), "#eta (l^{-})"       , 34, -3.4,   3.4) );
    LepKin_.push_back( fs->make<TH1D>(ns.name("LepPhiWrong"   ), "#phi (l^{-})"       , 34, -3.4,   3.4) );
    LepKin_.push_back( fs->make<TH1D>(ns.name("LepMassWrong"  ), "M (l^{-}) [GeV]"    , 30,  0. , 600. ) );

    NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarPtWrong"    ), "p_{t} (#bar{#nu}^{-}) [GeV]", 50,  0. , 500. ) );
    NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarEnergyWrong"), "E (#bar{#nu}^{-}) [GeV]"    , 50,  0. , 500. ) );
    NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarEtaWrong"   ), "#eta (#bar{#nu}^{-})"       , 34, -3.4,   3.4) );
    NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarPhiWrong"   ), "#phi (#bar{#nu}^{-})"       , 34, -3.4,   3.4) );
    NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarMassWrong"  ), "M (#bar{#nu}^{-}) [GeV]"    , 30,  0. , 600. ) );    
  }
}

/// book histograms for generated particles properties: Pt, E, Eta, Phi, m
void
FullLepHypothesesAnalyzer::bookKinGenHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("gen");
  
  TopKinGen_.push_back( fs->make<TH1D>(ns.name("GenTopPt"    ), "p_{t} (t) [GeV]", 50,  0. , 500. ) );
  TopKinGen_.push_back( fs->make<TH1D>(ns.name("GenTopEnergy"), "E (t) [GeV]"    , 50,  0. , 500. ) );  
  TopKinGen_.push_back( fs->make<TH1D>(ns.name("GenTopEta"   ), "#eta (t)"       , 34, -3.4,   3.4) );
  TopKinGen_.push_back( fs->make<TH1D>(ns.name("GenTopPhi"   ), "#phi (t)"       , 34, -3.4,   3.4) );
  TopKinGen_.push_back( fs->make<TH1D>(ns.name("GenTopMass"  ), "M (top) [GeV]"  , 40,  0. , 400. ) );

  WplusKinGen_.push_back( fs->make<TH1D>(ns.name("GenWplusPt"    ), "p_{t} (W^{+}) [GeV]", 50,  0. , 500. ) );
  WplusKinGen_.push_back( fs->make<TH1D>(ns.name("GenWplusEnergy"), "E (W^{+}) [GeV]"    , 50,  0. , 500. ) );
  WplusKinGen_.push_back( fs->make<TH1D>(ns.name("GenWplusEta"   ), "#eta (W^{+})"       , 34, -3.4,   3.4) );
  WplusKinGen_.push_back( fs->make<TH1D>(ns.name("GenWplusPhi"   ), "#phi (W^{+})"       , 34, -3.4,   3.4) );
  WplusKinGen_.push_back( fs->make<TH1D>(ns.name("GenWplusMass"  ), "M (W^{+}) [GeV]"    , 30,  0. , 600. ) );

  BKinGen_.push_back( fs->make<TH1D>(ns.name("GenBPt"    ), "p_{t} (b) [GeV]", 50,  0. , 500. ) );
  BKinGen_.push_back( fs->make<TH1D>(ns.name("GenBEnergy"), "E (b) [GeV]"    , 50,  0. , 500. ) );
  BKinGen_.push_back( fs->make<TH1D>(ns.name("GenBEta"   ), "#eta (b)"       , 34, -3.4,   3.4) );
  BKinGen_.push_back( fs->make<TH1D>(ns.name("GenBPhi"   ), "#phi (b)"       , 34, -3.4,   3.4) );
  BKinGen_.push_back( fs->make<TH1D>(ns.name("GenBMass"  ), "M (b) [GeV]"    , 30,  0. , 600. ) );
    
  LepBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenLepBarPt"    ), "p_{t} (l^{+}) [GeV]", 50,  0. , 500. ) );
  LepBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenLepBarEnergy"), "E (l^{+}) [GeV]"    , 50,  0. , 500. ) );
  LepBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenLepBarEta"   ), "#eta (l^{+})"       , 34, -3.4,   3.4) );
  LepBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenLepBarPhi"   ), "#phi (l^{+})"       , 34, -3.4,   3.4) );
  LepBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenLepBarMass"  ), "M (l^{+}) [GeV]"    , 30,  0. , 600. ) ); 

  NuKinGen_.push_back( fs->make<TH1D>(ns.name("GenNuPt"    ), "p_{t} (#nu^{-}) [GeV]", 50,  0. , 500. ) );
  NuKinGen_.push_back( fs->make<TH1D>(ns.name("GenNuEnergy"), "E (#nu^{-}) [GeV]"    , 50,  0. , 500. ) );
  NuKinGen_.push_back( fs->make<TH1D>(ns.name("GenNuEta"   ), "#eta (#nu^{-})"       , 34, -3.4,   3.4) );
  NuKinGen_.push_back( fs->make<TH1D>(ns.name("GenNuPhi"   ), "#phi (#nu^{-})"       , 34, -3.4,   3.4) );
  NuKinGen_.push_back( fs->make<TH1D>(ns.name("GenNuMass"  ), "M (#nu^{-}) [GeV]"    , 30,  0. , 600. ) );

  TopBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenTopBarPt"    ), "p_{t} (#bar{t}) [GeV]", 50,  0. , 500. ) );
  TopBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenTopBarEnergy"), "E (#bar{t}) [GeV]"    , 50,  0. , 500. ) );
  TopBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenTopBarEta"   ), "#eta (#bar{t})"       , 34, -3.4,   3.4) );
  TopBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenTopBarPhi"   ), "#phi (#bar{t})"       , 34, -3.4,   3.4) );
  TopBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenTopBarMass"  ), "M (#bar{t}) [GeV]"    , 40,  0. , 400. ) );

  WminusKinGen_.push_back( fs->make<TH1D>(ns.name("GenWminusPt"    ), "p_{t} (W^{-}) [GeV]", 50,  0. , 500. ) );
  WminusKinGen_.push_back( fs->make<TH1D>(ns.name("GenWminusEnergy"), "E (W^{-}) [GeV]"    , 50,  0. , 500. ) );
  WminusKinGen_.push_back( fs->make<TH1D>(ns.name("GenWminusEta"   ), "#eta (W^{-})"       , 34, -3.4,   3.4) );
  WminusKinGen_.push_back( fs->make<TH1D>(ns.name("GenWminusPhi"   ), "#phi (W^{-})"       , 34, -3.4,   3.4) );
  WminusKinGen_.push_back( fs->make<TH1D>(ns.name("GenWminusMass"  ), "M (W^{-}) [GeV]"    , 30,  0. , 600. ) );

  BBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenBBarPt"    ), "p_{t} (#bar{b}) [GeV]", 50,  0. , 500. ) );
  BBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenBBarEnergy"), "E (#bar{b}) [GeV]"    , 50,  0. , 500. ) );
  BBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenBBarEta"   ), "#eta (#bar{b})"       , 34, -3.4,   3.4) );
  BBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenBBarPhi"   ), "#phi (#bar{b})"       , 34, -3.4,   3.4) );
  BBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenBBarMass"  ), "M (#bar{b}) [GeV]"    , 30,  0. , 600. ) ); 
  
  LepKinGen_.push_back( fs->make<TH1D>(ns.name("GenLepPt"    ), "p_{t} (l^{-}) [GeV]", 50,  0. , 500. ) );
  LepKinGen_.push_back( fs->make<TH1D>(ns.name("GenLepEnergy"), "E (l^{-}) [GeV]"    , 50,  0. , 500. ) );
  LepKinGen_.push_back( fs->make<TH1D>(ns.name("GenLepEta"   ), "#eta (l^{-})"       , 34, -3.4,   3.4) );
  LepKinGen_.push_back( fs->make<TH1D>(ns.name("GenLepPhi"   ), "#phi (l^{-})"       , 34, -3.4,   3.4) );
  LepKinGen_.push_back( fs->make<TH1D>(ns.name("GenLepMass"  ), "M (l^{-}) [GeV]"    , 30,  0. , 600. ) );
  
  NuBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenNuBarPt"    ), "p_{t} (#bar{#nu}^{-}) [GeV]", 50,  0. , 500. ) );
  NuBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenNuBarEnergy"), "E (#bar{#nu}^{-}) [GeV]"    , 50,  0. , 500. ) );
  NuBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenNuBarEta"   ), "#eta (#bar{#nu}^{-})"       , 34, -3.4,   3.4) );
  NuBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenNuBarPhi"   ), "#phi (#bar{#nu}^{-})"       , 34, -3.4,   3.4) );
  NuBarKinGen_.push_back( fs->make<TH1D>(ns.name("GenNuBarMass"  ), "M (#bar{#nu}^{-}) [GeV]"    , 30,  0. , 600. ) );  
}

/// book histograms for particle resolutions
/// append wrong charge histos if chosen in config
void
FullLepHypothesesAnalyzer::bookKinResHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("res");

  TopKinRes_.push_back( fs->make<TH1D>(ns.name("TopPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (t)",    40, -1.0, 1.0 ) );
  TopKinRes_.push_back( fs->make<TH1D>(ns.name("TopEnRes"  ), "E_{rec}-E_{gen}/E_{gen} (t)"      ,    40, -1.0, 1.0 ) );  
  TopKinRes_.push_back( fs->make<TH1D>(ns.name("TopEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (t)", 40, -1.0, 1.0 ) );
  TopKinRes_.push_back( fs->make<TH1D>(ns.name("TopPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (t)", 40, -1.0, 1.0 ) );
  TopKinRes_.push_back( fs->make<TH1D>(ns.name("TopMassRes"), "M_{rec}-M_{gen}/M_{gen} (t)",          40, -1.0, 1.0 ) );
  
  WplusKinRes_.push_back( fs->make<TH1D>(ns.name("WplusPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (W^{+})",    40, -1.0, 1.0 ) );
  WplusKinRes_.push_back( fs->make<TH1D>(ns.name("WplusEnRes"  ), "E_{rec}-E_{gen}/E_{gen} (W^{+})",          40, -1.0, 1.0 ) );  
  WplusKinRes_.push_back( fs->make<TH1D>(ns.name("WplusEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (W^{+})", 40, -1.0, 1.0 ) );
  WplusKinRes_.push_back( fs->make<TH1D>(ns.name("WplusPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (W^{+})", 40, -1.0, 1.0 ) );
  WplusKinRes_.push_back( fs->make<TH1D>(ns.name("WplusMassRes"), "M_{rec}-M_{gen}/M_{gen} (W^{+})",          40, -1.0, 1.0 ) );  

  BKinRes_.push_back( fs->make<TH1D>(ns.name("BPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (b)",    40, -1.0, 1.0 ) );
  BKinRes_.push_back( fs->make<TH1D>(ns.name("BEnRes"  ), "E_{rec}-E_{gen}/E_{gen} (b)",          40, -1.0, 1.0 ) );  
  BKinRes_.push_back( fs->make<TH1D>(ns.name("BEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (b)", 40, -1.0, 1.0 ) );
  BKinRes_.push_back( fs->make<TH1D>(ns.name("BPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (b)", 40, -1.0, 1.0 ) );
  BKinRes_.push_back( fs->make<TH1D>(ns.name("BMassRes"), "M_{rec}-M_{gen}/M_{gen} (b)",          40, -1.0, 1.0 ) );  

  LepBarKinRes_.push_back( fs->make<TH1D>(ns.name("LepBarPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (l^{+})",    40, -1.0, 1.0 ) );
  LepBarKinRes_.push_back( fs->make<TH1D>(ns.name("LepBarEnRes"  ), "E_{rec}-E_{gen}/E_{gen} (l^{+})",          40, -1.0, 1.0 ) );  
  LepBarKinRes_.push_back( fs->make<TH1D>(ns.name("LepBarEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (l^{+})", 40, -1.0, 1.0 ) );
  LepBarKinRes_.push_back( fs->make<TH1D>(ns.name("LepBarPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (l^{+})", 40, -1.0, 1.0 ) );
  LepBarKinRes_.push_back( fs->make<TH1D>(ns.name("LepBarMassRes"), "M_{rec}-M_{gen}/M_{gen} (l^{+})",          40, -1.0, 1.0 ) ); 

  NuKinRes_.push_back( fs->make<TH1D>(ns.name("NuPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} #nu",    40, -1.0, 1.0 ) );
  NuKinRes_.push_back( fs->make<TH1D>(ns.name("NuEnRes"  ), "E_{rec}-E_{gen}/E_{gen} #nu",          40, -1.0, 1.0 ) );  
  NuKinRes_.push_back( fs->make<TH1D>(ns.name("NuEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} #nu", 40, -1.0, 1.0 ) );
  NuKinRes_.push_back( fs->make<TH1D>(ns.name("NuPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} #nu", 40, -1.0, 1.0 ) );
  NuKinRes_.push_back( fs->make<TH1D>(ns.name("NuMassRes"), "M_{rec}-M_{gen}/M_{gen} #nu",          40, -1.0, 1.0 ) ); 

  TopBarKinRes_.push_back( fs->make<TH1D>(ns.name("TopBarPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} #bar{t}",    40, -1.0, 1.0 ) );
  TopBarKinRes_.push_back( fs->make<TH1D>(ns.name("TopBarEnRes"  ), "E_{rec}-E_{gen}/E_{gen} #bar{t}",         40, -1.0, 1.0 ) );  
  TopBarKinRes_.push_back( fs->make<TH1D>(ns.name("TopBarEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} #bar{t}", 40, -1.0, 1.0 ) );
  TopBarKinRes_.push_back( fs->make<TH1D>(ns.name("TopBarPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} #bar{t}", 40, -1.0, 1.0 ) );
  TopBarKinRes_.push_back( fs->make<TH1D>(ns.name("TopBarMassRes"), "M_{rec}-M_{gen}/M_{gen} #bar{t}",          40, -1.0, 1.0 ) ); 

  WminusKinRes_.push_back( fs->make<TH1D>(ns.name("WminusPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (W^{-})",    40, -1.0, 1.0 ) );
  WminusKinRes_.push_back( fs->make<TH1D>(ns.name("WminusEnRes"  ), "E_{rec}-E_{gen}/E_{gen} (W^{-})",          40, -1.0, 1.0 ) );  
  WminusKinRes_.push_back( fs->make<TH1D>(ns.name("WminusEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (W^{-})", 40, -1.0, 1.0 ) );
  WminusKinRes_.push_back( fs->make<TH1D>(ns.name("WminusPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (W^{-})", 40, -1.0, 1.0 ) );
  WminusKinRes_.push_back( fs->make<TH1D>(ns.name("WminusMassRes"), "M_{rec}-M_{gen}/M_{gen} (W^{-})",          40, -1.0, 1.0 ) ); 

  BBarKinRes_.push_back( fs->make<TH1D>(ns.name("BBarPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (#bar{b})",    40, -1.0, 1.0 ) );
  BBarKinRes_.push_back( fs->make<TH1D>(ns.name("BBarEnRes"  ), "E_{rec}-E_{gen}/E_{gen} (#bar{b})",          40, -1.0, 1.0 ) );  
  BBarKinRes_.push_back( fs->make<TH1D>(ns.name("BBarEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (#bar{b})", 40, -1.0, 1.0 ) );
  BBarKinRes_.push_back( fs->make<TH1D>(ns.name("BBarPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (#bar{b})", 40, -1.0, 1.0 ) );
  BBarKinRes_.push_back( fs->make<TH1D>(ns.name("BBarMassRes"), "M_{rec}-M_{gen}/M_{gen} (#bar{b})",          40, -1.0, 1.0 ) ); 
  
  LepKinRes_.push_back( fs->make<TH1D>(ns.name("LepPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (l)",    40, -1.0, 1.0 ) );
  LepKinRes_.push_back( fs->make<TH1D>(ns.name("LepEnRes"  ), "E_{rec}-E_{gen}/E_{gen} (l)",          40, -1.0, 1.0 ) );  
  LepKinRes_.push_back( fs->make<TH1D>(ns.name("LepEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (l)", 40, -1.0, 1.0 ) );
  LepKinRes_.push_back( fs->make<TH1D>(ns.name("LepPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (l)", 40, -1.0, 1.0 ) );
  LepKinRes_.push_back( fs->make<TH1D>(ns.name("LepMassRes"), "M_{rec}-M_{gen}/M_{gen} (l)",          40, -1.0, 1.0 ) ); 
  
  NuBarKinRes_.push_back( fs->make<TH1D>(ns.name("NuBarPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (#bar{#nu})",    40, -1.0, 1.0 ) );
  NuBarKinRes_.push_back( fs->make<TH1D>(ns.name("NuBarEnRes"  ), "E_{rec}-E_{gen}/E_{gen} (#bar{#nu})",          40, -1.0, 1.0 ) );  
  NuBarKinRes_.push_back( fs->make<TH1D>(ns.name("NuBarEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (#bar{#nu})", 40, -1.0, 1.0 ) );
  NuBarKinRes_.push_back( fs->make<TH1D>(ns.name("NuBarPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (#bar{#nu})", 40, -1.0, 1.0 ) );
  NuBarKinRes_.push_back( fs->make<TH1D>(ns.name("NuBarMassRes"), "M_{rec}-M_{gen}/M_{gen} (#bar{#nu})",          40, -1.0, 1.0 ) ); 
  
  // push back the same histograms for wrong charge event solutions if demanded
  if(useWrongCharge_){
    TopKinRes_.push_back( fs->make<TH1D>(ns.name("TopPtResWrong"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (t)",    40, -1.0, 1.0 ) );
    TopKinRes_.push_back( fs->make<TH1D>(ns.name("TopEnResWrong"  ), "E_{rec}-E_{gen}/E_{gen} (t)"      ,    40, -1.0, 1.0 ) );  
    TopKinRes_.push_back( fs->make<TH1D>(ns.name("TopEtaResWrong" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (t)", 40, -1.0, 1.0 ) );
    TopKinRes_.push_back( fs->make<TH1D>(ns.name("TopPhiResWrong" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (t)", 40, -1.0, 1.0 ) );
    TopKinRes_.push_back( fs->make<TH1D>(ns.name("TopMassResWrong"), "M_{rec}-M_{gen}/M_{gen} (t)",          40, -1.0, 1.0 ) );

    WplusKinRes_.push_back( fs->make<TH1D>(ns.name("WplusPtResWrong"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (W^{+})",    40, -1.0, 1.0 ) );
    WplusKinRes_.push_back( fs->make<TH1D>(ns.name("WplusEnResWrong"  ), "E_{rec}-E_{gen}/E_{gen} (W^{+})",          40, -1.0, 1.0 ) );  
    WplusKinRes_.push_back( fs->make<TH1D>(ns.name("WplusEtaResWrong" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (W^{+})", 40, -1.0, 1.0 ) );
    WplusKinRes_.push_back( fs->make<TH1D>(ns.name("WplusPhiResWrong" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (W^{+})", 40, -1.0, 1.0 ) );
    WplusKinRes_.push_back( fs->make<TH1D>(ns.name("WplusMassResWrong"), "M_{rec}-M_{gen}/M_{gen} (W^{+})",          40, -1.0, 1.0 ) );  

    BKinRes_.push_back( fs->make<TH1D>(ns.name("BPtResWrong"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (b)",    40, -1.0, 1.0 ) );
    BKinRes_.push_back( fs->make<TH1D>(ns.name("BEnResWrong"  ), "E_{rec}-E_{gen}/E_{gen} (b)",          40, -1.0, 1.0 ) );  
    BKinRes_.push_back( fs->make<TH1D>(ns.name("BEtaResWrong" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (b)", 40, -1.0, 1.0 ) );
    BKinRes_.push_back( fs->make<TH1D>(ns.name("BPhiResWrong" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (b)", 40, -1.0, 1.0 ) );
    BKinRes_.push_back( fs->make<TH1D>(ns.name("BMassResWrong"), "M_{rec}-M_{gen}/M_{gen} (b)",          40, -1.0, 1.0 ) );  

    LepBarKinRes_.push_back( fs->make<TH1D>(ns.name("LepBarPtResWrong"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (l^{+})",    40, -1.0, 1.0 ) );
    LepBarKinRes_.push_back( fs->make<TH1D>(ns.name("LepBarEnResWrong"  ), "E_{rec}-E_{gen}/E_{gen} (l^{+})",          40, -1.0, 1.0 ) );  
    LepBarKinRes_.push_back( fs->make<TH1D>(ns.name("LepBarEtaResWrong" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (l^{+})", 40, -1.0, 1.0 ) );
    LepBarKinRes_.push_back( fs->make<TH1D>(ns.name("LepBarPhiResWrong" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (l^{+})", 40, -1.0, 1.0 ) );
    LepBarKinRes_.push_back( fs->make<TH1D>(ns.name("LepBarMassResWrong"), "M_{rec}-M_{gen}/M_{gen} (l^{+})",          40, -1.0, 1.0 ) ); 

    NuKinRes_.push_back( fs->make<TH1D>(ns.name("NuPtResWrong"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} #nu",    40, -1.0, 1.0 ) );
    NuKinRes_.push_back( fs->make<TH1D>(ns.name("NuEnResWrong"  ), "E_{rec}-E_{gen}/E_{gen} #nu",          40, -1.0, 1.0 ) );  
    NuKinRes_.push_back( fs->make<TH1D>(ns.name("NuEtaResWrong" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} #nu", 40, -1.0, 1.0 ) );
    NuKinRes_.push_back( fs->make<TH1D>(ns.name("NuPhiResWrong" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} #nu", 40, -1.0, 1.0 ) );
    NuKinRes_.push_back( fs->make<TH1D>(ns.name("NuMassResWrong"), "M_{rec}-M_{gen}/M_{gen} #nu",          40, -1.0, 1.0 ) ); 

    TopBarKinRes_.push_back( fs->make<TH1D>(ns.name("TopBarPtResWrong"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} #bar{t}",    40, -1.0, 1.0 ) );
    TopBarKinRes_.push_back( fs->make<TH1D>(ns.name("TopBarEnResWrong"  ), "E_{rec}-E_{gen}/E_{gen} #bar{t}",         40, -1.0, 1.0 ) );  
    TopBarKinRes_.push_back( fs->make<TH1D>(ns.name("TopBarEtaResWrong" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} #bar{t}", 40, -1.0, 1.0 ) );
    TopBarKinRes_.push_back( fs->make<TH1D>(ns.name("TopBarPhiResWrong" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} #bar{t}", 40, -1.0, 1.0 ) );
    TopBarKinRes_.push_back( fs->make<TH1D>(ns.name("TopBarMassResWrong"), "M_{rec}-M_{gen}/M_{gen} #bar{t}",          40, -1.0, 1.0 ) ); 

    WminusKinRes_.push_back( fs->make<TH1D>(ns.name("WminusPtResWrong"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (W^{-})",    40, -1.0, 1.0 ) );
    WminusKinRes_.push_back( fs->make<TH1D>(ns.name("WminusEnResWrong"  ), "E_{rec}-E_{gen}/E_{gen} (W^{-})",          40, -1.0, 1.0 ) );  
    WminusKinRes_.push_back( fs->make<TH1D>(ns.name("WminusEtaResWrong" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (W^{-})", 40, -1.0, 1.0 ) );
    WminusKinRes_.push_back( fs->make<TH1D>(ns.name("WminusPhiResWrong" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (W^{-})", 40, -1.0, 1.0 ) );
    WminusKinRes_.push_back( fs->make<TH1D>(ns.name("WminusMassResWrong"), "M_{rec}-M_{gen}/M_{gen} (W^{-})",          40, -1.0, 1.0 ) ); 

    BBarKinRes_.push_back( fs->make<TH1D>(ns.name("BBarPtResWrong"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (#bar{b})",    40, -1.0, 1.0 ) );
    BBarKinRes_.push_back( fs->make<TH1D>(ns.name("BBarEnResWrong"  ), "E_{rec}-E_{gen}/E_{gen} (#bar{b})",          40, -1.0, 1.0 ) );  
    BBarKinRes_.push_back( fs->make<TH1D>(ns.name("BBarEtaResWrong" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (#bar{b})", 40, -1.0, 1.0 ) );
    BBarKinRes_.push_back( fs->make<TH1D>(ns.name("BBarPhiResWrong" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (#bar{b})", 40, -1.0, 1.0 ) );
    BBarKinRes_.push_back( fs->make<TH1D>(ns.name("BBarMassResWrong"), "M_{rec}-M_{gen}/M_{gen} (#bar{b})",          40, -1.0, 1.0 ) ); 

    LepKinRes_.push_back( fs->make<TH1D>(ns.name("LepPtResWrong"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (l)",    40, -1.0, 1.0 ) );
    LepKinRes_.push_back( fs->make<TH1D>(ns.name("LepEnResWrong"  ), "E_{rec}-E_{gen}/E_{gen} (l)",          40, -1.0, 1.0 ) );  
    LepKinRes_.push_back( fs->make<TH1D>(ns.name("LepEtaResWrong" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (l)", 40, -1.0, 1.0 ) );
    LepKinRes_.push_back( fs->make<TH1D>(ns.name("LepPhiResWrong" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (l)", 40, -1.0, 1.0 ) );
    LepKinRes_.push_back( fs->make<TH1D>(ns.name("LepMassResWrong"), "M_{rec}-M_{gen}/M_{gen} (l)",          40, -1.0, 1.0 ) ); 

    NuBarKinRes_.push_back( fs->make<TH1D>(ns.name("NuBarPtResWrong"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (#bar{#nu})",    40, -1.0, 1.0 ) );
    NuBarKinRes_.push_back( fs->make<TH1D>(ns.name("NuBarEnResWrong"  ), "E_{rec}-E_{gen}/E_{gen} (#bar{#nu})",          40, -1.0, 1.0 ) );  
    NuBarKinRes_.push_back( fs->make<TH1D>(ns.name("NuBarEtaResWrong" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (#bar{#nu})", 40, -1.0, 1.0 ) );
    NuBarKinRes_.push_back( fs->make<TH1D>(ns.name("NuBarPhiResWrong" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (#bar{#nu})", 40, -1.0, 1.0 ) );
    NuBarKinRes_.push_back( fs->make<TH1D>(ns.name("NuBarMassResWrong"), "M_{rec}-M_{gen}/M_{gen} (#bar{#nu})",          40, -1.0, 1.0 ) );   
  }   
}

/// book histograms for hypothesis specific histos and correlations between hypotheses
void
FullLepHypothesesAnalyzer::bookQualityHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("qual");

  goodHypo_ = fs->make<TH1D>(ns.name("goodHypo"), "good hypothesis", 2, -0.5, 1.5);

  genMatchSumDR_ = fs->make<TH1D>(ns.name("genMatchSumDR"), "#Sigma #Delta R (genMatch)"          , 50, 0.,   5.);
  genMatchSumPt_ = fs->make<TH1D>(ns.name("genMatchSumPt"), "#Sigma #Delta p_{T} (genMatch) [GeV]", 40, 0., 400.);
  
  kinSolWeight_      = fs->make<TH1D>(ns.name("kinSolWeight"     ), "Weight of kin solution", 50,  0. , 1. );
  kinSolWeightWrong_ = fs->make<TH1D>(ns.name("kinSolWeightWrong"), "Weight of kin solution", 50,  0. , 1. );  
  wrongCharge_       = fs->make<TH1D>(ns.name("wrongCharge"      ), "is event wrong charge",   2, -0.5, 1.5);  
  
  bJetIdcs_   = fs->make<TH1D>(ns.name("bJetIdcs"    ),  "b jet indices used for hypo"     , 4, -0.5, 3.5);
  bBarJetIdcs_= fs->make<TH1D>(ns.name("bBarJetIdcs" ),  "bbar jet indices used for hypo"  , 4, -0.5, 3.5);  
  elec1Idcs_  = fs->make<TH1D>(ns.name("elec1Idcs"   ),  "electron 1 indices used for hypo", 5, -1.5, 3.5);
  elec2Idcs_  = fs->make<TH1D>(ns.name("elec2Idcs"   ),  "electron 2 indices used for hypo", 5, -1.5, 3.5);    
  muon1Idcs_  = fs->make<TH1D>(ns.name("muon1Idcs"   ),  "muon 1 indices used for hypo"    , 5, -1.5, 3.5); 
  muon2Idcs_  = fs->make<TH1D>(ns.name("muon2Idcs"   ),  "muon 2 indices used for hypo"    , 5, -1.5, 3.5);  
  
  deltaM_  = fs->make<TH1D>(ns.name("deltaM"   ), "M_{top}-M{#bar{t}}", 50, -25., 25.);
  
  jetIdCorrectnes_  = fs->make<TH1D>(ns.name("jetIdCorrectnes" ), "Correctnes of Jet Id",     3, -0.5, 2.5);  
  jetFlCorrectnes_  = fs->make<TH1D>(ns.name("jetFlCorrectnes" ), "Correctnes of Jet Flavor", 3, -0.5, 2.5); 

  compare_                = fs->make<TH2D>(ns.name("compare"               ), "Indices",        15, -0.5, 14.5, 15, -0.5, 14.5);
  spectrum_               = fs->make<TH2D>(ns.name("spectrum"              ), "Nu spectrum",    50, 0., 250., 50, 0., 250.);       
}

/// fill histograms for reconstructed particles properties in events with oppositely charged leptons: Pt, E, Eta, Phi, m
void
FullLepHypothesesAnalyzer::fillKinHistos(std::vector<TH1D*>& histos, const reco::Candidate& candidate, const double& weight)
{
  histos[0]->Fill( candidate.pt()    , weight );
  histos[1]->Fill( candidate.energy(), weight );  
  histos[2]->Fill( candidate.eta()   , weight );
  histos[3]->Fill( candidate.phi()   , weight );
  histos[4]->Fill( candidate.mass()  , weight );
}

/// fill histograms for reconstructed particles properties in events with equally charged leptons: Pt, E, Eta, Phi, m	
void
FullLepHypothesesAnalyzer::fillWrongChargeKinHistos(std::vector<TH1D*>& histos, const reco::Candidate& candidate, const double& weight)
{
  histos[5]->Fill( candidate.pt()    , weight );
  histos[6]->Fill( candidate.energy(), weight );  
  histos[7]->Fill( candidate.eta()   , weight );
  histos[8]->Fill( candidate.phi()   , weight );
  histos[9]->Fill( candidate.mass()  , weight );
}

/// fill histograms for generated particles properties: Pt, E, Eta, Phi, m
void
FullLepHypothesesAnalyzer::fillKinGenHistos(std::vector<TH1D*>& histos, const reco::Candidate& candidate, const double& weight)
{
  histos[0]->Fill( candidate.pt()    , weight );
  histos[1]->Fill( candidate.energy(), weight );  
  histos[2]->Fill( candidate.eta()   , weight );
  histos[3]->Fill( candidate.phi()   , weight );
  histos[4]->Fill( candidate.mass()  , weight );  
}

/// fill histograms for particle resolutions for right charge combinations
void
FullLepHypothesesAnalyzer::fillKinResHistos(std::vector<TH1D*>& histos, const reco::Candidate& candidate,
					    const reco::Candidate& genCandidate, const double& weight)
{
  histos[0]->Fill( (candidate.pt()    -genCandidate.pt()    )/genCandidate.pt()    , weight );
  histos[1]->Fill( (candidate.energy()-genCandidate.energy())/genCandidate.energy(), weight );  
  histos[2]->Fill( (candidate.eta()   -genCandidate.eta()   )/genCandidate.eta()   , weight );
  histos[3]->Fill( (candidate.phi()   -genCandidate.phi()   )/genCandidate.phi()   , weight );
  histos[4]->Fill( (candidate.mass()  -genCandidate.mass()  )/genCandidate.mass()  , weight );  
}

/// fill histograms for particle resolutions for wrong charge combinations
/// should be empty since the only entries are from right charge events that are reconstructed as wrong charge
void
FullLepHypothesesAnalyzer::fillWrongChargeKinResHistos(std::vector<TH1D*>& histos, const reco::Candidate& candidate,
					    const reco::Candidate& genCandidate, const double& weight)
{
  histos[5]->Fill( (candidate.pt()    -genCandidate.pt()    )/genCandidate.pt()    , weight );
  histos[6]->Fill( (candidate.energy()-genCandidate.energy())/genCandidate.energy(), weight );  
  histos[7]->Fill( (candidate.eta()   -genCandidate.eta()   )/genCandidate.eta()   , weight );
  histos[8]->Fill( (candidate.phi()   -genCandidate.phi()   )/genCandidate.phi()   , weight );
  histos[9]->Fill( (candidate.mass()  -genCandidate.mass()  )/genCandidate.mass()  , weight );
}

/// book histograms for hypothesis specific histos and correlations between hypotheses
void
FullLepHypothesesAnalyzer::fillQualityHistos(const TtFullLeptonicEvent& FullLepEvt, 
                                             const TtEvent::HypoClassKey& hypoKey, 
					     const double& weight)
{
  bJetIdcs_   ->Fill(FullLepEvt.jetLeptonCombination(hypoKey)[0] );
  bBarJetIdcs_->Fill(FullLepEvt.jetLeptonCombination(hypoKey)[1] );  
  elec1Idcs_  ->Fill(FullLepEvt.jetLeptonCombination(hypoKey)[2] );  
  elec2Idcs_  ->Fill(FullLepEvt.jetLeptonCombination(hypoKey)[3] );  
  muon1Idcs_  ->Fill(FullLepEvt.jetLeptonCombination(hypoKey)[4] );  
  muon2Idcs_  ->Fill(FullLepEvt.jetLeptonCombination(hypoKey)[5] ); 
  
  spectrum_->Fill(FullLepEvt.neutrino(hypoKey)->energy(), FullLepEvt.neutrinoBar(hypoKey)->energy());
    
  // genMatch histos
  if( hypoKey==3 ) {
    genMatchSumDR_->Fill( FullLepEvt.genMatchSumDR() , weight );
    genMatchSumPt_->Fill( FullLepEvt.genMatchSumPt() , weight ); 
  } 
  
  if( hypoKey==6 ) {
    deltaM_->Fill(FullLepEvt.top(hypoKey)->mass()-FullLepEvt.topBar(hypoKey)->mass()); 
    if(!FullLepEvt.isWrongCharge()) kinSolWeight_->Fill( FullLepEvt.solWeight() , weight );
    else kinSolWeightWrong_->Fill( FullLepEvt.solWeight() , weight );
    wrongCharge_ ->Fill( FullLepEvt.isWrongCharge() , weight ); 
  } 
  
  // indices Hist
  const TtEvent::HypoClassKey genKey = TtEvent::HypoClassKey(3);
  const TtEvent::HypoClassKey kinKey = TtEvent::HypoClassKey(6);
   
  if(FullLepEvt.isHypoValid(genKey) && FullLepEvt.isHypoValid(kinKey)){
    compare_->Fill(FullLepEvt.jetLeptonCombination(genKey)[0]   , FullLepEvt.jetLeptonCombination(kinKey)[0]   );
    compare_->Fill(FullLepEvt.jetLeptonCombination(genKey)[1]+ 4, FullLepEvt.jetLeptonCombination(kinKey)[1]+ 4);   
    compare_->Fill(FullLepEvt.jetLeptonCombination(genKey)[4]+ 8, FullLepEvt.jetLeptonCombination(kinKey)[4]+ 8);
    compare_->Fill(FullLepEvt.jetLeptonCombination(genKey)[5]+12, FullLepEvt.jetLeptonCombination(kinKey)[5]+12);  
    
    // are both b-jets identified right or only one or none of them?
    if(FullLepEvt.jetLeptonCombination(kinKey)[0] == FullLepEvt.jetLeptonCombination(genKey)[0] &&
     FullLepEvt.jetLeptonCombination(kinKey)[1] == FullLepEvt.jetLeptonCombination(genKey)[1]){
      jetIdCorrectnes_->SetBinContent(1,jetIdCorrectnes_->GetBinContent(1)+weight);
    }
    else if(FullLepEvt.jetLeptonCombination(kinKey)[0] == FullLepEvt.jetLeptonCombination(genKey)[0] ||
     FullLepEvt.jetLeptonCombination(kinKey)[1] == FullLepEvt.jetLeptonCombination(genKey)[1]){
      jetIdCorrectnes_->SetBinContent(2,jetIdCorrectnes_->GetBinContent(2)+weight);
    }
    else{
      jetIdCorrectnes_->SetBinContent(3,jetIdCorrectnes_->GetBinContent(3)+weight);
    } 
    
    //how many of the two jets have the right flavor?
    if((FullLepEvt.jetLeptonCombination(kinKey)[0] == FullLepEvt.jetLeptonCombination(genKey)[0] ||
     FullLepEvt.jetLeptonCombination(kinKey)[0] == FullLepEvt.jetLeptonCombination(genKey)[1]) &&
     (FullLepEvt.jetLeptonCombination(kinKey)[1] == FullLepEvt.jetLeptonCombination(genKey)[1] ||
      FullLepEvt.jetLeptonCombination(kinKey)[1] == FullLepEvt.jetLeptonCombination(genKey)[0])){
      jetFlCorrectnes_->SetBinContent(1,jetFlCorrectnes_->GetBinContent(1)+weight);
    }
    else if((FullLepEvt.jetLeptonCombination(kinKey)[0] == FullLepEvt.jetLeptonCombination(genKey)[0] ||
     FullLepEvt.jetLeptonCombination(kinKey)[0] == FullLepEvt.jetLeptonCombination(genKey)[1]) ||
     (FullLepEvt.jetLeptonCombination(kinKey)[1] == FullLepEvt.jetLeptonCombination(genKey)[1] ||
      FullLepEvt.jetLeptonCombination(kinKey)[1] == FullLepEvt.jetLeptonCombination(genKey)[0])){
      jetFlCorrectnes_->SetBinContent(2,jetFlCorrectnes_->GetBinContent(2)+weight);
    }
    else{
      jetFlCorrectnes_->SetBinContent(3,jetFlCorrectnes_->GetBinContent(3)+weight);
    }             
  }   
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( FullLepHypothesesAnalyzer );
