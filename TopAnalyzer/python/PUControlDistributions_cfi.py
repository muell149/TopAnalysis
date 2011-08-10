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
                                        DefEventWeight             = cms.InputTag("I","dont","weight")
                                        )

