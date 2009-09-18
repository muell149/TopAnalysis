#include "TopAnalysis/TopAnalyzer/interface/HypothesisKinFitJets.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"

/// default constructor for fw lite
HypothesisKinFitJets::HypothesisKinFitJets()
{
}

/// default constructor for full fw
HypothesisKinFitJets::HypothesisKinFitJets(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void HypothesisKinFitJets::book()
{
  /** 
      Pull Distributions (Relative to the Reco Input)
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
}

/// histogramm booking for fw
void HypothesisKinFitJets::book(edm::Service<TFileService>& fs)
{
  /** 
      Pull Distributions (Relative to the Reco Input)
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
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
HypothesisKinFitJets::fill(const TtSemiLeptonicEvent& tops, const std::vector<pat::Jet>& jets, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level
  if( tops.isHypoValid("kKinFit") ){
    /** 
	Fill the Pull Distributions (Relative to the MC Truth)
    **/
    // define indices in pat::Jet collection
    int lightQ    = tops.jetLeptonCombination("kKinFit")[TtSemiLepEvtPartons::LightQ   ];
    int lightQBar = tops.jetLeptonCombination("kKinFit")[TtSemiLepEvtPartons::LightQBar];
    int hadB      = tops.jetLeptonCombination("kKinFit")[TtSemiLepEvtPartons::HadB     ];
    int lepB      = tops.jetLeptonCombination("kKinFit")[TtSemiLepEvtPartons::LepB     ];
 
    // make sure the hadronic b-jet index is in the range of the jet collection
    if( hadB < (int)jets.size() ){
      // hadronic top b pt
      hists_.find("hadBQuarkPt"   )->second->Fill( (jets[hadB].pt()-tops.hadronicDecayB("kKinFit")->pt())/jets[hadB].pt() );
      // hadronic top b eta
      hists_.find("hadBQuarkEta"  )->second->Fill( jets[hadB].eta()-tops.hadronicDecayB("kKinFit")->eta() );
      // hadronic top b phi
      hists_.find("hadBQuarkPhi"  )->second->Fill( jets[hadB].phi()-tops.hadronicDecayB("kKinFit")->phi() );
    }
   // make sure the leptonic b-jet index is in the range of the jet collection
    if( lepB < (int)jets.size() ){
      // leptonic top b pt
      hists_.find("lepBQuarkPt"   )->second->Fill( (jets[lepB].pt()-tops.leptonicDecayB("kKinFit")->pt())/jets[lepB].pt() );
      // leptonic top b eta
      hists_.find("lepBQuarkEta"  )->second->Fill( jets[lepB].eta()-tops.leptonicDecayB("kKinFit")->eta() );
      // leptonic top b phi
      hists_.find("lepBQuarkPhi"  )->second->Fill( jets[lepB].phi()-tops.leptonicDecayB("kKinFit")->phi() );
    }
   // make sure the light quark index is in the range of the jet collection
    if( lightQ < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightQ].pt()-tops.hadronicDecayQuark("kKinFit")->pt())/jets[lightQ].pt() );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( jets[lightQ].eta()-tops.hadronicDecayQuark("kKinFit")->eta() );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( jets[lightQ].phi()-tops.hadronicDecayQuark("kKinFit")->phi() );
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightQBar < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightQBar].pt()-tops.hadronicDecayQuarkBar("kKinFit")->pt())/jets[lightQBar].pt() );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( jets[lightQBar].eta()-tops.hadronicDecayQuarkBar("kKinFit")->eta() );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( jets[lightQBar].phi()-tops.hadronicDecayQuarkBar("kKinFit")->phi() );
    }
  }
}
