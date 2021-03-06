import FWCore.ParameterSet.Config as cms

analyzeMETKinematics = cms.EDAnalyzer("METAnalyzer",
    ## input collection                        
    srcA= cms.InputTag("patMETs"),
    analyze   = cms.PSet(
        ## choose TTree for output instead of histograms, if applicable
        useTree  = cms.bool(False)
    )
)

analyzeMETCorrelations = cms.EDAnalyzer("METAnalyzer",
    ## input collections                        
    srcA= cms.InputTag("patMETs"),
    srcB= cms.InputTag("selectedPatMuons"),
    analyze   = cms.PSet(
        ## choose TTree for output instead of histograms, if applicable
        useTree  = cms.bool(False),
        ## fill correlation plots for 1.,2.,3.,... leading
        ## Object of srcB, -1 corresponds to 'all'
        ## counting starts with 0=leading Object! 
        index = cms.int32(0)                                     
    )
)
