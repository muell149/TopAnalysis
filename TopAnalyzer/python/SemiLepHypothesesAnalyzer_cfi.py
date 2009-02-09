import FWCore.ParameterSet.Config as cms

analyzeSemiLepHypotheses = cms.EDAnalyzer("SemiLepHypothesesAnalyzer",
    hist             = cms.string('analyzeSemiLepHypotheses.hist'),
    weight           = cms.InputTag("eventWeight"),
    semiLepEvent     = cms.InputTag("ttSemiLepEvent"),
    hypoClassKey     = cms.InputTag("ttSemiLepHypWMassMaxSumPt","Key"),
    nJetsMax         = cms.uint32(8),
    maxSumDRGenMatch = cms.double(0.8),
    minMVADisc       = cms.double(0.6),
    minProbKinFit    = cms.double(0.05)
)



