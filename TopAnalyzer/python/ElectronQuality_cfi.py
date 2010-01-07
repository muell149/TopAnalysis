import FWCore.ParameterSet.Config as cms

analyzeElectronQuality = cms.EDAnalyzer("ElectronQualityAnalyzer",
    ## input collection                             
    src = cms.InputTag("selectedLayer1Electrons"),
    ## event weight
    weight = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(False),
    ## special parameters for electron quality analysis
    analyze   = cms.PSet(
      ## fill histograms for 1.,2.,3.,... leading
      ## electron? -1 corresponds to 'all'
      ## counting starts with 0=leading Electron! 
      index = cms.int32(0)
    )
)



