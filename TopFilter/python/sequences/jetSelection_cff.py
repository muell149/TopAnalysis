import FWCore.ParameterSet.Config as cms

## muon vertex distance selector for jet cleaning
from TopAnalysis.TopFilter.sequences.MuonVertexDistanceSelector_cfi import *

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import *

## NOTE: For PF2PAT "selectedPatJets" instead of "selectedPatJetsAK5PF" must be used!
## At the moment this is implemented by overwriting it in each cfg file
noOverlapJetsPF = selectedPatJets.clone(src = "selectedPatJetsAK5PF")
#noOverlapJetsPF = cleanPatJets.clone(
   #src = cms.InputTag("selectedPatJetsAK5PF"),

   ## preselection (any string-based cut on pat::Jet)
   #preselection = cms.string(''),

   ## overlap checking configurables
   #checkOverlaps = cms.PSet(
       #muons = cms.PSet(
          #src       = cms.InputTag("vertexSelectedMuons"),
          #algorithm = cms.string("byDeltaR"),
          #preselection        = cms.string('pt > 20. & abs(eta) < 2.1 &'
                                           #'combinedMuon.isNull = 0 &'
                                           #'isTrackerMuon() =1 &'
                                           ##'(trackIso+caloIso)/pt < 0.05 &'
                                           #'(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.125&'
                                           #'innerTrack.numberOfValidHits >= 11 &'
                                           #'globalTrack.normalizedChi2 < 10.0 &'
                                           #'globalTrack.hitPattern.numberOfValidMuonHits>0 &'
                                           #'abs(dB)<0.02 &'
                                           #'innerTrack.hitPattern.pixelLayersWithMeasurement>=1 &'
                                           #'numberOfMatches>1'),
          #deltaR              = cms.double(0.1),
          #checkRecoComponents = cms.bool(False), # don't check if they share some AOD object ref
          #pairCut             = cms.string(""),
          #requireNoOverlaps   = cms.bool(True), # overlaps don't cause the jet to be discared
       #)
   #),
   ## finalCut (any string-based cut on pat::Jet)
   #finalCut = cms.string(''),
#)

## getting started
centralJets  = selectedPatJets.clone(src = 'selectedPatJets',
                                     cut = 'abs(eta) < 2.4'
                                     )
reliableJets = selectedPatJets.clone(src = 'selectedPatJets',
                                     cut = 'abs(eta) < 2.4 & pt > 30.'
                                     )
goodJets     = selectedPatJets.clone(src = 'selectedPatJets',
                                     cut = 'abs(eta) < 2.4 & pt > 30. &'
                                           'emEnergyFraction > 0.01   &'
                                           'jetID.fHPD < 0.98         &'
                                           'jetID.n90Hits > 1'
                                     )
centralJetsPF    = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                         cut = 'abs(eta) < 2.4'
                                         )
centralJetsPF25  = selectedPatJets.clone(src = 'centralJetsPF',
                                         cut = 'pt > 25.'
                                         )
centralJetsPF30  = selectedPatJets.clone(src = 'centralJetsPF',
                                         cut = 'pt > 30.'
                                         )
reliableJetsPF   = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                         cut = 'abs(eta) < 2.4 & pt > 20.'
                                         )
reliableJetsPF25 = selectedPatJets.clone(src = 'reliableJetsPF',
                                         cut = 'pt > 25.'
                                         )
reliableJetsPF30 = selectedPatJets.clone(src = 'reliableJetsPF',
                                         cut = 'pt > 30.'
                                         )
goodJetsPF       = selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                         cut = 'abs(eta) < 2.4 & pt > 20.          &'
                                               'chargedHadronEnergyFraction > 0.0  &'
                                               'neutralHadronEnergyFraction < 0.99 &'
                                               'electronEnergyFraction      < 0.99 &' # was *chargedEmEnergyFraction* which is deprecated
                                               'photonEnergyFraction        < 0.99 &' # was *neutralEmEnergyFraction* which is deprecated
                                               '(chargedHadronMultiplicity + electronMultiplicity + muonMultiplicity) > 0 &' # was *chargedMultiplicity* which is deprecated
                                               'numberOfDaughters > 1' # identical to nConstituents
                                         )
goodJetsPF20     = selectedPatJets.clone(src = 'goodJetsPF')
## currently they are not needed anymore as we are using top projections within PF2PAT
#goodJetsPF20     = selectedPatJets.clone(src = 'noOverlapJetsPF',
#                                         cut = 'abs(eta) < 2.4 & pt > 20.           &'
#                                               'neutralHadronEnergyFraction  < 0.99 &'
#                                               'neutralEmEnergyFraction      < 0.99 &'
#                                               '(chargedHadronEnergyFraction > 0.0  | abs(eta) >= 2.4) &'
#                                               '(chargedEmEnergyFraction     < 0.99 | abs(eta) >= 2.4) &'
#                                               '(chargedMultiplicity         > 0    | abs(eta) >= 2.4) &'
#                                               'numberOfDaughters > 1'
#                                         )
goodJetsPF25     = selectedPatJets.clone(src = 'goodJetsPF20',
                                         cut = 'pt > 25.'
                                         )
goodJetsPF30     = selectedPatJets.clone(src = 'goodJetsPF20',
                                         cut = 'pt > 30.'
                                         )
## N-1 collections
noEtaJets      = selectedPatJets.clone(src = 'selectedPatJets',
                                       cut = 'pt > 30.                  &'
                                             '0.01 < emEnergyFraction   &'
                                             'jetID.fHPD < 0.98         &'
                                             'jetID.n90Hits > 1'
                                       )
noPtJets       = selectedPatJets.clone(src = 'selectedPatJets',
                                       cut = 'abs(eta) < 2.4            &'
                                             '0.01 < emEnergyFraction   &'
                                             'jetID.fHPD < 0.98         &'
                                             'jetID.n90Hits > 1'
                                       )
noEmJets       = selectedPatJets.clone(src = 'selectedPatJets',
                                       cut = 'pt > 30. & abs(eta) < 2.4 &'
                                             'jetID.fHPD < 0.98         &'
                                             'jetID.n90Hits > 1'
                                       )
noN90HitsJets  = selectedPatJets.clone(src = 'selectedPatJets',
                                       cut = 'pt > 30. & abs(eta) < 2.4 &'
                                             '0.01 < emEnergyFraction   &'
                                             'jetID.fHPD < 0.98          '
                                       )
nofHPDJets     = selectedPatJets.clone(src = 'selectedPatJets',
                                       cut = 'pt > 30. & abs(eta) < 2.4 &'
                                             '0.01 < emEnergyFraction   &'
                                             'jetID.n90Hits > 1'                                                                       )

noEtaJetsPF     = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                        cut = 'pt > 20.                           &'
                                              'chargedHadronEnergyFraction > 0.0  &'
                                              'neutralHadronEnergyFraction < 0.99 &'
                                              'chargedEmEnergyFraction     < 0.99 &'
                                              'neutralEmEnergyFraction     < 0.99 &'
                                              'chargedMultiplicity > 0            &'
                                              'nConstituents > 1'
                                          )
noPtJetsPF      = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                        cut = 'abs(eta) < 2.4                     &'
                                              'chargedHadronEnergyFraction > 0.0  &'
                                              'neutralHadronEnergyFraction < 0.99 &'
                                              'chargedEmEnergyFraction     < 0.99 &'
                                              'neutralEmEnergyFraction     < 0.99 &'
                                              'chargedMultiplicity > 0            &'
                                              'nConstituents > 1'
                                        )
noKinJetsPF      = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                         cut = 'chargedHadronEnergyFraction > 0.0  &'
                                               'neutralHadronEnergyFraction < 0.99 &'
                                               'chargedEmEnergyFraction     < 0.99 &'
                                               'neutralEmEnergyFraction     < 0.99 &'
                                               'chargedMultiplicity > 0            &'
                                               'nConstituents > 1'
                                         )
noConstJetsPF   = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                        cut = 'abs(eta) < 2.4 & pt > 20.          &'
                                              'chargedHadronEnergyFraction > 0.0  &'
                                              'neutralHadronEnergyFraction < 0.99 &'
                                              'chargedEmEnergyFraction     < 0.99 &'
                                              'neutralEmEnergyFraction     < 0.99 &'
                                              'chargedMultiplicity > 0'
                                        )
noCEFJetsPF     = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                        cut = 'abs(eta) < 2.4 & pt > 20.          &'
                                              'chargedHadronEnergyFraction > 0.0  &'
                                              'neutralHadronEnergyFraction < 0.99 &'
                                              'neutralEmEnergyFraction     < 0.99 &'
                                              'chargedMultiplicity > 0            &'
                                              'nConstituents > 1'
                                        )
noNHFJetsPF     = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                        cut = 'abs(eta) < 2.4 & pt > 20.          &'
                                              'chargedHadronEnergyFraction > 0.0  &'
                                              'chargedEmEnergyFraction     < 0.99 &'
                                              'neutralEmEnergyFraction     < 0.99 &'
                                              'chargedMultiplicity > 0            &'
                                              'nConstituents > 1'
                                        )
noNEFJetsPF     = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                        cut = 'abs(eta) < 2.4 & pt > 20.          &'
                                              'chargedHadronEnergyFraction > 0.0  &'
                                              'neutralHadronEnergyFraction < 0.99 &'
                                              'chargedEmEnergyFraction     < 0.99 &'
                                              'chargedMultiplicity > 0            &'
                                              'nConstituents > 1'
                                        )
noCHFJetsPF     = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                        cut = 'abs(eta) < 2.4 & pt > 20.          &'
                                              'neutralHadronEnergyFraction < 0.99 &'
                                              'chargedEmEnergyFraction     < 0.99 &'
                                              'neutralEmEnergyFraction     < 0.99 &'
                                              'chargedMultiplicity > 0            &'
                                              'nConstituents > 1'
                                        )
noNCHJetsPF     = selectedPatJets.clone(src = 'noOverlapJetsPF',
                                        cut = 'abs(eta) < 2.4 & pt > 20.          &'
                                              'chargedHadronEnergyFraction > 0.0  &'
                                              'neutralHadronEnergyFraction < 0.99 &'
                                              'chargedEmEnergyFraction     < 0.99 &'
                                              'neutralEmEnergyFraction     < 0.99 &'
                                              'nConstituents > 1'
                                        )

noEtaJetsPF25   = selectedPatJets.clone(src = 'noEtaJetsPF',
                                        cut = 'pt > 25.'
                                        )
noPtJetsPF25    = selectedPatJets.clone(src = 'noPtJetsPF')
noConstJetsPF25 = selectedPatJets.clone(src = 'noConstJetsPF',
                                        cut = 'pt > 25.'
                                        )
noCEFJetsPF25   = selectedPatJets.clone(src = 'noCEFJetsPF',
                                        cut = 'pt > 25.'
                                        )
noNHFJetsPF25   = selectedPatJets.clone(src = 'noNHFJetsPF',
                                        cut = 'pt > 25.'
                                        )
noNEFJetsPF25   = selectedPatJets.clone(src = 'noNEFJetsPF',
                                        cut = 'pt > 25.'
                                        )
noCHFJetsPF25   = selectedPatJets.clone(src = 'noCHFJetsPF',
                                        cut = 'pt > 25.'
                                        )
noNCHJetsPF25   = selectedPatJets.clone(src = 'noNCHJetsPF',
                                        cut = 'pt > 25.'
                                        )

noEtaJetsPF30   = selectedPatJets.clone(src = 'noEtaJetsPF',
                                        cut = 'pt > 30.'
                                        )
noPtJetsPF30    = selectedPatJets.clone(src = 'noPtJetsPF')
noConstJetsPF30 = selectedPatJets.clone(src = 'noConstJetsPF',
                                        cut = 'pt > 30.'
                                        )
noCEFJetsPF30   = selectedPatJets.clone(src = 'noCEFJetsPF',
                                        cut = 'pt > 30.'
                                        )
noNHFJetsPF30   = selectedPatJets.clone(src = 'noNHFJetsPF',
                                        cut = 'pt > 30.'
                                        )
noNEFJetsPF30   = selectedPatJets.clone(src = 'noNEFJetsPF',
                                        cut = 'pt > 30.'
                                        )
noCHFJetsPF30   = selectedPatJets.clone(src = 'noCHFJetsPF',
                                        cut = 'pt > 30.'
                                        )
noNCHJetsPF30   = selectedPatJets.clone(src = 'noNCHJetsPF',
                                        cut = 'pt > 30.'
                                        )

## a kinematically well defined jet with
## reliable calibration and a robust rej
## of photons, electrons and prompt pi0's
selectGoodJets = cms.Sequence(noOverlapJetsPF  *
                              centralJets      *
                              reliableJets     *
                              goodJets         *
                              goodJetsPF       *
                              centralJetsPF    *
                              reliableJetsPF   *
                              goodJetsPF20     *
                              centralJetsPF25  *
                              reliableJetsPF25 *
                              goodJetsPF25     *
                              centralJetsPF30  *
                              reliableJetsPF30 *
                              goodJetsPF30
                              )

## collect the N-1 collections
selectNMinusOneJets = cms.Sequence(noEtaJets       *
                                   noPtJets        *
                                   noEmJets        *
                                   noN90HitsJets   *
                                   nofHPDJets      *
                                   noEtaJetsPF     *
                                   noPtJetsPF      *
                                   noConstJetsPF   *
                                   noCEFJetsPF     *
                                   noNHFJetsPF     *
                                   noNEFJetsPF     *
                                   noCHFJetsPF     *
                                   noNCHJetsPF     *
                                   noEtaJetsPF25   *
                                   noPtJetsPF25    *
                                   noConstJetsPF25 *
                                   noCEFJetsPF25   *
                                   noNHFJetsPF25   *
                                   noNEFJetsPF25   *
                                   noCHFJetsPF25   *
                                   noNCHJetsPF25   *
                                   noEtaJetsPF30   *
                                   noPtJetsPF30    *
                                   noConstJetsPF30 *
                                   noCEFJetsPF30   *
                                   noNHFJetsPF30   *
                                   noNEFJetsPF30   *
                                   noCHFJetsPF30   *
                                   noNCHJetsPF30
                                   )

## check for different btag properties
trackCountingHighPurBJets         = selectedPatJets.clone(src = 'goodJetsPF30',
                                                          cut = 'bDiscriminator(\"trackCountingHighPurBJetTags\") > 1.93'
                                                          )
trackCountingHighEffBJets         = selectedPatJets.clone(src = 'goodJetsPF30',
                                                          cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 3.3'
                                                          )
simpleSecondaryVertexHighEffBJets = selectedPatJets.clone(src = 'goodJetsPF30',
                                                          cut = 'bDiscriminator(\"simpleSecondaryVertexHighEffBJetTags\") > 1.74'
                                                          )
simpleSecondaryVertexHighPurBJets = selectedPatJets.clone(src = 'goodJetsPF30',
                                                          cut = 'bDiscriminator(\"simpleSecondaryVertexHighPurBJetTags\") > 2.0'
                                                          )
simpleSecondaryVertexNegBJets     = selectedPatJets.clone(src = 'goodJetsPF30',
                                                          cut = 'bDiscriminator(\"simpleSecondaryVertexNegativeBJetTags\") > 3.0'
                                                          )
combinedSecondaryVertexBJets      = selectedPatJets.clone(src = 'goodJetsPF30',
                                                          cut = 'bDiscriminator(\"combinedSecondaryVertexBJetTags\") > 0.679'
                                                          )
combinedSecondaryVertexMVABJets   = selectedPatJets.clone(src = 'goodJetsPF30',
                                                          cut = 'bDiscriminator(\"combinedSecondaryVertexMVABJetTags\") > 0.4'
                                                          )
softMuonBJets                     = selectedPatJets.clone(src = 'goodJetsPF30',
                                                          cut = 'bDiscriminator(\"softMuonBJetTags\") > 0.3'
                                                          )

## a goodJet fullfilling different btag
## criteria
selectBTaggedJets = cms.Sequence(goodJets                         *
                                goodJetsPF30                      *
                                trackCountingHighPurBJets         *
                                trackCountingHighEffBJets         *
                                simpleSecondaryVertexHighEffBJets *
                                simpleSecondaryVertexHighPurBJets *
                                simpleSecondaryVertexNegBJets     *
                                combinedSecondaryVertexBJets      *
                                combinedSecondaryVertexMVABJets   *
                                softMuonBJets
                                )

