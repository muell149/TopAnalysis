import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *

## ---
##    setup jet quality studies
## ---

## getting started
centralJets  = selectedLayer1Muons.clone(src = 'selectedLayer1Jets',
                                         cut = 'abs(eta) < 2.4'
                                         )
reliableJets = selectedLayer1Muons.clone(src = 'selectedLayer1Jets',
                                         cut = 'abs(eta) < 2.4 & pt > 30.'
                                         )
goodJets     = selectedLayer1Muons.clone(src = 'selectedLayer1Jets',
                                         cut = 'abs(eta) < 2.4 & pt > 30. &'
                                               '0.05 < emEnergyFraction   & '
                                               '0.95 > emEnergyFraction'
                                         )

## a kinematically well defined jet with
## reliable calibration and a robust rej
## of photons, electrons and prompt pi0's
selectGoodMuons = cms.Sequence(centralJets *
                               reliableJets
                               )

                               
## check for different btag properties
trackCountingHighPurBJets     = selectedLayer1Muons.clone(src = 'goodJets',
                                                          cut = 'bDiscriminator(\"trackCountingHighPurBJetTags\") > 3.0'
                                                          )
trackCountingHighEffBJets     = selectedLayer1Muons.clone(src = 'goodJets',
                                                          cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 3.0'
                                                          )
simpleSecondaryVertexBJets    = selectedLayer1Muons.clone(src = 'goodJets',
                                                          cut = 'bDiscriminator(\"simpleSecondaryVertexBJetTags\") > 3.0'
                                                          )
simpleSecondaryVertexNegBJets = selectedLayer1Muons.clone(src = 'goodJets',
                                                          cut = 'bDiscriminator(\"simpleSecondaryVertexNegativeBJetTags\") > 3.0'
                                                          )

## a goodJet fulfilling different btag
## criteria
selectTrackMuons = cms.Sequence(goodJets *
                                trackCountingHighPurBJets  *
                                trackCountingHighEffBJets  *
                                simpleSecondaryVertexBJets *
                                simpleSecondaryVertexNegBJets
                                )
