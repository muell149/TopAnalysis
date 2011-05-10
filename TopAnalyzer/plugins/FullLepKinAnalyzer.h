#ifndef FullLepKinAnalyzer_h
#define FullLepKinAnalyzer_h

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
   \class   FullLepKinAnalyzer FullLepKinAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/FullLepKinAnalyzer.h"

   \brief   simple EDAnalyzer for FullLeptonicEvent hypotheses with electrons and muons

   This is a cleaned up version of the FullLepHypothesesAnalyzer
   The analyzer needs TtFullLeptonicEvents as input and plots the kinematic quantities of some reconstructed particles
   in the ttbar decay chain. For the different hypotheses different quality plots are filled.
*/

class FullLepKinAnalyzer : public edm::EDAnalyzer {

 public:
  /// default constructor
  explicit FullLepKinAnalyzer(const edm::ParameterSet&);
  /// default destructor
  ~FullLepKinAnalyzer();
  
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
  /// inputJetCollection
  edm::InputTag jets_;
  
  
  /// book histograms for reconstructed particles properties: Pt, E, Eta, Phi, m
  void bookKinHistos      (edm::Service<TFileService>&);
  /// book histograms for generated particles properties: Pt, E, Eta, Phi, m
  void bookGenHistos      (edm::Service<TFileService>&);  
  /// book histograms for pulls of particle properties: Pt, E, Eta, Phi, m
  void bookPullHistos     (edm::Service<TFileService>&);    
  /// book histograms for kin hypothesis specific histos
  void bookQualityHistos  (edm::Service<TFileService>&);
  /// fill histograms for reconstructed particles properties in events with oppositely charged leptons: Pt, E, Eta, Phi, m
  void fillKinHistos           (std::vector<TH1D*>&, 
                                const reco::Candidate&);
  /// fill histograms for pulls of particle properties in events with oppositely charged leptons: Pt, E, Eta, Phi, m
  void fillPullHistos           (std::vector<TH1D*>&, 
                                 const reco::Candidate&,
				 const reco::Candidate&);								
				
  /// book histograms for kin hypothesis specific histos							
  void fillQualityHistos       (const TtFullLeptonicEvent&,
                                const TtEvent::HypoClassKey&);

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
  /// histograms for top pair kinematics
  std::vector<TH1D*> TtBarKin_;  
  /// histograms for lepton kinematics
  std::vector<TH1D*> LepLepBarKin_;
  
  
  /// histograms for generated top quark kinematics
  std::vector<TH1D*> TopGen_;
  /// histograms for generated W^+ kinematics
  std::vector<TH1D*> WplusGen_;
  /// histograms for generated B kinematics
  std::vector<TH1D*> BGen_;
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
  /// histograms for generated l^- kinematics
  std::vector<TH1D*> LepGen_;
  /// histograms for generated anti-neutrino kinematics
  std::vector<TH1D*> NuBarGen_;  
  /// histograms for generated top pair kinematics
  std::vector<TH1D*> TtBarGen_;
  /// histograms for generated lepton pair kinematics
  std::vector<TH1D*> LepLepBarGen_;
    

  /// histograms for pull distributions
  std::vector<TH1D*> TopPull_;
  /// histograms for  pull of W^+ kinematics
  std::vector<TH1D*> WplusPull_;
  /// histograms for  pull of B kinematics
  std::vector<TH1D*> BPull_;
  /// histograms for  pull of l^+ kinematics
  std::vector<TH1D*> LepBarPull_;
  /// histograms for  of neutrino kinematics
  std::vector<TH1D*> NuPull_; 
  /// histograms for  pull of anti-top quark kinematics 
  std::vector<TH1D*> TopBarPull_;
  /// histograms for  pull of W^- quark kinematics
  std::vector<TH1D*> WminusPull_;
  /// histograms for  pull of anti-b kinematics
  std::vector<TH1D*> BBarPull_;
  /// histograms for  pull of l^- kinematics
  std::vector<TH1D*> LepPull_;
  /// histograms for  pull of anti-neutrino kinematics
  std::vector<TH1D*> NuBarPull_;
  /// histograms for  pull of top pair kinematics
  std::vector<TH1D*> TtBarPull_;
  /// histograms for  pull of lepton pair kinematics
  std::vector<TH1D*> LepLepBarPull_;  
    

  /// histogram only for kinSolution hypothesis: weight from neutrino spectrum of best kinematic solution
  TH1D* kinSolWeight_;
  
  /// histogram for index of bJet in jet collection used for the event reconstruction
  TH1D* bJetIdcs_;
  /// histogram for index of bBarJet in jet collection used for the event reconstruction
  TH1D* bBarJetIdcs_; 
  
  /// historgram for the mass difference between reconstructed top and anti-top.
  /// For kinSolution hypothesis it should give a sharp peak around zero since the assumption that both masses
  /// are equal is used as a boundary condition. Differences appear only from rounding errors
  TH1D* deltaM_;
  /// correlation between event reco and b-tagging TCHE
  TH2D* kinTCHEcorrelation_;
  /// correlation between event reco and b-tagging SSVHE
  TH2D* kinSSVHEcorrelation_;      
};

#endif
