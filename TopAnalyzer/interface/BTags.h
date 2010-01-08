#ifndef BTags_h
#define BTags_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"

/**
   \class   BTags BTags.h "TopAnalysis/TopAnalyzer/interface/BTags.h"

   \brief   Derived class to analyze b-tags at generator level

   The structure keeps histograms for b-tag analysis. These histograms can be filled from
   the edm::View<pat::Jet> class. The class is derived from the SingleObject<Collection>
   interface, which makes it usable in full framework or fwlite. 
*/

class BTags : public SingleObject< edm::View< pat::Jet > > {
  
 public:
  /// default constructor for fw lite
  explicit BTags();
  /// default constructor for fwfull
  explicit BTags(const edm::ParameterSet& configFile);
  /// default destructor
  ~BTags(){};

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
    void fill(const edm::View<pat::Jet>& jets, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};
};

#endif
