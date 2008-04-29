#include "TopAnalysis/TopAnalyzer/interface/ElecId.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

ElecId::ElecId(const edm::ParameterSet& cfg):
  bshp_( cfg.getParameter<edm::InputTag>( "barrel_shape" ) ),
  eshp_( cfg.getParameter<edm::InputTag>( "endcap_shape" ) )  
{
}

void
ElecId::fill(const edm::Event& evt, const std::vector<pat::Electron>& elecs, const double& weight=1.)
{
  std::vector<pat::Electron>::const_iterator elec=elecs.begin();
  if(elec!=elecs.end()){
    eops_->Fill( elec->eSuperClusterOverP(),             weight );
    eopb_->Fill( elec->eSeedClusterOverPout(),           weight );
    nocl_->Fill( elec->numberOfClusters(),               weight );
    hoem_->Fill( TMath::Log10( elec->hadronicOverEm() ), weight );
    deta_->Fill( elec->deltaEtaSeedClusterTrackAtCalo(), weight );
    dphi_->Fill( elec->deltaPhiSeedClusterTrackAtCalo(), weight );
    
    reco::GsfTrackRef track = elec->gsfTrack();
    reco::Particle::Vector iMom = track->innerMomentum();
    reco::Particle::Vector oMom = track->outerMomentum();
    
    tdpt_ ->Fill( (iMom.Rho()-oMom.Rho())/iMom.Rho(), weight );
    tdeta_->Fill( (iMom.Eta()-oMom.Eta())/iMom.Eta(), weight );
    tdphi_->Fill( (iMom.Phi()-oMom.Phi())/iMom.Phi(), weight );
    nohit_->Fill( track->recHitsSize(),               weight );
    nvhit_->Fill( track->found(),                     weight );
    chi2_ ->Fill( track->chi2()/track->ndof(),        weight );
    
    reco::SuperClusterRef clus = elec->superCluster();
    math::XYZPoint tPos(elec->TrackPositionAtCalo().X(), 
			elec->TrackPositionAtCalo().Y(),
			elec->TrackPositionAtCalo().Z());
    
    drtk_->Fill( (clus->position()-tPos).R(), weight );  
    
    edm::Handle<reco::BasicClusterShapeAssociationCollection> barrel, endcap;
    evt.getByLabel(bshp_, barrel);
    evt.getByLabel(eshp_, endcap);
    
    reco::BasicClusterShapeAssociationCollection::const_iterator shapes;
    
    // find the entry in the map corresponding to
    // the seed BasicCluster of the SuperCluster
    DetId id = clus->seed()->getHitsByDetId()[0];
    if (id.subdetId() == EcalBarrel) {
      shapes = barrel->find(clus->seed());
    }
    else {
      shapes = endcap->find(clus->seed());
    }
    
    const reco::ClusterShapeRef& shp = shapes->val;
    s1os9_->Fill( shp->eMax()/shp->e3x3(), weight );
  }
}

void 
ElecId::book()
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  NameScheme id("id");
  eops_ = fs->make<TH1F>(id.name("eops" ), id.name("eops" ), 50,   0.,   5.);
  eopb_ = fs->make<TH1F>(id.name("eopb" ), id.name("eopb" ), 50,   0.,   5.);
  nocl_ = fs->make<TH1F>(id.name("nocl" ), id.name("nocl" ), 20,   0.,  20.);
  deta_ = fs->make<TH1F>(id.name("deta" ), id.name("deta" ), 40,-0.02, 0.02);
  dphi_ = fs->make<TH1F>(id.name("dphi" ), id.name("dphi" ), 40,-0.02, 0.02);
  hoem_ = fs->make<TH1F>(id.name("hoem" ), id.name("hoem" ), 50,  -5.,   0.);
  tdpt_ = fs->make<TH1F>(id.name("tdpt" ), id.name("dpt"  ), 30, -1.5,  1.5);
  tdeta_= fs->make<TH1F>(id.name("tdeta"), id.name("deta" ), 30, -1.5,  1.5);
  tdphi_= fs->make<TH1F>(id.name("tdphi"), id.name("dphi" ), 30, -1.5,  1.5);
  nohit_= fs->make<TH1F>(id.name("nohit"), id.name("nohit"), 25,   0.,  25.);
  nvhit_= fs->make<TH1F>(id.name("nvhit"), id.name("nvhit"), 25,   0.,  25.);
  chi2_ = fs->make<TH1F>(id.name("chi2" ), id.name("chi2" ), 50,   0.,  10.);
  drtk_ = fs->make<TH1F>(id.name("drtrk"), id.name("drtrk"), 31, -0.1,   3.);
  s1os9_= fs->make<TH1F>(id.name("s1os9"), id.name("s1os9"), 25,   0.,   1.);
}

void 
ElecId::book(ofstream& file)
{
  edm::Service<TFileService> fs;
  if( !fs )
    throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  NameScheme id("id");
  eops_ = fs->make<TH1F>(id.name(file, "eops" ), id.name("eops" ), 50,   0.,   5.);
  eopb_ = fs->make<TH1F>(id.name(file, "eopb" ), id.name("eopb" ), 50,   0.,   5.);
  nocl_ = fs->make<TH1F>(id.name(file, "nocl" ), id.name("nocl" ), 20,   0.,  20.);
  deta_ = fs->make<TH1F>(id.name(file, "deta" ), id.name("deta" ), 40,-0.02, 0.02);
  dphi_ = fs->make<TH1F>(id.name(file, "dphi" ), id.name("dphi" ), 40,-0.02, 0.02);
  hoem_ = fs->make<TH1F>(id.name(file, "hoem" ), id.name("hoem" ), 50,  -5.,   0.);
  tdpt_ = fs->make<TH1F>(id.name(file, "tdpt" ), id.name("dpt"  ), 30, -1.5,  1.5);
  tdeta_= fs->make<TH1F>(id.name(file, "tdeta"), id.name("deta" ), 30, -1.5,  1.5);
  tdphi_= fs->make<TH1F>(id.name(file, "tdphi"), id.name("dphi" ), 30, -1.5,  1.5);
  nohit_= fs->make<TH1F>(id.name(file, "nohit"), id.name("nohit"), 25,   0.,  25.);
  nvhit_= fs->make<TH1F>(id.name(file, "nvhit"), id.name("nvhit"), 25,   0.,  25.);
  chi2_ = fs->make<TH1F>(id.name(file, "chi2" ), id.name("chi2" ), 50,   0.,  10.);
  drtk_ = fs->make<TH1F>(id.name(file, "drtrk"), id.name("drtrk"), 31, -0.1,   3.);
  s1os9_= fs->make<TH1F>(id.name(file, "s1os9"), id.name("s1os9"), 25,   0.,   1.);
}
