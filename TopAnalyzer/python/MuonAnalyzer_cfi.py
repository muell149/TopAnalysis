import FWCore.ParameterSet.Config as cms

analyzeMuon = cms.EDAnalyzer("MuonAnalyzer",
    doId = cms.bool(True),
    weight = cms.InputTag("eventWeight"),
    doKin = cms.bool(True),
    res = cms.PSet(
        binsPt = cms.vdouble(0.0, 20.0, 30.0, 50.0, 80.0, 
            120.0, 180.0),
        binsEta = cms.vdouble(-2.5, -1.3, -0.5, 0.0, 0.5, 
            1.3, 2.5),
        matchDR = cms.double(0.1),
        binsPhi = cms.vdouble(-3.14, -1.57, 0.0, 1.57, 3.14)
    ),
    doRes = cms.bool(True),
    hist = cms.string('analyzeMuon.hist'),
    kin = cms.PSet(
        jets = cms.InputTag("allLayer1Jets")
    ),
    input = cms.InputTag("allLayer1Muons"),
    id = cms.PSet(

    )
)



