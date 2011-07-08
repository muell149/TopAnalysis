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

hardJets = selectedPatJets.clone(src = 'goodIdJets', cut = 'pt > 30. & abs(eta) < 2.5')

## check for different btag properties
trackCountingHighEffBJetsLoose = selectedPatJets.clone( src = 'hardJets',
                                                   cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 1.7'
                                                   #cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 3.3' medium wp
                                                   )

simpleSecondaryVertexBJets = selectedPatJets.clone( src = 'hardJets',
                                                    cut = 'bDiscriminator(\"simpleSecondaryVertexHighEffBJetTags\") > 1.74'
                                                    )

## Count Filters
oneHardJetPFSelection = countPatJets.clone(src = 'hardJets',                   minNumber = 1)
twoHardJetPFSelection = countPatJets.clone(src = 'hardJets',                   minNumber = 2)
bJetTCHSelection      = countPatJets.clone(src = 'trackCountingHighEffBJetsLoose',  minNumber = 1)
twobJetTCHSelection   = countPatJets.clone(src = 'trackCountingHighEffBJetsLoose',  minNumber = 2)
bJetSSVSelection      = countPatJets.clone(src = 'simpleSecondaryVertexBJets', minNumber = 1)

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

bTagSelection     = cms.Sequence( trackCountingHighEffBJetsLoose *
                                  bJetTCHSelection
                                  #twobJetTCHSelection
                                  #simpleSecondaryVertexBJets *
                                  #bJetSSVSelection
                                  )
