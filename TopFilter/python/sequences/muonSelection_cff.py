import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

## ---
##    setup muon quality studies
## ---

## getting started
standAloneMuons = selectedPatMuons.clone(src = 'selectedPatMuons',
                                         cut = 'standAloneMuon.isNull = 0'
                                         )
combinedMuons   = selectedPatMuons.clone(src = 'selectedPatMuons',
                                         cut = 'combinedMuon.isNull = 0'
                                         )
triggerMuons    = selectedPatMuons.clone(src = 'selectedPatMuons',
                                         cut = 'combinedMuon.isNull = 0 &'
                                         'abs(eta) < 2.5 & pt > 10.'
                                         )

## a kinematically well defined global muon,
## with some chance to pass the std triggers
selectTriggerMuons = cms.Sequence(combinedMuons *
                                  triggerMuons
                                  )
                               
## check tracker related muon qualities
validHits     = selectedPatMuons.clone(src = 'triggerMuons',
                                       cut = 'track.numberOfValidHits >= 11'
                                       )
chi2Fit       = selectedPatMuons.clone(src = 'triggerMuons',
                                       cut = 'combinedMuon.normalizedChi2 < 10.0'
                                       )
trackSig      = selectedPatMuons.clone(src = 'triggerMuons',
                                       cut = 'abs(dB) < 0.02'
                                       )
trackMuons    = selectedPatMuons.clone(src = 'triggerMuons',
                                       cut = 'track.numberOfValidHits >= 11 &'
                                       'combinedMuon.normalizedChi2 < 10.0 &'
                                       'abs(dB) < 0.02'
                                       )

## a triggerMuon with good tracker quality
selectTrackMuons = cms.Sequence(validHits *
                                chi2Fit   *
                                trackSig  *
                                trackMuons
                                )

## check muon kinematics
centralMuons  = selectedPatMuons.clone(src = 'trackMuons',
                                       cut = 'abs(eta) < 2.1'
                                       )
highptMuons   = selectedPatMuons.clone(src = 'trackMuons',
                                       cut = 'pt > 20.'
                                       )
goodMuons     = selectedPatMuons.clone(src = 'trackMuons',
                                       cut = 'pt > 20. & abs(eta) < 2.1'
                                       )
## a kinematically well defined trackMuon
selectGoodMuons = cms.Sequence(centralMuons *
                               highptMuons  *
                               goodMuons
                               )


## check for well behaved MIP qualities in
## both calorimeters
ecalDep       = selectedPatMuons.clone(src = 'goodMuons',
                                       cut = 'isolationR03.emVetoEt < 4'
                                       )
hcalDep       = selectedPatMuons.clone(src = 'goodMuons',
                                       cut = 'isolationR03.hadVetoEt < 6'
                                       )
goldenMuons   = selectedPatMuons.clone(src = 'goodMuons',
                                       cut = 'isolationR03.emVetoEt < 4 &'
                                       'isolationR03.hadVetoEt < 6'
                                       )
## a goodMuon withgood MIP characteristics
## in both calorimeters
selectGoldenMuons = cms.Sequence(ecalDep    *
                                 hcalDep    *
                                 goldenMuons
                                 )

## check for isolation
trackIsoMuons = selectedPatMuons.clone(src = 'goldenMuons',
                                       cut = 'trackIso < 1.'
                                       )
caloIsoMuons  = selectedPatMuons.clone(src = 'goldenMuons',
                                       cut = 'caloIso  < 5.'
                                       )
relIsoMuons   = selectedPatMuons.clone(src = 'goldenMuons',
                                       cut = '(trackIso+caloIso)/pt < 0.05'
                                       )

## a goldenMuons which are isolated
selectIsolatedMuons = cms.Sequence(caloIsoMuons  *
                                   trackIsoMuons *
                                   relIsoMuons
                                   )
