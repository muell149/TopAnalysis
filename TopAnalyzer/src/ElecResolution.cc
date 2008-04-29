#include "TopAnalysis/TopAnalyzer/interface/ElecResolution.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"


ElecResolution::ElecResolution(const edm::ParameterSet& cfg):
  binsPt_ ( cfg.getParameter<std::vector<double> >( "binsPt" ) ),
  matchDR_( cfg.getParameter<double>( "matchDR" ) )
{
}

void
ElecResolution::fill(const edm::Event& evt, const std::vector<pat::Electron>& elecs, const double& weight=1.)
{
  std::vector<pat::Electron>::const_iterator elec=elecs.begin();
  if(elec!=elecs.end()){
    if( abs(elec->genLepton()->pdgId())!=0){ 
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

void 
ElecResolution::book()
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );
  
  NameScheme fit("fit"), cal("cal"), res("res");
  for(int idx = 0; idx < ((int)binsPt_.size()-1); ++idx) {
    relPt_.push_back( fs->make<TH1F>(fit.name("relPt",idx), fit.name("relPt",idx), 100, -0.5, 0.5) );
  }
  calPt_= fs->make<TH1F>(cal.name("pt"), cal.name("pt"), ((int)binsPt_.size()-1), &binsPt_[0]);
  resPt_= fs->make<TH1F>(res.name("pt"), res.name("pt"), ((int)binsPt_.size()-1), &binsPt_[0]);
}

void 
ElecResolution::book(ofstream& file)
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );
  
  NameScheme fit("fit"), cal("cal"), res("res");
  for(int idx = 0; idx < ((int)binsPt_.size()-1); ++idx) {
    relPt_.push_back( fs->make<TH1F>(fit.name(file,"relPt",idx), fit.name("relPt",idx), 100, -0.5, 0.5) );
  }
  calPt_= fs->make<TH1F>(cal.name(file,"pt"), cal.name("pt"), ((int)binsPt_.size()-1), &binsPt_[0]);
  resPt_= fs->make<TH1F>(res.name(file,"pt"), res.name("pt"), ((int)binsPt_.size()-1), &binsPt_[0]);
}

