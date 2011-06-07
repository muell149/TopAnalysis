#ifndef SecondElectronFilter_h  
#define SecondElectronFilter_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

/**
   \class   SecondElectronFilter SecondElectronFilter.h "TopAnalysis/TopFilter/plugins/SecondElectronFilter.h"

   \brief   Plugin to veto events with a second (looser) electron which gives a certain invariant mass like Z, J/Psi, ...

   The class vetos events where the invariant mass of a leading electron with a second looser electron is within a window
   given in the config-file or with an invariant mass lower than a certain value. Note that there is no selection of the
   electrons within the event filer. 
*/

class SecondElectronFilter : public edm::EDFilter {

 public:
  /// default constructor
  explicit SecondElectronFilter(const edm::ParameterSet& configFile);
  /// default destructor
  ~SecondElectronFilter();
  
 private:
  /// sanity check 
  virtual void beginJob();
  /// event veto
  virtual bool filter(edm::Event& event, const edm::EventSetup& setup);
  
 private:

  /// first  lepton collection label
  edm::InputTag elecsTight_    ;
  /// second lepton collection label
  edm::InputTag elecsLoose_    ;

  /// veto on Z-mass window, default values are 76GeV, 106GeV
  std::vector<double> massWindow_;

};  

#endif  
