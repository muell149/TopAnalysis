#ifndef MuonKinematics_h
#define MuonKinematics_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleAnalyzer.h"

//
// muon kinematics analyzer equally usable for full 
// framework or framework lite
//

class MuonKinematics : public SingleAnalyzer<const std::vector<pat::Muon> > {

 public:
  /// default constructor for fw lite
  explicit MuonKinematics();
  /// default constructor for full fw
  explicit MuonKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonKinematics(){};

  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for full fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for full fw
  void fill(const std::vector<pat::Muon>& muons, const double& weight=1.);
  /// get energy of objects within a ring in deltaR corresponding top the 
  /// bin width of the histogram hist from iso deposits and fill hist with it
  void fillEnergyFlowHistogram(TH1F* hist, const pat::IsoDeposit* deposit);
  /// get number of objects within a ring in deltaR corresponding top the 
  /// bin width of the histogram hist from iso deposits and fill hist with it
  void fillObjectFlowHistogram(TH1F* hist, const pat::IsoDeposit* deposit);
  /// everything which needs to be done after the event loop
  void process();

 private:
  /// number of histogram fills for normalization (weighted)
  double norm_;
};

#endif
