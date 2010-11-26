import FWCore.ParameterSet.Config as cms

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## electron selector
from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *

## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
## electron count filter
from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *

#-------------------------------------------------
# cleaning
#-------------------------------------------------

from PhysicsTools.PatAlgos.cleaningLayer1.cleanPatCandidates_cff import *

## Electron cleaning against muons

cleanPatElectrons.src = "selectedPatElectrons"

cleanPatElectrons.checkOverlaps.muons.preselection = cms.string( 'isTrackerMuon'
                                                                 '& isGlobalMuon'
                                                                 '& abs(eta) < 2.4'
                                                                 '& pt > 20.'
                                                                 '& track.numberOfValidHits > 10'
                                                                 '& abs(dB) < 0.02'
                                                                 '& combinedMuon.normalizedChi2 < 10.0'
                                                                 '& (trackIso+caloIso)/pt < 0.15'
                                                                 )
cleanPatElectrons.checkOverlaps.muons.deltaR = 0.1
cleanPatElectrons.checkOverlaps.muons.requireNoOverlaps = True

## Jet cleaning against electrons & muons

cleanPatJets.src = "selectedPatJetsAK5PF"
#cleanPatJets.src = "selectedPatJets"

cleanPatJets.checkOverlaps.muons.preselection = cms.string( 'isTrackerMuon'
                                                            '& isGlobalMuon'
                                                            '& abs(eta) < 2.4'
                                                            '& pt > 20.'
                                                            '& track.numberOfValidHits > 10'
                                                            '& abs(dB) < 0.02'
                                                            '& combinedMuon.normalizedChi2 < 10.0'
                                                            '& (trackIso+caloIso)/pt < 0.15'
                                                            )
cleanPatJets.checkOverlaps.muons.deltaR = 0.4
cleanPatJets.checkOverlaps.muons.requireNoOverlaps = True

cleanPatJets.checkOverlaps.electrons.preselection = cms.string( 'abs(eta) < 2.5'
                                                                '& et > 20.'
                                                                '& electronID(\"eidRobustTight\") > 6.99'
                                                                #'& electronID(\"simpleEleId90relIso\") > 6.99'
                                                                '& (trackIso+caloIso)/et < 0.15'
                                                                )
cleanPatJets.checkOverlaps.electrons.deltaR = 0.4
cleanPatJets.checkOverlaps.electrons.requireNoOverlaps = True

#-------------------------------------------------
# muon selection
#-------------------------------------------------

## Build Collections

## muons reconstructed as track muon
trackerMuons = selectedPatMuons.clone( src = 'selectedPatMuons',
                                       cut = 'isTrackerMuon'
                                       )

## muons reconstructed globally
globalMuons = selectedPatMuons.clone( src = 'trackerMuons',
                                      cut = 'isGlobalMuon'
                                      )
## muons in tracker range
tightMuons = selectedPatMuons.clone( src = 'globalMuons',
                                     cut = 'abs(eta) < 2.4'
                                     )

## pt cut
hardMuons = selectedPatMuons.clone( src = 'tightMuons',
                                    cut = 'pt > 20.'
                                    )

## n_hits
goodTrackMuons = selectedPatMuons.clone( src = 'hardMuons',
                                         cut = 'track.numberOfValidHits > 10'
                                         )

## transverse impact parameter
goodD0Muons = selectedPatMuons.clone( src = 'goodTrackMuons',
                                      cut = 'abs(dB) < 0.02'
                                      )

## global fit
goodFitMuons = selectedPatMuons.clone( src = 'goodD0Muons',
                                       cut = 'combinedMuon.normalizedChi2 < 10.0'
                                       )

## isolation cut
isolatedMuons = selectedPatMuons.clone( src = 'goodFitMuons',
                                        cut = '(trackIso+caloIso)/pt < 0.15'
                                        )

## Count Filters
tightMuonSelection     = countPatMuons.clone(src = 'tightMuons',     minNumber = 1)
trackerMuonSelection   = countPatMuons.clone(src = 'trackerMuons',   minNumber = 1)
globalMuonSelection    = countPatMuons.clone(src = 'globalMuons',    minNumber = 1)
hardMuonSelection      = countPatMuons.clone(src = 'hardMuons',      minNumber = 1)
goodTrackMuonSelection = countPatMuons.clone(src = 'goodTrackMuons', minNumber = 1)
goodD0MuonSelection    = countPatMuons.clone(src = 'goodD0Muons',    minNumber = 1)
goodFitMuonSelection   = countPatMuons.clone(src = 'goodFitMuons',   minNumber = 1)
isolatedMuonSelection  = countPatMuons.clone(src = 'isolatedMuons',  minNumber = 1)

#-------------------------------------------------
# electron selection
#-------------------------------------------------

## Build Collections

centralElectrons = selectedPatElectrons.clone( src = 'cleanPatElectrons',
                                               cut = 'abs(eta) < 2.5'
                                               )

highPtElectrons = selectedPatElectrons.clone( src = 'centralElectrons',
                                              cut = 'et > 20.'
                                              )

idOnlyElectrons = selectedPatElectrons.clone( src = 'highPtElectrons',
                                              cut = 'electronID(\"eidRobustTight\") > 6.99'
                                              #cut = 'electronID(\"simpleEleId90relIso\") > 6.99'
                                              )

isolatedElectrons = selectedPatElectrons.clone( src = 'idOnlyElectrons',
                                                cut = '(trackIso+caloIso)/et < 0.15'
                                                )

## exact one very tight selected tag electron
idOnlyElectronSelection   = countPatElectrons.clone(src = 'idOnlyElectrons',   minNumber = 1, maxNumber = 999)
centralElectronSelection  = countPatElectrons.clone(src = 'centralElectrons',  minNumber = 1, maxNumber = 999)
highPtElectronSelection   = countPatElectrons.clone(src = 'highPtElectrons',   minNumber = 1, maxNumber = 999)
isolatedElectronSelection = countPatElectrons.clone(src = 'isolatedElectrons', minNumber = 1, maxNumber = 999)

#-------------------------------------------------
# jet selection
#-------------------------------------------------

## Build Collections

## good jet selection
goodJets = selectedPatJets.clone( src = 'cleanPatJets',
                                  cut = 'pt > 15.'
                                  )

## thight jet selection
tightJets = selectedPatJets.clone(src = 'goodJets',
                                  cut = 'abs(eta) < 2.5'
                                  )

## hard jet selection
hardJets = selectedPatJets.clone( src = 'tightJets',
                                  cut = 'pt > 30.'
                                  )

## jet ID selection
goodIdJets = selectedPatJets.clone( src = 'hardJets',
                                    cut = 'emEnergyFraction > 0.01'
                                          '& jetID.fHPD < 0.98'
                                          '& jetID.n90Hits > 1'
                                    )

## jet PF ID selection
goodIdJetsPF = selectedPatJets.clone( src = 'hardJets',
                                      cut = 'chargedHadronEnergyFraction > 0.'
                                            '& neutralHadronEnergyFraction/corrFactor("raw") < 0.99'
                                            '& chargedEmEnergyFraction/corrFactor("raw") < 0.99'
                                            '& neutralEmEnergyFraction/corrFactor("raw") < 0.99'
                                            '& chargedMultiplicity > 0'
                                            '& nConstituents > 0'
                                      )

## check for different btag properties
trackCountingHighEffBJets = selectedPatJets.clone( src = 'goodIdJetsPF',
                                                   cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 1.7'
                                                   )

simpleSecondaryVertexBJets = selectedPatJets.clone( src = 'goodIdJetsPF',
                                                    cut = 'bDiscriminator(\"simpleSecondaryVertexHighEffBJetTags\") > 1.74'
                                                    )

## Count Filters
hardJetSelection     = countPatJets.clone(src = 'hardJets',     minNumber = 2)
tightJetSelection    = countPatJets.clone(src = 'tightJets',    minNumber = 2)
goodIdJetSelection   = countPatJets.clone(src = 'goodIdJets',   minNumber = 2)
goodIdJetPFSelection = countPatJets.clone(src = 'goodIdJetsPF', minNumber = 2)
bJetTCHSelection     = countPatJets.clone(src = 'trackCountingHighEffBJets',  minNumber = 1)
bJetSSVSelection     = countPatJets.clone(src = 'simpleSecondaryVertexBJets', minNumber = 1)

#-------------------------------------------------
# met selection
#-------------------------------------------------

## met selector
highMETs = cms.EDFilter( "PATMETSelector",
                         src = cms.InputTag("patMETsPF"),
                         cut = cms.string("et > 20.")
                         )

## Count Filter
metSelection = cms.EDFilter("PATCandViewCountFilter",
                            minNumber = cms.uint32(1),
                            maxNumber = cms.uint32(999999),
                            src = cms.InputTag("highMETs")
                            )

#-------------------------------------------------
# sequences
#-------------------------------------------------

applyCleaning    = cms.Sequence( cleanPatCandidates )

oneGoodMuonSelection = cms.Sequence( goodJets *
                                     trackerMuons *
                                     trackerMuonSelection *
                                     globalMuons *
                                     globalMuonSelection *
                                     tightMuons *
                                     tightMuonSelection *
                                     hardMuons *
                                     hardMuonSelection *
                                     goodTrackMuons *
                                     goodTrackMuonSelection *
                                     goodD0Muons *
                                     goodD0MuonSelection *
                                     goodFitMuons *
                                     goodFitMuonSelection
                                     )

oneIsolatedMuonSelection = cms.Sequence( isolatedMuons *
                                         isolatedMuonSelection
                                         )

oneIsolatedElectronSelection = cms.Sequence( centralElectrons *
                                             centralElectronSelection *
                                             highPtElectrons *
                                             highPtElectronSelection *
                                             idOnlyElectrons *
                                             idOnlyElectronSelection *
                                             isolatedElectrons *
                                             isolatedElectronSelection
                                             )

jetMETSelection = cms.Sequence( tightJets *
                                tightJetSelection *
                                hardJets *
                                hardJetSelection *
                                # goodIdJets *
                                # goodIdJetSelection *
                                goodIdJetsPF *
                                goodIdJetPFSelection *

                                # trackCountingHighEffBJets *
                                # bJetTCHSelection *
                                # simpleSecondaryVertexBJets *
                                # bJetSSVSelection *

                                highMETs *
                                metSelection
                                )
