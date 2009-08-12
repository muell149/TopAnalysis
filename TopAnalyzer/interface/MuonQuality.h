#ifndef MuonQuality_h
#define MuonQuality_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"

/**
   \class   MuonQuality MuonQuality.h "TopAnalysis/TopAnalyzer/interface/MuonQuality.h"

   \brief   Derived class to analyze the quality/id of muons on reconstruction level

   The structure keeps histograms for the identification and high quality reconstruction 
   of muons. These histograms can be filled from std::vector<pat::Muon> only. The class 
   is derived from the SingleObject interface, which makes it usable in full framework
   (fw) or fwlite. 
*/

class MuonQuality : public SingleObject<const std::vector<pat::Muon> > {

 public:
  /// default constructor for fw lite
  explicit MuonQuality();
  /// default constructor for full fw
  explicit MuonQuality(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonQuality(){};

  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for full fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for full fw from reco objects
  void fill(const std::vector<pat::Muon>& muons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process();

 private:
  /// get energy of objects within a ring in deltaR corresponding to the 
  /// bin width of the histogram 'hist' from 'deposit' & fill hist with it
  void energyFlow(TH1* hist, const pat::IsoDeposit* deposit);
  /// get number of objects within a ring in deltaR corresponding to the 
  /// bin width of the histogram 'hist' from 'deposit' and fill hist with it
  void objectFlow(TH1* hist, const pat::IsoDeposit* deposit);

 private:
  /// number of (weighted) histogram entries for normalization
  double norm_;
};

#endif
