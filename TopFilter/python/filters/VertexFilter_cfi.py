import FWCore.ParameterSet.Config as cms

filterOnPrimaryVertex = cms.EDAnalyzer("VertexFilter",

    vertices      = cms.InputTag('offlinePrimaryVertices'),
    position_cuts = cms.vdouble(1.,1.,20.),
    n_tracks      = cms.uint32(2)
)
