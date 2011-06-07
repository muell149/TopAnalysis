import FWCore.ParameterSet.Config as cms

filterLooseElectrons = cms.EDFilter("SecondElectronFilter",
  elecsTight         = cms.InputTag("isolatedElectrons")  ,
  elecsLoose         = cms.InputTag("looseElectrons")     ,
  massWindow         = cms.vdouble(76.,106.)
)
