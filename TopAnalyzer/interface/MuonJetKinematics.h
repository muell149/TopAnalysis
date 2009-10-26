#ifndef MuonJetKinematics_h
#define MuonJetKinematics_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"

/**
   \class   MuonJetKinematics MuonJetKinematics.h "TopAnalysis/TopAnalyzer/interface/MuonJetKinematics.h"

   \brief   Derived class to analyze the relation between muons jets on reconstruction level

   The structure keeps histograms to analyze the relation between muons and jets on recostruction level. 
   These histograms can be filled from edm::View<pat::Muon>'s and edm::View<pat::Jet>'s only(!). The 
   class is derived from the DoubleObject<CollectionA, CollectionB> interface, which makes it usable in 
   fwfull or fwlite. This class is expected to be used with well defined isolated muons and a well defined 
   collection of jets. There is no implicit eta restriction on the jet collection applied within the 
   analyzer!
*/

class MuonJetKinematics : public DoubleObject<const edm::View<pat::Muon>, const edm::View<pat::Jet> > {

 public:
  /// default constructor for fwlite
  explicit MuonJetKinematics();
  /// default constructor for fwfull
  explicit MuonJetKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonJetKinematics(){};

  /**
     The following functions have to be implemented for any class
     derived from DoubleObject<CollectionA, CollectionB>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fwfull
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for fwfull
  void fill(const edm::View<pat::Muon>& muons, const edm::View<pat::Jet>& jets, const double& weight=1.);
  /// everything which needs to be done after the event loop
    void process(){};

 private:
  /// there is no further steering parameters
};

#endif
