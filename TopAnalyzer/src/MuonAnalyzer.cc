#include "TopAnalysis/TopAnalyzer/interface/MuonAnalyzer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "TMath.h"
#include "TopAnalysis/TopAnalyzer/interface/DileptonEventWeight.h"

MuonAnalyzer::MuonAnalyzer(const edm::ParameterSet& cfg):
  muons_      ( cfg.getParameter<edm::InputTag>     ( "muons"      )),
  jets_       ( cfg.getParameter<edm::InputTag>     ( "jets"       )),
  puWeight_   (cfg.getParameter<edm::InputTag>      ("weightPU"    )),
  lepSfWeight_(cfg.getParameter<edm::InputTag>      ("weightLepSF" )),  
  verbosity_  ( cfg.getParameter<bool>              ( "verbosity"  )),
  fromTo_     ( cfg.getParameter<std::vector<int> > ( "from_to"    ))
{
}

MuonAnalyzer::~MuonAnalyzer()
{
}

void
MuonAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  double weight = getDileptonEventWeight(evt, puWeight_, lepSfWeight_);
  if(verbosity_){
    std::cout << "-------------------------------------------" << std::endl;
     std::cout << "      Run: " << evt.id().run()              << std::endl;
     std::cout << "LumiBlock: " << evt.id().luminosityBlock()  << std::endl;
     std::cout << "    Event: " << evt.id().event()            << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
  }

  edm::Handle<PatMuonCollection> muons;
  evt.getByLabel(muons_, muons);

  edm::Handle<PatJetCollection> jets;
  evt.getByLabel(jets_, jets);

  multi_->Fill(muons->size(), weight);

  int i=0;
  for(PatMuonCollection::const_iterator muon = muons->begin(); muon!= muons->end(); ++muon) {

    // only take the muons from the selected range
    if(i<fromTo_[0]) continue;
    if(i>fromTo_[1]) break;

    ++i;
    pt_      ->Fill(muon->pt(), weight);
    eta_     ->Fill(muon->eta(), weight);
    phi_->Fill(muon->phi(), weight);

    dep_ecal_->Fill(muon->isolationR03().emVetoEt , weight);
    dep_hcal_->Fill(muon->isolationR03().hadVetoEt, weight);

    iso_comb_ ->Fill((muon->trackIso()+muon->caloIso())/muon->pt(), weight);
    iso_comb2_->Fill((muon->trackIso()+muon->caloIso())/muon->pt(), weight);
    pfIso_->Fill((muon->chargedHadronIso()+muon->neutralHadronIso()+muon->photonIso()) / muon->pt());

    dB_->Fill(muon->dB(), weight);

    n_mustations_->Fill(muon->numberOfMatches(), weight);

    if (jets.failedToGet()) {
        //if we don't have jets, make entry in last bin
        jet_dist_->Fill(jet_dist_->GetBinLowEdge(jet_dist_->GetNbinsX()), weight);
    } else {
        double minDr = 999.;
        for(PatJetCollection::const_iterator jet = jets->begin(); jet!= jets->end(); ++jet) {
            double dr = reco::deltaR<const pat::Muon, const pat::Jet>(*muon, *jet);
            if(dr<minDr) minDr = dr;
        }
        jet_dist_->Fill(minDr, weight);
    }

    d0_   ->Fill(muon->track()->d0(), weight);

    if(muon->isGlobalMuon()){
      chi_norm_ ->Fill(muon->globalTrack()->normalizedChi2(), weight);
      n_validmuhits_->Fill(muon->globalTrack()->hitPattern().numberOfValidMuonHits(), weight);
      type_->SetBinContent(2,type_->GetBinContent(2)+1);
    }
    if(muon->isTrackerMuon()){
      nhits_->Fill(muon->track()->numberOfValidHits(), weight);
      n_pixhits_    ->Fill(muon->track()->hitPattern().numberOfValidPixelHits(), weight);
      n_trackerhits_->Fill(muon->track()->hitPattern().numberOfValidTrackerHits(), weight);
      type_->SetBinContent(1,type_->GetBinContent(1)+1);
    }
    if(muon->isTrackerMuon() && muon->isGlobalMuon()){
      type_->SetBinContent(3,type_->GetBinContent(3)+1);
    }
    if(!muon->isTrackerMuon() && !muon->isGlobalMuon() && muon->isStandAloneMuon()){
      type_->SetBinContent(4,type_->GetBinContent(4)+1);
    }


    if(verbosity_){
      std::cout << "-------------------------------------------" << std::endl;
      std::cout << "MUON " << i-1 << ":" << std::endl;
      std::cout << "        pt = " << muon->pt() << std::endl;
      std::cout << "       eta = " << muon->eta() << std::endl;
      std::cout << "       phi = " << muon->phi() << std::endl;
      std::cout << "   depEcal = " << muon->isolationR03().emVetoEt << std::endl;
      std::cout << "   depHcal = " << muon->isolationR03().hadVetoEt << std::endl;
      std::cout << "       iso = " << (muon->trackIso()+muon->caloIso())/muon->pt() << std::endl;
      std::cout << "        dB = " << muon->dB() << std::endl;
      if(muon->isGlobalMuon()){
        std::cout << "chi^2/ndof = " << muon->combinedMuon()->normalizedChi2() << std::endl;
      }
      else if(!muon->track()){
        std::cout << "is stand alone muon" << std::endl;
      }
      else{
        std::cout << "     Nhits = " << muon->numberOfValidHits() << std::endl;
      }
      std::cout << "-------------------------------------------" << std::endl;
    }
  }
  if(verbosity_){
    std::cout << "-------------------------------------------" << std::endl;
  }
}


void
MuonAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }

  multi_= fs->make<TH1D>( "multi" , "N_{#mu} per Event", 10, -0.5, 9.5);
  multi_->GetXaxis()->SetTitle("N_{#mu}");
  multi_->GetYaxis()->SetTitle("N_{evts}");

  pt_= fs->make<TH1D>( "pt" , "Muon Transverse Momentum", 200, 0., 400.);
  pt_->GetXaxis()->SetTitle("p_{t,#mu} [GeV]");
  pt_->GetYaxis()->SetTitle("N");

  eta_= fs->make<TH1D>( "eta", "Muon Pseudorapidity", 80,-4., 4.);
  eta_->GetXaxis()->SetTitle("#eta_{#mu}");
  eta_->GetYaxis()->SetTitle("N");

  phi_ = fs->make<TH1D>("phi", "Muon Phi", 48, -TMath::Pi(), TMath::Pi());
  phi_->GetXaxis()->SetTitle("#phi_{#mu}");
  phi_->GetYaxis()->SetTitle("N per 7.5 degree");

  dep_ecal_= fs->make<TH1D>("dep_ecal", "Muon ECAL Energy", 100, 0., 10.);
  dep_ecal_->GetXaxis()->SetTitle("E_{ECAL} [GeV]");
  dep_ecal_->GetYaxis()->SetTitle("N");

  dep_hcal_= fs->make<TH1D>("dep_hcal", "Muon HCAL Energy", 100, 0., 10.);
  dep_hcal_->GetXaxis()->SetTitle("E_{HCAL} [GeV]");
  dep_hcal_->GetYaxis()->SetTitle("N");

  iso_comb_= fs->make<TH1D>("iso_comb", "Muon Combined Isolation", 300, 0.,  15.);
  iso_comb_->GetXaxis()->SetTitle("I_{comb}");
  iso_comb_->GetYaxis()->SetTitle("N");

  iso_comb2_= fs->make<TH1D>("iso_comb2", "Muon Combined Isolation", 200, 0.,  2.);
  iso_comb2_->GetXaxis()->SetTitle("I_{comb}");
  iso_comb2_->GetYaxis()->SetTitle("N");

  pfIso_= fs->make<TH1D>("pf_iso", "Particle Flow Isolation", 200, 0.,  0.5);
  pfIso_->GetXaxis()->SetTitle("I_{PF}");
  pfIso_->GetYaxis()->SetTitle("N");

  jet_dist_= fs->make<TH1D>("jet_dist", "Distance to closest Jet", 100, 0.,  10.);
  jet_dist_->GetXaxis()->SetTitle("#Delta r");
  jet_dist_->GetYaxis()->SetTitle("N");

  nhits_= fs->make<TH1D>( "nhits", "N_{Hits} of Muon Track", 51,-0.5 , 50.5 );
  nhits_->GetXaxis()->SetTitle("N_{hits}");
  nhits_->GetYaxis()->SetTitle("N");

  n_pixhits_= fs->make<TH1D>( "n_pixhits", "N_{Hits} in PIXEL", 11,-0.5 , 10.5 );
  n_pixhits_->GetXaxis()->SetTitle("N_{hits,PIX}");
  n_pixhits_->GetYaxis()->SetTitle("N");

  n_trackerhits_= fs->make<TH1D>( "n_trackerhits", "N_{Hits} in SiSTRIP", 51,-0.5 , 50.5 );
  n_trackerhits_->GetXaxis()->SetTitle("N_{hits,SiSTRIP}");
  n_trackerhits_->GetYaxis()->SetTitle("N");

  n_mustations_= fs->make<TH1D>( "n_mustations", "N_{#mu-Stations}", 11,-0.5 , 10.5 );
  n_mustations_->GetXaxis()->SetTitle("N_{#mu-Stat}");
  n_mustations_->GetYaxis()->SetTitle("N");

  n_validmuhits_= fs->make<TH1D>( "n_validmuhits", "N_{val #mu-hits} in global Fit", 51,-0.5 , 50.5 );
  n_validmuhits_->GetXaxis()->SetTitle("N_{val #mu-hits}");
  n_validmuhits_->GetYaxis()->SetTitle("N");

  chi_norm_= fs->make<TH1D>("chi_norm", "Normalized Chi2", 100, 0., 20.);
  chi_norm_->GetXaxis()->SetTitle("#chi^{2}/n_{dof}");
  chi_norm_->GetYaxis()->SetTitle("N");

  d0_= fs->make<TH1D>( "d0", "D0 of Inner Track", 100, 0., 2.);
  d0_->GetXaxis()->SetTitle("d0 [cm]");
  d0_->GetYaxis()->SetTitle("N");

  dB_= fs->make<TH1D>( "dB", "DB of Muon Track", 100, 0., 1.);
  dB_->GetXaxis()->SetTitle("dB [cm]");
  dB_->GetYaxis()->SetTitle("N");

  type_= fs->make<TH1D>( "type", "Muon Type", 4,-0.5 , 3.5 );
  type_->GetXaxis()->SetBinLabel(1,    "tracker");
  type_->GetXaxis()->SetBinLabel(2,     "global");
  type_->GetXaxis()->SetBinLabel(3,  "trk + gbl");
  type_->GetXaxis()->SetBinLabel(4,"stand alone");
  type_->GetYaxis()->SetTitle("N");
}


void
MuonAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE( MuonAnalyzer );
