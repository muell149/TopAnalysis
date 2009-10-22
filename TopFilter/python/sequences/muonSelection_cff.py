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
triggerMuons  = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                          cut = 'combinedMuon.isNull = 0 &'
                                                'abs(eta) < 2.5 & pt > 10.'
                                          )

## a kinematically well defined global muon,
## with some chance to pass the std triggers
selectTriggerMuons = cms.Sequence(combinedMuons *
                                  triggerMuons
                                  )
                               
## check tracker related muon qualities
validHits     = selectedLayer1Muons.clone(src = 'triggerMuons',
                                          cut = 'track.numberOfValidHits >= 11'
                                          )
chi2Fit       = selectedLayer1Muons.clone(src = 'triggerMuons',
                                          cut = 'combinedMuon.normalizedChi2 < 10.0'
                                          )
trackSig      = selectedLayer1Muons.clone(src = 'triggerMuons',
                                          cut = 'abs(track.d0) < 0.2'
                                          )
trackMuons    = selectedLayer1Muons.clone(src = 'triggerMuons',
                                          cut = 'track.numberOfValidHits >= 11 &'
                                                'combinedMuon.normalizedChi2 < 10.0 &'
                                                'abs(track.d0) < 0.2'
                                          )

## a triggerMuon with good tracker quality
selectTrackMuons = cms.Sequence(validHits *
                                chi2Fit   *
                                trackSig  *
                                trackMuons
                                )

## check muon kinematics
centralMuons  = selectedLayer1Muons.clone(src = 'trackMuons',
                                          cut = 'abs(eta) < 2.1'
                                          )
highptMuons   = selectedLayer1Muons.clone(src = 'trackMuons',
                                          cut = 'pt > 20.'
                                          )
goodMuons     = selectedLayer1Muons.clone(src = 'trackMuons',
                                          cut = 'pt > 20. & abs(eta) < 2.1'
                                          )
## a kinematically well defined trackMuon
selectGoodMuons = cms.Sequence(centralMuons *
                               highptMuons  *
                               goodMuons
                               )


## check for well behaved MIP qualities in
## both calorimeters
ecalDep       = selectedLayer1Muons.clone(src = 'goodMuons',
                                          cut = 'ecalIsoDeposit.candEnergy < 4'
                                          )
hcalDep       = selectedLayer1Muons.clone(src = 'goodMuons',
                                          cut = 'hcalIsoDeposit.candEnergy < 6'
                                          )
goldenMuons   = selectedLayer1Muons.clone(src = 'goodMuons',
                                          cut = 'ecalIsoDeposit.candEnergy < 4 &'
                                                'hcalIsoDeposit.candEnergy < 6'
                                          )
## a goodMuon withgood MIP characteristics
## in both calorimeters
selectGoldenMuons = cms.Sequence(ecalDep    *
                                 hcalDep    *
                                 goldenMuons
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

## a goldenMuons which are isolated
selectIsolatedMuons = cms.Sequence(caloIsoMuons  *
                                   trackIsoMuons *
                                   relIsoMuons
                                   )
