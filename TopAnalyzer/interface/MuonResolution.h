#ifndef MuonResolution_h
#define MuonResolution_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/ObjectResolution.h"

/**
   \class   MuonResolution MuonResolution.h "TopAnalysis/TopAnalyzer/interface/MuonResolution.h"

   \brief   Derived class to analyze the resolution of muons on reconstruction level using generator level information

   The structure keeps histograms to derive the resolution of muons using generator level information. 
   These histograms are to be filled from std::vector<pat::Muon>'s only(!). The class is derived from 
   the ObjectResolution<Collection> interface, which makes it usable in fwfull or fwlite. It needs a 
   dedicated contructor for fwlite to obtain the information of histogram binnings in pt, eta and phi 
   of the muon.
*/

class MuonResolution : public ObjectResolution<std::vector<pat::Muon> > {

 public:
  /// default constructor for fw lite
  explicit MuonResolution(double matchDR, std::vector<double> binsPt, std::vector<double> binsEta, std::vector<double> binsPhi);
  /// default constructor for full fw
  explicit MuonResolution(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonResolution(){};
  /// histogramm booking for fwlite (override of the base class with different binning)
  void book();
  /// histogramm booking for fwfull (override of the base class with different binning)
  void book(edm::Service<TFileService>& fileService);
  
  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>
  **/
  /// histogram filling for fwlite and for fwfull
  void fill(const std::vector<pat::Muon>& muons, const double& weight=1.);

 private:
  /// there are no additional data memebers with respect to the base class
};

#endif
