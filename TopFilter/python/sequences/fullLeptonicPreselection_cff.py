import FWCore.ParameterSet.Config as cms


## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

## electron selector
from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *

## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *

## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.leptonCountFilter_cfi import *

## muon selection
hardMuons = selectedPatMuons.clone(src = 'selectedPatMuons', 
                                       cut = 'pt > 15.'
					     '& abs(eta) < 2.5' )

## muon selection
hardElectrons = selectedPatElectrons.clone(src = 'selectedPatElectrons', 
                                           cut = 'pt > 15.'
					         '& abs(eta) < 2.5' )

## count filters: first demand one muon
muonSelection    = countPatMuons.clone(src       = 'hardMuons',    
                                       minNumber = 1
				      )
## if muon found filter for second lepton				      
leptonSelection = countPatLeptons.clone(muonSource     = 'hardMuons', 
                                        electronSource = 'hardElectrons', 
                                        countElectrons = cms.bool(True),
                                        countMuons     = cms.bool(True),
                                        countTaus      = cms.bool(False),					
                                        minNumber      = 2)

buildLeptonCollections = cms.Sequence(hardMuons * 
                                      hardElectrons
                                     )

fullLeptonicPreselection = cms.Sequence(muonSelection *
                                        leptonSelection 
                                       )
					       

