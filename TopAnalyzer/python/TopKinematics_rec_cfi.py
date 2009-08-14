import FWCore.ParameterSet.Config as cms

analyzeTopRecKinematics = cms.EDAnalyzer("TopKinematicsRecAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## event weight
    weight = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(True),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("kGenMatch"),
      ## apply matchin for stability&purity determination or not
      matchForStabilityAndPurity = cms.bool(False)
    )    
)



