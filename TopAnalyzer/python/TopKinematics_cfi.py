import FWCore.ParameterSet.Config as cms

analyzeTopGenKinematics = cms.EDAnalyzer("TopKinematicsGenAnalyzer",
    ## input collection                             
    src = cms.InputTag("genEvt"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("None"),
      ## apply matching for stability&purity determination or not
      matchForStabilityAndPurity = cms.bool(False),
      ## choose whether to save the variables in a ttree
      useTree = cms.bool(False),
      ## choose whether you want to destinguish between top/antitop instead of leptonic/hadronic top
      ttbarInsteadOfLepHadTop = cms.bool(False)
    )
)

analyzeTopRecKinematics = cms.EDAnalyzer("TopKinematicsRecAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("kGenMatch"),
      ## apply matching for stability&purity determination or not
      matchForStabilityAndPurity = cms.bool(False),
      ## choose whether to save the variables in a ttree
      useTree = cms.bool(False),
      ## choose whether you want to destinguish between top/antitop instead of leptonic/hadronic top
      ttbarInsteadOfLepHadTop = cms.bool(False)
    )    
)

analyzeTopRecKinematicsMatched = cms.EDAnalyzer("TopKinematicsRecAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("kGenMatch"),
      ## apply matching for stability&purity determination or not
      matchForStabilityAndPurity = cms.bool(True),
      ## choose whether to save the variables in a ttree
      useTree = cms.bool(False),
      ## choose whether you want to destinguish between top/antitop instead of leptonic/hadronic top
      ttbarInsteadOfLepHadTop = cms.bool(False)
      
    )    
)

