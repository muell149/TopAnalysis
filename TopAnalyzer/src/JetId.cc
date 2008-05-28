#include "TopAnalysis/TopAnalyzer/interface/JetId.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"


JetId::JetId(const edm::ParameterSet& cfg):
  nJets_( cfg.getParameter<int>( "nJetsId" ) ),
  normEvt_( 0 ), normJet_( 0 )
{
}

void
JetId::fill(const edm::Event& evt, const std::vector<pat::Jet>& jets, const double& weight=1.)
{
  normEvt_+=weight;
  unsigned int idx=0;
  for(std::vector<pat::Jet>::const_iterator jet = jets.begin(); 
      jet!=jets.end(); ++jet, ++idx) {
    normJet_+=weight;
    aEmf_->Fill( jet->emEnergyFraction(), weight );
    aHad_->Fill( jet->energyFractionHadronic(), weight );
    aHof_->Fill( jet->hadEnergyInHO(), weight );
    
    if( idx<emf_.size() ) emf_[idx]->Fill( jet->emEnergyFraction(), weight );
    if( idx<had_.size() ) had_[idx]->Fill( jet->energyFractionHadronic(), weight );
    if( idx<hof_.size() ) hof_[idx]->Fill( jet->hadEnergyInHO(), weight );
    
    //---------------------------------------------
    // check jet profiles
    //---------------------------------------------
    nTwr_->Fill(jet->getCaloConstituents().size(), weight);
    std::vector<CaloTowerRef> caloTowerRef = jet->getCaloConstituents();
    for(unsigned int jdx=0; jdx<caloTowerRef.size(); ++jdx){
      aProfEta_->Fill( jet->eta()-caloTowerRef[jdx]->eta(), caloTowerRef[jdx]->et() );
      aProfPhi_->Fill( jet->phi()-caloTowerRef[jdx]->phi(), caloTowerRef[jdx]->et() );
      
      if( idx<profEta_.size()) profEta_[idx]->Fill( jet->eta()-caloTowerRef[jdx]->eta(), caloTowerRef[jdx]->et() );
      if( idx<profPhi_.size()) profPhi_[idx]->Fill( jet->phi()-caloTowerRef[jdx]->phi(), caloTowerRef[jdx]->et() );
    }
  }
}

void 
JetId::book()
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );
  
  NameScheme id("id");
  aEmf_= fs->make<TH1F>(id.name("allEmf"),  id.name("All em. energy frac."  ), 60, -0.1,  1.1);
  aHad_= fs->make<TH1F>(id.name("allHdf"),  id.name("All hadr. energy frac."), 60, -0.1,  1.1);
  aHof_= fs->make<TH1F>(id.name("allHdHO"), id.name("All hadr. energy in HO"), 55, -10., 100.);
  
  for(int idx=0; idx<nJets_; ++idx){
    emf_.push_back( fs->make<TH1F>(id.name("emf",idx), id.name("emf",idx), 60, -0.1,  1.1) );
    had_.push_back( fs->make<TH1F>(id.name("had",idx), id.name("had",idx), 60, -0.1,  1.1) );
    hof_.push_back( fs->make<TH1F>(id.name("hof",idx), id.name("hof",idx), 55, -10., 100.) );
  }
  
  NameScheme pro("pro");
  nTwr_ = fs->make<TH1F>(pro.name("nTwr"), pro.name("nTwr"), 100, 0., 100.);
  aProfEta_= fs->make<TH1F>(pro.name("allEta"), pro.name("allEta"), 50, -0.5, 0.5);
  aProfPhi_= fs->make<TH1F>(pro.name("allPhi"), pro.name("allPhi"), 50, -0.5, 0.5);
  
  for(int idx=0; idx<nJets_; ++idx){
    profEta_.push_back( fs->make<TH1F>(pro.name("eta", idx),pro.name("eta", idx), 50, -0.5, 0.5) );
    profPhi_.push_back( fs->make<TH1F>(pro.name("phi", idx),pro.name("phi", idx), 50, -0.5, 0.5) );
  }
}

void 
JetId::book(ofstream& file)
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );
  
  NameScheme id("id");
  aEmf_= fs->make<TH1F>(id.name(file, "allEmf"),  id.name("All em. energy frac."  ), 60, -0.1,  1.1);
  aHad_= fs->make<TH1F>(id.name(file, "allHdf"),  id.name("All hadr. energy frac."), 60, -0.1,  1.1);
  aHof_= fs->make<TH1F>(id.name(file, "allHdHO"), id.name("All hadr. energy in HO"), 55, -10., 100.);
  
  for(int idx=0; idx<nJets_; ++idx){
    emf_.push_back( fs->make<TH1F>(id.name(file, "emf",idx), id.name("emf",idx), 60, -0.1,  1.1) );
    had_.push_back( fs->make<TH1F>(id.name(file, "had",idx), id.name("had",idx), 60, -0.1,  1.1) );
    hof_.push_back( fs->make<TH1F>(id.name(file, "hof",idx), id.name("hof",idx), 55, -10., 100.) );
  }
  
  NameScheme pro("pro");
  nTwr_ = fs->make<TH1F>(pro.name(file,"nTwr"), pro.name("nTwr"), 100, 0., 100.);
  aProfEta_= fs->make<TH1F>(pro.name(file,"allEta"), pro.name("allEta"), 50, -0.5, 0.5);
  aProfPhi_= fs->make<TH1F>(pro.name(file,"allPhi"), pro.name("allPhi"), 50, -0.5, 0.5);
  
  for(int idx=0; idx<nJets_; ++idx){
    profEta_.push_back( fs->make<TH1F>(pro.name(file,"eta", idx),pro.name("eta", idx), 50, -0.5, 0.5) );
    profPhi_.push_back( fs->make<TH1F>(pro.name(file,"phi", idx),pro.name("phi", idx), 50, -0.5, 0.5) );
  }
}
