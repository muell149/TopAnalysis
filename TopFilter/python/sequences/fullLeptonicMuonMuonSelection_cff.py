import FWCore.ParameterSet.Config as cms

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *

###########################################################################################
#
# MUON SELECTION
#
###########################################################################################

## muons in tracker range
tightMuons = selectedPatMuons.clone(src = 'selectedPatMuons',
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
<<<<<<< fullLeptonicMuonMuonSelection_cff.py
				  )

## isolation cut				      				      
isolatedMuons = selectedPatMuons.clone(src = 'goodMuons', 
                                       cut = '(trackIso+caloIso)/pt < 0.15' 
				      )

## this collection is needed to make sure that one muon is in trigger range
isolatedTightMuons = selectedPatMuons.clone(src = 'isolatedMuons', 
                                            cut = 'abs(eta) < 2.1' 
				           )					      
				      			      
=======
				  )
## isolation cut
isolatedMuons = selectedPatMuons.clone(src = 'goodMuons',
                                       cut = '(trackIso+caloIso)/pt < 0.15'
				      )
## this collection is needed to make sure that one muon is in trigger range
isolatedTightMuons = selectedPatMuons.clone(src = 'isolatedMuons',
                                            cut = 'abs(eta) < 2.1'
				           )

>>>>>>> 1.27

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
# JET SELECTION
#
###########################################################################################

from PhysicsTools.PatAlgos.cleaningLayer1.cleanPatCandidates_cff import *
cleanPatElectrons.finalCut = cms.string('et > 20.'
                                        '& abs(eta) < 2.5'
					'& electronID("eidTight")'
					'&(trackIso+caloIso)/pt < 0.15'
                                       )
cleanPatJets.src = "selectedPatJets"

cleanPatJets.checkOverlaps.muons.src  = 'goodMuons'
cleanPatJets.checkOverlaps.muons.preselection = '(trackIso+caloIso)/pt < 0.15'

cleanPatJets.checkOverlaps.muons.deltaR  = 0.4
cleanPatJets.checkOverlaps.muons.requireNoOverlaps = True 

cleanPatJets.checkOverlaps.electrons.deltaR  = 0.4
cleanPatJets.checkOverlaps.electrons.requireNoOverlaps = True 

## good id jet selection
from TopAnalysis.TopFilter.filters.JetIdFunctorFilter_cfi import *
goodIdJets.src     = cms.InputTag('cleanPatJets') 
goodIdJets.jetType = cms.string('CALO')
goodIdJets.version = cms.string('PURE09')
goodIdJets.quality = cms.string('LOOSE')

## thight jet selection
tightJets = selectedPatJets.clone(src = 'goodIdJets',
                                  cut = 'abs(eta) < 2.5'
			         )
## hard jet selection
hardJets = selectedPatJets.clone(src = 'tightJets', 
                                 cut = 'pt > 30.' 
			        )

## b-jet selection (optional)
bJetsTCHE = selectedPatJets.clone(src = 'hardJets',
		                  cut = 'bDiscriminator("trackCountingHighEffBJetTags") > 1.7' 
		                 )
## OR
bJetsSVHE = selectedPatJets.clone(src = 'hardJets',
		                  cut = 'bDiscriminator("simpleSecondaryVertexHighEffBJetTags") > 1.74' 
		                 )

## Count Filters with n >= 1 for control plots
oneTightJetSelection  = countPatJets.clone(src = 'tightJets', minNumber = 1)
oneGoodIdJetSelection = countPatJets.clone(src = 'goodIdJets',minNumber = 1)
oneHardJetSelection   = countPatJets.clone(src = 'hardJets',  minNumber = 1)
oneBJetTCHE           = countPatJets.clone(src = 'bJetsTCHE', minNumber = 1)
oneBJetSVHE           = countPatJets.clone(src = 'bJetsSVHE', minNumber = 1)

## Count Filters with n >= 2 for control plots
twoTightJetSelection  = countPatJets.clone(src = 'tightJets', minNumber = 2)
twoGoodIdJetSelection = countPatJets.clone(src = 'goodIdJets',minNumber = 2)
twoHardJetSelection   = countPatJets.clone(src = 'hardJets',  minNumber = 2)
twoBJetTCHE           = countPatJets.clone(src = 'bJetsTCHE', minNumber = 2)
twoBJetSVHE           = countPatJets.clone(src = 'bJetsSVHE', minNumber = 2)


###########################################################################################
#
# MET SELECTION
#
###########################################################################################

## met selector
highMETs = cms.EDFilter("PATMETSelector",
    src = cms.InputTag("patMETs"),
    cut = cms.string("et>30.")
)

## Count Filter
metSelection = cms.EDFilter("PATCandViewCountFilter",
    minNumber = cms.uint32(     1),
    maxNumber = cms.uint32(999999),
    src = cms.InputTag("highMETs")
)


###########################################################################################
#
# SEQUENCES
#
###########################################################################################

requireOneGoodMuon = cms.Sequence(tightMuons *
				  oneTightMuonSelection *
				  trackerMuons *
        			  oneTrackerMuonSelection *
				  globalMuons *
        			  oneGlobalMuonSelection *
        			  hardMuons *
        			  oneHardMuonSelection *
        			  goodTrackMuons *
        			  oneGoodTrackMuonSelection *
        			  muHitMuons *
        			  oneMuHitMuonSelection *
        			  goodD0Muons *
        			  oneGoodD0MuonSelection *
        			  goodMuons *
        			  oneGoodMuonSelection
                                 )

requireTwoGoodMuons = cms.Sequence(twoTightMuonSelection *
				   twoTrackerMuonSelection *
				   twoGlobalMuonSelection *
        			   twoHardMuonSelection *
        			   twoGoodTrackMuonSelection *
        			   twoMuHitMuonSelection *
        			   twoGoodD0MuonSelection *
        			   twoGoodMuonSelection 
				  )

requireTwoIsolatedMuons = cms.Sequence(isolatedMuons *
                                       twoIsolatedMuonSelection *
				       isolatedTightMuons *
				       oneIsolatedTightMuonSelection
				      )

applyJetCleaning = cms.Sequence(cleanPatCandidates)

buildJets = cms.Sequence(goodIdJets *
			 tightJets *
			 hardJets
			)
			
requireOneHardJet = cms.Sequence(oneGoodIdJetSelection *	
                                 oneTightJetSelection *	    
			         oneHardJetSelection
			        )

requireTwoHardJets = cms.Sequence(twoGoodIdJetSelection *
                                  twoTightJetSelection *
			          twoHardJetSelection
			         )
			     
requireMET = cms.Sequence(highMETs *
			  metSelection
			 )
			 
requireOneBtagTCHE = cms.Sequence(bJetsTCHE *
                                 oneBJetTCHE
				 )

requireTwoBtagsTCHE = cms.Sequence(twoBJetTCHE)
				 
requireOneBtagSVHE = cms.Sequence(bJetsSVHE *
                                 oneBJetSVHE
				 )

requireTwoBtagsSVHE = cms.Sequence(twoBJetSVHE)


################################################################################
#
# HELPER FUNCTION
#
################################################################################

def switchJetType(jt):
	if jt == "JPT":
		cleanPatJets.src   = cms.InputTag("selectedPatJetsAK5JPT")
		goodIdJets.jets    = cms.InputTag("cleanPatJets")
		goodIdJets.jetType = cms.string('JPT')
		goodIdJets.version = cms.string('PURE09')
		goodIdJets.quality = cms.string('LOOSE')
		highMETs.src       = cms.InputTag("patMETsJPT")
	elif jt == "PF":
		cleanPatJets.src   = cms.InputTag("selectedPatJetsAK5PF")
		goodIdJets.jets    = cms.InputTag("cleanPatJets")
		goodIdJets.jetType = cms.string('PF')
		goodIdJets.version = cms.string('FIRSTDATA')
		goodIdJets.quality = cms.string('LOOSE')
		highMETs.src	 = cms.InputTag("patMETsPF")
	elif jt == "CALO":
		cleanPatJets.src   = cms.InputTag("selectedPatJets")
		goodIdJets.jets    = cms.InputTag("cleanPatJets")
		goodIdJets.jetType = cms.string('CALO')
		goodIdJets.version = cms.string('PURE09')
		goodIdJets.quality = cms.string('LOOSE')
		highMETs.src     = cms.InputTag("patMETs")
	else:
		print "WARNING: unknown jet type specified in selection sequence. Will use default."
