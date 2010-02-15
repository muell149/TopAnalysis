#include "TopAnalysis/TopAnalyzer/interface/EventShapes.h"

/// default constructor for fw lite
EventShapes::EventShapes(const std::string& correctionLevel) : correctionLevel_(correctionLevel)
{
}

/// default constructor for fwfull
EventShapes::EventShapes(const edm::ParameterSet& cfg) :
  correctionLevel_( cfg.getParameter<std::string>( "correctionLevel" ) )
{
}

/// histogramm booking for fwlite 
void
EventShapes::book()
{
  /** 
      Event Shape Variables
  **/

  /// the return value is 1 for spherical events and 0 for events linear in r-phi. This function 
  /// needs the number of steps to determine how fine the granularity of the algorithm in phi 
  /// should be
  hists_["isotropy"   ] = new TH1F( "isotropy"    , "isotropy"    ,  100 , 0. ,  1. );
  /// the return value is 1 for spherical and 0 linear events in r-phi. This function needs the 
  /// number of steps to determine how fine the granularity of the algorithm in phi should be
  hists_["circularity"] = new TH1F( "circularity" , "circularity" ,  100 , 0. ,  1. );
  /// 1.5*(q1+q2) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 1 for spherical, 3/4 for 
  /// plane and 0 for linear events
  hists_["sphericity" ] = new TH1F( "sphericity"  , "sphericity"  ,  100 , 0. ,  1. );
  /// 1.5*q1 where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 0.5 for spherical and 0 
  /// for plane and linear events
  hists_["aplanarity" ] = new TH1F( "aplanarity"  , "aplanarity"  ,  50 , 0. ,  0.5 );
  /// 3.*(q1*q2+q1*q3+q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
  /// and measures the 3-jet structure of the event (C vanishes for a "perfect" 2-jet event)
  hists_["C"]           = new TH1F( "C"           , "C"           ,  100 , 0. ,  1. );
  /// 27.*(q1*q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
  /// and measures the 4-jet structure of the event (D vanishes for a planar event)
  hists_["D"]           = new TH1F( "D"           , "D"           ,  100 , 0. ,  1. );
}

/// histogramm booking for full fw
void
EventShapes::book(edm::Service<TFileService>& fs)
{
  /** 
      Event Shape Variables
  **/

  /// the return value is 1 for spherical events and 0 for events linear in r-phi. This function 
  /// needs the number of steps to determine how fine the granularity of the algorithm in phi 
  /// should be
  hists_["isotropy"] = fs->make<TH1F>( "isotropy" , "isotropy" ,  100 , 0. ,  1. );

  /// the return value is 1 for spherical and 0 linear events in r-phi. This function needs the 
  /// number of steps to determine how fine the granularity of the algorithm in phi should be
  hists_["circularity"] = fs->make<TH1F>( "circularity" , "circularity" ,  100 , 0. ,  1. );

  /// 1.5*(q1+q2) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 1 for spherical, 3/4 for 
  /// plane and 0 for linear events
  hists_["sphericity"] = fs->make<TH1F>( "sphericity" , "sphericity" ,  100 , 0. ,  1. );

  /// 1.5*q1 where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 0.5 for spherical and 0 
  /// for plane and linear events
  hists_["aplanarity"] = fs->make<TH1F>( "aplanarity" , "aplanarity" ,  50 , 0. ,  0.5 );

  /// 3.*(q1*q2+q1*q3+q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
  /// and measures the 3-jet structure of the event (C vanishes for a "perfect" 2-jet event)
  hists_["C"]  = fs->make<TH1F>( "C" , "C",  100 , 0. ,  1. );

  /// 27.*(q1*q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
  /// and measures the 4-jet structure of the event (D vanishes for a planar event)
  hists_["D"] = fs->make<TH1F>( "D" , "D" ,  100 , 0. ,  1. );

  /** 
      Correlations of Event Shape Variables
  **/

  hists2D_["iso_cir"] = fs->make<TH2F>( "iso_cir" , "iso_cir" ,  100 , 0. ,  1. , 100 , 0. , 1. );
  hists2D_["iso_sph"] = fs->make<TH2F>( "iso_sph" , "iso_sph" ,  100 , 0. ,  1. , 100 , 0. , 1. );
  hists2D_["iso_apl"] = fs->make<TH2F>( "iso_apl" , "iso_apl" ,  100 , 0. ,  1. , 50 , 0. , 0.5 );
  hists2D_["iso_c"  ] = fs->make<TH2F>( "iso_c"   , "iso_c"   ,  100 , 0. ,  1. , 100 , 0. , 1. );
  hists2D_["iso_d"  ] = fs->make<TH2F>( "iso_d"   , "iso_d"   ,  100 , 0. ,  1. , 100 , 0. , 1. );
  hists2D_["cir_sph"] = fs->make<TH2F>( "cir_sph" , "cir_sph" ,  100 , 0. ,  1. , 100 , 0. , 1. );
  hists2D_["cir_apl"] = fs->make<TH2F>( "cir_apl" , "cir_apl" ,  100 , 0. ,  1. , 50 , 0. , 0.5 );
  hists2D_["cir_c"  ] = fs->make<TH2F>( "cir_c"   , "cir_c"   ,  100 , 0. ,  1. , 100 , 0. , 1. );
  hists2D_["cir_d"  ] = fs->make<TH2F>( "cir_d"   , "cir_d"   ,  100 , 0. ,  1. , 100 , 0. , 1. );
  hists2D_["sph_apl"] = fs->make<TH2F>( "sph_apl" , "sph_apl" ,  100 , 0. ,  1. , 50 , 0. , 0.5 );
  hists2D_["sph_c"  ] = fs->make<TH2F>( "sph_c"   , "sph_c"   ,  100 , 0. ,  1. , 100 , 0. , 1. );
  hists2D_["sph_d"  ] = fs->make<TH2F>( "sph_d"   , "sph_d"   ,  100 , 0. ,  1. , 100 , 0. , 1. );
  hists2D_["apl_c"  ] = fs->make<TH2F>( "apl_c"   , "apl_c"   ,  50 , 0. ,  0.5 , 100 , 0. , 1. );
  hists2D_["apl_d"  ] = fs->make<TH2F>( "apl_d"   , "apl_d"   ,  50 , 0. ,  0.5 , 100 , 0. , 1. );
  hists2D_["c_d"    ] = fs->make<TH2F>( "c_d"     , "c_d"     ,  100 , 0. ,  1. , 100 , 0. , 1. );

}

std::vector<math::XYZVector> makeVecForEventShape(edm::View<reco::Candidate> jets, double scale = 1.) {
  std::vector<math::XYZVector> p;
  unsigned int i=1;
  for (edm::View<reco::Candidate>::const_iterator jet = jets.begin(); jet != jets.end(); jet++) {
    math::XYZVector Vjet(jet->px() * scale, jet->py() * scale, jet->pz() * scale);
    p.push_back(Vjet);
    ++i;
    if(i==6) break;
  }
  return p;
}


/// histogram filling for fwlite and for full fw
void
EventShapes::fill(const edm::View<reco::Candidate>& jets, const double& weight)
{
  /**
     Calculate Event Shape Variables
  **/

  EventShapeVariables eventshape(makeVecForEventShape(jets));

  double aplanarity_  = eventshape.aplanarity();
  double sphericity_  = eventshape.sphericity();
  double circularity_ = eventshape.circularity();
  double isotropy_    = eventshape.isotropy();
  double C_           = eventshape.C();
  double D_           = eventshape.D();

  /** 
      Fill Event Shape Variables
  **/

  // aplanarity of event
  hists_.find("aplanarity"  )->second->Fill( aplanarity_  , weight );
  // sphericity of event
  hists_.find("sphericity"  )->second->Fill( sphericity_  , weight );
  // circularity of event
  hists_.find("circularity" )->second->Fill( circularity_ , weight );
  // isotropy of event
  hists_.find("isotropy"    )->second->Fill( isotropy_    , weight );
  // C of event
  hists_.find("C"           )->second->Fill( C_           , weight );
  // D of event
  hists_.find("D"           )->second->Fill( D_           , weight );

  hists2D_.find("iso_cir")->second->Fill( isotropy_    , circularity_ , weight );
  hists2D_.find("iso_sph")->second->Fill( isotropy_    , sphericity_  , weight );
  hists2D_.find("iso_apl")->second->Fill( isotropy_    , aplanarity_  , weight );
  hists2D_.find("iso_c"  )->second->Fill( isotropy_    , C_           , weight );
  hists2D_.find("iso_d"  )->second->Fill( isotropy_    , D_           , weight );
  hists2D_.find("cir_sph")->second->Fill( circularity_ , sphericity_  , weight );
  hists2D_.find("cir_apl")->second->Fill( circularity_ , aplanarity_  , weight );
  hists2D_.find("cir_c"  )->second->Fill( circularity_ , C_           , weight );
  hists2D_.find("cir_d"  )->second->Fill( circularity_ , D_           , weight );
  hists2D_.find("sph_apl")->second->Fill( sphericity_  , aplanarity_  , weight );
  hists2D_.find("sph_c"  )->second->Fill( sphericity_  , C_           , weight );
  hists2D_.find("sph_d"  )->second->Fill( sphericity_  , D_           , weight );
  hists2D_.find("apl_c"  )->second->Fill( aplanarity_  , C_           , weight );
  hists2D_.find("apl_d"  )->second->Fill( aplanarity_  , D_           , weight );
  hists2D_.find("c_d"    )->second->Fill( C_           , D_           , weight );
}

/// return the desired correction step from the configuration string, which is expected to be of type 'step' or 'step:flavor'
const std::string EventShapes::correctionStep() const
{
  std::string step;
  if(correctionLevel_.find(":")!=std::string::npos){
    step=correctionLevel_.substr(0,correctionLevel_.find(":"));
  }
  else{
    step=correctionLevel_;
  }
  return step;
}

/// return the desired correction flavor from the configuration string, which is expected to be of type 'step' or 'step:flavor'
const std::string EventShapes::correctionFlavor() const
{
  std::string flavor;
  if(correctionLevel_.find(":")!=std::string::npos){
    flavor=correctionLevel_.substr(1+correctionLevel_.find(":"));
  }
  return flavor;
}
