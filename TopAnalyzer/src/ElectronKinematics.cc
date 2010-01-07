#include "TopAnalysis/TopAnalyzer/interface/ElectronKinematics.h"

/// default constructor for fw lite
ElectronKinematics::ElectronKinematics(const int index) : index_(index)
{
}

/// default constructor for fwfull
ElectronKinematics::ElectronKinematics(const edm::ParameterSet& cfg) :
  index_( cfg.getParameter<int>( "index" ) )
{
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
  // transverse momentum of the electron
  hists_["et" ] = new TH1F( "et"  , "et"  ,  30 ,     0. , 150.  );
  // pseudorapidity eta of the electron
  hists_["eta"] = new TH1F( "eta" , "eta" ,  70 ,  -3.5  ,   3.5 );
  // azimuthal angle phi of the electron
  hists_["phi"] = new TH1F( "phi" , "phi" ,  70 ,  -3.14 ,   3.14);
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
  // transverse momentum of the electron
  hists_["et" ] = fs->make<TH1F>( "et"  , "et"  ,  30 ,     0. ,   150. );
  // pseudorapidity eta of the electron
  hists_["eta"] = fs->make<TH1F>( "eta" , "eta" ,  70 ,   -3.5 ,    3.5 );
  // azimuthal angle phi of the electron
  hists_["phi"] = fs->make<TH1F>( "phi" , "phi" ,  70 ,  -3.14 ,   3.14 );
}

/// histogram filling for fwlite and for full fw
void
ElectronKinematics::fill(const std::vector<reco::GenParticle>& electrons, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/

  // index for the leading, 2. leading, 3. leading electron
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all electrons' and index_=n
  // n>=-1 means 'fill only n-th leading electron'
  int index=0;
  for(std::vector<reco::GenParticle>::const_iterator electron=electrons.begin(); electron!=electrons.end(); ++electron, ++index){
    if( index_<0 || index_==index ){
      // energy of the electron
      hists_.find("en"  )->second->Fill( electron->energy() , weight );
      // transverse momentum of the electron
      hists_.find("et"  )->second->Fill( electron->et() , weight );
      // pseudorapidity eta of the electron
      hists_.find("eta" )->second->Fill( electron->eta() , weight );
      // azimuthal angle phi of the electron
      hists_.find("phi" )->second->Fill( electron->phi() , weight );
    }
  }
  // electron multiplicty is always filled the same way
  // independent from the choice of index_
  hists_.find("n"  )->second->Fill( index , weight );
}

/// histogram filling for fwlite and for full fw
void
ElectronKinematics::fill(const edm::View<pat::Electron>& electrons, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/

  // index for the leading, 2. leading, 3. leading electron
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all electrons' and index_=n
  // n>=-1 means 'fill only n-th leading electron'
  int index=0;
  for(edm::View<pat::Electron>::const_iterator electron=electrons.begin(); electron!=electrons.end(); ++electron, ++index){
    if( index_<0 || index_==index ){
      // energy of the electron
      hists_.find( "en"  )->second->Fill( electron->energy() , weight );
      // transverse momentum of the electron
      hists_.find( "et"  )->second->Fill( electron->et() , weight );
      // pseudorapidity eta of the electron
      hists_.find( "eta" )->second->Fill( electron->eta() , weight );
      // azimuthal angle phi of the electron
      hists_.find( "phi" )->second->Fill( electron->phi() , weight );
    }
  }
  // electron multiplicty is always filled the same way
  // independent from the choice of index_
  hists_.find("n"  )->second->Fill( electrons.size() , weight );
}
