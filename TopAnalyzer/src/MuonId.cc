#include "TopAnalysis/TopAnalyzer/interface/MuonId.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/MuonReco/interface/MuonEnergy.h"


MuonId::MuonId(const edm::ParameterSet& cfg)  
{
}

void
MuonId::fill(const edm::Event& evt, const std::vector<pat::Muon>& muons, const double& weight=1.)
{
  std::vector<pat::Muon>::const_iterator muon=muons.begin();
  if(muon!=muons.end()){
    reco::MuonEnergy muEnergy = muon->getCalEnergy();   
    muComp_ ->Fill( muon->getCaloCompatibility(), weight );
    muEm_   ->Fill( muEnergy.em, weight );
    muEmS9_ ->Fill( muEnergy.emS9, weight );  
    muHad_  ->Fill( muEnergy.had, weight );
    muHadS9_->Fill( muEnergy.hadS9,weight );  
    muHo_   ->Fill( muEnergy.ho, weight );
    muHoS9_ ->Fill( muEnergy.hoS9, weight );  
  }
}

void 
MuonId::book()
{
  edm::Service<TFileService> fs;

  NameScheme mu("id");
  muComp_ = fs->make<TH1F>(mu.name("muComp" ), mu.name("muComp" ), 50,  0.,  1.);
  muEm_   = fs->make<TH1F>(mu.name("muEm" ),   mu.name("muEm" ),   50,  0.,  5.); 
  muEmS9_ = fs->make<TH1F>(mu.name("muEmS9" ), mu.name("muEmS9" ), 50,  0.,  5.); 
  muHad_  = fs->make<TH1F>(mu.name("muHad" ),  mu.name("muHad" ),  50,  0.,  5.); 
  muHadS9_= fs->make<TH1F>(mu.name("muHadS9" ),mu.name("muHadS9" ),50,  0.,  5.);
  muHo_   = fs->make<TH1F>(mu.name("muHo" ),   mu.name("muHo" ),   50,  0.,  5.); 
  muHoS9_ = fs->make<TH1F>(mu.name("muHoS9" ), mu.name("muHoS9" ), 50,  0.,  5.);   
}

void 
MuonId::book(ofstream& file)
{
  edm::Service<TFileService> fs;

  NameScheme mu("id");
  muComp_ = fs->make<TH1F>(mu.name(file, "muComp" ), mu.name("muComp" ), 50,  0.,  1.);
  muEm_   = fs->make<TH1F>(mu.name(file, "muEm" ),   mu.name("muEm" ),   50,  0.,  5.); 
  muEmS9_ = fs->make<TH1F>(mu.name(file, "muEmS9" ), mu.name("muEmS9" ), 50,  0.,  5.); 
  muHad_  = fs->make<TH1F>(mu.name(file, "muHad" ),  mu.name("muHad" ),  50,  0.,  5.); 
  muHadS9_= fs->make<TH1F>(mu.name(file, "muHadS9" ),mu.name("muHadS9" ),50,  0.,  5.);
  muHo_   = fs->make<TH1F>(mu.name(file, "muHo" ),   mu.name("muHo" ),   50,  0.,  5.); 
  muHoS9_ = fs->make<TH1F>(mu.name(file, "muHoS9" ), mu.name("muHoS9" ), 50,  0.,  5.);   
}
