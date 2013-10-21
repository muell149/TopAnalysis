#ifndef visiblePhaseSpaceFilter_h
#define visiblePhaseSpaceFilter_h

#include <memory>
#include <string>
#include <iostream>
#include <utility>

#include "TH1F.h"
#include "TTree.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

/**
   \class   visiblePhaseSpaceFilter visiblePhaseSpaceFilter.h "TopAnalysis/TopUtils/interface/visiblePhaseSpaceFilter.h"

   \brief   Module to check if the event is with the visible gen hadron level phase space

   This is a module to indicate whether an event is within the visible gen hadron level phase space, 
   which is defined by the multiplicity of gen leptons, gen jets, gen b jets and gen light jets.
   A boolean "inVisiblePS" is written to the event and can be used in other modules, e.g. when filling
   2D gen-rec plots to put events outside the phase space into the gen underflow bin. 
   
   _genJets_        : input gen jet collection
   
   _genbJets_       : input gen b jet collection

   _genlightJets_   : input gen light jet collection

   _genLeptons_     : input gen lepton collection

   _useTree_        : save object multiplicities in tree?

   _nLeptonsMin_     : minimal multiplicity of input lepton collection
   _nLeptonsMax_     : maximal multiplicity of input lepton collection

   _nJetsMin_        : minimal multiplicity of input jet collection
   _nJetsMax_        : maximal multiplicity of input jet collection

   _nbJetsMin_       : minimal multiplicity of input b jet collection
   _nbJetsMax_       : maximal multiplicity of input b jet collection

   _nlightJetsMin_   : minimal multiplicity of input light jet collection
   _nlightJetsMax_   : maximal multiplicity of input light jet collection

*/

class visiblePhaseSpaceFilter : public edm::EDProducer {

 public:
  /// default constructor
  explicit visiblePhaseSpaceFilter(const edm::ParameterSet&);
  /// default destructor
  ~visiblePhaseSpaceFilter(){};
  
 private:
  /// produce function to select
  virtual void produce(edm::Event&, const edm::EventSetup&);

 private:
  /// input lepton collection
  edm::InputTag genLeptons_;
  /// lepton multiplicity
  int nLeptonsMin_;
  int nLeptonsMax_;
  /// input jet collection
  edm::InputTag genJets_;
  /// jet multiplicity
  int nJetsMin_;
  int nJetsMax_;
  /// input b jet collection
  edm::InputTag genbJets_;
  /// b jet multiplicity
  int nbJetsMin_;
  int nbJetsMax_;
  /// input light jet collection
  edm::InputTag genlightJets_;
  /// light jet multiplicity
  int nlightJetsMin_;
  int nlightJetsMax_;
  /// multiplicities for histogram filling
  int nLeptons, nJets, nbJets, nlightJets, naddJets30, naddJets50;
  /// phase space indicator
  bool inVisiblePS;
  /// histogram container
  /// multiplicity hists as output for control
  std::map<std::string, TH1F*> hists_;

}; 

#endif
