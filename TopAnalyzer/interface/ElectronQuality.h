#ifndef ElectronQuality_h
#define ElectronQuality_h

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"

/**
   \class   ElectronQuality ElectronQuality.h "TopAnalysis/TopAnalyzer/interface/ElectronQuality.h"

   \brief   Derived class to analyze the quality/id of electrons on reconstruction level

   The structure keeps histograms for the identification and (high quality) of reconstruc- 
   ted electrons. These histograms can be filled from edm::View<pat::Electron> only(!). The class 
   is derived from the SingleObject<Collection> interface, which makes it usable in fwfull
   or fwlite. 
*/

class ElectronQuality : public SingleObject<const edm::View<pat::Electron> > {

 public:
  /// default constructor for fwlite
  explicit ElectronQuality(const int index);
  /// default constructor for fwfull
  explicit ElectronQuality(const edm::ParameterSet& configFile);
  /// default destructor
  ~ElectronQuality(){};

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fwfull
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for fwfull from reco objects
  void fill(const edm::View<pat::Electron>& electrons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process();

 private:
  /**
     Helper functions to fill energy/object flow histograms
  **/
  /// get energy of objects within a ring in deltaR corresponding to the 
  /// bin width of the histogram 'hist' from 'deposit' & fill hist with it
  void energyFlow(TH1* hist, const pat::IsoDeposit* deposit);
  /// get energy of objects within a ring in deltaR corresponding to the 
  /// bin width of the histogram 'hist' from 'deposit' & fill hist with it
  void energyFlow(TH1* hist, const pat::IsoDeposit* ecalDeposit, const pat::IsoDeposit* hcalDeposit);
  /// get number of objects within a ring in deltaR corresponding to the 
  /// bin width of the histogram 'hist' from 'deposit' and fill hist with it
  void objectFlow(TH1* hist, const pat::IsoDeposit* deposit);

 private:
  /// number of (weighted) histogram entries for normalization
  double norm_;
  /// index of jet to be plotted
  int index_;
};

#endif
