#include "TopAnalysis/TopAnalyzer/interface/MuonKinematic.h"


/// constructor for FWLite analyzer
MuonKinematic::MuonKinematic():
  jets_()
{ 
}

/// constructor for full FW analyzer
MuonKinematic::MuonKinematic(const edm::ParameterSet& cfg):
  jets_  ( cfg.getParameter<edm::InputTag>( "jets" ) )  
{
}

/// fill interface for full FW analyzer
void
MuonKinematic::fill(const edm::Event& evt, const std::vector<pat::Muon>& muons, const double& weight=1.)
{
  if(muons.begin()==muons.end()) return;
  
  // jet isolation
  edm::Handle<std::vector<pat::Jet> > jets; 
  evt.getByLabel(jets_, jets);
  
  fill(*jets, muons, weight);
}

/// fill interface for FWLite analyzer
void
MuonKinematic::fill(const std::vector<pat::Jet>& jets, 
		    const std::vector<pat::Muon>& muons, const double& weight=1.)
{
  std::vector<pat::Muon>::const_iterator muon=muons.begin();
  if(muon!=muons.end()){
    //---------------------------------------------
    // basic kinematics
    //---------------------------------------------
    en_ ->Fill( muon->energy(), weight );
    pt_ ->Fill( muon->et(),     weight );    
    eta_->Fill( muon->eta(),    weight );
    phi_->Fill( muon->phi(),    weight );

    //---------------------------------------------
    // jet isolation
    //---------------------------------------------
    double minDR   =-1.;
    double minDR_5 =-1.;
    double minDR_10=-1.;
    double minDR_15=-1.;
    double minDR_20=-1.;
    for(std::vector<pat::Jet>::const_iterator jet = jets.begin(); 
	jet!=jets.end(); ++jet) {
      double dR=deltaR(muon->eta(), muon->phi(), jet->eta(), jet->phi());
      if(  minDR   <0 || dR<minDR   )                   minDR   =dR;
      if( (minDR_5 <0 || dR<minDR_5 ) && jet->pt()>5  ) minDR_5 =dR;
      if( (minDR_10<0 || dR<minDR_10) && jet->pt()>10 ) minDR_10=dR;
      if( (minDR_15<0 || dR<minDR_15) && jet->pt()>15 ) minDR_15=dR;
      if( (minDR_20<0 || dR<minDR_20) && jet->pt()>20 ) minDR_20=dR;
    }
    if( minDR   >=0 ) isoJet_  ->Fill( minDR   , weight );
    if( minDR_5 >=0 ) isoJet5_ ->Fill( minDR_5 , weight );
    if( minDR_10>=0 ) isoJet10_->Fill( minDR_10, weight );
    if( minDR_15>=0 ) isoJet15_->Fill( minDR_15, weight );
    if( minDR_20>=0 ) isoJet20_->Fill( minDR_20, weight );
    
    //---------------------------------------------
    // track & calo isolation
    //---------------------------------------------
    const pat::IsoDeposit *trackDep=0, *ecalDep=0, *hcalDep=0;  
    trackDep = muon->trackerIsoDeposit();
    ecalDep  = muon->ecalIsoDeposit();
    hcalDep  = muon->hcalIsoDeposit();
    
    // fill profiles
    double dR=-0.1;
    for(unsigned idx=0; idx<42; ++idx){
      dR+=0.05;
      dRCalN_ ->Fill(dR, hcalDep ->depositAndCountWithin(dR).second );
      dRCalPt_->Fill(dR, hcalDep ->depositAndCountWithin(dR).first  );
      dRTrkN_ ->Fill(dR, trackDep->depositAndCountWithin(dR).second );
      dRTrkPt_->Fill(dR, trackDep->depositAndCountWithin(dR).first  );
    }
    // fill summed deposits 
    double stdDR = 0.3;
    double stdThreshold = 0.3;
    isoCalN_ ->Fill( hcalDep->depositAndCountWithin(stdDR, reco::MuIsoDeposit::Vetos(), stdThreshold).second, weight );
    isoTrkN_ ->Fill( hcalDep->depositAndCountWithin(stdDR, reco::MuIsoDeposit::Vetos(), stdThreshold).second, weight );
    isoTrkPt_->Fill( muon->trackIso(), weight );
    isoCalPt_->Fill( muon->caloIso (), weight );

    // fill correlation plots   
    ptVsTrkIso_ ->Fill( muon->pt(), muon->trackIso() );
    ptVsCalIso_ ->Fill( muon->pt(), muon->caloIso () );
  }
}

/// book for FWLite
void 
MuonKinematic::book()
{
  NameScheme kin("kin");
  en_ = new TH1F(kin.name( "en"  ), kin.name("en"  ), 60,   0., 300.);
  pt_ = new TH1F(kin.name( "pt"  ), kin.name("pt"  ), 30,   0., 150.);
  eta_= new TH1F(kin.name( "eta" ), kin.name("eta" ), 35, -3.5,  3.5);
  phi_= new TH1F(kin.name( "phi" ), kin.name("phi" ), 35, -3.5,  3.5);

  NameScheme iso("iso");
  isoJet_    = new TH1F(iso.name( "isoJet"  ), iso.name("isoJet"  ), 80,   0.,  4.);
  isoJet5_   = new TH1F(iso.name( "isoJet5" ), iso.name("isoJet5" ), 80,   0.,  4.);
  isoJet10_  = new TH1F(iso.name( "isoJet10"), iso.name("isoJet10"), 80,   0.,  4.);
  isoJet15_  = new TH1F(iso.name( "isoJet15"), iso.name("isoJet15"), 80,   0.,  4.);
  isoJet20_  = new TH1F(iso.name( "isoJet20"), iso.name("isoJet20"), 80,   0.,  4.);
  isoTrkPt_  = new TH1F(iso.name( "isoTrkPt"), iso.name("isoTrkPt"), 60,  -1.,  5.);
  isoCalPt_  = new TH1F(iso.name( "isoCalPt"), iso.name("isoCalPt"), 40, -10., 30.);
  isoTrkN_   = new TH1F(iso.name( "isoTrkN" ), iso.name("isoTrkN" ), 21,  -1., 20.);
  isoCalN_   = new TH1F(iso.name( "isoCalN" ), iso.name("isoCaloN"), 31,  -1., 30.);
  dRTrkPt_   = new TH1F(iso.name( "dRTrkPt" ), iso.name("dRTrkPt" ), 42, -0.1,  2.);
  dRTrkN_    = new TH1F(iso.name( "dRTrkN"  ), iso.name("dRTrkN"  ), 42, -0.1,  2.);
  dRCalPt_   = new TH1F(iso.name( "dRCalPt" ), iso.name("dRCalPt" ), 42, -0.1,  2.);
  dRCalN_    = new TH1F(iso.name( "dRCalN"  ), iso.name("dRCalN"  ), 42, -0.1,  2.);

  ptVsTrkIso_ = new TH2F(iso.name( "ptVsTrkIso" ), iso.name( "ptVsTrkIso" ), 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = new TH2F(iso.name( "ptVsCalIso" ), iso.name( "ptVsCalIso" ), 100, 0., 100., 50, -10., 25.);
}

/// book for full FW
void 
MuonKinematic::book(edm::Service<TFileService>& fs)
{
  NameScheme kin("kin");
  en_ = fs->make<TH1F>(kin.name( "en"  ), kin.name("en"  ), 60,   0., 300.);
  pt_ = fs->make<TH1F>(kin.name( "pt"  ), kin.name("pt"  ), 30,   0., 150.);
  eta_= fs->make<TH1F>(kin.name( "eta" ), kin.name("eta" ), 35, -3.5,  3.5);
  phi_= fs->make<TH1F>(kin.name( "phi" ), kin.name("phi" ), 35, -3.5,  3.5);

  NameScheme iso("iso");
  isoJet_  = fs->make<TH1F>(iso.name( "isoJet"  ), iso.name("isoJet"  ), 80,   0.,  4.);
  isoJet5_ = fs->make<TH1F>(iso.name( "isoJet5" ), iso.name("isoJet5" ), 80,   0.,  4.);
  isoJet10_= fs->make<TH1F>(iso.name( "isoJet10"), iso.name("isoJet10"), 80,   0.,  4.);
  isoJet15_= fs->make<TH1F>(iso.name( "isoJet15"), iso.name("isoJet15"), 80,   0.,  4.);
  isoJet20_= fs->make<TH1F>(iso.name( "isoJet20"), iso.name("isoJet20"), 80,   0.,  4.);
  isoTrkPt_= fs->make<TH1F>(iso.name( "isoTrkPt"), iso.name("isoTrkPt"), 60,  -1.,  5.);
  isoCalPt_= fs->make<TH1F>(iso.name( "isoCalPt"), iso.name("isoCalPt"), 40, -10., 30.);
  isoTrkN_ = fs->make<TH1F>(iso.name( "isoTrkN" ), iso.name("isoTrkN" ), 21,  -1., 20.);
  isoCalN_ = fs->make<TH1F>(iso.name( "isoCalN" ), iso.name("isoCaloN"), 31,  -1., 30.);
  dRTrkPt_ = fs->make<TH1F>(iso.name( "dRTrkPt" ), iso.name("dRTrkPt" ), 42, -0.1,  2.);
  dRTrkN_  = fs->make<TH1F>(iso.name( "dRTrkN"  ), iso.name("dRTrkN"  ), 42, -0.1,  2.);
  dRCalPt_ = fs->make<TH1F>(iso.name( "dRCalPt" ), iso.name("dRCalPt" ), 42, -0.1,  2.);
  dRCalN_  = fs->make<TH1F>(iso.name( "dRCalN"  ), iso.name("dRCalN"  ), 42, -0.1,  2.);

  ptVsTrkIso_ = fs->make<TH2F>(iso.name( "ptVsTrkIso" ), iso.name( "ptVsTrkIso" ), 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = fs->make<TH2F>(iso.name( "ptVsCalIso" ), iso.name( "ptVsCalIso" ), 100, 0., 100., 50, -10., 25.);
}

/// book for full FW with output stream
void 
MuonKinematic::book(edm::Service<TFileService>& fs, ofstream& file)
{
  NameScheme kin("kin");
  en_ = fs->make<TH1F>(kin.name( file, "en"  ), kin.name("en"  ), 60,   0., 300.);
  pt_ = fs->make<TH1F>(kin.name( file, "pt"  ), kin.name("pt"  ), 30,   0., 150.);
  eta_= fs->make<TH1F>(kin.name( file, "eta" ), kin.name("eta" ), 35, -3.5,  3.5);
  phi_= fs->make<TH1F>(kin.name( file, "phi" ), kin.name("phi" ), 35, -3.5,  3.5);

  NameScheme iso("iso");
  isoJet_  = fs->make<TH1F>(iso.name( file, "isoJet"  ), iso.name("isoJet"  ), 80,   0.,  4.);
  isoJet5_ = fs->make<TH1F>(iso.name( file, "isoJet5" ), iso.name("isoJet5" ), 80,   0.,  4.);
  isoJet10_= fs->make<TH1F>(iso.name( file, "isoJet10"), iso.name("isoJet10"), 80,   0.,  4.);
  isoJet15_= fs->make<TH1F>(iso.name( file, "isoJet15"), iso.name("isoJet15"), 80,   0.,  4.);
  isoJet20_= fs->make<TH1F>(iso.name( file, "isoJet20"), iso.name("isoJet20"), 80,   0.,  4.);
  isoTrkPt_= fs->make<TH1F>(iso.name( file, "isoTrkPt"), iso.name("isoTrkPt"), 60,  -1.,  5.);
  isoCalPt_= fs->make<TH1F>(iso.name( file, "isoCalPt"), iso.name("isoCalPt"), 40, -10., 30.);
  isoTrkN_ = fs->make<TH1F>(iso.name( file, "isoTrkN" ), iso.name("isoTrkN" ), 21,  -1., 20.);
  isoCalN_ = fs->make<TH1F>(iso.name( file, "isoCalN" ), iso.name("isoCaloN"), 31,  -1., 30.);
  dRTrkPt_ = fs->make<TH1F>(iso.name( file, "dRTrkPt" ), iso.name("dRTrkPt" ), 42, -0.1,  2.);
  dRTrkN_  = fs->make<TH1F>(iso.name( file, "dRTrkN"  ), iso.name("dRTrkN"  ), 42, -0.1,  2.);
  dRCalPt_ = fs->make<TH1F>(iso.name( file, "dRCalPt" ), iso.name("dRCalPt" ), 42, -0.1,  2.);
  dRCalN_  = fs->make<TH1F>(iso.name( file, "dRCalN"  ), iso.name("dRCalN"  ), 42, -0.1,  2.);

  ptVsTrkIso_ = fs->make<TH2F>(iso.name( "ptVsTrkIso" ), iso.name( "ptVsTrkIso" ), 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = fs->make<TH2F>(iso.name( "ptVsCalIso" ), iso.name( "ptVsCalIso" ), 100, 0., 100., 50, -10., 25.);
}

/// write to file and free allocated space for FWLite
void 
MuonKinematic::write(const char* filename, const char* directory)
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
  isoJet5_ ->Write( );
  isoJet10_->Write( );
  isoJet15_->Write( );
  isoJet20_->Write( );
  isoTrkPt_->Write( );
  isoCalPt_->Write( );
  isoTrkN_ ->Write( );
  isoCalN_ ->Write( );
  dRTrkPt_ ->Write( );
  dRTrkN_  ->Write( );
  dRCalPt_ ->Write( );
  dRCalN_  ->Write( );

  /// correlations
  ptVsTrkIso_ ->Write( );
  ptVsCalIso_ ->Write( );

  outFile.Close();

  // free allocated space
  delete en_;
  delete pt_;
  delete eta_;
  delete phi_;

  /// isolation
  delete isoJet_;
  delete isoJet5_;
  delete isoJet10_;
  delete isoJet15_;
  delete isoJet20_;
  delete isoTrkPt_;
  delete isoCalPt_;
  delete isoTrkN_;
  delete isoCalN_;
  delete dRTrkPt_;
  delete dRTrkN_;
  delete dRCalPt_;
  delete dRCalN_;

  /// correlations
  delete ptVsTrkIso_;
  delete ptVsCalIso_;
}
