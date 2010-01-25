#include "TopAnalysis/TopAnalyzer/interface/HypothesisKinFit.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "DataFormats/Math/interface/deltaPhi.h"
/// default constructor for fw lite
HypothesisKinFit::HypothesisKinFit()
{
}

/// default constructor for full fw
HypothesisKinFit::HypothesisKinFit(const edm::ParameterSet& cfg) :
  hypoKey_( cfg.getParameter<std::string>("hypoKey") )
{
}

/// histogramm booking for fwlite 
void HypothesisKinFit::book()
{
  /** 
      Monitoring Variables
  **/
  // fit probability of the best fit hypothesis
  hists_["prob"       ] = new TH1F( "prob"       , "prob"       ,   100,    0.,    1. );
  // chi2 of the best fit hypothesis
  hists_["chi2"       ] = new TH1F( "chi2"       , "chi2"       ,   100,    0.,   10. );
  // delta chi2 between best and second best fit hyothesis
  hists_["delChi2"    ] = new TH1F( "delChi2"    , "delChi2"    ,   100,    0.,   10. );
  // difference of hadBQuark index between genMatch and kinFit 
  hists_["hadBQuark"  ] = new TH1F( "hadBQuark"  , "hadBQuark"  ,     9,  -4.5,   4.5 );
  // difference of lepBQuark index between genMatch and kinFit 
  hists_["lepBQuark"  ] = new TH1F( "lepBQuark"  , "lepBQuark"  ,     9,  -4.5,   4.5 );
  // smallest difference of the two lightQuark indices between genMatch and kinFit 
  // (taking into accont that the two indices can be switched)
  hists_["lightQuark" ] = new TH1F( "lightQuark" , "lightQuark" ,     9,  -4.5,   4.5 );
  // number of quarks differing in the index between genMatch and the other hypothesis
  hists_["wrongAssign"] = new TH1F( "wrongAssign", "wrongAssign",     5,  -0.5,   4.5 );

  /** 
      Pull Distributions (Relative to the MC Truth)
  **/
  // hadronic top b pt
  hists_["hadBQuarkPt"  ] = new TH1F( "hadBQuarkPt"   , "hadBQuarkPt"    ,  100,  -5.,   5. );
  // hadronic top b eta
  hists_["hadBQuarkEta" ] = new TH1F( "hadBQuarkEta"  , "hadBQuarkEta"   ,  100,  -5.,   5. );
  // hadronic top b phi
  hists_["hadBQuarkPhi" ] = new TH1F( "hadBQuarkPhi"  , "hadBQuarkPhi"   ,  100,  -5.,   5. );
  // leptonic top b pt
  hists_["lepBQuarkPt"  ] = new TH1F( "lepBQuarkPt"   , "lepBQuarkPt"    ,  100,  -5.,   5. );
  // leptonic top b eta
  hists_["lepBQuarkEta" ] = new TH1F( "lepBQuarkEta"  , "lepBQuarkEta"   ,  100,  -5.,   5. );
  // leptonic top b phi
  hists_["lepBQuarkPhi" ] = new TH1F( "lepBQuarkPhi"  , "lepBQuarkPhi"   ,  100,  -5.,   5. );
  // lightQuark pt
  hists_["lightQuarkPt" ] = new TH1F( "lightQuarkPt"  , "lightQuarkPt"   ,  100,  -5.,   5. );
  // lightQuark b eta
  hists_["lightQuarkEta"] = new TH1F( "lightQuarkEta" , "lightQuarkEta"  ,  100,  -5.,   5. );
  // lightQuark b phi
  hists_["lightQuarkPhi"] = new TH1F( "lightQuarkPhi" , "lightQuarkPhi"  ,  100,  -5.,   5. );
  // lepton pt
  hists_["leptonPt"     ] = new TH1F( "leptonPt"      , "leptonPt"       ,  100,  -.5,   .5 );
  // lepton eta
  hists_["leptonEta"    ] = new TH1F( "leptonEta"     , "leptonEta"      ,  100,  -.5,   .5 );
  // lepton phi
  hists_["leptonPhi"    ] = new TH1F( "leptonPhi"     , "leptonPhi"      ,  100,  -.5,   .5 );
  // neutrino pt
  hists_["neutrinoPt"   ] = new TH1F( "neutrinoPt"    , "neutrinoPt"     ,  100,  -5.,   5. );
  // neutrino eta
  hists_["neutrinoEta"  ] = new TH1F( "neutrinoEta"   , "neutrinoEta"    ,  100,  -5.,   5. );
  // neutrino phi
  hists_["neutrinoPhi"  ] = new TH1F( "neutrinoPhi"   , "neutrinoPhi"    ,  100,  -5.,   5. );

  /** 
      Correlation Plots
  **/
  // correlation between jet hypothesis and jet index 
  corrs_["mapGenMatch_"    ] = new TH2F( "mapGenMatch_",  "mapGenMatch_",   4,  0.,  4.,  4,  0.,  4.);
  // correlation between jet hypothesis and jet index 
  corrs_["mapKinFit_"      ] = new TH2F( "mapKinFit_"  ,  "mapKinFit_"  ,   4,  0.,  4.,  4,  0.,  4.);
}

/// histogramm booking for fw
void HypothesisKinFit::book(edm::Service<TFileService>& fs)
{
  /** 
      Monitoring Variables
  **/
  // fit probability of the best fit hypothesis
  hists_["prob"       ] = fs->make<TH1F>( "prob"       , "prob"       ,   100,    0.,    1. );
  // chi2 of the best fit hypothesis
  hists_["chi2"       ] = fs->make<TH1F>( "chi2"       , "chi2"       ,   100,    0.,   10. );
  // delta chi2 between best and second best fit hyothesis
  hists_["delChi2"    ] = fs->make<TH1F>( "delChi2"    , "delChi2"    ,   100,    0.,   10. );
  // difference of hadBQuark index between genMatch and kinFit 
  hists_["hadBQuark"  ] = fs->make<TH1F>( "hadBQuark"  , "hadBQuark"  ,     9,  -4.5,   4.5 );
  // difference of lepBQuark index between genMatch and kinFit 
  hists_["lepBQuark"  ] = fs->make<TH1F>( "lepBQuark"  , "lepBQuark"  ,     9,  -4.5,   4.5 );
  // smallest difference of the two lightQuark indices between genMatch and kinFit 
  // (taking into accont that the two indices can be switched)
  hists_["lightQuark" ] = fs->make<TH1F>( "lightQuark" , "lightQuark" ,     9,  -4.5,   4.5 );
  // number of quarks differing in the index between genMatch and the other hypothesis
  hists_["wrongAssign"] = fs->make<TH1F>( "wrongAssign", "wrongAssign",     5,  -0.5,   4.5 );

  /** 
      Pull Distributions (Relative to the MC Truth)
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
  hists_["leptonPt"      ] = fs->make<TH1F>( "leptonPt"       , "leptonPt"        ,  100,  -.5,   .5 );
  // lepton eta
  hists_["leptonEta"     ] = fs->make<TH1F>( "leptonEta"      , "leptonEta"       ,  100,  -.5,   .5 );
  // lepton phi
  hists_["leptonPhi"     ] = fs->make<TH1F>( "leptonPhi"      , "leptonPhi"       ,  100,  -.5,   .5 );
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
  corrs_["mapGenMatch_"    ] = fs->make<TH2F>( "mapGenMatch_",  "mapGenMatch_",   4,  0.,  4.,  4,  0.,  4.);
  // correlation between jet hypothesis and jet index 
  corrs_["mapKinFit_"      ] = fs->make<TH2F>( "mapKinFit_"  ,  "mapKinFit_"  ,   4,  0.,  4.,  4,  0.,  4.);
}

/// calculating difference of object indices in the reco collections between the genMatch and kinFit hypotheses
int
HypothesisKinFit::delObjectIndex(const TtSemiLeptonicEvent& tops, const int& index)
{
  if(index==TtSemiLepEvtPartons::LightQ)
     return std::min(abs(objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQ)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQ)),abs(objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQBar)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQBar))) < std::min(abs(objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQ)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQBar)),abs(objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQBar)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQ))) ? objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQ)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQ) : objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQ)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQBar);
  else if(index==TtSemiLepEvtPartons::LightQBar)
    return std::min(abs(objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQ)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQ)),abs(objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQBar)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQBar))) < std::min(abs(objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQ)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQBar)),abs(objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQBar)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQ))) ? objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQBar)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQBar) : objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQBar)-objectIndex(tops, hypoKey_, TtSemiLepEvtPartons::LightQ);
  else
    return objectIndex(tops, "kGenMatch", index)-objectIndex(tops, hypoKey_, index);
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
HypothesisKinFit::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level
  if( tops.isHypoValid(hypoKey_) ){
    /** 
	Fill the Monitoring Variables
    **/
    if( hypoKey_ == "kKinFit" ){
      // fit probability of the best fit hypothesis
      hists_.find("prob")->second->Fill( tops.fitProb(), weight);
      // chi2 of the best fit hypothesis
      hists_.find("chi2")->second->Fill( tops.fitChi2(), weight);

      // make sure that a second best fit hypothesis exists to be able to fill these plots
      if( tops.fitChi2(1) >= 0 ){
	// delta chi2 between best and second best fit hyothesis
	hists_.find("delChi2")->second->Fill( tops.fitChi2(1)-tops.fitChi2(0), weight);
      }
    }

    // make sure that the genMatch hypothesis exists to be able to fill these plots
    if( tops.isHypoValid("kGenMatch") ){
      // difference of hadBQuark index between genMatch and kinFit
      hists_.find("hadBQuark" )->second->Fill( delObjectIndex(tops, TtSemiLepEvtPartons::HadB), weight);
      // difference of lepBQuark index between genMatch and kinFit 
      hists_.find("lepBQuark" )->second->Fill( delObjectIndex(tops, TtSemiLepEvtPartons::LepB), weight);
      // smallest difference of the two lightQuark indices between genMatch and kinFit 
      // (taking into account that the two indices can be switched)
      hists_.find("lightQuark")->second->Fill( delObjectIndex(tops, TtSemiLepEvtPartons::LightQ   ), weight);
      hists_.find("lightQuark")->second->Fill( delObjectIndex(tops, TtSemiLepEvtPartons::LightQBar), weight);
      // number of quarks differing in the index between genMatch and the other hypothesis
      int numberOfDifferingIndices = 0;
      if(delObjectIndex(tops, TtSemiLepEvtPartons::HadB     ))numberOfDifferingIndices++;
      if(delObjectIndex(tops, TtSemiLepEvtPartons::LepB     ))numberOfDifferingIndices++;
      if(delObjectIndex(tops, TtSemiLepEvtPartons::LightQ   ))numberOfDifferingIndices++;
      if(delObjectIndex(tops, TtSemiLepEvtPartons::LightQBar))numberOfDifferingIndices++;
      hists_.find("wrongAssign")->second->Fill( numberOfDifferingIndices, weight);
    }

    /** 
	Fill the Pull Distributions (Relative to the MC Truth)
    **/
    if( tops.genEvent().isAvailable() && tops.genEvent()->isSemiLeptonic(WDecay::kMuon) ){
      if( tops.hadronicDecayB() && tops.hadronicDecayB(hypoKey_) ){
	// hadronic top b pt
	hists_.find("hadBQuarkPt"   )->second->Fill( (tops.hadronicDecayB()->pt()-tops.hadronicDecayB(hypoKey_)->pt())/tops.hadronicDecayB()->pt() );
	// hadronic top b eta
	hists_.find("hadBQuarkEta"  )->second->Fill( tops.hadronicDecayB()->eta()-tops.hadronicDecayB(hypoKey_)->eta() );
	// hadronic top b phi
	hists_.find("hadBQuarkPhi"  )->second->Fill( deltaPhi(tops.hadronicDecayB()->phi(), tops.hadronicDecayB(hypoKey_)->phi()) );
      }
      if( tops.leptonicDecayB() && tops.leptonicDecayB(hypoKey_) ){
	// leptonic top b pt
	hists_.find("lepBQuarkPt"   )->second->Fill( (tops.leptonicDecayB()->pt()-tops.leptonicDecayB(hypoKey_)->pt())/tops.leptonicDecayB()->pt() );
	// leptonic top b eta
	hists_.find("lepBQuarkEta"  )->second->Fill( tops.leptonicDecayB()->eta()-tops.leptonicDecayB(hypoKey_)->eta() );
	// leptonic top b phi
	hists_.find("lepBQuarkPhi"  )->second->Fill( deltaPhi(tops.leptonicDecayB()->phi(), tops.leptonicDecayB(hypoKey_)->phi()) );
      }
      if( tops.hadronicDecayQuark() && tops.hadronicDecayQuark(hypoKey_) ){
	// lightQuark pt
	hists_.find("lightQuarkPt"  )->second->Fill( (tops.hadronicDecayQuark()->pt()-tops.hadronicDecayQuark(hypoKey_)->pt())/tops.hadronicDecayQuark()->pt() );
	// lightQuark b eta
	hists_.find("lightQuarkEta" )->second->Fill( tops.hadronicDecayQuark()->eta()-tops.hadronicDecayQuark(hypoKey_)->eta() );
	// lightQuark b phi
	hists_.find("lightQuarkPhi" )->second->Fill( deltaPhi(tops.hadronicDecayQuark()->phi(), tops.hadronicDecayQuark(hypoKey_)->phi()) );
      }
      if( tops.hadronicDecayQuarkBar() && tops.hadronicDecayQuarkBar(hypoKey_) ){
	// lightQuark pt
	hists_.find("lightQuarkPt"  )->second->Fill( (tops.hadronicDecayQuarkBar()->pt()-tops.hadronicDecayQuarkBar(hypoKey_)->pt())/tops.hadronicDecayQuarkBar()->pt() );
	// lightQuark b eta
	hists_.find("lightQuarkEta" )->second->Fill( tops.hadronicDecayQuarkBar()->eta()-tops.hadronicDecayQuarkBar(hypoKey_)->eta() );
	// lightQuark b phi
	hists_.find("lightQuarkPhi" )->second->Fill( deltaPhi(tops.hadronicDecayQuarkBar()->phi(), tops.hadronicDecayQuarkBar(hypoKey_)->phi()) );
      }
      if( tops.singleLepton() && tops.singleLepton(hypoKey_) ){
	// lepton pt
	hists_.find("leptonPt"      )->second->Fill( (tops.singleLepton()->pt()-tops.singleLepton(hypoKey_)->pt())/tops.singleLepton()->pt() );
	// lepton eta
	hists_.find("leptonEta"     )->second->Fill( tops.singleLepton()->eta()-tops.singleLepton(hypoKey_)->eta() );
	// lepton phi
	hists_.find("leptonPhi"     )->second->Fill( deltaPhi(tops.singleLepton()->phi(), tops.singleLepton(hypoKey_)->phi()) );
      }
      if( tops.singleNeutrino() && tops.singleNeutrino(hypoKey_) ){
	// neutrino pt
	hists_.find("neutrinoPt"    )->second->Fill( (tops.singleNeutrino()->pt()-tops.singleNeutrino(hypoKey_)->pt())/tops.singleNeutrino()->pt() );
	// neutrino eta
	hists_.find("neutrinoEta"   )->second->Fill( tops.singleNeutrino()->eta()-tops.singleNeutrino(hypoKey_)->eta() );
	// neutrino phi
	hists_.find("neutrinoPhi"   )->second->Fill( deltaPhi(tops.singleNeutrino()->phi(), tops.singleNeutrino(hypoKey_)->phi()) );
      }
    }

    /** 
	Correlation Plots
    **/
    if( tops.isHypoValid("kGenMatch") ){
      // correlation between jet hypothesis and jet index
      corrs_.find("mapGenMatch_" )->second->Fill(TtSemiLepEvtPartons::LightQ   , objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQ   ) );
      corrs_.find("mapGenMatch_" )->second->Fill(TtSemiLepEvtPartons::LightQBar, objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LightQBar) );
      corrs_.find("mapGenMatch_" )->second->Fill(TtSemiLepEvtPartons::HadB     , objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::HadB     ) );
      corrs_.find("mapGenMatch_" )->second->Fill(TtSemiLepEvtPartons::LepB     , objectIndex(tops, "kGenMatch", TtSemiLepEvtPartons::LepB     ) );
    }
    // correlation between jet hypothesis and jet index
    corrs_.find("mapKinFit_"   )->second->Fill(TtSemiLepEvtPartons::LightQ   , objectIndex(tops, hypoKey_  , TtSemiLepEvtPartons::LightQ   ) );
    corrs_.find("mapKinFit_"   )->second->Fill(TtSemiLepEvtPartons::LightQBar, objectIndex(tops, hypoKey_  , TtSemiLepEvtPartons::LightQBar) );
    corrs_.find("mapKinFit_"   )->second->Fill(TtSemiLepEvtPartons::HadB     , objectIndex(tops, hypoKey_  , TtSemiLepEvtPartons::HadB     ) );
    corrs_.find("mapKinFit_"   )->second->Fill(TtSemiLepEvtPartons::LepB     , objectIndex(tops, hypoKey_  , TtSemiLepEvtPartons::LepB     ) );
  }
}
