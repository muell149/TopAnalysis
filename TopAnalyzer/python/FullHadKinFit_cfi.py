import FWCore.ParameterSet.Config as cms

analyzeFullHadKinFit = cms.EDAnalyzer("FullHadKinFit",
    ## input collection                             
    src = cms.InputTag("genParticles"),
    ## analyzer specific configurables
    ## select which jet should get smeard, set to -1 for all, counting starts at 0
    smearOnly = cms.int32( -1 ),
    ## strength of smearing
    smear = cms.double( 1.0 ),
    ## type of smearing to be used
    smearType = cms.string( "" ),
    ## scale of resolution
    resol = cms.double( 1.0 ),
    ## type of resolution to be used
    resolType = cms.string( "" ),
    ## number of bTags to be used in fit (right now only PseudoBTags an gen level)
    bTags = cms.uint32( 2 ),
    ## fill histograms only for the right combination
    onlyGenMatch = cms.bool( False ),
    ## plot histograms for all combinations instead of only for the best one
    saveAllCombo = cms.bool( False ),
    ## exchange lowest pt genParticle with one radiated particle (if more than 1 available exchange -> do it again)
    exchangePart = cms.bool( False ),
    ## use fitted event as input for another fit
    fitAsFitInpt = cms.bool( False ),
    ## only take those events, with no Non-Top-ME-genParticles
    noRadiations = cms.bool( False ),
    ## lower pt cut applied on all (pseudo) reco particles
    recoPtCut = cms.double( 30.0 ),
    ## lower pt cut applied on all genParticles
    genPtCut = cms.double( 15.0 )
)
