#include "TopAnalysis/TopAnalyzer/interface/HypothesisKinFitMuon.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"

/// default constructor for fw lite
HypothesisKinFitMuon::HypothesisKinFitMuon()
{
}

/// default constructor for full fw
HypothesisKinFitMuon::HypothesisKinFitMuon(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void HypothesisKinFitMuon::book()
{
  /** 
      Pull Distributions (Relative to the Reco Input)
  **/
  // lepton pt
  hists_["leptonPt"      ] = new TH1F( "leptonPt"       , "leptonPt"        ,  100,  -5.,   5. );
  // lepton eta
  hists_["leptonEta"     ] = new TH1F( "leptonEta"      , "leptonEta"       ,  100,  -5.,   5. );
  // lepton phi
  hists_["leptonPhi"     ] = new TH1F( "leptonPhi"      , "leptonPhi"       ,  100,  -5.,   5. );
}

/// histogramm booking for fw
void HypothesisKinFitMuon::book(edm::Service<TFileService>& fs)
{
  /** 
      Pull Distributions (Relative to the Reco Input)
  **/
  // lepton pt
  hists_["leptonPt"      ] = fs->make<TH1F>( "leptonPt" , "leptonPt"        ,  100,  -5.,   5. );
  // lepton eta
  hists_["leptonEta"     ] = fs->make<TH1F>( "leptonEta", "leptonEta"       ,  100,  -5.,   5. );
  // lepton phi
  hists_["leptonPhi"     ] = fs->make<TH1F>( "leptonPhi", "leptonPhi"       ,  100,  -5.,   5. );
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
HypothesisKinFitMuon::fill(const TtSemiLeptonicEvent& tops, const std::vector<pat::Muon>& muons, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level
  if( tops.isHypoValid("kKinFit") ){
    /** 
	Fill the Pull Distributions (Relative to the Reco Input)
    **/
    // define index in pat::Muon collection
    int lepton = tops.jetLeptonCombination("kKinFit")[TtSemiLepEvtPartons::Lepton];
 
    // make sure the hadronic b-jet index is in the range of the jet collection
    if( lepton < (int)muons.size() ){
      // lepton pt
      hists_.find("leptonPt"   )->second->Fill( (muons[lepton].pt()-tops.singleLepton("kKinFit")->pt())/muons[lepton].pt() );
      // lepton eta
      hists_.find("leptonEta"  )->second->Fill( muons[lepton].eta()-tops.singleLepton("kKinFit")->eta() );
      // lepton phi
      hists_.find("leptonPhi"  )->second->Fill( muons[lepton].phi()-tops.singleLepton("kKinFit")->phi() );
    }
  }
}
