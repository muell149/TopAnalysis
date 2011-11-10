import FWCore.ParameterSet.Config as cms

analyzeHypothesisKinFitMET = cms.EDAnalyzer("HypothesisKinFitMETAnalyzer",
    ## input collectionA
    srcA = cms.InputTag("ttSemiLepEvent"),
    ## input collectionB                            
    srcB = cms.InputTag("patMETs"),                                         
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## consider only events with correct jet assignment?
      ## judgement is done wrt. dR matching algorithm
      corrPerm=cms.bool(False),
      ## apply chi2 cut for events plotted
      maxChi2=cms.double(10000)
    )    
)



