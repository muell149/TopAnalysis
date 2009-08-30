import FWCore.ParameterSet.Config as cms

## high level trigger filter
from HLTrigger.HLTfilters.hltHighLevel_cfi import *

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
##    setup trigger filter path
## ---
## single-muon trigger, threshold pt > 9 GeV, no isolation requirements
hltHighLevel.HLTPaths = ["HLT_Mu9"]

## ---
##    setup muon/electron selections
## ---
## tight muon selection
tightMuons = selectedLayer1Muons.clone(src = 'selectedLayer1Muons', cut = 'pt > 20. & abs(eta) < 2.1 & (trackIso+caloIso)/pt < 0.05')
## loose muon selection (for veto)
looseMuons = selectedLayer1Muons.clone(src = 'selectedLayer1Muons', cut = 'pt > 10. & abs(eta) < 2.5 & (trackIso+caloIso)/pt <  0.2')
## loose electron selection (for veto)
looseElectrons = selectedLayer1Electrons.clone(src = 'selectedLayer1Electrons', cut = 'et > 15. & abs(eta) < 2.5 & (trackIso+caloIso)/et <  0.2')

## ---
##    setup lepton filters
## ---
## at least one tight muon
muonSelection  = countLayer1Muons.clone(src = 'tightMuons', minNumber = 1, maxNumber = 1)
## no additional loose muon
secondMuonVeto = countLayer1Muons.clone(src = 'looseMuons', maxNumber = 1)
## no additional loose electron
electronVeto   = countLayer1Electrons.clone(src = 'looseElectrons', maxNumber = 0)

## ---
##    setup jet selection
## ---
## tight jet selection
tightLeadingJets = selectedLayer1Jets.clone(src = 'selectedLayer1Jets', cut = 'pt > 30. & abs(eta) < 2.4 & 0.05 < emEnergyFraction & emEnergyFraction < 0.95')
## tight b jet selection
tightBottomJets  = selectedLayer1Jets.clone(src = 'tightLeadingJets', cut = 'bDiscriminator(\"trackCountingHighPurBJetTags\") > 2.0')

## ---
##    setup jet filter
## ---
## at least four jets
leadingJetSelection = countLayer1Jets.clone(src = 'tightLeadingJets', minNumber = 4)
## at least one of them should be a b-jet
bottomJetSelection  = countLayer1Jets.clone(src = 'tightBottomJets', minNumber = 1)

## ---
##    provide a sequence
## ---
semiLeptonicSelection = cms.Sequence( hltHighLevel                             * 
                                     (tightMuons       * muonSelection       ) *
                                     (looseMuons       * secondMuonVeto      ) *
                                     (looseElectrons   * electronVeto        ) *
                                     (tightLeadingJets * leadingJetSelection ) *
                                     (tightBottomJets  * bottomJetSelection  )
                                     )

## ---
##    provide a function to disable parts of the selection
## ---
def disableCountFilter(whichCountFilter):
    whichCountFilter.minNumber = 0
    whichCountFilter.maxNumber = 999999
