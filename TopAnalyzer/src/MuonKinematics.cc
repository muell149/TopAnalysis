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
  hists_["n"  ] = new TH1F( "n"   , "n"   ,  10 ,     0. ,    10. );
  // energy of the muon
  hists_["en" ] = new TH1F( "en"  , "en"  ,  60 ,     0. ,   300. );
  // transverse momentum of the muon
  hists_["pt" ] = new TH1F( "pt"  , "pt"  ,  30 ,     0. ,   150. );
  // pseudorapidity eta of the muon
  hists_["eta"] = new TH1F( "eta" , "eta" ,  70 ,   -3.5 ,    3.5 );
  // azimuthal angle phi of the muon
  hists_["phi"] = new TH1F( "phi" , "phi" ,  70 ,  -3.14 ,   3.14 );
}

/// histogramm booking for full fw
void
MuonKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Kinematic Variables
  **/
  // muon multiplicty
  hists_["n"  ] = fs->make<TH1F>( "n"   , "n"   ,  10 ,     0. ,    10. );
  // energy of the muon
  hists_["en" ] = fs->make<TH1F>( "en"  , "en"  ,  60 ,     0. ,   300. );
  // transverse momentum of the muon
  hists_["pt" ] = fs->make<TH1F>( "pt"  , "pt"  ,  30 ,     0. ,   150. );
  // pseudorapidity eta of the muon
  hists_["eta"] = fs->make<TH1F>( "eta" , "eta" ,  70 ,   -3.5 ,    3.5 );
  // azimuthal angle phi of the muon
  hists_["phi"] = fs->make<TH1F>( "phi" , "phi" ,  70 ,  -3.14 ,   3.14 );
}

/// histogram filling for fwlite and for full fw
void
MuonKinematics::fill(const std::vector<reco::GenParticle>& muons, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/

  // index for the leading, 2. leading, 3. leading muon
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all muons' and index_=n
  // n>=-1 means 'fill only n-th leading muon'
  int index=0;
  for(std::vector<reco::GenParticle>::const_iterator muon=muons.begin(); muon!=muons.end(); ++muon, ++index){
    if( index_<0 || index_==index ){
      // energy of the muon
      hists_.find("en"  )->second->Fill( muon->energy() , weight );
      // transverse momentum of the muon
      hists_.find("pt"  )->second->Fill( muon->et() , weight );
      // pseudorapidity eta of the muon
      hists_.find("eta" )->second->Fill( muon->eta() , weight );
      // azimuthal angle phi of the muon
      hists_.find("phi" )->second->Fill( muon->phi() , weight );
    }
    // muon multiplicty is always filled the same way
    // independent from the choice of index_
    hists_.find("n"  )->second->Fill( index , weight );
  }
}

/// histogram filling for fwlite and for full fw
void
MuonKinematics::fill(const std::vector<pat::Muon>& muons, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/

  // index for the leading, 2. leading, 3. leading muon
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all muons' and index_=n
  // n>=-1 means 'fill only n-th leading muon'
  int index=0;
  for(std::vector<pat::Muon>::const_iterator muon=muons.begin(); muon!=muons.end(); ++muon, ++index){
    if( index_<0 || index_==index ){
      // energy of the muon
      hists_.find( "en"  )->second->Fill( muon->energy() , weight );
      // transverse momentum of the muon
      hists_.find( "pt"  )->second->Fill( muon->et() , weight );
      // pseudorapidity eta of the muon
      hists_.find( "eta" )->second->Fill( muon->eta() , weight );
      // azimuthal angle phi of the muon
      hists_.find( "phi" )->second->Fill( muon->phi() , weight );
    }
    // muon multiplicty is always filled the same way
    // independent from the choice of index_
    hists_.find("n"  )->second->Fill( muons.size() , weight );
  }
}
