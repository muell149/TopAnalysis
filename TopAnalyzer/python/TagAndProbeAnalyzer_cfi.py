import FWCore.ParameterSet.Config as cms

tagAndProbeAnalyzer = cms.EDAnalyzer("TagAndProbeAnalyzer",
    ## input collection for jets                            
    jets   = cms.InputTag("selectedLayer1Jets"),
    ## test collection                    
    tests  = cms.InputTag("selectedLayer1Muons"),
    ## probe collection                                     
    probes = cms.InputTag("selectedLayer1Muons")                                     
)



