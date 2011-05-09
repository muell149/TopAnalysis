import FWCore.ParameterSet.Config as cms

analyzeTopGenKinematics = cms.EDAnalyzer("TopKinematicsGenAnalyzer",
    ## input collection                             
    src = cms.InputTag("genEvt"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("None"),
      ## draw 1D plots only for events with rec&&gen in the same bin for stability&purity determination?
      matchForStabilityAndPurity = cms.bool(False),
      ## choose whether to save the variables in a ttree
      useTree = cms.bool(False),
      ## choose whether you want to destinguish between top/antitop instead of leptonic/hadronic top
      ttbarInsteadOfLepHadTop = cms.bool(False),
      ## number of jets considered in Kinematic fit
      ## (needed for the classification of permutations)
      maxNJets = cms.int32(4)
    )
)

analyzeTopRecKinematics = cms.EDAnalyzer("TopKinematicsRecAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("kGenMatch"),
      ## draw 1D plots only for events with rec&&gen in the same bin for stability&purity determination?
      matchForStabilityAndPurity = cms.bool(False),
      ## choose whether to save the variables in a ttree
      useTree = cms.bool(False),
      ## choose whether you want to destinguish between top/antitop instead of leptonic/hadronic top
      ttbarInsteadOfLepHadTop = cms.bool(False),
      ## number of jets considered in Kinematic fit
      ## (needed for the classification of permutations)
      maxNJets = cms.int32(4)
    )    
)

analyzeTopRecKinematicsMatched = cms.EDAnalyzer("TopKinematicsRecAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("kGenMatch"),
      ## draw 1D plots only for events with rec&&gen in the same bin for stability&purity determination?
      matchForStabilityAndPurity = cms.bool(True),
      ## choose whether to save the variables in a ttree
      useTree = cms.bool(False),
      ## choose whether you want to destinguish between top/antitop instead of leptonic/hadronic top
      ttbarInsteadOfLepHadTop = cms.bool(False),
      ## number of jets considered in Kinematic fit
      ## (needed for the classification of permutations)
      maxNJets = cms.int32(4)
    )
)

