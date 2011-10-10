#ifndef DiLeptonAnalyzer_h
#define DiLeptonAnalyzer_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonEnergy.h"
#include "DataFormats/MuonReco/interface/MuonIsolation.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "HLTrigger/HLTfilters/interface/HLTHighLevel.h"

class TH1F;
class TH2F;
class DiLeptonAnalyzer : public edm::EDAnalyzer {

  public:

    DiLeptonAnalyzer(const edm::ParameterSet&);
    ~DiLeptonAnalyzer();

  protected:

    void beginJob();
    void beginRun(const edm::Run&, const edm::EventSetup&);

    void analyze(const edm::Event&, const edm::EventSetup&);

    void endRun(  const edm::Run&, const edm::EventSetup&);
    void endJob();

  private:

    bool fileOutput_;
    std::string outputFile_;
    std::ofstream  outfile;

    edm::InputTag vertex_;
    double vertex_X_cut_;
    double vertex_Y_cut_;
    double vertex_Z_cut_;

    edm::InputTag loose_muons_;
    edm::InputTag muons_;
    edm::InputTag elecs_;
    edm::InputTag jets_;
    edm::InputTag puWeight_;
    edm::InputTag lepSfWeight_;

    double muon_iso_cut_;
    double elec_iso_cut_;

    double MassWindow_up_;
    double MassWindow_down_;

    // these two histograms are needed for the analysis
    // the other ones are kept for backward compatibility
    TH1F * DiLeptonMass;
    TH1F * DiLeptonPt;

    TH1F * Events_RC;
    TH1F * Events_WC;
    TH2F * Events_iso;
    TH1F * Ntracks;
    TH2F * VxVy_muons;
    TH1F * Vz_muons;

    TH1F * Nmuons;
    TH1F * Nmuons_iso;
    TH1F * Nmuons_charge;

    TH1F * Nelecs;
    TH1F * Nelecs_iso;
    TH1F * Nelecs_charge;

    TH1F * Muon_CombRelIso03;
    TH1F * Elec_CombRelIso03;

    TH1F * DimassRC_MM;
    TH1F * DimassRC_EE;
    TH1F * DimassRC_ME;
    TH1F * DimassWC_MM;
    TH1F * DimassWC_EE;
    TH1F * DimassWC_ME;

    TH1F * DimassRC_LOGX_MM;
    TH1F * DimassRC_LOGX_EE;
    TH1F * DimassRC_LOGX_ME;
    TH1F * DimassWC_LOGX_MM;
    TH1F * DimassWC_LOGX_EE;
    TH1F * DimassWC_LOGX_ME;

    TH1F * D_R_muon_jet;
    TH1F * D_R_elec_jet;
    TH1F * D_R_elec_muon;

    TH1F * D_eta_muonsRC;
    TH1F * D_eta_muonsWC;
    TH1F * D_phi_muonsRC;
    TH1F * D_phi_muonsWC;

    TH1F * D_eta_leptsRC;
    TH1F * D_eta_leptsWC;
    TH1F * D_phi_leptsRC;
    TH1F * D_phi_leptsWC;

    TH1F * D_eta_elecsRC;
    TH1F * D_eta_elecsWC;
    TH1F * D_phi_elecsRC;
    TH1F * D_phi_elecsWC;
};

#endif
