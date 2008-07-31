#include "TopAnalysis/TopAnalyzer/interface/ElecResolution.h"


/// constructor for FWLite analyzer
ElecResolution::ElecResolution(std::vector<double> binsPt, double matchDR):
  binsPt_(binsPt), matchDR_(matchDR)  
{
}

/// constructor for full FW analyzer
ElecResolution::ElecResolution(const edm::ParameterSet& cfg):
  binsPt_ ( cfg.getParameter<std::vector<double> >( "binsPt" ) ),
  matchDR_( cfg.getParameter<double>( "matchDR" ) )
{
}

/// fill interface for full FW analyzer
void
ElecResolution::fill(const edm::Event& evt, const std::vector<pat::Electron>& elecs, const double& weight=1.)
{
  if(elecs.begin()==elecs.end()) return;
  fill(elecs, weight);
}

/// fill interface for FWLite analyzer
void
ElecResolution::fill(const std::vector<pat::Electron>& elecs, const double& weight=1.)
{
  std::vector<pat::Electron>::const_iterator elec=elecs.begin();
  if(elec!=elecs.end()){
    if( elec->genLepton()!=0 ){ 
      double dR=deltaR( elec->eta(), elec->phi(), elec->genLepton()->eta(), elec->genLepton()->phi() ); 
      if(dR<matchDR_){
	double dPt=(elec->pt()-elec->genLepton()->pt())/(elec->genLepton())->pt();
	for(unsigned int idx=0; idx<(binsPt_.size()-1); ++idx) {
	  if( (binsPt_[idx]<elec->genLepton()->pt()) && (elec->genLepton()->pt()<binsPt_[idx+1]) ){
	    relPt_[idx]->Fill(dPt, weight);
	  }
	}
      }
    }
  }
}

/// book for FWLite
void 
ElecResolution::book()
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
ElecResolution::book(edm::Service<TFileService>& fs)
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
ElecResolution::book(edm::Service<TFileService>& fs, ofstream& file)
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
ElecResolution::write(const char* filename, const char* directory)
{
  /// save histograms to file
  TFile outFile( filename, "recreate" );
  outFile.mkdir( directory );
  outFile.cd( directory );

  /// basic kinematic
  calPt_->Write( );
  resPt_->Write( );

  outFile.Close();

  // free allocated space
  delete calPt_;
  delete resPt_;
}
