import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

## ---
##    setup muon quality studies
## ---

## getting started
combinedMuons = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                          cut = 'combinedMuon.isNull = 0'
                                          )
centralMuons  = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                          cut = 'combinedMuon.isNull = 0 &'
                                                'abs(eta) < 2.1'
                                          )
goodMuons     = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                          cut = 'combinedMuon.isNull = 0 &'
                                                'abs(eta) < 2.1 & pt > 20.'
                                          )

## a kinematically well defined global muon,
## with some chance to pass the std triggers
selectGoodMuons = cms.Sequence(combinedMuons *
                               centralMuons
                               )
                               
## check tracker related muon qualities
validHits     = selectedLayer1Muons.clone(src = 'goodMuons',
                                          cut = 'track.numberOfValidHits >= 11'
                                          )
chi2Fit       = selectedLayer1Muons.clone(src = 'goodMuons',
                                          cut = 'combinedMuon.normalizedChi2 < 10.0'
                                          )
trackSig      = selectedLayer1Muons.clone(src = 'goodMuons',
                                          cut = 'abs(track.d0) < 0.2'
                                          )
trackMuons    = selectedLayer1Muons.clone(src = 'goodMuons',
                                          cut = 'track.numberOfValidHits >= 11 &'
                                                'combinedMuon.normalizedChi2 < 10.0 &'
                                                'abs(track.d0) < 0.2'
                                          )

## a goodMuon with good tracker quality
selectTrackMuons = cms.Sequence(goodMuons *
                                validHits *
                                chi2Fit   *
                                trackSig
                                )

## check for well behaved MIP qualities in
## both calorimeters
ecalDep       = selectedLayer1Muons.clone(src = 'trackMuons',
                                          cut = 'ecalIsoDeposit.candEnergy < 4'
                                          )
hcalDep       = selectedLayer1Muons.clone(src = 'trackMuons',
                                          cut = 'hcalIsoDeposit.candEnergy < 6'
                                          )
goldenMuons   = selectedLayer1Muons.clone(src = 'trackMuons',
                                          cut = 'ecalIsoDeposit.candEnergy < 4 &'
                                                'hcalIsoDeposit.candEnergy < 6'
                                          )
## a trackMuon withgood MIP characteristics
## in both calorimeters
selectGoldenMuons = cms.Sequence(trackMuons *
                                 ecalDep    *
                                 hcalDep
                                 )

## check for isolation
trackIsoMuons = selectedLayer1Muons.clone(src = 'goldenMuons',
                                          cut = 'trackIso < 1.'
                                        )
caloIsoMuons  = selectedLayer1Muons.clone(src = 'goldenMuons',
                                          cut = 'caloIso  < 5.'
                                        )
relIsoMuons   = selectedLayer1Muons.clone(src = 'goldenMuons',
                                          cut = '(trackIso+caloIso)/pt < 0.05'
                                          )

## a goodMuons which are isolated
selectIsolatedMuons = cms.Sequence(goldenMuons   *
                                   caloIsoMuons  *
                                   trackIsoMuons *
                                   relIsoMuons
                                   )
