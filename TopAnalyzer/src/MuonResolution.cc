#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonResolution.h"

typedef ObjectResolution<std::vector<pat::Muon> > BaseClass;

/// default constructor for fw lite
MuonResolution::MuonResolution(double matchDR, std::vector<double> binsPt, std::vector<double> binsEta, std::vector<double> binsPhi):
  BaseClass::ObjectResolution(matchDR, binsPt, binsEta, binsPhi)
{ 
}

/// default constructor for full fw
MuonResolution::MuonResolution(const edm::ParameterSet& cfg):
  BaseClass::ObjectResolution(cfg)
{
}

/// histogramm booking for fwlite 
void 
MuonResolution::book()
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
MuonResolution::book(edm::Service<TFileService>& fs)
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
MuonResolution::fill(const std::vector<pat::Muon>& muons, const double& weight)
{
  for(std::vector<pat::Muon>::const_iterator muon=muons.begin(); muon!=muons.end(); ++muon){
    if( muon->genLepton() ){ 
      if(deltaR( muon->eta(), muon->phi(), muon->genLepton()->eta(), muon->genLepton()->phi() )<matchDR_){
	// fill resolution histograms binned in pt
	for(unsigned int idx=0; idx<(binsPt_.size()-1); ++idx) {
	  if( (binsPt_[idx]<muon->genLepton()->pt()) && (muon->genLepton()->pt()<binsPt_[idx+1]) ){
	    pt_[idx]->Fill((muon->pt()-muon->genLepton()->pt())/(muon->genLepton())->pt(), weight);
	  }
	}
	// fill resolution histograms binned in eta
	for(unsigned int idx=0; idx<(binsEta_.size()-1); ++idx) {
	  if( (binsEta_[idx]<muon->genLepton()->eta()) && (muon->genLepton()->eta()<binsEta_[idx+1]) ){
	    eta_[idx]->Fill(muon->eta()-muon->genLepton()->eta(), weight);
	  }
	}
	// fill resolution histograms binned in phi
	for(unsigned int idx=0; idx<(binsPhi_.size()-1); ++idx) {
	  if( (binsPhi_[idx]<muon->genLepton()->phi()) && (muon->genLepton()->phi()<binsPhi_[idx+1]) ){
	    phi_[idx]->Fill(deltaPhi(muon->phi(), muon->genLepton()->phi()), weight);
	  }
	}
      }
    }
  }
}
