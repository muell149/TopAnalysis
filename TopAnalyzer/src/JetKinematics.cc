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
  hists_["n"  ] = new TH1F( "n"   , "n"   ,   20 ,   -0.5 ,   19.5 );
  // energy of the jet			    
  hists_["en" ] = new TH1F( "en"  , "en"  ,  180 ,     0. ,   900. );
  // transverse momentum of the jet	    
  hists_["pt" ] = new TH1F( "pt"  , "pt"  ,  120 ,     0. ,   600. );
  // pseudorapidity eta of the jet	    
  hists_["eta"] = new TH1F( "eta" , "eta" ,   70 ,   -3.5 ,    3.5 );
  // azimuthal angle phi of the jet	    
  hists_["phi"] = new TH1F( "phi" , "phi" ,   70 ,  -3.14 ,   3.14 );
  // scalar sum	of jet et			    
  hists_["ht" ] = new TH1F( "ht"  , "ht"  , 2000 ,     0. ,  2000. );
  // 2D histogram of eta and phi
  hists2D_["etaPt"] = new TH2F ("etaPt","etaPt", 70 , -3.5 , 3.5, 120 , 0. , 600.);
  // indicator wheter it is gen or rec jet
  hists_["type"   ] = new TH1F( "type"   , "type"   ,   2 ,     0. ,    2. );
}

/// histogramm booking for full fw
void
JetKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Kinematic Variables
  **/
  
  /// histos in any case (also if tree is produced)
  // jet multiplicty
  bookVariable( fs, "n"   ,   20 , -0.5  , 19.5);
 // energy of the jet
  bookVariable( fs, "en"  ,  180 ,  0.   , 900.);
  // transverse momentum of the jet
  bookVariable( fs, "pt"  ,  120 ,  0.   , 600.);
  // pseudorapidity eta of the jet
  bookVariable( fs, "eta" ,   70 , -3.5  ,  3.5);
  // azimuthal angle phi of the jet
  bookVariable( fs, "phi" ,   70 , -M_PI , M_PI);
  // scalar sum	of jet et
  bookVariable( fs, "ht"  , 2000 ,  0.   , 2000.);
  // 2D histogram of eta and phi
  hists2D_["etaPt"] = fs->make<TH2F>( "etaPt", "etaPt", 70 , -3.5 , 3.5, 120 , 0. , 600. );
  // indicator wheter it is gen or rec jet
  bookVariable( fs, "type",   2 ,     0. ,    2.);
  hists_.find("type")->second->GetXaxis()->SetBinLabel(1, "pat");
  hists_.find("type")->second->GetXaxis()->SetBinLabel(2, "other");

  /// tree
  // only produce a tree for the following collctions if they are only
  // for one object and a tree should be written
  if(useTree_){
    if(index_ > -1){
    // jet multiplicty
    bookVariable( fs, "n");
    // energy of the jet
    bookVariable( fs, "en");
    // transverse momentum of the jet
    bookVariable( fs, "pt");
    // pseudorapidity eta of the jet
    bookVariable( fs, "eta");
    // azimuthal angle phi of the jet
    bookVariable( fs, "phi");
    // scalar sum	of jet et
    bookVariable( fs, "ht");
    // scalar sum	of jet et
    bookVariable( fs, "type");
    }
    else if( index_ == -1){
      /// in case of index_==-1 tree is filled with kinematic variables of first 5 jets
      // jet multiplicty
      bookVariable( fs, "n");
      // energy of the jet 1
      bookVariable( fs, "en1");
      // transverse momentum of the jet 1
      bookVariable( fs, "pt1");
      // pseudorapidity eta of the jet 1
      bookVariable( fs, "eta1");
      // azimuthal angle phi of the jet 1
      bookVariable( fs, "phi1");
      // energy of the jet 2
      bookVariable( fs, "en2");
      // transverse momentum of the jet 2
      bookVariable( fs, "pt2");
      // pseudorapidity eta of the jet 2
      bookVariable( fs, "eta2");
      // azimuthal angle phi of the jet 2
      bookVariable( fs, "phi2");
      // energy of the jet 3
      bookVariable( fs, "en3");
      // transverse momentum of the jet 3
      bookVariable( fs, "pt3");
      // pseudorapidity eta of the jet 3
      bookVariable( fs, "eta3");
      // azimuthal angle phi of the jet 3
      bookVariable( fs, "phi3");
      // energy of the jet 4
      bookVariable( fs, "en4");
      // transverse momentum of the jet 4
      bookVariable( fs, "pt4");
      // pseudorapidity eta of the jet 4
      bookVariable( fs, "eta4");
      // azimuthal angle phi of the jet 4
      bookVariable( fs, "phi4");
      // energy of the jet 5
      bookVariable( fs, "en5");
      // transverse momentum of the jet 5
      bookVariable( fs, "pt5");
      // pseudorapidity eta of the jet 5
      bookVariable( fs, "eta5");
      // azimuthal angle phi of the jet 5
      bookVariable( fs, "phi5");
    }
  }

  
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
  std::string flavor = "none";
  if(correctionLevel_.find(":")!=std::string::npos){
    flavor=correctionLevel_.substr(1+correctionLevel_.find(":"));
  }
  return flavor;
}

/// histogram filling for fwlite and for full fw
void
JetKinematics::fill(const edm::View<reco::Jet>& jets, const double& weight)
{
  
  // initialize tree
  if(useTree_) initializeTrees(-9999, weight);
  
  /** 
      Fill Kinematic Variables
  **/
  // index for the leading, 2. leading, 3. leading jet
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all jets' and index_=n
  // n>=-1 means 'fill only n-th leading jet'

  int index=0;
  double HT=0.;
  for(edm::View<reco::Jet>::const_iterator recoJet=jets.begin(); recoJet!=jets.end(); ++recoJet, ++index){
    // switch to pat::jet to use information of correction level
    const pat::Jet* jet = dynamic_cast< const pat::Jet* >(&(*recoJet));
    if(jet){
      // calculate scalar sum of jet et
      HT+=jet->correctedJet(correctionStep(), correctionFlavor()).et();
      if( index_<0 || index_==index ){
	// fill pat/other jet type
	fillValue( "type" , 0.5 , weight );
	// energy of the jet
	fillValue( "en" , jet->correctedJet(correctionStep(), correctionFlavor()).energy() , weight );
	// transverse momentum of the jet
	fillValue( "pt" , jet->correctedJet(correctionStep(), correctionFlavor()).pt() , weight );
	// pseudorapidity eta of the jet
	fillValue( "eta" , jet->eta() , weight );
	// azimuthal angle phi of the jet
	fillValue( "phi" , jet->phi() , weight );
	// eta, pt for 2D histo
	hists2D_.find("etaPt")->second->Fill(jet->eta() , jet->pt() , weight);
      }
    }
    // use uncorrected energy otherwise
    else{
      // calculate scalar sum of jet et
      HT+=recoJet->et();
      if( index_<0 || index_==index ){
	// fill pat/other jet type
	fillValue( "type" , 1.5 , weight );
	// energy of the recoJet
	fillValue( "en" , recoJet->energy() , weight );
	// transverse momentum of the jet
	fillValue( "pt" , recoJet->pt() , weight );
	// pseudorapidity eta of the jet
	fillValue( "eta" , recoJet->eta() , weight );
	// azimuthal angle phi of the jet
	fillValue( "phi" , recoJet->phi() , weight );
	// eta, phi for 2D histo
	hists2D_.find("etaPt")->second->Fill(recoJet->eta() , recoJet->pt() , weight);
      }
    }
    // fill tree in case of index==-1
    if(useTree_ && index_==-1 && index<5){
      // energy of the jet
      fillValue( Form("en%i",index+1) , jet->energy() , weight );
      // transverse momentum of the jet
      fillValue( Form("pt%i",index+1) , jet->pt() , weight );
      // pseudorapidity eta of the jet
      fillValue( Form("eta%i",index+1) , jet->eta() , weight );
      // azimuthal angle phi of the jet
      fillValue( Form("phi%i",index+1) , jet->phi() , weight );
    }
  }
  // scalar sum of jet et filled at least
  fillValue( "ht" , HT , weight );
  // jet multiplicty is always filled the same way
  // independent from the choice of index_
  fillValue( "n" , jets.size() , weight );
  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();
}
