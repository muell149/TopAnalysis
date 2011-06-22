#ifndef DiLeptonFilter_h
#define DiLeptonFilter_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

/**
   \class   DiLeptonFilter DiLeptonFilter.h "TopAnalysis/TopFilter/plugins/DiLeptonFilter.h"

   \brief   Plugin to filter di-lepton candidate events for mass range, charge, and type

   The class vetos events where the invariant mass of the two paired leptons lies between two values given in the
   config-file or with an invariant mass lower than a certain value. Note that there is no selection of the leptons
   within the event filer.
*/

class DiLeptonFilter : public edm::EDFilter {

public:
  /// default constructor
  explicit DiLeptonFilter(const edm::ParameterSet& configFile);
  /// default destructor
  ~DiLeptonFilter();

private:
  /// sanity check
  virtual void beginJob();
  /// event veto
  virtual bool filter(edm::Event& event, const edm::EventSetup& setup);

private:


  /// electron collection label
  const edm::InputTag electrons_;
  const edm::InputTag muons_;

  /// true if cut window is vetoed, false if window is to be selected
  const bool isVeto_;

  /// cut on Z-mass, default values are 76GeV, 106GeV
  const std::vector<double> Cut_;

  /// filter on sign
  const int fltrChrg_;
};

#endif
