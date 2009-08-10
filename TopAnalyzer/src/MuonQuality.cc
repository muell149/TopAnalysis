#include "TopAnalysis/TopAnalyzer/interface/MuonQuality.h"

/// default constructor for fw lite
MuonQuality::MuonQuality() : norm_(0.)
{ 
}

/// constructor for full FW analyzer
MuonQuality::MuonQuality(const edm::ParameterSet& cfg) : norm_(0.) 
{
}

/// histogramm booking for fwlite 
void 
MuonQuality::book()
{
  hists_["comp"     ] = new TH1F( "comp"      ,  "comp"      ,    50,    0.,    1. );
  hists_["em"       ] = new TH1F( "em"        ,  "em"        ,    50,    0.,    5. ); 
  hists_["emS9"     ] = new TH1F( "emS9"      ,  "emS9"      ,    50,    0.,    5. ); 
  hists_["had"      ] = new TH1F( "had"       ,  "had"       ,    50,    0.,    5. ); 
  hists_["hadS9"    ] = new TH1F( "hadS9"     ,  "hadS9"     ,    50,    0.,    5. );
  hists_["ho"       ] = new TH1F( "ho"        ,  "ho"        ,    50,    0.,    5. ); 
  hists_["hoS9"     ] = new TH1F( "hoS9"      ,  "hoS9"      ,    50,    0.,    5. );   
  hists_["isoTkN"   ] = new TH1F( "isoTkN"    ,  "isoTkN"    ,    20,    0.,   20. );
  hists_["isoTkPt"  ] = new TH1F( "isoTkPt"   ,  "isoTkPt"   ,    60,   -1.,    5. );
  hists_["isoEcN"   ] = new TH1F( "isoEcN"    ,  "isoEcN"    ,    30,    0.,   30. );
  hists_["isoHcN"   ] = new TH1F( "isoHcN"    ,  "isoHcN"    ,    30,    0.,   30. );
  hists_["isoCalPt" ] = new TH1F( "isoCalPt"  ,  "isoCalPt"  ,    40,  -10.,   30. );
  hists_["isoRelPt" ] = new TH1F( "isoRelPt"  ,  "isoRelPt"  ,    44,    0.,   1.1 );
  hists_["isoRelCmb"] = new TH1F( "isoRelCmb" ,  "isoRelCmb" ,    44,    0.,   1.1 );
  hists_["dRTkN"    ] = new TH1F( "dRTkN"     ,  "dRTkN"     ,    20,    0.,    1. );
  hists_["dRTkPt"   ] = new TH1F( "dRTkPt"    ,  "dRTkPt"    ,    20,    0.,    1. );
  hists_["dREcN"    ] = new TH1F( "dREcN"     ,  "dREcN"     ,    20,    0.,    1. );
  hists_["dREcPt"   ] = new TH1F( "dREcPt"    ,  "dREcPt"    ,    20,    0.,    1. );
  hists_["dRHcN"    ] = new TH1F( "dRHcN"     ,  "dRHcN"     ,    20,    0.,    1. );
  hists_["dRHcPt"   ] = new TH1F( "dRHcPt"    ,  "dRHcPt"    ,    20,    0.,    1. );
}

/// histogramm booking for full fw
void 
MuonQuality::book(edm::Service<TFileService>& fs)
{
  hists_["comp"     ] = fs->make<TH1F>( "comp"      ,  "comp"      ,    50,    0.,    1. );
  hists_["em"       ] = fs->make<TH1F>( "em"        ,  "em"        ,    50,    0.,    5. ); 
  hists_["emS9"     ] = fs->make<TH1F>( "emS9"      ,  "emS9"      ,    50,    0.,    5. ); 
  hists_["had"      ] = fs->make<TH1F>( "had"       ,  "had"       ,    50,    0.,    5. ); 
  hists_["hadS9"    ] = fs->make<TH1F>( "hadS9"     ,  "hadS9"     ,    50,    0.,    5. );
  hists_["ho"       ] = fs->make<TH1F>( "ho"        ,  "ho"        ,    50,    0.,    5. ); 
  hists_["hoS9"     ] = fs->make<TH1F>( "hoS9"      ,  "hoS9"      ,    50,    0.,    5. );   
  hists_["isoTkN"   ] = fs->make<TH1F>( "isoTkN"    ,  "isoTkN"    ,    20,    0.,   20. );
  hists_["isoTkPt"  ] = fs->make<TH1F>( "isoTkPt"   ,  "isoTkPt"   ,    60,   -1.,    5. );
  hists_["isoEcN"   ] = fs->make<TH1F>( "isoEcN"    ,  "isoEcN"    ,    30,    0.,   30. );
  hists_["isoHcN"   ] = fs->make<TH1F>( "isoHcN"    ,  "isoHcN"    ,    30,    0.,   30. );
  hists_["isoCalPt" ] = fs->make<TH1F>( "isoCalPt"  ,  "isoCalPt"  ,    40,  -10.,   30. );
  hists_["isoRelPt" ] = fs->make<TH1F>( "isoRelPt"  ,  "isoRelPt"  ,    44,    0.,   1.1 );
  hists_["isoRelCmb"] = fs->make<TH1F>( "isoRelCmb" ,  "isoRelCmb" ,    44,    0.,   1.1 );
  hists_["dRTkN"    ] = fs->make<TH1F>( "dRTkN"     ,  "dRTkN"     ,    20,    0.,    1. );
  hists_["dRTkPt"   ] = fs->make<TH1F>( "dRTkPt"    ,  "dRTkPt"    ,    20,    0.,    1. );
  hists_["dREcN"    ] = fs->make<TH1F>( "dREcN"     ,  "dREcN"     ,    20,    0.,    1. );
  hists_["dREcPt"   ] = fs->make<TH1F>( "dREcPt"    ,  "dREcPt"    ,    20,    0.,    1. );
  hists_["dRHcN"    ] = fs->make<TH1F>( "dRHcN"     ,  "dRHcN"     ,    20,    0.,    1. );
  hists_["dRHcPt"   ] = fs->make<TH1F>( "dRHcPt"    ,  "dRHcPt"    ,    20,    0.,    1. );
}

/// histogram filling for fwlite and for full fw from reco objects
void
MuonQuality::fill(const std::vector<pat::Muon>& muons, const double& weight)
{
  std::vector<pat::Muon>::const_iterator muon=muons.begin();
  if(muon!=muons.end()){
    reco::MuonEnergy muEnergy = muon->calEnergy();   
    hists_.find( "comp" )->second->Fill( muon->caloCompatibility(), weight );
    hists_.find( "em"   )->second->Fill( muEnergy.em    , weight );
    hists_.find( "emS9" )->second->Fill( muEnergy.emS9  , weight );  
    hists_.find( "had"  )->second->Fill( muEnergy.had   , weight );
    hists_.find( "hadS9")->second->Fill( muEnergy.hadS9 , weight );  
    hists_.find( "ho"   )->second->Fill( muEnergy.ho    , weight );
    hists_.find( "hoS9" )->second->Fill( muEnergy.hoS9  , weight );  

    // fill enegry flow and object flow histograms
    norm_+=weight;
    objectFlow( hists_.find( "dREcN"  )->second , muon->ecalIsoDeposit()    );
    objectFlow( hists_.find( "dRHcN"  )->second , muon->hcalIsoDeposit()    );
    objectFlow( hists_.find( "dRTkN"  )->second , muon->trackerIsoDeposit() );
    energyFlow( hists_.find( "dREcPt" )->second , muon->ecalIsoDeposit()    );
    energyFlow( hists_.find( "dRHcPt" )->second , muon->hcalIsoDeposit()    );
    energyFlow( hists_.find( "dRTkPt" )->second , muon->trackerIsoDeposit() );

    // fill summed up deposits
    double stdCone  = 0.3;
    hists_.find( "isoEcN"   )->second->Fill( muon->ecalIsoDeposit()->countWithin(stdCone)    , weight );
    hists_.find( "isoHcN"   )->second->Fill( muon->hcalIsoDeposit()->countWithin(stdCone)    , weight );
    hists_.find( "isoTkN"   )->second->Fill( muon->trackerIsoDeposit()->countWithin(stdCone) , weight );
    hists_.find( "isoTkPt"  )->second->Fill( muon->trackIso() , weight );
    hists_.find( "isoCalPt" )->second->Fill( muon->caloIso () , weight );

    // fill relative isolation
    hists_.find("isoRelComb")->second->Fill( (muon->trackIso()+muon->caloIso())/muon->pt()            , weight );
    hists_.find("isoRelPt"  )->second->Fill( muon->pt()/(muon->pt()+muon->trackIso()+muon->caloIso()) , weight );
  }
}

/// everything which needs to be done after the event loop
void 
MuonQuality::process()
{
  // normalize histograms to the number of muons, that went in (weighted)
  hists_.find( "dREcN"  )->second->Scale( 1./norm_ );
  hists_.find( "dRHcN"  )->second->Scale( 1./norm_ );
  hists_.find( "dRTkN"  )->second->Scale( 1./norm_ );
  hists_.find( "dREcPt" )->second->Scale( 1./norm_ );
  hists_.find( "dRHcPt" )->second->Scale( 1./norm_ );
  hists_.find( "dRTkPt" )->second->Scale( 1./norm_ );
}

/// get number of objects within a ring in deltaR corresponding to the bin width 
/// of the histogram 'hist' from 'deposit' and fill hist with it
void
MuonQuality::objectFlow(TH1F* hist, const pat::IsoDeposit* deposit)
{
  if(hist && deposit){
    for(int bin=1; bin<=hist->GetNbinsX(); ++bin){
      double lowerEdge = hist->GetBinLowEdge(bin);
      double upperEdge = hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
      hist->Fill(hist->GetBinCenter(bin), deposit->countWithin(upperEdge) - deposit->countWithin(lowerEdge));
    }
  }
}

/// get energy of objects within a ring in deltaR corresponding to the bin width 
/// of the histogram 'hist' from 'deposit' and fill hist with it
void
MuonQuality::energyFlow(TH1F* hist, const pat::IsoDeposit* deposit)
{
  if(hist && deposit){
    for(int bin=1; bin<=hist->GetNbinsX(); ++bin){
      double lowerEdge = hist->GetBinLowEdge(bin);
      double upperEdge = hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
      hist->Fill(hist->GetBinCenter(bin), deposit->depositWithin(upperEdge) - deposit->depositWithin(lowerEdge));
    }
  }
}
