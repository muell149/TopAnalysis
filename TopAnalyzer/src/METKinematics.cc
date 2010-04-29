#include "TopAnalysis/TopAnalyzer/interface/METKinematics.h"

/// default constructor for fwlite
METKinematics::METKinematics()
{
}

/// default constructor for fwfull
METKinematics::METKinematics(const edm::ParameterSet& cfg)
{ 
}

/// histogramm booking for fwlite 
void METKinematics::book()
{
  // et of missing Et
  hists_["metEt"   ] = new TH1F( "met.et"    , "met.et"    ,  400 ,  0.  , 400. );
  // px of missing Et
  hists_["metPx"   ] = new TH1F( "met.px"    , "met.px"    ,  500 , -250., 250. );
  // py of missing Et
  hists_["metPy"   ] = new TH1F( "met.py"    , "met.py"    ,  500 , -250., 250. );
  // scalar sum of transverse energy over all objects
  hists_["metSumEt"] = new TH1F( "met.sumEt" , "met.sumEt" ,  1500,  0.  , 1500.);
  // significance of missing Et
  hists_["metSig"  ] = new TH1F( "met.sig"   , "met.sig"   ,  100 ,  0.  , 25.  );
  // phi of missing Et events
  hists_["metPhi"  ] = new TH1F( "met.phi"   , "met.phi"   ,  70  , -3.5 , 3.5  );
}


/// histogramm booking for fwfull
void METKinematics::book(edm::Service<TFileService>& fs)
{
  // et of missing Et
  hists_["metEt"   ] = fs->make<TH1F>("met.et"    , "met.et"    , 400 ,  0.   , 400. );
  // px of missing Et
  hists_["metPx"   ] = fs->make<TH1F>("met.px"    , "met.px"    , 500 , -250. , 250. );
  // py of missing Et
  hists_["metPy"   ] = fs->make<TH1F>("met.py"    , "met.py"    , 500 , -250. , 250. );
  // scalar sum of transverse energy over all objects
  hists_["metSumEt"] = fs->make<TH1F>("met.sumEt" , "met.sumEt" , 1500,  0.   , 1500.); 
  // significance of missing Et
  hists_["metSig"  ] = fs->make<TH1F>("met.sig"   , "met.sig"   , 100 ,  0.   , 25.  ); 
  // phi of missing Et events
  hists_["metPhi"  ] = fs->make<TH1F>("met.phi"   , "met.phi"   , 70  , -3.5  , 3.5  );
}

/// histogram filling for fw lite and for fw full
void
METKinematics::fill(const edm::View<reco::MET>& met, const double& weight)
{
  // filling for et transversal missing Et
  hists_.find("metEt"   )->second->Fill( met.begin()->et()    , weight);
  // filling for px of missing Et
  hists_.find("metPx"   )->second->Fill( met.begin()->px()    , weight);
  // filling for py of missing Et
  hists_.find("metPy"   )->second->Fill( met.begin()->py()    , weight);
  // filling for scalar sum of transverse energy over all objects (sum of absolute values)
  hists_.find("metSumEt")->second->Fill( met.begin()->sumEt() , weight);
  // filling for significance of missing Et
  // MET Significance = MET / sqrt(SumET)
  hists_.find("metSig"  )->second->Fill( met.begin()->mEtSig() , weight);
  // filling for phi of missing Et
  hists_.find("metPhi"  )->second->Fill( met.begin()->phi()   , weight);

}

void
METKinematics::process() 
{
}
