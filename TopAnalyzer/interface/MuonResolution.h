#ifndef MuonResolution_h
#define MuonResolution_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"

/**
   \class   MuonResolution MuonResolution.h "TopAnalysis/TopAnalyzer/interface/MuonResolution.h"

   \brief   Derived class to analyze the resolution of muons on reconstruction level using generator level information

   The structure keeps histograms to derive the resolution of muons using generator level information. 
   These histograms are to be filled from std::vector<pat::Muon>'s only(!). The class is derived from 
   the SingleObject<Collection> interface, which makes it usable in fwfull or fwlite. It needs a dedi-
   cated contructor for fwlite to obtain the information of histogram binnings in pt, eta and phi of 
   the muon.
*/

class MuonResolution : public SingleObject<const std::vector<pat::Muon> > {

 public:
  /// default constructor for fw lite
  explicit MuonResolution(double matchDR, std::vector<double> binsPt, std::vector<double> binsEta, std::vector<double> binsPhi);
  /// default constructor for full fw
  explicit MuonResolution(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonResolution(){};
  
  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fwfull
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for fwfull
  void fill(const std::vector<pat::Muon>& muons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};

  /**
     The following function is an override of the base class function
     to fit to the requirements of the resolution histogram management
  **/
  /// writing histograms to file in fwlite
  void write(TFile& file, const char* directory);

 private:
  /**
     Helper function for special histogram management
  **/
  /// book a vector of histograms according to a given binning
  void book(std::vector<TH1F*>& hists, const char* kin, std::vector<double> binning, unsigned int nBins, double boundary);
  /// book a vector of histograms according to a given binning
  void book(edm::Service<TFileService>& fs, std::vector<TH1F*>& hists, const char* kin, std::vector<double> binning, unsigned int nBins, double boundary);

 private:
  /// maximally acceptable distance in deltaR (for matching)
  double matchDR_;
  /// binning of resolution histograms
  std::vector<double> binsPt_;
  std::vector<double> binsEta_;
  std::vector<double> binsPhi_;

  /// resolution histograms
  std::vector<TH1F*> pt_;
  std::vector<TH1F*> eta_;
  std::vector<TH1F*> phi_;
};

#endif
