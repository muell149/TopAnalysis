import FWCore.ParameterSet.Config as cms

analyzeElectronKinematics = cms.EDAnalyzer("ElectronKinematicsAnalyzer",
    ## input collection                             
    src = cms.InputTag("cleanPatElectrons"),
    ## special parameters for electron quality analysis
    analyze   = cms.PSet(
      ## fill histograms for 1.,2.,3.,... leading
      ## counting starts with 0=leading Electron! 
      ## electron? -1 corresponds to 'all'
      index = cms.int32(0)
    )                                       
)



