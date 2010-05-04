import FWCore.ParameterSet.Config as cms

analyzeMETKinematics = cms.EDAnalyzer("METAnalyzer",
    ## input collection                        
    srcA= cms.InputTag("patMETs")
)

analyzeMETCorrelations = cms.EDAnalyzer("METAnalyzer",
    ## input collections                        
    srcA= cms.InputTag("patMETs"),
    srcB= cms.InputTag("selectedPatMuons")                            
)
