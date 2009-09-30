#ifndef JetEnergyCorrections_h
#define JetEnergyCorrections_h

#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

/**
   \class   JetEnergyCorrections JetEnergyCorrections.h "TopAnalysis/TopAnalyzer/interface/JetEnergyCorrections.h"
*/

class JetEnergyCorrections : public SingleObject<TtSemiLeptonicEvent> {

 public:
  /// default constructor
  explicit JetEnergyCorrections(const edm::ParameterSet& configFile);
  /// default destructor
  ~JetEnergyCorrections(){};

  /// histogramm booking for fwlite (not yet implemented!)
  void book(){};
  /// histogramm booking
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling
  void fill(const TtSemiLeptonicEvent& semiLepEvt, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process() {};

 private:
  /// class key of hypothesis
  std::string hypoKey_;
};

#endif
