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
  hists_["aplanarity" ] = new TH1F( "aplanarity"  , "aplanarity"  ,  100 , 0. ,  1. );
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
  hists_["isotropy"] = fs->make<TH1F>( "isotropy" , "isotropy" ,  100 , -5. ,  5. );

  /// the return value is 1 for spherical and 0 linear events in r-phi. This function needs the 
  /// number of steps to determine how fine the granularity of the algorithm in phi should be
  hists_["circularity"] = fs->make<TH1F>( "circularity" , "circularity" ,  100 , -5. ,  5. );

  /// 1.5*(q1+q2) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 1 for spherical, 3/4 for 
  /// plane and 0 for linear events
  hists_["sphericity"] = fs->make<TH1F>( "sphericity" , "sphericity" ,  100 , -5. ,  5. );

  /// 1.5*q1 where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 0.5 for spherical and 0 
  /// for plane and linear events
  hists_["aplanarity"] = fs->make<TH1F>( "aplanarity" , "aplanarity" ,  100 , -5. ,  5. );

  /// 3.*(q1*q2+q1*q3+q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
  /// and measures the 3-jet structure of the event (C vanishes for a "perfect" 2-jet event)
  hists_["C"]  = fs->make<TH1F>( "C" , "C",  100 , -5. ,  5. );

  /// 27.*(q1*q2*q3) where 0<=q1<=q2<=q3 are the eigenvalues of the momemtum tensor 
  /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
  /// and measures the 4-jet structure of the event (D vanishes for a planar event)
  hists_["D"] = fs->make<TH1F>( "D" , "D" ,  100 , -5. ,  5. );

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

// /// histogram filling for fwlite and for full fw
// void
// EventShapes::fill(const edm::View<reco::Candidate>& jets, const double& weight)
// {
//   /**
//      Calculate Event Shape Variables
//   **/

//   EventShapeVariables eventshape(makeVecForEventShape(jets));

//   double aplanarity_  = eventshape.aplanarity();
//   double sphericity_  = eventshape.sphericity();
//   double circularity_ = eventshape.circularity();
//   double isotropy_    = eventshape.isotropy();
//   double C_           = eventshape.C();
//   double D_           = eventshape.D();

//   /** 
//       Fill Event Shape Variables
//   **/

//   // aplanarity of event
//   hists_.find("aplanarity"  )->second->Fill( aplanarity_  , weight );
//   // sphericity of event
//   hists_.find("sphericity"  )->second->Fill( sphericity_  , weight );
//   // circularity of event
//   hists_.find("circularity" )->second->Fill( circularity_ , weight );
//   // isotropy of event
//   hists_.find("isotropy"    )->second->Fill( isotropy_    , weight );
//   // C of event
//   hists_.find("C"           )->second->Fill( C_           , weight );
//   // D of event
//   hists_.find("D"           )->second->Fill( D_           , weight );

//   /** 
//       Fill Event Shape Variables
//   **/
// /*
//   for(edm::View<pat::Jet>::const_iterator jet=jets.begin(); jet!=jets.end(); ++jet, ++index){
//     if( index_<0 || index_==index ){
//       // energy of the jet
//       hists_.find( "en"  )->second->Fill( jet->correctedJet(correctionStep(), correctionFlavor()).energy() , weight );
//       // transverse momentum of the jet
//       hists_.find( "pt"  )->second->Fill( jet->correctedJet(correctionStep(), correctionFlavor()).pt() , weight );
//       // pseudorapidity eta of the jet
//       hists_.find( "eta" )->second->Fill( jet->eta() , weight );
//       // azimuthal angle phi of the jet
//       hists_.find( "phi" )->second->Fill( jet->phi() , weight );
//     }
//   }
//   // jet multiplicty is always filled the same way
//   // independent from the choice of index_
//   hists_.find("n"  )->second->Fill( jets.size() , weight );
// */
// }
