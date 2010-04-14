import FWCore.ParameterSet.Config as cms

analyzeGenParticles = cms.EDAnalyzer("GenParticleAnalyzer",
    ## input collection                             
    src = cms.InputTag("genParticles"),
    ## event weight
    weight = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(False),
    ## analyzer specific configurables
    analyze   = cms.PSet(
    ## choose the status of the genParticles to be listed
    ## status =  1 : shower particles
    ## status =  2 : 
    ## status =  3 : ME (matrix element) level particles
    ## status = -1 : take all
    status = cms.int32(3)
    )
)
