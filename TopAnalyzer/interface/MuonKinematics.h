#ifndef MuonKinematics_h
#define MuonKinematics_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

/**
   \class   MuonKinematics MuonKinematics.h "TopAnalysis/TopAnalyzer/interface/MuonKinematics.h"

   \brief   Derived class to analyze the kinematics of muons on reconstruction and generator level

   The structure keeps histograms for the kinematics of muons only(!). These histograms can be 
   filled from std::vector<pat::Muon>'s or from std::vector<reco::GenParticles>'s. The class 
   is derived from the SingleObject<Collection> interface, which makes it usable in fwfull  or 
   fwlite. 
*/

class MuonKinematics : public SingleObject<const std::vector<pat::Muon> > {

 public:
  /// default constructor for fw lite
  explicit MuonKinematics(const int index);
  /// default constructor for full fw
  explicit MuonKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonKinematics(){};

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fwfull
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for fwfull from reco objects
  void fill(const std::vector<pat::Muon>& muons, const double& weight=1.);
  /// histogram filling for fwlite and for fwfull from generator objects
  void fill(const std::vector<reco::GenParticle>& muons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process() {};

 private:
  /// index of jet to be plotted
  int index_;
};

#endif
