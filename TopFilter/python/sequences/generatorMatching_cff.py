import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *

## ---
##    setup jet parton matching
## ---

## jet to parton matching
matchedLightQJets  = selectedLayer1Jets.clone(src = 'selectedLayer1Jets',
                                              cut = 'abs(partonFlavour()) < 5'
                                              )
matchedBottomJets  = selectedLayer1Jets.clone(src = 'selectedLayer1Jets',
                                              cut = 'abs(partonFlavour()) = 5'
                                              )
matchedCharmJets   = selectedLayer1Jets.clone(src = 'selectedLayer1Jets',
                                              cut = 'abs(partonFlavour()) = 4'
                                              )
matchedUdsJets     = selectedLayer1Jets.clone(src = 'selectedLayer1Jets',
                                              cut = 'abs(partonFlavour()) < 4'
                                              )

## four sets of differently matched jet collections
## jets are matched to parton level
matchJetsToPartons = cms.Sequence(matchedLightQJets +
                                  matchedBottomJets +
                                  matchedCharmJets  +
                                  matchedUdsJets
                                  )

## muon matching to generator level
matchedMuons         = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                                 cut = 'genLepton.isNull = 0 &'
                                                       'abs(genLepton.pdgId) = 13 &'
                                                 )
matchedIsolatedMuons = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
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
