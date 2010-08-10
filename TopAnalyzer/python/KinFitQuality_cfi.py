import FWCore.ParameterSet.Config as cms

analyzeKinFitQuality = cms.EDAnalyzer("KinFitQualityAnalyzer",
    ## input collectionA
    srcA = cms.InputTag("ttFullHadEvent"),
    ## input collectionB                            
    srcB = cms.InputTag("selectedPatJets"),                                         
    ## analyzer specific configurables
    analyze   = cms.PSet(
    ## number of hypotheses for plot kinFit Chi2 and Prob
    numberOfHypos = cms.uint32( 1 )
    )
)



