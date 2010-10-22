import FWCore.ParameterSet.Config as cms

analyzeHTlep = cms.EDAnalyzer("HTlepAnalyzer",
    ## input collections                        
    srcA= cms.InputTag("patMETs"),
    srcB= cms.InputTag("selectedPatMuons"),
    analyze   = cms.PSet()
)
