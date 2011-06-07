import FWCore.ParameterSet.Config as cms

vertexSelectedElectrons = cms.EDProducer("ElectronVertexDistanceSelector",
  src           = cms.InputTag("selectedPatElectrons"),
  primaryVertex = cms.InputTag("offlinePrimaryVertices")
)
