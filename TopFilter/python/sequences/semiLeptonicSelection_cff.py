import FWCore.ParameterSet.Config as cms

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
##    setup the collections for the semi-leptonic event selection
## ---

## setup the lepton selection collections
tightMuons     = selectedPatMuons.clone(src = 'goldenMuons',
                                           cut = '(trackIso+caloIso)/pt < 0.05'
                                           )
looseMuons     = selectedPatMuons.clone(src = 'trackMuons',
                                           cut = '(trackIso+caloIso)/pt <  0.2'
                                           )
looseElectrons = selectedPatElectrons.clone(src = 'selectedPatElectrons',
                                               cut = 'et > 15. & abs(eta) < 2.5 &'
                                                     'electronID(\"eidRobustLoose\") &'
                                                     '(trackIso+caloIso)/et <  0.2'
                                               )

## setup jet selection collection
tightLeadingJets = selectedPatJets.clone(src = 'goodJets',
                                            cut=''
                                            )
tightBottomJets  = selectedPatJets.clone(src = 'trackCountingHighPurBJets',
                                            cut=''
                                            )

## setting up the collections for the semi-leptonic
## event selection; on these collection monitoring
## can still be performed
semiLeptonicSelection = cms.Sequence(looseElectrons   *
                                     triggerMuons     *
                                     trackMuons       *
                                     goodMuons        *
                                     goldenMuons      *
                                     looseMuons       *
                                     tightMuons       *
                                     goodJets         *
                                     trackCountingHighPurBJets *
                                     tightLeadingJets *
                                     tightBottomJets
                                     )

## ---
##    setup the semi-leptonic event selection
## ---

## setup the lepton selection
secondMuonVeto = countPatMuons.clone(src = 'looseMuons',
                                        maxNumber = 1
                                        )
muonSelection  = countPatMuons.clone(src = 'tightMuons',
                                        minNumber = 1,
                                        maxNumber = 1
                                        )
electronVeto   = countPatElectrons.clone(src = 'looseElectrons',
                                            maxNumber = 0
                                            )

## setup jet selection collection
leadingJetSelection = countPatJets.clone(src = 'tightLeadingJets',
                                            minNumber = 4
                                            )
bottomJetSelection  = countPatJets.clone(src = 'tightBottomJets',
                                            minNumber = 1
                                            )

## setting up the semi-leptonic event selection;
## on these collection monitoring can still be
## performed
semiLeptonicEvents = cms.Sequence(muonSelection       *
                                  secondMuonVeto      *
                                  electronVeto        *
                                  leadingJetSelection *
                                  bottomJetSelection
                                  )

## ---
##    provide a function to disable parts of the selection
## ---
def disableCountFilter(whichCountFilter):
    whichCountFilter.minNumber = 0
    whichCountFilter.maxNumber = 999999
