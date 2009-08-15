#ifndef SemiLeptonicTopJetSelector_h
#define SemiLeptonicTopJetSelector_h

#include <memory>
#include <string>
#include <iostream>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

/*
   \class   SemiLeptonicTopJetSelector SemiLeptonicTopJetSelector.h "TopAnalysis/TopFilter/plugins/SemiLeptonicTopJetSelector.h"

   \brief   Plugin to select the jets, which are part of the top hypothesis and the best matching to the decay on generator level  

   The class selects those jets which are part of the top hypothesis and those jets with the best match 
   to the quarks of the semileptonic ttbar system on generator level. It has the TtSemiLeptonicEvent as
   input and produces two std::vector<pat::Jet>'s, which can be further processed with standard analyzers. 
   The std::vector<pat::Jet> with the best matches to the quarks of the semileptonic decay ttbar system on 
   generator level is provided with the additional instance label 'gen'. For the 'kGenMatch' hypothesis 
   both jet collections should be the same.

   The class allows to restrict the output to the bjets of the ttbar system and to switch whether the jets 
   which are part of the hypothesis should be selected or the opposite.
**/

class SemiLeptonicTopJetSelector : public edm::EDProducer {
  
 public:
  /// default constructor
  explicit SemiLeptonicTopJetSelector(const edm::ParameterSet& configFile);
  /// default destructor
  ~SemiLeptonicTopJetSelector();
  
 private:
  /// produce function
  virtual void produce(edm::Event& event, const edm::EventSetup& setup);
  /// helper function to decide whether the element should be pushed or not
  bool pushElement(const int& idx, const std::vector<int>& match);

 private:
  /// jet collection label
  edm::InputTag src_;
  /// generator match label
  edm::InputTag genMatch_;
  /// top event label
  edm::InputTag topEvent_;
  /// hypothesis key
  std::string hypoKey_;
  // jet type (b, uds or all)
  std::string jetType_;
  // select top jets or the opposite
  bool partOfHyp_;
};

#endif
