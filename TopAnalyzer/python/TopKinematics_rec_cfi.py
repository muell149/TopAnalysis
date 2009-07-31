import FWCore.ParameterSet.Config as cms

analyzeTopRecKinematics = cms.EDAnalyzer("TopKinematicsRecAnalyzer",
    ## input collection                             
    input     = cms.InputTag("ttSemiLepEvent"),
    ## event weight
    weight    = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(True),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      hypoKey = cms.int32(3)
    )    
)



