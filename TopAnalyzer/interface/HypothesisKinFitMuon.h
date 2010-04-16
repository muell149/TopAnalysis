#ifndef HypothesisKinFitMuon_h
#define HypothesisKinFitMuon_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

/**
   \class   HypothesisKinFitMuon HypothesisKinFitMuon.h "TopAnalysis/TopAnalyzer/interface/HypothesisKinFitMuon.h"

   \brief   Derived class to analyze the kinematic fit hypothesis of semileptonic ttbar events

   The structure keeps control histograms to analyze the relation between the fitted four vectors 
   of the kinematic fit hypothesis of semi-leptonic ttbar events and the original input vectors 
   of the selected pat::Muon. These histograms are to be filled from the TtSemiLeptonicEvent and 
   from edm::View<pat::Muon>'s. The class is derived from the DoubleObject<CollectionA, CollectionB> 
   interface, which makes it usable in fwfull or fwlite.  This class is expected to be run with 
   the same muon collection from which the kinematic fit hypothesis was derived, otherwise it will 
   lead to wrong results!
*/

class HypothesisKinFitMuon : public DoubleObject<TtSemiLeptonicEvent, const edm::View<pat::Muon> > {

 public:
  /// default constructor for fw lite
  explicit HypothesisKinFitMuon();
  /// default constructor for fw full
  explicit HypothesisKinFitMuon(const edm::ParameterSet& configFile);
  /// default destructor
  ~HypothesisKinFitMuon(){};

  /**
     The following functions have to be implemented for any class
     derived from DoubleObject<CollectionA, CollectionB>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling interface for reconstruction level for access with fw or fwlite
  void fill(const TtSemiLeptonicEvent& tops, const edm::View<pat::Muon>& muons, const double& weight=1.);
  /// histogram filling
  void fill(const TtSemiLeptonicEvent& tops, const double& weight=1.){ 
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
  /// nothing to be done here for the moment
};

#endif
