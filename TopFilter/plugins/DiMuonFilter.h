#ifndef DiMuonFilter_h  
#define DiMuonFilter_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

/**
   \class   DiMuonFilter DiMuonFilter.h "TopAnalysis/TopFilter/plugins/DiMuonFilter.h"

   \brief   Plugin to veto/select events with two muons that give a certain invariant mass like Z, J/Psi, ... or/and
            that have same charge/opposite charge. 
*/

class DiMuonFilter : public edm::EDFilter {

 public:
  /// default constructor
  explicit DiMuonFilter(const edm::ParameterSet& configFile);
  /// default destructor
  ~DiMuonFilter();
  
 private:
  /// sanity check 
  virtual void beginJob();
  /// event veto
  virtual bool filter(edm::Event& event, const edm::EventSetup& setup);
  
 private:
  /// muon collection label
  edm::InputTag muons_;
  /// filter on unlike or like sign
  int fltrChrg_;
  /// filter on mass window
  bool fltrMass_;
  /// cut on Z-mass, default values are 76GeV, 106GeV
  std::vector<double> Cut_;
  /// inverts selection
  bool isVeto_;

};  

#endif  
