import FWCore.ParameterSet.Config as cms

analyzeFullHadTopReco = cms.EDAnalyzer("FullHadTopRecoAnalyzer",
    ## input collectionA
    srcA = cms.InputTag("ttFullHadEvent"),
    ## input collectionB                            
    srcB = cms.InputTag("selectedPatJets"),                                         
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## choose TTree for output instead of histograms, if applicable
      useTree  = cms.bool(False),
      ## choose hypo to be used for reco
      hypo     = cms.string("kKinFit"),
      ## choose b-tagging algorithm
      bTagAlgo = cms.string("simpleSecondaryVertexBJetTags"),
      ## top mass for respective plots
      topMass  = cms.double(172.5),
      ## window around top mass for respective plots
      window   = cms.double(30.0)      
    )
)



