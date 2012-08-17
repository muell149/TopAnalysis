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
                                          ## gen jets
                                          GenJetSrc =  cms.InputTag(""),
                                          ## gen MET
                                          GenMETSrc =  cms.InputTag(""),
                                          ## gen lepton
                                          GenLepSrc =  cms.InputTag(""),
                                          ## event weight (PU, etc...)
                                          weight = cms.InputTag("eventWeightPU","eventWeightPU"),
                                          ## primary vertex info
                                          VertexSrc = cms.InputTag("goodOfflinePrimaryVertices"),
                                          ## get kinematic fit output
                                          semiLepEvent = cms.InputTag("ttSemiLepEvent"),
                                          ## specify kinematic fit hypothesis
                                          hypoKey = cms.string("kKinFit"),
                                          ## specify btag algorithm (e.g. used for bjet multiplicity and m(bb))
                                          btagAlgo=cms.string("combinedSecondaryVertexBJetTags"),
                                          ## specify btag cut value (e.g. used for bjet multiplicity and m(bb))
                                          btagDiscr=cms.double(0.679)
                                          )



