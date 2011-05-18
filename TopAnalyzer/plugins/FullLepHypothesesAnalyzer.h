#ifndef FullLepHypothesesAnalyzer_h
#define FullLepHypothesesAnalyzer_h

#include "TH1D.h"
#include "TH2D.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullLeptonicEvent.h"

/**
   \class   FullLepHypothesesAnalyzer FullLepHypothesesAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/FullLepHypothesesAnalyzer.h"

   \brief   EDAnalyzer for FullLeptonicEvent hypotheses with electrons and muons

   The analyzer needs TtFullLeptonicEvents as input and plots the kinematic quantities of all generated and reconstructed particles
   in the ttbar decay chain and also the resolution of the reconstructed particles. For the different hypotheses different quality
   plots are filled.
*/

class FullLepHypothesesAnalyzer : public edm::EDAnalyzer {

 public:
  /// default constructor
  explicit FullLepHypothesesAnalyzer(const edm::ParameterSet&);
  /// default destructor
  ~FullLepHypothesesAnalyzer();
  
 private:
  /// everything that has to be done before the event loop: books histograms
  virtual void beginJob() ;
  /// everything that has to be done during the event loop: filling plots
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  /// everything that has to be done after the event loop: summarizes if wantSummary_ is true
  virtual void endJob();

  /// input given in config has to be TtFullLeptonicEvent
  edm::InputTag FullLepEvt_;
  /// keyword for hypothesis from config: ttFullLepHypKinSolution:Key or ttFullLepHypGenMatch:Key
  edm::InputTag hypoKey_;
  /// event weight given in config 
  edm::InputTag wgt_;
  
  /// input bool: use a event weight?     
  bool useEvtWgt_;
  /// bool if also plots for wrong charge combinations  are filled
  bool useWrongCharge_;
  /// bool if summary is wanted after event loop
  bool wantSummary_;  
  
  /// counter for events with available hypothesis
  int Nava;
  /// counter for events with valid hypothesis
  int Nval;

  /// book histograms for reconstructed particles properties: Pt, E, Eta, Phi, m
  /// append wrong charge histos if chosen in config
  void bookKinHistos      (edm::Service<TFileService>&);
  /// book histograms for generated particles properties: Pt, E, Eta, Phi, m
  void bookKinGenHistos   (edm::Service<TFileService>&);  
  /// book histograms for particle resolutions
  /// append wrong charge histos if chosen in config
  void bookKinResHistos   (edm::Service<TFileService>&);
  /// book histograms for hypothesis specific histos and correlations between hypotheses 
  void bookQualityHistos  (edm::Service<TFileService>&);

  /// fill histograms for reconstructed particles properties in events with oppositely charged leptons: Pt, E, Eta, Phi, m
  void fillKinHistos           (std::vector<TH1D*>&, 
                                const reco::Candidate&, 
				const double&);
  /// fill histograms for reconstructed particles properties in events with equally charged leptons: Pt, E, Eta, Phi, m				
  void fillWrongChargeKinHistos(std::vector<TH1D*>&, 
                                const reco::Candidate&, 
                                const double&);
  /// fill histograms for generated particles properties: Pt, E, Eta, Phi, m				
  void fillKinGenHistos        (std::vector<TH1D*>&,  
				const reco::Candidate&, 
				const double&);
  /// fill histograms for particle resolutions for right charge combinations								  
  void fillKinResHistos        (std::vector<TH1D*>&, 
                                const reco::Candidate&, 
				const reco::Candidate&, 
				const double&);
  /// fill histograms for particle resolutions for wrong charge combinations
  /// should be empty since the only entries are from right charge events that are reconstructed as wrong charge					
  void fillWrongChargeKinResHistos(std::vector<TH1D*>&, 
                                   const reco::Candidate&, 
				   const reco::Candidate&, 
				   const double&);	
  /// book histograms for hypothesis specific histos and correlations between hypotheses 							
  void fillQualityHistos       (const TtFullLeptonicEvent&,
                                const TtEvent::HypoClassKey&,
                                const double&);

  /// histograms for top quark kinematics
  std::vector<TH1D*> TopKin_;
  /// histograms for W^+ kinematics
  std::vector<TH1D*> WplusKin_;
  /// histograms for B kinematics
  std::vector<TH1D*> BKin_;
  /// histograms for l^+ kinematics
  std::vector<TH1D*> LepBarKin_;
  /// histograms for neutrino kinematics
  std::vector<TH1D*> NuKin_; 
  /// histograms for anti-top quark kinematics 
  std::vector<TH1D*> TopBarKin_;
  /// histograms for W^- quark kinematics
  std::vector<TH1D*> WminusKin_;
  /// histograms for anti-b kinematics
  std::vector<TH1D*> BBarKin_;
  /// histograms for l^- kinematics
  std::vector<TH1D*> LepKin_;
  /// histograms for anti-neutrino kinematics
  std::vector<TH1D*> NuBarKin_;
  
  /// histograms for generated top quark kinematics
  std::vector<TH1D*> TopKinGen_;
  /// histograms for generated W^+ kinematics
  std::vector<TH1D*> WplusKinGen_;
  /// histograms for generated B kinematics
  std::vector<TH1D*> BKinGen_;
  /// histograms for generated l^+ kinematics
  std::vector<TH1D*> LepBarKinGen_;
  /// histograms for generated neutrino kinematics
  std::vector<TH1D*> NuKinGen_;  
  /// histograms for generated anti-top quark kinematics 
  std::vector<TH1D*> TopBarKinGen_;
  /// histograms for generated W^- quark kinematics
  std::vector<TH1D*> WminusKinGen_;
  /// histograms for generated anti-b kinematics
  std::vector<TH1D*> BBarKinGen_;
  /// histograms for generated l^- kinematics
  std::vector<TH1D*> LepKinGen_;
  /// histograms for generated anti-neutrino kinematics
  std::vector<TH1D*> NuBarKinGen_;  
  
  /// histograms for top quark resolutions
  std::vector<TH1D*> TopKinRes_;
  /// histograms for W^+ resolutions
  std::vector<TH1D*> WplusKinRes_;
  /// histograms for B resolutions
  std::vector<TH1D*> BKinRes_;
  /// histograms for l^+ resolutions
  std::vector<TH1D*> LepBarKinRes_;
  /// histograms for neutrino resolutions
  std::vector<TH1D*> NuKinRes_; 
  /// histograms for anti-top quark resolutions 
  std::vector<TH1D*> TopBarKinRes_;
  /// histograms for W^- quark resolutions
  std::vector<TH1D*> WminusKinRes_;
  /// histograms for anti-b resolutions
  std::vector<TH1D*> BBarKinRes_;
  /// histograms for l^- resolutions
  std::vector<TH1D*> LepKinRes_;
  /// histograms for anti-neutrino resolutions
  std::vector<TH1D*> NuBarKinRes_;
    
  /// histogram with two bins: 0 for invalid and 1 for valid (i.e. succesfully reconstructed) events 
  TH1D* goodHypo_;
  
  /// histogram only for genMatch hypothesis: sum of deltaR between reconstructed leptons and jets and
  /// corresponding generated objects
  TH1D* genMatchSumDR_;
  /// histogram only for genMatch hypothesis: sum of delta pt between reconstructed leptons and jets and
  /// corresponding generated objects  
  TH1D* genMatchSumPt_;
  
  /// histogram only for kinSolution hypothesis: weight from neutrino spectrum of best kinematic solution
  TH1D* kinSolWeight_;
  /// histogram only for kinSolution hypothesis: weight from neutrino spectrum of best kinematic solution
  /// for solutions with equally charged leptons
  TH1D* kinSolWeightWrong_;  
  /// histogram with two bins: 0 for right charge, 1 for wrong charge 
  TH1D* wrongCharge_; 
  
  /// histogram for index of bJet in jet collection used for the event reconstruction
  TH1D* bJetIdcs_;
  /// histogram for index of bBarJet in jet collection used for the event reconstruction
  TH1D* bBarJetIdcs_; 
  /// histogram for index of the first electron in electron collection used for the event reconstruction 
  TH1D* elec1Idcs_;
  /// histogram for index of the second electron in electron collection used for the event reconstruction
  TH1D* elec2Idcs_; 
  /// histogram for index of the first muon in muon collection used for the event reconstruction
  TH1D* muon1Idcs_; 
  /// histogram for index of the first muon in muon collection used for the event reconstruction
  TH1D* muon2Idcs_; 
  
  /// historgram for the mass difference between reconstructed top and anti-top.
  /// For kinSolution hypothesis it should give a sharp peak around zero since the assumption that both masses
  /// are equal is used as a boundary condition. Differences appear only from rounding errors
  TH1D* deltaM_;
  
  /// histogram that shows the number of correctly identified jets in hypothesis: 0, 1 or 2
  TH1D* jetIdCorrectnes_;
  /// histogram that shows how many of jets in reconstructed hypothesis are in deed b-Jets: 0, 1 or 2
  TH1D* jetFlCorrectnes_;  
  /// histogram that compares the indices of the muons and jets in both hypotheses.
  /// Does not include electrons yet but can be extended easily
  TH2D* compare_;
  /// histogram that shows the two dimensional neutrino spectrum
  TH2D* spectrum_;
  /// histogram to compare the generated neutrino momenta to the reconstructed ones
  TH2D* genRecoNuComparison_; 
  /// histogram to compare the generated antineutrino momenta to the reconstructed ones
  TH2D* genRecoNuBarComparison_; 
  /// histogram to compare the generated neutrino momenta to the reconstructed ones
  TH2D* genRecoNuPx_; 
  /// histogram to compare the generated antineutrino momenta to the reconstructed ones
  TH2D* genRecoNuBarPx_;
  /// histogram to compare the generated neutrino momenta to the reconstructed ones  
  TH2D* genRecoNuPy_; 
  /// histogram to compare the generated antineutrino momenta to the reconstructed ones
  TH2D* genRecoNuBarPy_;           
};

#endif
