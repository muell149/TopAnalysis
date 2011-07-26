import FWCore.ParameterSet.Config as cms

# ============================
#  Default Configuration
# ============================

PUControlDistributions = cms.EDAnalyzer('PUControlDistributionsAnalyzer',
                                        
                                        PUSource                = cms.InputTag("addPileupInfo"),
                                        PVertexSource           = cms.InputTag("offlinePrimaryVertices"),
                                        PUEventWeightSource     = cms.InputTag("eventWeightPU","eventWeightPU"),
                                        PUEventWeightUpSource   = cms.InputTag("eventWeightPU","eventWeightPUUp"),
                                        PUEventWeightDownSource = cms.InputTag("eventWeightPU","eventWeightPUDown")
                                        
                                        )

