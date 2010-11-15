import FWCore.ParameterSet.Config as cms

analyzeL1QuadJetTrigger = cms.EDAnalyzer("L1QuadJetTriggerAnalyzer",
                                         patTriggerEvent = cms.InputTag("patTriggerEvent")
                                         )



