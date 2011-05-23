import FWCore.ParameterSet.Config as cms

filterElectronVertexDistance = cms.EDFilter("ElectronVertexFilter",
    vertices = cms.InputTag('offlinePrimaryVertices'),
    src      = cms.InputTag('selectedPatElectrons'),
    n_leps   = cms.uint32(2),

    ndof   = cms.uint32(4),
    rho    = cms.double(2),
    z      = cms.double(24),
    z_dist = cms.double(1)
)
