#include "TopAnalysis/TopAnalyzer/interface/ElectronQuality.h"

/// default constructor for fw lite
ElectronQuality::ElectronQuality(const int index) : norm_(0.), index_(index)
{ 
}

/// constructor for full FW analyzer
ElectronQuality::ElectronQuality(const edm::ParameterSet& cfg) : norm_(0.), 
  index_( cfg.getParameter<int>( "index" ) )
{
}

/// histogramm booking for fwlite 
void 
ElectronQuality::book()
{
  /** 
      Selection Variables
  **/
  // number of valid hits in silicon tracker   
  hists_["nHit"            ] = new TH1F( "nHit"             ,  "nHit"             ,   35,  -0.5,  34.5 );
  // normalized chi2 of global electron track fit
  hists_["chi2"            ] = new TH1F( "chi2"             ,  "chi2"             ,   30,   0. ,  30.  );
  // d0 significance of track (still to nominal IP)
  hists_["d0"              ] = new TH1F( "d0"               ,  "d0"               ,   200,  0. ,  1.   );
  // energy in ecal attached to the candidate trajectory
  hists_["ecalEn"          ] = new TH1F( "ecalEn"           ,  "ecalEn"           ,   40,   0. ,  10.  );
  // energy in hcal attached to the candidate trajectory
  hists_["hcalEnOverEcalEn"] = new TH1F( "hcalEnOverEcalEn" ,  "hcalEnOverEcalEn" ,   40,   0. ,  10.  );
  // relative isolation (tracker and calo combined)
  hists_["relIso"          ] = new TH1F( "relIso"           ,  "relIso"           ,   50,   0. ,  1.0  );
  // the supercluster eta - track eta position at calo extrapolated from innermost track state
  hists_["deltaEtaIn"      ] = new TH1F( "deltaEtaIn"     ,    "deltaEtaIn"       ,   50,   0.,   0.2  );
  // the seed cluster phi - track phi position at calo extrapolated from the innermost track state
  hists_["deltaPhiIn"      ] = new TH1F( "deltaPhiIn"     ,    "deltaPhiIn"       ,   50,   0.,   0.4  );

}


/// histogramm booking for full fw
void 
ElectronQuality::book(edm::Service<TFileService>& fs)
{
  /** 
      Selection Variables
  **/
  // number of valid hits in silicon tracker
  hists_["nHit"     ]        = fs->make<TH1F>( "nHit"              ,  "nHit"               ,   35,  -0.5, 34.5 );
  // normalized chi2 of global electron track fit
  hists_["chi2"     ]        = fs->make<TH1F>( "chi2"              ,  "chi2"               ,   30,   0.,  30.  );
  // d0 significance of track (still to nominal IP)
  hists_["d0"       ]        = fs->make<TH1F>( "d0"                ,  "d0"                 ,   200,  0.,  1.   );
  // energy in ecal attached to the candidate trajectory
  hists_["ecalEn"   ]        = fs->make<TH1F>( "ecalEn"            ,  "ecalEn"             ,   40,   0.,  10.  );
  // energy in hcal attached to the candidate trajectory
  hists_["hcalEnOverEcalEn"] = fs->make<TH1F>( "hcalEnOverEcalEn"  ,  "hcalEnOverEcalEn"   ,   1000,  0.,  5.  );
  // relative isolation (tracker and calo combined)
  hists_["relIso"   ]        = fs->make<TH1F>( "relIso"            ,  "relIso"             ,   50,   0.,  1.0  );
  // the supercluster eta - track eta position at calo extrapolated from innermost track state
  hists_["deltaEtaIn"]       = fs->make<TH1F>( "deltaEtaIn"        ,  "deltaEtaIn"         ,   50,   0.,  0.2  );
  // the seed cluster phi - track phi position at calo extrapolated from the innermost track state
  hists_["deltaPhiIn"]       = fs->make<TH1F>( "deltaPhiIn"        ,  "deltaPhiIn"         ,   50,   0.,  0.4  );


  // conserve the normalization information (for the use with hadd)
  //  hists_["norm_"   ] = fs->make<TH1F>( "norm_"    ,  "norm_"    ,    1,   0.,   1. );
}



/// histogram filling for fwlite and for full fw from reco objects
void
ElectronQuality::fill(const edm::View<pat::Electron>& electrons, const double& weight)
{
  int index=0;
  for(edm::View<pat::Electron>::const_iterator electron=electrons.begin(); electron!=electrons.end(); ++electron, ++index){
      if( (index_<0 || index_==index) ){
      /**
	 Fill Selection Variables
      **/
      // number of valid hits in silicon tracker
      hists_.find("nHit")            ->second->Fill( electron->gsfTrack()->numberOfValidHits(), weight ); 
      // normalized chi2 of global electron track fit
      hists_.find("chi2")            ->second->Fill( electron->gsfTrack()->normalizedChi2(), weight ); 
      // d0 significance of track (still to nominal IP)
      hists_.find("d0"  )            ->second->Fill( electron->gsfTrack()->d0(), weight );
      // relative isolation (tracker and calo combined)
      hists_.find("relIso")          ->second->Fill( (electron->trackIso()+electron->caloIso())/electron->et() , weight );    
      // energy in ecal attached to the candidate trajectory
      hists_.find("ecalEn")          ->second->Fill( electron->ecalEnergy(), weight ); 
      // ratio of energy deposit in hcal and ecal
      hists_.find("hcalEnOverEcalEn")->second->Fill( electron->hcalOverEcal() , weight );
      // the supercluster eta - track eta position at calo extrapolated from innermost track state
      hists_.find("deltaEtaIn")      ->second->Fill(  electron->deltaEtaSuperClusterTrackAtVtx(), weight );
      // the seed cluster phi - track phi position at calo extrapolated from the innermost track state
      hists_.find("deltaPhiIn")      ->second->Fill(  electron->deltaPhiSuperClusterTrackAtVtx(), weight );    
    }
  }
}

/// everything which needs to be done after the event loop
void 
ElectronQuality::process()
{
  // fill normalization histogramwith the number of electrons, 
  // that went into the eflow histograms (weighted); we 
  // need this workaround to be able to normalize even 
  // after the use of hadd, when running in batch mode...
  //  hists_.find("norm_" )->second->SetBinContent( 1, norm_ );
}

/// get number of objects within a ring in deltaR corresponding to the bin width 
/// of the histogram 'hist' from 'deposit' and fill hist with it
void
ElectronQuality::objectFlow(TH1* hist, const pat::IsoDeposit* deposit)
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
ElectronQuality::energyFlow(TH1* hist, const pat::IsoDeposit* deposit)
{
  if(hist && deposit){
    for(int bin=1; bin<=hist->GetNbinsX(); ++bin){
      double lowerEdge = hist->GetBinLowEdge(bin);
      double upperEdge = hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
      // restrict the differential energy deposit to less than 10GeV
      // in order not to have too high weight in the plot
      if(deposit->depositWithin(upperEdge) - deposit->depositWithin(lowerEdge) < 10)
	hist->Fill(hist->GetBinCenter(bin), deposit->depositWithin(upperEdge) - deposit->depositWithin(lowerEdge));
    }
  }
}

/// get energy of objects within a ring in deltaR corresponding to the bin width 
/// of the histogram 'hist' from 'deposit' and fill hist with it
void
ElectronQuality::energyFlow(TH1* hist, const pat::IsoDeposit* ecalDeposit, const pat::IsoDeposit* hcalDeposit)
{
  if(hist && ecalDeposit && hcalDeposit){
    for(int bin=1; bin<=hist->GetNbinsX(); ++bin){
      double lowerEdge = hist->GetBinLowEdge(bin);
      double upperEdge = hist->GetBinLowEdge(bin)+hist->GetBinWidth(bin);
      hist->Fill(hist->GetBinCenter(bin), ecalDeposit->depositWithin(upperEdge)-ecalDeposit->depositWithin(lowerEdge) +  hcalDeposit->depositWithin(upperEdge)-hcalDeposit->depositWithin(lowerEdge) );
    }
  }
}
