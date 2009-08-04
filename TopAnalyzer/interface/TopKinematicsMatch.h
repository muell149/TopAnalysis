#ifndef TopKinematicsMatch_h
#define TopKinematicsMatch_h

#include "TopAnalysis/TopAnalyzer/interface/TopKinematicsRec.h"


//
// top kinematics analyzer equally usable for full 
// framework or framework lite
//

class TopKinematicsMatch : public TopKinematicsRec {

 public:
  /// default constructor for fw lite
  explicit TopKinematicsMatch(const int& hypoKey);
  /// default constructor for full fw
  explicit TopKinematicsMatch(const edm::ParameterSet& configFile);
  /// default destructor
  ~TopKinematicsMatch(){};

  /// histogram filling interface for rec level for access
  /// with fwlite or full framework (override from rec class)
  void fill(const TtSemiLeptonicEvent& tops, const double& weight=1.);
};

#endif
