import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## jet selector for distance filter input collection
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## muon jet distance filter
from TopAnalysis.TopFilter.filters.MuonJetOverlapSelector_cfi import *


## create collection for cut on distance to muon
from TopAnalysis.TopFilter.sequences.jetSelection_cff import goodJets
vetoJets = goodJets.clone()

## create helper collection with jet-distance filter only
dRMuons = checkJetOverlapMuons.clone(muons = "selectedPatMuons",
                                     jets =  "vetoJets" ,
                                     deltaR  = cms.double(0.3),
                                     overlap = cms.bool(False)
                                     )
## ---
##    set up muon quality studies
## ---

## getting started
standAloneMuons = selectedPatMuons.clone(src = 'selectedPatMuons',
                                         cut = 'standAloneMuon.isNull = 0'
                                         )
## check if Global Muon
combinedMuons   = selectedPatMuons.clone(src = 'selectedPatMuons',
                                         cut = 'combinedMuon.isNull = 0'
                                         )
## check muon kinematics
triggerMuons    = selectedPatMuons.clone(src = 'combinedMuons',
                                         cut = 'abs(eta) < 2.5 & pt > 10.'
                                         )

## check tracker related muon qualities: isGlobalMuonPromptTight? & Tracker Muon & impact parameter
trackMuons = selectedPatMuons.clone(src = 'triggerMuons',
                                    cut = 'isTrackerMuon() =1 &'
                                          'innerTrack.numberOfValidHits >= 11 &'
                                          'globalTrack.normalizedChi2 < 10.0  &'
                                          'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                          'abs(dB)<0.02'
                                    )
## restrict kinematic range
goodMuons    = selectedPatMuons.clone(src = 'trackMuons',
                                      cut = 'abs(eta) < 2.1 & pt > 20.'
                                      )



## check for good isolation concerning surrounding jets (MIP-qualities)
goldenMuons = checkJetOverlapMuons.clone(muons = "goodMuons",
                                         jets =  "vetoJets" ,
                                         deltaR  = cms.double(0.3),
                                         overlap = cms.bool(False)
                                         )

## check muon isolation (combined relative) -> final Muon Collection
tightMuons     = selectedPatMuons.clone(src = 'goldenMuons',
                                       cut = '(trackIso+caloIso)/pt < 0.05 '
                                       )

## N-1 collections
noDRMuons     = selectedPatMuons.clone(src = 'selectedPatMuons',
                                       cut = 'pt > 20. & abs(eta) < 2.1 &'
                                             'combinedMuon.isNull = 0 &'
                                             'isTrackerMuon() =1 &'
                                             '(trackIso+caloIso)/pt < 0.05 &'
                                             'innerTrack.numberOfValidHits >= 11 &'
                                             'globalTrack.normalizedChi2 < 10.0 &'
                                             'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                             'abs(dB)<0.02'
                                       )

noPtMuons     = selectedPatMuons.clone(src = 'dRMuons',
                                       cut = 'abs(eta) < 2.1 &'
                                             'combinedMuon.isNull = 0 &'
                                             'isTrackerMuon() =1 &'
                                             '(trackIso+caloIso)/pt < 0.05 &'
                                             'innerTrack.numberOfValidHits >= 11 &'
                                             'globalTrack.normalizedChi2 < 10.0 &'
                                             'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                             'abs(dB)<0.02'
                                       )
noEtaMuons     = selectedPatMuons.clone(src = 'dRMuons',
                                        cut = 'pt > 20. &'
                                              'combinedMuon.isNull = 0 &'
                                              'isTrackerMuon() =1 &'
                                              '(trackIso+caloIso)/pt < 0.05 &'
                                              'innerTrack.numberOfValidHits >= 11 &'
                                              'globalTrack.normalizedChi2 < 10.0 &'
                                              'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                              'abs(dB)<0.02'
                                       )

noIsoMuons     = selectedPatMuons.clone(src = 'dRMuons',
                                        cut = 'pt > 20. & abs(eta) < 2.1 &'
                                              'combinedMuon.isNull = 0 &'
                                              'isTrackerMuon() =1 &'                                            
                                              'innerTrack.numberOfValidHits >= 11 &'
                                              'globalTrack.normalizedChi2 < 10.0 &'
                                              'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                              'abs(dB)<0.02'
                                        )
noTrkHitsMuons     = selectedPatMuons.clone(src = 'dRMuons',
                                            cut = 'pt > 20. & abs(eta) < 2.1 &'
                                                  'combinedMuon.isNull = 0 &'
                                                  'isTrackerMuon() =1 &'
                                                  '(trackIso+caloIso)/pt < 0.05 &'
                                                  'globalTrack.normalizedChi2 < 10.0 &'
                                                  'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                                  'abs(dB)<0.02'
                                            )
noChi2Muons     = selectedPatMuons.clone(src = 'dRMuons',
                                         cut = 'pt > 20. & abs(eta) < 2.1 &'
                                               'combinedMuon.isNull = 0 &'
                                               'isTrackerMuon() =1 &'
                                               '(trackIso+caloIso)/pt < 0.05 &'
                                               'innerTrack.numberOfValidHits >= 11 &'
                                               'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                               'abs(dB)<0.02'
                                         )
noDbMuons     = selectedPatMuons.clone(src = 'dRMuons',
                                       cut = 'pt > 20. & abs(eta) < 2.1 &'
                                             'combinedMuon.isNull = 0 &'
                                             'isTrackerMuon() =1 &'
                                             '(trackIso+caloIso)/pt < 0.05 &'
                                             'innerTrack.numberOfValidHits >= 11 &'
                                             'globalTrack.normalizedChi2 < 10.0 &'
                                             'globalTrack.hitPattern.numberOfValidMuonHits>0 '                              
                                       )

## N-1 Collections
selectNMinusOneMuons = cms.Sequence(noDbMuons        *
                                    noChi2Muons      *
                                    noTrkHitsMuons   *
                                    noIsoMuons       *
                                    noEtaMuons       *
                                    noPtMuons        *
                                    noDRMuons
                                    )
