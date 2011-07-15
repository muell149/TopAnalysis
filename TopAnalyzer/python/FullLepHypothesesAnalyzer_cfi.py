import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzeFullLepHypotheses = cms.EDAnalyzer("FullLepHypothesesAnalyzer",
    hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
    useEventWeight = cms.bool(False),
    weight = eventWeightInputTag,
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    alsoWrongCharge = cms.bool(True),
    wantSummary = cms.bool(False)
)



