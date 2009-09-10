#ifndef JetCombinatorics_h
#define JetCombinatorics_h

//#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

/**
   \class   JetCombinatorics JetCombinatorics.h "TopAnalysis/TopAnalyzer/interface/JetCombinatorics.h"
*/

class JetCombinatorics : public SingleObject<TtSemiLeptonicEvent> {

 public:
  /// default constructor
  explicit JetCombinatorics(const edm::ParameterSet& configFile);
  /// default destructor
  ~JetCombinatorics(){};

  /// histogramm booking for fwlite (not yet implemented!)
  void book(){};
  /// histogramm booking
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling
  void fill(const TtSemiLeptonicEvent& semiLepEvt, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process();

 private:

  /// compare a subset of jet combinations in two hypotheses
  bool sameJets(const TtSemiLeptonicEvent& semiLepEvt,
		const std::string& hyp1,
		const std::string& hyp2,
		const std::vector<int>& jetsToCompare);

 private:
  /// class key of hypothesis
  std::string hypoKey_;
  /// total number of events passed to this analyzer
  int nEventsTotal_;
  /// number of events used in this study
  int nEventsStudy_;
  /// number of events in which the chosen hypothesis had the same jets as the GenMatch hypothesis
  std::vector<int> nEventsGood_;
};

#endif
