#ifndef KinFitImprover_h
#define KinFitImprover_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadronicEvent.h"

/**
   \class   KinFitImprover KinFitImprover.h "TopAnalysis/TopAnalyzer/interface/KinFitImprover.h"

   \brief   Derived class to analyze and improve the kinematic fit hypothesis of fullhadronic ttbar events

   The structure keeps control histograms to analyze the relation between the fitted four vectors 
   of the kinematic fit hypothesis of fullhadronic ttbar events and the original input vectors 
   of the selected pat::Jets. These histograms are to be filled from the TtFullHadronicEvent and 
   from edm::View<pat::Jet>'s. The class is derived from the DoubleObject<CollectionA, CollectionB> 
   interface, which makes it usable in fwfull or fwlite.  This class is expected to be run with 
   the same jet collection from which the kinematic fit hypothesis was derived, otherwise it will 
   lead to wrong results!
*/

class KinFitImprover : public DoubleObject<TtFullHadronicEvent, const edm::View<pat::Jet> > {

 public:
  /// default constructor for fw lite
  explicit KinFitImprover();
  /// default constructor for fw full
  explicit KinFitImprover(const edm::ParameterSet& configFile);
  /// default destructor
  ~KinFitImprover(){};

  /**
     The following functions have to be implemented for any class
     derived from DoubleObject<CollectionA, CollectionB>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling interface for reconstruction level for access with fw or fwlite
  void fill(const TtFullHadronicEvent& tops, const edm::View<pat::Jet>& jets, const double& weight=1.);
  /// histogram filling
  void fill(const TtFullHadronicEvent& tops, const double& weight=1.){ 
    std::string exception;
    exception += "-----------------------------------------------------------------------------\n";
    exception += "NOTE: You omitted the parameter _srcB_ in your configuration file, which is  \n";
    exception += "      not optional in this case. The program will terminate here. Check what \n";
    exception += "      parameters are expected in the definition of your module.              \n";
    exception += "-----------------------------------------------------------------------------\n";
    throw edm::Exception(edm::errors::Configuration, exception);
  } 
  /// everything which needs to be done after the event loop
  void process(){};

 private:
  /// function to find types of jet-combinations in KinFits
  int comboType();
  /// variable from cfi.py / cfg.py to decide which combination to analyze
  int comboType_;
  /// vector to store the jet indices
  std::vector<int> jetIndex;
  /// store position in jetIndex vector with corresponding particle name
  /// keep enum whichParticle and vector jetIndex (filled in KinFitImprover::fill()) synced !!!
  enum whichParticle{LQ, LQBar, B, BBar, LP, LPBar, LQ_Gen, LQBar_Gen, B_Gen, BBar_Gen, LP_Gen, LPBar_Gen};
};

#endif
