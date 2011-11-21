#ifndef JetKinematics_h
#define JetKinematics_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

/**
   \class   JetKinematics JetKinematics.h "TopAnalysis/TopAnalyzer/interface/JetKinematics.h"

   \brief   Derived class to analyze the kinematics of jets on reconstruction and generator level

   The structure keeps histograms for the kinematics of jets only(!). These histograms can be 
   filled from edm::View<reco::Jet>'s while pat::Jet's and reco::GenJet's can be used. For 
   pat::Jet's additional informations concerning the JES correction can be specified which will 
   be ignored otherwise The class is derived from the SingleObject<Collection> interface, which 
   makes it usable in fwfull or fwlite. 
*/

class JetKinematics : public SingleObject< const edm::View<reco::Jet> > {

 public:
  /// default constructor for fw lite
  explicit JetKinematics(const int index, const std::string& correctionLevel);
  /// default constructor for full fw
  explicit JetKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~JetKinematics(){};

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fwfull
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for fwfull from reco::Jet objects
  void fill(const edm::View<reco::Jet>& jets, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process() {};

 private:
  /// return the desired correction step from the configuration string,
  /// which is expected to be of type 'step' or 'step:flavor'
  const std::string correctionStep() const;
  /// return the desired correction flavor from the configuration string,
  /// which is expected to be of type 'step' or 'step:flavor'
  const std::string correctionFlavor() const;

 private:
  /// produce a TTree as output instead of histograms
  bool useTree_;
  /// index of jet to be plotted
  int index_;
  /// JES correction level
  std::string correctionLevel_;
};

#endif
