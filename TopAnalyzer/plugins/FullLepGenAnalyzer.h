#ifndef FullLepGenAnalyzer_h
#define FullLepGenAnalyzer_h

#include "TH1D.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"

/**
  \class   FullLepGenAnalyzer FullLepGenAnalyzer.cc "TopAnalysis/TopAnalyzer/plugins/FullLepGenAnalyzer.cc"

  \brief   EDAnalyzer for full leptonic events
*/

using namespace std;

class FullLepGenAnalyzer : public edm::EDAnalyzer {
 public:
  /// default constructor
  explicit FullLepGenAnalyzer(const edm::ParameterSet&);
  /// default destructor
  ~FullLepGenAnalyzer();

 private:
  /// read in which channels are going to be selected and print out
  virtual void beginJob();
  /// everything that has to be done during the event loop: filling plots
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  /// gives a summary how many events have been selected
  virtual void endJob();
  /// book histograms for generated particles properties: Pt, E, Eta, Phi, m
  void bookGenHistos(edm::Service<TFileService>&);
  /// fill histograms for reconstructed particles properties in events with oppositely charged leptons: Pt, E, Eta, Phi, m
  void fillGenHistos(std::vector<TH1D*>&, const reco::Candidate&, double weight);
  /// returns electron/muon daughter of tau lepton		     
  const reco::Candidate* getTauDaughter(const reco::Candidate*);	     
  /// GenParticle Collection
  edm::InputTag src_;
  /// pile-up weight
  edm::InputTag puWeight_;
  /// lep SF weight
  edm::InputTag lepSfWeight_;
  
    edm::InputTag genJets_;
    edm::InputTag bIndex_;
    edm::InputTag antiBIndex_;

    /// histograms for generated top quark kinematics
  std::vector<TH1D*> TopGen_;
  /// histograms for generated W^+ kinematics
  std::vector<TH1D*> WplusGen_;
  /// histograms for generated B kinematics
  std::vector<TH1D*> BGen_;
  std::vector<TH1D*> HadronBGen_;
  /// histograms for generated l^+ kinematics
  std::vector<TH1D*> LepBarGen_;
  /// histograms for generated neutrino kinematics
  std::vector<TH1D*> NuGen_;
  /// histograms for generated anti-top quark kinematics
  std::vector<TH1D*> TopBarGen_;
  /// histograms for generated W^- quark kinematics
  std::vector<TH1D*> WminusGen_;
  /// histograms for generated anti-b kinematics
  std::vector<TH1D*> BBarGen_;
  std::vector<TH1D*> HadronBBarGen_;
  /// histograms for generated l^- kinematics
  std::vector<TH1D*> LepGen_;
  /// histograms for generated anti-neutrino kinematics
  std::vector<TH1D*> NuBarGen_;
  /// histograms for generated top pair kinematics
  std::vector<TH1D*> TtBarGen_;
  /// histograms for generated lepton pair kinematics
  std::vector<TH1D*> LepPairGen_;
  /// histograms for generated jet pair kinematics
  std::vector<TH1D*> JetPairGen_;

};

#endif
