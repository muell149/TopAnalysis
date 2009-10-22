#include "TopAnalysis/TopAnalyzer/interface/JetKinematics.h"

/// default constructor for fw lite
JetKinematics::JetKinematics(const int index, const std::string& correctionLevel) : index_(index), correctionLevel_(correctionLevel)
{
}

/// default constructor for fwfull
JetKinematics::JetKinematics(const edm::ParameterSet& cfg) :
  index_( cfg.getParameter<int>( "index" ) ),
  correctionLevel_( cfg.getParameter<std::string>( "correctionLevel" ) )
{
}

/// histogramm booking for fwlite 
void
JetKinematics::book()
{
  /** 
      Kinematic Variables
  **/
  // jet multiplicty
  hists_["n"  ] = new TH1F( "n"   , "n"   ,  10 ,     0. ,    10. );
  // energy of the jet
  hists_["en" ] = new TH1F( "en"  , "en"  ,  60 ,     0. ,   300. );
  // transverse momentum of the jet
  hists_["pt" ] = new TH1F( "pt"  , "pt"  ,  30 ,     0. ,   150. );
  // pseudorapidity eta of the jet
  hists_["eta"] = new TH1F( "eta" , "eta" ,  70 ,   -3.5 ,    3.5 );
  // azimuthal angle phi of the jet
  hists_["phi"] = new TH1F( "phi" , "phi" ,  70 ,  -3.14 ,   3.14 );
}

/// histogramm booking for full fw
void
JetKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Kinematic Variables
  **/
  // jet multiplicty
  hists_["n"  ] = fs->make<TH1F>( "n"   , "n"   ,  10 ,     0. ,    10. );
  // energy of the jet
  hists_["en" ] = fs->make<TH1F>( "en"  , "en"  ,  60 ,     0. ,   300. );
  // transverse momentum of the jet
  hists_["pt" ] = fs->make<TH1F>( "pt"  , "pt"  ,  30 ,     0. ,   150. );
  // pseudorapidity eta of the jet
  hists_["eta"] = fs->make<TH1F>( "eta" , "eta" ,  70 ,   -3.5 ,    3.5 );
  // azimuthal angle phi of the jet
  hists_["phi"] = fs->make<TH1F>( "phi" , "phi" ,  70 ,  -3.14 ,   3.14 );
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
  int index=0;
  for(std::vector<reco::GenJet>::const_iterator jet=jets.begin(); jet!=jets.end(); ++jet, ++index){
    if( index_<0 || index_==index ){
      // energy of the jet
      hists_.find("en"  )->second->Fill( jet->energy() , weight );
      // transverse momentum of the jet
      hists_.find("pt"  )->second->Fill( jet->pt() , weight );
      // pseudorapidity eta of the jet
      hists_.find("eta" )->second->Fill( jet->eta() , weight );
      // azimuthal angle phi of the jet
      hists_.find("phi" )->second->Fill( jet->phi() , weight );
    }
  }
  // jet multiplicty is always filled the same way
  // independent from the choice of index_
  hists_.find("n"  )->second->Fill( index , weight );
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
JetKinematics::fill(const std::vector<pat::Jet>& jets, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/
  // index for the leading, 2. leading, 3. leading jet
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all jets' and index_=n
  // n>=-1 means 'fill only n-th leading jet'
  int index=0;
  for(std::vector<pat::Jet>::const_iterator jet=jets.begin(); jet!=jets.end(); ++jet, ++index){
    if( index_<0 || index_==index ){
      // energy of the jet
      hists_.find( "en"  )->second->Fill( jet->correctedJet(correctionStep(), correctionFlavor()).energy() , weight );
      // transverse momentum of the jet
      hists_.find( "pt"  )->second->Fill( jet->correctedJet(correctionStep(), correctionFlavor()).pt() , weight );
      // pseudorapidity eta of the jet
      hists_.find( "eta" )->second->Fill( jet->eta() , weight );
      // azimuthal angle phi of the jet
      hists_.find( "phi" )->second->Fill( jet->phi() , weight );
    }
  }
  // jet multiplicty is always filled the same way
  // independent from the choice of index_
  hists_.find("n"  )->second->Fill( jets.size() , weight );
}
