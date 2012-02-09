import FWCore.ParameterSet.Config as cms

# ============================
#  Default Configuration
# ============================

PUControlDistributions = cms.EDAnalyzer('PUControlDistributionsAnalyzer',
                                        
                                        PUSource                   = cms.InputTag("addPileupInfo"),
                                        PVertexSource              = cms.InputTag("offlinePrimaryVertices"),
                                        PUEventWeightSource        = cms.InputTag("eventWeightPU",       "eventWeightPU"),
                                        PUEventWeightUpSource      = cms.InputTag("eventWeightPUsysUp",  "eventWeightPUUp"),
                                        PUEventWeightDownSource    = cms.InputTag("eventWeightPUsysDown","eventWeightPUDown"),
                                        PUEventWeight3DSource      = cms.InputTag("eventWeightPU",       "eventWeightPU3D"),
                                        PUEventWeight3DUpSource    = cms.InputTag("eventWeightPUsysUp",  "eventWeightPU3DUp"),
                                        PUEventWeight3DDownSource  = cms.InputTag("eventWeightPUsysDown","eventWeightPU3DDown"),
                                        DefEventWeight             = cms.InputTag("I","dont","mind")
                                        )

