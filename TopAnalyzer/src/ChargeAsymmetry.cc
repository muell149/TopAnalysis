#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TopAnalysis/TopAnalyzer/interface/ChargeAsymmetry.h"
#include <iostream>

/// default constructor for generator level analysis in fw lite
ChargeAsymmetry::ChargeAsymmetry(int index, int lepton) : index_(index),  lepton_(lepton)
{
}

/// default constructor for full fw
ChargeAsymmetry::ChargeAsymmetry(const edm::ParameterSet& cfg) :
  index_( cfg.getParameter<int>( "index" ) ), lepton_( cfg.getParameter<int>( "lepton" ) )
{
}

/// histogramm booking for fwlite 
void ChargeAsymmetry::book()
{
  /** 
      Lepton histos, same variable and binning as in MuonCrossSection module
  **/
  // lepton pt
  hists_["pt"    ] = new TH1F( "pt"       , "pt"        ,   6, chargeAsymmetry::leptonPt );
  // lepton charge
  hists_["charge"] = new TH1F( "charge"   , "charge"    ,   2 ,    -1.     ,     1.      );
  // positive charged lepton pt
  hists_["ptp"   ] = new TH1F( "ptPlus"   , "pt(lep+)"  ,   6, chargeAsymmetry::leptonPt );
  // negative charged lepton pt
  hists_["ptm"   ] = new TH1F( "ptMinus"  , "pt(lep-)"  ,   6, chargeAsymmetry::leptonPt );
}

/// histogramm booking for full fw
void ChargeAsymmetry::book(edm::Service<TFileService>& fs)
{
   /** 
      Lepton histos, same variable and binning as in MuonCrossSection module
  **/
  // lepton pt
  hists_["pt"    ] = fs->make<TH1F>( "pt"       , "pt"        ,   6, chargeAsymmetry::leptonPt );
  // lepton charge
  hists_["charge"] = fs->make<TH1F>( "charge"   , "charge"    ,   2 ,    -1.     ,     1.      );
  // positive charged lepton pt
  hists_["ptp"   ] = fs->make<TH1F>( "ptPlus"   , "pt(lep+)"  ,   6, chargeAsymmetry::leptonPt );
  // negative charged lepton pt
  hists_["ptm"   ] = fs->make<TH1F>( "ptMinus"  , "pt(lep-)"  ,   6, chargeAsymmetry::leptonPt );
}

/// histogram filling with fwlite or full framework
void
ChargeAsymmetry::fill(const edm::View<reco::GenParticle>& leptons, const double& weight)
{
  // index for the leading, 2. leading, 3. leading lepton to be compared with index_
  // from the module config where index_=-1 means 'fill all leptons' and index_=n
  // n>=-1 means 'fill only n-th leading lepton'
  int index=0;
  for(edm::View<reco::GenParticle>::const_iterator lep=leptons.begin(); lep!=leptons.end(); ++lep, ++index){
    if( index_<0 || index_==index ){
      if(abs(lep->pdgId())==lepton_ || (lepton_ <0 && (abs(lep->pdgId())==11 || abs(lep->pdgId())==13 || abs(lep->pdgId())==15) ) ){
	// make sure charge is of abs value 1
	float charge=lep->charge();
	if(lep->charge()!=0){
	  charge=(float)lep->charge()/(float)abs(lep->charge());
	}
	else{
	  std::string exception;
	  exception += "-----------------------------------------------------------\n";
	  exception += "charge of objects is equal 0! Division will not be done.   \n";
	  exception += "This should not be the case because this module is ought   \n";
	  exception += "to deal with leptons                                       \n";
	  exception += "-----------------------------------------------------------\n";
	  throw edm::Exception(edm::errors::Configuration, exception);
	}
	// transverse momentum of the chosen lepton
	fill( "pt"    ,  lep->et()  , weight );
	// fill charge distribution of chosen lepton
	fill( "charge",  0.5*charge , weight );
	// fill histograms for charged leptons
	fill( charged(std::string("pt"),  charge),  lep->et()  , weight );
      }
    }
  }
}
