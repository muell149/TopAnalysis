#ifndef JetQuality_h
#define JetQuality_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"

/**
   \class   JetQuality JetQuality.h "TopAnalysis/TopAnalyzer/interface/JetQuality.h"

   \brief   Derived class to analyze the quality/id of jets on reconstruction level

   The structure keeps histograms for the identification and (high quality) of reconstruc-
   ted jets. These histograms can be filled from edm::View<pat::Jet> only(!). The class 
   is derived from the SingleObject<Collection> interface, which makes it usable in fwfull
   or fwlite. 
*/

class JetQuality : public SingleObject<const edm::View<pat::Jet> > {

 public:
  /// default constructor for fwlite
  explicit JetQuality(const int index, std::string flavor);
  /// default constructor for fwfull
  explicit JetQuality(const edm::ParameterSet& configFile);
  /// default destructor
  ~JetQuality(){};

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
    void process(){};

 private:
  /// index of jet to be plotted
  int index_;
  /// decide which flaor to be used for the L5 and L7 flavor dependend 
  /// JEC monitoring plots
  std::string flavor_;
};

#endif
