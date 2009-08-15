#ifndef DiMuonMassFilter_h  
#define DiMuonMassFilter_h

#include <memory>
#include <string>
#include <iostream>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

/*
   \class   DiMuonMassFilter DiMuonMassFilter.h "TopAnalysis/TopFilter/plugins/DiMuonMassFilter.h"

   \brief   Plugin to veto events with two muons, which pass a Z to mu mu hypothesis

   The class vetos events where the invariant mass of the two leading muons lies between 84 GeV 
   and 98 GeV. The Z mass window is hard coded. Note that there is no selection of the muons 
   within the event filer. 
**/

class DiMuonMassFilter : public edm::EDFilter {

 public:
  /// default constructor
  explicit DiMuonMassFilter(const edm::ParameterSet& configFile);
  /// default destructor
  ~DiMuonMassFilter();
  
 private:
  /// event veto
  virtual bool filter(edm::Event& event, const edm::EventSetup& setup);
  
 private:
  /// muon collection label
  edm::InputTag muons_;
};  

#endif  
