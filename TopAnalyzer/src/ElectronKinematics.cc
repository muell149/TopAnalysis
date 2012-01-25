#include "TopAnalysis/TopAnalyzer/interface/ElectronKinematics.h"

/// default constructor for fw lite
ElectronKinematics::ElectronKinematics(const int index) : index_(index)
{
  tree = 0;
}

/// default constructor for fwfull
ElectronKinematics::ElectronKinematics(const edm::ParameterSet& cfg) :
  useTree_ ( cfg.getParameter<bool>( "useTree" ) ),
  index_( cfg.getParameter<int>( "index" ) )
{
  tree = 0;
}

/// histogramm booking for fwlite 
void
ElectronKinematics::book()
{
  /** 
      Kinematic Variables
  **/
  // electron multiplicty
  hists_["n"  ] = new TH1F( "n"   , "n"   ,  10 ,  -0.5  ,   9.5 );
  // energy of the electron
  hists_["en" ] = new TH1F( "en"  , "en"  ,  60 ,     0. , 300.  );
  // transverse energy of the electron
  hists_["et" ] = new TH1F( "et"  , "et"  ,  30 ,     0. , 150.  );
  // transverse momentum of the electron
  hists_["pt" ] = new TH1F( "pt"  , "pt"  ,  30 ,     0. , 150.  );
  // pseudorapidity eta of the electron
  hists_["eta"] = new TH1F( "eta" , "eta" ,  35 ,  -3.5  ,   3.5 );
  // azimuthal angle phi of the electron
  hists_["phi"] = new TH1F( "phi" , "phi" ,  30 ,  -3.14 ,   3.14);
}

/// histogramm booking for full fw
void
ElectronKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Kinematic Variables
  **/
  // electron multiplicty
  hists_["n"  ] = fs->make<TH1F>( "n"   , "n"   ,  10 ,  -0.5  ,   9.5  );
  // energy of the electron
  hists_["en" ] = fs->make<TH1F>( "en"  , "en"  ,  60 ,     0. ,   300. );
   // transverse energy of the electron
  hists_["et" ] = fs->make<TH1F>( "et"  , "et"  ,  30 ,     0. ,   150. );
  // transverse momentum of the electron
  hists_["pt" ] = fs->make<TH1F>( "pt"  , "pt"  ,  30 ,     0. ,   150. );
  // pseudorapidity eta of the electron
  hists_["eta"] = fs->make<TH1F>( "eta" , "eta" ,  35 ,   -3.5 ,    3.5 );
  // azimuthal angle phi of the electron
  hists_["phi"] = fs->make<TH1F>( "phi" , "phi" ,  30 ,  -3.14 ,   3.14 );
  
  /// tree
  // only produce a tree for the following collctions if they are only
  // for one object and a tree should be written
  if(index_ > -1 && useTree_){
    // electron multiplicty
      bookVariable( fs, "n");
    // energy of the electron
      bookVariable( fs, "en");
    // transverse energy of the electron
      bookVariable( fs, "et");
    // transverse momentum of the electron
      bookVariable( fs, "pt");
    // pseudorapidity eta of the electron
      bookVariable( fs, "eta");
    // azimuthal angle phi of the electron
      bookVariable( fs, "phi");
    }
}

/// histogram filling for fwlite and for full fw
void
ElectronKinematics::fill(const edm::View<reco::Candidate>& electrons, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/
  
  // initialize tree
  if(useTree_) initializeTrees(-9999, weight);

  // index for the leading, 2. leading, 3. leading electron
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all electrons' and index_=n
  // n>=-1 means 'fill only n-th leading electron'
  int index=0;
  for(edm::View<reco::Candidate>::const_iterator electron=electrons.begin(); electron!=electrons.end(); ++electron, ++index){
    if( index_<0 || index_==index ){
      // energy of the electron
      fillValue("en", electron->energy() , weight );
      // transverse energy of the electron
      fillValue("et", electron->et() , weight ); 
      // transverse momentum of the electron
      fillValue("pt", electron->pt() , weight );
      // pseudorapidity eta of the electron
      fillValue("eta", electron->eta() , weight );
      // azimuthal angle phi of the electron
      fillValue("phi", electron->phi() , weight );
    }
  }
  // electron multiplicty is always filled the same way
  // independent from the choice of index_
  fillValue("n", index , weight );
  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();
}
