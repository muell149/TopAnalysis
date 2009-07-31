#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonKinematics.h"


/// default constructor for fw lite
MuonKinematics::MuonKinematics():norm_(0.)
{
}

/// default constructor for full fw
MuonKinematics::MuonKinematics(const edm::ParameterSet& cfg):norm_(0.)
{
}

/// histogramm booking for fwlite 
void
MuonKinematics::book()
{
  NameScheme kin("kin");
  hists_["en"        ] = new TH1F(kin("en"        ), "en",          60,    0.,  300.);
  hists_["pt"        ] = new TH1F(kin("pt"        ), "pt",          30,    0.,  150.);
  hists_["eta"       ] = new TH1F(kin("eta"       ), "eta",         70,  -3.5,   3.5);
  hists_["phi"       ] = new TH1F(kin("phi"       ), "phi",         70,  -3.5,   3.5);
  hists_["isoTrkN"   ] = new TH1F(kin("isoTrkN"   ), "isoTrkN" ,    20,    0.,   20.);
  hists_["isoTrkPt"  ] = new TH1F(kin("isoTrkPt"  ), "isoTrkPt",    60,   -1.,    5.);
  hists_["isoEcalN"  ] = new TH1F(kin("isoEcalN"  ), "isoEcalN",    30,    0.,   30.);
  hists_["isoHcalN"  ] = new TH1F(kin("isoHcalN"  ), "isoHcalN",    30,    0.,   30.);
  hists_["isoVetoPt" ] = new TH1F(kin("isoVetoPt" ), "isoVetoPt",   40,  -10.,   30.);
  hists_["isoCalPt"  ] = new TH1F(kin("isoCalPt"  ), "isoCalPt",    40,  -10.,   30.);
  hists_["isoRelPt"  ] = new TH1F(kin("isoRelPt"  ), "isoRelPt",    44,    0.,   1.1);
  hists_["isoRelComb"] = new TH1F(kin("isoRelComb"), "isoRelComb" , 44,    0.,   1.1);
  hists_["dRTrkN"    ] = new TH1F(kin("dRTrkN"    ), "dRTrkN"  ,    20,    0.,    1.);
  hists_["dRTrkPt"   ] = new TH1F(kin("dRTrkPt"   ), "dRTrkPt" ,    20,    0.,    1.);
  hists_["dREcalN"   ] = new TH1F(kin("dREcalN"   ), "dREcalN" ,    20,    0.,    1.);
  hists_["dREcalPt"  ] = new TH1F(kin("dREcalPt"  ), "dREcalPt",    20,    0.,    1.);
  hists_["dRHcalN"   ] = new TH1F(kin("dRHcalN"   ), "dRHcalN" ,    20,    0.,    1.);
  hists_["dRHcalPt"  ] = new TH1F(kin("dRHcalPt"  ), "dRHcalPt",    20,    0.,    1.);
}

/// histogramm booking for full fw
void
MuonKinematics::book(edm::Service<TFileService>& fs)
{
  NameScheme kin("kin");
  hists_["en"        ] = fs->make<TH1F>(kin("en"        ), "en",          60,    0.,  300.);
  hists_["pt"        ] = fs->make<TH1F>(kin("pt"        ), "pt",          30,    0.,  150.);
  hists_["eta"       ] = fs->make<TH1F>(kin("eta"       ), "eta",         70,  -3.5,   3.5);
  hists_["phi"       ] = fs->make<TH1F>(kin("phi"       ), "phi",         70,  -3.5,   3.5);
  hists_["isoTrkN"   ] = fs->make<TH1F>(kin("isoTrkN"   ), "isoTrkN" ,    20,    0.,   20.);
  hists_["isoTrkPt"  ] = fs->make<TH1F>(kin("isoTrkPt"  ), "isoTrkPt",    60,   -1.,    5.);
  hists_["isoEcalN"  ] = fs->make<TH1F>(kin("isoEcalN"  ), "isoEcalN",    30,    0.,   30.);
  hists_["isoHcalN"  ] = fs->make<TH1F>(kin("isoHcalN"  ), "isoHcalN",    30,    0.,   30.);
  hists_["isoVetoPt" ] = fs->make<TH1F>(kin("isoVetoPt" ), "isoVetoPt",   40,  -10.,   30.);
  hists_["isoCalPt"  ] = fs->make<TH1F>(kin("isoCalPt"  ), "isoCalPt",    40,  -10.,   30.);
  hists_["isoRelPt"  ] = fs->make<TH1F>(kin("isoRelPt"  ), "isoRelPt",    44,    0.,   1.1);
  hists_["isoRelComb"] = fs->make<TH1F>(kin("isoRelComb"), "isoRelComb" , 44,    0.,   1.1);
  hists_["dRTrkN"    ] = fs->make<TH1F>(kin("dRTrkN"    ), "dRTrkN"  ,    20,    0.,    1.);
  hists_["dRTrkPt"   ] = fs->make<TH1F>(kin("dRTrkPt"   ), "dRTrkPt" ,    20,    0.,    1.);
  hists_["dREcalN"   ] = fs->make<TH1F>(kin("dREcalN"   ), "dREcalN" ,    20,    0.,    1.);
  hists_["dREcalPt"  ] = fs->make<TH1F>(kin("dREcalPt"  ), "dREcalPt",    20,    0.,    1.);
  hists_["dRHcalN"   ] = fs->make<TH1F>(kin("dRHcalN"   ), "dRHcalN" ,    20,    0.,    1.);
  hists_["dRHcalPt"  ] = fs->make<TH1F>(kin("dRHcalPt"  ), "dRHcalPt",    20,    0.,    1.);
}

/// get number of objects within a ring in deltaR corresponding top the bin width 
/// of the histogram hist from iso deposits and fill hist with it
void
MuonKinematics::fillObjectFlowHistogram(TH1F* hist, const pat::IsoDeposit* deposit)
{
  if(hist && deposit){
    for(int bin=1; bin<=hist->GetNbinsX(); ++bin){
      double lowerEdge = hist->GetBinLowEdge(bin);
      double upperEdge = hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
      hist->Fill(hist->GetBinCenter(bin), deposit->countWithin(upperEdge) - deposit->countWithin(lowerEdge));
    }
  }
}

/// get energy of objects within a ring in deltaR corresponding top the bin width 
/// of the histogram hist from iso deposits and fill hist with it
void
MuonKinematics::fillEnergyFlowHistogram(TH1F* hist, const pat::IsoDeposit* deposit)
{
  if(hist && deposit){
    for(int bin=1; bin<=hist->GetNbinsX(); ++bin){
      double lowerEdge = hist->GetBinLowEdge(bin);
      double upperEdge = hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
      hist->Fill(hist->GetBinCenter(bin), deposit->depositWithin(upperEdge) - deposit->depositWithin(lowerEdge));
    }
  }
}

/// histogram filling for fwlite and for full fw
void
MuonKinematics::fill(const std::vector<pat::Muon>& muons, const double& weight)
{
  std::vector<pat::Muon>::const_iterator muon=muons.begin();
  if(muon!=muons.end()){
    // fill basic kinematics
    hists_["en" ]->Fill( muon->energy(), weight );
    hists_["pt" ]->Fill( muon->et(),     weight );
    hists_["eta"]->Fill( muon->eta(),    weight );
    hists_["phi"]->Fill( muon->phi(),    weight );

    // fill enegry flow and object flow histograms
    norm_+=weight;
    fillObjectFlowHistogram( hists_["dREcalN" ], muon->ecalIsoDeposit() );
    fillEnergyFlowHistogram( hists_["dREcalPt"], muon->ecalIsoDeposit() );
    fillObjectFlowHistogram( hists_["dRHcalN" ], muon->hcalIsoDeposit() );
    fillEnergyFlowHistogram( hists_["dRHcalPt"], muon->hcalIsoDeposit() );
    fillObjectFlowHistogram( hists_["dRTrkN"  ], muon->trackerIsoDeposit() );
    fillEnergyFlowHistogram( hists_["dRTrkPt" ], muon->trackerIsoDeposit() );

    // fill summed deposits
    double stdCone  = 0.3;
    double vetoCone = 0.1;
    hists_["isoEcalN" ]->Fill( muon->ecalIsoDeposit()->countWithin(stdCone), weight );
    hists_["isoHcalN" ]->Fill( muon->hcalIsoDeposit()->countWithin(stdCone), weight );
    hists_["isoTrkN"  ]->Fill( muon->trackerIsoDeposit()->countWithin(stdCone), weight );
    hists_["isoVetoPt"]->Fill( muon->ecalIsoDeposit()->countWithin(vetoCone)+muon->hcalIsoDeposit()->countWithin(vetoCone), weight );
    hists_["isoTrkPt" ]->Fill( muon->trackIso(), weight );
    hists_["isoCalPt" ]->Fill( muon->caloIso (), weight );

    // fill relative isolation
    hists_["isoRelComb"]->Fill( (muon->trackIso()+muon->caloIso())/muon->pt(), weight );
    hists_["isoRelPt"  ]->Fill(  muon->pt()/(muon->pt()+muon->trackIso()+muon->caloIso()), weight );
  }
}

/// everything which needs to be done after the event loop
void 
MuonKinematics::process()
{
  // normalize histograms to the number of muons, then went in
  hists_["dREcalPt"]->Scale( 1./norm_ );
  hists_["dREcalN" ]->Scale( 1./norm_ );
  hists_["dRHcalPt"]->Scale( 1./norm_ );
  hists_["dRHcalN" ]->Scale( 1./norm_ );
  hists_["dRTrkPt" ]->Scale( 1./norm_ );
  hists_["dRTrkN"  ]->Scale( 1./norm_ );
}
