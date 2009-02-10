import FWCore.ParameterSet.Config as cms

analyzeMuon = cms.EDAnalyzer("MuonAnalyzer",
    input   = cms.InputTag("selectedLayer1Muons"),
    hist    = cms.string('analyzeMuon.hist'),

    ## event weight
    useEventWeight = cms.bool(True),
    weight  = cms.InputTag("eventWeight"),  
                             
    ## fill id  histograms
    id = cms.PSet(
    ),    
    doId = cms.bool(True),

    ## fill kin histograms
    kin = cms.PSet(
        jets = cms.InputTag("selectedLayer1Jets")
    ),
    doKin = cms.bool(True),

    ## fill res histograms
    res = cms.PSet(
        binsPt  = cms.vdouble( 0.0, 20.0, 30.0, 50.0, 80.0, 120.0, 180.0),
        binsEta = cms.vdouble(-2.5, -1.3, -0.5,  0.0,  0.5,   1.3,   2.5),
        matchDR = cms.double (0.1),
        binsPhi = cms.vdouble(-3.14, -1.57, 0.0, 1.57, 3.14)
    ),                             
    doRes = cms.bool(True)
)



