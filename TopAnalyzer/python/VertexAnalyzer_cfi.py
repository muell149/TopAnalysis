import FWCore.ParameterSet.Config as cms

analyzePrimaryVertex = cms.EDAnalyzer("VertexAnalyzer",

    vertices = cms.InputTag('offlinePrimaryVertices'),
    muons    = cms.InputTag('selectedPatMuons')
)
