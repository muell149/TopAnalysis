#ifndef FullHadQCDEstimation_h
#define FullHadQCDEstimation_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TopQuarkAnalysis/TopKinFitter/interface/TtFullHadKinFitter.h"

/**
   \class   FullHadQCDEstimation FullHadQCDEstimation.h "TopAnalysis/TopAnalyzer/interface/FullHadQCDEstimation.h"

   \brief   Derived class to analyze the kinematics of jets on reconstruction and generator level

   The structure keeps histograms for the kinematics of jets only(!). These histograms can be 
   filled from edm::View<pat::Jet>'s or from std::vector<reco::GenParticles>'s. The class is
   derived from the SingleObject<Collection> interface, which makes it usable in fwfull  or 
   fwlite. 
*/

class FullHadQCDEstimation : public SingleObject<const edm::View<pat::Jet> > {

 public:
  /// default constructor for fw lite
  explicit FullHadQCDEstimation();
  /// default constructor for full fw
  explicit FullHadQCDEstimation(const edm::ParameterSet& configFile);
  /// default destructor
  ~FullHadQCDEstimation(){};

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fwfull
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for fwfull from reco objects
  void fill(const edm::View<pat::Jet>& jets, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process() {};

 private:
  /// produce a TTree as output instead of histograms
  bool useTree_;
  /// store resolutions for the kinematic fit
  std::vector<edm::ParameterSet> udscResolutions_;
  std::vector<edm::ParameterSet> bResolutions_;

  /// kinematic fit interface
  TtFullHadKinFitter::KinFit* kinFitter;
};

#endif
