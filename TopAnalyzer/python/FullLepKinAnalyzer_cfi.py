import FWCore.ParameterSet.Config as cms

analyzeFullLepKinematics = cms.EDAnalyzer("FullLepKinAnalyzer",
    hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    jets = cms.InputTag("hardJets")
)



