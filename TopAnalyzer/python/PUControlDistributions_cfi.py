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
                                        DefEventWeight             = cms.InputTag("I","dont","mind"),
                                        MCSampleTag                = cms.string("Fall11")
                                        )

