import FWCore.ParameterSet.Config as cms

## gen jet selector
from TopAnalysis.TopUtils.CommonGenJetSelector_cfi import *
## gen muon selector
from TopAnalysis.TopUtils.CommonGenParticleSelector_cfi import *

## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *


## configure jet and Muon selections
selectedGenJetCollection = selectedGenJets.clone(src = 'antikt5GenJets',
                                                 cut = 'abs(eta) < 2.4 & pt > 30.'
                                                 )

selectedGenMuonCollection = selectedGenParticles.clone(src = 'isolatedGenMuons',
                                                       cut = 'abs(eta) < 2.1 & pt > 20.'
                                                       )


semiLeptGenCollections = cms.Sequence(selectedGenMuonCollection  *
                                      selectedGenJetCollection
                                      )

## set up the muon selection
genMuonSelection  = countPatMuons.clone(src = 'selectedGenMuonCollection',
                                        minNumber = 1,
                                        maxNumber = 1
                                        )

## set up the jet selection 
leadingGenJetSelection = countPatJets.clone(src = 'selectedGenJetCollection',
                                            minNumber = 4
                                            )
