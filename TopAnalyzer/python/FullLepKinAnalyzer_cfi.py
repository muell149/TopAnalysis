import FWCore.ParameterSet.Config as cms
from DileptonEventWeight_cfi import *

analyzeFullLepKinematics = cms.EDAnalyzer("FullLepKinAnalyzer",
    isSignalMC   = cms.bool(False),
    hypoKey      = cms.InputTag("ttFullLepHypKinSolution","Key"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    jets         = cms.InputTag("hardJets"),
    useBtagging  = cms.bool(True),
    bAlgorithm   = cms.string("trackCountingHighEffBJetTags"),
    weightPU     = eventWeightPUTag,
    weightLepSF  = eventWeightLepSFTag       
)



