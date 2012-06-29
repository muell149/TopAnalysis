import FWCore.ParameterSet.Config as cms

analyzeCompositedObjects = cms.EDAnalyzer("MixedObjectsAnalyzer",
                                  ## jets
                                  JetSrc = cms.InputTag('selectedPatJets'),
                                  ## MET
                                  METSrc = cms.InputTag('patMETs'),
                                  ## muons
                                  MuonSrc = cms.InputTag('selectedPatMuons'),
                                  ## electrons
                                  ElectronSrc = cms.InputTag('selectedPatElectrons'),
                                  ## event weight (PU, etc...)
                                  weight = cms.InputTag("eventWeightPU","eventWeightPU"),
                                  ## primary vertex info
                                  VertexSrc = cms.InputTag("goodOfflinePrimaryVertices")

                                          )



