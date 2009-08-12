#ifndef TopKinematics_h
#define TopKinematics_h

#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

/**
   \class   TopKinematics TopKinematics.h "TopAnalysis/TopAnalyzer/interface/TopKinematics.h"

   \brief   Derived class to analyze the kinematics of top quarks on reconstruction and generator level

   The structure keeps histograms for the kinematics of top quarks and ttbar pairs. These histograms 
   can be filled from the TtSemiLeptonicEvent (with an extra option to require matching for purity &
   stability studies) or from TtGenEvent. The class is derived from the SingleObject interface, which 
   makes it usable in full framework (fw) or fwlite. 
*/

class TopKinematics : public SingleObject<TtSemiLeptonicEvent> {

 public:
  /// default constructor for generator level analysis in fw lite
  explicit TopKinematics();
  /// default constructor for reco level analysis in fw lite
  explicit TopKinematics(const std::string& hypoKey, const bool& matchForStabilityAndPurity);
  /// default constructor for full fw
  explicit TopKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~TopKinematics(){};

  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling interface for rec level for access with fw or fwlite
  void fill(const TtSemiLeptonicEvent& tops, const double& weight=1.);
  /// histogram filling interface for gen level for access with fw or fwlite 
  void fill(const TtGenEvent& tops, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};

 private:
  /// histogram filling for candidates topA and topB
  void fill(const reco::Candidate* topA, const reco::Candidate* topB, const double& weight=1.);
  /// histogram filling for candidate topA and topB (for stability and purity calculation)
  void fill(const reco::Candidate* recTopA, const reco::Candidate* genTopA, const reco::Candidate* recTopB, const reco::Candidate* genTopB, const double& weight=1.);
  /// helper function for determining stability and purity
  void match(TH1* hist, const double& genValue, const double& recValue, const double& weight);

 private:
  /// class key of hypothesis
  std::string hypoKey_;
  /// apply matchin for stability and purity or not
  bool matchForStabilityAndPurity_;
};

#endif
