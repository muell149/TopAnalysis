#ifndef DiMuonFilter_h  
#define DiMuonFilter_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

/**
   \class   DiMuonFilter DiMuonFilter.h "TopAnalysis/TopFilter/plugins/DiMuonFilter.h"

   \brief   Plugin to veto events with two muons which give a certain invariant mass like Z, J/Psi, ...

   The class vetos events where the invariant mass of the two leading muons lies between two values given in the
   config-file or with an invariant mass lower than a certain value. Note that there is no selection of the muons 
   within the event filer. 
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
  /// true if cut window is vetoed, false if window is to be selected
  bool isVeto_;
  /// cut on Z-mass, default values are 76GeV, 106GeV
  std::vector<double> Cut_;
  /// filter on unlike sign
  int fltrChrg_;  
};  

#endif  
