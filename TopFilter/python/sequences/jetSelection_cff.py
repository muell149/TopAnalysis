import FWCore.ParameterSet.Config as cms

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *

## ---
##    setup jet quality studies
## ---

## getting started
centralJets  = selectedPatJets.clone(src = 'selectedPatJets',
                                        cut = 'abs(eta) < 2.4'
                                        )
reliableJets = selectedPatJets.clone(src = 'selectedPatJets',
                                        cut = 'abs(eta) < 2.4 & pt > 30.'
                                        )
goodJets     = selectedPatJets.clone(src = 'selectedPatJets',
                                        cut = 'abs(eta) < 2.4 & pt > 30. &'
                                              '0.05 < emEnergyFraction   & '
                                              '0.95 > emEnergyFraction'
                                        )

## a kinematically well defined jet with
## reliable calibration and a robust rej
## of photons, electrons and prompt pi0's
selectGoodJets = cms.Sequence(centralJets *
                              reliableJets
                              )

                               
## check for different btag properties
trackCountingHighPurBJets     = selectedPatJets.clone(src = 'goodJets',
                                                         cut = 'bDiscriminator(\"trackCountingHighPurBJetTags\") > 3.0'
                                                         )
trackCountingHighEffBJets     = selectedPatJets.clone(src = 'goodJets',
                                                         cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 3.0'
                                                         )
simpleSecondaryVertexBJets    = selectedPatJets.clone(src = 'goodJets',
                                                         cut = 'bDiscriminator(\"simpleSecondaryVertexBJetTags\") > 3.0'
                                                         )
simpleSecondaryVertexNegBJets = selectedPatJets.clone(src = 'goodJets',
                                                         cut = 'bDiscriminator(\"simpleSecondaryVertexNegativeBJetTags\") > 3.0'
                                                         )
combinedSecondaryVertexBJets  = selectedPatJets.clone(src = 'goodJets',
                                                         cut = 'bDiscriminator(\"combinedSecondaryVertexBJetTags\") > 0.9'
                                                         )
softMuonBJets                 = selectedPatJets.clone(src = 'goodJets',
                                                         cut = 'bDiscriminator(\"softMuonBJetTags\") > 0.3'
                                                         )

## a goodJet fullfilling different btag
## criteria
selectBTaggedJets = cms.Sequence(goodJets                      *
                                 trackCountingHighPurBJets     *
                                 trackCountingHighEffBJets     *
                                 simpleSecondaryVertexBJets    *
                                 simpleSecondaryVertexNegBJets *
                                 combinedSecondaryVertexBJets  *
                                 softMuonBJets
                                 )
