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
  /// helper function to recieve the object index in the reco collection for hypothesis
  /// 'hypo' and object index 'index' in the TtSemiLepEvtPartons definition
  int objectIndex(const TtSemiLeptonicEvent& tops, const std::string& hypo, const int& index) const { return tops.jetLeptonCombination(hypo)[index]; };
  /// helper function to recieve the difference of object indices in the reco 
  /// collections  between the genMatch and kinFit hypotheses
  int delObjectIndex(const TtSemiLeptonicEvent& tops, const int& index) const { return objectIndex(tops, "kGenMatch", index)-objectIndex(tops, "kKinFit", index); };

 private:
  /// histogram container for correlation plots
  std::map<std::string, TH2*> corrs_;
};

#endif
