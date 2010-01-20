#ifndef GenParticle_h
#define GenParticle_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"

/**
   \class   GenParticle GenParticle.h "TopAnalysis/TopAnalyzer/interface/GenParticle.h"

   \brief   Derived class to analyze genParticles

   The structure keeps histograms for genParticle analysis. These histograms can be filled from
   the edm::View<reco::GenParticle> class. The class is derived from the SingleObject<Collection>
   interface, which makes it usable in full framework or fwlite. 
*/

class GenParticle : public SingleObject< edm::View< reco::GenParticle > > {
  
 public:
  /// default constructor for fw lite
  explicit GenParticle();
  /// default constructor for fwfull
  explicit GenParticle(const edm::ParameterSet& configFile);
  /// default destructor
  ~GenParticle(){};

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
  void fill(const edm::View<reco::GenParticle>& parts, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};
};

#endif
