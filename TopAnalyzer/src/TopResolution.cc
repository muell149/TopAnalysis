#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "TopAnalysis/TopAnalyzer/interface/TopResolution.h"

typedef ObjectResolution<TtSemiLeptonicEvent> BaseClass;

/// default constructor for fw lite
TopResolution::TopResolution(double matchDR, std::vector<double> binsPt, std::vector<double> binsEta, std::vector<double> binsPhi, const char* hypoKey):
  BaseClass::ObjectResolution(matchDR, binsPt, binsEta, binsPhi), hypoKey_(hypoKey)
{ 
}

/// default constructor for full fw
TopResolution::TopResolution(const edm::ParameterSet& cfg):
  BaseClass::ObjectResolution(cfg), 
  hypoKey_( cfg.getParameter<std::string>( "hypoKey" ) )
{
}

/// histogramm booking for fwlite 
void 
TopResolution::book()
{
  /** 
      Resolution Histograms
  **/
  BaseClass::book( pt_  ,  "pt" ,  binsPt_  ,  100 ,    0.5 );
  BaseClass::book( eta_ , "eta" ,  binsEta_ ,  100 ,  0.005 );
  BaseClass::book( phi_ , "phi" ,  binsPhi_ ,  100 ,  0.005 );
}

/// histogramm booking for fwfull
void 
TopResolution::book(edm::Service<TFileService>& fs)
{
  /** 
      Resolution Histograms
  **/
  BaseClass::book( fs , pt_  ,  "pt"  , binsPt_  ,  100 ,    0.5 );
  BaseClass::book( fs , eta_ ,  "eta" , binsEta_ ,  100 ,  0.005 );
  BaseClass::book( fs , phi_ ,  "phi" , binsPhi_ ,  100 ,  0.005 );
}

/// histogram filling for fwlite and for full fw
void
TopResolution::fill(const TtSemiLeptonicEvent& tops, const double& weight)
{
  // make sure to have a valid hypothesis on reconstruction level. If 
  // this is the case fill the resolution histograms for top quarks
  if( tops.genEvent().isAvailable() && tops.genEvent()->isSemiLeptonic(WDecay::kMuon) && tops.isHypoValid(hypoKey_) ){
    if(deltaR( tops.hadronicDecayTop(hypoKey_)->eta(), tops.hadronicDecayTop(hypoKey_)->phi(), tops.hadronicDecayTop()->eta(), tops.hadronicDecayTop()->phi() )<matchDR_){
      // fill resolution histograms binned in pt
      for(unsigned int idx=0; idx<(binsPt_.size()-1); ++idx) {
	if( (binsPt_[idx]<tops.hadronicDecayTop(hypoKey_)->pt()) && (tops.hadronicDecayTop(hypoKey_)->pt()<binsPt_[idx+1]) ){
	  pt_[idx]->Fill((tops.hadronicDecayTop(hypoKey_)->pt()-tops.hadronicDecayTop(hypoKey_)->pt())/tops.hadronicDecayTop(hypoKey_)->pt(), weight);
	}
      }
      // fill resolution histograms binned in eta
      for(unsigned int idx=0; idx<(binsEta_.size()-1); ++idx) {
	if( (binsEta_[idx]<tops.hadronicDecayTop(hypoKey_)->eta()) && (tops.hadronicDecayTop(hypoKey_)->eta()<binsEta_[idx+1]) ){
	  eta_[idx]->Fill(tops.hadronicDecayTop(hypoKey_)->eta()-tops.hadronicDecayTop(hypoKey_)->eta(), weight);
	}
      }
      // fill resolution histograms binned in phi
      for(unsigned int idx=0; idx<(binsPhi_.size()-1); ++idx) {
	if( (binsPhi_[idx]<tops.hadronicDecayTop(hypoKey_)->phi()) && (tops.hadronicDecayTop(hypoKey_)->phi()<binsPhi_[idx+1]) ){
	  phi_[idx]->Fill(deltaPhi(tops.hadronicDecayTop(hypoKey_)->phi(), tops.hadronicDecayTop(hypoKey_)->phi()), weight);
	}
      }
    }
  }
}
