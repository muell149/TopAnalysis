#ifndef MuonCrossSection_h
#define MuonCrossSection_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include "TMath.h"

/**
   \class   MuonCrossSection MuonCrossSection.h "TopAnalysis/TopAnalyzer/interface/MuonCrossSection.h"

   \brief   Derived class to determine differential cross section for top production in semimuonic decay channel

   The structure keeps histograms for the kinematics of muons originating from semileptonic ttbar decays.
   The class is derived from the SingleObject<Collection> interface, which makes it usable in full framework or fwlite. 
*/

namespace CrossSection{
 // binning for cross section histograms
 double muonPt[]  = {   0. ,    20. ,    40.,    65. ,   150.                 };
 double muonEta[] = {  -2.1,   -0.75,    0.0,    0.75,   2.1                  };
 double muonPhi[] = {  -3.0,   -2.0 ,   -1.0,    0.0 ,   1.0 ,   2.0 ,   3.0  };
}

class MuonCrossSection : public SingleObject<const edm::View<pat::Muon> > {
  
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
  void fill(const edm::View<pat::Muon>& muons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};


 private:
  /// histogram container for correlation plots
  std::map<std::string, TH2*> corrs_;
};

#endif
