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
                                    cut = 'abs(eta) < 2.5'					        
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
goodD0Muons = selectedPatMuons.clone(src = 'goodTrackMuons', 
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
twoIsolatedMuonSelection   = countPatMuons.clone(src = 'isolatedMuons',  minNumber = 2)


###########################################################################################
#
# JET COLLECTION CLEANING
#
###########################################################################################

from PhysicsTools.PatAlgos.cleaningLayer1.cleanPatCandidates_cff import *
cleanPatElectrons.finalCut = cms.string('et > 20.'
                                        '& abs(eta) < 2.5'
					'& electronID("eidTight")'
					'&(trackIso+caloIso)/pt < 0.15'
                                       )
							  
cleanPatJets.src = "selectedPatJetsAK5PF"

cleanPatJets.checkOverlaps.muons.src  = 'goodMuons'
cleanPatJets.checkOverlaps.muons.preselection = '(trackIso+caloIso)/pt < 0.15'
cleanPatJets.checkOverlaps.muons.deltaR  = 0.4
cleanPatJets.checkOverlaps.muons.requireNoOverlaps = True 

cleanPatJets.checkOverlaps.electrons.deltaR  = 0.4
cleanPatJets.checkOverlaps.electrons.requireNoOverlaps = True 


###########################################################################################
#
# JET SELECTION
#
###########################################################################################

## thight jet selection				   
tightJets = selectedPatJets.clone(src = 'cleanPatJets', 
                                  cut = 'abs(eta) < 2.5' 				        
			         )

## good jet selection
goodJets = selectedPatJets.clone(src = 'tightJets', 
                                 cut = 'chargedHadronEnergyFraction > 0.0'
                                       '& neutralHadronEnergyFraction < 1.0'
                                       '& chargedEmEnergyFraction < 1.0'
                                       '& neutralEmEnergyFraction < 1.0'
                                       '& chargedMultiplicity > 0'
                                       '& nConstituents > 1'
                                )
## hard jet selection
hardJets = selectedPatJets.clone(src = 'goodJets', 
                                 cut = 'pt > 30.' 
			        )
								    				        
## Count Filters with n >= 1 for control plots
oneTightJetSelection  = countPatJets.clone(src = 'tightJets', minNumber = 1)
oneGoodJetSelection   = countPatJets.clone(src = 'goodJets',  minNumber = 1)
oneHardJetSelection   = countPatJets.clone(src = 'hardJets',  minNumber = 1)

## Count Filters with n >= 2 for control plots
twoTightJetSelection  = countPatJets.clone(src = 'tightJets', minNumber = 2)
twoGoodJetSelection   = countPatJets.clone(src = 'goodJets',  minNumber = 2)
twoHardJetSelection   = countPatJets.clone(src = 'hardJets',  minNumber = 2)


###########################################################################################
#
# MET SELECTION
#
###########################################################################################

## met selector
highMETs = cms.EDFilter("PATMETSelector",
    src = cms.InputTag("patMETsPF"),
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
                                       twoIsolatedMuonSelection)	

applyJetCleaning = cms.Sequence(cleanPatCandidates)

buildJets = cms.Sequence(tightJets *
			 goodJets *
			 hardJets				
			)	
			
requireOneHardJet = cms.Sequence(oneTightJetSelection *
                                 oneGoodJetSelection *		    
			         oneHardJetSelection
			        )			

requireTwoHardJets = cms.Sequence(twoTightJetSelection *
                                  twoGoodJetSelection *		    
			          twoHardJetSelection
			         )
			     
requireMET = cms.Sequence(highMETs * 		    
			  metSelection
			 )			     
