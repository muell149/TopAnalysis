
import FWCore.ParameterSet.Config as cms

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
## electron count filter
from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *

###########################################################################################
#
# MUON SELECTION
#
###########################################################################################

#
# Build Collections
#

## muons in tracker range
tightMuons = selectedPatMuons.clone(src = 'selectedPatMuons', 
                                    cut = 'abs(eta) < 2.4'					        
				   )
## muons reconstructed globally
globalMuons = selectedPatMuons.clone(src = 'tightMuons', 
                                     cut = 'combinedMuon.isNull = 0'					        
				    )
## pt cut
hardMuons = selectedPatMuons.clone(src = 'globalMuons', 
                                   cut = 'pt > 20.'					        
				  )				      
## n_hits
goodTrackMuons = selectedPatMuons.clone(src = 'hardMuons', 
                                        cut = 'track.numberOfValidHits >= 11' 
				       )	
## transverse impact parameter
goodD0Muons = selectedPatMuons.clone(src = 'goodTrackMuons', 
                                     cut = 'abs(track.d0) < 0.2'
				    )	
## global fit
goodFitMuons = selectedPatMuons.clone(src = 'goodD0Muons', 
                                      cut = 'combinedMuon.normalizedChi2 < 10.0'
				     )						     
## mip signature ecal
ecalMipMuons = selectedPatMuons.clone(src = 'goodFitMuons', 
                                      cut = 'ecalIsoDeposit.candEnergy < 4'
				     )					     					     
## mip signature hcal
hcalMipMuons = selectedPatMuons.clone(src = 'ecalMipMuons', 
                                      cut = 'hcalIsoDeposit.candEnergy < 6'
				     )					     					     			    
## isolation cut				      				      
isolatedMuons = selectedPatMuons.clone(src = 'hcalMipMuons', 
                                       cut = '(trackIso+caloIso)/pt < 0.25' 
				      )				      

#
# Count Filters
#
tightMuonSelection      = countPatMuons.clone(src = 'tightMuons',     minNumber = 2)
globalMuonSelection     = countPatMuons.clone(src = 'globalMuons',    minNumber = 2)
hardMuonSelection       = countPatMuons.clone(src = 'hardMuons',      minNumber = 2)
goodTrackMuonSelection  = countPatMuons.clone(src = 'goodTrackMuons', minNumber = 2)
goodD0MuonSelection     = countPatMuons.clone(src = 'goodD0Muons',    minNumber = 2)
goodFitMuonSelection    = countPatMuons.clone(src = 'goodFitMuons',   minNumber = 2)
ecalMipMuonSelection    = countPatMuons.clone(src = 'ecalMipMuons',   minNumber = 2)
hcalMipMuonSelection    = countPatMuons.clone(src = 'hcalMipMuons',   minNumber = 2)
isolatedMuonSelection   = countPatMuons.clone(src = 'isolatedMuons',  minNumber = 2)


###########################################################################################
#
# JET SELECTION
#
###########################################################################################

#
# Build Collections
#

## hard jet selection
hardJets = selectedPatJets.clone(src = 'selectedPatJets', 
                                 cut = 'pt > 40.' 
			        )

## thight jet selection				   
tightJets = selectedPatJets.clone(src = 'hardJets', 
                                  cut = 'abs(eta) < 2.3' 
				        #'& 0.05 < emEnergyFraction' 
					#'& emEnergyFraction < 0.95'
			         )
				    				        
#
# Count Filters
#
hardJetSelection   = countPatJets.clone(src = 'hardJets',  minNumber = 2)
tightJetSelection  = countPatJets.clone(src = 'tightJets', minNumber = 2)

###########################################################################################
#
# SEQUENCES
#
###########################################################################################

buildCollections = cms.Sequence(tightMuons *
                                globalMuons *
				hardMuons *
				goodTrackMuons *
				goodD0Muons *
				goodFitMuons *
				ecalMipMuons *
				hcalMipMuons *
				isolatedMuons *
				hardJets *
				tightJets				
			       )			       			       

fullLeptonicMuonMuonSelection = cms.Sequence(tightMuonSelection *
                                             globalMuonSelection *
				             hardMuonSelection *
				             goodTrackMuonSelection *
				             goodD0MuonSelection *
				             goodFitMuonSelection *
				             ecalMipMuonSelection *
				             hcalMipMuonSelection *
				             isolatedMuonSelection *
				             hardJetSelection *
				             tightJetSelection	
                                            )
