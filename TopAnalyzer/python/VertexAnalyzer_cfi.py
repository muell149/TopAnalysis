import FWCore.ParameterSet.Config as cms
from DileptonEventWeight_cfi import *

analyzePrimaryVertex = cms.EDAnalyzer("VertexAnalyzer",

    vertices = cms.InputTag('offlinePrimaryVertices'),
    leptons  = cms.InputTag('selectedPatMuons'),

    ndof = cms.uint32(4),
    rho  = cms.double(2),
    z    = cms.double(24),
    weightPU     = eventWeightPUTag,
    weightLepSF  = eventWeightLepSFTag 
)
