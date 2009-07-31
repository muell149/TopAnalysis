#ifndef MuonQuality_h
#define MuonQuality_h

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleAnalyzer.h"

//
// muon id analyzer equally usable for full 
// framework or framework lite
//

class MuonQuality : public SingleAnalyzer<const std::vector<pat::Muon> > {

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
  void book(edm::Service<TFileService>&);
  /// histogram filling for fwlite and for full fw
  void fill(const std::vector<pat::Muon>& muons, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process() {};
};

#endif
