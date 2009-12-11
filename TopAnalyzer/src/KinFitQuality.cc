#include "TopAnalysis/TopAnalyzer/interface/KinFitQuality.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"

/// default constructor for fw lite
KinFitQuality::KinFitQuality()
{
}

/// default constructor for full fw
KinFitQuality::KinFitQuality(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void KinFitQuality::book()
{
  /** 
      Pull Distributions (Relative to the Reco Input)
  **/

  // b pt
  hists_["bQuarkPt"     ] = new TH1F( "bQuarkPt"      , "bQuarkPt"      ,  100,  -5.,   5.    );
  // b eta
  hists_["bQuarkEta"    ] = new TH1F( "bQuarkEta"     , "bQuarkEta"     ,  100,  -5.,   5.    );
  // b phi
  hists_["bQuarkPhi"    ] = new TH1F( "bQuarkPhi"     , "bQuarkPhi"     ,  100,  -5.,   5.    );
  // lightQuark pt
  hists_["lightQuarkPt" ] = new TH1F( "lightQuarkPt"  , "lightQuarkPt"  ,  100,  -5.,   5.    );
  // lightQuark b eta
  hists_["lightQuarkEta"] = new TH1F( "lightQuarkEta" , "lightQuarkEta" ,  100,  -5.,   5.    );
  // lightQuark b phi
  hists_["lightQuarkPhi"] = new TH1F( "lightQuarkPhi" , "lightQuarkPhi" ,  100,  -5.,   5.    );

  /**
     KinFit Properties
  **/

  // chi2 of kinfit
  hists_["chi2"] = new TH1F( "chi2" , "chi2" ,  1000,  0.,   1000. );
  // chi2prob of kinfit
  hists_["prob"] = new TH1F( "prob" , "prob" ,  1001, -0.001 ,  1. );
}

/// histogramm booking for fw
void KinFitQuality::book(edm::Service<TFileService>& fs)
{
  /** 
      Pull Distributions (Relative to the Reco Input)
  **/

  // b pt
  hists_["bQuarkPt"     ] = fs->make<TH1F>( "bQuarkPt"      , "bQuarkPt"      ,  100,  -5.,   5.    );
  // b eta
  hists_["bQuarkEta"    ] = fs->make<TH1F>( "bQuarkEta"     , "bQuarkEta"     ,  100,  -5.,   5.    );
  // b phi
  hists_["bQuarkPhi"    ] = fs->make<TH1F>( "bQuarkPhi"     , "bQuarkPhi"     ,  100,  -5.,   5.    );
  // lightQuark pt
  hists_["lightQuarkPt" ] = fs->make<TH1F>( "lightQuarkPt"  , "lightQuarkPt"  ,  100,  -5.,   5.    );
  // lightQuark b eta
  hists_["lightQuarkEta"] = fs->make<TH1F>( "lightQuarkEta" , "lightQuarkEta" ,  100,  -5.,   5.    );
  // lightQuark b phi
  hists_["lightQuarkPhi"] = fs->make<TH1F>( "lightQuarkPhi" , "lightQuarkPhi" ,  100,  -5.,   5.    );

  /**
     KinFit Properties
  **/

  // chi2 of kinfit
  hists_["chi2"] = fs->make<TH1F>( "chi2" , "chi2" ,  1000,  0.,   1000. );
  // chi2prob of kinfit
  hists_["prob"] = fs->make<TH1F>( "prob" , "prob" ,  1001, -0.001 ,  1. );
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
KinFitQuality::fill(const TtFullHadronicEvent& tops, const edm::View<pat::Jet>& jets, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level
  if( tops.isHypoValid("kKinFit") ){
    /** 
	Fill the Pull Distributions (Relative to the Reco Input)
    **/
    // define indices in pat::Jet collection

    int lightQ    = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQ   ];
    int lightQBar = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQBar];
    int b         = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::B        ];
    int bBar      = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::BBar     ];
    int lightP    = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightP   ];
    int lightPBar = tops.jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightPBar];


    // make sure the b-jet index is in the range of the jet collection
    if( b >=0 && b < (int)jets.size() ){
      // b pt
      hists_.find("bQuarkPt"   )->second->Fill( (jets[b].pt()-tops.b("kKinFit")->pt())/jets[b].pt() );
      // b eta
      hists_.find("bQuarkEta"  )->second->Fill( jets[b].eta()-tops.b("kKinFit")->eta() );
      // b phi
      hists_.find("bQuarkPhi"  )->second->Fill( jets[b].phi()-tops.b("kKinFit")->phi() );
    }
   // make sure the bBar-jet index is in the range of the jet collection
    if( bBar >= 0 && bBar< (int)jets.size() ){
      // bBar pt
      hists_.find("bQuarkPt"   )->second->Fill( (jets[bBar].pt()-tops.bBar("kKinFit")->pt())/jets[bBar].pt() );
      // bBar eta
      hists_.find("bQuarkEta"  )->second->Fill( jets[bBar].eta()-tops.bBar("kKinFit")->eta() );
      // bBar phi
      hists_.find("bQuarkPhi"  )->second->Fill( jets[bBar].phi()-tops.bBar("kKinFit")->phi() );
    }
   // make sure the light quark index is in the range of the jet collection
    if( lightQ >= 0 && lightQ < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightQ].pt()-tops.lightQ("kKinFit")->pt())/jets[lightQ].pt() );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( jets[lightQ].eta()-tops.lightQ("kKinFit")->eta() );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( jets[lightQ].phi()-tops.lightQ("kKinFit")->phi() );
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightQBar >= 0 && lightQBar< (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightQBar].pt()-tops.lightQBar("kKinFit")->pt())/jets[lightQBar].pt() );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( jets[lightQBar].eta()-tops.lightQBar("kKinFit")->eta() );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( jets[lightQBar].phi()-tops.lightQBar("kKinFit")->phi() );
    }
   // make sure the light quark index is in the range of the jet collection
    if( lightP >= 0 && lightP < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightP].pt()-tops.lightP("kKinFit")->pt())/jets[lightP].pt() );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( jets[lightP].eta()-tops.lightP("kKinFit")->eta() );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( jets[lightP].phi()-tops.lightP("kKinFit")->phi() );
    }
    // make sure the light quark bar index is in the range of the jet collection
    if( lightPBar >= 0 && lightPBar < (int)jets.size() ){
      // lightQuark pt
      hists_.find("lightQuarkPt"  )->second->Fill( (jets[lightPBar].pt()-tops.lightPBar("kKinFit")->pt())/jets[lightPBar].pt() );
      // lightQuark eta
      hists_.find("lightQuarkEta" )->second->Fill( jets[lightPBar].eta()-tops.lightPBar("kKinFit")->eta() );
      // lightQuark phi
      hists_.find("lightQuarkPhi" )->second->Fill( jets[lightPBar].phi()-tops.lightPBar("kKinFit")->phi() );
    }

    // chi2 of kinfit
    hists_.find("chi2")->second->Fill( tops.fitChi2() );
    // chi2prob of kinfit
    hists_.find("prob")->second->Fill( tops.fitProb() );

  }
}
