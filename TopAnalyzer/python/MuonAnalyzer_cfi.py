import FWCore.ParameterSet.Config as cms

analyzeMuon = cms.EDAnalyzer("MuonAnalyzer",
    ## necessary inputs
    hist   = cms.string  ('analyzeMuon.hist'),
    weight = cms.InputTag("eventWeight"),
    input  = cms.InputTag("allLayer1Muons"),

    ## fill id  histograms
    id = cms.PSet(

    ),    
    doId = cms.bool(True),

    ## fill kin histograms
    kin = cms.PSet(
        jets = cms.InputTag("allLayer1Jets")
    ),                             
    doKin = cms.bool(True),

    ## fill res histograms
    res = cms.PSet(
        matchDR = cms.double (  0.1 ),    
        binsPt  = cms.vdouble(  0.0,  20.0, 30.0, 50.0, 80.0, 120.0, 180.0),
        binsEta = cms.vdouble( -2.5,  -1.3, -0.5,  0.0,  0.5,   1.3,   2.5),
        binsPhi = cms.vdouble(-3.14, -1.57,  0.0, 1.57, 3.14)
    ),
    doRes = cms.bool(True)
)


