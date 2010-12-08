#ifndef MuonVertexKinematics_h
#define MuonVertexKinematics_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

/**
   \class   MuonVertexKinematics MuonVertexKinematics.h "TopAnalysis/TopKinematics/interface/MuonVertexKinematics.h"

   \brief   Derived class to analyze the relation between muons and the PV on reconstruction level

   The structure keeps histograms to analyze the relation between muons and the PV vertex on reconstruction level. 
   These histograms can be filled from edm::View<pat::Muon>'s and edm::View<reco::Vertex>. The 
   class is derived from the DoubleObject<CollectionA, CollectionB> interface, which makes it usable in 
   fwfull or fwlite. This class is expected to be used with well defined muons and a well defined 
   collection of jets.
*/

class MuonVertexKinematics : public DoubleObject<const edm::View<pat::Muon>, const edm::View<reco::Vertex> > {

 public:
  /// default constructor for fwlite
  explicit MuonVertexKinematics(const int index);
  /// default constructor for fwfull
  explicit MuonVertexKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonVertexKinematics(){};

  /**
     The following functions have to be implemented for any class
     derived from DoubleObject<CollectionA, CollectionB>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for full fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling
  void fill(const edm::View<pat::Muon>& muons, const edm::View<reco::Vertex>& primaryVertex, const double& weight=1.);
  /// histogram filling
  void fill(const edm::View<pat::Muon>& muons, const double& weight=1.){ 
    std::string exception;
    exception += "-----------------------------------------------------------------------------\n";
    exception += "NOTE: You omitted the parameter _srcB_ in your configuration file, which is  \n";
    exception += "      not optional in this case. The program will terminate here. Check what \n";
    exception += "      parameters are expected in the definition of your module.              \n";
    exception += "-----------------------------------------------------------------------------\n";
    throw edm::Exception(edm::errors::Configuration, exception);
  }
  /// everything which needs to be done after the event loop
  void process(){};

 private:
  /// index of muon to be plotted
  int index_;
};

#endif
