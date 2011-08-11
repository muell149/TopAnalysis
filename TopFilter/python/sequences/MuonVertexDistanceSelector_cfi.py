import FWCore.ParameterSet.Config as cms

vertexSelectedMuons = cms.EDProducer("MuonVertexDistanceSelector",
  src           = cms.InputTag("selectedPatMuons"),
  primaryVertex = cms.InputTag("offlinePrimaryVertices"),
  cutValue      = cms.double(1.)
)
