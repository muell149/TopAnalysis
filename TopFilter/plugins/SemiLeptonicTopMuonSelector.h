#ifndef SemiLeptonicTopMuonSelector_h
#define SemiLeptonicTopMuonSelector_h

#include <memory>
#include <string>
#include <iostream>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

/*
   \class   SemiLeptonicTopMuonSelector SemiLeptonicTopMuonSelector.h "TopAnalysis/TopFilter/plugins/SemiLeptonicTopMuonSelector.h"

   \brief   Plugin to select the muon, which is part of the semileptonic top hypothesis and the best matching to the decay on generator level  

   The class selects the muon that is part of the top hypothesis and for the muon with the best match to 
   the muon of the leptonically decaying top quark on generator level. It has the TtSemiLeptonicEvent as 
   input and produces two std::vector<pat::Muon>'s, which can be further processed with standard analyzers. 
   The std::vector<pat::Muon> with the best match to the muon from the leptonic decay on generator level in 
   deltaR is provided with the additional instance label 'gen'. For the 'kGenMatch' hypothesis both muons 
   should be the same.
**/

class SemiLeptonicTopMuonSelector : public edm::EDProducer {

 public:
  /// default constructor
  explicit SemiLeptonicTopMuonSelector(const edm::ParameterSet& configFile);
  /// default destructor
  ~SemiLeptonicTopMuonSelector();
  
 private:
  /// produce selected muon collections
  virtual void produce(edm::Event& event, const edm::EventSetup& setup);

 private:
  /// muon collection label
  edm::InputTag src_;
  /// top event label
  edm::InputTag topEvent_;
  /// hypothesis key
  std::string hypoKey_;
};

#endif
