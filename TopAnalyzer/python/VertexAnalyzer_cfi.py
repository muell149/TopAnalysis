import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzePrimaryVertex = cms.EDAnalyzer("VertexAnalyzer",

    vertices = cms.InputTag('offlinePrimaryVertices'),
    leptons  = cms.InputTag('selectedPatMuons'),

    ndof = cms.uint32(4),
    rho  = cms.double(2),
    z    = cms.double(24),
    weight = eventWeightInputTag
)
