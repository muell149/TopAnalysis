import FWCore.ParameterSet.Config as cms

analyzeFullHadTopReco = cms.EDAnalyzer("FullHadTopRecoAnalyzer",
    ## input collectionA
    srcA = cms.InputTag("ttFullHadEvent"),
    ## input collectionB                            
    srcB = cms.InputTag("selectedPatJets"),                                         
    ## event weight
    weight = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(False),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## choose hypo to be used for reco
      hypo = cms.string("kKinFit")
    )
)



