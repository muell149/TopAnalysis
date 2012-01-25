#include "TopAnalysis/TopAnalyzer/interface/MuonKinematics.h"

/// default constructor for fw lite
MuonKinematics::MuonKinematics(const int index) : index_(index)
{
}

/// default constructor for fwfull
MuonKinematics::MuonKinematics(const edm::ParameterSet& cfg) :
  useTree_ ( cfg.getParameter<bool>( "useTree" ) ),
  index_( cfg.getParameter<int>( "index" ) )
{
  tree = 0;
}

/// histogramm booking for fwlite 
void
MuonKinematics::book()
{
  /** 
      Kinematic Variables
  **/
  // muon multiplicty
  hists_["n"  ] = new TH1F( "n"   , "n"   ,  10 ,  -0.5  ,   9.5 );
  // energy of the muon
  hists_["en" ] = new TH1F( "en"  , "en"  ,  60 ,     0. , 300.  );
  // transverse momentum of the muon
  hists_["pt" ] = new TH1F( "pt"  , "pt"  ,  30 ,     0. , 150.  );
  // pseudorapidity eta of the muon
  hists_["eta"] = new TH1F( "eta" , "eta" ,  70 ,  -3.5  ,   3.5 );
  // rapidity y of the muon
  hists_["y"  ] = new TH1F( "y"   , "y"  ,  70  ,  -3.5  ,   3.5 );
  // azimuthal angle phi of the muon
  hists_["phi"] = new TH1F( "phi" , "phi" ,  70 ,  -3.14 ,   3.14);
}

/// histogramm booking for full fw
void
MuonKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Kinematic Variables
  **/
  // muon multiplicty
  hists_["n"  ] = fs->make<TH1F>( "n"   , "n"   ,  10 ,  -0.5  ,   9.5  );
  // energy of the muon
  hists_["en" ] = fs->make<TH1F>( "en"  , "en"  ,  60 ,     0. ,   300. );
  // transverse momentum of the muon
  hists_["pt" ] = fs->make<TH1F>( "pt"  , "pt"  ,  30 ,     0. ,   150. );
  // pseudorapidity eta of the muon
  hists_["eta"] = fs->make<TH1F>( "eta" , "eta" ,  70 ,   -3.5 ,    3.5 );
  // rapidity y of the muon
  hists_["y"  ] = fs->make<TH1F>( "y"   , "y"   ,  70 ,   -3.5 ,    3.5 );
  // azimuthal angle phi of the muon
  hists_["phi"] = fs->make<TH1F>( "phi" , "phi" ,  70 ,  -3.14 ,   3.14 );
  
  /// tree
  // only produce a tree for the following collctions if they are only
  // for one object and a tree should be written
  if(index_ > -1 && useTree_){
  // muon multiplicty
    bookVariable( fs, "n");
  // energy of the muon
    bookVariable( fs, "en");
  // transverse momentum of the muon
    bookVariable( fs, "pt");
  // pseudorapidity eta of the muon
    bookVariable( fs, "eta");
  // rapidity y of the muon
    bookVariable( fs, "y");
  // azimuthal angle phi of the muon
    bookVariable( fs, "phi");
    // additionally relIso
    bookVariable( fs, "relIso");
  }

}

/// histogram filling for fwlite and for full fw
void
    MuonKinematics::fill(const edm::View<pat::Muon>& muons, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/

  // initialize tree
  if(index_ > -1 && useTree_) initializeTrees(-9999, weight);

  // index for the leading, 2. leading, 3. leading muon
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all muons' and index_=n
  // n>=-1 means 'fill only (n-1)-th leading muon'
  int index=0;
  for(edm::View<pat::Muon>::const_iterator muon=muons.begin(); muon!=muons.end(); ++muon, ++index){
    if( index_<0 || index_==index ){
      // energy of the muon
      fillValue( "en" , muon->energy() , weight );
      // transverse momentum of the muon
      fillValue( "pt" , muon->et()     , weight );
      // pseudorapidity eta of the muon
      fillValue( "eta", muon->eta()    , weight );
      // rapidity y of the muon
      fillValue( "y"  , muon->rapidity(), weight );
      // azimuthal angle phi of the muon
      fillValue( "phi", muon->phi()    , weight );
      // relIso of the muon (only for tree)
      fillValue("relIso", (muon->chargedHadronIso() + muon->neutralHadronIso() + 
	  muon->photonIso()) / muon->et() , weight );
    }
  }
  // muon multiplicty is always filled the same way
  // independent from the choice of index_
  fillValue("n",  index , weight );
  
  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();
}
