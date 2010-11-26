#include "TopAnalysis/TopAnalyzer/interface/JetKinematics.h"

/// default constructor for fw lite
JetKinematics::JetKinematics(const int index, const std::string& correctionLevel) : index_(index), correctionLevel_(correctionLevel)
{
  tree = 0;
}

/// default constructor for fwfull
JetKinematics::JetKinematics(const edm::ParameterSet& cfg) :
  useTree_ ( cfg.getParameter<bool>( "useTree" ) ),
  index_( cfg.getParameter<int>( "index" ) ),
  correctionLevel_( cfg.getParameter<std::string>( "correctionLevel" ) )
{
  tree = 0;
}

/// histogramm booking for fwlite 
void
JetKinematics::book()
{
  /** 
      Kinematic Variables
  **/
  // jet multiplicty
  hists_["n"  ] = new TH1F( "n"   , "n"   ,  20 , -0.5 ,  19.5  );
  // energy of the jet
  hists_["en" ] = new TH1F( "en"  , "en"  , 200 ,   0. ,  1000. );
  // transverse momentum of the jet
  hists_["pt" ] = new TH1F( "pt"  , "pt"  , 100 ,   0. ,   500. );
  // pseudorapidity eta of the jet
  hists_["eta"] = new TH1F( "eta" , "eta" ,  50 ,  -5. ,     5. );
  // azimuthal angle phi of the jet
  hists_["phi"] = new TH1F( "phi" , "phi" ,  40 ,  -4. ,     4. );
}

/// histogramm booking for full fw
void
JetKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Kinematic Variables
  **/
  // jet multiplicty
<<<<<<< JetKinematics.cc
  hists_["n"  ] = fs->make<TH1F>( "n"   , "n"   ,  20 , -0.5 ,  19.5  );
=======
  bookVariable( fs, "n"      ,  10,  0. , 10. , useTree_ );

  // only produce a tree for the following collctions if they are only
  // for one object and a tree should be written
  bool singleObjectInTree = false;
  if(index_ > -1 && useTree_) singleObjectInTree = true;

>>>>>>> 1.6
  // energy of the jet
<<<<<<< JetKinematics.cc
  hists_["en" ] = fs->make<TH1F>( "en"  , "en"  , 200 ,   0. ,  1000. );
=======
  bookVariable( fs, "en"  ,  180 ,  0.   , 900. , singleObjectInTree );
>>>>>>> 1.6
  // transverse momentum of the jet
<<<<<<< JetKinematics.cc
  hists_["pt" ] = fs->make<TH1F>( "pt"  , "pt"  , 100 ,   0. ,   500. );
=======
  bookVariable( fs, "pt"  ,  120 ,  0.   , 600. , singleObjectInTree );
>>>>>>> 1.6
  // pseudorapidity eta of the jet
<<<<<<< JetKinematics.cc
  hists_["eta"] = fs->make<TH1F>( "eta" , "eta" ,  50 ,  -5. ,     5. );
=======
  bookVariable( fs, "eta" ,   70 , -3.5  ,  3.5 , singleObjectInTree );
>>>>>>> 1.6
  // azimuthal angle phi of the jet
<<<<<<< JetKinematics.cc
  hists_["phi"] = fs->make<TH1F>( "phi" , "phi" ,  40 ,  -4. ,     4. );
=======
  bookVariable( fs, "phi" ,   70 , -M_PI , M_PI , singleObjectInTree );
>>>>>>> 1.6
}

/// histogram filling for fwlite and for full fw
void
JetKinematics::fill(const std::vector<reco::GenJet>& jets, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/

  // index for the leading, 2. leading, 3. leading jet
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all jets' and index_=n
  // n>=-1 means 'fill only n-th leading jet'

  int index = 0;

  for(std::vector<reco::GenJet>::const_iterator jet=jets.begin(); jet!=jets.end(); ++jet, ++index){
    if( index_<0 || index_==index ){
      // energy of the jet
      fillValue( "en" , jet->energy() , weight );
      // transverse momentum of the jet
      fillValue( "pt" , jet->pt() , weight );
      // pseudorapidity eta of the jet
      fillValue( "eta" , jet->eta() , weight );
      // azimuthal angle phi of the jet
      fillValue( "phi" , jet->phi() , weight );
    }
  }
  // jet multiplicty is always filled the same way
  // independent from the choice of index_
<<<<<<< JetKinematics.cc
  hists_.find("n"  )->second->Fill( index  , weight );

=======
  fillValue( "n" , index , weight );

  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();
>>>>>>> 1.6
}

/// return the desired correction step from the configuration string, which is expected to be of type 'step' or 'step:flavor'
const std::string JetKinematics::correctionStep() const
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
const std::string JetKinematics::correctionFlavor() const
{
  std::string flavor;
  if(correctionLevel_.find(":")!=std::string::npos){
    flavor=correctionLevel_.substr(1+correctionLevel_.find(":"));
  }
  return flavor;
}

/// histogram filling for fwlite and for full fw
void
JetKinematics::fill(const edm::View<pat::Jet>& jets, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/
  // index for the leading, 2. leading, 3. leading jet
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all jets' and index_=n
  // n>=-1 means 'fill only n-th leading jet'
  int index=0;
  for(edm::View<pat::Jet>::const_iterator jet=jets.begin(); jet!=jets.end(); ++jet, ++index){
    if( index_<0 || index_==index ){
      // energy of the jet
      fillValue( "en" , jet->correctedJet(correctionStep(), correctionFlavor()).energy() , weight );
      // transverse momentum of the jet
      fillValue( "pt" , jet->correctedJet(correctionStep(), correctionFlavor()).pt() , weight );
      // pseudorapidity eta of the jet
      fillValue( "eta" , jet->eta() , weight );
      // azimuthal angle phi of the jet
      fillValue( "phi" , jet->phi() , weight );
    }
  }
  // jet multiplicty is always filled the same way
  // independent from the choice of index_
  fillValue( "n" , jets.size() , weight );

  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();
}
