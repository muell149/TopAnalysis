#ifndef PtHat_h
#define PtHat_h

#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

/**
   \class   PtHat PtHat.h "TopAnalysis/TopAnalyzer/interface/PtHat.h"

   \brief   Derived class to analyze ptHat

   The structure keeps histograms for ptHat analysis. These histograms can be filled from
   the GenEventInfoProduct class. The class is derived from the SingleObject<Collection>
   interface, which makes it usable in full framework or fwlite. 
*/

class PtHat : public SingleObject< GenEventInfoProduct > {
  
 public:
  /// default constructor for fw lite
  explicit PtHat();
  /// default constructor for fwfull
  explicit PtHat(const edm::ParameterSet& configFile);
  /// default destructor
  ~PtHat(){};

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
  void fill(const GenEventInfoProduct& genEventInfoProduct, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};
};

#endif
