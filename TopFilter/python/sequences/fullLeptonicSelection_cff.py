import FWCore.ParameterSet.Config as cms

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## electron selector
from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *

## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
## electron count filter
from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *

#-------------------------------------------------
# cleaning
#-------------------------------------------------

from PhysicsTools.PatAlgos.cleaningLayer1.cleanPatCandidates_cff import *

## Electron cleaning against muons

cleanPatElectrons.src = "selectedPatElectrons"

cleanPatElectrons.checkOverlaps.muons.src = 'fullySelectedPatMuons'
cleanPatElectrons.checkOverlaps.muons.preselection = cms.string( 'isGlobalMuon'
                                                                 '| isTrackerMuon'
                                                                 )
cleanPatElectrons.checkOverlaps.muons.deltaR = 0.1
cleanPatElectrons.checkOverlaps.muons.requireNoOverlaps = True

## Jet cleaning against electrons & muons

cleanPatJets.src = "selectedPatJets"
#cleanPatJets.src = "selectedPatJets"

cleanPatJets.checkOverlaps.muons.src = 'selectedPatMuons'
cleanPatJets.checkOverlaps.muons.preselection = cms.string( 'isTrackerMuon'
                                                            '& isGlobalMuon'
                                                            '& abs(eta) < 2.4'
                                                            '& pt > 20.'
                                                            '& globalTrack.hitPattern.numberOfValidTrackerHits > 10'
                                                            '& globalTrack.hitPattern.numberOfValidMuonHits    >  0'
                                                            '& abs(dB) < 0.02'
                                                            '& combinedMuon.normalizedChi2 < 10.'
                                                            '& (trackIso+caloIso)/pt < 0.15'
                                                            )

cleanPatJets.checkOverlaps.muons.deltaR = 0.4
cleanPatJets.checkOverlaps.muons.requireNoOverlaps = True

cleanPatJets.checkOverlaps.electrons.src = 'cleanPatElectrons'
cleanPatJets.checkOverlaps.electrons.preselection = cms.string( 'abs(eta) < 2.5 '
                                                                '& pt > 20. '
                                                                '& superCluster.energy > 15.'
                                                                '& abs(dB) < 0.04'
                                                                '& test_bit(electronID("simpleEleId90cIso"), 0) ' #id
                                                                #'& test_bit(electronID(\"simpleEleId90cIso\"), 2) ' #cr

                                                                #3x Conversion Rejection
                                                                ' & abs(convDcot) > 0.02 '
                                                                ' & abs(convDist) > 0.02 '
                                                                ' & gsfTrack.trackerExpectedHitsInner.numberOfLostHits < 2 '

                                                                #'& ( (electronID(\"simpleEleId90cIso\") = 5.)'
                                                                #'|   (electronID(\"simpleEleId90cIso\") = 7.) )'
                                                                '& ( ( (abs(superCluster.eta) > 1.479) & (dr03TkSumPt()+dr03EcalRecHitSumEt()+dr03HcalTowerSumEt())/et < 0.15)'
                                                                '   |( (abs(superCluster.eta) < 1.479) & (dr03TkSumPt()+max(0.,dr03EcalRecHitSumEt()-1.)+dr03HcalTowerSumEt())/et < 0.15 )'
                                                                '  )'
                                                                )

cleanPatJets.checkOverlaps.electrons.deltaR = 0.4
cleanPatJets.checkOverlaps.electrons.requireNoOverlaps = True

#-------------------------------------------------
# muon selection
#-------------------------------------------------

## Build Collections

## muons reconstructed as track muon
trackerMuons = selectedPatMuons.clone( src = 'fullySelectedPatMuons',
                                       cut = 'isTrackerMuon'
                                       )

## muons reconstructed globally
globalMuons = selectedPatMuons.clone( src = 'trackerMuons',
                                      cut = 'isGlobalMuon'
                                      )
## muons in tracker range
tightMuons = selectedPatMuons.clone( src = 'globalMuons',
                                     cut = 'abs(eta) < 2.4'
                                     )

## pt cut
hardMuons = selectedPatMuons.clone( src = 'tightMuons',
                                    cut = 'pt > 20.'
                                    )

## n_hits
goodTrackMuons = selectedPatMuons.clone( src = 'hardMuons',
                                         cut = 'globalTrack.hitPattern.numberOfValidTrackerHits > 10'
                                               '& globalTrack.hitPattern.numberOfValidMuonHits  > 0'
                                         )

## transverse impact parameter
goodD0Muons = selectedPatMuons.clone( src = 'goodTrackMuons',
                                      cut = 'abs(dB) < 0.02'
                                      )

## global fit
goodFitMuons = selectedPatMuons.clone( src = 'goodD0Muons',
                                       cut = 'combinedMuon.normalizedChi2 < 10.'
                                       )

## isolation cut
isolatedMuons = selectedPatMuons.clone( src = 'goodFitMuons',
                                        cut = '(trackIso+caloIso)/pt < 0.15'
                                        )

## Count Filters
tightMuonSelection     = countPatMuons.clone(src = 'tightMuons',     minNumber = 1)
trackerMuonSelection   = countPatMuons.clone(src = 'trackerMuons',   minNumber = 1)
globalMuonSelection    = countPatMuons.clone(src = 'globalMuons',    minNumber = 1)
hardMuonSelection      = countPatMuons.clone(src = 'hardMuons',      minNumber = 1)
goodTrackMuonSelection = countPatMuons.clone(src = 'goodTrackMuons', minNumber = 1)
goodD0MuonSelection    = countPatMuons.clone(src = 'goodD0Muons',    minNumber = 1)
goodFitMuonSelection   = countPatMuons.clone(src = 'goodFitMuons',   minNumber = 1)
isolatedMuonSelection  = countPatMuons.clone(src = 'isolatedMuons',  minNumber = 1)
onlyOneMuonSelection   = countPatMuons.clone(src = 'isolatedMuons',  minNumber = 1, maxNumber = 1)

#-------------------------------------------------
# electron selection
#-------------------------------------------------

#from TopAnalysis.TopFilter.filters.ElectronCRFunctorFilter_cfi import *

## Build Collections

# Select I.D. only  -->  ( 1 || 3 || 5 || 7 )
#goodIdElectrons = selectedPatElectrons.clone( src = 'cleanPatElectrons',
                                              #cut = 'test_bit(electronID("simpleEleId90cIso"), 0)'
                                              ##cut = '(electronID(\"simpleEleId90cIso\")   = 1.)'
                                                    ##'| (electronID(\"simpleEleId90cIso\") = 3.)'
                                                    ##'| (electronID(\"simpleEleId90cIso\") = 5.)'
                                                    ##'| (electronID(\"simpleEleId90cIso\") = 7.)'
                                              #)

#goodIdElectrons = fullySelectedElectronsCiC.clone()

#goodIdElectrons = selectedPatElectrons.clone( src = 'cleanPatElectrons',
#                                              cut = '( (  (superCluster.eta > 1.479)'
#                                                    '   & (hadronicOverEm < 0.05)'
#                                                    '   & (deltaPhiSuperClusterTrackAtVtx < 0.7)'
#                                                    #'   & (deltaEtaSuperClusterTrackAtVtx < 0.009)'
#                                                    '   & (sigmaIetaIeta < 0.03) )'
#                                                    '| (  (superCluster.eta < 1.479)'
#                                                    '   & (hadronicOverEm < 0.12)'
#                                                    '   & (deltaPhiSuperClusterTrackAtVtx < 0.8)'
#                                                    '   & (deltaEtaSuperClusterTrackAtVtx < 0.007)'
#                                                    '   & (sigmaIetaIeta < 0.01) ) )'
#                                              )

## Electron Conversion Rejection selection
#goodCRElectrons.elecs = cms.InputTag("goodIdElectrons")

goodCRElectrons = selectedPatElectrons.clone( src = 'fullySelectedPatElectronsCiC',
                                              cut = 'abs(convDcot) > 0.02 '
					            ' & abs(convDist) > 0.02'
						    ' & gsfTrack.trackerExpectedHitsInner.numberOfLostHits < 2',
                                               )

centralElectrons = selectedPatElectrons.clone( src = 'goodCRElectrons',
                                               cut = 'abs(eta) < 2.5'
                                               )

highPtElectrons = selectedPatElectrons.clone( src = 'centralElectrons',
                                              cut = 'pt > 20.'
                                              )

goodSCElectrons = selectedPatElectrons.clone( src = 'highPtElectrons',
                                              cut = 'superCluster.energy > 15.'
                                              )

goodD0Electrons = selectedPatElectrons.clone( src = 'goodSCElectrons',
                                              cut = 'abs(dB) < 0.04'
                                              )

isolatedElectrons = selectedPatElectrons.clone( src = 'goodD0Electrons',
                                                cut = '(   (abs(superCluster.eta) > 1.479) & (dr03TkSumPt()+dr03EcalRecHitSumEt()+dr03HcalTowerSumEt())/et < 0.15 )'
                                                      '| ( (abs(superCluster.eta) < 1.479) & (dr03TkSumPt()+max(0.,dr03EcalRecHitSumEt()-1.)+dr03HcalTowerSumEt())/et < 0.15 )'
                                                )

## exact one very tight selected tag electron

#goodIdElectronSelection   = countPatElectrons.clone(src = 'goodIdElectrons',   minNumber = 1)
goodCRElectronSelection   = countPatElectrons.clone(src = 'goodCRElectrons',   minNumber = 1)
centralElectronSelection  = countPatElectrons.clone(src = 'centralElectrons',  minNumber = 1)
highPtElectronSelection   = countPatElectrons.clone(src = 'highPtElectrons',   minNumber = 1)
goodSCElectronSelection   = countPatElectrons.clone(src = 'goodSCElectrons',   minNumber = 1)
goodD0ElectronSelection   = countPatElectrons.clone(src = 'goodD0Electrons',   minNumber = 1)
isolatedElectronSelection = countPatElectrons.clone(src = 'isolatedElectrons', minNumber = 1)
onlyOneElectronSelection  = countPatElectrons.clone(src = 'isolatedElectrons', minNumber = 1, maxNumber = 1)

#-------------------------------------------------
# jet selection
#-------------------------------------------------

from TopAnalysis.TopFilter.filters.JetIdFunctorFilter_cfi import *

## Build Collections

## jet PF ID selection

#selectedPatJets.src = cms.InputTag("selectedPatJets")

goodIdJets.jets    = cms.InputTag("selectedPatJets")
goodIdJets.jetType = cms.string('PF')
goodIdJets.version = cms.string('FIRSTDATA')
goodIdJets.quality = cms.string('LOOSE')

#goodIdJetsPF = selectedPatJets.clone( src = 'cleanPatJets',
#                                      cut = '( (  (abs(eta) > 2.4)'
#                                            '   & (neutralHadronEnergyFraction < 0.99)'
#                                            '   & (neutralEmEnergyFraction     < 0.99)'
#                                            '   & (nConstituents > 1) )'
#                                            '| (  (abs(eta) < 2.4)'
#                                            '   & (neutralHadronEnergyFraction < 0.99)'
#                                            '   & (neutralEmEnergyFraction     < 0.99)'
#                                            '   & (nConstituents > 1)'
#                                            '   & (chargedEmEnergyFraction     < 0.99)'
#                                            '   & (chargedHadronEnergyFraction > 0.)'
#                                            '   & (chargedMultiplicity > 0) ) )'
#                                      )

## thight jet selection

tightJets = selectedPatJets.clone(src = 'selectedPatJets',
                                  cut = 'abs(eta) < 2.5'
                                  )

## hard jet selection
hardJets = selectedPatJets.clone( src = 'tightJets',
                                  cut = 'pt > 30.'
                                  )

## check for different btag properties
trackCountingHighEffBJetsLoose = selectedPatJets.clone( src = 'hardJets',
                                                   cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 1.7'
                                                   #cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 3.3' medium wp
                                                   )

simpleSecondaryVertexBJets = selectedPatJets.clone( src = 'hardJets',
                                                    cut = 'bDiscriminator(\"simpleSecondaryVertexHighEffBJetTags\") > 1.74'
                                                    )

## Count Filters
#goodIdJetPFSelection  = countPatJets.clone(src = 'goodIdJets',               minNumber = 1)
tightJetSelection     = countPatJets.clone(src = 'tightJets',                  minNumber = 1)
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

## Count Filter
metSelection = cms.EDFilter("PATCandViewCountFilter",
                            minNumber = cms.uint32(1),
                            maxNumber = cms.uint32(999),
                            src = cms.InputTag("highMETs")
                            )

#-------------------------------------------------
# sequences
#-------------------------------------------------

#applyCleaning = cms.Sequence( cleanPatCandidates *
                              #goodIdElectrons *
                              #goodIdJets
                              #)

oneHardMuonSelection = cms.Sequence( trackerMuons *
                                     trackerMuonSelection *
                                     globalMuons *
                                     globalMuonSelection *
                                     tightMuons *
                                     tightMuonSelection *
                                     hardMuons *
                                     hardMuonSelection
                                     )

requireOneMuonAllCutsButIso = cms.Sequence(
        oneHardMuonSelection *
        goodTrackMuons *
        goodTrackMuonSelection *
        goodD0Muons *
        goodD0MuonSelection *
        goodFitMuons *
        goodFitMuonSelection
)

oneIsolatedMuonSelection = cms.Sequence(
                                         isolatedMuons *
                                         isolatedMuonSelection
                                         )

requireOneElectronAllCutsButIso = cms.Sequence(
    #goodIdElectronSelection *
    goodCRElectrons *
    goodCRElectronSelection *
    centralElectrons *
    centralElectronSelection *
    highPtElectrons *
    highPtElectronSelection *
    goodSCElectrons *
    goodSCElectronSelection *
    goodD0Electrons *
    goodD0ElectronSelection
)

oneIsolatedElectronSelection = cms.Sequence(
                                             isolatedElectrons *
                                             isolatedElectronSelection
                                             )

leptonVetoSelection = cms.Sequence( onlyOneMuonSelection *
                                    onlyOneElectronSelection
                                    )

buildJets = cms.Sequence( #goodIdJetPFSelection *
                                  goodIdJets *
                                  tightJets *
                                  tightJetSelection *
                                  hardJets)

onePFJetSelection = cms.Sequence(oneHardJetPFSelection)

twoPFJetSelection = cms.Sequence( twoHardJetPFSelection )

pfMETSelection    = cms.Sequence( highMETs *
                                  metSelection
                                  )

bTagSelection     = cms.Sequence( trackCountingHighEffBJetsLoose *
                                  bJetTCHSelection
                                  #twobJetTCHSelection
                                  #simpleSecondaryVertexBJets *
                                  #bJetSSVSelection
                                  )
