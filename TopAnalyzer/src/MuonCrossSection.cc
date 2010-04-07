#include <Math/Boost.h>
#include <Math/VectorUtil.h>
#include "TopAnalysis/TopAnalyzer/interface/MuonCrossSection.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"


/// default constructor for generator level analysis in fw lite
MuonCrossSection::MuonCrossSection()
{
}

/// default constructor for full fw
MuonCrossSection::MuonCrossSection(const edm::ParameterSet& cfg)
{
}

/// histogramm booking for fwlite 
void MuonCrossSection::book()
{
  /** 
      Muon Variables for Cross Section Measurement Reco Particles
  **/
  // muon pt
  hists_["pt" ] = new TH1F( "pt",   "pt",   4, CrossSection::muonPt  );
  // muon eta
  hists_["eta"] = new TH1F( "eta", "eta",   4, CrossSection::muonEta );
  // muon phi
  hists_["phi"] = new TH1F( "phi", "phi",   6, CrossSection::muonPhi );

  /** 
      Muon Variables for Cross Section Measurement Generator Particles
  **/
  // muon pt
  hists_["ptGen" ] = new TH1F( "ptGen",   "ptGen",   4, CrossSection::muonPt  );
  // muon eta
  hists_["etaGen"] = new TH1F( "etaGen", "etaGen",   4, CrossSection::muonEta );
  // muon phi
  hists_["phiGen"] = new TH1F( "phiGen", "phiGen",   6, CrossSection::muonPhi );

  /** 
      Correlation Plots
  **/
  // gen-rec level correlation muon pt
  corrs_["muonPt_"    ] = new TH2F( "muonPt_"    , "muonPt_"    ,  400,    0.,  400.,     400,   0.,  400.);
  // gen-rec level correlation muon eta
  corrs_["muonEta_"   ] = new TH2F( "muonEta_"   , "muonEta_"   ,  800,   -4.,    4.,     800,  -4.,    4.);
  // gen-rec level correlation muon phi
  corrs_["muonPhi_"   ] = new TH2F( "muonPhi_"   , "muonPhi_"   ,  628, -3.14,  3.14,     628,-3.14,  3.14);

  /** 
      Muon Charge Distribution plot
  **/
  // muon multiplicty
  hists_["charge"  ] = new TH1F( "charge"   , "charge"   ,  4 ,  0  ,  4 );

  /** 
      Charge dependent Muon Variables for Cross Section Measurement Reco Particles
  **/
  // positive charged muon pt
  hists_["ptMuPlus"   ] = new TH1F( "ptMuPlus", "ptMuPlus"  ,   4, CrossSection::muonPt  );
  // positive charged muon eta
  hists_["etaMuPlus"  ] = new TH1F( "etaMuPlus", "etaMuPlus",   4, CrossSection::muonEta );
  // positive charged muon phi
  hists_["phiMuPlus"  ] = new TH1F( "phiMuPlus", "phiMuPlus",   6, CrossSection::muonPhi );
  // negative charged muon pt
  hists_["ptMuMinus"  ] = new TH1F( "ptMuMinus", "ptMuMinus"  ,   4, CrossSection::muonPt  );
  // negative charged muon eta
  hists_["etaMuMinus" ] = new TH1F( "etaMuMinus", "etaMuMinus",   4, CrossSection::muonEta );
  // negative charged muon phi
  hists_["phiMuMinus" ] = new TH1F( "phiMuMinus", "phiMuMinus",   6, CrossSection::muonPhi );

}

/// histogramm booking for fw
void MuonCrossSection::book(edm::Service<TFileService>& fs)
{
  /** 
      Muon Variables for Cross Section Measurement Reco Particles
  **/
  // muon pt
  hists_["pt"  ] = fs->make<TH1F>( "pt"    ,  "pt",   4, CrossSection::muonPt  );
  // muon eta
  hists_["eta" ] = fs->make<TH1F>( "eta"   , "eta",   4, CrossSection::muonEta );
  // muon phi
  hists_["phi" ] = fs->make<TH1F>( "phi"   , "phi",   6, CrossSection::muonPhi );

  /** 
      Muon Variables for Cross Section Measurement Generator Particles
  **/
  // muon pt
  hists_["ptGen"  ] = fs->make<TH1F>( "ptGen"    ,  "ptGen",   4, CrossSection::muonPt  );
  // muon eta
  hists_["etaGen" ] = fs->make<TH1F>( "etaGen"   , "etaGen",   4, CrossSection::muonEta );
  // muon phi
  hists_["phiGen" ] = fs->make<TH1F>( "phiGen"   , "phiGen",   6, CrossSection::muonPhi );

 /** 
      Correlation Plots
  **/
  // gen-rec level correlation muon pt
  corrs_["muonPt_"    ] = fs->make<TH2F>( "muonPt_"    , "muonPt_"    ,  400,    0.,  400.,     400,   0.,  400.);
  // gen-rec level correlation muon eta
  corrs_["muonEta_"   ] = fs->make<TH2F>( "muonEta_"   , "muonEta_"   ,  800,   -4.,    4.,     800,  -4.,    4.);
  // gen-rec level correlation muon phi
  corrs_["muonPhi_"   ] = fs->make<TH2F>( "muonPhi_"   , "muonPhi_"   ,  628, -3.14,  3.14,     628,-3.14,  3.14);

  /** 
      Muon Charge Distribution plot
  **/
  // muon multiplicty
  hists_["charge"  ] = fs->make<TH1F>( "charge"   , "charge"   ,  4 ,  0  ,  4 );


  /** 
      Charge dependent Muon Variables for Cross Section Measurement Reco Particles
  **/
  // positive charged muon pt
  hists_["ptMuPlus"   ] = fs->make<TH1F>( "ptMuPlus", "ptMuPlus"  ,   4, CrossSection::muonPt   );
  // positive charged muon eta
  hists_["etaMuPlus"  ] = fs->make<TH1F>( "etaMuPlus", "etaMuPlus",   4, CrossSection::muonEta  );
  // positive charged muon phi
  hists_["phiMuPlus"  ] = fs->make<TH1F>( "phiMuPlus", "phiMuPlus",   6, CrossSection::muonPhi  );
  // negative charged muon pt
  hists_["ptMuMinus"  ] = fs->make<TH1F>( "ptMuMinus", "ptMuMinus"  ,   4, CrossSection::muonPt  );
  // negative charged muon eta
  hists_["etaMuMinus" ] = fs->make<TH1F>( "etaMuMinus", "etaMuMinus",   4, CrossSection::muonEta );
  // negative charged muon phi
  hists_["phiMuMinus" ] = fs->make<TH1F>( "phiMuMinus", "phiMuMinus",   6, CrossSection::muonPhi );
  //  std::cout << "booking ok" << std::endl;
}

/// histogram filling with fwlite or full framework
void
MuonCrossSection::fill(const edm::View<pat::Muon>& muons, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/
  for(edm::View<pat::Muon>::const_iterator muon=muons.begin(); muon!=muons.end(); ++muon){


    //------------------------------//
    //--filling for reco particles--//
    //------------------------------//

    // transverse momentum of the muon
    hists_.find( "pt"   )->second->Fill( muon->et()  , weight );
     // pseudorapidity of the muon
    hists_.find( "eta"  )->second->Fill( muon->eta() , weight );
     // azimuth angle of the muon
    hists_.find( "phi"  )->second->Fill( muon->phi() , weight );
 

    //-----------------------------------//
    //--filling for generator particles--//
    //-----------------------------------//

    if(muon->genLepton()){
    // transverse momentum of the muon
    hists_.find( "ptGen"   )->second->Fill( muon->genLepton()->et()  , weight );
     // pseudorapidity of the muon
    hists_.find( "etaGen"  )->second->Fill( muon->genLepton()->eta() , weight );
     // azimuth angle of the muon
    hists_.find( "phiGen"  )->second->Fill( muon->genLepton()->phi() , weight );
 
    //---------------------------------//
    //--filling for correlation plots--//
    //---------------------------------//

    // transverse momentum of the muon
    corrs_.find("muonPt_"  )->second->Fill( muon->genLepton()->et() ,  muon->et()   , weight );
    // pseudorapidity of the muon
    corrs_.find("muonEta_" )->second->Fill( muon->genLepton()->eta(),  muon->eta()  , weight );
    // azimuth angle of the muon
    corrs_.find("muonPhi_" )->second->Fill( muon->genLepton()->phi(),  muon->phi()  , weight );
    }
    else{
      edm::LogWarning ( "NoGenLepton" ) << "no associated GenLepton found";
    } 
    
    //----------------------------//
    //--charge dependent filling--//
    //----------------------------//

    // filling for negative charged muons
    if(muon->charge()<0){
    hists_.find("charge"  )->second->Fill( 1 , weight );
 
    // filling for reco particles
    // transverse momentum of the muon
    hists_.find( "ptMuMinus"   )->second->Fill( muon->et()  , weight );
     // pseudorapidity of the muon
    hists_.find( "etaMuMinus"  )->second->Fill( muon->eta() , weight );
     // azimuth angle of the muon
    hists_.find( "phiMuMinus"  )->second->Fill( muon->phi() , weight );
    }
    // filling for positive charged muons
    if(muon->charge()>0){
    hists_.find("charge"  )->second->Fill( 3 , weight );

    // filling for reco particles
    // transverse momentum of the muon
    hists_.find( "ptMuPlus"   )->second->Fill( muon->et()  , weight );
    // pseudorapidity of the muon
    hists_.find( "etaMuPlus"  )->second->Fill( muon->eta() , weight );
    // azimuth angle of the muon
    hists_.find( "phiMuPlus"  )->second->Fill( muon->phi() , weight );
    }
  }
}

