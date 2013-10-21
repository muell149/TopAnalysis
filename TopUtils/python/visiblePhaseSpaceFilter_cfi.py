import FWCore.ParameterSet.Config as cms

visiblePhaseSpace = cms.EDProducer("visiblePhaseSpaceFilter",
  ## input gen lepton collection     (should be of type reco::GenParticle)
  genLeptons   = cms.InputTag("genParticles"),
  ## required lepton multiplicity
  nLeptonsMin   = cms.int32(1),
  nLeptonsMax   = cms.int32(1),
  ## input gen jet collection        (should be of type reco::GenJet)
  genJets      = cms.InputTag("reco::GenJet"),  
  ## required jet multiplicity
  nJetsMin      = cms.int32(4),
  nJetsMax      = cms.int32(99999),            
  ## input gen b jet collection      (should be of type reco::GenJet)
  genbJets     = cms.InputTag("reco::GenJet"),
  ## required b jet multiplicity
  nbJetsMin     = cms.int32(2),
  nbJetsMax     = cms.int32(2),
  ## input gen light jet collection  (should be of type reco::GenJet)
  genlightJets = cms.InputTag("reco::GenJet"),
  ## required light jet multiplicity
  nlightJetsMin = cms.int32(2),
  nlightJetsMax = cms.int32(2)
)
