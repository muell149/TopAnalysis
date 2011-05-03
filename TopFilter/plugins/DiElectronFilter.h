#ifndef DiElectronFilter_h  
#define DiElectronFilter_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

/**
   \class   DiElectronFilter DiElectronFilter.h "TopAnalysis/TopFilter/plugins/DiElectronFilter.h"

   \brief   Plugin to veto events with two electrons which give a certain invariant mass like Z, J/Psi, ...

   The class vetos events where the invariant mass of the two leading electrons lies between two values given in the
   config-file or with an invariant mass lower than a certain value. Note that there is no selection of the electrons 
   within the event filer. 
*/

class DiElectronFilter : public edm::EDFilter {

 public:
  /// default constructor
  explicit DiElectronFilter(const edm::ParameterSet& configFile);
  /// default destructor
  ~DiElectronFilter();
  
 private:
  /// sanity check 
  virtual void beginJob();
  /// event veto
  virtual bool filter(edm::Event& event, const edm::EventSetup& setup);
  
 private:
  /// electron collection label
  edm::InputTag electrons_;
  /// true if cut window is vetoed, false if window is to be selected
  bool isVeto_;
  /// cut on Z-mass, default values are 76GeV, 106GeV
  std::vector<double> Cut_;
  /// filter on unlike sign
  int fltrChrg_;  
};  

#endif 
