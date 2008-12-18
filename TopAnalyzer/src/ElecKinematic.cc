#include "TopAnalysis/TopAnalyzer/interface/ElecKinematic.h"


/// constructor for FWLite analyzer
ElecKinematic::ElecKinematic(double dRMax):
  jets_(), towers_(), tracks_(), dRMax_(dRMax)
{ 
}

/// constructor for full FW analyzer
ElecKinematic::ElecKinematic(const edm::ParameterSet& cfg):
  jets_  ( cfg.getParameter<edm::InputTag>( "jets" ) ),
  towers_( cfg.getParameter<edm::InputTag>( "towers" ) ),
  tracks_( cfg.getParameter<edm::InputTag>( "tracks" ) ),  
  dRMax_ ( cfg.getParameter<double>( "dRMax" ) )  
{
}

/// fill interface for full FW analyzer
void
ElecKinematic::fill(const edm::Event& evt, const std::vector<pat::Electron>& elecs, const double& weight=1.)
{
  if(elecs.begin()==elecs.end()) return;

  // jet isolation
  edm::Handle<std::vector<pat::Jet> > jets; 
  evt.getByLabel(jets_, jets);

  // track isolation
  edm::Handle<reco::TrackCollection> tracks;
  evt.getByLabel(tracks_, tracks);

  // calo isolation
  edm::Handle<CaloTowerCollection> towers;
  evt.getByLabel(towers_, towers);

  fill(*jets, *tracks, *towers, elecs, weight);  
}

/// fill interface for FWLite analyzer
void
ElecKinematic::fill(const std::vector<pat::Jet>& jets, 
		    const reco::TrackCollection& tracks, 
		    const CaloTowerCollection& towers,
		    const std::vector<pat::Electron>& elecs, const double& weight=1.)
{
  std::vector<pat::Electron>::const_iterator elec=elecs.begin();
  if(elec!=elecs.end()){
    //---------------------------------------------
    // basic kinematics
    //---------------------------------------------
    en_ ->Fill( elec->energy(), weight );
    pt_ ->Fill( elec->et(),     weight );    
    eta_->Fill( elec->eta(),    weight );
    phi_->Fill( elec->phi(),    weight );
    
    //---------------------------------------------
    // jet isolation
    //---------------------------------------------
    double minDR=-1.;
    for(std::vector<pat::Jet>::const_iterator jet = jets.begin(); 
	jet!=jets.end(); ++jet) {
      double dR=deltaR(elec->eta(), elec->phi(), jet->eta(), jet->phi());
      if( minDR<0 || dR<minDR ) minDR=dR;
    }
    if( minDR>=0 )
      isoJet_->Fill( minDR, weight );  
    
    //---------------------------------------------
    // calo isolation
    //---------------------------------------------

    // count number of towers in cone
    int nTowers = 0;
    for(CaloTowerCollection::const_iterator tower = towers.begin(); 
	tower != towers.end(); ++tower) {
      double dR=deltaR( elec->eta(), elec->phi(), tower->eta(), tower->phi() );
      dRCalN_ ->Fill(dR);
      dRCalPt_->Fill(dR, tower->et());
      if(dR<dRMax_)++nTowers;
    }
    isoCalN_->Fill(nTowers, weight);
    
    //---------------------------------------------
    // track isolation
    //---------------------------------------------

    // search for track closest to the electron 
    double dRmin = -1.;
    for(reco::TrackCollection::const_iterator track = tracks.begin(); 
	track != tracks.end(); ++track) {
      double dR=deltaR( elec->eta(), elec->phi(), track->eta(), track->phi() );
      if(dRmin<0 || dR<dRmin) dRmin=dR;
    }
    closestCtf_->Fill(dRmin);
    
    // count number of tracks in cone
    int nTracks = 0;
    for(reco::TrackCollection::const_iterator track = tracks.begin(); 
	track != tracks.end(); ++track) {
      double dR=deltaR( elec->eta(), elec->phi(), track->eta(), track->phi() );
      if( dR==dRmin) 
	continue;
      dRTrkN_->Fill(dR);
      if(track->pt()<100.)
	dRTrkPt_->Fill(dR, track->pt());    
      if(dR<dRMax_) ++nTracks;
    }
    isoTrkN_->Fill(nTracks, weight);
    
    //---------------------------------------------
    // fill std isolation plots
    //---------------------------------------------
    isoTrk_ ->Fill( elec->trackIso(), weight );
    isoCal_ ->Fill( elec->caloIso (), weight );
    isoEcal_->Fill( elec->ecalIso (), weight );
    isoHcal_->Fill( elec->hcalIso (), weight );
    
    ptVsTrkIso_ ->Fill( elec->pt(), elec->trackIso() );
    ptVsCalIso_ ->Fill( elec->pt(), elec->caloIso () );
    ptVsEcalIso_->Fill( elec->pt(), elec->ecalIso () );
    ptVsHcalIso_->Fill( elec->pt(), elec->hcalIso () );
  }
}

/// book for FWLite
void 
ElecKinematic::book()
{
  NameScheme kin("kin");
  en_ = new TH1F(kin.name("en" ), "en" , 60,   0., 300.);
  pt_ = new TH1F(kin.name("pt" ), "pt" , 30,   0., 150.);
  eta_= new TH1F(kin.name("eta"), "eta", 35, -3.5,  3.5);
  phi_= new TH1F(kin.name("phi"), "phi", 35, -3.5,  3.5);

  NameScheme iso("iso");
  isoJet_    = new TH1F(iso.name("isoJet"    ), "isoJet"    , 60,   0., 1.5);
  closestCtf_= new TH1F(iso.name("closestCtf"), "closestCtf", 20,   0., 0.2);
  isoTrk_    = new TH1F(iso.name("isoTrk"    ), "isoTrk"    , 60,  -1.,  5.);
  isoCal_    = new TH1F(iso.name("isoCal"    ), "isoCal"    , 40, -10., 30.);
  isoEcal_   = new TH1F(iso.name("isoEcal"   ), "isoEcal"   , 40, -10., 30.);
  isoHcal_   = new TH1F(iso.name("isoHcal"   ), "isoHcal"   , 40, -10., 30.);
  isoTrkN_   = new TH1F(iso.name("isoTrkN"   ), "isoTrkN"   , 21,  -1., 20.);
  isoCalN_   = new TH1F(iso.name("isoCalN"   ), "isoCaloN"  , 31,  -1., 30.);
  dRTrkPt_   = new TH1F(iso.name("dRTrkPt"   ), "dRTrkPt"   , 42, -0.1,  2.);
  dRTrkN_    = new TH1F(iso.name("dRTrkN"    ), "dRTrkN"    , 42, -0.1,  2.);
  dRCalPt_   = new TH1F(iso.name("dRCalPt"   ), "dRCalPt"   , 42, -0.1,  2.);
  dRCalN_    = new TH1F(iso.name("dRCalN"    ), "dRCalN"    , 42, -0.1,  2.);

  NameScheme iso2d("iso2d");
  ptVsTrkIso_ = new TH2F(iso2d.name("ptVsTrkIso" ), "ptVsTrkIso" , 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = new TH2F(iso2d.name("ptVsCalIso" ), "ptVsCalIso" , 100, 0., 100., 50, -10., 25.);
  ptVsEcalIso_= new TH2F(iso2d.name("ptVsEcalIso"), "ptVsEcalIso", 100, 0., 100., 50, -10., 25.);
  ptVsHcalIso_= new TH2F(iso2d.name("ptVsHcalIso"), "ptVsHcalIso", 100, 0., 100., 50, -10., 25.);
}

/// book for full FW
void 
ElecKinematic::book(edm::Service<TFileService>& fs)
{
  NameScheme kin("kin");
  en_ = fs->make<TH1F>(kin.name("en" ), "E(electron) [GeV]"    , 60,   0., 300.);
  pt_ = fs->make<TH1F>(kin.name("pt" ), "p_{T}(electron) [GeV]", 30,   0., 150.);
  eta_= fs->make<TH1F>(kin.name("eta"), "#eta(electron)"       , 35, -3.5,  3.5);
  phi_= fs->make<TH1F>(kin.name("phi"), "#phi(electron)"       , 35, -3.5,  3.5);

  NameScheme iso("iso");
  isoJet_    = fs->make<TH1F>(iso.name("isoJet"    ), "smallest dR(electron,jet))"               , 60,   0.,  1.5);
  closestCtf_= fs->make<TH1F>(iso.name("closestCtf"), "smallest dR(electron,track)"              , 20,   0.,  0.2);
  isoTrk_    = fs->make<TH1F>(iso.name("isoTrk"    ), "#Sigma_{#delta R<0.3}(p_{T}(track))"      , 60,  -1.,   5.);
  isoCal_    = fs->make<TH1F>(iso.name("isoCal"    ), "#Sigma_{#delta R<0.3}(E_{T}(tower))"      , 40, -10.,  30.);
  isoEcal_   = fs->make<TH1F>(iso.name("isoEcal"   ), "#Sigma_{#delta R<0.3}(E_{T}^{em}(tower))" , 40, -10.,  30.);
  isoHcal_   = fs->make<TH1F>(iso.name("isoHcal"   ), "#Sigma_{#delta R<0.3}(E_{T}^{had}(tower))", 40, -10.,  30.);
  isoTrkN_   = fs->make<TH1F>(iso.name("isoTrkN"   ), "N_{track}^{dR<0.3}"                       , 21,  -1.,  20.);
  isoCalN_   = fs->make<TH1F>(iso.name("isoCalN"   ), "N_{tower}^{dR<0.3}"                       , 31,  -1.,  30.);
  dRTrkPt_   = fs->make<TH1F>(iso.name("dRTrkPt"   ), "dR(electron,track)"                       , 42, -0.1,   2.);
  dRTrkN_    = fs->make<TH1F>(iso.name("dRTrkN"    ), "dR(electron,track)"                       , 42, -0.1,   2.);
  dRCalPt_   = fs->make<TH1F>(iso.name("dRCalPt"   ), "dR(electron,tower)"                       , 42, -0.1,   2.);
  dRCalN_    = fs->make<TH1F>(iso.name("dRCalN"    ), "dR(electron,tower)"                       , 42, -0.1,   2.);

  NameScheme iso2d("iso2d");
  ptVsTrkIso_ = fs->make<TH2F>(iso2d.name("ptVsTrkIso" ), "ptVsTrkIso" , 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = fs->make<TH2F>(iso2d.name("ptVsCalIso" ), "ptVsCalIso" , 100, 0., 100., 50, -10., 25.);
  ptVsEcalIso_= fs->make<TH2F>(iso2d.name("ptVsEcalIso"), "ptVsEcalIso", 100, 0., 100., 50, -10., 25.);
  ptVsHcalIso_= fs->make<TH2F>(iso2d.name("ptVsHcalIso"), "ptVsHcalIso", 100, 0., 100., 50, -10., 25.);
}

/// book for full FW with output stream
void 
ElecKinematic::book(edm::Service<TFileService>& fs, ofstream& file)
{
  NameScheme kin("kin");
  en_ = fs->make<TH1F>(kin.name(file, "en" ), "E(electron) [GeV]"    , 60,   0., 300.);
  pt_ = fs->make<TH1F>(kin.name(file, "pt" ), "p_{T}(electron) [GeV]", 30,   0., 150.);
  eta_= fs->make<TH1F>(kin.name(file, "eta"), "#eta(electron)"       , 35, -3.5,  3.5);
  phi_= fs->make<TH1F>(kin.name(file, "phi"), "#phi(electron)"       , 35, -3.5,  3.5);

  NameScheme iso("iso");
  isoJet_    = fs->make<TH1F>(iso.name(file, "isoJet"    ), "smallest dR(electron,jet))"               , 60,   0.,  1.5);
  closestCtf_= fs->make<TH1F>(iso.name(file, "closestCtf"), "smallest dR(electron,track)"              , 20,   0.,  0.2);
  isoTrk_    = fs->make<TH1F>(iso.name(file, "isoTrk"    ), "#Sigma_{#delta R<0.3}(p_{t}(track))"      , 60,  -1.,   5.);
  isoCal_    = fs->make<TH1F>(iso.name(file, "isoCal"    ), "#Sigma_{#delta R<0.3}(E_{t}(tower))"      , 40, -10.,  30.);
  isoEcal_   = fs->make<TH1F>(iso.name(file, "isoEcal"   ), "#Sigma_{#delta R<0.3}(E_{t}^{em}(tower))" , 40, -10.,  30.);
  isoHcal_   = fs->make<TH1F>(iso.name(file, "isoHcal"   ), "#Sigma_{#delta R<0.3}(E_{t}^{had}(tower))", 40, -10.,  30.);
  isoTrkN_   = fs->make<TH1F>(iso.name(file, "isoTrkN"   ), "N_{track}^{dR<0.3}"                       , 21,  -1.,  20.);
  isoCalN_   = fs->make<TH1F>(iso.name(file, "isoCalN"   ), "N_{tower}^{dR<0.3}"                       , 31,  -1.,  30.);
  dRTrkPt_   = fs->make<TH1F>(iso.name(file, "dRTrkPt"   ), "dR(electron,track)"                       , 42, -0.1,   2.);
  dRTrkN_    = fs->make<TH1F>(iso.name(file, "dRTrkN"    ), "dR(electron,track)"                       , 42, -0.1,   2.);
  dRCalPt_   = fs->make<TH1F>(iso.name(file, "dRCalPt"   ), "dR(electron,tower)"                       , 42, -0.1,   2.);
  dRCalN_    = fs->make<TH1F>(iso.name(file, "dRCalN"    ), "dR(electron,tower)"                       , 42, -0.1,   2.);

  NameScheme iso2d("iso2d");
  ptVsTrkIso_ = fs->make<TH2F>(iso2d.name(file, "ptVsTrkIso" ), "ptVsTrkIso" , 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = fs->make<TH2F>(iso2d.name(file, "ptVsCalIso" ), "ptVsCalIso" , 100, 0., 100., 50, -10., 25.);
  ptVsEcalIso_= fs->make<TH2F>(iso2d.name(file, "ptVsEcalIso"), "ptVsEcalIso", 100, 0., 100., 50, -10., 25.);
  ptVsHcalIso_= fs->make<TH2F>(iso2d.name(file, "ptVsHcalIso"), "ptVsHcalIso", 100, 0., 100., 50, -10., 25.);
}

/// write to file and free allocated space for FWLite
void 
ElecKinematic::write(const char* filename, const char* directory)
{
  /// save histograms to file
  TFile outFile( filename, "recreate" );
  outFile.mkdir( directory );
  outFile.cd( directory );

  /// basic kinematic
  en_ ->Write( );
  pt_ ->Write( );
  eta_->Write( );
  phi_->Write( );

  /// isolation
  isoJet_  ->Write( );
  isoTrk_  ->Write( );
  isoCal_  ->Write( );
  isoEcal_ ->Write( );
  isoHcal_ ->Write( );
  dRTrkPt_ ->Write( );
  dRTrkN_  ->Write( );
  dRCalPt_ ->Write( );
  dRCalN_  ->Write( );
  closestCtf_->Write( );

  /// correlations
  ptVsTrkIso_ ->Write( );
  ptVsCalIso_ ->Write( );
  ptVsEcalIso_->Write( );
  ptVsHcalIso_->Write( );

  outFile.Close();

  // free allocated space
  delete en_;
  delete pt_;
  delete eta_;
  delete phi_;

  /// isolation
  delete isoJet_;
  delete isoTrk_;
  delete isoCal_;
  delete isoEcal_;
  delete isoHcal_;
  delete dRTrkPt_;
  delete dRTrkN_;
  delete dRCalPt_;
  delete dRCalN_;
  delete closestCtf_;

  /// correlations
  delete ptVsTrkIso_;
  delete ptVsCalIso_;
  delete ptVsEcalIso_;
  delete ptVsHcalIso_;
}
