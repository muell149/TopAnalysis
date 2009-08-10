#include "TopAnalysis/TopAnalyzer/interface/MuonKinematics.h"

/// default constructor for fw lite
MuonKinematics::MuonKinematics()
{
}

/// default constructor for full fw
MuonKinematics::MuonKinematics(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void
MuonKinematics::book()
{
  hists_["en" ] = new TH1F( "en"  , "en"  ,  60 ,     0. ,   300. );
  hists_["pt" ] = new TH1F( "pt"  , "pt"  ,  30 ,     0. ,   150. );
  hists_["eta"] = new TH1F( "eta" , "eta" ,  70 ,   -3.5 ,    3.5 );
  hists_["phi"] = new TH1F( "phi" , "phi" ,  70 ,   -3.5 ,    3.5 );
}

/// histogramm booking for full fw
void
MuonKinematics::book(edm::Service<TFileService>& fs)
{
  hists_["en" ] = fs->make<TH1F>( "en"  , "en"  ,  60 ,     0. ,   300. );
  hists_["pt" ] = fs->make<TH1F>( "pt"  , "pt"  ,  30 ,     0. ,   150. );
  hists_["eta"] = fs->make<TH1F>( "eta" , "eta" ,  70 ,   -3.5 ,    3.5 );
  hists_["phi"] = fs->make<TH1F>( "phi" , "phi" ,  70 ,   -3.5 ,    3.5 );
}

/// histogram filling for fwlite and for full fw
void
MuonKinematics::fill(const std::vector<reco::GenParticle>& muons, const double& weight)
{
  std::vector<reco::GenParticle>::const_iterator muon=muons.begin();
  if(muon!=muons.end()){
    hists_.find( "en"  )->second->Fill( muon->energy(), weight );
    hists_.find( "pt"  )->second->Fill( muon->et(),     weight );
    hists_.find( "eta" )->second->Fill( muon->eta(),    weight );
    hists_.find( "phi" )->second->Fill( muon->phi(),    weight );
  }
}

/// histogram filling for fwlite and for full fw
void
MuonKinematics::fill(const std::vector<pat::Muon>& muons, const double& weight)
{
  std::vector<pat::Muon>::const_iterator muon=muons.begin();
  if(muon!=muons.end()){
    hists_.find( "en"  )->second->Fill( muon->energy(), weight );
    hists_.find( "pt"  )->second->Fill( muon->et(),     weight );
    hists_.find( "eta" )->second->Fill( muon->eta(),    weight );
    hists_.find( "phi" )->second->Fill( muon->phi(),    weight );
  }
}
