import FWCore.ParameterSet.Config as cms

analyzePtHat = cms.EDAnalyzer("PtHatAnalyzer",
    ## input collection                             
    src = cms.InputTag("generator"),
    ## event weight
    weight = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(False),
    ## analyzer specific configurables
    analyze   = cms.PSet(
    ## nothing to choose right now
    )
)
