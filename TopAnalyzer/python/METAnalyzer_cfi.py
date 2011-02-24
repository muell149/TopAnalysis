import FWCore.ParameterSet.Config as cms

analyzeMET = cms.EDAnalyzer("MetAnalyzer",
    
    # Source   
    METs = cms.InputTag("patMETsPF")
)

