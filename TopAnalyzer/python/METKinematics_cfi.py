import FWCore.ParameterSet.Config as cms

analyzeMETKinematics = cms.EDAnalyzer("METAnalyzer",
    ## input collection                        
    src= cms.InputTag("patMETs"))


