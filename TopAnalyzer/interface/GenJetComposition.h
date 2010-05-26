#ifndef GenJetComposition_h
#define GenJetComposition_h

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"

/**
   \class   GenJetComposition GenJetComposition.h "TopAnalysis/TopAnalyzer/interface/GenJetComposition.h"

   \brief   Derived class to analyze GenJetCollections

   The structure keeps histograms that shows the content of the 
   edm::View<reco::GenJet> class type Collections. The class 
   is derived from the SingleObject<Collection> interface, which 
   makes it usable in full framework or fwlite. 
*/

class GenJetComposition : public SingleObject< edm::View< reco::GenJet > > {
  
 public:
  /// default constructor for fw lite
  explicit GenJetComposition();
  /// default constructor for fwfull
  explicit GenJetComposition(const edm::ParameterSet& configFile);
  /// default destructor
  ~GenJetComposition(){};

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
  void fill(const edm::View<reco::GenJet>& jets, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};

  /// genJet index
  int index_;
};

#endif
