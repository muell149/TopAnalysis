#ifndef TopKinematicsGen_h
#define TopKinematicsGen_h

#include "TopAnalysis/TopAnalyzer/interface/TopKinematics.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"


//
// top kinematics analyzer equally usable for full 
// framework or framework lite
//

class TopKinematicsGen : public TopKinematics<const TtGenEvent> {

 public:
  /// default constructor for fw lite
  explicit TopKinematicsGen();
  /// default constructor for full fw
  explicit TopKinematicsGen(const edm::ParameterSet& configFile);
  /// default destructor
  ~TopKinematicsGen(){};

  /// histogram filling interface for gen level for access with fwlite or full framework
  void fill(const TtGenEvent& tops, const double& weight=1.);
};

#endif
