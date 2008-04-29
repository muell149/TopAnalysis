#include "TopAnalysis/TopAnalyzer/interface/JetResolution.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"


JetResolution::JetResolution(const edm::ParameterSet& cfg):
  nJets_( cfg.getParameter<int> ( "nJetsRes" ) ),
  binsPt_( cfg.getParameter<std::vector<double> >( "binsPt" ) ),
  matchDR_( cfg.getParameter<double>( "matchDR" ) )
{
}

void
JetResolution::fill(const edm::Event& evt, const std::vector<pat::Jet>& jets, const double& weight)
{
  unsigned int idx=0;
  for(std::vector<pat::Jet>::const_iterator jet = jets.begin(); 
       jet!=jets.end(); ++jet) {
    if( abs(jet->genJet()->pdgId())!=0){ 
      double dR=deltaR( jet->eta(), jet->phi(), jet->genJet()->eta(), jet->genJet()->phi() ); 
      if(dR<matchDR_){
	double dPt=(jet->pt()-jet->genJet()->pt())/(jet->genJet())->pt();
	for(unsigned int jdx=0; jdx<(binsPt_.size()-1); ++jdx) {
	  if( (binsPt_[jdx]<jet->genJet()->pt()) && (jet->genJet()->pt()<binsPt_[jdx+1]) ){
	    relPtAll_[jdx]->Fill(dPt, weight);
	    if( idx< relPtAll_.size() ){
	      (relPtJet_[idx])[jdx]->Fill(dPt, weight);
	    }
	  }
	}
      }
    }
  }
}

void
JetResolution::book()
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  NameScheme fit("fit"), cal("cal"), res("res");
  for(int jdx=0; jdx<nJets_; ++jdx){
    std::vector<TH1F*> buffer;
    calPtJet_.push_back(fs->make<TH1F>(cal.name("calPt",jdx), cal.name("calPt",jdx), ((int)binsPt_.size()-1), &binsPt_[0]));
    resPtJet_.push_back(fs->make<TH1F>(res.name("resPt",jdx), res.name("resPt",jdx), ((int)binsPt_.size()-1), &binsPt_[0]));
    for(int idx=0; idx<((int)binsPt_.size()-1); ++idx)
      buffer.push_back( fs->make<TH1F>(fit.name("relPt",jdx,idx), fit.name("relPt",jdx,idx), 100, -0.5, 0.5) );
    relPtJet_.push_back(buffer); 
  }
  for(int idx = 0; idx < ((int)binsPt_.size()-1); ++idx) {
    relPtAll_.push_back( fs->make<TH1F>(fit.name("relPt",idx), fit.name("relPt",idx), 100, -0.5, 0.5) );
  }
  calPtAll_= fs->make<TH1F>(cal.name("calPt"), cal.name("calPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
  resPtAll_= fs->make<TH1F>(res.name("resPt"), res.name("resPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
}

void
JetResolution::book(ofstream& file)
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  NameScheme fit("fit"), cal("cal"), res("res");
  for(int jdx=0; jdx<nJets_; ++jdx){
    std::vector<TH1F*> buffer;
    calPtJet_.push_back(fs->make<TH1F>(cal.name(file,"calPt",jdx), cal.name("calPt",jdx), ((int)binsPt_.size()-1), &binsPt_[0]));
    resPtJet_.push_back(fs->make<TH1F>(res.name(file,"resPt",jdx), res.name("resPt",jdx), ((int)binsPt_.size()-1), &binsPt_[0]));
    for(int idx=0; idx<((int)binsPt_.size()-1); ++idx)
      buffer.push_back( fs->make<TH1F>(fit.name(file,"relPt",jdx,idx), fit.name("relPt",jdx,idx), 100, -0.5, 0.5) );
    relPtJet_.push_back(buffer); 
  }
  for(int idx = 0; idx < ((int)binsPt_.size()-1); ++idx) {
    relPtAll_.push_back( fs->make<TH1F>(fit.name(file,"relPt",idx), fit.name("relPt",idx), 100, -0.5, 0.5) );
  }
  calPtAll_= fs->make<TH1F>(cal.name(file,"calPt"), cal.name("calPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
  resPtAll_= fs->make<TH1F>(res.name(file,"resPt"), res.name("resPt"), ((int)binsPt_.size()-1), &binsPt_[0]);
}

