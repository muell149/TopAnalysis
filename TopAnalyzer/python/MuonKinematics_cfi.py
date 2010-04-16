import FWCore.ParameterSet.Config as cms

analyzeMuonKinematics = cms.EDAnalyzer("MuonKinematicsAnalyzer",
    ## input collection                             
    src = cms.InputTag("selectedPatMuons"),
    ## special parameters for muon quality analysis
    analyze   = cms.PSet(
      ## fill histograms for 1.,2.,3.,... leading
      ## counting starts with 0=leading Muon! 
      ## muon? -1 corresponds to 'all'
      index = cms.int32(0)
    )                                       
)



