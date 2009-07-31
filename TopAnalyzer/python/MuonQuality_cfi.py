import FWCore.ParameterSet.Config as cms

analyzeMuonQuality = cms.EDAnalyzer("MuonQualityAnalyzer",
    ## input collection                             
    input     = cms.InputTag("selectedLayer1Muons"),
    ## event weight
    weight    = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(True),
    ## analyzer specific configurables
    analyze   = cms.PSet()    
)



