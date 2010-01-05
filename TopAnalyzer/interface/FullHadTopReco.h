#ifndef FullHadTopReco_h
#define FullHadTopReco_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadronicEvent.h"

/**
   \class   FullHadTopReco FullHadTopReco.h "TopAnalysis/TopAnalyzer/interface/FullHadTopReco.h"

   \brief   Derived class to analyze the reconstruction of fullhadronic ttbar events

   The structure keeps control histograms to analyze the reconstruction of fullhadronic ttbar
   events. These histograms are to be filled from the TtFullHadronicEvent and from
   edm::View<pat::Jet>'s. The class is derived from the DoubleObject<CollectionA, CollectionB> 
   interface, which makes it usable in fwfull or fwlite.  This class is expected to be run with 
   the same jet collection from which the hypothesis was derived, otherwise it will 
   lead to wrong results!
*/

class FullHadTopReco : public DoubleObject<TtFullHadronicEvent, const edm::View<pat::Jet> > {

 public:
  /// default constructor for fw lite
  explicit FullHadTopReco();
  /// default constructor for fw full
  explicit FullHadTopReco(const edm::ParameterSet& configFile);
  /// default destructor
  ~FullHadTopReco(){};

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
  /// everything which needs to be done after the event loop
  void process(){};

 private:
  /// hypothesis chosen for reco
  std::string hypo_;
};

#endif
