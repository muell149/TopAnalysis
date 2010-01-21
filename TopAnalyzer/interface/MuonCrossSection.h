#ifndef MuonCrossSection_h
#define MuonCrossSection_h

#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "TMath.h"

/**
   \class   MuonCrossSection MuonCrossSection.h "TopAnalysis/TopAnalyzer/interface/MuonCrossSection.h"

   \brief   Derived class to analyze the kinematics of top quarks on reconstruction and generator level

   The structure keeps histograms for the kinematics of top quarks and ttbar pairs. These histograms 
   can be filled from the TtSemiLeptonicEvent class (with an extra option to require matching for 
   purity & stability studies) or from the TtGenEvent class. The class is derived from the 
   SingleObject<Collection> interface, which makes it usable in full framework or fwlite. 
*/

namespace CrossSection{
 // binning for top & ttbar cross section histograms
 double muonPt[] = {   0. ,    30. ,    50. ,    75. ,   150. };
}

class MuonCrossSection : public SingleObject<const edm::View<reco::Candidate> > {
  
 public:
  /// default constructor for generator level analysis in fw lite
  explicit MuonCrossSection();
  /// default constructor for fwfull
  explicit MuonCrossSection(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonCrossSection(){};

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>. The fill function is
     overloaded to serve both for the TtGenEvent class directoy or 
     the TtSemiLeptonicEvent class.
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling interface for reconstruction level for access with fw or fwlite
  void fill(const edm::View<reco::Candidate>& muons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};
};

#endif
