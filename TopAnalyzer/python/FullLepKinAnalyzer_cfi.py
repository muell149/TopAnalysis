import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzeFullLepKinematics = cms.EDAnalyzer("FullLepKinAnalyzer",
    isSignalMC   = cms.bool(False),
    hypoKey      = cms.InputTag("ttFullLepHypKinSolution","Key"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    jets         = cms.InputTag("hardJets"),
    useBtagging  = cms.bool(True),
    bAlgorithm   = cms.string("trackCountingHighEffBJetTags"),
    bCut         = cms.double(3.3),
    weight       = eventWeightInputTag,
)



