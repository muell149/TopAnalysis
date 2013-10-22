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
                                          ## gen jets coming not from ttbar decay (additional radiation) 
                                          addGenJetSrc =  cms.InputTag(""),
                                          ## gen MET
                                          GenMETSrc =  cms.InputTag(""),
                                          ## gen lepton
                                          GenLepSrc =  cms.InputTag(""),                                          
                                          ## within visible cross section range?
                                          ingenPS = cms.InputTag("visiblePhaseSpace", "inVisiblePS"),
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
                                          btagDiscr=cms.double(0.679),
                                          ## specify pt value to be used for additional (non-ttbar) jets
                                          addJetPt=cms.double(30.)
                                          )



