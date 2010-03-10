import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## jet selectors
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
from TopAnalysis.TopFilter.sequences.jetSelection_cff import *

## ---
##    setup jet parton matching
## ---

## jet to parton matching
matchedLightQJets  = selectedPatJets.clone(src = 'selectedPatJets',
                                              cut = 'abs(partonFlavour()) < 5'
                                              )
matchedBottomJets  = selectedPatJets.clone(src = 'selectedPatJets',
                                              cut = 'abs(partonFlavour()) = 5'
                                              )
matchedCharmJets   = selectedPatJets.clone(src = 'selectedPatJets',
                                              cut = 'abs(partonFlavour()) = 4'
                                              )
matchedUdsJets     = selectedPatJets.clone(src = 'selectedPatJets',
                                              cut = 'abs(partonFlavour()) < 4'
                                              )
tightMatchedLightQJets  = selectedPatJets.clone(src = 'goodJets',
                                              cut = 'abs(partonFlavour()) < 5'
                                              )
tightMatchedBottomJets  = selectedPatJets.clone(src = 'goodJets',
                                              cut = 'abs(partonFlavour()) = 5'
                                              )
tightMatchedCharmJets   = selectedPatJets.clone(src = 'goodJets',
                                              cut = 'abs(partonFlavour()) = 4'
                                              )
tightMatchedUdsJets     = selectedPatJets.clone(src = 'goodJets',
                                              cut = 'abs(partonFlavour()) < 4'
                                              )

## four sets of differently matched jet collections
## jets are matched to parton level
matchJetsToPartons = cms.Sequence(matchedLightQJets      +
                                  matchedBottomJets      +
                                  matchedCharmJets       +
                                  matchedUdsJets         +
                                  tightMatchedLightQJets +
                                  tightMatchedBottomJets +
                                  tightMatchedCharmJets  +
                                  tightMatchedUdsJets
                                  )

## muon matching to generator level
matchedMuons         = selectedPatMuons.clone(src = 'selectedPatMuons',
                                                 cut = 'genLepton.isNull = 0 &'
                                                       'abs(genLepton.pdgId) = 13 &'
                                                 )
matchedIsolatedMuons = selectedPatMuons.clone(src = 'selectedPatMuons',
                                                 cut = 'genLepton.isNull = 0 &'
                                                       'abs(genLepton.pdgId) = 13 &'
                                                       'genLepton.mother.isNull = 0 &'
                                                       'abs(genLepton.mother.pdgId()) = 24'
                                                 )

## matching of isolated muons means matching
## to muons that originate from W bosons
matchMuonsToGenerator= cms.Sequence(matchedMuons +
                                    matchedIsolatedMuons
                                    )
