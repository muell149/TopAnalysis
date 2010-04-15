#include "TopAnalysis/TopAnalyzer/interface/PtHat.h"

/// default constructor for generator level analysis in fw lite
PtHat::PtHat()
{
}

/// default constructor for full fw
PtHat::PtHat(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void PtHat::book()
{
  hists_["ptHat"] = new TH1F( "ptHat" , "ptHat" , 3000, 0. , 3000. );
}

/// histogramm booking for fw
void PtHat::book(edm::Service<TFileService>& fs)
{
  hists_["ptHat"] = fs->make<TH1F>( "ptHat" , "ptHat" , 3000, 0. , 3000. );
}


/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
PtHat::fill(const GenEventInfoProduct& genEventInfoProduct, const double& weight)
{
  if( genEventInfoProduct.hasBinningValues() ){
    if( genEventInfoProduct.binningValues().size() > 0 ){
      hists_.find("ptHat")->second->Fill( genEventInfoProduct.binningValues()[0] , weight );
    }
  }
}
