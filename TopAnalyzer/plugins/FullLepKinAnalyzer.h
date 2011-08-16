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


  /// book histograms for reconstructed particles properties: Pt, E, Eta, Phi, m
  void bookKinHistos      (edm::Service<TFileService>&);
  /// book histograms for generated particles properties: Pt, E, Eta, Phi, m
  void bookGenHistos      (edm::Service<TFileService>&);
  /// book histograms for pulls of particle properties: Pt, E, Eta, Phi, m
  void bookPullHistos     (edm::Service<TFileService>&);
  /// book histograms for 2D distributions of particle properties: Pt, E, Eta, Phi, m
  void book2DHistos(edm::Service<TFileService>&);
  /// book histograms for 2D correlations between reconstructed quantities
  void bookRecCorrelHistos(edm::Service<TFileService>&);
  /// book histograms for kin hypothesis specific histos
  void bookQualityHistos  (edm::Service<TFileService>&);
  /// fill histograms for reconstructed particles properties in events with oppositely charged leptons: Pt, E, Eta, Phi, m
  void fillKinHistos           (std::vector<TH1D*>&,
                                const reco::Candidate&,
                                double
                               );
  /// fill histograms for pulls of particle properties in events with oppositely charged leptons: Pt, E, Eta, Phi, m
  void fillPullHistos           (std::vector<TH1D*>&,
                                 TH2D& hist2D,
                                 const reco::Candidate&,
				 const reco::Candidate&,
                                 double
                                );
  /// fill histograms for 2D distributions of particle properties in events with oppositely charged leptons: Pt, E, Eta, Phi, m
  void fill2DHistos           (std::vector<TH2D*>&,
                               const reco::Candidate&,
			       const reco::Candidate&,
                               double
                              );

  /// fill histograms for kin hypothesis specific histos
  void fillQualityHistos       (const TtFullLeptonicEvent&,
                                const TtEvent::HypoClassKey&,
                                double
                               );

  bool isRealBJet(const reco::Candidate&,
                  const reco::Candidate&,
		  const reco::Candidate&
                 );

  /// book and fill additional plots with gen information?
  bool isSignalMC_;
  /// is b-tagging taken into account to choose best hypothessis
  bool useBtagging_;
  /// b-tagging algorithm to be used
  std::string bAlgo_;
  /// cut value for b-tagging
  double bCut_;
  /// input given in config has to be TtFullLeptonicEvent
  edm::InputTag FullLepEvt_;
  /// keyword for hypothesis from config: ttFullLepHypKinSolution:Key or ttFullLepHypGenMatch:Key
  edm::InputTag hypoKey_;
  /// inputJetCollection
  edm::InputTag jets_;
  /// pile-up weight
  edm::InputTag weight_;

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
  /// histograms for dilepton kinematics
  std::vector<TH1D*> LepPairKin_;
  /// histograms for dijet kinematics
  std::vector<TH1D*> JetPairKin_;


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
  std::vector<TH1D*> LepPairGen_;
  /// histograms for generated jet pair kinematics
  std::vector<TH1D*> JetPairGen_;


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
  std::vector<TH1D*> LepPairPull_;
  /// histograms for  pull of jet pair kinematics
  std::vector<TH1D*> JetPairPull_;


  /// histograms for 2D distributions
  std::vector<TH2D*> Top2D_;
  /// histograms for 2D distributions of W^+ kinematics
  std::vector<TH2D*> Wplus2D_;
  /// histograms for  2D distributions of B kinematics
  std::vector<TH2D*> B2D_;
  /// histograms for  2D distributions of l^+ kinematics
  std::vector<TH2D*> LepBar2D_;
  /// histograms for 2D distributions of neutrino kinematics
  std::vector<TH2D*> Nu2D_;
  /// histograms for  2D distributions of anti-top quark kinematics
  std::vector<TH2D*> TopBar2D_;
  /// histograms for  2D distributions of W^- quark kinematics
  std::vector<TH2D*> Wminus2D_;
  /// histograms for  2D distributions of anti-b kinematics
  std::vector<TH2D*> BBar2D_;
  /// histograms for  2D distributions of l^- kinematics
  std::vector<TH2D*> Lep2D_;
  /// histograms for  2D distributions of anti-neutrino kinematics
  std::vector<TH2D*> NuBar2D_;
  /// histograms for  2D distributions of top pair kinematics
  std::vector<TH2D*> TtBar2D_;
  /// histograms for  2D distributions of lepton pair kinematics
  std::vector<TH2D*> LepPair2D_;
  /// histograms for  2D distributions of jet pair kinematics
  std::vector<TH2D*> JetPair2D_;


  /// 2 dimensional eta-phi pulls
  TH2D* TopPull2D_;
  /// histogram for  pull of W^+ kinematics
  TH2D* WplusPull2D_;
  /// histogram for  pull of B kinematics
  TH2D* BPull2D_;
  /// histogram for  pull of l^+ kinematics
  TH2D* LepBarPull2D_;
  /// histograms for  of neutrino kinematics
  TH2D* NuPull2D_;
  /// histogram for  pull of anti-top quark kinematics
  TH2D* TopBarPull2D_;
  /// histogram for  pull of W^- quark kinematics
  TH2D* WminusPull2D_;
  /// histogram for  pull of anti-b kinematics
  TH2D* BBarPull2D_;
  /// histogram for  pull of l^- kinematics
  TH2D* LepPull2D_;
  /// histogram for  pull of anti-neutrino kinematics
  TH2D* NuBarPull2D_;
  /// histogram for  pull of top pair kinematics
  TH2D* TtBarPull2D_;
  /// histogram for  pull of lepton pair kinematics
  TH2D* LepPairPull2D_;
  /// histogram for  pull of jet pair kinematics
  TH2D* JetPairPull2D_;


  /// histogram only for kinSolution hypothesis: weight from neutrino spectrum of best kinematic solution
  TH1D* kinSolWeight_;
  /// histogram for index of bJet in jet collection used for the event reconstruction
  TH1D* bJetIdcs_;
  /// histogram for index of bBarJet in jet collection used for the event reconstruction
  TH1D* bBarJetIdcs_;

  /// histogram for the mass difference between reconstructed top and anti-top.
  /// For kinSolution hypothesis it should give a sharp peak around zero since the assumption that both masses
  /// are equal is used as a boundary condition. Differences appear only from rounding errors
  TH1D* deltaM_;
  /// invariant mass of anti-lepton and b-jet
  TH1D* LepBarBMass_;
  /// invariant mass of lepton and b-jet  
  TH1D* LepBMass_;
  /// invariant mass of lepton and bbar-jet
  TH1D* LepBBarMass_;
  /// invariant mass of anti-lepton and bbar-jet  
  TH1D* LepBarBBarMass_;  
  /// correlation between event reco and b-tagging TCHEL
  TH2D* kinTCHELcorrelation_;
  /// correlation between event reco and b-tagging TCHEM
  TH2D* kinTCHEMcorrelation_;
  /// correlation between event reco and b-tagging SSVHEM
  TH2D* kinSSVHEMcorrelation_;
  /// compares indices of objects in gen and kin hypotheses
  TH2D* compare_;

  /// correlation histograms for different reconstructed quantities
  TH2D* diLeptonMassVsLeptonPt_;
  TH2D* diLeptonMassVsLeptonEta_;
  TH2D* diLeptonMassVsDiLeptonPt_;
  TH2D* diLeptonMassVsTopPt_;
  TH2D* diLeptonMassVsTopRapidity_;
  TH2D* diLeptonMassVsTtBarPt_;
  TH2D* diLeptonMassVsTtBarRapidity_;
  TH2D* diLeptonMassVsTtBarMass_;
  
  // correlation between number of tagged jets and relevant quantities for differential cross sections
  TH2D* nBtagsTCHELVsLeptonPt_;
  TH2D* nBtagsTCHELVsLeptonEta_;
  TH2D* nBtagsTCHELVsDiLeptonPt_;
  TH2D* nBtagsTCHELVsDiLeptonMass_;
  TH2D* nBtagsTCHELVsTopPt_;
  TH2D* nBtagsTCHELVsTopRapidity_;
  TH2D* nBtagsTCHELVsTtBarPt_;
  TH2D* nBtagsTCHELVsTtBarRapidity_;
  TH2D* nBtagsTCHELVsTtBarMass_;

  TH2D* nBtagsTCHEMVsLeptonPt_;
  TH2D* nBtagsTCHEMVsLeptonEta_;
  TH2D* nBtagsTCHEMVsDiLeptonPt_;
  TH2D* nBtagsTCHEMVsDiLeptonMass_;
  TH2D* nBtagsTCHEMVsTopPt_;
  TH2D* nBtagsTCHEMVsTopRapidity_;
  TH2D* nBtagsTCHEMVsTtBarPt_;
  TH2D* nBtagsTCHEMVsTtBarRapidity_;
  TH2D* nBtagsTCHEMVsTtBarMass_;

  TH2D* nBtagsSSVHEMVsLeptonPt_;
  TH2D* nBtagsSSVHEMVsLeptonEta_;
  TH2D* nBtagsSSVHEMVsDiLeptonPt_;
  TH2D* nBtagsSSVHEMVsDiLeptonMass_;
  TH2D* nBtagsSSVHEMVsTopPt_;
  TH2D* nBtagsSSVHEMVsTopRapidity_;
  TH2D* nBtagsSSVHEMVsTtBarPt_;
  TH2D* nBtagsSSVHEMVsTtBarRapidity_;
  TH2D* nBtagsSSVHEMVsTtBarMass_;
    
  // correlation between number of matched jets and relevant quantities for differential cross sections
  TH2D* nMatchesVsLeptonPt_;
  TH2D* nMatchesVsLeptonEta_;
  TH2D* nMatchesVsDiLeptonPt_;
  TH2D* nMatchesVsDiLeptonMass_;
  TH2D* nMatchesVsTopPt_;
  TH2D* nMatchesVsTopRapidity_;
  TH2D* nMatchesVsTtBarPt_;
  TH2D* nMatchesVsTtBarRapidity_;
  TH2D* nMatchesVsTtBarMass_; 
  
  /// number of btags vs number of jets matched to b quarks
  TH2D* nMatchVsNtagsTCHEL_;
  TH2D* nMatchVsNtagsTCHEM_;
  TH2D* nMatchVsNtagsSSVHEM_; 
};

#endif
