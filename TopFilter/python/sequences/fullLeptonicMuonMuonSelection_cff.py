
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

## phase space cuts
hardMuons = selectedPatMuons.clone(src = 'selectedPatMuons', 
                                      cut = 'combinedMuon.isNull = 0'
					     '& pt > 20.'
					     '& abs(eta) < 2.4'    
				     )
				      
## default qualtiy cuts
qualityMuons = selectedPatMuons.clone(src = 'hardMuons', 
                                         cut = 'track.numberOfValidHits >= 11' 
					       '& abs(track.d0) < 0.2'
					       '& combinedMuon.normalizedChi2 < 10.0'
					       '& ecalIsoDeposit.candEnergy < 4'
					       '& hcalIsoDeposit.candEnergy < 6'
				        )				      

## isolation cut				      				      
isolatedMuons = selectedPatMuons.clone(src = 'qualityMuons', 
                                          cut = '(trackIso+caloIso)/pt < 0.25' 
				         )				      

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
				        
## muon count filter in three steps
hardMuonSelection      = countPatMuons.clone(src = 'hardMuons',     minNumber = 2, maxNumber = 999)
qualityMuonSelection   = countPatMuons.clone(src = 'qualityMuons',  minNumber = 2, maxNumber = 999)
isolatedMuonSelection  = countPatMuons.clone(src = 'isolatedMuons', minNumber = 2, maxNumber = 999)


## at least two jets
hardJetSelection   = countPatJets.clone(src = 'hardJets',  minNumber = 2)
tightJetSelection  = countPatJets.clone(src = 'tightJets', minNumber = 2)

buildCollections = cms.Sequence(hardMuons *
                                qualityMuons *
				isolatedMuons *
				hardJets *
				tightJets				
			       )			       			       

fullLeptonicMuonMuonSelection = cms.Sequence(hardMuonSelection * 
                                             qualityMuonSelection * 
                                             isolatedMuonSelection * 
                                             hardJetSelection *
					     tightJetSelection
                                            )
