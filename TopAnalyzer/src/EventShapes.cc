#include "TopAnalysis/TopAnalyzer/interface/EventShapes.h"

/// default constructor for fw lite
EventShapes::EventShapes()
{
  tree = 0;
}

/// default constructor for fwfull
EventShapes::EventShapes(const edm::ParameterSet& cfg):
  useTree_ ( cfg.getParameter<bool>( "useTree" ) )
{
  tree = 0;
}

/// histogramm booking for fwlite 
void
EventShapes::book()
{
  /** 
      Add needed histogramms from full fw list of histogramms
  **/
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
  bookVariable( fs, "isotropy" , 100,  0. , 1. , useTree_ );

  /// the return value is 1 for spherical and 0 linear events in r-phi. This function needs the 
  /// number of steps to determine how fine the granularity of the algorithm in phi should be
  bookVariable( fs, "circularity" , 100,  0. , 1. , useTree_ );

  /// 1.5*(q1+q2) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 1 for spherical, 3/4 for 
  /// plane and 0 for linear events
  bookVariable( fs, "sphericity" , 100,  0. , 1. , useTree_ );

  /// 1.5*q1 where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 0.5 for spherical and 0 
  /// for plane and linear events
  bookVariable( fs, "aplanarity" ,  50,  0. , 0.5 , useTree_ );

  /// 3.*(q1*q2+q1*q3+q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
  /// and measures the 3-jet structure of the event (C vanishes for a "perfect" 2-jet event)
  bookVariable( fs, "C" ,  100,  0. , 1. , useTree_ );

  /// 27.*(q1*q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
  /// and measures the 4-jet structure of the event (D vanishes for a planar event)
  bookVariable( fs, "D" ,  100,  0. , 1. , useTree_ );

  /** 
      Correlations of Event Shape Variables
  **/

  if(!useTree_){
    bookVariable( fs, "iso_cir" ,  100,  0. , 1.  , 100 , 0. , 1.  );
    bookVariable( fs, "iso_sph" ,  100,  0. , 1.  , 100 , 0. , 1.  );
    bookVariable( fs, "iso_apl" ,  100,  0. , 1.  ,  50 , 0. , 0.5 );
    bookVariable( fs, "iso_c"   ,  100,  0. , 1.  , 100 , 0. , 1.  );
    bookVariable( fs, "iso_d"   ,  100,  0. , 1.  , 100 , 0. , 1.  );
    bookVariable( fs, "cir_sph" ,  100,  0. , 1.  , 100 , 0. , 1.  );
    bookVariable( fs, "cir_apl" ,  100,  0. , 1.  ,  50 , 0. , 0.5 );
    bookVariable( fs, "cir_c"   ,  100,  0. , 1.  , 100 , 0. , 1.  );
    bookVariable( fs, "cir_d"   ,  100,  0. , 1.  , 100 , 0. , 1.  );
    bookVariable( fs, "sph_apl" ,  100,  0. , 1.  ,  50 , 0. , 0.5 );
    bookVariable( fs, "sph_c"   ,  100,  0. , 1.  , 100 , 0. , 1.  );
    bookVariable( fs, "sph_d"   ,  100,  0. , 1.  , 100 , 0. , 1.  );
    bookVariable( fs, "apl_c"   ,   50,  0. , 0.5 , 100 , 0. , 1.  );
    bookVariable( fs, "apl_d"   ,   50,  0. , 0.5 , 100 , 0. , 1.  );
    bookVariable( fs, "c_d"     ,  100,  0. , 1.  , 100 , 0. , 1.  );
  }

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
  fillValue("aplanarity" , aplanarity_ , weight);
  // sphericity of event
  fillValue("sphericity" , sphericity_ , weight);
  // circularity of event
  fillValue("circularity", circularity_, weight);
  // isotropy of event
  fillValue("isotropy"   , isotropy_   , weight);
  // C of event
  fillValue("C"          , C_          , weight);
  // D of event
  fillValue("D"          , D_          , weight);

  if(!useTree_){
    fillValue("iso_cir" , isotropy_    , circularity_ , weight);
    fillValue("iso_sph" , isotropy_    , sphericity_  , weight);
    fillValue("iso_apl" , isotropy_    , aplanarity_  , weight);
    fillValue("iso_c"   , isotropy_    , C_           , weight);
    fillValue("iso_d"   , isotropy_    , D_           , weight);
    fillValue("cir_sph" , circularity_ , sphericity_  , weight);
    fillValue("cir_apl" , circularity_ , aplanarity_  , weight);
    fillValue("cir_c"   , circularity_ , C_           , weight);
    fillValue("cir_d"   , circularity_ , D_           , weight);
    fillValue("sph_apl" , sphericity_  , aplanarity_  , weight);
    fillValue("sph_c"   , sphericity_  , C_           , weight);
    fillValue("sph_d"   , sphericity_  , D_           , weight);
    fillValue("apl_c"   , aplanarity_  , C_           , weight);
    fillValue("apl_d"   , aplanarity_  , D_           , weight);
    fillValue("c_d"     , C_           , D_           , weight);
  }

  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();

}
