import FWCore.ParameterSet.Config as cms

analyzeEventShapes = cms.EDAnalyzer("EventShapeAnalyzer",
    ## input collection                             
    src = cms.InputTag("selectedPatJets"),
    ## special parameters for muon quality analysis
    analyze   = cms.PSet(
      ## choose TTree for output instead of histograms, if applicable
      useTree  = cms.bool(False),
      ## correct jets up to the correction level given
      ## at SWGuidePATDataFormats#pat_JetCorrFactors;
      ## the expected form is of type 'step' or 'step:
      ## flavor'
      correctionLevel = cms.string("abs")
    )                                       
)



