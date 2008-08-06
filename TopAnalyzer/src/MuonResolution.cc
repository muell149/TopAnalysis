#include "TopAnalysis/TopAnalyzer/interface/MuonResolution.h"


/// constructor for FWLite analyzer
MuonResolution::MuonResolution():
  fwLite_(true ) { }

/// constructor for full FW analyzer
MuonResolution::MuonResolution(const edm::ParameterSet& cfg):
  fwLite_(true ),   
  binsPt_ ( cfg.getParameter<std::vector<double> >( "binsPt" ) ),
  matchDR_( cfg.getParameter<double>( "matchDR" ) )
{
}

/// fill interface for full FW analyzer
void
MuonResolution::fill(const edm::Event& evt, const std::vector<pat::Muon>& muons, const double& weight = 1.)
{
  if(muons.begin()==muons.end()) return;
  fill(muons, weight);
}

/// fill interface for FWLite analyzer
void
MuonResolution::fill(const std::vector<pat::Muon>& muons, const double& weight = 1.)
{
  std::vector<pat::Muon>::const_iterator muon=muons.begin();
  if(muon!=muons.end()){
    if( muon->genLepton()!=0 ){ 
      double dR=deltaR( muon->eta(), muon->phi(), muon->genLepton()->eta(), muon->genLepton()->phi() ); 
      if(dR<matchDR_){
	double dPt=(muon->pt()-muon->genLepton()->pt())/(muon->genLepton())->pt();
	for(unsigned int idx=0; idx<(binsPt_.size()-1); ++idx) {
	  if( (binsPt_[idx]<muon->genLepton()->pt()) && (muon->genLepton()->pt()<binsPt_[idx+1]) ){
	    relPt_[idx]->Fill(dPt, weight);
	  }
	}
      }
    }
  }
}

/// book for FWLite
void 
MuonResolution::book()
{
  NameScheme fit("fit"), cal("cal"), res("res");
  for(int idx = 0; idx < ((int)binsPt_.size()-1); ++idx) {
    relPt_.push_back( new TH1F(fit.name("relPt",idx), fit.name("relPt",idx), 100, -0.5, 0.5) );
  }
  calPt_= new TH1F(cal.name("relPt"), cal.name("relPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
  resPt_= new TH1F(res.name("relPt"), res.name("relPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
}

/// book for full FW
void 
MuonResolution::book(edm::Service<TFileService>& fs)
{
  NameScheme fit("fit"), cal("cal"), res("res");
  for(int idx = 0; idx < ((int)binsPt_.size()-1); ++idx) {
    relPt_.push_back( fs->make<TH1F>(fit.name("relPt",idx), fit.name("relPt",idx), 100, -0.5, 0.5) );
  }
  calPt_= fs->make<TH1F>(cal.name("relPt"), cal.name("relPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
  resPt_= fs->make<TH1F>(res.name("relPt"), res.name("relPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
}

/// book for full FW with output stream
void 
MuonResolution::book(edm::Service<TFileService>& fs, ofstream& file)
{
  NameScheme fit("fit"), cal("cal"), res("res");
  for(int idx = 0; idx < ((int)binsPt_.size()-1); ++idx) {
    relPt_.push_back( fs->make<TH1F>(fit.name(file,"relPt",idx), fit.name("relPt",idx), 100, -0.5, 0.5) );
  } 
  calPt_= fs->make<TH1F>(cal.name(file,"relPt"), cal.name("relPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
  resPt_= fs->make<TH1F>(res.name(file,"relPt"), res.name("relPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
}

/// write to file and free allocated space for FWLite
void 
MuonResolution::write(TFile& file, const char* directory)
{
  /// save histograms to file
  file.cd( directory );
  calPt_->Write( );
  resPt_->Write( );
}
