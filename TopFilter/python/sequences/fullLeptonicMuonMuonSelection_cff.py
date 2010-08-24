
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

#
# Build Collections
#

## muons in tracker range
tightMuons = selectedPatMuons.clone(src = 'selectedPatMuons', 
                                    cut = 'abs(eta) < 2.4'					        
				   )
## muons reconstructed globally
globalMuons = selectedPatMuons.clone(src = 'tightMuons', 
                                     cut = 'isGlobalMuon'					        
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
                                     cut = 'abs(dB) < 0.02'
				    )	
## global fit
goodFitMuons = selectedPatMuons.clone(src = 'goodD0Muons', 
                                      cut = 'combinedMuon.normalizedChi2 < 10.0'
				     )						     
## mip signature ecal
ecalMipMuons = selectedPatMuons.clone(src = 'goodFitMuons', 
                                      cut = 'isolationR03.emVetoEt < 4'
				     )					     					     
## mip signature hcal
hcalMipMuons = selectedPatMuons.clone(src = 'ecalMipMuons', 
                                      cut = 'isolationR03.hadVetoEt < 6'
				     )					     					     			    
## isolation cut				      				      
isolatedMuons = selectedPatMuons.clone(src = 'hcalMipMuons', 
                                       cut = '(trackIso+caloIso)/pt < 0.15' 
				      )				      

## Count Filters
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


## hard jet selection
hardJets = selectedPatJets.clone(src = 'selectedPatJetsAK5PF', 
                                 cut = 'pt > 40.' 
			        )
## thight jet selection				   
tightJets = selectedPatJets.clone(src = 'hardJets', 
                                  cut = 'abs(eta) < 2.3' 				        
			         )
				    				        
## Count Filters
hardJetSelection   = countPatJets.clone(src = 'hardJets',  minNumber = 2)
tightJetSelection  = countPatJets.clone(src = 'tightJets', minNumber = 2)


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
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(999999),
    src = cms.InputTag("highMETs")
)

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
				tightJets *
				highMETs				
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
				             tightJetSelection *
					     metSelection	
                                            )
