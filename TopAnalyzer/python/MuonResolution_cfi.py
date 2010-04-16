import FWCore.ParameterSet.Config as cms

analyzeMuonResolution = cms.EDAnalyzer("MuonResolutionAnalyzer",
    ## input collection                             
    src = cms.InputTag("selectedPatMuons"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      matchDR = cms.double ( 0.1),
      binsPt  = cms.vdouble( 0.0,   20.0,  30.0,  50.0,  80.0, 120.0, 180.0),
      binsEta = cms.vdouble(-2.5,   -1.3,  -0.5,   0.0,   0.5,   1.3,   2.5),
      binsPhi = cms.vdouble(              -3.14, -1.57,   0.0,  1.57,  3.14)
    )    
)



