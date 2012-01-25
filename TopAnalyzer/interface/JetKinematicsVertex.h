#ifndef JetKinematicsVertex_h
#define JetKinematicsVertex_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

/**
   \class   JetKinematicsVertex JetKinematicsVertex.h "TopAnalysis/TopAnalyzer/interface/JetKinematicsVertex.h"

   \brief   Derived class to analyze the kinematics of jets on reconstruction and generator level and the primary vertex distribution

   The structure keeps histograms for the kinematics of jets and the primary vertices. These histograms can be 
   filled from edm::View<pat::Jet>'s or from std::vector<reco::GenParticles>'s. The class is
   derived from the DoubleObject<Collection> interface, which makes it usable in fwfull  or 
   fwlite. 
*/

class JetKinematicsVertex : public DoubleObject<const edm::View<pat::Jet>, const edm::View<reco::Vertex> > {

 public:
  /// default constructor for fw lite
   explicit JetKinematicsVertex(const int index, const std::string& correctionLevel);
  /// default constructor for full fw
  explicit JetKinematicsVertex(const edm::ParameterSet& configFile);
  /// default destructor
  ~JetKinematicsVertex(){};

  /**
     The following functions have to be implemented for any class
     derived from DoubleObject<Collection>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fwfull
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for fwfull from reco objects
  void fill(const edm::View<pat::Jet>& jets, const edm::View<reco::Vertex>& vertices, const double& weight=1.);
  void fill(const edm::View<pat::Jet>& jets, const double& weight=1.){ 
    std::string exception;
    exception += "-----------------------------------------------------------------------------\n";
    exception += "NOTE: You omitted the parameter _srcB_ in your configuration file, which is  \n";
    exception += "      not optional in this case. The program will terminate here. Check what \n";
    exception += "      parameters are expected in the definition of your module.              \n";
    exception += "-----------------------------------------------------------------------------\n";
    throw edm::Exception(edm::errors::Configuration, exception);
  }

  /// histogram filling for fwlite and for fwfull from generator objects
  void fill(const std::vector<reco::GenJet>& jets, const edm::View<reco::Vertex>& vertices, const double& weight=1.);
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
