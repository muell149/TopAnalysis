import FWCore.ParameterSet.Config as cms

analyzeJetCombinatorics = cms.EDAnalyzer("JetCombinatoricsAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key
      hypoKey = cms.string("kGenMatch")
    )    
)



