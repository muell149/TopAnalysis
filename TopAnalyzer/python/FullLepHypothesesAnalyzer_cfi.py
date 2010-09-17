import FWCore.ParameterSet.Config as cms

analyzeFullLepHypotheses = cms.EDAnalyzer("FullLepHypothesesAnalyzer",
    hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
    useEventWeight = cms.bool(False),
    weight = cms.InputTag("eventWeight"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    alsoWrongCharge = cms.bool(True),
    wantSummary = cms.bool(False)
)



