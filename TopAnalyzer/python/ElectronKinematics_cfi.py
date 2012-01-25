import FWCore.ParameterSet.Config as cms

analyzeElectronKinematics = cms.EDAnalyzer("ElectronKinematicsAnalyzer",
    ## input collection                             
    src = cms.InputTag("selectedPatElectrons"),
    ## special parameters for electron quality analysis
    analyze   = cms.PSet(
      ## choose TTree for output instead of histograms, if applicable
      useTree  = cms.bool(False),
      ## fill histograms for 1.,2.,3.,... leading
      ## counting starts with 0=leading Electron! 
      ## electron? -1 corresponds to 'all'
      index = cms.int32(0)
    )                                       
)



