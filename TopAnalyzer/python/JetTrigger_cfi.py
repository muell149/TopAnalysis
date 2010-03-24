import FWCore.ParameterSet.Config as cms

analyzeJetTrigger = cms.EDAnalyzer("JetTrigger",
                                   TriggerResults     = cms.InputTag('TriggerResults','','HLT'),
                                   TriggerSummary     = cms.InputTag('hltTriggerSummaryAOD','','HLT'),
                                   patTriggerEvent    = cms.InputTag('patTriggerEvent'),
                                   patTrigger         = cms.InputTag('patTrigger'),
                                   jets               = cms.InputTag('selectedPatJets'),
                                   triggerMatchedJets = cms.InputTag('triggerMatchedSelectedPatJets'),
                                   analyzedTrigger    = cms.InputTag('hlt4jet30', '', 'HLT')
)



