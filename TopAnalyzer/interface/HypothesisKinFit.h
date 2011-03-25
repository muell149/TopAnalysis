#ifndef HypothesisKinFit_h
#define HypothesisKinFit_h

#include "TTree.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

/**
   \class   HypothesisKinFit HypothesisKinFit.h "TopAnalysis/TopAnalyzer/interface/HypothesisKinFit.h"

   \brief   Derived class to analyze the kinematic fit hypothesis of semileptonic ttbar events

   The structure keeps control histograms for the kinematics of the reconstructed objects for the 
   chosen fit hypothesis for semi-leptonic ttbar events. Among these are quantities showing monitoring 
   variables of the fit, pull distributions and correlation plots for the reconstructed objects.
   These histograms are be filled from the TtSemiLeptonicEvent class. The class is derived 
   from the SingleObject<Collection> interface, which makes it usable in full framework or fwlite. 
*/

class HypothesisKinFit : public SingleObject<TtSemiLeptonicEvent> {

 public:
  /// default constructor for fw lite
  explicit HypothesisKinFit();
  /// default constructor for fw full
  explicit HypothesisKinFit(const edm::ParameterSet& configFile);
  /// default destructor
  ~HypothesisKinFit(){};

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>. The fill function is
     overloaded to serve both for the TtGenEvent class directoy or 
     the TtSemiLeptonicEvent class.
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling interface for reconstruction level for access with fw or fwlite
  void fill(const TtSemiLeptonicEvent& tops, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};

 private:
  /// helper function to recieve the object index in the reco collection for hypothesis
  /// 'hypo' and object index 'index' in the TtSemiLepEvtPartons definition
  int objectIndex(const TtSemiLeptonicEvent& tops, const std::string& hypo, const int& index) const { return tops.jetLeptonCombination(hypo)[index]; };
  /// helper function to recieve the difference of object indices in the reco 
  /// collections  between the genMatch and kinFit hypotheses
  int delObjectIndex(const TtSemiLeptonicEvent& tops, const int& index,  const std::string& hypo);

 private:
  /// class key of hypothesis
  std::string hypoKey_;
  /// bool to enable or disable ttree output
  bool wantTree;
  /// number of jets considered in Kinematic fit (needed for the classification of permutations)
  int maxNJets;
  /// histogram container for correlation plots
  std::map<std::string, TH2*> corrs_;
  /// all avriables used to fill the tree
  TTree* tree;
  int numberOfDifferingIndices;
  int hadBIndexDiff;
  int lepBIndexDiff;
  int lepBIndex;
  int hadBIndex;
  int lightQIndex;
  int lightQBarIndex;
  int lepBIndexGen;
  int hadBIndexGen;
  int lightQIndexGen;
  int lightQBarIndexGen;
  int lightQIndexDiff;
  int lightQBarIndexDiff;
  float hadTopMass;
  float lepTopMass;
  float TopMass2ndchi2;
  float TopMass3rdchi2;
  float TopMass4thchi2;
  float TopMass5thchi2;
  float TopMass6thchi2;
  float TopMass7thchi2;
  float TopMass8thchi2;
  float TopMass9thchi2;
  float TopMass10thchi2;
  float hadWMass;
  float lepWMass;
  float prob;
  float chi2;
  float delChi2;
  int numberOfDifferingIndicesKinFit;
  int hadBIndexDiffKinFit;
  int lepBIndexDiffKinFit;
  int lightQIndexDiffKinFit;
  int lightQBarIndexDiffKinFit;
  float hadTopMassKinFit;
  float lepTopMassKinFit;
  float hadWMassKinFit;
  float lepWMassKinFit;
  float lepBpt_gen;
  float lepBphi_gen;
  float lepBeta_gen;
  float hadBpt_gen;
  float hadBphi_gen;
  float hadBeta_gen;
  float lightQpt_gen;
  float lightQphi_gen;
  float lightQeta_gen;
  float lightQBarpt_gen;
  float lightQBarphi_gen;
  float lightQBareta_gen;
  float leptonpt_gen;
  float leptonphi_gen;
  float leptoneta_gen;
  float neutrinopt_gen;
  float neutrinophi_gen;
  float neutrinoeta_gen;
  float lepWpt_gen;
  float lepWphi_gen;
  float lepWeta_gen;
  float hadWpt_gen;
  float hadWphi_gen;
  float hadWeta_gen;
  float lepToppt_gen; 
  float lepTopphi_gen;
  float lepTopeta_gen;
  float lepTopY_gen;
  float hadToppt_gen; 
  float hadTopphi_gen;
  float hadTopeta_gen;
  float hadTopY_gen;
  float ttBarpt_gen; 
  float ttBarphi_gen;
  float ttBareta_gen;
  float ttBarY_gen;
  float ttBarMass_gen;
  float ttBarDelPhi_gen;
  float ttBarDelY_gen;
  float ttBarSumY_gen;
  float lepBpt_fit;
  float lepBphi_fit;
  float lepBeta_fit;
  float hadBpt_fit;
  float hadBphi_fit;
  float hadBeta_fit;
  float lightQpt_fit;
  float lightQphi_fit;
  float lightQeta_fit;
  float lightQBarpt_fit;
  float lightQBarphi_fit;
  float lightQBareta_fit;
  float leptonpt_fit;
  float leptonphi_fit;
  float leptoneta_fit;
  float neutrinopt_fit;
  float neutrinophi_fit;
  float neutrinoeta_fit;
  float lepWpt_fit;
  float lepWphi_fit;
  float lepWeta_fit;
  float hadWpt_fit;
  float hadWphi_fit;
  float hadWeta_fit;
  float lepToppt_fit; 
  float lepTopphi_fit;
  float lepTopeta_fit;
  float lepTopY_fit;
  float hadToppt_fit; 
  float hadTopphi_fit;
  float hadTopeta_fit;
  float hadTopY_fit;
  float ttBarpt_fit; 
  float ttBarphi_fit;
  float ttBareta_fit;
  float ttBarY_fit;
  float ttBarMass_fit;
  float ttBarDelPhi_fit;
  float ttBarDelY_fit;
  float ttBarSumY_fit;
  int assignment;
};

#endif
