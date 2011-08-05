#ifndef DiLeptonObjAnalyzer_h
#define DiLeptonObjAnalyzer_h

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
/* #include "DataFormats/Common/interface/TriggerResults.h" */
/* #include "DataFormats/MuonReco/interface/Muon.h" */
/* #include "DataFormats/MuonReco/interface/MuonFwd.h" */
/* #include "DataFormats/MuonReco/interface/MuonEnergy.h" */
/* #include "DataFormats/MuonReco/interface/MuonIsolation.h" */
/* #include "DataFormats/EgammaCandidates/interface/Electron.h" */
/* #include "DataFormats/EgammaCandidates/interface/ElectronFwd.h" */
/* #include "DataFormats/EgammaCandidates/interface/GsfElectron.h" */
/* #include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h" */

#include "DataFormats/PatCandidates/interface/Jet.h"
/* #include "DataFormats/PatCandidates/interface/Muon.h" */
/* #include "DataFormats/PatCandidates/interface/Electron.h" */

/* #include "DataFormats/GsfTrackReco/interface/GsfTrack.h" */
/* #include "DataFormats/VertexReco/interface/Vertex.h" */
/* #include "DataFormats/VertexReco/interface/VertexFwd.h" */
/* #include "HLTrigger/HLTfilters/interface/HLTHighLevel.h" */


#include "DataFormats/Candidate/interface/CompositeCandidate.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h"

class TH1F;
class TH2F;
class DiLeptonObjAnalyzer : public edm::EDAnalyzer {

  public:

    DiLeptonObjAnalyzer(const edm::ParameterSet&);
    ~DiLeptonObjAnalyzer();

  protected:

    void beginJob();
    void beginRun(const edm::Run&, const edm::EventSetup&);

    void analyze(const edm::Event&, const edm::EventSetup&);

    void endRun(  const edm::Run&, const edm::EventSetup&);
    void endJob();

  private:

    bool fileOutput_;
    bool onlyFirst_;
    std::string outputFile_;
    std::ofstream  outfile;

    edm::InputTag dileptons_;
    edm::InputTag  jets_;


    TH1F * Dimass;

    TH1F * Eta;

    TH1F * Phi;

    TH1F * D_R_lepton_lepton;
    TH1F * D_eta_lepton_lepton;
    TH1F * D_phi_lepton_lepton;


    TH1F * D_R_dilepton_jet;

    TH1F * Multi;

    //rapidity()

    edm::InputTag weight_;

};

#endif
