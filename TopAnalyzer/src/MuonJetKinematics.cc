#include "DataFormats/Math/interface/deltaR.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonJetKinematics.h"

/// default constructor for fw lite
MuonJetKinematics::MuonJetKinematics()
{
}

/// default constructor for full fw
MuonJetKinematics::MuonJetKinematics(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void
MuonJetKinematics::book()
{
  /** 
      Distance between muon and closest jet in deltaR for different pt thresholds
  **/
  // jets with pt>20
  hists_["dist20_"] = new TH1F( "dist20_" , "dist20_" ,   40,   0.,   1.);
  // jets with pt>30
  hists_["dist30_"] = new TH1F( "dist30_" , "dist30_" ,   40,   0.,   1.);
  // jets with pt>40
  hists_["dist40_"] = new TH1F( "dist40_" , "dist40_" ,   40,   0.,   1.);
}

/// histogramm booking for full fw
void
MuonJetKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Distance between muon and closest jet in deltaR for different pt thresholds
  **/
  // jets with pt>20
  hists_["dist20_"] = fs->make<TH1F>( "dist20_" , "dist20_" ,   20,   0.,   1.);
  // jets with pt>30
  hists_["dist30_"] = fs->make<TH1F>( "dist30_" , "dist30_" ,   20,   0.,   1.);
  // jets with pt>40
  hists_["dist40_"] = fs->make<TH1F>( "dist40_" , "dist40_" ,   20,   0.,   1.);
}

/// histogram filling for fwlite and for full fw
void
MuonJetKinematics::fill(const edm::View<pat::Muon>& muons, const edm::View<pat::Jet>& jets, const double& weight)
{
  for(edm::View<pat::Muon>::const_iterator muon=muons.begin(); muon!=muons.end(); ++muon){
    double dist20=-1., dist30=-1., dist40=-1.;
    for(edm::View<pat::Jet>::const_iterator jet = jets.begin(); jet!=jets.end(); ++jet){
      double dR=deltaR(muon->eta(), muon->phi(), jet->eta(), jet->phi());
      // determine closest jet muon with pt>20
      if( jet->pt()>20 && (dR<dist20 || dist20<0.) ){ dist20=dR; }
      // determine closest jet muon with pt>30
      if( jet->pt()>30 && (dR<dist30 || dist30<0.) ){ dist30=dR; }
      // determine closest jet muon with pt>40
      if( jet->pt()>40 && (dR<dist40 || dist40<0.) ){ dist40=dR; }
    }
    /**
       Fill Distance histograms
    **/    
    if( dist20>=0 ) hists_.find("dist20_" )->second->Fill( dist20, weight );
    if( dist30>=0 ) hists_.find("dist30_" )->second->Fill( dist30, weight );
    if( dist40>=0 ) hists_.find("dist40_" )->second->Fill( dist40, weight );
  }
}
