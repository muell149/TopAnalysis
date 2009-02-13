import FWCore.ParameterSet.Config as cms

analyzeFullLepHypotheses = cms.EDAnalyzer("FullLepHypothesesAnalyzer",
    hist = cms.string('analyzeFullLepHypotheses.hist'),
    hypoKey = cms.InputTag("ttFullLepHypWMassMaxSumPt","Key"),
    weight = cms.InputTag("eventWeight"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    maxSumDRGenMatch = cms.double(0.8),
    nJetsMax = cms.uint32(8),
    minProbKinFit = cms.double(0.05)
)



