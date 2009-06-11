import FWCore.ParameterSet.Config as cms

analyzeFullLepHypothesesBSM = cms.EDAnalyzer("FullLepHypothesesAnalyzerBSM",
    hist = cms.string('analyzeFullLepHypotheses.hist'),
    hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
    weight = cms.InputTag("eventWeight"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    maxSumDRGenMatch = cms.double(0.8),
    alsoWrongCharge = cms.bool(True),
    minProbKinFit = cms.double(0.05)
)



