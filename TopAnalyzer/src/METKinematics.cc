#include "TopAnalysis/TopAnalyzer/interface/METKinematics.h"

/// default constructor for fwlite
METKinematics::METKinematics()
{
  tree = 0;
}

/// default constructor for fwfull
METKinematics::METKinematics(const edm::ParameterSet& cfg) :
  useTree_( cfg.getParameter<bool>( "useTree" ) )
{
  if(cfg.exists("index")) index_ = cfg.getParameter<int>( "index" );

  tree = 0;
}

/// histogramm booking for fwlite 
void METKinematics::book()
{
  /** 
      MET Variables
  **/
  // et of missing Et
  hists_["metEt"   ] = new TH1F( "met.et"    , "met.et"    ,  400 ,  0.   , 400. );
  // px of missing Et
  hists_["metPx"   ] = new TH1F( "met.px"    , "met.px"    ,  500 , -250. , 250. );
  // py of missing Et
  hists_["metPy"   ] = new TH1F( "met.py"    , "met.py"    ,  500 , -250. , 250. );
  // scalar sum of transverse energy over all objects
  hists_["metSumEt"] = new TH1F( "met.sumEt" , "met.sumEt" ,  1500,  0.   , 1500.);
  // significance of missing Et
  hists_["metSig"  ] = new TH1F( "met.sig"   , "met.sig"   ,  100 ,  0.   , 25.  );
  // phi of missing Et events
  hists_["metPhi"  ] = new TH1F( "met.phi"   , "met.phi"   ,  70  , -M_PI , M_PI  );
  // missing Et vs. sumEt
  hists2D_["metSumEt"] = new TH2F("metSumEt" , "metSumEt"  ,  1500,    0. ,  1500.,  400, 0.,  400.);

  /** 
      correlation MET - Kinematic quantities
  **/
  // gen-rec level correlation muon pt
  hists2D_["METpt_" ] = new TH2F( "METpt_"   , "METpt_"    ,  400,     0. ,   400.,  400,  0.,  400.);
  // gen-rec level correlation muon eta
  hists2D_["METeta_"] = new TH2F( "METeta_"  , "METeta_"   ,  800,    -4. ,     4.,  400,  0.,  400.);
  // gen-rec level correlation muon phi
  hists2D_["METphi_"] = new TH2F( "METphi_"  , "METphi_"   ,  628,  -M_PI ,   M_PI,  400,  0.,  400.);

}


/// histogramm booking for fwfull
void METKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      MET Variables
  **/
  // et of missing Et
  bookVariable( fs, "metEt"   , 400 ,  0.    , 400. , useTree_ );
  // px of missing Et
  bookVariable( fs, "metPx"   , 500 , -250.  , 250. , useTree_ );
  // py of missing Et
  bookVariable( fs, "metPy"   , 500 , -250.  , 250. , useTree_ );
  // scalar sum of transverse energy over all objects
  bookVariable( fs, "metSumEt", 1500,  0.    , 1500., useTree_ ); 
  // significance of missing Et
  bookVariable( fs, "metSig"  , 100 ,  0.    , 25.  , useTree_ ); 
  // phi of missing Et events
  bookVariable( fs, "metPhi"  , 70  , -M_PI  , M_PI  , useTree_ );
  // missing Et vs. sumEt
  if(!useTree_) bookVariable( fs, "metSumEt", 1500, 0. , 1500., 400, 0., 400. );

  /** 
      correlation MET - Kinematic quantities
  **/
  // gen-rec level correlation muon pt
  bookVariable( fs, "METpt_" , 400,    0. , 400., 400, 0., 400. );
  // gen-rec level correlation muon eta
  bookVariable( fs, "METeta_", 800,   -4. ,   4., 400, 0., 400. );
  // gen-rec level correlation muon phi
  bookVariable( fs, "METphi_", 628, -M_PI , M_PI, 400, 0., 400. );
}

/// histogram filling for fw lite and for fw full
void
METKinematics::fill(const edm::View<reco::MET>& met, const double& weight)
{
  // filling for et transversal missing Et
  fillValue("metEt"   , met.begin()->et()    , weight );
  // filling for px of missing Et
  fillValue("metPx"   , met.begin()->px()    , weight );
  // filling for py of missing Et
  fillValue("metPy"   , met.begin()->py()    , weight );
  // filling for scalar sum of transverse energy over all objects (sum of absolute values)
  fillValue("metSumEt", met.begin()->sumEt() , weight );
  // filling for significance of missing Et
  // MET Significance = MET / sqrt(SumET)
  fillValue("metSig"  , met.begin()->mEtSig(), weight );
  // filling for phi of missing Et
  fillValue("metPhi"  , met.begin()->phi()   , weight );
  // filling missing Et vs. sumEt
  if(!useTree_) fillValue("metSumEt", met.begin()->sumEt(), met.begin()->et(), weight );

  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();

}

/// histogram filling with fwlite or full framework
void
METKinematics::fill(const edm::View<reco::MET>& metCollection, const edm::View<reco::Candidate>& particleCollection, const double& weight)
{
  int index=0;
  //  int index_=0;
  for(edm::View<reco::Candidate>::const_iterator part= particleCollection.begin(); part!= particleCollection.end(); ++part, ++index){
    // transverse momentum of the muon
    if(index==index_ || index_<0){
      fillValue("METpt_"  , part->pt()  ,  metCollection.begin()->et() , weight );
      // pseudorapidity of the muon
      fillValue("METeta_" , part->eta() ,  metCollection.begin()->et() , weight );
      // azimuth angle of the muon
      fillValue("METphi_" , part->phi() ,  metCollection.begin()->et() , weight );
    }
  }
  // fill 1-dimensional MET histograms from metCollection input
  fill(metCollection, weight);
}


void
METKinematics::process() 
{
}
