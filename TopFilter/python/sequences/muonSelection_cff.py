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

from TopAnalysis.TopFilter.sequences.MuonVertexDistanceSelector_cfi import *

vertexSelectedMuons2012 = vertexSelectedMuons.clone(cutValue = 0.5)

## create helper collection with jet-distance filter only
#dRMuons = checkJetOverlapMuons.clone(muons = "vertexSelectedMuons2012",
                                     #jets =  "vetoJets" ,
                                     #deltaR  = cms.double(0.3),
                                     #overlap = cms.bool(False)
                                     #)
## dR cut REMOVED!!!!!!
dRMuons = vertexSelectedMuons2012.clone(cutValue = 0.5)
## ---
##    set up muon quality studies
## ---

## getting started
standAloneMuons = selectedPatMuons.clone(src = 'selectedPatMuons',
                                         cut = 'standAloneMuon.isNull = 0'
                                         )
## check if Global Muon
combinedMuons   = selectedPatMuons.clone(src = 'selectedPatMuons',
                                         cut = 'isGlobalMuon'
                                         )
## select Muons with high pt
highPtMuons20    = selectedPatMuons.clone(src = 'combinedMuons',
                                        cut = 'pt > 20.'
                                        )
highPtMuons    = selectedPatMuons.clone(src = 'combinedMuons',
                                        cut = 'pt > 30.'
                                        )

## check muon kinematics
kinematicMuons    = selectedPatMuons.clone(src = 'highPtMuons',
                                           cut = 'abs(eta) < 2.1'
                                           )

## check tracker related muon qualities: isGlobalMuonPromptTight? & Tracker Muon & impact parameter
trackMuons = selectedPatMuons.clone(src = 'vertexSelectedMuons2012',
                                    cut = 'isGlobalMuon &'
                                          'isPFMuon &' # new in 2012
                                          'pt > 30. &' # changed wrt reference selection (was 26)
                                          'abs(eta) < 2.1 &'
                                          #'innerTrack.numberOfValidHits >= 11 &' # not in 2012
                                          'globalTrack.normalizedChi2 < 10.0  &'
                                          'innerTrack.hitPattern.trackerLayersWithMeasurement>5 &' # new in 2012
                                          'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                          'abs(dB)<0.02 &' # changed wrt referense selection (ref is 0.2)
                                          'innerTrack.hitPattern.numberOfValidPixelHits>=1 &' # changed in 2012 (was pixelLayersWithMeasurement)
                                          'numberOfMatchedStations>1' # changed in 2012 (was numberOfMatches)
                                    )

## check for good isolation concerning surrounding jets (MIP-qualities)
#goldenMuons = checkJetOverlapMuons.clone(muons = "trackMuons",
                                         #jets =  "vetoJets" ,
                                         #deltaR  = cms.double(0.3),
                                         #overlap = cms.bool(False)
                                         #)
## dR cut REMOVED!!!!!!
goldenMuons = trackMuons.clone()

## check muon isolation (combined relative) -> final Muon Collection
tightMuons     = selectedPatMuons.clone(src = 'goldenMuons',
                                        cut = '(chargedHadronIso+max((neutralHadronIso+photonIso-0.5*puChargedHadronIso),0.0))/pt < 0.12' # changed in 2012
                                       )

## N-1 collections
noDRMuons     = selectedPatMuons.clone(src = 'vertexSelectedMuons2012',
                                       cut = 'pt > 30. & abs(eta) < 2.1 &'
                                             'combinedMuon.isNull = 0 &'
                                             'isTrackerMuon() =1 &'
                                             '(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125&'
                                             #'(trackIso+caloIso)/pt < 0.05 &'
                                             'innerTrack.numberOfValidHits >= 11 &'
                                             'globalTrack.normalizedChi2 < 10.0 &'
                                             'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                             'abs(dB)<0.02 &'
                                             'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                             'numberOfMatches>1'
                                       )

noPtMuons     = selectedPatMuons.clone(src = 'dRMuons',
                                       cut = 'abs(eta) < 2.1 &'
                                             'combinedMuon.isNull = 0 &'
                                             'isTrackerMuon() =1 &'
                                             '(trackIso+caloIso)/pt < 0.05 &'
                                             #'(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125&'
                                             'innerTrack.numberOfValidHits >= 11 &'
                                             'globalTrack.normalizedChi2 < 10.0 &'
                                             'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                             'abs(dB)<0.02 &'
                                             'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                             'numberOfMatches>1'
                                       )
noEtaMuons     = selectedPatMuons.clone(src = 'dRMuons',
                                        cut = 'pt > 30. &'
                                              'combinedMuon.isNull = 0 &'
                                              'isTrackerMuon() =1 &'
                                              '(trackIso+caloIso)/pt < 0.05 &'
                                              #'(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125&'
                                              'innerTrack.numberOfValidHits >= 11 &'
                                              'globalTrack.normalizedChi2 < 10.0 &'
                                              'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                              'abs(dB)<0.02 &'
                                              'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                              'numberOfMatches>1'
                                       )
noKinMuons     = selectedPatMuons.clone(src = 'dRMuons',
                                        cut = 'combinedMuon.isNull = 0 &'
                                              'isTrackerMuon() =1 &'
                                              '(trackIso+caloIso)/pt < 0.05 &'
                                              #'(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125&'
                                              'innerTrack.numberOfValidHits >= 11 &'
                                              'globalTrack.normalizedChi2 < 10.0 &'
                                              'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                              'abs(dB)<0.02 &'
                                              'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                              'numberOfMatches>1'
                                       )

noIsoMuons     = selectedPatMuons.clone(src = 'dRMuons',
                                        cut = 'pt > 30. & abs(eta) < 2.1 &'
                                              'combinedMuon.isNull = 0 &'
                                              'isTrackerMuon() =1 &'                                            
                                              'innerTrack.numberOfValidHits >= 11 &'
                                              'globalTrack.normalizedChi2 < 10.0 &'
                                              'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                              'abs(dB)<0.02 &'
                                              'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                              'numberOfMatches>1'
                                        )
noTrkHitsMuons     = selectedPatMuons.clone(src = 'dRMuons',
                                            cut = 'pt > 30. & abs(eta) < 2.1 &'
                                                  'combinedMuon.isNull = 0 &'
                                                  'isTrackerMuon() =1 &'
                                                  #'(trackIso+caloIso)/pt < 0.05 &'
                                                  '(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125&'
                                                  'globalTrack.normalizedChi2 < 10.0 &'
                                                  'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                                  'abs(dB)<0.02 &'
                                                  'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                                  'numberOfMatches>1'
                                            )
noChi2Muons     = selectedPatMuons.clone(src = 'dRMuons',
                                         cut = 'pt > 30. & abs(eta) < 2.1 &'
                                               'combinedMuon.isNull = 0 &'
                                               'isTrackerMuon() =1 &'
                                               #'(trackIso+caloIso)/pt < 0.05 &'
                                               '(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125&'
                                               'innerTrack.numberOfValidHits >= 11 &'
                                               'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                               'abs(dB)<0.02 &'
                                               'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                               'numberOfMatches>1'
                                         )
noDbMuons = selectedPatMuons.clone(src = 'vertexSelectedMuons2012',
                                   cut = 'isGlobalMuon &'
                                         'isPFMuon &'
                                         'pt > 30. &'
                                         'abs(eta) < 2.1 &'
                                         'globalTrack.normalizedChi2 < 10.0 &'
                                         'innerTrack.hitPattern.trackerLayersWithMeasurement>5 &'
                                         'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                         'innerTrack.hitPattern.numberOfValidPixelHits>=1 &'
                                         'numberOfMatchedStations>1 &'
                                         '(chargedHadronIso+max((neutralHadronIso+photonIso-0.5*puChargedHadronIso),0.0))/pt < 0.12'
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
