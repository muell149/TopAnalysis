#ifndef MuonJetOverlapSelector_h
#define MuonJetOverlapSelector_h

#include <memory>
#include <string>
#include <iostream>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

/*
   \class   MuonJetOverlapSelector MuonJetOverlapSelector.h "TopAnalysis/TopFilter/plugins/MuonJetOverlapSelector.h"

   \brief   Plugin to select the muons with or without overlap to the nearest jet

   The class selects muons with or without overlap with the nearest jet within a cone of 
   given radius deltaR. It has a muon collection and a jet collection as input. Note 
   that there is no selection for the choice of jets or muons within the analyzer. The
   parameter deltaR can be specified. The output is a std::vector<pat::Muon> which on the 
   choice of the user contains muons with overlap to the nearest jet or not.
**/

class MuonJetOverlapSelector : public edm::EDProducer {

 public:
  /// default constructor
  explicit MuonJetOverlapSelector(const edm::ParameterSet& configFile);
  /// default destructor
  ~MuonJetOverlapSelector();
  
 private:
  /// produce selected muon collections
  virtual void produce(edm::Event& event, const edm::EventSetup& setup);
  /// helper function to decide whether the element should be pushed or not
  bool pushElement(const double& deltaR){ return deltaR<deltaR_ ?  overlap_ : !overlap_; };

 private:
  /// muon/jet collection label
  edm::InputTag muons_;
  edm::InputTag jets_;
  /// overlap cone
  double deltaR_;
  /// selecto for overlap or non-overlap
  bool overlap_;
};

#endif
