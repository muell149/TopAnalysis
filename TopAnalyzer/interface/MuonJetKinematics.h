#ifndef MuonJetKinematics_h
#define MuonJetKinematics_h

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/DoubleAnalyzer.h"

//
// muon kinematics analyzer equally usable for full 
// framework or framework lite
//

class MuonJetKinematics : public DoubleAnalyzer<const std::vector<pat::Muon>, const std::vector<pat::Jet> > {

 public:
  /// default constructor for fw lite
  explicit MuonJetKinematics();
  /// default constructor for full fw
  explicit MuonJetKinematics(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonJetKinematics(){};

  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for full fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling for fwlite and for full fw
  void fill(const std::vector<pat::Muon>& muons, const std::vector<pat::Jet>& jets, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process();

 private:
  /// number of histogram fills for normalization (weighted)
  double norm_;
};

#endif
