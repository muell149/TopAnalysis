#include "TLorentzVector.h"
#include "TopAnalysis/TopAnalyzer/plugins/FullLepKinAnalyzer.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "AnalysisDataFormats/TopObjects/interface/TtEventPartons.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Common/interface/View.h"

#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"


/// default constructor
FullLepKinAnalyzer::FullLepKinAnalyzer(const edm::ParameterSet& cfg):
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
  bookGenHistos      (fs);  
  bookPullHistos     (fs);    
  bookQualityHistos  (fs);
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
  
  int nTCHE  = 0;
  int nSSVHE = 0;
  
  for(edm::View<pat::Jet>::const_iterator jet = jets->begin();jet != jets->end(); ++jet) { 
    if(jet->bDiscriminator("trackCountingHighEffBJetTags")>1.7          && nTCHE<2 ) ++nTCHE;
    if(jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags")>1.74 && nSSVHE<2) ++nSSVHE;
  }

  int y = 0;   
  if( FullLepEvt->isHypoValid(hypoKey) ) y = 1;
  
  kinTCHEcorrelation_ ->Fill(nTCHE, y);
  kinSSVHEcorrelation_->Fill(nSSVHE,y);
  
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
  reco::CompositeCandidate* LepLepBar = new reco::CompositeCandidate();
  LepLepBar->addDaughter(*Lep);
  LepLepBar->addDaughter(*LepBar);  
  addFourMomenta.set(*LepLepBar);


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
  
  fillKinHistos(TtBarKin_,     *TtBar     );
  fillKinHistos(LepLepBarKin_, *LepLepBar );  
    
  // -----------------------
  // fill generator and pull histos for kinematic variables
  // -----------------------
  if( !FullLepEvt->genEvent() || !FullLepEvt->genEvent()->isFullLeptonic()){
    delete TtBar;
    delete LepLepBar;
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
  reco::CompositeCandidate* genLepLepBar = new reco::CompositeCandidate();
  genLepLepBar->addDaughter(*genLep);
  genLepLepBar->addDaughter(*genLepBar);
  addFourMomenta.set(*genLepLepBar); 

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
  
  fillKinHistos(TtBarGen_,     *genTtBar     );
  fillKinHistos(LepLepBarGen_, *genLepLepBar );  
  
  // pull distributions
  fillPullHistos(TopPull_,    *Top,     *genTop    );
  fillPullHistos(WplusPull_,  *Wplus,   *genWplus  );
  fillPullHistos(BPull_,      *B,       *genB	   );
  fillPullHistos(LepBarPull_, *LepBar,  *genLepBar );
  fillPullHistos(NuPull_,     *Nu,      *genNu     );

  fillPullHistos(TopBarPull_, *TopBar,  *genTopBar );
  fillPullHistos(WminusPull_, *Wminus,  *genWminus );
  fillPullHistos(BBarPull_,   *BBar,    *genBBar   );
  fillPullHistos(LepPull_,    *Lep,     *genLep    );
  fillPullHistos(NuBarPull_,  *NuBar,   *genNuBar  ); 
  
  fillPullHistos(TtBarPull_,     *TtBar,     *genTtBar     );
  fillPullHistos(LepLepBarPull_, *LepLepBar, *genLepLepBar );
  
  delete TtBar;
  delete LepLepBar;
  delete genTtBar;
  delete genLepLepBar;       
}

/// everything that has to be done after the event loop: summarizes if wantSummary_ is true
void
FullLepKinAnalyzer::endJob() 
{
}

/// book histograms for reconstructed particles properties: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::bookKinHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("kin");

  TopKin_.push_back( fs->make<TH1D>(ns.name("TopPt"    ), "p_{t} (t) [GeV]", 50,  0. , 500. ) );
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopEnergy"), "E (t) [GeV]"    , 50,  0. , 500. ) );  
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopEta"   ), "#eta (t)"       , 34, -3.4,   3.4) );
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopPhi"   ), "#phi (t)"       , 34, -3.4,   3.4) );
  TopKin_.push_back( fs->make<TH1D>(ns.name("TopMass"  ), "M (top) [GeV]"  , 50, -50. , 450. ) );

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

  NuKin_.push_back( fs->make<TH1D>(ns.name("NuPt"    ), "p_{t} (#nu) [GeV]", 50,  0. , 500. ) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuEnergy"), "E (#nu) [GeV]"    , 50,  0. , 500. ) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuEta"   ), "#eta (#nu)"       , 34, -3.4,   3.4) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuPhi"   ), "#phi (#nu)"       , 34, -3.4,   3.4) );
  NuKin_.push_back( fs->make<TH1D>(ns.name("NuMass"  ), "M (#nu) [GeV]"    , 30,  0. , 600. ) );

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
  
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarPt"    ), "p_{t} (#bar{#nu}) [GeV]", 50,  0. , 500. ) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarEnergy"), "E (#bar{#nu}) [GeV]"    , 50,  0. , 500. ) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarEta"   ), "#eta (#bar{#nu})"       , 34, -3.4,   3.4) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarPhi"   ), "#phi (#bar{#nu})"       , 34, -3.4,   3.4) );
  NuBarKin_.push_back( fs->make<TH1D>(ns.name("NuBarMass"  ), "M (#bar{#nu}) [GeV]"    , 30,  0. , 600. ) );
  
  TtBarKin_.push_back( fs->make<TH1D>(ns.name("TtBarPt"    ), "p_{t} (t#bar{t}) [GeV]", 50,  0. , 500. ) );
  TtBarKin_.push_back( fs->make<TH1D>(ns.name("TtBarEnergy"), "E (t#bar{t}) [GeV]"    , 50,  0. , 500. ) );
  TtBarKin_.push_back( fs->make<TH1D>(ns.name("TtBarEta"   ), "#eta (t#bar{t})"       , 34, -3.4,   3.4) );
  TtBarKin_.push_back( fs->make<TH1D>(ns.name("TtBarPhi"   ), "#phi (t#bar{t})"       , 34, -3.4,   3.4) );
  TtBarKin_.push_back( fs->make<TH1D>(ns.name("TtBarMass"  ), "M (t#bar{t}) [GeV]"    ,100,  0. ,2000. ) );
  
  LepLepBarKin_.push_back( fs->make<TH1D>(ns.name("LepLepBarPt"    ), "p_{t} (l^{+}l^{-}) [GeV]", 50,  0. , 500. ) );
  LepLepBarKin_.push_back( fs->make<TH1D>(ns.name("LepLepBarEnergy"), "E (l^{+}l^{-}) [GeV]"    , 50,  0. , 500. ) );
  LepLepBarKin_.push_back( fs->make<TH1D>(ns.name("LepLepBarEta"   ), "#eta (l^{+}l^{-})"       , 34, -3.4,   3.4) );
  LepLepBarKin_.push_back( fs->make<TH1D>(ns.name("LepLepBarPhi"   ), "#phi (l^{+}l^{-})"       , 34, -3.4,   3.4) );
  LepLepBarKin_.push_back( fs->make<TH1D>(ns.name("LepLepBarMass"  ), "M (l^{+}l^{-}) [GeV]"    , 30,  0. , 600. ) );    
}



/// book histograms for generated particles properties: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::bookGenHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("gen");

  TopGen_.push_back( fs->make<TH1D>(ns.name("TopPt"    ), "p_{t} (t) [GeV]", 50,  0. , 500. ) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopEnergy"), "E (t) [GeV]"    , 50,  0. , 500. ) );  
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopEta"   ), "#eta (t)"       , 34, -3.4,   3.4) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopPhi"   ), "#phi (t)"       , 34, -3.4,   3.4) );
  TopGen_.push_back( fs->make<TH1D>(ns.name("TopMass"  ), "M (top) [GeV]"  , 50, -50. , 450. ) );

  WplusGen_.push_back( fs->make<TH1D>(ns.name("WplusPt"    ), "p_{t} (W^{+}) [GeV]", 50,  0. , 500. ) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WplusEnergy"), "E (W^{+}) [GeV]"    , 50,  0. , 500. ) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WplusEta"   ), "#eta (W^{+})"       , 34, -3.4,   3.4) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WplusPhi"   ), "#phi (W^{+})"       , 34, -3.4,   3.4) );
  WplusGen_.push_back( fs->make<TH1D>(ns.name("WplusMass"  ), "M (W^{+}) [GeV]"    , 30,  0. , 600. ) );

  BGen_.push_back( fs->make<TH1D>(ns.name("BPt"    ), "p_{t} (b) [GeV]", 50,  0. , 500. ) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BEnergy"), "E (b) [GeV]"    , 50,  0. , 500. ) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BEta"   ), "#eta (b)"       , 34, -3.4,   3.4) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BPhi"   ), "#phi (b)"       , 34, -3.4,   3.4) );
  BGen_.push_back( fs->make<TH1D>(ns.name("BMass"  ), "M (b) [GeV]"    , 30,  0. , 600. ) );
    
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarPt"    ), "p_{t} (l^{+}) [GeV]", 50,  0. , 500. ) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarEnergy"), "E (l^{+}) [GeV]"    , 50,  0. , 500. ) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarEta"   ), "#eta (l^{+})"       , 34, -3.4,   3.4) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarPhi"   ), "#phi (l^{+})"       , 34, -3.4,   3.4) );
  LepBarGen_.push_back( fs->make<TH1D>(ns.name("LepBarMass"  ), "M (l^{+}) [GeV]"    , 30,  0. , 600. ) ); 

  NuGen_.push_back( fs->make<TH1D>(ns.name("NuPt"    ), "p_{t} (#nu^{-}) [GeV]", 50,  0. , 500. ) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuEnergy"), "E (#nu^{-}) [GeV]"    , 50,  0. , 500. ) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuEta"   ), "#eta (#nu^{-})"       , 34, -3.4,   3.4) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuPhi"   ), "#phi (#nu^{-})"       , 34, -3.4,   3.4) );
  NuGen_.push_back( fs->make<TH1D>(ns.name("NuMass"  ), "M (#nu^{-}) [GeV]"    , 30,  0. , 600. ) );

  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarPt"    ), "p_{t} (#bar{t}) [GeV]", 50,  0. , 500. ) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarEnergy"), "E (#bar{t}) [GeV]"    , 50,  0. , 500. ) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarEta"   ), "#eta (#bar{t})"       , 34, -3.4,   3.4) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarPhi"   ), "#phi (#bar{t})"       , 34, -3.4,   3.4) );
  TopBarGen_.push_back( fs->make<TH1D>(ns.name("TopBarMass"  ), "M (#bar{t}) [GeV]"    , 40,  0. , 400. ) );

  WminusGen_.push_back( fs->make<TH1D>(ns.name("WminusPt"    ), "p_{t} (W^{-}) [GeV]", 50,  0. , 500. ) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WminusEnergy"), "E (W^{-}) [GeV]"    , 50,  0. , 500. ) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WminusEta"   ), "#eta (W^{-})"       , 34, -3.4,   3.4) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WminusPhi"   ), "#phi (W^{-})"       , 34, -3.4,   3.4) );
  WminusGen_.push_back( fs->make<TH1D>(ns.name("WminusMass"  ), "M (W^{-}) [GeV]"    , 30,  0. , 600. ) );

  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarPt"    ), "p_{t} (#bar{b}) [GeV]", 50,  0. , 500. ) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarEnergy"), "E (#bar{b}) [GeV]"    , 50,  0. , 500. ) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarEta"   ), "#eta (#bar{b})"       , 34, -3.4,   3.4) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarPhi"   ), "#phi (#bar{b})"       , 34, -3.4,   3.4) );
  BBarGen_.push_back( fs->make<TH1D>(ns.name("BBarMass"  ), "M (#bar{b}) [GeV]"    , 30,  0. , 600. ) ); 
  
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepPt"    ), "p_{t} (l^{-}) [GeV]", 50,  0. , 500. ) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepEnergy"), "E (l^{-}) [GeV]"    , 50,  0. , 500. ) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepEta"   ), "#eta (l^{-})"       , 34, -3.4,   3.4) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepPhi"   ), "#phi (l^{-})"       , 34, -3.4,   3.4) );
  LepGen_.push_back( fs->make<TH1D>(ns.name("LepMass"  ), "M (l^{-}) [GeV]"    , 30,  0. , 600. ) );
  
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarPt"    ), "p_{t} (#bar{#nu}^{-}) [GeV]", 50,  0. , 500. ) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarEnergy"), "E (#bar{#nu}^{-}) [GeV]"    , 50,  0. , 500. ) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarEta"   ), "#eta (#bar{#nu}^{-})"       , 34, -3.4,   3.4) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarPhi"   ), "#phi (#bar{#nu}^{-})"       , 34, -3.4,   3.4) );
  NuBarGen_.push_back( fs->make<TH1D>(ns.name("NuBarMass"  ), "M (#bar{#nu}^{-}) [GeV]"    , 30,  0. , 600. ) );
  
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarPt"    ), "p_{t} (t#bar{t}) [GeV]", 50,  0. , 500. ) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarEnergy"), "E (t#bar{t}) [GeV]"    , 50,  0. , 500. ) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarEta"   ), "#eta (t#bar{t})"       , 34, -3.4,   3.4) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarPhi"   ), "#phi (t#bar{t})"       , 34, -3.4,   3.4) );
  TtBarGen_.push_back( fs->make<TH1D>(ns.name("TtBarMass"  ), "M (t#bar{t}) [GeV]"    ,100,  0. ,2000. ) );
  
  LepLepBarGen_.push_back( fs->make<TH1D>(ns.name("LepLepBarPt"    ), "p_{t} (l^{+}l^{-}) [GeV]", 50,  0. , 500. ) );
  LepLepBarGen_.push_back( fs->make<TH1D>(ns.name("LepLepBarEnergy"), "E (l^{+}l^{-}) [GeV]"    , 50,  0. , 500. ) );
  LepLepBarGen_.push_back( fs->make<TH1D>(ns.name("LepLepBarEta"   ), "#eta (l^{+}l^{-})"       , 34, -3.4,   3.4) );
  LepLepBarGen_.push_back( fs->make<TH1D>(ns.name("LepLepBarPhi"   ), "#phi (l^{+}l^{-})"       , 34, -3.4,   3.4) );
  LepLepBarGen_.push_back( fs->make<TH1D>(ns.name("LepLepBarMass"  ), "M (l^{+}l^{-}) [GeV]"    , 30,  0. , 600. ) );     
}



/// book histograms for pull distributions of particle properties: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::bookPullHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("pull");

  TopPull_.push_back( fs->make<TH1D>(ns.name("TopPt"    ), "p_{t} (t) [GeV]", 100,  -1 , 1. ) );
  TopPull_.push_back( fs->make<TH1D>(ns.name("TopEnergy"), "E (t) [GeV]"    , 100,  -1 , 1. ) ); 
  TopPull_.push_back( fs->make<TH1D>(ns.name("TopEta"   ), "#eta (t)"       , 100,  -1 , 1. ) );
  TopPull_.push_back( fs->make<TH1D>(ns.name("TopPhi"   ), "#phi (t)"       , 100,  -1 , 1. ) );
  TopPull_.push_back( fs->make<TH1D>(ns.name("TopMass"  ), "M (top) [GeV]"  , 100,  -1 , 1. ) );

  WplusPull_.push_back( fs->make<TH1D>(ns.name("WplusPt"    ), "p_{t} (W^{+}) [GeV]", 100,  -1 , 1. ) );
  WplusPull_.push_back( fs->make<TH1D>(ns.name("WplusEnergy"), "E (W^{+}) [GeV]"    , 100,  -1 , 1. ) );
  WplusPull_.push_back( fs->make<TH1D>(ns.name("WplusEta"   ), "#eta (W^{+})"       , 100,  -1 , 1. ) );
  WplusPull_.push_back( fs->make<TH1D>(ns.name("WplusPhi"   ), "#phi (W^{+})"       , 100,  -1 , 1. ) );
  WplusPull_.push_back( fs->make<TH1D>(ns.name("WplusMass"  ), "M (W^{+}) [GeV]"    , 100,  -1 , 1. ) );

  BPull_.push_back( fs->make<TH1D>(ns.name("BPt"    ), "p_{t} (b) [GeV]", 100,  -1 , 1. ) );
  BPull_.push_back( fs->make<TH1D>(ns.name("BEnergy"), "E (b) [GeV]"    , 100,  -1 , 1. ) );
  BPull_.push_back( fs->make<TH1D>(ns.name("BEta"   ), "#eta (b)"       , 100,  -1 , 1. ) );
  BPull_.push_back( fs->make<TH1D>(ns.name("BPhi"   ), "#phi (b)"       , 100,  -1 , 1. ) );
  BPull_.push_back( fs->make<TH1D>(ns.name("BMass"  ), "M (b) [GeV]"    , 100,  -1 , 1. ) );
    
  LepBarPull_.push_back( fs->make<TH1D>(ns.name("LepBarPt"    ), "p_{t} (l^{+}) [GeV]", 100,  -1 , 1. ) );
  LepBarPull_.push_back( fs->make<TH1D>(ns.name("LepBarEnergy"), "E (l^{+}) [GeV]"    , 100,  -1 , 1. ) );
  LepBarPull_.push_back( fs->make<TH1D>(ns.name("LepBarEta"   ), "#eta (l^{+})"       , 100,  -1 , 1. ) );
  LepBarPull_.push_back( fs->make<TH1D>(ns.name("LepBarPhi"   ), "#phi (l^{+})"       , 100,  -1 , 1. ) );
  LepBarPull_.push_back( fs->make<TH1D>(ns.name("LepBarMass"  ), "M (l^{+}) [GeV]"    , 100,  -1 , 1. ) );

  NuPull_.push_back( fs->make<TH1D>(ns.name("NuPt"    ), "p_{t} (#nu^{-}) [GeV]", 100,  -1 , 1. ) );
  NuPull_.push_back( fs->make<TH1D>(ns.name("NuEnergy"), "E (#nu^{-}) [GeV]"    , 100,  -1 , 1. ) );
  NuPull_.push_back( fs->make<TH1D>(ns.name("NuEta"   ), "#eta (#nu^{-})"       , 100,  -1 , 1. ) );
  NuPull_.push_back( fs->make<TH1D>(ns.name("NuPhi"   ), "#phi (#nu^{-})"       , 100,  -1 , 1. ) );
  NuPull_.push_back( fs->make<TH1D>(ns.name("NuMass"  ), "M (#nu^{-}) [GeV]"    , 100,  -1 , 1. ) );

  TopBarPull_.push_back( fs->make<TH1D>(ns.name("TopBarPt"    ), "p_{t} (#bar{t}) [GeV]", 100,  -1 , 1. ) );
  TopBarPull_.push_back( fs->make<TH1D>(ns.name("TopBarEnergy"), "E (#bar{t}) [GeV]"    , 100,  -1 , 1. ) );
  TopBarPull_.push_back( fs->make<TH1D>(ns.name("TopBarEta"   ), "#eta (#bar{t})"       , 100,  -1 , 1. ) );
  TopBarPull_.push_back( fs->make<TH1D>(ns.name("TopBarPhi"   ), "#phi (#bar{t})"       , 100,  -1 , 1. ) );
  TopBarPull_.push_back( fs->make<TH1D>(ns.name("TopBarMass"  ), "M (#bar{t}) [GeV]"    , 100,  -1 , 1. ) );

  WminusPull_.push_back( fs->make<TH1D>(ns.name("WminusPt"    ), "p_{t} (W^{-}) [GeV]", 100,  -1 , 1. ) ); 
  WminusPull_.push_back( fs->make<TH1D>(ns.name("WminusEnergy"), "E (W^{-}) [GeV]"    , 100,  -1 , 1. ) ); 
  WminusPull_.push_back( fs->make<TH1D>(ns.name("WminusEta"   ), "#eta (W^{-})"       , 100,  -1 , 1. ) ); 
  WminusPull_.push_back( fs->make<TH1D>(ns.name("WminusPhi"   ), "#phi (W^{-})"       , 100,  -1 , 1. ) ); 
  WminusPull_.push_back( fs->make<TH1D>(ns.name("WminusMass"  ), "M (W^{-}) [GeV]"    , 100,  -1 , 1. ) ); 

  BBarPull_.push_back( fs->make<TH1D>(ns.name("BBarPt"    ), "p_{t} (#bar{b}) [GeV]", 100,  -1 , 1. ) ); 
  BBarPull_.push_back( fs->make<TH1D>(ns.name("BBarEnergy"), "E (#bar{b}) [GeV]"    , 100,  -1 , 1. ) );
  BBarPull_.push_back( fs->make<TH1D>(ns.name("BBarEta"   ), "#eta (#bar{b})"       , 100,  -1 , 1. ) );
  BBarPull_.push_back( fs->make<TH1D>(ns.name("BBarPhi"   ), "#phi (#bar{b})"       , 100,  -1 , 1. ) );
  BBarPull_.push_back( fs->make<TH1D>(ns.name("BBarMass"  ), "M (#bar{b}) [GeV]"    , 100,  -1 , 1. ) );
  
  LepPull_.push_back( fs->make<TH1D>(ns.name("LepPt"    ), "p_{t} (l^{-}) [GeV]", 100,  -1 , 1. ) );
  LepPull_.push_back( fs->make<TH1D>(ns.name("LepEnergy"), "E (l^{-}) [GeV]"    , 100,  -1 , 1. ) );
  LepPull_.push_back( fs->make<TH1D>(ns.name("LepEta"   ), "#eta (l^{-})"       , 100,  -1 , 1. ) );
  LepPull_.push_back( fs->make<TH1D>(ns.name("LepPhi"   ), "#phi (l^{-})"       , 100,  -1 , 1. ) );
  LepPull_.push_back( fs->make<TH1D>(ns.name("LepMass"  ), "M (l^{-}) [GeV]"    , 100,  -1 , 1. ) );
  
  NuBarPull_.push_back( fs->make<TH1D>(ns.name("NuBarPt"    ), "p_{t} (#bar{#nu}^{-}) [GeV]", 100,  -1 , 1. ) );
  NuBarPull_.push_back( fs->make<TH1D>(ns.name("NuBarEnergy"), "E (#bar{#nu}^{-}) [GeV]"    , 100,  -1 , 1. ) );
  NuBarPull_.push_back( fs->make<TH1D>(ns.name("NuBarEta"   ), "#eta (#bar{#nu}^{-})"       , 100,  -1 , 1. ) );
  NuBarPull_.push_back( fs->make<TH1D>(ns.name("NuBarPhi"   ), "#phi (#bar{#nu}^{-})"       , 100,  -1 , 1. ) );
  NuBarPull_.push_back( fs->make<TH1D>(ns.name("NuBarMass"  ), "M (#bar{#nu}^{-}) [GeV]"    , 100,  -1 , 1. ) );
    
  TtBarPull_.push_back( fs->make<TH1D>(ns.name("TtBarPt"    ), "p_{t} (t#bar{t}) [GeV]", 100,  -1 , 1. ) );
  TtBarPull_.push_back( fs->make<TH1D>(ns.name("TtBarEnergy"), "E (t#bar{t}) [GeV]"    , 100,  -1 , 1. ) );
  TtBarPull_.push_back( fs->make<TH1D>(ns.name("TtBarEta"   ), "#eta (t#bar{t})"       , 100,  -1 , 1. ) );
  TtBarPull_.push_back( fs->make<TH1D>(ns.name("TtBarPhi"   ), "#phi (t#bar{t})"       , 100,  -1 , 1. ) );
  TtBarPull_.push_back( fs->make<TH1D>(ns.name("TtBarMass"  ), "M (t#bar{t}) [GeV]"    , 100,  -1 , 1. ) );
  
  LepLepBarPull_.push_back( fs->make<TH1D>(ns.name("LepLepBarPt"    ), "p_{t} (l^{+}l^{-}) [GeV]", 100,  -1 , 1. ) );
  LepLepBarPull_.push_back( fs->make<TH1D>(ns.name("LepLepBarEnergy"), "E (l^{+}l^{-}) [GeV]"    , 100,  -1 , 1. ) );
  LepLepBarPull_.push_back( fs->make<TH1D>(ns.name("LepLepBarEta"   ), "#eta (l^{+}l^{-})"       , 100,  -1 , 1. ) );
  LepLepBarPull_.push_back( fs->make<TH1D>(ns.name("LepLepBarPhi"   ), "#phi (l^{+}l^{-})"       , 100,  -1 , 1. ) );
  LepLepBarPull_.push_back( fs->make<TH1D>(ns.name("LepLepBarMass"  ), "M (l^{+}l^{-}) [GeV]"    , 100,  -1 , 1. ) );	 
}



/// book histograms for hypothesis specific histos and correlations between hypotheses
void
FullLepKinAnalyzer::bookQualityHistos(edm::Service<TFileService>& fs)
{
  NameScheme ns("qual");
  
  kinSolWeight_        = fs->make<TH1D>(ns.name("kinSolWeight"       ), "Weight of kin solution",           50,  0. , 1. ); 
  bJetIdcs_            = fs->make<TH1D>(ns.name("bJetIdcs"           ), "b jet indices used for hypo"      , 4, -0.5, 3.5);
  bBarJetIdcs_         = fs->make<TH1D>(ns.name("bBarJetIdcs"        ), "bbar jet indices used for hypo"   , 4, -0.5, 3.5);
  deltaM_              = fs->make<TH1D>(ns.name("deltaM"             ), "M_{top}-M{#bar{t}}",               50, -25., 25.);
  kinTCHEcorrelation_  = fs->make<TH2D>(ns.name("kinTCHEcorrelation" ), "mass reco vs. TCHE",        3, -0.5, 2.5, 2, -0.5, 1.5);
  kinSSVHEcorrelation_ = fs->make<TH2D>(ns.name("kinSSVHEcorrelation"), "mass reco vs. TCHE",        3, -0.5, 2.5, 2, -0.5, 1.5);   
}

/// fill histograms for reconstructed or generated particle properties in events with oppositely charged leptons: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::fillKinHistos(std::vector<TH1D*>& histos, const reco::Candidate& candidate)
{
  histos[0]->Fill( candidate.pt()     );
  histos[1]->Fill( candidate.energy() );  
  histos[2]->Fill( candidate.eta()    );
  histos[3]->Fill( candidate.phi()    );
  histos[4]->Fill( candidate.mass()   );
}


/// fill histograms for particle pulls in events with oppositely charged leptons: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::fillPullHistos(std::vector<TH1D*>& histos, const reco::Candidate& candidate,  const reco::Candidate& gencandidate)
{
  histos[0]->Fill( ( candidate.pt()    -gencandidate.pt() )     / gencandidate.pt()     );
  histos[1]->Fill( ( candidate.energy()-gencandidate.energy() ) / gencandidate.energy() );  
  histos[2]->Fill( ( candidate.eta()   -gencandidate.eta() )    / gencandidate.eta()    );
  histos[3]->Fill( ( candidate.phi()   -gencandidate.phi() )    / gencandidate.phi()    );
  histos[4]->Fill( ( candidate.mass()  -gencandidate.mass() )   / gencandidate.mass()   );
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
