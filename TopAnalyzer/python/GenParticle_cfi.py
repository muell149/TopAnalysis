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
      ## non right now
    )
)
