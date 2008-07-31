#include "TopAnalysis/TopAnalyzer/interface/JetResolution.h"


/// constructor for FWLite analyzer
JetResolution::JetResolution(int nJets, double matchDR, std::vector<double> binsPt):
  nJets_(nJets), binsPt_(binsPt), matchDR_(matchDR)  
{
}

/// constructor for full FW analyzer
JetResolution::JetResolution(const edm::ParameterSet& cfg):
  nJets_( cfg.getParameter<int> ( "nJets" ) ),
  binsPt_( cfg.getParameter<std::vector<double> >( "binsPt" ) ),
  matchDR_( cfg.getParameter<double>( "matchDR" ) )
{
}

/// fill interface for full FW analyzer
void
JetResolution::fill(const edm::Event& evt, const std::vector<pat::Jet>& jets, const double& weight)
{
  fill(jets, weight);
}

/// fill interface for FWLite analyzer
void
JetResolution::fill(const std::vector<pat::Jet>& jets, const double& weight)
{
  unsigned int idx=0;
  for(std::vector<pat::Jet>::const_iterator jet = jets.begin(); 
      jet!=jets.end(); ++jet, ++idx) {
    if( jet->genJet() ){ 
      double dR=deltaR( jet->eta(), jet->phi(), jet->genJet()->eta(), jet->genJet()->phi() ); 
      if(dR<matchDR_){
	double dPt=(jet->pt()-jet->genJet()->pt())/(jet->genJet())->pt();
	for(unsigned int jdx=0; jdx<(binsPt_.size()-1); ++jdx) {
	  if( (binsPt_[jdx]<jet->genJet()->pt()) && (jet->genJet()->pt()<binsPt_[jdx+1]) ){
	    relPtAll_[jdx]->Fill(dPt, weight);
	    if( idx< relPtJet_.size() ){
	      (relPtJet_[idx])[jdx]->Fill(dPt, weight);
	    }
	  }
	}
      }
    }
  }
}

/// book for FWLite
void
JetResolution::book()
{
  NameScheme fit("fit"), cal("cal"), res("res");
  for(int jdx=0; jdx<nJets_; ++jdx){
    std::vector<TH1F*> buffer;
    calPtJet_.push_back(new TH1F(cal.name("calPt",jdx), cal.name("calPt",jdx), ((int)binsPt_.size()-1), &binsPt_[0]));
    resPtJet_.push_back(new TH1F(res.name("relPt",jdx), res.name("relPt",jdx), ((int)binsPt_.size()-1), &binsPt_[0]));
    for(int idx=0; idx<((int)binsPt_.size()-1); ++idx)
      buffer.push_back( new TH1F(fit.name("relPt",jdx,idx), fit.name("relPt",jdx,idx), 100, -0.5, 0.5) );
    relPtJet_.push_back(buffer); 
  }
  for(int idx = 0; idx < ((int)binsPt_.size()-1); ++idx) {
    relPtAll_.push_back( new TH1F(fit.name("relPt",idx), fit.name("relPt",idx), 100, -0.5, 0.5) );
  }
  calPtAll_= new TH1F(cal.name("calPt"), cal.name("calPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
  resPtAll_= new TH1F(res.name("relPt"), res.name("relPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
}

/// book for full FW
void
JetResolution::book(edm::Service<TFileService>& fs)
{
  NameScheme fit("fit"), cal("cal"), res("res");
  for(int jdx=0; jdx<nJets_; ++jdx){
    std::vector<TH1F*> buffer;
    calPtJet_.push_back(fs->make<TH1F>(cal.name("calPt",jdx), cal.name("calPt",jdx), ((int)binsPt_.size()-1), &binsPt_[0]));
    resPtJet_.push_back(fs->make<TH1F>(res.name("relPt",jdx), res.name("relPt",jdx), ((int)binsPt_.size()-1), &binsPt_[0]));
    for(int idx=0; idx<((int)binsPt_.size()-1); ++idx)
      buffer.push_back( fs->make<TH1F>(fit.name("relPt",jdx,idx), fit.name("relPt",jdx,idx), 100, -0.5, 0.5) );
    relPtJet_.push_back(buffer); 
  }
  for(int idx = 0; idx < ((int)binsPt_.size()-1); ++idx) {
    relPtAll_.push_back( fs->make<TH1F>(fit.name("relPt",idx), fit.name("relPt",idx), 100, -0.5, 0.5) );
  }
  calPtAll_= fs->make<TH1F>(cal.name("calPt"), cal.name("calPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
  resPtAll_= fs->make<TH1F>(res.name("relPt"), res.name("relPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
}

/// book for full FW with output stream
void
JetResolution::book(edm::Service<TFileService>& fs, ofstream& file)
{
  NameScheme fit("fit"), cal("cal"), res("res");
  for(int jdx=0; jdx<nJets_; ++jdx){
    std::vector<TH1F*> buffer;
    calPtJet_.push_back(fs->make<TH1F>(cal.name(file,"calPt",jdx), cal.name("calPt",jdx), ((int)binsPt_.size()-1), &binsPt_[0]));
    resPtJet_.push_back(fs->make<TH1F>(res.name(file,"relPt",jdx), res.name("relPt",jdx), ((int)binsPt_.size()-1), &binsPt_[0]));
    for(int idx=0; idx<((int)binsPt_.size()-1); ++idx)
      buffer.push_back( fs->make<TH1F>(fit.name(file,"relPt",jdx,idx), fit.name("relPt",jdx,idx), 100, -0.5, 0.5) );
    relPtJet_.push_back(buffer); 
  }
  for(int idx = 0; idx < ((int)binsPt_.size()-1); ++idx) {
    relPtAll_.push_back( fs->make<TH1F>(fit.name(file,"relPt",idx), fit.name("relPt",idx), 100, -0.5, 0.5) );
  }
  calPtAll_= fs->make<TH1F>(cal.name(file,"calPt"), cal.name("calPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
  resPtAll_= fs->make<TH1F>(res.name(file,"relPt"), res.name("relPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
}

/// write to file and free allocated space for FWLite
void 
JetResolution::write(const char* filename, const char* directory)
{
  /// save histograms to file
  TFile outFile( filename, "recreate" );
  outFile.mkdir( directory );
  outFile.cd( directory );

  /// basic kinematic
  calPtAll_->Write( );
  resPtAll_->Write( );

  outFile.Close();

  // free allocated space
  delete calPtAll_;
  delete resPtAll_;
}
