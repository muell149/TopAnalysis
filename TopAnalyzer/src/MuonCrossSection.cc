#include <Math/Boost.h>
#include <Math/VectorUtil.h>
#include "TopAnalysis/TopAnalyzer/interface/MuonCrossSection.h"

/// default constructor for generator level analysis in fw lite
MuonCrossSection::MuonCrossSection()
{
}

/// default constructor for full fw
MuonCrossSection::MuonCrossSection(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void MuonCrossSection::book()
{
  /** 
      Muon Variables for Cross Section Measurement
  **/
  // muon pt
  hists_["pt" ] = new TH1F( "pt", "pt",   4, CrossSection::muonPt );
}

/// histogramm booking for fw
void MuonCrossSection::book(edm::Service<TFileService>& fs)
{
  /** 
      Muon Variables for Cross Section Measurement
  **/
  // top pt (at the moment both top candidates are filled in one histogram)
  hists_["pt" ] = fs->make<TH1F>( "pt"   , "pt",   4, CrossSection::muonPt );
}

/// histogram filling interface for rec or gen level for access with fwlite or full framework
void
MuonCrossSection::fill(const edm::View<reco::Candidate>& muons, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/
  for(edm::View<reco::Candidate>::const_iterator muon=muons.begin(); muon!=muons.end(); ++muon){
    // transverse momentum of the muon
    hists_.find( "pt"  )->second->Fill( muon->et() , weight );
  }
}

