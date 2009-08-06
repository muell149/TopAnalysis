#ifndef TopKinematicsRec_h
#define TopKinematicsRec_h

#include "TopAnalysis/TopAnalyzer/interface/TopKinematics.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"


//
// top kinematics analyzer equally usable for full 
// framework or framework lite
//

class TopKinematicsRec : public TopKinematics<TtSemiLeptonicEvent> {

 public:
  /// default constructor for fw lite
  explicit TopKinematicsRec(const int& hypoKey);
  /// default constructor for full fw
  explicit TopKinematicsRec(const edm::ParameterSet& configFile);
  /// default destructor
  ~TopKinematicsRec(){};

  /// histogram filling interface for rec level for access with fwlite or full framework
  void fill(const TtSemiLeptonicEvent& tops, const double& weight=1.);

 protected:
  /// class key of hypothesis
   std::string hypoKey_;
};

#endif
