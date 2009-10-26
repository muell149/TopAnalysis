#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "TopAnalysis/TopAnalyzer/interface/JetResolution.h"

typedef ObjectResolution<edm::View<pat::Jet> > BaseClass;

/// default constructor for fw lite
JetResolution::JetResolution(double matchDR, std::vector<double> binsPt, std::vector<double> binsEta, std::vector<double> binsPhi):
  BaseClass::ObjectResolution(matchDR, binsPt, binsEta, binsPhi)
{ 
}

/// default constructor for full fw
JetResolution::JetResolution(const edm::ParameterSet& cfg):
  BaseClass::ObjectResolution(cfg)
{
}

/// histogramm booking for fwlite 
void 
JetResolution::book()
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
JetResolution::book(edm::Service<TFileService>& fs)
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
JetResolution::fill(const edm::View<pat::Jet>& jets, const double& weight)
{
  for(edm::View<pat::Jet>::const_iterator jet=jets.begin(); jet!=jets.end(); ++jet){
    if( jet->genParton() ){ 
      if(deltaR( jet->eta(), jet->phi(), jet->genParton()->eta(), jet->genParton()->phi() )<matchDR_){
	// fill resolution histograms binned in pt
	for(unsigned int idx=0; idx<(binsPt_.size()-1); ++idx) {
	  if( (binsPt_[idx]<jet->genParton()->pt()) && (jet->genParton()->pt()<binsPt_[idx+1]) ){
	    pt_[idx]->Fill((jet->pt()-jet->genParton()->pt())/(jet->genParton())->pt(), weight);
	  }
	}
	// fill resolution histograms binned in eta
	for(unsigned int idx=0; idx<(binsEta_.size()-1); ++idx) {
	  if( (binsEta_[idx]<jet->genParton()->eta()) && (jet->genParton()->eta()<binsEta_[idx+1]) ){
	    eta_[idx]->Fill(jet->eta()-jet->genParton()->eta(), weight);
	  }
	}
	// fill resolution histograms binned in phi
	for(unsigned int idx=0; idx<(binsPhi_.size()-1); ++idx) {
	  if( (binsPhi_[idx]<jet->genParton()->phi()) && (jet->genParton()->phi()<binsPhi_[idx+1]) ){
	    phi_[idx]->Fill(deltaPhi(jet->phi(), jet->genParton()->phi()), weight);
	  }
	}
      }
    }
  }
}
