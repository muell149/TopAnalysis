#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonResolution.h"

/// default constructor for fw lite
MuonResolution::MuonResolution(double matchDR, std::vector<double> binsPt, std::vector<double> binsEta, std::vector<double> binsPhi):
  matchDR_( matchDR ), 
  binsPt_ ( binsPt  ),
  binsEta_( binsEta ),
  binsPhi_( binsPhi )
{ 
}

/// default constructor for full fw
MuonResolution::MuonResolution(const edm::ParameterSet& cfg):
  matchDR_( cfg.getParameter<double>( "matchDR" ) ),
  binsPt_ ( cfg.getParameter<std::vector<double> >( "binsPt" ) ),
  binsEta_( cfg.getParameter<std::vector<double> >( "binsEta") ),
  binsPhi_( cfg.getParameter<std::vector<double> >( "binsPhi") )
{
}

/// histogramm booking for fwlite 
void 
MuonResolution::book()
{
  book(pt_,  "pt" , binsPt_,  100,   0.5);
  book(eta_, "eta", binsEta_, 100, 0.005);
  book(phi_, "phi", binsPhi_, 100, 0.005);
}

/// histogramm booking for full fw
void 
MuonResolution::book(edm::Service<TFileService>& fs)
{
  book(fs, pt_,  "pt" , binsPt_,  100,   0.5);
  book(fs, eta_, "eta", binsEta_, 100, 0.005);
  book(fs, phi_, "phi", binsPhi_, 100, 0.005);
}

/// histogram filling for fwlite and for full fw
void
MuonResolution::fill(const std::vector<pat::Muon>& muons, const double& weight)
{
  std::vector<pat::Muon>::const_iterator muon=muons.begin();
  if(muon!=muons.end()){
    if( muon->genLepton() ){ 
      if(deltaR( muon->eta(), muon->phi(), muon->genLepton()->eta(), muon->genLepton()->phi() )<matchDR_){
	for(unsigned int idx=0; idx<(binsPt_.size()-1); ++idx) {
	  if( (binsPt_[idx]<muon->genLepton()->pt()) && (muon->genLepton()->pt()<binsPt_[idx+1]) ){
	    pt_[idx]->Fill((muon->pt()-muon->genLepton()->pt())/(muon->genLepton())->pt(), weight);
	  }
	}
	for(unsigned int idx=0; idx<(binsEta_.size()-1); ++idx) {
	  if( (binsEta_[idx]<muon->genLepton()->eta()) && (muon->genLepton()->eta()<binsEta_[idx+1]) ){
	    eta_[idx]->Fill(muon->eta()-muon->genLepton()->eta(), weight);
	  }
	}
	for(unsigned int idx=0; idx<(binsPhi_.size()-1); ++idx) {
	  if( (binsPhi_[idx]<muon->genLepton()->phi()) && (muon->genLepton()->phi()<binsPhi_[idx+1]) ){
	    phi_[idx]->Fill(deltaPhi(muon->phi(), muon->genLepton()->phi()), weight);
	  }
	}
      }
    }
  }
}

/// writing histograms to file in fwlite
void
MuonResolution::write(TFile& file, const char* directory)
{
  file.cd( directory );
  for(std::vector<TH1F*>::const_iterator hist=pt_ .begin(); hist!=pt_ .end(); ++hist){
    const TH1F* out = *hist;
    out->Write();
  }
  for(std::vector<TH1F*>::const_iterator hist=eta_.begin(); hist!=eta_.end(); ++hist){
     const TH1F* out = *hist;
    out->Write();
  }
  for(std::vector<TH1F*>::const_iterator hist=phi_.begin(); hist!=phi_.end(); ++hist){
     const TH1F* out = *hist;
    out->Write();
  }
}

/// book a vector of histograms according to a given binning
void 
MuonResolution::book(edm::Service<TFileService>& fs, std::vector<TH1F*>& hists, const char* kin, std::vector<double> binning, unsigned int nBins, double boundary)
{
  NameScheme res("res");
  for(unsigned int idx=0; idx<binning.size()-1; ++idx){
    hists.push_back( fs->make<TH1F>(res(kin, binning[idx], binning[idx+1]), res.name(kin,binning[idx], binning[idx+1]), nBins, -boundary, boundary) );
  }  
}

/// book a vector of histograms according to a given binning
void 
MuonResolution::book(std::vector<TH1F*>& hists, const char* kin, std::vector<double> binning, unsigned int nBins, double boundary)
{
  NameScheme res("res");
  for(unsigned int idx=0; idx<binning.size()-1; ++idx){
    hists.push_back( new TH1F(res(kin, binning[idx], binning[idx]+1), res.name(kin,binning[idx], binning[idx+1]), nBins, -boundary, boundary) );
  }  
}
