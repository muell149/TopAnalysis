import FWCore.ParameterSet.Config as cms

filterLeptonVertexDistance = cms.EDFilter("LeptonVertexFilter",
    vertices = cms.InputTag('offlinePrimaryVertices'),
    muons    = cms.InputTag('selectedPatMuons'),
    elecs    = cms.InputTag('selectedPatElectrons'),

    ndof   = cms.uint32(4),
    rho    = cms.double(2),
    z      = cms.double(24),
    z_dist = cms.double(1)   
)
