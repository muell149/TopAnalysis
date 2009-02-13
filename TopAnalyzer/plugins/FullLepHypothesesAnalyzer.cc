#include "TopAnalysis/TopAnalyzer/plugins/FullLepHypothesesAnalyzer.h"

#include "TopAnalysis/TopUtils/interface/NameScheme.h"

#include "TopQuarkAnalysis/TopTools/interface/TtFullLepEvtPartons.h"


int Nava;
int Nval;

FullLepHypothesesAnalyzer::FullLepHypothesesAnalyzer(const edm::ParameterSet& cfg):
  FullLepEvt_      (cfg.getParameter<edm::InputTag>("FullLepEvent"    )),
  hypoKey_         (cfg.getParameter<edm::InputTag>("hypoKey"         )),
  wgt_             (cfg.getParameter<edm::InputTag>("weight"          )),
  nJetsMax_        (cfg.getParameter<unsigned int> ("nJetsMax"        )),
  maxSumDRGenMatch_(cfg.getParameter<double>       ("maxSumDRGenMatch")),
  minProbKinFit_   (cfg.getParameter<double>       ("minProbKinFit"   )),
  hist_            (cfg.getParameter<std::string>  ("hist"            ))
{
  Nava = 0;
  Nval = 0;
}

void
FullLepHypothesesAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{

  edm::Handle<TtFullLeptonicEvent> FullLepEvt;
  evt.getByLabel(FullLepEvt_, FullLepEvt);

  edm::Handle<int> hypoKeyHandle;
  evt.getByLabel(hypoKey_, hypoKeyHandle);
  TtEvent::HypoClassKey& hypoKey = (TtEvent::HypoClassKey&) *hypoKeyHandle;

  edm::Handle<double> wgt;
  evt.getByLabel(wgt_, wgt);
  double weight = *wgt;

  // -----------------------
  // check if hypothesis is valid in this event
  // and if it satisfies some quality criteria
  // -----------------------
  
  if( !FullLepEvt->isHypoAvailable(hypoKey) ){
    edm::LogWarning ( "NonValidHyp" ) << "Hypothesis not available for this event";
    return;
  }
  Nava++;
  
  if( !FullLepEvt->isHypoValid(hypoKey) )  {
    goodHypo_->Fill(0., weight); // not a good hypothesis
  }
  else goodHypo_->Fill(1., weight); // good hypothesis

  if( !FullLepEvt->isHypoValid(hypoKey) ){
    edm::LogWarning ( "NonValidHyp" ) << "Hypothesis not valid for this event";
    return;  // return if any of the hypotheses is not valid
  }
  Nval++;  

  // -----------------------
  // fill histos related to quality of the TtFullLeptonicEvent
  // -----------------------
  fillQualityHistos(*FullLepEvt, weight);

  //if( FullLepEvt->genMatchSumDR() > maxSumDRGenMatch_ )
  //  return; // return if any of the quality criteria is not fulfilled

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
  
  // -----------------------
  // fill resolution histos for kinematic variables
  // with respect to the generator particles
  // -----------------------
  if( FullLepEvt->genEvent()->isFullLeptonic() ) {   
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

    fillKinResHistos(TopKinRes_,    *Top,   *genTop,    weight);
    fillKinResHistos(WplusKinRes_,  *Wplus, *genWplus,  weight);
    fillKinResHistos(BKinRes_,      *B,     *genB,      weight);
    fillKinResHistos(LepBarKinRes_, *LepBar,*genLepBar, weight);
    fillKinResHistos(NuKinRes_,     *Nu,    *genNu,     weight);

    fillKinResHistos(TopBarKinRes_, *TopBar,*genTopBar, weight);
    fillKinResHistos(WminusKinRes_, *Wminus,*genWminus, weight);
    fillKinResHistos(BBarKinRes_,   *BBar,  *genBBar,   weight);
    fillKinResHistos(LepKinRes_,    *Lep,   *genLep,    weight);
    fillKinResHistos(NuBarKinRes_,  *NuBar, *genNuBar,  weight); 
  }      
}

void 
FullLepHypothesesAnalyzer::beginJob(const edm::EventSetup&)
{
  if( hist_.empty() ) throw edm::Exception( edm::errors::Configuration, "Empty string for hist in cfi file" );
  ofstream hist(hist_.c_str(), std::ios::out);

  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  bookKinHistos      (fs, hist);
  bookKinResHistos   (fs, hist);
  bookQualityHistos  (fs, hist);
}

void
FullLepHypothesesAnalyzer::endJob() 
{
  std::cout << "++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << "Summary for Hypothese " << hypoKey_ << std::endl;
  std::cout << "number of available events is " << Nava << std::endl;
  std::cout << "number of valid events is " << Nval << std::endl;
  std::cout << "++++++++++++++++++++++++++++++++" << std::endl;
}

void
FullLepHypothesesAnalyzer::bookKinHistos(edm::Service<TFileService>& fs, ofstream& hist)
{

  NameScheme ns("kin");

  TopKin_.push_back( fs->make<TH1F>(ns.name(hist, "TopPt"  ), "p_{t} (t) [GeV]", 50,  0. , 500. ) );
  TopKin_.push_back( fs->make<TH1F>(ns.name(hist, "TopEta" ), "#eta (t)"       , 34, -3.4,   3.4) );
  TopKin_.push_back( fs->make<TH1F>(ns.name(hist, "TopPhi" ), "#phi (t)"       , 34, -3.4,   3.4) );
  TopKin_.push_back( fs->make<TH1F>(ns.name(hist, "TopMass"), "M (top) [GeV]"    , 30,  0. , 600. ) );

  WplusKin_.push_back( fs->make<TH1F>(ns.name(hist, "WplusPt"  ), "p_{t} (W^{+}) [GeV]", 50,  0. , 500. ) );
  WplusKin_.push_back( fs->make<TH1F>(ns.name(hist, "WplusEta" ), "#eta (W^{+})"       , 34, -3.4,   3.4) );
  WplusKin_.push_back( fs->make<TH1F>(ns.name(hist, "WplusPhi" ), "#phi (W^{+})"       , 34, -3.4,   3.4) );
  WplusKin_.push_back( fs->make<TH1F>(ns.name(hist, "WplusMass"), "M (W^{+}) [GeV]"    , 30,  0. , 600. ) );

  BKin_.push_back( fs->make<TH1F>(ns.name(hist, "BPt"  ), "p_{t} (b) [GeV]", 50,  0. , 500. ) );
  BKin_.push_back( fs->make<TH1F>(ns.name(hist, "BEta" ), "#eta (b)"       , 34, -3.4,   3.4) );
  BKin_.push_back( fs->make<TH1F>(ns.name(hist, "BPhi" ), "#phi (b)"       , 34, -3.4,   3.4) );
  BKin_.push_back( fs->make<TH1F>(ns.name(hist, "BMass"), "M (b) [GeV]"    , 30,  0. , 600. ) );
    
  LepBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "LepBarPt"  ), "p_{t} (l^{+}) [GeV]", 50,  0. , 500. ) );
  LepBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "LepBarEta" ), "#eta (l^{+})"       , 34, -3.4,   3.4) );
  LepBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "LepBarPhi" ), "#phi (l^{+})"       , 34, -3.4,   3.4) );
  LepBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "LepBarMass"), "M (l^{+}) [GeV]"    , 30,  0. , 600. ) ); 

  NuKin_.push_back( fs->make<TH1F>(ns.name(hist, "NuPt"  ), "p_{t} (#nu^{-}) [GeV]", 50,  0. , 500. ) );
  NuKin_.push_back( fs->make<TH1F>(ns.name(hist, "NuEta" ), "#eta (#nu^{-})"       , 34, -3.4,   3.4) );
  NuKin_.push_back( fs->make<TH1F>(ns.name(hist, "NuPhi" ), "#phi (#nu^{-})"       , 34, -3.4,   3.4) );
  NuKin_.push_back( fs->make<TH1F>(ns.name(hist, "NuMass"), "M (#nu^{-}) [GeV]"    , 30,  0. , 600. ) );

  TopBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "TopBarPt"  ), "p_{t} (#bar{t}) [GeV]", 50,  0. , 500. ) );
  TopBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "TopBarEta" ), "#eta (#bar{t})"       , 34, -3.4,   3.4) );
  TopBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "TopBarPhi" ), "#phi (#bar{t})"       , 34, -3.4,   3.4) );
  TopBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "TopBarMass"), "M (#bar{t}) [GeV]"    , 30,  0. , 600. ) );

  WminusKin_.push_back( fs->make<TH1F>(ns.name(hist, "WminusPt"  ), "p_{t} (W^{-}) [GeV]", 50,  0. , 500. ) );
  WminusKin_.push_back( fs->make<TH1F>(ns.name(hist, "WminusEta" ), "#eta (W^{-})"       , 34, -3.4,   3.4) );
  WminusKin_.push_back( fs->make<TH1F>(ns.name(hist, "WminusPhi" ), "#phi (W^{-})"       , 34, -3.4,   3.4) );
  WminusKin_.push_back( fs->make<TH1F>(ns.name(hist, "WminusMass"), "M (W^{-}) [GeV]"    , 30,  0. , 600. ) );

  BBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "BBarPt"  ), "p_{t} (#bar{b}) [GeV]", 50,  0. , 500. ) );
  BBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "BBarEta" ), "#eta (#bar{b})"       , 34, -3.4,   3.4) );
  BBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "BBarPhi" ), "#phi (#bar{b})"       , 34, -3.4,   3.4) );
  BBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "BBarMass"), "M (#bar{b}) [GeV]"    , 30,  0. , 600. ) ); 
  
  LepKin_.push_back( fs->make<TH1F>(ns.name(hist, "LepPt"  ), "p_{t} (l^{-}) [GeV]", 50,  0. , 500. ) );
  LepKin_.push_back( fs->make<TH1F>(ns.name(hist, "LepEta" ), "#eta (l^{-})"       , 34, -3.4,   3.4) );
  LepKin_.push_back( fs->make<TH1F>(ns.name(hist, "LepPhi" ), "#phi (l^{-})"       , 34, -3.4,   3.4) );
  LepKin_.push_back( fs->make<TH1F>(ns.name(hist, "LepMass"), "M (l^{-}) [GeV]"    , 30,  0. , 600. ) );
  
  NuBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "NuBarPt"  ), "p_{t} (#bar{#nu}^{-}) [GeV]", 50,  0. , 500. ) );
  NuBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "NuBarEta" ), "#eta (#bar{#nu}^{-})"       , 34, -3.4,   3.4) );
  NuBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "NuBarPhi" ), "#phi (#bar{#nu}^{-})"       , 34, -3.4,   3.4) );
  NuBarKin_.push_back( fs->make<TH1F>(ns.name(hist, "NuBarMass"), "M (#bar{#nu}^{-}) [GeV]"    , 30,  0. , 600. ) );      
}

void
FullLepHypothesesAnalyzer::bookKinResHistos(edm::Service<TFileService>& fs, ofstream& hist)
{

  NameScheme ns("res");

  TopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "TopPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (t)",    20, -1.2, 1.2 ) );
  TopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "TopEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (t)", 20, -1.2, 1.2 ) );
  TopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "TopPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (t)", 20, -1.2, 1.2 ) );
  TopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "TopMassRes"), "M_{rec}-M_{gen}/M_{gen} (t)",          20, -1.2, 1.2 ) );
  
  WplusKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "WplusPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (W^{+})",    20, -1.2, 1.2 ) );
  WplusKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "WplusEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (W^{+})", 20, -1.2, 1.2 ) );
  WplusKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "WplusPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (W^{+})", 20, -1.2, 1.2 ) );
  WplusKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "WplusMassRes"), "M_{rec}-M_{gen}/M_{gen} (W^{+})",          20, -1.2, 1.2 ) );  

  BKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "BPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (b)",    20, -1.2, 1.2 ) );
  BKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "BEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (b)", 20, -1.2, 1.2 ) );
  BKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "BPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (b)", 20, -1.2, 1.2 ) );
  BKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "BMassRes"), "M_{rec}-M_{gen}/M_{gen} (b)",          20, -1.2, 1.2 ) );  

  LepBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "LepBarPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (l^{+})",    20, -1.2, 1.2 ) );
  LepBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "LepBarEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (l^{+})", 20, -1.2, 1.2 ) );
  LepBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "LepBarPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (l^{+})", 20, -1.2, 1.2 ) );
  LepBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "LepBarMassRes"), "M_{rec}-M_{gen}/M_{gen} (l^{+})",          20, -1.2, 1.2 ) ); 

  NuKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "NuPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} #nu",    20, -1.2, 1.2 ) );
  NuKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "NuEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} #nu", 20, -1.2, 1.2 ) );
  NuKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "NuPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} #nu", 20, -1.2, 1.2 ) );
  NuKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "NuMassRes"), "M_{rec}-M_{gen}/M_{gen} #nu",          20, -1.2, 1.2 ) ); 

  TopBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "TopBarPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} #bar{t}",    20, -1.2, 1.2 ) );
  TopBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "TopBarEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} #bar{t}", 20, -1.2, 1.2 ) );
  TopBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "TopBarPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} #bar{t}", 20, -1.2, 1.2 ) );
  TopBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "TopBarMassRes"), "M_{rec}-M_{gen}/M_{gen} #bar{t}",          20, -1.2, 1.2 ) ); 

  WminusKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "WminusPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (W^{-})",    20, -1.2, 1.2 ) );
  WminusKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "WminusEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (W^{-})", 20, -1.2, 1.2 ) );
  WminusKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "WminusPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (W^{-})", 20, -1.2, 1.2 ) );
  WminusKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "WminusMassRes"), "M_{rec}-M_{gen}/M_{gen} (W^{-})",          20, -1.2, 1.2 ) ); 

  BBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "BBarPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (#bar{b})",    20, -1.2, 1.2 ) );
  BBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "BBarEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (#bar{b})", 20, -1.2, 1.2 ) );
  BBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "BBarPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (#bar{b})", 20, -1.2, 1.2 ) );
  BBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "BBarMassRes"), "M_{rec}-M_{gen}/M_{gen} (#bar{b})",          20, -1.2, 1.2 ) ); 
  
  LepKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "LepPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (l)",    20, -1.2, 1.2 ) );
  LepKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "LepEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (l)", 20, -1.2, 1.2 ) );
  LepKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "LepPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (l)", 20, -1.2, 1.2 ) );
  LepKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "LepMassRes"), "M_{rec}-M_{gen}/M_{gen} (l)",          20, -1.2, 1.2 ) ); 
  
  NuBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "NuBarPtRes"  ), "p_{t,rec}-p_{t,gen}/p_{t,gen} (#bar{#nu})",    20, -1.2, 1.2 ) );
  NuBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "NuBarEtaRes" ), "#eta_{rec}-#eta_{gen}/#eta_{gen} (#bar{#nu})", 20, -1.2, 1.2 ) );
  NuBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "NuBarPhiRes" ), "#phi_{rec}-#phi_{gen}/#phi_{gen} (#bar{#nu})", 20, -1.2, 1.2 ) );
  NuBarKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "NuBarMassRes"), "M_{rec}-M_{gen}/M_{gen} (#bar{#nu})",          20, -1.2, 1.2 ) );   
}

void
FullLepHypothesesAnalyzer::bookQualityHistos(edm::Service<TFileService>& fs, ofstream& hist)
{

  NameScheme ns("qual1D");

  goodHypo_ = fs->make<TH1F>(ns.name(hist, "goodHypo"), "good hypothesis", 2, -0.5, 1.5);

  genMatchSumDR_ = fs->make<TH1F>(ns.name(hist, "genMatchSumDR"), "#Sigma #Delta R (genMatch)"          , 50, 0., 5.);
  genMatchSumPt_ = fs->make<TH1F>(ns.name(hist, "genMatchSumPt"), "#Sigma #Delta p_{T} (genMatch) [GeV]", 40, 0., 400.);
}

void
FullLepHypothesesAnalyzer::fillKinHistos(std::vector<TH1F*>& histos, const reco::Candidate& candidate, const double& weight)
{
  histos[0]->Fill( candidate.pt()   , weight );
  histos[1]->Fill( candidate.eta()  , weight );
  histos[2]->Fill( candidate.phi()  , weight );
  histos[3]->Fill( candidate.mass() , weight );
}

void
FullLepHypothesesAnalyzer::fillKinResHistos(std::vector<TH1F*>& histos, const reco::Candidate& candidate,
					    const reco::Candidate& genCandidate, const double& weight)
{
  histos[0]->Fill( (candidate.pt()  -genCandidate.pt()  )/genCandidate.pt()   , weight );
  histos[1]->Fill( (candidate.eta() -genCandidate.eta() )/genCandidate.eta()  , weight );
  histos[2]->Fill( (candidate.phi() -genCandidate.phi() )/genCandidate.phi()  , weight );
  histos[3]->Fill( (candidate.mass()-genCandidate.mass())/genCandidate.mass() , weight );
}

void
FullLepHypothesesAnalyzer::fillQualityHistos(const TtFullLeptonicEvent& FullLepEvt, const double& weight)
{

  // genMatch histos
  if( FullLepEvt.isHypoValid(TtFullLeptonicEvent::kGenMatch) ) {
    genMatchSumDR_->Fill( FullLepEvt.genMatchSumDR() , weight );
    genMatchSumPt_->Fill( FullLepEvt.genMatchSumPt() , weight ); 
  }  
}
