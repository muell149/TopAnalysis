import FWCore.ParameterSet.Config as cms

goodIdJets = cms.EDProducer("JetIdFunctorFilter",
    jets = cms.InputTag("selectedPatJets"),
    jetType = cms.string("CALO"),
    version = cms.string("PURE09"),
    quality = cms.string("LOOSE")   
)
