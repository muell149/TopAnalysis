#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonCrossSection.h"

/// default constructor for generator level analysis in fw lite
MuonCrossSection::MuonCrossSection(int index) : index_(index)
{
}

/// default constructor for full fw
MuonCrossSection::MuonCrossSection(const edm::ParameterSet& cfg) :
  index_( cfg.getParameter<int>( "index" ) )
{
}

/// histogramm booking for fwlite 
void MuonCrossSection::book()
{
  /** 
      Muon Variables for Cross Section Measurement Reco Particles
  **/
  // muon pt
  hists_["pt"    ] = new TH1F( "pt"    ,  "pt",   6, CrossSection::muonPt  );
  // muon eta
  hists_["eta"   ] = new TH1F( "eta"   , "eta",   4, CrossSection::muonEta );
  // muon phi
  hists_["phi"   ] = new TH1F( "phi"   , "phi",   6, CrossSection::muonPhi );

 /** 
      Control Distribution plot
  **/
  // muon multiplicty
  hists_["charge"] = new TH1F( "charge"   , "charge"   ,   2 ,       -1.    ,     1.);
  // positive charged muon pt
  hists_["ptp"   ] = new TH1F( "ptPlus"   , "pt(mu+)"  ,   6, CrossSection::muonPt  );
  // positive charged muon eta
  hists_["etap"  ] = new TH1F( "etaPlus"  , "eta(mu+)" ,   4, CrossSection::muonEta );
  // positive charged muon phi
  hists_["phip"  ] = new TH1F( "phiPlus"  , "phi(mu+)" ,   6, CrossSection::muonPhi );
  // negative charged muon pt
  hists_["ptm"   ] = new TH1F( "ptMinus"  , "pt(mu-)"  ,   6, CrossSection::muonPt  );
  // negative charged muon eta
  hists_["etam"  ] = new TH1F( "etaMinus" , "eta(mu-)" ,   4, CrossSection::muonEta );
  // negative charged muon phi
  hists_["phim"  ] = new TH1F( "phiMinus" , "phi(mu-)" ,   6, CrossSection::muonPhi );

 /** 
      Correlation Plots
  **/
  // gen-rec level correlation muon pt
  hists2D_["pt_" ] = new TH2F( "pt_"    , "pt_"    ,  400,    0.,  400.,     400,   0.,  400.);
  // gen-rec level correlation muon eta
  hists2D_["eta_"] = new TH2F( "eta_"   , "eta_"   ,  800,   -4.,    4.,     800,  -4.,    4.);
  // gen-rec level correlation muon phi
  hists2D_["phi_"] = new TH2F( "phi_"   , "phi_"   ,  628, -3.14,  3.14,     628,-3.14,  3.14);
}

/// histogramm booking for full fw
void MuonCrossSection::book(edm::Service<TFileService>& fs)
{
  /** 
      Muon Variables for Cross Section Measurement Reco Particles
  **/
  // muon pt
  hists_["pt"  ] = fs->make<TH1F>( "pt"    ,  "pt",   6, CrossSection::muonPt  );
  // muon eta
  hists_["eta" ] = fs->make<TH1F>( "eta"   , "eta",   4, CrossSection::muonEta );
  // muon phi
  hists_["phi" ] = fs->make<TH1F>( "phi"   , "phi",   6, CrossSection::muonPhi );

  /** 
      Control Distribution plot
  **/
  // muon multiplicty
  hists_["charge"] = fs->make<TH1F>( "charge"   , "charge"   ,   2 ,       -1.    ,     1.);
  // positive charged muon pt
  hists_["ptp"   ] = fs->make<TH1F>( "ptPlus"   , "pt(mu+)"  ,   6, CrossSection::muonPt  );
  // positive charged muon eta
  hists_["etap"  ] = fs->make<TH1F>( "etaPlus"  , "eta(mu+)" ,   4, CrossSection::muonEta );
  // positive charged muon phi
  hists_["phip"  ] = fs->make<TH1F>( "phiPlus"  , "phi(mu+)" ,   6, CrossSection::muonPhi );
  // negative charged muon pt
  hists_["ptm"   ] = fs->make<TH1F>( "ptMinus"  , "pt(mu-)"  ,   6, CrossSection::muonPt  );
  // negative charged muon eta
  hists_["etam"  ] = fs->make<TH1F>( "etaMinus" , "eta(mu-)" ,   4, CrossSection::muonEta );
  // negative charged muon phi
  hists_["phim"  ] = fs->make<TH1F>( "phiMinus" , "phi(mu-)" ,   6, CrossSection::muonPhi );

  /** 
      Correlation Plots
  **/
  // gen-rec level correlation muon pt
  hists2D_["pt_" ] = fs->make<TH2F>( "pt_"    , "pt_"    ,  400,    0.,  400.,     400,   0.,  400.);
  // gen-rec level correlation muon eta
  hists2D_["eta_"] = fs->make<TH2F>( "eta_"   , "eta_"   ,  800,   -4.,    4.,     800,  -4.,    4.);
  // gen-rec level correlation muon phi
  hists2D_["phi_"] = fs->make<TH2F>( "phi_"   , "phi_"   ,  628, -3.14,  3.14,     628,-3.14,  3.14);
}

/// histogram filling with fwlite or full framework
void
MuonCrossSection::fill(const edm::View<reco::Candidate>& muons, const double& weight)
{
  // index for the leading, 2. leading, 3. leading muon to be compared with index_ 
  // from the module config where index_=-1 means 'fill all muons' and index_=n
  // n>=-1 means 'fill only n-th leading muon'
  int index=0;
  for(edm::View<reco::Candidate>::const_iterator muon=muons.begin(); muon!=muons.end(); ++muon, ++index){
    if( index_<0 || index_==index ){
      // make sure charge is of abs value 1
      float charge=muon->charge();
      if(muon->charge()!=0){
	charge=(float)muon->charge()/(float)abs(muon->charge());
      }
      // transverse momentum of the muon
      fill( "pt"    ,  muon->et()  , weight );
      // pseudorapidity of the muon
      fill( "eta"   ,  muon->eta() , weight );
      // azimuth angle of the muon
      fill( "phi"   ,  muon->phi() , weight );
      // fill charge of the muon
      fill( "charge",  0.5*charge  , weight );
      // fill histograms for charged muons
      fill( charged(std::string("pt"),  charge),  muon->et()  , weight );
      // pseudorapidity of the muon
      fill( charged(std::string("eta"), charge),  muon->eta() , weight );
      // azimuth angle of the muon
      fill( charged(std::string("phi"), charge),  muon->phi() , weight );
    }
  }
}

/// histogram filling with fwlite or full framework
void
MuonCrossSection::fill(const edm::View<reco::Candidate>& recs, const edm::View<reco::GenParticle>& gens, const double& weight)
{
  for(edm::View<reco::GenParticle>::const_iterator gen=gens.begin(); gen!=gens.end(); ++gen){
    for(edm::View<reco::Candidate>::const_iterator rec=recs.begin(); rec!=recs.end(); ++rec){
      // transverse momentum of the muon
      hists2D_.find("pt_"  )->second->Fill( gen->pt () ,  rec->pt () , weight );
      // pseudorapidity of the muon
      hists2D_.find("eta_" )->second->Fill( gen->eta() ,  rec->eta() , weight );
      // azimuth angle of the muon
      hists2D_.find("phi_" )->second->Fill( gen->phi(),   rec->phi() , weight );
    }
  }
  // fill 1-dimensional histograms from rec input
  fill(recs, weight);
}
