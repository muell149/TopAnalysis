#ifndef TopResolution_h
#define TopResolution_h

#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/ObjectResolution.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

/**
   \class   TopResolution TopResolution.h "TopAnalysis/TopAnalyzer/interface/TopResolution.h"

   \brief   Derived class to analyze the resolution of top quarks on reconstruction level using generator level information

   The structure keeps histograms to derive the resolution of top quarks using generator level information. 
   These histograms are to be filled from the TtSemiLeptonicEvent class. The class is derived from the
   ObjectResolution<Collection> interface, which makes it usable in fwfull or fwlite. It needs a dedicated 
   contructor for fwlite to obtain the information of histogram binnings in pt, eta and phi of the top 
   quark and the desired hypothesis key.
*/

class TopResolution : public ObjectResolution<TtSemiLeptonicEvent> {

 public:
  /// default constructor for fw lite
   explicit TopResolution(double matchDR, std::vector<double> binsPt, std::vector<double> binsEta, std::vector<double> binsPhi, const char* hypoKey);
  /// default constructor for full fw
  explicit TopResolution(const edm::ParameterSet& configFile);
  /// default destructor
  ~TopResolution(){};
  /// histogramm booking for fwlite (override of the base class with different binning)
  void book();
  /// histogramm booking for fwfull (override of the base class with different binning)
  void book(edm::Service<TFileService>& fileService);
  
  /**
     The following function has to be implemented for any class
     derived from ObjectResolution<Collection>
  **/
  /// histogram filling for fwlite and for fwfull
  void fill(const TtSemiLeptonicEvent& tops, const double& weight=1.);

 private:
  /// class key of hypothesis
  std::string hypoKey_;
};

#endif 
