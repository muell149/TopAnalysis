import FWCore.ParameterSet.Config as cms

analyzeTriggerEfficiency = cms.EDAnalyzer("TriggerEfficiency",
      patTriggerEvent    = cms.InputTag('patTriggerEvent')
)



