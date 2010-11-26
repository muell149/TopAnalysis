import FWCore.ParameterSet.Config as cms

analyzeJetQuality = cms.EDAnalyzer("JetQualityAnalyzer",
    ## input collection                             
    src = cms.InputTag("goodJets"),
    ## special parameters for jet quality analysis
    analyze   = cms.PSet(
      ## choose TTree for output instead of histograms, if applicable
      useTree  = cms.bool(False),
      ## fill histograms for 1.,2.,3.,... leading
      ## jet? -1 corresponds to 'all'
      ## counting starts with 0=leading Jet! 
      index  = cms.int32(-1),
      ## flavor tag for the flavor dependend JEC monitor
      ## plots; the form is expected as described in
      ## SWGuidePATDataFormats#pat_JetCorrFactors
      flavor = cms.string("uds")
    )
)



