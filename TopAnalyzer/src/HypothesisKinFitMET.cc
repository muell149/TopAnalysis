#include "TopAnalysis/TopAnalyzer/interface/HypothesisKinFitMET.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"

/// default constructor for fw lite
HypothesisKinFitMET::HypothesisKinFitMET()
{
}

/// default constructor for full fw
HypothesisKinFitMET::HypothesisKinFitMET(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void HypothesisKinFitMET::book()
{
  /** 
      Pull Distributions (Relative to the Reco Input)
  **/
  // neutrino pt
  hists_["neutrinoPt"      ] = new TH1F( "neutrinoPt"       , "neutrinoPt"        ,  100,  -5.,   5. );
  // neutrino eta
  hists_["neutrinoEta"     ] = new TH1F( "neutrinoEta"      , "neutrinoEta"       ,  100,  -5.,   5. );
  // neutrino phi
  hists_["neutrinoPhi"     ] = new TH1F( "neutrinoPhi"      , "neutrinoPhi"       ,  100,  -5.,   5. );
}

/// histogramm booking for fw
void HypothesisKinFitMET::book(edm::Service<TFileService>& fs)
{
  /** 
      Pull Distributions (Relative to the Reco Input)
  **/
  // neutrino pt
  hists_["neutrinoPt"      ] = fs->make<TH1F>( "neutrinoPt" , "neutrinoPt"        ,  100,  -5.,   5. );
  // neutrino eta
  hists_["neutrinoEta"     ] = fs->make<TH1F>( "neutrinoEta", "neutrinoEta"       ,  100,  -5.,   5. );
  // neutrino phi
  hists_["neutrinoPhi"     ] = fs->make<TH1F>( "neutrinoPhi", "neutrinoPhi"       ,  100,  -5.,   5. );
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
HypothesisKinFitMET::fill(const TtSemiLeptonicEvent& tops, const edm::View<pat::MET>& mets, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level
  if( tops.isHypoValid("kKinFit") ){
    /** 
	Fill the Pull Distributions (Relative to the Reco Input)
    **/
    // make sure the hadronic b-jet index is in the range of the jet collection
    if( 0 < (int)mets.size() ){
      // neutrino pt
      hists_.find("neutrinoPt"   )->second->Fill( (mets[0].pt()-tops.singleNeutrino("kKinFit")->pt())/mets[0].pt() );
      // neutrino eta
      hists_.find("neutrinoEta"  )->second->Fill( mets[0].eta()-tops.singleNeutrino("kKinFit")->eta() );
      // neutrino phi
      hists_.find("neutrinoPhi"  )->second->Fill( mets[0].phi()-tops.singleNeutrino("kKinFit")->phi() );
    }
  }
} 
