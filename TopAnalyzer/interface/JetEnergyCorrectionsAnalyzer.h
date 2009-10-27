#ifndef JetEnergyCorrectionsAnalyzer_h
#define JetEnergyCorrectionsAnalyzer_h

#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "TH1F.h"
#include "TH2F.h"

namespace reco {
  class Candidate;
  class GenJet;
  class GenParticle;
}

/**
   \class   JetEnergyCorrectionsAnalyzer JetEnergyCorrectionsAnalyzer.h "TopAnalysis/TopAnalyzer/interface/JetEnergyCorrectionsAnalyzer.h"
*/

class JetEnergyCorrectionsAnalyzer : public edm::EDAnalyzer {

 public:
  /// default constructor
  explicit JetEnergyCorrectionsAnalyzer(const edm::ParameterSet&);
  /// default destructor
  ~JetEnergyCorrectionsAnalyzer(){};

  virtual void beginJob(const edm::EventSetup&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  
  private:
  /// fill histograms related to the response of light jets  
  void analyzeLightJetResponse(const reco::Candidate& recJet, const reco::GenJet& genJet, const reco::GenParticle& parton);
  /// fill histograms related to the response of b jets
  void analyzeBJetResponse(const reco::Candidate& recJet, const reco::GenJet& genJet, const reco::GenParticle& parton);
  /// fill pdgId specific histograms
  void analyzeFlavorComposition(const reco::Candidate& jet, const reco::GenParticle& parton);

  private:
  /// ttSemiLeptonicEvent
  edm::InputTag semiLepEvt_;
  /// class key of hypothesis
  std::string hypoKey_;
  /// genJets
  edm::InputTag genJets_;
  /// matching of genJets to partons
  edm::InputTag genJetMatching_;

 protected:
  /// histogram container
  std::map<std::string, TH1*> hists_;
};

#endif
