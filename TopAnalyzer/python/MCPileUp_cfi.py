import FWCore.ParameterSet.Config as cms

MCPUDistribution = cms.EDAnalyzer('MCPileUp',                                     

                                  PUSource    = cms.InputTag("addPileupInfo")

                                  )


