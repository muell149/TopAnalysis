import FWCore.ParameterSet.Config as cms

analyzeEventShapes = cms.EDAnalyzer("EventShapeAnalyzer",
    ## input collection                             
    src = cms.InputTag("selectedPatJets"),
    ## event weight
    weight = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(False),
    ## special parameters for muon quality analysis
    analyze   = cms.PSet(
      ## correct jets up to the correction level given
      ## at SWGuidePATDataFormats#pat_JetCorrFactors;
      ## the expected form is of type 'step' or 'step:
      ## flavor'
      correctionLevel = cms.string("abs")
    )                                       
)



