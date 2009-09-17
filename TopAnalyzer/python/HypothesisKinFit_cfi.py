import FWCore.ParameterSet.Config as cms

analyzeHypothesisKinFit = cms.EDAnalyzer("HypothesisKinFitAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## event weight
    weight = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(True),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## no additional configurables needed in this case
    )    
)



