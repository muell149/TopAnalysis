import FWCore.ParameterSet.Config as cms

analyzeKinFitImprover = cms.EDAnalyzer("KinFitImproveAnalyzer",
    ## input collectionA
    srcA = cms.InputTag("ttFullHadEvent"),
    ## input collectionB                            
    srcB = cms.InputTag("selectedPatJets"),                                         
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## decide which type of combination should get analyzed:
      ## 1 : right combination
      ## 2 : right quarks in branches but inner-branch mixing
      ## 3 : right jets but inter-branch mixing
      ## 4 : at least 1 jet is missing
      comboType = cms.uint32(1)
      )    
)



