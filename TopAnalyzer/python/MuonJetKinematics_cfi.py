import FWCore.ParameterSet.Config as cms

analyzeMuonJetKinematics = cms.EDAnalyzer("MuonJetKinematicsAnalyzer",
    ## input collectionA
    srcA = cms.InputTag("selectedPatMuons"),
    ## input collectionB
    srcB = cms.InputTag("selectedPatJets"),                                       
    ## special parameters for muon quality analysis
    analyze   = cms.PSet(
      ## no additional configurables needed in this case
    )                                       
)



