#ifndef MuonResolution_h
#define MuonResolution_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleAnalyzer.h"

//
// muon resolution analyzer equally usable for full 
// framework or framework lite
//

class MuonResolution : public SingleAnalyzer<const std::vector<pat::Muon> > {

 public:
  /// default constructor for fw lite
  explicit MuonResolution(double matchDR, std::vector<double> binsPt, std::vector<double> binsEta, std::vector<double> binsPhi);
  /// default constructor for full fw
  explicit MuonResolution(const edm::ParameterSet& confgiFile);
  /// default destructor
  ~MuonResolution(){};
  
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for full fw
  void book(edm::Service<TFileService>& fileService);
  /// book a vector of histograms according to a given binning
  void bookHistogram(std::vector<TH1F*>& hists, const char* kin, std::vector<double> binning, unsigned int nBins, double boundary);
  /// book a vector of histograms according to a given binning
  void bookHistogram(edm::Service<TFileService>& fs, std::vector<TH1F*>& hists, const char* kin, std::vector<double> binning, unsigned int nBins, double boundary);
  /// histogram filling for fwlite and for full fw
  void fill(const std::vector<pat::Muon>& muons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};
  /// writing histograms to file in fwlite (override from base class)
  void write(TFile& file, const char* directory);

 private:
  /// maximally acceptable distasnce in dR for matching
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
