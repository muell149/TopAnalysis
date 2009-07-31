#include "DataFormats/Math/interface/deltaR.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonJetKinematics.h"


/// default constructor for fw lite
MuonJetKinematics::MuonJetKinematics():norm_(0.)
{
}

/// default constructor for full fw
MuonJetKinematics::MuonJetKinematics(const edm::ParameterSet& cfg):norm_(0.)
{
}

/// histogramm booking for fwlite 
void
MuonJetKinematics::book()
{
  NameScheme kin("kin");
  hists_["dR20N" ] = new TH1F(kin("dR20N" ), "dR20N"  ,    20,    0.,    1.);
  hists_["dR30N" ] = new TH1F(kin("dR30N" ), "dR30N"  ,    20,    0.,    1.);
  hists_["dR40N" ] = new TH1F(kin("dR40N" ), "dR40N"  ,    20,    0.,    1.);
  hists_["dR20Pt"] = new TH1F(kin("dR20Pt"), "dR20Pt" ,    20,    0.,    1.);
  hists_["dR30Pt"] = new TH1F(kin("dR30Pt"), "dR30Pt" ,    20,    0.,    1.);
  hists_["dR40Pt"] = new TH1F(kin("dR40Pt"), "dR40Pt" ,    20,    0.,    1.);
}

/// histogramm booking for full fw
void
MuonJetKinematics::book(edm::Service<TFileService>& fs)
{
  NameScheme kin("kin");
  hists_["dR20N" ] = fs->make<TH1F>(kin("dR20N" ), "dR20N"  ,    20,    0.,    1.);
  hists_["dR30N" ] = fs->make<TH1F>(kin("dR30N" ), "dR30N"  ,    20,    0.,    1.);
  hists_["dR40N" ] = fs->make<TH1F>(kin("dR40N" ), "dR40N"  ,    20,    0.,    1.);
  hists_["dR20Pt"] = fs->make<TH1F>(kin("dR20Pt"), "dR20Pt" ,    20,    0.,    1.);
  hists_["dR30Pt"] = fs->make<TH1F>(kin("dR30Pt"), "dR30Pt" ,    20,    0.,    1.);
  hists_["dR40Pt"] = fs->make<TH1F>(kin("dR40Pt"), "dR40Pt" ,    20,    0.,    1.);
}

/// histogram filling for fwlite and for full fw
void
MuonJetKinematics::fill(const std::vector<pat::Muon>& muons, const std::vector<pat::Jet>& jets, const double& weight)
{
  std::vector<pat::Muon>::const_iterator muon=muons.begin();
  if(muon!=muons.end()){

    double minDR20=-1., minDR30=-1., minDR40=-1.;
    double minPt20=-1., minPt30=-1., minPt40=-1.;
    for(std::vector<pat::Jet>::const_iterator jet = jets.begin(); jet!=jets.end(); ++jet) {
      double dR=deltaR(muon->eta(), muon->phi(), jet->eta(), jet->phi());
      if(fabs(jet->eta())<2.4 && jet->pt()>20){
	if(dR<minDR20 || minDR20<0.){
	  minDR20=dR;
	  minPt20=jet->pt();
	}
      }
      if(fabs(jet->eta())<2.4 && jet->pt()>30){
	if(dR<minDR30 || minDR30<0.){
	  minDR30=dR;
	  minPt30=jet->pt();
	}
      }
      if(fabs(jet->eta())<2.4 && jet->pt()>40){
	if(dR<minDR40 || minDR40<0.){
	  minDR40=dR;
	  minPt40=jet->pt();
	}
      }
    }

    // fill enegry flow and object flow histograms
    norm_+=weight; 
    hists_["dR20N"  ]->Fill( minDR20, weight  );
    hists_["dR30N"  ]->Fill( minDR30, weight  );
    hists_["dR40N"  ]->Fill( minDR40, weight  );
    hists_["dR20Pt" ]->Fill( minDR20, minPt20 );
    hists_["dR30Pt" ]->Fill( minDR30, minPt30 );
    hists_["dR40Pt" ]->Fill( minDR40, minPt40 );
  }
}

/// everything which needs to be done after the event loop
void 
MuonJetKinematics::process()
{
  // normalize histograms to the number of muons, then went in
  hists_["dR20N" ]->Scale( 1./norm_ );
  hists_["dR30N" ]->Scale( 1./norm_ );
  hists_["dR40N" ]->Scale( 1./norm_ );
  hists_["dR20Pt"]->Scale( 1./norm_ );
  hists_["dR30Pt"]->Scale( 1./norm_ );
  hists_["dR40Pt"]->Scale( 1./norm_ );
}
