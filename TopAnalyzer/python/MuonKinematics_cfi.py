import FWCore.ParameterSet.Config as cms

analyzeMuonKinematics = cms.EDAnalyzer("MuonKinematicsAnalyzer",
    ## input collection                             
    input     = cms.InputTag("selectedLayer1Muons"),
    ## event weight
    weight    = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(True),
    ## analyzer specific configurables
    analyze   = cms.PSet()    
)



