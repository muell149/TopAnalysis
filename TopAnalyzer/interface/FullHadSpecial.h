#ifndef FullHadSpecial_h
#define FullHadSpecial_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

/**
   \class   FullHadSpecial FullHadSpecial.h "TopAnalysis/TopAnalyzer/interface/FullHadSpecial.h"

   \brief   Derived class to analyze variables for full hadronic analysis

   The structure keeps histograms. The class is derived from the 
   SingleObject<Collection> interface, which makes it usable in fwfull or fwlite. 
*/

class FullHadSpecial : public SingleObject<const edm::View<pat::Jet> > {

 public:
  /// default constructor for fw lite
  explicit FullHadSpecial();
  /// default constructor for full fw
  explicit FullHadSpecial(const edm::ParameterSet& configFile);
  /// default destructor
  ~FullHadSpecial(){};

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

};

#endif
