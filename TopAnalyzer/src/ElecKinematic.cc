#include "TopAnalysis/TopAnalyzer/interface/ElecKinematic.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"


ElecKinematic::ElecKinematic(const edm::ParameterSet& cfg):
  towers_( cfg.getParameter<edm::InputTag>( "towers" ) ),
  tracks_( cfg.getParameter<edm::InputTag>( "tracks" ) ),  
  dRMax_ ( cfg.getParameter<double>( "dRMax" ) )  
{
}

void
ElecKinematic::fill(const edm::Event& evt, const std::vector<pat::Electron>& elecs, const double& weight=1.)
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
    // calo isolation
    //---------------------------------------------
    edm::Handle<reco::CandidateCollection> towers;
    evt.getByLabel(towers_, towers);
    
    //---------------------------------------------
    // count number of towers in cone
    //---------------------------------------------
    int nTowers = 0;
    for(reco::CandidateCollection::const_iterator tower = towers->begin(); 
	tower != towers->end(); ++tower) {
      double dR=deltaR( elec->eta(), elec->phi(), tower->eta(), tower->phi() );
      dRCalN_ ->Fill(dR);
      dRCalPt_->Fill(dR, tower->et());
      if(dR<dRMax_)++nTowers;
    }
    isoCalN_->Fill(nTowers, weight);
    
    //---------------------------------------------
    // track isolation
    //---------------------------------------------
    edm::Handle<reco::TrackCollection> tracks;
    evt.getByLabel(tracks_, tracks);
    
    //---------------------------------------------
    // search for track closest to the electron 
    //---------------------------------------------
    double dRmin = -1.;
    for(reco::TrackCollection::const_iterator track = tracks->begin(); 
	track != tracks->end(); ++track) {
      double dR=deltaR( elec->eta(), elec->phi(), track->eta(), track->phi() );
      if(dRmin<0 || dR<dRmin) dRmin=dR;
    }
    closestCtf_->Fill(dRmin);
    
    //---------------------------------------------
    // count number of tracks in cone
    //---------------------------------------------
    int nTracks = 0;
    for(reco::TrackCollection::const_iterator track = tracks->begin(); 
	track != tracks->end(); ++track) {
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

void 
ElecKinematic::book()
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  NameScheme kin("kin");
  en_ = fs->make<TH1F>(kin.name( "en"  ), kin.name("en"  ), 60,   0., 300.);
  pt_ = fs->make<TH1F>(kin.name( "pt"  ), kin.name("pt"  ), 30,   0., 150.);
  eta_= fs->make<TH1F>(kin.name( "eta" ), kin.name("eta" ), 35, -3.5,  3.5);
  phi_= fs->make<TH1F>(kin.name( "phi" ), kin.name("phi" ), 35, -3.5,  3.5);

  NameScheme iso("iso");
  isoTrk_  = fs->make<TH1F>(iso.name( "isoTrk"  ), iso.name("isoTrk"  ), 60,  -1.,   5.);
  isoCal_  = fs->make<TH1F>(iso.name( "isoCal"  ), iso.name("isoCal"  ), 40, -10.,  30.);
  isoEcal_ = fs->make<TH1F>(iso.name( "isoEcal" ), iso.name("isoEcal" ), 40, -10.,  30.);
  isoHcal_ = fs->make<TH1F>(iso.name( "isoHcal" ), iso.name("isoHcal" ), 40, -10.,  30.);
  dRTrkPt_ = fs->make<TH1F>(iso.name( "dRTrkPt" ), iso.name("dRTrkPt" ), 42, -0.1,   2.);
  dRTrkN_  = fs->make<TH1F>(iso.name( "dRTrkN"  ), iso.name("dRTrkN"  ), 42, -0.1,   2.);
  dRCalPt_ = fs->make<TH1F>(iso.name( "dRCalPt" ), iso.name("dRCalPt" ), 42, -0.1,   2.);
  dRCalN_  = fs->make<TH1F>(iso.name( "dRCalN"  ), iso.name("dRCalN"  ), 42, -0.1,   2.);
  isoTrkN_ = fs->make<TH1F>(iso.name( "isoTrkN" ), iso.name("isoTrkN" ), 21,  -1.,  20.);
  isoCalN_ = fs->make<TH1F>(iso.name( "isoCalN" ), iso.name("isoCaloN"), 31,  -1.,  30.);
  closestCtf_= fs->make<TH1F>(iso.name( "closestCtf" ), iso.name("closestCtf" ), 20, 0., 0.2);

  ptVsTrkIso_ = fs->make<TH2F>(iso.name( "ptVsTrkIso" ), iso.name( "ptVsTrkIso" ), 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = fs->make<TH2F>(iso.name( "ptVsCalIso" ), iso.name( "ptVsCalIso" ), 100, 0., 100., 50, -10., 25.);
  ptVsEcalIso_= fs->make<TH2F>(iso.name( "ptVsEcalIso"), iso.name( "ptVsEcalIso"), 100, 0., 100., 50, -10., 25.);
  ptVsHcalIso_= fs->make<TH2F>(iso.name( "ptVsHcalIso"), iso.name( "ptVsHcalIso"), 100, 0., 100., 50, -10., 25.);
}

void 
ElecKinematic::book(ofstream& file)
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  NameScheme kin("kin");
  en_ = fs->make<TH1F>(kin.name( file, "en"  ), kin.name("en"  ), 60,   0., 300.);
  pt_ = fs->make<TH1F>(kin.name( file, "pt"  ), kin.name("pt"  ), 30,   0., 150.);
  eta_= fs->make<TH1F>(kin.name( file, "eta" ), kin.name("eta" ), 35, -3.5,  3.5);
  phi_= fs->make<TH1F>(kin.name( file, "phi" ), kin.name("phi" ), 35, -3.5,  3.5);

  NameScheme iso("iso");
  isoTrk_  = fs->make<TH1F>(iso.name( file, "isoTrk"  ), iso.name("isoTrk"  ), 60,  -1.,   5.);
  isoCal_  = fs->make<TH1F>(iso.name( file, "isoCal"  ), iso.name("isoCal"  ), 40, -10.,  30.);
  isoEcal_ = fs->make<TH1F>(iso.name( file, "isoEcal" ), iso.name("isoEcal" ), 40, -10.,  30.);
  isoHcal_ = fs->make<TH1F>(iso.name( file, "isoHcal" ), iso.name("isoHcal" ), 40, -10.,  30.);
  dRTrkPt_ = fs->make<TH1F>(iso.name( file, "dRTrkPt" ), iso.name("dRTrkPt" ), 42, -0.1,   2.);
  dRTrkN_  = fs->make<TH1F>(iso.name( file, "dRTrkN"  ), iso.name("dRTrkN"  ), 42, -0.1,   2.);
  dRCalPt_ = fs->make<TH1F>(iso.name( file, "dRCalPt" ), iso.name("dRCalPt" ), 42, -0.1,   2.);
  dRCalN_  = fs->make<TH1F>(iso.name( file, "dRCalN"  ), iso.name("dRCalN"  ), 42, -0.1,   2.);
  isoTrkN_ = fs->make<TH1F>(iso.name( file, "isoTrkN" ), iso.name("isoTrkN" ), 21,  -1.,  20.);
  isoCalN_ = fs->make<TH1F>(iso.name( file, "isoCalN" ), iso.name("isoCaloN"), 31,  -1.,  30.);
  closestCtf_= fs->make<TH1F>(iso.name( file, "closestCtf" ), iso.name("closestCtf" ), 20, 0., 0.2);

  ptVsTrkIso_ = fs->make<TH2F>(iso.name( "ptVsTrkIso" ), iso.name( "ptVsTrkIso" ), 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = fs->make<TH2F>(iso.name( "ptVsCalIso" ), iso.name( "ptVsCalIso" ), 100, 0., 100., 50, -10., 25.);
  ptVsEcalIso_= fs->make<TH2F>(iso.name( "ptVsEcalIso"), iso.name( "ptVsEcalIso"), 100, 0., 100., 50, -10., 25.);
  ptVsHcalIso_= fs->make<TH2F>(iso.name( "ptVsHcalIso"), iso.name( "ptVsHcalIso"), 100, 0., 100., 50, -10., 25.);
}
