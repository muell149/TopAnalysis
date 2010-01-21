#ifndef TopKinematics_h
#define TopKinematics_h

#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "TMath.h"

/**
   \class   TopKinematics TopKinematics.h "TopAnalysis/TopAnalyzer/interface/TopKinematics.h"

   \brief   Derived class to analyze the kinematics of top quarks on reconstruction and generator level

   The structure keeps histograms for the kinematics of top quarks and ttbar pairs. These histograms 
   can be filled from the TtSemiLeptonicEvent class (with an extra option to require matching for 
   purity & stability studies) or from the TtGenEvent class. The class is derived from the 
   SingleObject<Collection> interface, which makes it usable in full framework or fwlite. 
*/
double pi = TMath::Pi();

namespace CrossSection{
 // binning for top & ttbar cross section histograms
 double topPt       [] = {             0. ,    10. ,    35. ,    65. ,   100. ,   135. ,   170. ,   215. ,   300. ,   400.  };
 double topY        [] = {   -4. ,    -3. ,  -1.92 ,   -1.2 ,  -0.48 ,     0. ,   0.48 ,    1.2 ,   1.92 ,     3. ,     4.  };
 double topPhi      [] = {                                       -pi ,   -2.0 ,   -1.0 ,     0. ,     1. ,     2. ,     pi  };
 double ttbarMass   [] = {                                      300. ,   345. ,   400. ,   490. ,   615. ,   790. ,  1000.  };
 double ttbarPt     [] = {                      0. ,    10. ,    20. ,    30. ,    40. ,    60. ,    80. ,   130. ,   200.  };
 double ttbarY      [] = {   -5. ,    -4. ,    -3. ,   -2.3 ,   -1.6 ,     0. ,    1.6 ,    2.3 ,     3. ,     4. ,     5.  };
 double ttbarPhi    [] = {                                       -pi ,   -2.0 ,   -1.0 ,     0. ,     1. ,     2. ,     pi  };
 double ttbarDelPhi [] = {                                       -pi ,   -2.0 ,   -1.0 ,     0. ,     1. ,     2. ,     pi  };
 double topWAnglelab[] = {                                        0. ,   0.15 ,   0.25 ,    0.4 ,    0.6 ,     1. ,     pi  };
 double topWAngletop[] = {                                        0. , 1./6*pi, 1./3*pi, 1./2*pi, 2./3*pi, 5./6*pi,     pi  };
}

class TopKinematics : public SingleObject<TtSemiLeptonicEvent> {
  
 public:
  /// default constructor for generator level analysis in fw lite
  explicit TopKinematics();
  /// default constructor for reco level analysis in fw lite
  explicit TopKinematics(const std::string& hypoKey, const bool& matchForStabilityAndPurity);
  /// default constructor for fwfull
  explicit TopKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~TopKinematics(){};

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
  /// histogram filling interface for generator level for access with fw or fwlite 
  void fill(const TtGenEvent& tops, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};

 private:
  /**
     Helper functions for special histogram management
  **/
  /// histogram filling for candidates topA and topB
  void fill(const reco::Candidate* leptonicTop, const reco::Candidate* hadronicTop, const reco::Candidate* leptonicW, const reco::Candidate* hadronicW, double HT, const double& weight=1.);
  /// histogram filling for candidate topA and topB (for stability and purity calculation)
  void fill(const reco::Candidate* leptonicTopRec, const reco::Candidate* leptonicTopGen, const reco::Candidate* hadronicTopRec, const reco::Candidate* hadronicTopGen, const reco::Candidate* leptonicWRec, const reco::Candidate* leptonicWGen, const reco::Candidate* hadronicWRec, const reco::Candidate* hadronicWGen, double HTrec, double HTgen, const double& weight=1.);
  /// helper function for determining stability and purity
  void match(TH1* hist, const double& genValue, const double& recValue, const double& weight);

 private:
  /// class key of hypothesis
  std::string hypoKey_;
  /// apply matching for stability and purity or not
  bool matchForStabilityAndPurity_;

  /// histogram container for correlation plots
  std::map<std::string, TH2*> corrs_;
};

#endif
