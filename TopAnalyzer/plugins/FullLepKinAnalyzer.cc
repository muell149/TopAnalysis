#include "TLorentzVector.h"
#include "TopAnalysis/TopAnalyzer/plugins/FullLepKinAnalyzer.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "AnalysisDataFormats/TopObjects/interface/TtEventPartons.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

/// default constructor
FullLepKinAnalyzer::FullLepKinAnalyzer(const edm::ParameterSet& cfg):
  FullLepEvt_      (cfg.getParameter<edm::InputTag>("FullLepEvent"    )),
  hypoKey_         (cfg.getParameter<edm::InputTag>("hypoKey"         ))   
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
}

/// everything that has to be done after the event loop: summarizes if wantSummary_ is true
void
FullLepKinAnalyzer::endJob() 
{
}

/// book histograms for reconstructed particles properties: Pt, E, Eta, Phi, m
/// append wrong charge histos if chosen in config
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
}

/// book histograms for hypothesis specific histos and correlations between hypotheses
void
FullLepKinAnalyzer::bookQualityHistos(edm::Service<TFileService>& fs)
{

  NameScheme ns("qual");
  
  kinSolWeight_      = fs->make<TH1D>(ns.name("kinSolWeight"     ), "Weight of kin solution", 50,  0. , 1. );    
  bJetIdcs_   = fs->make<TH1D>(ns.name("bJetIdcs"    ),  "b jet indices used for hypo"     , 4, -0.5, 3.5);
  bBarJetIdcs_= fs->make<TH1D>(ns.name("bBarJetIdcs" ),  "bbar jet indices used for hypo"  , 4, -0.5, 3.5);    
  deltaM_  = fs->make<TH1D>(ns.name("deltaM"   ), "M_{top}-M{#bar{t}}", 50, -25., 25.);  
}

/// fill histograms for reconstructed particles properties in events with oppositely charged leptons: Pt, E, Eta, Phi, m
void
FullLepKinAnalyzer::fillKinHistos(std::vector<TH1D*>& histos, const reco::Candidate& candidate)
{
  histos[0]->Fill( candidate.pt()     );
  histos[1]->Fill( candidate.energy() );  
  histos[2]->Fill( candidate.eta()    );
  histos[3]->Fill( candidate.phi()    );
  histos[4]->Fill( candidate.mass()   );
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
