import FWCore.ParameterSet.Config as cms

tagAndProbeAnalyzer = cms.EDAnalyzer("TagAndProbeAnalyzer",
    ## input collection for jets                            
    jets = cms.InputTag("selectedLayer1Jets"),
    ## input collection for muons                    
    muons = cms.InputTag("selectedLayer1Muons")                                    
)



