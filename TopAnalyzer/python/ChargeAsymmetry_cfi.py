import FWCore.ParameterSet.Config as cms

analyzeChargeAsymmetry = cms.EDAnalyzer("ChargeAsymmetryAnalyzer",
    ## input collection. This is expected to be generator level lepton
    src = cms.InputTag("genParticles"),
    ## special parameters
      analyze   = cms.PSet(
      ## fill histograms for 1.,2.,3.,... leading lepton
      ## counting starts with 0=leading Lepton! 
      ## index = -1 corresponds to 'all'
      index = cms.int32(-1),
      ## choose lepton you want to fill
      ## lepton = -1 corresponds to all objects within the collection
      lepton = cms.int32(-1)
    )                                       
)
