#ifndef TriggerAnalyzer_h
#define TriggerAnalyzer_h

#include <string>
#include <vector>

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerEventWithRefs.h"
#include "DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h"
#include "DataFormats/Candidate/interface/Particle.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h" 
#include "DataFormats/MuonReco/interface/MuonEnergy.h"
#include "DataFormats/MuonReco/interface/MuonIsolation.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "HLTrigger/HLTfilters/interface/HLTHighLevel.h"

class TriggerAnalyzer : public edm::EDAnalyzer {

  public:
    explicit TriggerAnalyzer(const edm::ParameterSet&);
    ~TriggerAnalyzer();

  private:
    virtual void beginJob();
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob();

    edm::InputTag triggerResults_;
    edm::InputTag triggerEvent_;
    edm::InputTag triggerFilter_;
    edm::InputTag vertex_;
    edm::InputTag muons_;

    std::vector<std::string> hltPaths_;
    std::vector<std::string> hltPaths_sig_;
    std::vector<std::string> hltPaths_trig_;

    double vertex_X_cut_;
    double vertex_Y_cut_;
    double vertex_Z_cut_;

    double muon_pT_cut_;
    double muon_eta_cut_;
    double muon_iso_cut_;

    double MassWindow_up_;
    double MassWindow_down_;

    TH1F * NTracks;
    TH1F * NMuons;
    TH1F * NMuons_charge;
    TH1F * NMuons_iso;
    TH1F * PtMuons;
    TH1F * PtMuons_LOGX;
    TH1F * EtaMuons;
    TH1F * PhiMuons;
    TH1F * CombRelIso03;
    TH2F * VxVy_muons;
    TH1F * Vz_muons;
    TH1F * PixelHits_muons;
    TH1F * TrackerHits_muons;
    TH3F * VxVyVz_PV;

    TH1F * Trigs;
    TH1F * TriggerEfficiencies;
    TH1F * TriggerEfficiencies_sig;
    TH1F * TriggerEfficiencies_trig;
    TH2D * Correlations;

    TH1F * MuonEfficiency_pT;
    TH1F * MuonEfficiency_pT_sig;
    TH1F * MuonEfficiency_pT_trig;

    TH1F * MuonEfficiency_pT_LOGX;
    TH1F * MuonEfficiency_pT_LOGX_sig;
    TH1F * MuonEfficiency_pT_LOGX_trig;

    TH1F * MuonEfficiency_eta;
    TH1F * MuonEfficiency_eta_sig;
    TH1F * MuonEfficiency_eta_trig;

    TH1F * MuonEfficiency_phi;
    TH1F * MuonEfficiency_phi_sig;
    TH1F * MuonEfficiency_phi_trig;

    TH2F * MuonEfficiency_eta_phi;
    TH2F * MuonEfficiency_eta_phi_sig;
    TH2F * MuonEfficiency_eta_phi_trig;

    TH2F * MuonEfficiency_pT_eta;
    TH2F * MuonEfficiency_pT_eta_sig;
    TH2F * MuonEfficiency_pT_eta_trig;

    TH1F * DiMuonMassRC;
    TH1F * DiMuonMassWC;
    TH1F * DiMuonMassRC_LOGX;
    TH1F * DiMuonMassWC_LOGX;

    TH1F * DeltaEtaMuonsRC;
    TH1F * DeltaPhiMuonsRC;
    TH1F * DeltaEtaMuonsWC;
    TH1F * DeltaPhiMuonsWC;

    TH1F * DeltaR_Trig;
    TH1F * DeltaR_Reco;
    TH1F * DeltaR_Match;
    TH1F * Trigger_Match;

};

#endif
