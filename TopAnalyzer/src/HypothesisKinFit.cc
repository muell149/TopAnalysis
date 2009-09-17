#include "TopAnalysis/TopAnalyzer/interface/HypothesisKinFit.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"

/// default constructor for fw lite
HypothesisKinFit::HypothesisKinFit()
{
}

/// default constructor for full fw
HypothesisKinFit::HypothesisKinFit(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void HypothesisKinFit::book()
{
  /** 
      Monitoring Variables
  **/
  // fit probability of the best fit hypothesis
  hists_["prob"       ] = new TH1F( "prob"       , "prob"      ,   100,    0.,    1. );
  // chi2 of the best fit hypothesis
  hists_["chi2"       ] = new TH1F( "chi2"       , "chi2"      ,   100,    0.,   10. );
  // delta chi2 between best and second best fit hyothesis
  hists_["delChi2"    ] = new TH1F( "delChi2"    , "delChi2"   ,   100,    0.,   10. );
  // difference of hadBQuark index between genMatch and kinFit 
  hists_["hadBQuark"  ] = new TH1F( "hadBQuark"  , "hadBQuark" ,     9,   -4.,    4. );
  // difference of lepBQuark index between genMatch and kinFit 
  hists_["lepBQuark"  ] = new TH1F( "lepBQuark"  , "lepBQuark" ,     9,   -4.,    4. );
  // smallest difference of the two lightQuark indices between genMatch and kinFit 
  // (taking into accont that the two indices can be switched)
  hists_["lightQuark" ] = new TH1F( "lightQuark" , "lightQuark",     9,   -4.,    4. );

  /** 
      Pull Distributions (Relative to the MC Truth)
  **/
  // hadronic top b pt
  hists_["hadBQuarkPt_"  ] = new TH1F( "hadBQuarkPt_"   , "hadBQuarkPt_"    ,  100,  -5.,   5. );
  // hadronic top b eta
  hists_["hadBQuarkEta_" ] = new TH1F( "hadBQuarkEta_"  , "hadBQuarkEta_"   ,  100,  -5.,   5. );
  // hadronic top b phi
  hists_["hadBQuarkPhi_" ] = new TH1F( "hadBQuarkPhi_"  , "hadBQuarkPhi_"   ,  100,  -5.,   5. );
  // leptonic top b pt
  hists_["lepBQuarkPt_"  ] = new TH1F( "lepBQuarkPt_"   , "lepBQuarkPt_"    ,  100,  -5.,   5. );
  // leptonic top b eta
  hists_["lepBQuarkEta_" ] = new TH1F( "lepBQuarkEta_"  , "lepBQuarkEta_"   ,  100,  -5.,   5. );
  // leptonic top b phi
  hists_["lepBQuarkPhi_" ] = new TH1F( "lepBQuarkPhi_"  , "lepBQuarkPhi_"   ,  100,  -5.,   5. );
  // lightQuark pt
  hists_["lightQuarkPt_" ] = new TH1F( "lightQuarkPt_"  , "lightQuarkPt_"   ,  100,  -5.,   5. );
  // lightQuark b eta
  hists_["lightQuarkEta_"] = new TH1F( "lightQuarkEta_" , "lightQuarkEta_"  ,  100,  -5.,   5. );
  // lightQuark b phi
  hists_["lightQuarkPhi_"] = new TH1F( "lightQuarkPhi_" , "lightQuarkPhi_"  ,  100,  -5.,   5. );
  // lepton pt
  hists_["leptonPt_"     ] = new TH1F( "leptonPt_"      , "leptonPt_"       ,  100,  -5.,   5. );
  // lepton eta
  hists_["leptonEta_"    ] = new TH1F( "leptonEta_"     , "leptonEta_"      ,  100,  -5.,   5. );
  // lepton phi
  hists_["leptonPhi_"    ] = new TH1F( "leptonPhi_"     , "leptonPhi_"      ,  100,  -5.,   5. );
  // neutrino pt
  hists_["neutrinoPt_"   ] = new TH1F( "neutrinoPt_"    , "neutrinoPt_"     ,  100,  -5.,   5. );
  // neutrino eta
  hists_["neutrinoEta_"  ] = new TH1F( "neutrinoEta_"   , "neutrinoEta_"    ,  100,  -5.,   5. );
  // neutrino phi
  hists_["neutrinoPhi_"  ] = new TH1F( "neutrinoPhi_"   , "neutrinoPhi_"    ,  100,  -5.,   5. );

  /** 
      Pull Distributions (Relative to the Reco Input -- this one still needs changes in the 
      TtSemiLeptonicEvent to allow access to the original reco objects
  **/
  // hadronic top b pt
  hists_["hadBQuarkPt"   ] = new TH1F( "hadBQuarkPt"    , "hadBQuarkPt"     ,  100,  -5.,   5. );
  // hadronic top b eta
  hists_["hadBQuarkEta"  ] = new TH1F( "hadBQuarkEta"   , "hadBQuarkEta"    ,  100,  -5.,   5. );
  // hadronic top b phi
  hists_["hadBQuarkPhi"  ] = new TH1F( "hadBQuarkPhi"   , "hadBQuarkPhi"    ,  100,  -5.,   5. );
  // leptonic top b pt
  hists_["lepBQuarkPt"   ] = new TH1F( "lepBQuarkPt"    , "lepBQuarkPt"     ,  100,  -5.,   5. );
  // leptonic top b eta
  hists_["lepBQuarkEta"  ] = new TH1F( "lepBQuarkEta"   , "lepBQuarkEta"    ,  100,  -5.,   5. );
  // leptonic top b phi
  hists_["lepBQuarkPhi"  ] = new TH1F( "lepBQuarkPhi"   , "lepBQuarkPhi"    ,  100,  -5.,   5. );
  // lightQuark pt
  hists_["lightQuarkPt"  ] = new TH1F( "lightQuarkPt"   , "lightQuarkPt"    ,  100,  -5.,   5. );
  // lightQuark b eta
  hists_["lightQuarkEta" ] = new TH1F( "lightQuarkEta"  , "lightQuarkEta"   ,  100,  -5.,   5. );
  // lightQuark b phi
  hists_["lightQuarkPhi" ] = new TH1F( "lightQuarkPhi"  , "lightQuarkPhi"   ,  100,  -5.,   5. );
  // lepton pt
  hists_["leptonPt"      ] = new TH1F( "leptonPt"       , "leptonPt"        ,  100,  -5.,   5. );
  // lepton eta
  hists_["leptonEta"     ] = new TH1F( "leptonEta"      , "leptonEta"       ,  100,  -5.,   5. );
  // lepton phi
  hists_["leptonPhi"     ] = new TH1F( "leptonPhi"      , "leptonPhi"       ,  100,  -5.,   5. );
  // neutrino pt
  hists_["neutrinoPt"    ] = new TH1F( "neutrinoPt"     , "neutrinoPt"      ,  100,  -5.,   5. );
  // neutrino eta
  hists_["neutrinoEta"   ] = new TH1F( "neutrinoEta"    , "neutrinoEta"     ,  100,  -5.,   5. );
  // neutrino phi
  hists_["neutrinoPhi"   ] = new TH1F( "neutrinoPhi"    , "neutrinoPhi"     ,  100,  -5.,   5. );

  /** 
      Correlation Plots
  **/
  // correlation between jet hypothesis and jet index 
  corrs_["jetHypo_"      ] = new TH2F( "jetHypo_" ,  "jetHypo_"  ,   4,  0.,  4.,  4,  0.,  4.);
}

/// histogramm booking for fw
void HypothesisKinFit::book(edm::Service<TFileService>& fs)
{
  /** 
      Monitoring Variables
  **/
  // fit probability of the best fit hypothesis
  hists_["prob"       ] = fs->make<TH1F>( "prob"       , "prob"      ,   100,    0.,    1. );
  // chi2 of the best fit hypothesis
  hists_["chi2"       ] = fs->make<TH1F>( "chi2"       , "chi2"      ,   100,    0.,   10. );
  // delta chi2 between best and second best fit hyothesis
  hists_["delChi2"    ] = fs->make<TH1F>( "delChi2"    , "delChi2"   ,   100,    0.,   10. );
  // difference of hadBQuark index between genMatch and kinFit 
  hists_["hadBQuark"  ] = fs->make<TH1F>( "hadBQuark"  , "hadBQuark" ,     9,   -4.,    4. );
  // difference of lepBQuark index between genMatch and kinFit 
  hists_["lepBQuark"  ] = fs->make<TH1F>( "lepBQuark"  , "lepBQuark" ,     9,   -4.,    4. );
  // smallest difference of the two lightQuark indices between genMatch and kinFit 
  // (taking into accont that the two indices can be switched)
  hists_["lightQuark" ] = fs->make<TH1F>( "lightQuark" , "lightQuark",     9,   -4.,    4. );

  /** 
      Pull Distributions (Relative to the MC Truth)
  **/
  // hadronic top b pt
  hists_["hadBQuarkPt_"  ] = fs->make<TH1F>( "hadBQuarkPt_"   , "hadBQuarkPt_"    ,  100,  -5.,   5. );
  // hadronic top b eta
  hists_["hadBQuarkEta_" ] = fs->make<TH1F>( "hadBQuarkEta_"  , "hadBQuarkEta_"   ,  100,  -5.,   5. );
  // hadronic top b phi
  hists_["hadBQuarkPhi_" ] = fs->make<TH1F>( "hadBQuarkPhi_"  , "hadBQuarkPhi_"   ,  100,  -5.,   5. );
  // leptonic top b pt
  hists_["lepBQuarkPt_"  ] = fs->make<TH1F>( "lepBQuarkPt_"   , "lepBQuarkPt_"    ,  100,  -5.,   5. );
  // leptonic top b eta
  hists_["lepBQuarkEta_" ] = fs->make<TH1F>( "lepBQuarkEta_"  , "lepBQuarkEta_"   ,  100,  -5.,   5. );
  // leptonic top b phi
  hists_["lepBQuarkPhi_" ] = fs->make<TH1F>( "lepBQuarkPhi_"  , "lepBQuarkPhi_"   ,  100,  -5.,   5. );
  // lightQuark pt
  hists_["lightQuarkPt_" ] = fs->make<TH1F>( "lightQuarkPt_"  , "lightQuarkPt_"   ,  100,  -5.,   5. );
  // lightQuark b eta
  hists_["lightQuarkEta_"] = fs->make<TH1F>( "lightQuarkEta_" , "lightQuarkEta_"  ,  100,  -5.,   5. );
  // lightQuark b phi
  hists_["lightQuarkPhi_"] = fs->make<TH1F>( "lightQuarkPhi_" , "lightQuarkPhi_"  ,  100,  -5.,   5. );
  // lepton pt
  hists_["leptonPt_"     ] = fs->make<TH1F>( "leptonPt_"      , "leptonPt_"       ,  100,  -5.,   5. );
  // lepton eta
  hists_["leptonEta_"    ] = fs->make<TH1F>( "leptonEta_"     , "leptonEta_"      ,  100,  -5.,   5. );
  // lepton phi
  hists_["leptonPhi_"    ] = fs->make<TH1F>( "leptonPhi_"     , "leptonPhi_"      ,  100,  -5.,   5. );
  // neutrino pt
  hists_["neutrinoPt_"   ] = fs->make<TH1F>( "neutrinoPt_"    , "neutrinoPt_"     ,  100,  -5.,   5. );
  // neutrino eta
  hists_["neutrinoEta_"  ] = fs->make<TH1F>( "neutrinoEta_"   , "neutrinoEta_"    ,  100,  -5.,   5. );
  // neutrino phi
  hists_["neutrinoPhi_"  ] = fs->make<TH1F>( "neutrinoPhi_"   , "neutrinoPhi_"    ,  100,  -5.,   5. );

  /** 
      Pull Distributions (Relative to the Reco Input -- this one still needs changes in the 
      TtSemiLeptonicEvent to allow access to the original reco objects
  **/
  // hadronic top b pt
  hists_["hadBQuarkPt"   ] = fs->make<TH1F>( "hadBQuarkPt"    , "hadBQuarkPt"     ,  100,  -5.,   5. );
  // hadronic top b eta
  hists_["hadBQuarkEta"  ] = fs->make<TH1F>( "hadBQuarkEta"   , "hadBQuarkEta"    ,  100,  -5.,   5. );
  // hadronic top b phi
  hists_["hadBQuarkPhi"  ] = fs->make<TH1F>( "hadBQuarkPhi"   , "hadBQuarkPhi"    ,  100,  -5.,   5. );
  // leptonic top b pt
  hists_["lepBQuarkPt"   ] = fs->make<TH1F>( "lepBQuarkPt"    , "lepBQuarkPt"     ,  100,  -5.,   5. );
  // leptonic top b eta
  hists_["lepBQuarkEta"  ] = fs->make<TH1F>( "lepBQuarkEta"   , "lepBQuarkEta"    ,  100,  -5.,   5. );
  // leptonic top b phi
  hists_["lepBQuarkPhi"  ] = fs->make<TH1F>( "lepBQuarkPhi"   , "lepBQuarkPhi"    ,  100,  -5.,   5. );
  // lightQuark pt
  hists_["lightQuarkPt"  ] = fs->make<TH1F>( "lightQuarkPt"   , "lightQuarkPt"    ,  100,  -5.,   5. );
  // lightQuark b eta
  hists_["lightQuarkEta" ] = fs->make<TH1F>( "lightQuarkEta"  , "lightQuarkEta"   ,  100,  -5.,   5. );
  // lightQuark b phi
  hists_["lightQuarkPhi" ] = fs->make<TH1F>( "lightQuarkPhi"  , "lightQuarkPhi"   ,  100,  -5.,   5. );
  // lepton pt
  hists_["leptonPt"      ] = fs->make<TH1F>( "leptonPt"       , "leptonPt"        ,  100,  -5.,   5. );
  // lepton eta
  hists_["leptonEta"     ] = fs->make<TH1F>( "leptonEta"      , "leptonEta"       ,  100,  -5.,   5. );
  // lepton phi
  hists_["leptonPhi"     ] = fs->make<TH1F>( "leptonPhi"      , "leptonPhi"       ,  100,  -5.,   5. );
  // neutrino pt
  hists_["neutrinoPt"    ] = fs->make<TH1F>( "neutrinoPt"     , "neutrinoPt"      ,  100,  -5.,   5. );
  // neutrino eta
  hists_["neutrinoEta"   ] = fs->make<TH1F>( "neutrinoEta"    , "neutrinoEta"     ,  100,  -5.,   5. );
  // neutrino phi
  hists_["neutrinoPhi"   ] = fs->make<TH1F>( "neutrinoPhi"    , "neutrinoPhi"     ,  100,  -5.,   5. );

  /** 
      Correlation Plots
  **/
  // correlation between jet hypothesis and jet index 
  corrs_["jetHypo_"      ] = fs->make<TH2F>( "jetHypo_" ,  "jetHypo_"  ,   4,  0.,  4.,  4,  0.,  4.);
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
HypothesisKinFit::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level
  if( tops.isHypoValid("kKinFit") ){
    /** 
	Fill the Monitoring Variables
    **/
    // fit probability of the best fit hypothesis
    hists_.find("prob")->second->Fill( tops.fitProb(), weight);
    // chi2 of the best fit hypothesis
    hists_.find("chi2")->second->Fill( tops.fitChi2(), weight);

    // make sure that a second best fit hypothesis exists to be able to fill these plots
    if( tops.fitChi2(1) >= 0 ){
      // delta chi2 between best and second best fit hyothesis
      hists_.find("delChi2")->second->Fill( tops.fitChi2(0)-tops.fitChi2(1), weight);
    }
    // make sure that the genMatch hypothesis exists to be able to fill these plots

    if( tops.isHypoValid("kGenMatch") ){
      // difference of hadBQuark index between genMatch and kinFit
      hists_.find("hadBQuark" )->second->Fill( delObjectIndex(tops, TtSemiLepEvtPartons::HadB), weight);
      // difference of lepBQuark index between genMatch and kinFit 
      hists_.find("hadBQuark" )->second->Fill( delObjectIndex(tops, TtSemiLepEvtPartons::LepB), weight);
      // smallest difference of the two lightQuark indices between genMatch and kinFit 
      // (taking into accont that the two indices can be switched)
      abs(delObjectIndex(tops, TtSemiLepEvtPartons::LightQ)) < abs(delObjectIndex(tops, TtSemiLepEvtPartons::LightQBar)) ? hists_.find("lightQuark")->second->Fill( delObjectIndex(tops, TtSemiLepEvtPartons::LightQ   ), weight ) : hists_.find("lightQuark")->second->Fill( delObjectIndex(tops, TtSemiLepEvtPartons::LightQBar), weight);
    }

    /** 
	Fill the Pull Distributions (Relative to the MC Truth)
    **/
    if( tops.genEvent().isAvailable() && tops.genEvent()->isSemiLeptonic(WDecay::kMuon) ){
      // hadronic top b pt
      hists_.find("hadBQuarkPt_"   )->second->Fill( (tops.hadronicDecayB()->pt()-tops.hadronicDecayB("kKinFit")->pt())/tops.hadronicDecayB()->pt() );
      // hadronic top b eta
      hists_.find("hadBQuarkEta_"  )->second->Fill( tops.hadronicDecayB()->eta()-tops.hadronicDecayB("kKinFit")->eta() );
      // hadronic top b phi
      hists_.find("hadBQuarkPhi_"  )->second->Fill( tops.hadronicDecayB()->phi()-tops.hadronicDecayB("kKinFit")->phi() );
      // leptonic top b pt
      hists_.find("lepBQuarkPt_"   )->second->Fill( (tops.leptonicDecayB()->pt()-tops.leptonicDecayB("kKinFit")->pt())/tops.leptonicDecayB()->pt() );
      // leptonic top b eta
      hists_.find("lepBQuarkEta_"  )->second->Fill( tops.leptonicDecayB()->eta()-tops.leptonicDecayB("kKinFit")->eta() );
      // leptonic top b phi
      hists_.find("lepBQuarkPhi_"  )->second->Fill( tops.leptonicDecayB()->phi()-tops.leptonicDecayB("kKinFit")->phi() );
      // lightQuark pt
      hists_.find("lightQuarkPt_"  )->second->Fill( (tops.hadronicDecayQuark()->pt()-tops.hadronicDecayQuark("kKinFit")->pt())/tops.hadronicDecayQuark()->pt() );
      // lightQuark b eta
      hists_.find("lightQuarkEta_" )->second->Fill( tops.hadronicDecayQuark()->eta()-tops.hadronicDecayQuark("kKinFit")->eta() );
      // lightQuark b phi
      hists_.find("lightQuarkPhi_" )->second->Fill( tops.hadronicDecayQuark()->phi()-tops.hadronicDecayQuark("kKinFit")->phi() );
      // lightQuark pt
      hists_.find("lightQuarkPt_"  )->second->Fill( (tops.hadronicDecayQuarkBar()->pt()-tops.hadronicDecayQuarkBar("kKinFit")->pt())/tops.hadronicDecayQuarkBar()->pt() );
      // lightQuark b eta
      hists_.find("lightQuarkEta_" )->second->Fill( tops.hadronicDecayQuarkBar()->eta()-tops.hadronicDecayQuarkBar("kKinFit")->eta() );
      // lightQuark b phi
      hists_.find("lightQuarkPhi_" )->second->Fill( tops.hadronicDecayQuarkBar()->phi()-tops.hadronicDecayQuarkBar("kKinFit")->phi() );
      // lepton pt
      hists_.find("leptonPt_"      )->second->Fill( (tops.singleLepton()->pt()-tops.singleLepton("kKinFit")->pt())/tops.singleLepton()->pt() );
      // lepton eta
      hists_.find("leptonEta_"     )->second->Fill( tops.singleLepton()->eta()-tops.singleLepton("kKinFit")->eta() );
      // lepton phi
      hists_.find("leptonPhi_"     )->second->Fill( tops.singleLepton()->phi()-tops.singleLepton("kKinFit")->phi() );
      // neutrino pt
      hists_.find("neutrinoPt_"    )->second->Fill( (tops.singleNeutrino()->pt()-tops.singleNeutrino("kKinFit")->pt())/tops.singleNeutrino()->pt() );
      // neutrino eta
      hists_.find("neutrinoEta_"   )->second->Fill( tops.singleNeutrino()->eta()-tops.singleNeutrino("kKinFit")->eta() );
      // neutrino phi
      hists_.find("neutrinoPhi_"   )->second->Fill( tops.singleNeutrino()->phi()-tops.singleNeutrino("kKinFit")->phi() );
    }

    /** 
	Correlation Plots
    **/
    // correlation between jet hypothesis and jet index
    corrs_.find("jetHypo_" )->second->SetBinContent(TtSemiLepEvtPartons::LightQ   +1, objectIndex(tops, "kKinFit", TtSemiLepEvtPartons::LightQ   )+1 );
    corrs_.find("jetHypo_" )->second->SetBinContent(TtSemiLepEvtPartons::LightQBar+1, objectIndex(tops, "kKinFit", TtSemiLepEvtPartons::LightQBar)+1 );
    corrs_.find("jetHypo_" )->second->SetBinContent(TtSemiLepEvtPartons::HadB     +1, objectIndex(tops, "kKinFit", TtSemiLepEvtPartons::HadB     )+1 );
    corrs_.find("jetHypo_" )->second->SetBinContent(TtSemiLepEvtPartons::LepB     +1, objectIndex(tops, "kKinFit", TtSemiLepEvtPartons::LepB     )+1 );
  }
}
