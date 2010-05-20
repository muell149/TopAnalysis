import FWCore.ParameterSet.Config as cms

analyzeFullHadKinFit = cms.EDAnalyzer("FullHadKinFit",
    ## input collection                             
    src = cms.InputTag("genParticles"),
    ## analyzer specific configurables
    ## select which jet should get smeard, set to -1 for all, counting starts at 0
    smearOnly = cms.int32( -1 ),
    ## strength of smearing
    smear = cms.double( 1.0 ),
    ## scale of resolution
    resol = cms.double( 1.0 )
)
