#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TopAnalysis/TopAnalyzer/interface/PUEventWeight.h"
#include "TH1D.h"
#include "TMath.h"
#include <vector>
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/IsolatedPFCandidate.h"
#include <DataFormats/TrackReco/interface/Track.h>
#include <DataFormats/MuonReco/interface/Muon.h>

class PFCandidateAnalyzer : public edm::EDAnalyzer {

public:

    explicit PFCandidateAnalyzer(const edm::ParameterSet&);
    ~PFCandidateAnalyzer();

private:

    virtual void beginJob() ;
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob();
    double calculateIsolation(const reco::PFCandidate& candidate);

    edm::InputTag src_;

    bool verbosity_;
    std::vector<int> fromTo_;

    typedef std::vector<reco::PFCandidate> PFCandidateCollection;

    TH1D* multi_;
    TH1D* pt_;
    TH1D* eta_;
    TH1D* dep_ecal_;
    TH1D* dep_hcal_;
    TH1D* iso_comb_;
    TH1D* iso_comb2_;
    TH1D* nhits_;
    TH1D* n_pixhits_;
    TH1D* n_trackerhits_;
    TH1D* n_mustations_;
    TH1D* n_validmuhits_;
    TH1D* chi_norm_;
    TH1D* d0_;
    TH1D* dB_;
    TH1D* type_;
    TH1D* phi_;
    TH1D* deltaP_;
    TH1D* ecalEnergy_;
    TH1D* hcalEnergy_;
    TH1D* mva_e_mu_;
    TH1D* mva_e_pi_;
    TH1D* mva_gamma_nh_;
    TH1D* mva_nothing_gamma_;
    TH1D* mva_nothing_nh_;
    TH1D* mva_pi_mu_;
    edm::InputTag weight_;
};



PFCandidateAnalyzer::PFCandidateAnalyzer(const edm::ParameterSet& cfg):
        src_      ( cfg.getParameter<edm::InputTag>     ( "src"    ) ),
        verbosity_  ( cfg.getParameter<bool>              ( "verbosity") ),
        fromTo_     ( cfg.getParameter<std::vector<int> > ( "from_to"  ) ),
        weight_     ( cfg.getParameter<edm::InputTag>("weight"))
{
}

PFCandidateAnalyzer::~PFCandidateAnalyzer()
{
}

void
PFCandidateAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
    double weight = getPUEventWeight(evt, weight_);
    if (verbosity_) {
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "      Run: " << evt.id().run()              << std::endl;
        std::cout << "LumiBlock: " << evt.id().luminosityBlock()  << std::endl;
        std::cout << "    Event: " << evt.id().event()            << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
    }

    edm::Handle<PFCandidateCollection> pfcandidates;
    evt.getByLabel(src_, pfcandidates);

    multi_->Fill(pfcandidates->size(), weight);

    int i=0;
    for (PFCandidateCollection::const_iterator candidate = pfcandidates->begin(); candidate!= pfcandidates->end(); ++candidate) {

        // only take the pfcandidates from the selected range
        if (i<fromTo_[0]) continue;
        if (i>fromTo_[1]) break;

        ++i;
        pt_      ->Fill(candidate->pt(), weight);
        eta_     ->Fill(candidate->eta(), weight);
        phi_->Fill(candidate->phi(), weight);

        deltaP_->Fill(candidate->deltaP(), weight);
        ecalEnergy_->Fill(candidate->ecalEnergy(), weight);
        hcalEnergy_->Fill(candidate->hcalEnergy(), weight);
        mva_e_mu_->Fill(candidate->mva_e_mu(), weight);
        mva_e_pi_->Fill(candidate->mva_e_pi(), weight);
        mva_gamma_nh_->Fill(candidate->mva_gamma_nh(), weight);
        mva_nothing_gamma_->Fill(candidate->mva_nothing_gamma(), weight);
        mva_nothing_nh_->Fill(candidate->mva_nothing_nh(), weight);
        mva_pi_mu_->Fill(candidate->mva_pi_mu(), weight);
        if (candidate->trackRef().isNonnull())
            d0_->Fill(candidate->trackRef()->d0(), weight);

        const reco::MuonRef muon = candidate->muonRef();
        if (muon.isNonnull()) {
            dep_ecal_->Fill(muon->isolationR03().emVetoEt , weight);
            dep_hcal_->Fill(muon->isolationR03().hadVetoEt, weight);

          //  iso_comb_ ->Fill((muon->trackIso()+muon->caloIso())/muon->pt(), weight);
          //  iso_comb2_->Fill((muon->trackIso()+muon->caloIso())/muon->pt(), weight);

            //muon->
            //dB_->Fill(muon->dB(), weight);
            if (muon->isGlobalMuon()) {
                chi_norm_ ->Fill(muon->globalTrack()->normalizedChi2(), weight);
                n_validmuhits_->Fill(muon->globalTrack()->hitPattern().numberOfValidMuonHits(), weight);
                type_->SetBinContent(2,type_->GetBinContent(2)+1);
            }
            if (muon->isTrackerMuon()) {
                nhits_->Fill(muon->track()->numberOfValidHits(), weight);
                n_pixhits_    ->Fill(muon->track()->hitPattern().numberOfValidPixelHits(), weight);
                n_trackerhits_->Fill(muon->track()->hitPattern().numberOfValidTrackerHits(), weight);
                type_->SetBinContent(1,type_->GetBinContent(1)+1);
            }
            if (muon->isTrackerMuon() && muon->isGlobalMuon()) {
                type_->SetBinContent(3,type_->GetBinContent(3)+1);
            }
            if (!muon->isTrackerMuon() && !muon->isGlobalMuon() && muon->isStandAloneMuon()) {
                type_->SetBinContent(4,type_->GetBinContent(4)+1);
            }
        }

        iso_comb2_->Fill(calculateIsolation(*candidate), weight);
    }
}

double PFCandidateAnalyzer::calculateIsolation(const reco::PFCandidate& candidate) {
    // read all isolation value maps
//     candidate.
//     candidate.
//     std::vector< edm::Handle<IsoMap> >
//       isoMaps(isolationValueMapLabels_.size());
//     for(unsigned iMap = 0; iMap<isolationValueMapLabels_.size(); ++iMap) {
//       e.getByLabel(isolationValueMapLabels_[iMap], isoMaps[iMap]);
//     }
//
//     unsigned key=0;
//     //    for( unsigned i=0; i<collection->size(); i++ ) {
//     for( collection::const_iterator pfc = hc->begin();
//          pfc != hc->end(); ++pfc, ++key) {
//       reco::PFCandidateRef candidate(hc,key);
//
//       bool passed = true;
//       double isoSum=0.0;
//       for(unsigned iMap = 0; iMap<isoMaps.size(); ++iMap) {
//
//         const IsoMap & isoMap = *(isoMaps[iMap]);
//
//         double val = isoMap[candidate];
//         double cut = isolationCuts_[iMap];
//         if(isRelative_ && candidate->pt()>0.0) val/=candidate->pt();
//         isoSum+=val;
//         //std::cout << "val " << iMap << " = " << val << std::endl;
//
//         if ( !isCombined_ && val>cut ) {
//           passed = false;
//           break;
//         }
//       }
    return -1;
}

void
PFCandidateAnalyzer::beginJob()
{
    edm::Service<TFileService> fs;
    if ( !fs ) {
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

    deltaP_ = fs->make<TH1D>("deltaP", "deltaP", 100, -0.2, 0.2);
    ecalEnergy_ = fs->make<TH1D>("ecalEnergy", "ecalEnergy", 100, 0, 100);
    hcalEnergy_ = fs->make<TH1D>("hcalEnergy", "hcalEnergy", 100, 0, 100);
    mva_e_mu_ = fs->make<TH1D>("mva_e_mu", "mva_e_mu", 100, -1000, 100);
    mva_e_pi_ = fs->make<TH1D>("mva_e_pi", "mva_e_pi", 100, -1000, 100);
    mva_gamma_nh_ = fs->make<TH1D>("mva_gamma_nh", "mva_gamma_nh", 100, -1000, 100);
    mva_nothing_gamma_ = fs->make<TH1D>("mva_nothing_gamma", "mva_nothing_gamma", 100, -1000, 100);
    mva_nothing_nh_ = fs->make<TH1D>("mva_nothing_nh", "mva_nothing_nh", 100, -1000, 100);
    mva_pi_mu_ = fs->make<TH1D>("mva_pi_mu", "mva_pi_mu", 100, -1000, 100);

}


void
PFCandidateAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE( PFCandidateAnalyzer );
