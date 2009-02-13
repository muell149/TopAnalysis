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
  if( !FullLepEvt->isHypoValid(hypoKey) ){
    edm::LogWarning ( "NonValidHyp" ) << "Hypothesis not valid for this event";
    return;
  }
  Nval++;
  
  //if( !FullLepEvt->isHypoValid(hypoKey) ||
  //    (hypoKey==TtFullLeptonicEvent::kGenMatch && FullLepEvt->genMatchSumDR()>maxSumDRGenMatch_) ||
  //    (hypoKey==TtFullLeptonicEvent::kKinFit   && FullLepEvt->fitProb()<minProbKinFit_         ) 
  //    ) {
  //  goodHypo_->Fill(0., weight); // not a good hypothesis
  //}
  //else goodHypo_->Fill(1., weight); // good hypothesis

  //if( !FullLepEvt->isHypoValid(TtFullLeptonicEvent::kGenMatch     ) ||
  //    !FullLepEvt->isHypoValid(TtFullLeptonicEvent::kKinFit       ) )
  //  return;  // return if any of the hypotheses is not valid

  // -----------------------
  // fill histos related to quality of the TtFullLeptonicEvent
  // -----------------------
  //fillQualityHistos(*FullLepEvt, weight);

  //if( FullLepEvt->genMatchSumDR() > maxSumDRGenMatch_ ||
  //    FullLepEvt->fitProb() < minProbKinFit_          ||
  //    FullLepEvt->mvaDisc() < minMVADisc_ )
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
  // fill correlation histos for jet parton association
  // -----------------------
//  fillJetCorrelHistos(FullLepEvt->jetMatch(hypoKey),
//		      FullLepEvt->jetMatch(TtFullLeptonicEvent::kGenMatch),
//		      weight);

}

void 
FullLepHypothesesAnalyzer::beginJob(const edm::EventSetup&)
{

  if( hist_.empty() ) throw edm::Exception( edm::errors::Configuration, "Empty string for hist in cfi file" );
  ofstream hist(hist_.c_str(), std::ios::out);

  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  bookKinHistos      (fs, hist);
  //bookKinResHistos   (fs, hist);
  //bookJetCorrelHistos(fs, hist);
  //bookQualityHistos  (fs, hist);

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


// void
// FullLepHypothesesAnalyzer::bookJetCorrelHistos(edm::Service<TFileService>& fs, ofstream& hist)
// {
// 
//   NameScheme ns("jetCorrel");
// 
//   int nBins = nJetsMax_;
//   double upEdge = nJetsMax_ + 0.5;
// 
//   hadBJetCorrel_ = fs->make<TH2F>(ns.name(hist, "hadB"), ns.name("hadB"), nBins, 0.5, upEdge, nBins, 0.5, upEdge);
//   hadQJetCorrel_ = fs->make<TH2F>(ns.name(hist, "hadQ"), ns.name("hadQ"), nBins, 0.5, upEdge, nBins, 0.5, upEdge);
//   hadPJetCorrel_ = fs->make<TH2F>(ns.name(hist, "hadP"), ns.name("hadP"), nBins, 0.5, upEdge, nBins, 0.5, upEdge);
//   lepBJetCorrel_ = fs->make<TH2F>(ns.name(hist, "lepB"), ns.name("lepB"), nBins, 0.5, upEdge, nBins, 0.5, upEdge);
// 
// }

// void
// FullLepHypothesesAnalyzer::bookQualityHistos(edm::Service<TFileService>& fs, ofstream& hist)
// {
// 
//   NameScheme ns("qual1D");
// 
//   goodHypo_ = fs->make<TH1F>(ns.name(hist, "goodHypo"), "good hypothesis", 2, -0.5, 1.5);
// 
//   genMatchSumDR_ = fs->make<TH1F>(ns.name(hist, "genMatchSumDR"), "#Sigma #Delta R (genMatch)"          , 50, 0., 5.);
//   genMatchSumPt_ = fs->make<TH1F>(ns.name(hist, "genMatchSumPt"), "#Sigma #Delta p_{T} (genMatch) [GeV]", 40, 0., 400.);
//   mvaDisc_       = fs->make<TH1F>(ns.name(hist, "mvaDisc"),       "MVA discrim."                        , 20, 0., 1.);
//   fitChi2_       = fs->make<TH1F>(ns.name(hist, "fitChi2"),       "#chi^{2} (kinFit)"                   , 20, 0., 2.);
//   fitProb_       = fs->make<TH1F>(ns.name(hist, "fitProb"),       "#chi^{2} probability (kinFit)"       , 20, 0., 1.);
// 
//   NameScheme ns2("qual2D");
// 
//   genMatchSumDRVsSumPt_      = fs->make<TH2F>(ns2.name(hist, "genMatchSumDRVsSumPt"),      "#Sigma #Delta R (genMatch) vs. #Sigma #Delta p_{T} (genMatch) [GeV]", 50, 0., 5., 40, 0., 400.);
//   genMatchSumDRVsHadWMass_   = fs->make<TH2F>(ns2.name(hist, "genMatchSumDRVsHadWMass"),   "#Sigma #Delta R (genMatch) vs. M (W_{had}) [GeV] (genMatch)"        , 50, 0., 5., 50, 0., 500.);
//   genMatchSumDRVsHadTopMass_ = fs->make<TH2F>(ns2.name(hist, "genMatchSumDRVsHadTopMass"), "#Sigma #Delta R (genMatch) vs. M (t_{had}) [GeV] (genMatch)"        , 50, 0., 5., 60, 0., 600.);
//   genMatchSumDRVsMVADisc_    = fs->make<TH2F>(ns2.name(hist, "genMatchSumDRVsMVADisc"),    "#Sigma #Delta R (genMatch) vs. MVA discrim."                        , 50, 0., 5., 20, 0., 1.);
//   genMatchSumDRVsFitProb_    = fs->make<TH2F>(ns2.name(hist, "genMatchSumDRVsFitProb"),    "#Sigma #Delta R (genMatch) vs. #chi^{2} probability (kinFit)"                      , 50, 0., 5., 20, 0., 1.);
//   mvaDiscVsHadWMass_   = fs->make<TH2F>(ns2.name(hist, "mvaDiscVsHadWMass"),   "MVA discrim. vs. M (W_{had}) [GeV] (MVADisc)"  , 20, 0., 1., 50, 0., 500.);
//   mvaDiscVsHadTopMass_ = fs->make<TH2F>(ns2.name(hist, "mvaDiscVsHadTopMass"), "MVA discrim. vs. M (t_{had}) [GeV] (MVADisc)", 20, 0., 1., 60, 0., 600.);
//   mvaDiscVsFitProb_       = fs->make<TH2F>(ns2.name(hist, "mvaDiscVsFitProb"), "MVA discrim. vs. #chi^{2} probability (kinFit)", 20, 0., 1., 20, 0., 1.);
//   fitProbVsHadWMass_   = fs->make<TH2F>(ns2.name(hist, "fitProbVsHadWMass"),   "#chi^{2} probability (kinFit) vs. M (W_{had}) [GeV] (MVADisc)"  , 20, 0., 1., 50, 0., 500.);
//   fitProbVsHadTopMass_ = fs->make<TH2F>(ns2.name(hist, "fitProbVsHadTopMass"), "#chi^{2} probability (kinFit) vs. M (t_{had}) [GeV] (MVADisc)", 20, 0., 1., 60, 0., 600.);
// 
// }

void
FullLepHypothesesAnalyzer::fillKinHistos(std::vector<TH1F*>& histos, const reco::Candidate& candidate, const double& weight)
{
  histos[0]->Fill( candidate.pt()   , weight );
  histos[1]->Fill( candidate.eta()  , weight );
  histos[2]->Fill( candidate.phi()  , weight );
  histos[3]->Fill( candidate.mass() , weight );
}

// void
// FullLepHypothesesAnalyzer::fillJetCorrelHistos(const std::vector<int>& match, const std::vector<int>& matchCompare, const double& weight)
// {
// 
//   hadBJetCorrel_->Fill( match[TtFullLepEvtPartons::HadB]     +1, matchCompare[TtFullLepEvtPartons::HadB]     +1, weight );
//   hadQJetCorrel_->Fill( match[TtFullLepEvtPartons::LightQ]   +1, matchCompare[TtFullLepEvtPartons::LightQ]   +1, weight );
//   hadPJetCorrel_->Fill( match[TtFullLepEvtPartons::LightQBar]+1, matchCompare[TtFullLepEvtPartons::LightQBar]+1, weight );
//   lepBJetCorrel_->Fill( match[TtFullLepEvtPartons::LepB]     +1, matchCompare[TtFullLepEvtPartons::LepB]     +1, weight );
// 
// }

// void
// FullLepHypothesesAnalyzer::fillQualityHistos(const TtFullLeptonicEvent& FullLepEvt, const double& weight)
// {
// 
//   // genMatch histos
//   if( FullLepEvt.isHypoValid(TtFullLeptonicEvent::kGenMatch) ) {
//     genMatchSumDR_->Fill( FullLepEvt.genMatchSumDR() , weight );
//     genMatchSumPt_->Fill( FullLepEvt.genMatchSumPt() , weight );
//     genMatchSumDRVsSumPt_     ->Fill( FullLepEvt.genMatchSumDR() , FullLepEvt.genMatchSumPt()                                     , weight );
//     genMatchSumDRVsHadWMass_  ->Fill( FullLepEvt.genMatchSumDR() , FullLepEvt.hadronicW  (TtFullLeptonicEvent::kGenMatch)->mass() , weight );
//     genMatchSumDRVsHadTopMass_->Fill( FullLepEvt.genMatchSumDR() , FullLepEvt.hadronicTop(TtFullLeptonicEvent::kGenMatch)->mass() , weight );
//     // vs. MVADisc
//     if( FullLepEvt.isHypoValid(TtFullLeptonicEvent::kMVADisc) )
//       genMatchSumDRVsMVADisc_->Fill( FullLepEvt.genMatchSumDR() , FullLepEvt.mvaDisc() , weight );
//     // vs. KinFit
//     if( FullLepEvt.isHypoValid(TtFullLeptonicEvent::kKinFit) )
//       genMatchSumDRVsFitProb_->Fill( FullLepEvt.genMatchSumDR() , FullLepEvt.fitProb() , weight );
//   }
// 
//   // MVADisc histos
//   if( FullLepEvt.isHypoValid(TtFullLeptonicEvent::kMVADisc) ) {
//     mvaDisc_->Fill( FullLepEvt.mvaDisc() , weight );
//     mvaDiscVsHadWMass_  ->Fill( FullLepEvt.mvaDisc() , FullLepEvt.hadronicW  (TtFullLeptonicEvent::kMVADisc)->mass() , weight );
//     mvaDiscVsHadTopMass_->Fill( FullLepEvt.mvaDisc() , FullLepEvt.hadronicTop(TtFullLeptonicEvent::kMVADisc)->mass() , weight );
//     // vs. kinFit
//     if( FullLepEvt.isHypoValid(TtFullLeptonicEvent::kKinFit) )
//       mvaDiscVsFitProb_->Fill( FullLepEvt.mvaDisc() , FullLepEvt.fitProb() , weight );
//   }
// 
//   // kinFit histos
//   if( FullLepEvt.isHypoValid(TtFullLeptonicEvent::kKinFit) ) {
//     fitChi2_->Fill( FullLepEvt.fitChi2() , weight );
//     fitProb_->Fill( FullLepEvt.fitProb() , weight );
//     fitProbVsHadWMass_  ->Fill( FullLepEvt.fitProb() , FullLepEvt.hadronicW   (TtFullLeptonicEvent::kKinFit)->mass() , weight );
//     fitProbVsHadTopMass_->Fill( FullLepEvt.fitProb() , FullLepEvt.hadronicTop (TtFullLeptonicEvent::kKinFit)->mass() , weight );
//   }
// 
// }
