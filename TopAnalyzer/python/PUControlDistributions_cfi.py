import FWCore.ParameterSet.Config as cms

# ============================
#  Default Configuration
# ============================

PUControlDistributions = cms.EDAnalyzer('PUControlDistributionsAnalyzer',
                                        
                                        PUSource                   = cms.InputTag("addPileupInfo"),
                                        PVertexSource              = cms.InputTag("offlinePrimaryVertices"),
                                        PUEventWeightSource        = cms.InputTag("eventWeightPU","eventWeightPU"),
                                        PUEventWeightUpSource      = cms.InputTag("eventWeightPU","eventWeightPUUp"),
                                        PUEventWeightDownSource    = cms.InputTag("eventWeightPU","eventWeightPUDown"),
                                        PUEventWeight3BXSource     = cms.InputTag("eventWeightPU","eventWeightPU3BX"),
                                        PUEventWeight3BXUpSource   = cms.InputTag("eventWeightPU","eventWeightPU3BXUp"),
                                        PUEventWeight3BXDownSource = cms.InputTag("eventWeightPU","eventWeightPU3BXDown"),
                                        PUEventWeight3DSource      = cms.InputTag("eventWeightPU","eventWeightPU3D"),
                                        PUEventWeight3DUpSource    = cms.InputTag("eventWeightPU","eventWeightPU3DUp"),
                                        PUEventWeight3DDownSource  = cms.InputTag("eventWeightPU","eventWeightPU3DDown"),
                                        DefEventWeight             = cms.InputTag("I","dont","mind")
                                        )

