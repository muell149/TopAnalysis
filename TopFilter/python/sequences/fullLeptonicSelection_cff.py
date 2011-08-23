import FWCore.ParameterSet.Config as cms

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *

## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *

#-------------------------------------------------
# jet selection
#-------------------------------------------------

from TopAnalysis.TopFilter.filters.JetIdFunctorFilter_cfi import *

## Build Collections

goodIdJets.jets    = cms.InputTag("selectedPatJets")
goodIdJets.jetType = cms.string('PF')
goodIdJets.version = cms.string('FIRSTDATA')
goodIdJets.quality = cms.string('LOOSE')

#goodIdJetsPF = selectedPatJets.clone( src = 'selectedPatJets',
#                                     cut = '( (  (abs(eta) > 2.4)'
#                                           '   & (neutralHadronEnergyFraction < 0.99)'
#                                           '   & (neutralEmEnergyFraction     < 0.99)'
#                                           '   & (nConstituents > 1) )'
#                                           '| (  (abs(eta) < 2.4)'
#                                           '   & (neutralHadronEnergyFraction < 0.99)'
#                                           '   & (neutralEmEnergyFraction     < 0.99)'
#                                           '   & (nConstituents > 1)'
#                                           '   & (chargedEmEnergyFraction     < 0.99)'
#                                           '   & (chargedHadronEnergyFraction > 0.)'
#                                           '   & (chargedMultiplicity > 0) ) )'
#                                     )

hardJets = selectedPatJets.clone(src = 'goodIdJets', cut = 'pt > 30. & abs(eta) < 2.4')

## check for different btag properties
trackCountingHighEffBJetsLoose = selectedPatJets.clone( src = 'hardJets',
                                                   cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 1.7'
                                                   )
						   
trackCountingHighEffBJetsMedium = selectedPatJets.clone( src = 'hardJets',
                                                   cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 3.3' 
                                                   )						   
						   

simpleSecondaryVertexBJets = selectedPatJets.clone( src = 'hardJets',
                                                    cut = 'bDiscriminator(\"simpleSecondaryVertexHighEffBJetTags\") > 1.74'
                                                    )

## Count Filters
oneHardJetPFSelection = countPatJets.clone(src = 'hardJets',                   minNumber = 1)
twoHardJetPFSelection = countPatJets.clone(src = 'hardJets',                   minNumber = 2)
bJetTCHELSelection    = countPatJets.clone(src = 'trackCountingHighEffBJetsLoose',  minNumber = 1)
bJetTCHEMSelection    = countPatJets.clone(src = 'trackCountingHighEffBJetsMedium',  minNumber = 1)
bJetSSVHEMSelection   = countPatJets.clone(src = 'simpleSecondaryVertexBJets', minNumber = 1)

#-------------------------------------------------
# met selection
#-------------------------------------------------

## met selector
highMETs = cms.EDFilter( "PATMETSelector",
                         src = cms.InputTag("patMETs"),
                         cut = cms.string("et > 30.")
                         )

lowEMuMETs = cms.EDFilter( "PATMETSelector",
                         src = cms.InputTag("patMETs"),
                         cut = cms.string("et > 20.")
                         )

## Count Filter
metSelection = cms.EDFilter("PATCandViewCountFilter",
                            minNumber = cms.uint32(1),
                            maxNumber = cms.uint32(999),
                            src = cms.InputTag("highMETs")
                            )

metSelectionEMu = cms.EDFilter("PATCandViewCountFilter",
                            minNumber = cms.uint32(1),
                            maxNumber = cms.uint32(999),
                            src = cms.InputTag("lowEMuMETs")
                            )

#-------------------------------------------------
# sequences
#-------------------------------------------------

buildJets = cms.Sequence(goodIdJets * hardJets)

onePFJetSelection = cms.Sequence(oneHardJetPFSelection)

twoPFJetSelection = cms.Sequence( twoHardJetPFSelection )

pfMETSelection    = cms.Sequence( highMETs *
                                  metSelection
                                )

pfMETSelectionEMu = cms.Sequence( lowEMuMETs *
                                  metSelectionEMu
                                )

bTagSelectionTCHEL = cms.Sequence( trackCountingHighEffBJetsLoose *
                                   bJetTCHELSelection
                                  )
				  
bTagSelectionTCHEM = cms.Sequence( trackCountingHighEffBJetsMedium *
                                   bJetTCHEMSelection
                                  )
				  
bTagSelectionSSVHEM = cms.Sequence( simpleSecondaryVertexBJets *
                                    bJetSSVHEMSelection
                                  )				  
