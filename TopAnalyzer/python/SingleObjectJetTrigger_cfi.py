import FWCore.ParameterSet.Config as cms

analyzeSingleObjectJetTrigger = cms.EDAnalyzer("SingleObjectJetTrigger",
           patTriggerEvent    = cms.InputTag('patTriggerEvent'),
           patTrigger         = cms.InputTag('patTrigger'),
           jets               = cms.InputTag('selectedPatJets'),
           triggerMatchedJets = cms.InputTag('triggerMatchedSelectedPatJets'),
           width              = cms.double(1.)
)



