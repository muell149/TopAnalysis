#include "TopAnalysis/TopAnalyzer/interface/MuonKinematics.h"

/// default constructor for fw lite
MuonKinematics::MuonKinematics(const int index) : index_(index)
{
}

/// default constructor for fwfull
MuonKinematics::MuonKinematics(const edm::ParameterSet& cfg) :
  index_( cfg.getParameter<int>( "index" ) )
{
}

/// histogramm booking for fwlite 
void
MuonKinematics::book()
{
  /** 
      Kinematic Variables
  **/
  // muon multiplicty
  hists_["n"  ] = new TH1F( "n"   , "n"   ,  10 ,  -0.5  , 9.5  );
  // energy of the muon
  hists_["en" ] = new TH1F( "en"  , "en"  , 100 ,     0. , 500. );
  // transverse momentum of the muon
  hists_["pt" ] = new TH1F( "pt"  , "pt"  , 100 ,     0. , 200. );
  // pseudorapidity eta of the muon
  hists_["eta"] = new TH1F( "eta" , "eta" ,  50 ,    -5. ,   5. );
  // azimuthal angle phi of the muon
  hists_["phi"] = new TH1F( "phi" , "phi" ,  40 ,    -4. ,   4. );
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
  hists_["en" ] = fs->make<TH1F>( "en"  , "en"  , 100 ,     0. ,   500. );
  // transverse momentum of the muon
  hists_["pt" ] = fs->make<TH1F>( "pt"  , "pt"  , 100 ,     0. ,   200. );
  // pseudorapidity eta of the muon
  hists_["eta"] = fs->make<TH1F>( "eta" , "eta" ,  50 ,    -5. ,     5. );
  // azimuthal angle phi of the muon
  hists_["phi"] = fs->make<TH1F>( "phi" , "phi" ,  40 ,    -4. ,     4. );
}

/// histogram filling for fwlite and for full fw
void
MuonKinematics::fill(const edm::View<reco::Candidate>& muons, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/

  // index for the leading, 2. leading, 3. leading muon
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all muons' and index_=n
  // n>=-1 means 'fill only n-th leading muon'
  int index=0;
  for(edm::View<reco::Candidate>::const_iterator muon=muons.begin(); muon!=muons.end(); ++muon, ++index){
    if( index_<0 || index_==index ){
      // energy of the muon
      fill( "en" , muon->energy() , weight );
      // transverse momentum of the muon
      fill( "pt" , muon->et()     , weight );
      // pseudorapidity eta of the muon
      fill( "eta", muon->eta()    , weight );
      // azimuthal angle phi of the muon
      fill( "phi", muon->phi()    , weight );
    }
  }
  // muon multiplicty is always filled the same way
  // independent from the choice of index_
  fill("n",  index , weight );
}
