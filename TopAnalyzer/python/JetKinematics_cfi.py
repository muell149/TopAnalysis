import FWCore.ParameterSet.Config as cms

analyzeJetKinematics = cms.EDAnalyzer("JetKinematicsAnalyzer",
    ## input collection                             
    src = cms.InputTag("goodJets"),
    ## special parameters for muon quality analysis
    analyze   = cms.PSet(
      ## choose TTree for output instead of histograms, if applicable
      useTree  = cms.bool(False),
      ## fill histograms for 1.,2.,3.,... leading
      ## jet? -1 corresponds to 'all'
      ## counting starts with 0=leading Jet! 
      index = cms.int32(-1),
      ## correct jets up to the correction level given
      ## at SWGuidePATDataFormats#pat_JetCorrFactors;
      ## the expected form is of type 'step' or 'step:
      ## flavor'
      correctionLevel = cms.string("abs")
    )                                       
)



