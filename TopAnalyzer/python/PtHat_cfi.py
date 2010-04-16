import FWCore.ParameterSet.Config as cms

analyzePtHat = cms.EDAnalyzer("PtHatAnalyzer",
    ## input collection                             
    src = cms.InputTag("generator"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
    ## nothing to choose right now
    )
)
