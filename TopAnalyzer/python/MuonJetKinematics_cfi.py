import FWCore.ParameterSet.Config as cms

analyzeMuonJetKinematics = cms.EDAnalyzer("MuonJetKinematicsAnalyzer",
    ## input collectionA
    srcA = cms.InputTag("selectedLayer1Muons"),
    ## input collectionB
    srcB = cms.InputTag("selectedLayer1Jets"),                                       
    ## event weight
    weight = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(False),
    ## special parameters for muon quality analysis
    analyze   = cms.PSet(
      ## no additional configurables needed in this case
    )                                       
)



