import FWCore.ParameterSet.Config as cms


## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *



## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *


## tight muon selection
hardMuons = selectedLayer1Muons.clone(src = 'selectedLayer1Muons', 
                                       cut = 'combinedMuon.isNull = 0'
					     '& pt > 20.'
					     '& abs(eta) < 2.4' )




## at least two tight muons
muonSelection  = countLayer1Muons.clone(src = 'hardMuons', minNumber = 2, maxNumber = 999)

fullLeptonicMuonMuonPreselection = cms.Sequence(hardMuons * 
                                                muonSelection 
                                               )
