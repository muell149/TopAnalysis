import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzeElectronPrimaryVertex = cms.EDAnalyzer("ElectronVertexAnalyzer",

    vertices     = cms.InputTag('offlinePrimaryVertices'),
    electrons    = cms.InputTag('selectedPatElectrons'),
    beamspot     = cms.InputTag('offlineBeamSpot'),

    ndof = cms.uint32(4),
    rho  = cms.double(2),
    z    = cms.double(24),
    weight = eventWeightInputTag

)
