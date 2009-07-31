import FWCore.ParameterSet.Config as cms

analyzeTopGenKinematics = cms.EDAnalyzer("TopKinematicsGenAnalyzer",
    ## input collection                             
    input     = cms.InputTag("genEvt"),
    ## event weight
    weight    = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(True),
    ## analyzer specific configurables
    analyze   = cms.PSet()    
)



