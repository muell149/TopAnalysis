import FWCore.ParameterSet.Config as cms

analyzeJets = cms.EDAnalyzer("JetAnalyzer",
    doId = cms.bool(True),
    weight = cms.InputTag("eventWeight"),
    doKin = cms.bool(True),
    res = cms.PSet(
        binsPt = cms.vdouble(0.0, 10.0, 30.0, 50.0, 70.0, 100.0, 150.0, 200.0),
        matchDR = cms.double(0.1),
        nJets = cms.int32(4)
    ),
    doRes = cms.bool(True),
    hist = cms.string('analyzeJets.hist'),
    kin = cms.PSet(
        nJets = cms.int32(4)
    ),
    input = cms.InputTag("allLayer1Jets"),
    id = cms.PSet(
        nJets = cms.int32(4)
    )
)



