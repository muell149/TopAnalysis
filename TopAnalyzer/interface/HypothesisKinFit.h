#ifndef HypothesisKinFit_h
#define HypothesisKinFit_h

#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

/**
   \class   HypothesisKinFit HypothesisKinFit.h "TopAnalysis/TopAnalyzer/interface/HypothesisKinFit.h"

   \brief   Derived class to analyze the kinematic fit hypothesis of semileptonic ttbar events

   The structure keeps control histograms for the kinematics fit hypothesis of semi-leptonic ttbar 
   events. These histograms are be filled from the TtSemiLeptonicEvent class. The class is derived 
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
  /// input tag for selected jets
  edm::InputTag jets_;
  /// input tag for selected mets
  edm::InputTag mets_;
  /// input tag for selected muons
  edm::InputTag muons_;

  /// maximal allowed sum of DR for genMatch hypothesis
  double maxGenMatchSumDR_;
  /// maximal allowed sum of Pt for genMatch hypothesis
  double maxGenMatchSumPt_;

  /// histogram container for correlation plots
  std::map<std::string, TH2*> corrs_;
};

#endif
