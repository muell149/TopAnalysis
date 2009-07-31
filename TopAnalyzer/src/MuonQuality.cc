#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonQuality.h"


/// default constructor for fw lite
MuonQuality::MuonQuality() 
{ 
}

/// constructor for full FW analyzer
MuonQuality::MuonQuality(const edm::ParameterSet& cfg) 
{
}

/// histogramm booking for fwlite 
void 
MuonQuality::book()
{
  NameScheme id("id");
  hists_["muComp" ] = new TH1F(id("muComp" ), "muComp" ,  50,   0.,   1.);
  hists_["muEm"   ] = new TH1F(id("muEm"   ), "muEm"   ,  50,   0.,   5.); 
  hists_["muEmS9" ] = new TH1F(id("muEmS9" ), "muEmS9" ,  50,   0.,   5.); 
  hists_["muHad"  ] = new TH1F(id("muHad"  ), "muHad"  ,  50,   0.,   5.); 
  hists_["muHadS9"] = new TH1F(id("muHadS9"), "muHadS9",  50,   0.,   5.);
  hists_["muHo"   ] = new TH1F(id("muHo"   ), "muHo"   ,  50,   0.,   5.); 
  hists_["muHoS9" ] = new TH1F(id("muHoS9" ), "muHoS9" ,  50,   0.,   5.);   
}

/// histogramm booking for full fw
void 
MuonQuality::book(edm::Service<TFileService>& fs)
{
  NameScheme id("id");
  hists_["muComp" ] = fs->make<TH1F>(id("muComp" ), "muComp" ,  50,   0.,   1.);
  hists_["muEm"   ] = fs->make<TH1F>(id("muEm"   ), "muEm"   ,  50,   0.,   5.); 
  hists_["muEmS9" ] = fs->make<TH1F>(id("muEmS9" ), "muEmS9" ,  50,   0.,   5.); 
  hists_["muHad"  ] = fs->make<TH1F>(id("muHad"  ), "muHad"  ,  50,   0.,   5.); 
  hists_["muHadS9"] = fs->make<TH1F>(id("muHadS9"), "muHadS9",  50,   0.,   5.);
  hists_["muHo"   ] = fs->make<TH1F>(id("muHo"   ), "muHo"   ,  50,   0.,   5.); 
  hists_["muHoS9" ] = fs->make<TH1F>(id("muHoS9" ), "muHoS9" ,  50,   0.,   5.);  
}

/// fill interface for FWLite analyzer
void
MuonQuality::fill(const std::vector<pat::Muon>& muons, const double& weight)
{
  std::vector<pat::Muon>::const_iterator muon=muons.begin();
  if(muon!=muons.end()){
    reco::MuonEnergy muEnergy = muon->calEnergy();   
    hists_["muComp" ]->Fill( muon->caloCompatibility(), weight );
    hists_["muEm"   ]->Fill( muEnergy.em   , weight );
    hists_["muEmS9" ]->Fill( muEnergy.emS9 , weight );  
    hists_["muHad"  ]->Fill( muEnergy.had  , weight );
    hists_["muHadS9"]->Fill( muEnergy.hadS9, weight );  
    hists_["muHo"   ]->Fill( muEnergy.ho   , weight );
    hists_["muHoS9" ]->Fill( muEnergy.hoS9 , weight );  
  }
}
