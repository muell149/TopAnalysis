import FWCore.ParameterSet.Config as cms

analyzeTopGenKinematics = cms.EDAnalyzer("TopKinematicsGenAnalyzer",
    ## input collection                             
    src = cms.InputTag("genEvt"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("None"),
      ## apply matchin for stability&purity determination or not
      matchForStabilityAndPurity = cms.bool(False)
    )
)

analyzeTopRecKinematics = cms.EDAnalyzer("TopKinematicsRecAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("kGenMatch"),
      ## apply matchin for stability&purity determination or not
      matchForStabilityAndPurity = cms.bool(False)
    )    
)

analyzeTopRecKinematicsMatched = cms.EDAnalyzer("TopKinematicsRecAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("kGenMatch"),
      ## apply matchin for stability&purity determination or not
      matchForStabilityAndPurity = cms.bool(True)
    )    
)

