import FWCore.ParameterSet.Config as cms

analyzePrimaryVertex = cms.EDAnalyzer("VertexAnalyzer",

    vertices = cms.InputTag('offlinePrimaryVertices'),
    muons    = cms.InputTag('selectedPatMuons'),
    
    ndof = cms.uint32(4),
    rho  = cms.double(2),
    z    = cms.double(24)    
)
