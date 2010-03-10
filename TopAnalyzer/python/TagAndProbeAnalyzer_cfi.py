import FWCore.ParameterSet.Config as cms

tagAndProbeAnalyzer = cms.EDAnalyzer("TagAndProbeAnalyzer",
    ## input collection for jets                            
    jets   = cms.InputTag("selectedPatJets"),
    ## test collection                    
    tests  = cms.InputTag("selectedPatMuons"),
    ## probe collection                                     
    probes = cms.InputTag("selectedPatMuons")                                     
)



