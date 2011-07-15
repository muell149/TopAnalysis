import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzeFullLepKinematics = cms.EDAnalyzer("FullLepKinAnalyzer",
    isSignalMC   = cms.bool(False),
    hypoKey      = cms.InputTag("ttFullLepHypKinSolution","Key"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    jets         = cms.InputTag("hardJets"),
    weight = eventWeightInputTag
)



