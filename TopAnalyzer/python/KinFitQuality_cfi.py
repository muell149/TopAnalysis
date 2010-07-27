import FWCore.ParameterSet.Config as cms

analyzeKinFitQuality = cms.EDAnalyzer("KinFitQualityAnalyzer",
    ## input collectionA
    srcA = cms.InputTag("ttFullHadEvent"),
    ## input collectionB                            
    srcB = cms.InputTag("selectedPatJets"),                                         
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## no additional configurables needed in this case
    numberOfHypos = cms.uint32( 1 )
    )    
)



