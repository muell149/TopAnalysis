import FWCore.ParameterSet.Config as cms

analyzeKinFitImprover = cms.EDAnalyzer("KinFitImproveAnalyzer",
    ## input collectionA
    srcA = cms.InputTag("ttFullHadEvent"),
    ## input collectionB                            
    srcB = cms.InputTag("selectedPatJets"),                                         
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## no additional configurables needed in this case
    )    
)



