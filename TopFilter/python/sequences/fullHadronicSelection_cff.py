import FWCore.ParameterSet.Config as cms

## all leptons kept for possible rejection of events later on (not yet implemented)

## jet selector
from TopAnalysis.TopFilter.sequences.jetSelection_cff import *
## muon selector
from TopAnalysis.TopFilter.sequences.muonSelection_cff import *

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


## ---
##    setup the collections for the fully-hadronic event selection
## ---

## setup the jet selection collection
tightLeadingJets = selectedLayer1Jets.clone(src = 'goodJets',
                                            cut = 'pt > 40'
                                            )
tightBottomJets  = selectedLayer1Jets.clone(src = 'trackCountingHighPurBJets',
                                            cut = 'pt > 50'
                                            )

## setting up the collections for the fully-hadronic
## event selection; on these collection monitoring
## can still be performed
fullHadronicSelection = cms.Sequence(goodJets *
                                     trackCountingHighPurBJets *
                                     tightLeadingJets *
                                     tightBottomJets
                                     )

## ---
##    setup the fully-hadronic event selection
## ---

## setup jet selection collection
leadingJetSelection = countLayer1Jets.clone(src = 'tightLeadingJets',
                                            minNumber = 6
                                            )
bottomJetSelection  = countLayer1Jets.clone(src = 'tightBottomJets',
                                            minNumber = 2
                                            )

## setting up the fully-hadronic event selection;
## on these collection monitoring can still be
## performed
fullHadronicEvents = cms.Sequence(leadingJetSelection *
                                  bottomJetSelection
                                  )

## ---
##    provide a function to disable parts of the selection
## ---
def disableCountFilter(whichCountFilter):
    whichCountFilter.minNumber = 0
    whichCountFilter.maxNumber = 999999
