import FWCore.ParameterSet.Config as cms

analyzeHypothesisKinFitMuon = cms.EDAnalyzer("HypothesisKinFitMuonAnalyzer",
    ## input collectionA
    srcA = cms.InputTag("ttSemiLepEvent"),
    ## input collectionB                            
    srcB = cms.InputTag("selectedPatMuons"),                                         
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## no additional configurables needed in this case
    )    
)



