import FWCore.ParameterSet.Config as cms

analyzeHypothesisKinFit = cms.EDAnalyzer("HypothesisKinFitAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("kKinFit"),
      ## choose if you want to have a tree
      wantTree = cms.bool(False),
      ## number of jets considered in Kinematic fit
      ## (needed for the classification of permutations)
      maxNJets = cms.int32(4)
    )
)



