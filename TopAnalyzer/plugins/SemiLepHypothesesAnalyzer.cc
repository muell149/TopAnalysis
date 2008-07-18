#include "TopAnalysis/TopAnalyzer/plugins/SemiLepHypothesesAnalyzer.h"

#include "TopAnalysis/TopUtils/interface/NameScheme.h"

#include "TopQuarkAnalysis/TopTools/interface/TtSemiEvtPartons.h"

SemiLepHypothesesAnalyzer::SemiLepHypothesesAnalyzer(const edm::ParameterSet& cfg):
  semiEvt_ (cfg.getParameter<edm::InputTag>("semiEvent")),
  hypoKey_ (cfg.getParameter<edm::InputTag>("hypoKey"  )),
  nJetsMax_(cfg.getParameter<unsigned int> ("nJetsMax" )),
  hist_    (cfg.getParameter<std::string>  ("hist"     ))
{
}

void
SemiLepHypothesesAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{

  edm::Handle<TtSemiEvent> semiEvt;
  evt.getByLabel(semiEvt_, semiEvt);

  edm::Handle<int> hypoKeyHandle;
  evt.getByLabel(hypoKey_, hypoKeyHandle);
  TtSemiEvent::HypoKey& hypoKey = (TtSemiEvent::HypoKey&) *hypoKeyHandle;

  // -----------------------
  // fill histos for basic kinematic variables
  // -----------------------
  const reco::Candidate* HadTop   = semiEvt->hadronicTop(hypoKey);
  const reco::Candidate* HadW     = semiEvt->hadronicW  (hypoKey);
  const reco::Candidate* HadB     = semiEvt->hadronicB  (hypoKey);
  const reco::Candidate* HadQ     = semiEvt->lightQuarkQ(hypoKey);
  const reco::Candidate* HadP     = semiEvt->lightQuarkP(hypoKey);
  const reco::Candidate* LepTop   = semiEvt->leptonicTop(hypoKey);
  const reco::Candidate* LepW     = semiEvt->leptonicW  (hypoKey);
  const reco::Candidate* LepB     = semiEvt->leptonicB  (hypoKey);
  const reco::Candidate* Lepton   = semiEvt->lepton     (hypoKey);
  const reco::Candidate* Neutrino = semiEvt->neutrino   (hypoKey);

  fillKinHistos(hadTopKin_, *HadTop  );
  fillKinHistos(hadWKin_,   *HadW    );
  fillKinHistos(hadBKin_,   *HadB    );
  fillKinHistos(hadQKin_,   *HadQ    );
  fillKinHistos(hadPKin_,   *HadP    );
  fillKinHistos(lepTopKin_, *LepTop  );
  fillKinHistos(lepWKin_,   *LepW    );
  fillKinHistos(lepBKin_,   *LepB    );
  fillKinHistos(leptonKin_, *Lepton  );
  fillKinHistos(neutriKin_, *Neutrino);

  hadTopLepTopMassDiff->Fill( HadTop->mass() - LepTop->mass() );
  hadWLepWMassDiff    ->Fill( HadW  ->mass() - LepW  ->mass() );

  // -----------------------
  // fill resolution histos for kinematic variables
  // with respect to the generator particles
  // -----------------------
  if( semiEvt->genEvent()->isSemiLeptonic() ) {

    const reco::Candidate* genHadTop   = semiEvt->genHadronicTop();
    const reco::Candidate* genHadW     = semiEvt->genHadronicW();
    const reco::Candidate* genHadB     = semiEvt->genHadronicB();
    const reco::Candidate* genHadQ     = semiEvt->genHadronicQ();
    const reco::Candidate* genHadP     = semiEvt->genHadronicP();
    const reco::Candidate* genLepTop   = semiEvt->genLeptonicTop();
    const reco::Candidate* genLepW     = semiEvt->genLeptonicW();
    const reco::Candidate* genLepB     = semiEvt->genLeptonicB();
    const reco::Candidate* genLepton   = semiEvt->genLepton();
    const reco::Candidate* genNeutrino = semiEvt->genNeutrino();

    fillKinResHistos(hadTopKinRes_, *HadTop  , *genHadTop);
    fillKinResHistos(hadWKinRes_,   *HadW    , *genHadW);
    fillKinResHistos(hadBKinRes_,   *HadB    , *genHadB);
    fillKinResHistos(hadQKinRes_,   *HadQ    , *genHadQ);
    fillKinResHistos(hadPKinRes_,   *HadP    , *genHadP);
    fillKinResHistos(lepTopKinRes_, *LepTop  , *genLepTop);
    fillKinResHistos(lepWKinRes_,   *LepW    , *genLepW);
    fillKinResHistos(lepBKinRes_,   *LepB    , *genLepB);
    fillKinResHistos(leptonKinRes_, *Lepton  , *genLepton);
    fillKinResHistos(neutriKinRes_, *Neutrino, *genNeutrino);

  }

  // -----------------------
  // fill correlation histos for jet parton association
  // -----------------------
  fillJetCorrelHistos( semiEvt->jetMatch(hypoKey), semiEvt->jetMatch(TtSemiEvent::kGenMatch) );

  // -----------------------
  // fill histos related to quality of the TtSemiEvent
  // -----------------------
  fillQualityHistos( *semiEvt );

}

void 
SemiLepHypothesesAnalyzer::beginJob(const edm::EventSetup&)
{

  if( hist_.empty() ) throw edm::Exception( edm::errors::Configuration, "Empty string for hist in cfi file" );
  ofstream hist(hist_.c_str(), std::ios::out);

  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  bookKinHistos      (fs, hist);
  bookKinResHistos   (fs, hist);
  bookJetCorrelHistos(fs, hist);
  bookQualityHistos  (fs, hist);

}

void
SemiLepHypothesesAnalyzer::endJob() 
{
}

void
SemiLepHypothesesAnalyzer::bookKinHistos(edm::Service<TFileService>& fs, ofstream& hist)
{

  NameScheme ns("kin");

  hadTopKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadTopPt"  ), "p_{T} (t_{had}) [GeV]", 100,  0. , 500. ) );
  hadTopKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadTopEta" ), "#eta (t_{had})"       ,  60, -3. ,   3. ) );
  hadTopKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadTopPhi" ), "#phi (t_{had})"       ,  70, -3.5,   3.5) );
  hadTopKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadTopMass"), "M (t_{had}) [GeV]"    ,  60,  0. , 600. ) );

  hadWKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadWPt"  ), "p_{T} (W_{had}) [GeV]", 100,  0. , 500. ) );
  hadWKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadWEta" ), "#eta (W_{had})"       ,  60, -3. ,   3. ) );
  hadWKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadWPhi" ), "#phi (W_{had})"       ,  70, -3.5,   3.5) );
  hadWKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadWMass"), "M (W_{had}) [GeV]"    ,  50,  0. , 500. ) );

  hadBKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadBPt"  ), "p_{T} (b_{had}) [GeV]", 100,  0. , 500. ) );
  hadBKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadBEta" ), "#eta (b_{had})"       ,  60, -3. ,   3. ) );
  hadBKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadBPhi" ), "#phi (b_{had})"       ,  70, -3.5,   3.5) );
  hadBKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadBMass"), "M (b_{had}) [GeV]"    ,  60,  0. , 600. ) );

  hadQKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadQPt"  ), "p_{T} (q_{had}) [GeV]", 100,  0. , 500. ) );
  hadQKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadQEta" ), "#eta (q_{had})"       ,  60, -3. ,   3. ) );
  hadQKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadQPhi" ), "#phi (q_{had})"       ,  70, -3.5,   3.5) );
  hadQKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadQMass"), "M (q_{had}) [GeV]"    ,  60,  0. , 600. ) );

  hadPKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadPPt"  ), "p_{T} (#bar q_{had}) [GeV]", 100,  0. , 500. ) );
  hadPKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadPEta" ), "#eta (#bar q_{had})"       ,  60, -3. ,   3. ) );
  hadPKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadPPhi" ), "#phi (#bar q_{had})"       ,  70, -3.5,   3.5) );
  hadPKin_.push_back( fs->make<TH1F>(ns.name(hist, "hadPMass"), "M (#bar q_{had}) [GeV]"    ,  60,  0. , 600. ) );

  lepTopKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepTopPt"  ), "p_{T} (t_{lep}) [GeV]", 100,  0. , 500. ) );
  lepTopKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepTopEta" ), "#eta (t_{lep})"       ,  60, -3. ,   3. ) );
  lepTopKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepTopPhi" ), "#phi (t_{lep})"       ,  70, -3.5,   3.5) );
  lepTopKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepTopMass"), "M (t_{lep}) [GeV]"    ,  60,  0. , 600. ) );

  lepWKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepWPt"  ), "p_{T} (W_{lep}) [GeV]", 100,  0. , 500. ) );
  lepWKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepWEta" ), "#eta (W_{lep})"       ,  60, -3. ,   3. ) );
  lepWKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepWPhi" ), "#phi (W_{lep})"       ,  70, -3.5,   3.5) );
  lepWKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepWMass"), "M (W_{lep}) [GeV]"    ,  50,  0. , 500. ) );

  lepBKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepBPt"  ), "p_{T} (b_{lep}) [GeV]", 100,  0. , 500. ) );
  lepBKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepBEta" ), "#eta (b_{lep})"       ,  60, -3. ,   3. ) );
  lepBKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepBPhi" ), "#phi (b_{lep})"       ,  70, -3.5,   3.5) );
  lepBKin_.push_back( fs->make<TH1F>(ns.name(hist, "lepBMass"), "M (b_{lep}) [GeV]"    ,  60,  0. , 600. ) );

  leptonKin_.push_back( fs->make<TH1F>(ns.name(hist, "leptonPt"  ), "p_{T} (lepton) [GeV]", 100,  0. , 500. ) );
  leptonKin_.push_back( fs->make<TH1F>(ns.name(hist, "leptonEta" ), "#eta (lepton)"       ,  60, -3. ,   3. ) );
  leptonKin_.push_back( fs->make<TH1F>(ns.name(hist, "leptonPhi" ), "#phi (lepton)"       ,  70, -3.5,   3.5) );
  leptonKin_.push_back( fs->make<TH1F>(ns.name(hist, "leptonMass"), "M (lepton) [GeV]"    ,  60,  0. , 600. ) );

  neutriKin_.push_back( fs->make<TH1F>(ns.name(hist, "neutriPt"  ), "p_{T} (neutrino) [GeV]", 100,  0. , 500. ) );
  neutriKin_.push_back( fs->make<TH1F>(ns.name(hist, "neutriEta" ), "#eta (neutrino)"       ,  60, -3. ,   3. ) );
  neutriKin_.push_back( fs->make<TH1F>(ns.name(hist, "neutriPhi" ), "#phi (neutrino)"       ,  70, -3.5,   3.5) );
  neutriKin_.push_back( fs->make<TH1F>(ns.name(hist, "neutriMass"), "M (neutrino) [GeV]"    ,  60,  0. , 600. ) );  

  hadTopLepTopMassDiff = fs->make<TH1F>(ns.name(hist, "hadTopLepTopMassDiff"), "M (t_{had}) -  M (t_{lep}) [GeV]", 60, -300., 300);
  hadWLepWMassDiff     = fs->make<TH1F>(ns.name(hist, "hadWLepWMassDiff"    ), "M (W_{had}) -  M (W_{lep}) [GeV]", 60, -300., 300);

}

void
SemiLepHypothesesAnalyzer::bookKinResHistos(edm::Service<TFileService>& fs, ofstream& hist)
{

  NameScheme ns("kinRes");

  hadTopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadTopPt"  ), "(p_{T}^{rec}-p_{T}^{gen})/p_{T}^{gen} (t_{had})",  20, -1.2, 1.2) );
  hadTopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadTopEta" ), "(#eta^{rec}-#eta^{gen})/#eta^{gen} (t_{had})   ",  20, -1.2, 1.2) );
  hadTopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadTopPhi" ), "(#phi^{rec}-#phi^{gen})/#phi^{gen} (t_{had})   ",  20, -1.2, 1.2) );
  hadTopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadTopMass"), "(M^{rec}-M^{gen})/M^{gen} (t_{had})            ",  20, -1.2, 1.2) );

  hadWKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadWPt"  ), "(p_{T}^{rec}-p_{T}^{gen})/p_{T}^{gen} (W_{had})", 20, -1.2, 1.2) );
  hadWKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadWEta" ), "(#eta^{rec}-#eta^{gen})/#eta^{gen} (W_{had})   ", 20, -1.2, 1.2) );
  hadWKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadWPhi" ), "(#phi^{rec}-#phi^{gen})/#phi^{gen} (W_{had})   ", 20, -1.2, 1.2) );
  hadWKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadWMass"), "(M^{rec}-M^{gen})/M^{gen} (W_{had})            ", 20, -1.2, 1.2) );

  hadBKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadBPt"  ), "(p_{T}^{rec}-p_{T}^{gen})/p_{T}^{gen} (b_{had})", 20, -1.2, 1.2) );
  hadBKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadBEta" ), "(#eta^{rec}-#eta^{gen})/#eta^{gen} (b_{had})   ", 20, -1.2, 1.2) );
  hadBKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadBPhi" ), "(#phi^{rec}-#phi^{gen})/#phi^{gen} (b_{had})   ", 20, -1.2, 1.2) );
  hadBKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadBMass"), "(M^{rec}-M^{gen})/M^{gen} (b_{had})            ", 20, -1.2, 1.2) );

  hadQKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadQPt"  ), "(p_{T}^{rec}-p_{T}^{gen})/p_{T}^{gen} (q_{had})", 20, -1.2, 1.2) );
  hadQKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadQEta" ), "(#eta^{rec}-#eta^{gen})/#eta^{gen} (q_{had})   ", 20, -1.2, 1.2) );
  hadQKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadQPhi" ), "(#phi^{rec}-#phi^{gen})/#phi^{gen} (q_{had})   ", 20, -1.2, 1.2) );
  hadQKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadQMass"), "(M^{rec}-M^{gen})/M^{gen} (q_{had})            ", 20, -1.2, 1.2) );

  hadPKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadPPt"  ), "(p_{T}^{rec}-p_{T}^{gen})/p_{T}^{gen} (#bar q_{had})", 20, -1.2, 1.2) );
  hadPKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadPEta" ), "(#eta^{rec}-#eta^{gen})/#eta^{gen} (#bar q_{had})   ", 20, -1.2, 1.2) );
  hadPKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadPPhi" ), "(#phi^{rec}-#phi^{gen})/#phi^{gen} (#bar q_{had})   ", 20, -1.2, 1.2) );
  hadPKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "hadPMass"), "(M^{rec}-M^{gen})/M^{gen} (#bar q_{had})            ", 20, -1.2, 1.2) );

  lepTopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepTopPt"  ), "(p_{T}^{rec}-p_{T}^{gen})/p_{T}^{gen} (t_{lep})", 20, -1.2, 1.2) );
  lepTopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepTopEta" ), "(#eta^{rec}-#eta^{gen})/#eta^{gen} (t_{lep})   ", 20, -1.2, 1.2) );
  lepTopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepTopPhi" ), "(#phi^{rec}-#phi^{gen})/#phi^{gen} (t_{lep})   ", 20, -1.2, 1.2) );
  lepTopKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepTopMass"), "(M^{rec}-M^{gen})/M^{gen} (t_{lep})            ", 20, -1.2, 1.2) );

  lepWKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepWPt"  ), "(p_{T}^{rec}-p_{T}^{gen})/p_{T}^{gen} (W_{lep})", 20, -1.2, 1.2) );
  lepWKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepWEta" ), "(#eta^{rec}-#eta^{gen})/#eta^{gen} (W_{lep})   ", 20, -1.2, 1.2) );
  lepWKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepWPhi" ), "(#phi^{rec}-#phi^{gen})/#phi^{gen} (W_{lep})   ", 20, -1.2, 1.2) );
  lepWKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepWMass"), "(M^{rec}-M^{gen})/M^{gen} (W_{lep})            ", 20, -1.2, 1.2) );

  lepBKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepBPt"  ), "(p_{T}^{rec}-p_{T}^{gen})/p_{T}^{gen} (b_{lep})", 20, -1.2, 1.2) );
  lepBKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepBEta" ), "(#eta^{rec}-#eta^{gen})/#eta^{gen} (b_{lep})   ", 20, -1.2, 1.2) );
  lepBKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepBPhi" ), "(#phi^{rec}-#phi^{gen})/#phi^{gen} (b_{lep})   ", 20, -1.2, 1.2) );
  lepBKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "lepBMass"), "(M^{rec}-M^{gen})/M^{gen} (b_{lep})            ", 20, -1.2, 1.2) );

  leptonKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "leptonPt"  ), "(p_{T}^{rec}-p_{T}^{gen})/p_{T}^{gen} (lepton)", 20, -1.2, 1.2) );
  leptonKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "leptonEta" ), "(#eta^{rec}-#eta^{gen})/#eta^{gen} (lepton)   ", 20, -1.2, 1.2) );
  leptonKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "leptonPhi" ), "(#phi^{rec}-#phi^{gen})/#phi^{gen} (lepton)   ", 20, -1.2, 1.2) );
  leptonKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "leptonMass"), "(M^{rec}-M^{gen})/M^{gen} (lepton)            ", 20, -1.2, 1.2) );

  neutriKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "neutriPt"  ), "(p_{T}^{rec}-p_{T}^{gen})/p_{T}^{gen} (neutrino)", 20, -1.2, 1.2) );
  neutriKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "neutriEta" ), "(#eta^{rec}-#eta^{gen})/#eta^{gen} (neutrino)   ", 20, -1.2, 1.2) );
  neutriKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "neutriPhi" ), "(#phi^{rec}-#phi^{gen})/#phi^{gen} (neutrino)   ", 20, -1.2, 1.2) );
  neutriKinRes_.push_back( fs->make<TH1F>(ns.name(hist, "neutriMass"), "(M^{rec}-M^{gen})/M^{gen} (neutrino)            ", 20, -1.2, 1.2) );

}

void
SemiLepHypothesesAnalyzer::bookJetCorrelHistos(edm::Service<TFileService>& fs, ofstream& hist)
{

  NameScheme ns("jetCorrel");

  int nBins = nJetsMax_;
  double upEdge = nJetsMax_ + 0.5;

  hadBJetCorrel_ = fs->make<TH2F>(ns.name(hist, "hadB"), ns.name("hadB"), nBins, 0.5, upEdge, nBins, 0.5, upEdge);
  hadQJetCorrel_ = fs->make<TH2F>(ns.name(hist, "hadQ"), ns.name("hadQ"), nBins, 0.5, upEdge, nBins, 0.5, upEdge);
  hadPJetCorrel_ = fs->make<TH2F>(ns.name(hist, "hadP"), ns.name("hadP"), nBins, 0.5, upEdge, nBins, 0.5, upEdge);
  lepBJetCorrel_ = fs->make<TH2F>(ns.name(hist, "lepB"), ns.name("lepB"), nBins, 0.5, upEdge, nBins, 0.5, upEdge);

}

void
SemiLepHypothesesAnalyzer::bookQualityHistos(edm::Service<TFileService>& fs, ofstream& hist)
{

  NameScheme ns("qual1D");

  genMatchSumDR_ = fs->make<TH1F>(ns.name(hist, "genMatchSumDR"), "#Sigma #Delta R (genMatch)"          , 50, 0., 5.);
  genMatchSumPt_ = fs->make<TH1F>(ns.name(hist, "genMatchSumPt"), "#Sigma #Delta p_{T} (genMatch) [GeV]", 40, 0., 400.);
  mvaDisc_       = fs->make<TH1F>(ns.name(hist, "mvaDisc"),       "MVA discrim."                        , 20, 0., 1.);

  NameScheme ns2("qual2D");

  genMatchSumDRVsSumPt_      = fs->make<TH2F>(ns2.name(hist, "genMatchSumDRVsSumPt"),      "#Sigma #Delta R (genMatch) vs. #Sigma #Delta p_{T} (genMatch) [GeV]", 50, 0., 5., 40, 0., 400.);
  genMatchSumDRVsHadWMass_   = fs->make<TH2F>(ns2.name(hist, "genMatchSumDRVsHadWMass"),   "#Sigma #Delta R (genMatch) vs. M (W_{had}) [GeV] (genMatch)"        , 50, 0., 5., 50, 0., 500.);
  genMatchSumDRVsHadTopMass_ = fs->make<TH2F>(ns2.name(hist, "genMatchSumDRVsHadTopMass"), "#Sigma #Delta R (genMatch) vs. M (t_{had}) [GeV] (genMatch)"        , 50, 0., 5., 60, 0., 600.);
  genMatchSumDRVsMVADisc_    = fs->make<TH2F>(ns2.name(hist, "genMatchSumDRVsMVADisc"),    "#Sigma #Delta R (genMatch) vs. MVA discrim."                        , 50, 0., 5., 20, 0., 1.);
  mvaDiscVsHadWMass_   = fs->make<TH2F>(ns2.name(hist, "mvaDiscVsHadWMass"),   "MVA discrim. vs. M (W_{had}) [GeV] (MVADisc)"  , 20, 0., 1., 50, 0., 500.);
  mvaDiscVsHadTopMass_ = fs->make<TH2F>(ns2.name(hist, "mvaDiscVsHadTopMass"), "MVA discrim. vs. M (t_{had}) [GeV] (MVADisc)", 20, 0., 1., 60, 0., 600.);

}

void
SemiLepHypothesesAnalyzer::fillKinHistos(std::vector<TH1F*>& histos, const reco::Candidate& candidate)
{
  histos[0]->Fill( candidate.pt()   );
  histos[1]->Fill( candidate.eta()  );
  histos[2]->Fill( candidate.phi()  );
  histos[3]->Fill( candidate.mass() );
}

void
SemiLepHypothesesAnalyzer::fillKinResHistos(std::vector<TH1F*>& histos, const reco::Candidate& candidate,
					    const reco::Candidate& genCandidate)
{
  histos[0]->Fill( ( candidate.pt()   - genCandidate.pt()   ) / genCandidate.pt()   );
  histos[1]->Fill( ( candidate.eta()  - genCandidate.eta()  ) / genCandidate.eta()  );
  histos[2]->Fill( ( candidate.phi()  - genCandidate.phi()  ) / genCandidate.phi()  );
  histos[3]->Fill( ( candidate.mass() - genCandidate.mass() ) / genCandidate.mass() );
}

void
SemiLepHypothesesAnalyzer::fillJetCorrelHistos(const std::vector<int>& match, const std::vector<int>& matchCompare)
{

  hadBJetCorrel_->Fill( match[TtSemiEvtPartons::HadB]      +1, matchCompare[TtSemiEvtPartons::HadB]      +1);
  hadQJetCorrel_->Fill( match[TtSemiEvtPartons::LightQ]    +1, matchCompare[TtSemiEvtPartons::LightQ]    +1);
  hadPJetCorrel_->Fill( match[TtSemiEvtPartons::LightQBar] +1, matchCompare[TtSemiEvtPartons::LightQBar] +1);
  lepBJetCorrel_->Fill( match[TtSemiEvtPartons::LepB]      +1, matchCompare[TtSemiEvtPartons::LepB]      +1);

}

void
SemiLepHypothesesAnalyzer::fillQualityHistos(const TtSemiEvent& semiEvt)
{

  genMatchSumDR_->Fill( semiEvt.genMatchSumDR() );
  genMatchSumPt_->Fill( semiEvt.genMatchSumPt() );
  mvaDisc_      ->Fill( semiEvt.mvaDisc() );

  genMatchSumDRVsSumPt_     ->Fill( semiEvt.genMatchSumDR(), semiEvt.genMatchSumPt()                             );
  genMatchSumDRVsHadWMass_  ->Fill( semiEvt.genMatchSumDR(), semiEvt.hadronicW  (TtSemiEvent::kGenMatch)->mass() );
  genMatchSumDRVsHadTopMass_->Fill( semiEvt.genMatchSumDR(), semiEvt.hadronicTop(TtSemiEvent::kGenMatch)->mass() );
  genMatchSumDRVsMVADisc_   ->Fill( semiEvt.genMatchSumDR(), semiEvt.mvaDisc()                                   );
  mvaDiscVsHadWMass_        ->Fill( semiEvt.mvaDisc()      , semiEvt.hadronicW  (TtSemiEvent::kMVADisc)->mass()  );
  mvaDiscVsHadTopMass_      ->Fill( semiEvt.mvaDisc()      , semiEvt.hadronicTop(TtSemiEvent::kMVADisc)->mass()  );

}
