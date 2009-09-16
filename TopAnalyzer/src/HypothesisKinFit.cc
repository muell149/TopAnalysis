#include "TopAnalysis/TopAnalyzer/interface/HypothesisKinFit.h"

/// default constructor for fw lite
HypothesisKinFit::HypothesisKinFit()
{
}

/// default constructor for full fw
HypothesisKinFit::HypothesisKinFit(const edm::ParameterSet& cfg) :
  jets_ ( cfg.getParameter<edm::InputTag>( "jets"  ) ),
  mets_ ( cfg.getParameter<edm::InputTag>( "mets"  ) ),
  muons_( cfg.getParameter<edm::InputTag>( "muons" ) ),
  maxGenMatchSumDR_( cfg.getParameter<double>( "maxGenMatchSumDR" ) ),
  maxGenMatchSumPt_( cfg.getParameter<double>( "maxGenMatchSumPt" ) )
{
}

/// histogramm booking for fwlite 
void HypothesisKinFit::book()
{
  /** 
      Monitoring Variables
  **/
  // chi2 of the best fit hypothesis
  hists_["chi2"       ] = new TH1F( "chi2"       , "chi2"      ,   100,    0.,   10. );
  // delta chi2 between best and second best fit hyothesis
  hists_["delChi2"    ] = new TH1F( "delChi2"    , "delChi2"   ,   100,    0.,   10. );
  // fit probability of the best fit hypothesis
  hists_["prob"       ] = new TH1F( "prob"       , "prob"      ,   100,    0.,    1. );
  // difference of hadBQuark index between genMatch and kinFit 
  hists_["hadBQuak"   ] = new TH1F( "hadBQuark"  , "hadBQuark" ,     9,   -4.,    4. );
  // difference of hadBQuark index between genMatch and kinFit 
  hists_["lepBQuak"   ] = new TH1F( "lepBQuark"  , "lepBQuark" ,     9,   -4.,    4. );
  // smallest difference of the two lightQuark indices between genMatch and kinFit 
  // (taking into accont that the two indices can be switched)
  hists_["lightQuak"  ] = new TH1F( "lightQuark" , "lightQuark",     9,   -4.,    4. );

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

  /** 
      Correlation Plots
  **/
  // correlation between jet thypothesis and jet index 
  corrs_["jetHypo_"      ] = new TH2F( "jetHypo_" ,  "jetHypo_"  ,   4,  0.,  4.,  4,  0.,  4.);
}

/// histogramm booking for fw
void HypothesisKinFit::book(edm::Service<TFileService>& fs)
{

}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
HypothesisKinFit::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level. If this is the case
  // fill matched (for stability & purity determination) or normal depending on the 
  // value of matchForStabilityAndPurity_
  if( tops.genEvent().isAvailable() && tops.genEvent()->isSemiLeptonic(WDecay::kMuon) && tops.isHypoValid("kKinFit") ){

  }
}
