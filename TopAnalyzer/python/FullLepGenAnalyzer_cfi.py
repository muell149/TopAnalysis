import FWCore.ParameterSet.Config as cms

analyzeFullLepGenEvent = cms.EDAnalyzer("FullLepGenAnalyzer",
    weight = cms.InputTag('eventWeightPU')
)



