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

cleanPatElectrons.checkOverlaps.muons.preselection = cms.string( 'isGlobalMuon'
                                                                 '| isTrackerMuon'
                                                                 #'& abs(eta) < 2.4'
                                                                 #'& pt > 20.'
                                                                 #'& track.numberOfValidHits > 10'
                                                                 #'& abs(dB) < 0.02'
                                                                 #'& combinedMuon.normalizedChi2 < 10.0'
                                                                 #'& (trackIso+caloIso)/pt < 0.15'
                                                                 )
cleanPatElectrons.checkOverlaps.muons.deltaR = 0.1
cleanPatElectrons.checkOverlaps.muons.requireNoOverlaps = True

## Jet cleaning against electrons & muons

#cleanPatJets.src = "selectedPatJetsAK5PF"
#cleanPatJets.src = "selectedPatJets"
cleanPatJets.src = cms.InputTag("residualCorrectedJets")

cleanPatJets.checkOverlaps.muons.preselection = cms.string( 'isTrackerMuon'
                                                            '& isGlobalMuon'
                                                            '& abs(eta) < 2.4'
                                                            '& pt > 20.'
                                                            '& track.numberOfValidHits > 10'
                                                            '& globalTrack.hitPattern.numberOfValidMuonHits > 0'

                                                            '& abs(dB) < 0.02'
                                                            '& combinedMuon.normalizedChi2 < 10.0'
                                                            '& (trackIso+caloIso)/pt < 0.15'
                                                            )
cleanPatJets.checkOverlaps.muons.deltaR = 0.4
cleanPatJets.checkOverlaps.muons.requireNoOverlaps = True

cleanPatJets.checkOverlaps.electrons.src = 'cleanPatElectrons'
cleanPatJets.checkOverlaps.electrons.preselection = cms.string( 'abs(eta) < 2.5'
                                                                '& et > 15.'
                                                                '& superCluster.energy > 15.'
                                                                '& abs(dB) < 0.04'
                                                                #'& hcalOverEcal < 0.05'
                                                                '& ( electronID(\"simpleEleId90cIso\") = 5.  '
                                                                '|   electronID(\"simpleEleId90cIso\") = 7. )'
                                                                '& ( ( (abs(superCluster.eta)>1.479) & (dr03TkSumPt()+dr03EcalRecHitSumEt()+dr03HcalTowerSumEt())/max(20.,et) < 0.15)'
                                                                '|   ( (abs(superCluster.eta)<1.479) & (dr03TkSumPt()+max(0.,dr03EcalRecHitSumEt()-1.)+dr03HcalTowerSumEt())/max(20.,et) < 0.15 ) )'
                                                                )
cleanPatJets.checkOverlaps.electrons.deltaR = 0.4
cleanPatJets.checkOverlaps.electrons.requireNoOverlaps = True



###########################################################################################
#
# MUON SELECTION
#
###########################################################################################

## muons in tracker range
tightMuons = selectedPatMuons.clone(src = 'cleanPatMuons',
                                    cut = 'abs(eta) < 2.4'
				   )
## tracker muons
trackerMuons = selectedPatMuons.clone(src = 'tightMuons',
                                      cut = 'isTrackerMuon'
				     )
## muons reconstructed globally
globalMuons = selectedPatMuons.clone(src = 'trackerMuons',
                                     cut = 'isGlobalMuon'
				    )
## pt cut
hardMuons = selectedPatMuons.clone(src = 'globalMuons',
                                   cut = 'pt > 20.'
				  )
## n_hits
goodTrackMuons = selectedPatMuons.clone(src = 'hardMuons',
                                        cut = 'track.numberOfValidHits > 10'
				       )
## at least one valid muon hit
muHitMuons = selectedPatMuons.clone(src = 'goodTrackMuons',
                                    cut = 'globalTrack.hitPattern.numberOfValidMuonHits > 0'
				   )
## transverse impact parameter
goodD0Muons = selectedPatMuons.clone(src = 'muHitMuons',
                                     cut = 'abs(dB) < 0.02'
				    )
## global fit
goodMuons = selectedPatMuons.clone(src = 'goodD0Muons',
                                   cut = 'combinedMuon.normalizedChi2 < 10.0'
				  )
## isolation cut
isolatedMuons = selectedPatMuons.clone(src = 'goodMuons',
                                       cut = '(trackIso+caloIso)/pt < 0.15'
				      )
## this collection is needed to make sure that one muon is in trigger range
isolatedTightMuons = selectedPatMuons.clone(src = 'isolatedMuons',
                                            cut = 'abs(eta) < 2.1'
				           )


## Count Filters with n >= 1 requirement for control plots
oneTightMuonSelection      = countPatMuons.clone(src = 'tightMuons',     minNumber = 1)
oneTrackerMuonSelection    = countPatMuons.clone(src = 'trackerMuons',   minNumber = 1)
oneGlobalMuonSelection     = countPatMuons.clone(src = 'globalMuons',    minNumber = 1)
oneHardMuonSelection       = countPatMuons.clone(src = 'hardMuons',      minNumber = 1)
oneGoodTrackMuonSelection  = countPatMuons.clone(src = 'goodTrackMuons', minNumber = 1)
oneMuHitMuonSelection      = countPatMuons.clone(src = 'muHitMuons',     minNumber = 1)
oneGoodD0MuonSelection     = countPatMuons.clone(src = 'goodD0Muons',    minNumber = 1)
oneGoodMuonSelection       = countPatMuons.clone(src = 'goodMuons',      minNumber = 1)

## Count Filters with n >= 2 requirement for finale selection 
twoTightMuonSelection      = countPatMuons.clone(src = 'tightMuons',     minNumber = 2)
twoTrackerMuonSelection    = countPatMuons.clone(src = 'trackerMuons',   minNumber = 2)
twoGlobalMuonSelection     = countPatMuons.clone(src = 'globalMuons',    minNumber = 2)
twoHardMuonSelection       = countPatMuons.clone(src = 'hardMuons',      minNumber = 2)
twoGoodTrackMuonSelection  = countPatMuons.clone(src = 'goodTrackMuons', minNumber = 2)
twoMuHitMuonSelection      = countPatMuons.clone(src = 'muHitMuons',     minNumber = 2)
twoGoodD0MuonSelection     = countPatMuons.clone(src = 'goodD0Muons',    minNumber = 2)
twoGoodMuonSelection       = countPatMuons.clone(src = 'goodMuons',      minNumber = 2)

## Count Requirements for isolated muons
twoIsolatedMuonSelection      = countPatMuons.clone(src = 'isolatedMuons',       minNumber = 2)
oneIsolatedTightMuonSelection = countPatMuons.clone(src = 'isolatedTightMuons',  minNumber = 1)


###########################################################################################
#
# ELECTRON SELECTION
#
###########################################################################################

## Build Collections

# this if I do cleaning afterwards
# centralElectrons = selectedPatElectrons.clone( src = 'selectedPatElectrons',
#                                                cut = 'abs(eta) < 2.5'
#                                               )

# this is I do cleaning before
centralElectrons = selectedPatElectrons.clone( src = 'cleanPatElectrons',
                                               cut = 'abs(eta) < 2.5'
                                               )

highPtElectrons = selectedPatElectrons.clone( src = 'centralElectrons',
                                              cut = 'et > 20.'
                                              )

goodSCElectrons = selectedPatElectrons.clone( src = 'highPtElectrons',
                                              cut = 'superCluster.energy > 15.'
                                              )

goodD0Electrons = selectedPatElectrons.clone( src = 'goodSCElectrons',
                                              cut = 'abs(dB) < 0.04'
                                              )

#HoverEmElectrons = selectedPatElectrons.clone( src = 'goodD0Electrons',
#                                               cut = 'hcalOverEcal < 0.05'
#                                               )

# Select conv.rej. & ID only -> 5 OR 7
idOnlyElectrons = selectedPatElectrons.clone( src = 'goodD0Electrons',
                                              cut = 'electronID(\"simpleEleId90cIso\")   = 5.'
                                                    '| electronID(\"simpleEleId90cIso\") = 7.'
                                              )

isolatedElectrons = selectedPatElectrons.clone( src = 'idOnlyElectrons',
                                                cut = '(   (abs(superCluster.eta)>1.479) & (dr03TkSumPt()+dr03EcalRecHitSumEt()+dr03HcalTowerSumEt())/max(20.,et) < 0.15 )'
                                                      '| ( (abs(superCluster.eta)<1.479) & (dr03TkSumPt()+max(0.,dr03EcalRecHitSumEt()-1.)+dr03HcalTowerSumEt())/max(20.,et) < 0.15 )'
                                                )

## exact one very tight selected tag electron

centralElectronSelection  = countPatElectrons.clone(src = 'centralElectrons',  minNumber = 1)
highPtElectronSelection   = countPatElectrons.clone(src = 'highPtElectrons',   minNumber = 1)
goodSCElectronSelection   = countPatElectrons.clone(src = 'goodSCElectrons',   minNumber = 1)
goodD0ElectronSelection   = countPatElectrons.clone(src = 'goodD0Electrons',   minNumber = 1)
HoverEmElectronSelection  = countPatElectrons.clone(src = 'HoverEmElectrons',  minNumber = 1)
idOnlyElectronSelection   = countPatElectrons.clone(src = 'idOnlyElectrons',   minNumber = 1)
isolatedElectronSelection = countPatElectrons.clone(src = 'isolatedElectrons', minNumber = 1)
onlyOneElectronSelection  = countPatElectrons.clone(src = 'isolatedElectrons', minNumber = 1, maxNumber = 1)


## Count Filters with n >= 2 requirement for finale selection 
twoCentralElectronSelection  = countPatElectrons.clone(src = 'centralElectrons',  minNumber = 2)
twoHighPtElectronSelection   = countPatElectrons.clone(src = 'highPtElectrons',   minNumber = 2)
twoGoodSCElectronSelection   = countPatElectrons.clone(src = 'goodSCElectrons',   minNumber = 2)
twoGoodD0ElectronSelection   = countPatElectrons.clone(src = 'goodD0Electrons',   minNumber = 2)
twoHoverEmElectronSelection  = countPatElectrons.clone(src = 'HoverEmElectrons',  minNumber = 2)
twoIdOnlyElectronSelection   = countPatElectrons.clone(src = 'idOnlyElectrons',   minNumber = 2)
twoIsolatedElectronSelection = countPatElectrons.clone(src = 'isolatedElectrons', minNumber = 2)
exactlyTwoElectronSelection  = countPatElectrons.clone(src = 'isolatedElectrons', minNumber = 2, maxNumber = 2)


## Count Requirements for isolated electrons
# twoIsolatedElectronSelection = countPatElectrons.clone(src = 'isolatedElectrons', minNumber = 2)
# isolatedElectronSelection = countPatElectrons.clone(src = 'isolatedElectrons', minNumber = 1)




###########################################################################################
#
# JET SELECTION
#
###########################################################################################

## Build Collections
# this is needed for the new definition of PF id
from TopAnalysis.TopFilter.filters.JetIdFunctorFilter_cfi import *
## jet PF ID selection   
# cleanPatJets.src   = cms.InputTag("selectedPatJetsAK5PF")
# cleanPatJets.src   = cms.InputTag("residualCorrectedJets")   # for data
goodIdJets.jets    = cms.InputTag("cleanPatJets")
goodIdJets.jetType = cms.string('PF')
goodIdJets.version = cms.string('FIRSTDATA')
goodIdJets.quality = cms.string('LOOSE')

## good jet selection
goodJets = selectedPatJets.clone( src = 'goodIdJets',
                                  cut = 'pt > 15.'
                                  )

## tight jet selection
tightJets = selectedPatJets.clone(src = 'goodJets',
                                  cut = 'abs(eta) < 2.5'
                                  )

## hard jet selection
hardJets = selectedPatJets.clone( src = 'tightJets',
                                  cut = 'pt > 30.'
                                  )


goodIdJetsPF = selectedPatJets.clone( src = 'hardJets')



## check for different btag properties
trackCountingHighEffBJets = selectedPatJets.clone( src = 'goodIdJetsPF',
                                                   cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 1.7'
                                                   )

simpleSecondaryVertexBJets = selectedPatJets.clone( src = 'goodIdJetsPF',
                                                    cut = 'bDiscriminator(\"simpleSecondaryVertexHighEffBJetTags\") > 1.74'
                                                    )

## Count Filters
hardJetSelection        = countPatJets.clone(src = 'hardJets',                   minNumber = 1, maxNumber = 999)
tightJetSelection       = countPatJets.clone(src = 'tightJets',                  minNumber = 1, maxNumber = 999)
oneGoodIdJetPFSelection = countPatJets.clone(src = 'goodIdJetsPF',               minNumber = 1, maxNumber = 999)
twoGoodIdJetPFSelection = countPatJets.clone(src = 'goodIdJetsPF',               minNumber = 2, maxNumber = 999)
bJetTCHSelection        = countPatJets.clone(src = 'trackCountingHighEffBJets',  minNumber = 1, maxNumber = 999)
bJetSSVSelection        = countPatJets.clone(src = 'simpleSecondaryVertexBJets', minNumber = 1, maxNumber = 999)



###########################################################################################
#
# MET SELECTION
#
###########################################################################################

## met selector
highMETs = cms.EDFilter( "PATMETSelector",
                         src = cms.InputTag("patMETsPF"),
                         cut = cms.string("et > 30.")
                         )

## Count Filter
metSelection = cms.EDFilter("PATCandViewCountFilter",
                            minNumber = cms.uint32(1),
                            maxNumber = cms.uint32(999999),
                            src = cms.InputTag("highMETs")
                            )




###########################################################################################
#
# SEQUENCES
#
###########################################################################################
applyCleaning    = cms.Sequence( cleanPatCandidates )


buildJets = cms.Sequence(goodIdJets *
                         goodJets *
			 tightJets *
			 hardJets *
                         goodIdJetsPF
			)


requireOneIsolatedElectronSelection = cms.Sequence( centralElectrons *
                                             centralElectronSelection *
                                             highPtElectrons *
                                             highPtElectronSelection *
                                             goodSCElectrons *
                                             goodSCElectronSelection *
                                             goodD0Electrons *
                                             goodD0ElectronSelection *
                                             #HoverEmElectrons *
                                             #HoverEmElectronSelection *
                                             idOnlyElectrons *
                                             idOnlyElectronSelection *
                                             isolatedElectrons *
                                             isolatedElectronSelection
                                             #onlyOneMuonSelection *
                                             #onlyOneElectronSelection
                                             )



requireTwoIsolatedElectrons = cms.Sequence(twoCentralElectronSelection *
				   twoHighPtElectronSelection *
				   twoGoodSCElectronSelection *
        			   twoGoodD0ElectronSelection *
        			   twoIdOnlyElectronSelection *
        			   twoIsolatedElectronSelection  
				  )


onePFJetSelection = cms.Sequence( goodIdJets *
                                  goodJets  *
                                  tightJets *
                                  tightJetSelection *
                                  hardJets *
                                  hardJetSelection *
                                  goodIdJetsPF *
                                  oneGoodIdJetPFSelection
                                  )

twoPFJetSelection = cms.Sequence( twoGoodIdJetPFSelection )

pfMETSelection = cms.Sequence( highMETs *
                               metSelection
                               )

bTagSelection = cms.Sequence( trackCountingHighEffBJets *
                              bJetTCHSelection
                              # simpleSecondaryVertexBJets *
                              # bJetSSVSelection
                              )

################################################################################
#
# HELPER FUNCTION
#
################################################################################
		# cleanPatJets.src   = cms.InputTag("residualCorrectedJets")
