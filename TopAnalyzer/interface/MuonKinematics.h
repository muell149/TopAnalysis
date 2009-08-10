#ifndef MuonKinematics_h
#define MuonKinematics_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

/**
   \class   MuonKinematics MuonKinematics.h "TopAnalysis/TopAnalyzer/interface/MuonKinematics.h"

   \brief   Derived class to analyze the kinematics of muons on reconstruction and generator level

   The structure keeps histograms for the kinematics of muons only. These histograms can be filled 
   from std::vector<pat::Muon>'s or from std::vector<reco::GenParticles>'s. The class is derived 
   from the SingleObject interface, which makes it usable in full framework (fw) or fwlite. 
*/

class MuonKinematics : public SingleObject<const std::vector<pat::Muon> > {

 public:
  /// default constructor for fw lite
  explicit MuonKinematics();
  /// default constructor for full fw
  explicit MuonKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonKinematics(){};

  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for full fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for full fw from reco objects
  void fill(const std::vector<pat::Muon>& muons, const double& weight=1.);
  /// histogram filling for fwlite and for full fw from generator objecst
  void fill(const std::vector<reco::GenParticle>& muons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process() {};

 private:
  /// steering parameters will go here
};

#endif
