#ifndef JetResolution_h
#define JetResolution_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TopAnalysis/TopAnalyzer/interface/ObjectResolution.h"

/**
   \class   JetResolution JetResolution.h "TopAnalysis/TopAnalyzer/interface/JetResolution.h"

   \brief   Derived class to analyze the resolution of jets on reconstruction level using generator level information

   The structure keeps histograms to derive the resolution of jets using generator level information. 
   These histograms are to be filled from std::vector<pat::Jet>'s only(!). The class is derived from 
   the ObjectResolution<Collection> interface, which makes it usable in fwfull or fwlite. It needs a 
   dedicated constructor for fwlite to obtain the information of histogram binnings in pt, eta and 
   phi of the jet.
*/

class JetResolution : public ObjectResolution<std::vector<pat::Jet> > {

 public:
  /// default constructor for fw lite
  explicit JetResolution(double matchDR, std::vector<double> binsPt, std::vector<double> binsEta, std::vector<double> binsPhi);
  /// default constructor for full fw
  explicit JetResolution(const edm::ParameterSet& configFile);
  /// default destructor
  ~JetResolution(){};
  /// histogramm booking for fwlite (override of the base class with different binning)
  void book();
  /// histogramm booking for fwfull (override of the base class with different binning)
  void book(edm::Service<TFileService>& fileService);
  
  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>
  **/
  /// histogram filling for fwlite and for fwfull
  void fill(const std::vector<pat::Jet>& jets, const double& weight=1.);

 private:
  /// there are no additional data memebers with respect to the base class
};

#endif
