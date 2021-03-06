import FWCore.ParameterSet.Config as cms

## jet selector
from TopAnalysis.TopFilter.sequences.jetSelection_cff import *
## muon selector
from TopAnalysis.TopFilter.sequences.muonSelection_cff import *
## electron selection
from TopAnalysis.TopFilter.sequences.electronSelection_cff import *

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
## for tight Muons see muonSelection_cff.py
looseMuons     = selectedPatMuons.clone(src = 'selectedPatMuons',
                                        cut = '(isGlobalMuon | isTrackerMuon) & isPFMuon &' # changed in 2012 (was isGlobalMuon)
                                              'abs(eta) < 2.5 & pt > 10.&'
                                              '(chargedHadronIso+max((neutralHadronIso+photonIso-0.5*puChargedHadronIso),0.0))/pt < 0.2' # changed in 2012
                                        )
## NB: defintions also in electronSelection_cff.py
looseElectrons = selectedPatElectrons.clone(src = 'selectedPatElectrons',
                                            cut = 'pt > 20. & abs(eta) < 2.5 &' # changed in 2012 (was et>15)
                                                  '(chargedHadronIso+max((neutralHadronIso+photonIso-0.5*puChargedHadronIso),0.0))/et < 0.15 &'
                                                  'electronID("mvaTrigV0") > 0'
                                           )

## setup jet selection collection
tightLeadingJets = selectedPatJets.clone(src = 'goodJets',
                                         cut=''
                                         )
tightBottomJets  = combinedSecondaryVertexBJets.clone(src = 'goodJets',
                                         cut=''
                                         )
tightLeadingPFJets = selectedPatJets.clone(src = 'goodJetsPF30',
                                           cut=''
                                           )
tightBottomPFJets  = selectedPatJets.clone(src = 'combinedSecondaryVertexBJets'
                                           )
## setting up the collections for the semi-leptonic
## event selection; on these collection monitoring
## can still be performed
semiLeptonicSelection = cms.Sequence(vertexSelectedMuons       *
                                     vertexSelectedMuons2012   *
                                     vertexSelectedElectrons   *  
                                     looseElectrons            * 
                                     standAloneMuons           *
                                     tightElectronsEJ          *
                                     centralJets               *
                                     reliableJets              *
                                     goodJets                  *
                                     noOverlapJetsPF           *
                                     centralJetsPF             *
                                     reliableJetsPF            *
                                     goodJetsPF                *
                                     goodJetsPF20              *
                                     centralJetsPF25           *
                                     reliableJetsPF25          *
                                     goodJetsPF25              *
                                     centralJetsPF30           *
                                     reliableJetsPF30          *
                                     goodJetsPF30              *
                                     vetoJets                  *
                                     noKinJetsPF               *
                                     dRMuons                   *
                                     combinedMuons             *
				     highPtMuons20             *
                                     highPtMuons               *
                                     kinematicMuons            *
                                     trackMuons                *
                                     goldenMuons               *
                                     looseMuons                *
                                     tightMuons                *
                                     noKinMuons                *
                                     goodElectronsEJ           *
                                     noKinTightElectronsEJ     *
                                     trackCountingHighPurBJets *
                                     trackCountingHighEffBJets *
                                     simpleSecondaryVertexHighEffBJets *
				     combinedSecondaryVertexBJets      *
                                     tightLeadingJets          *
                                     tightBottomJets           *
                                     tightLeadingPFJets        *
                                     tightBottomPFJets
                                     )

## ---
##    setup the semi-leptonic event selection (muon + jets)
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
##    setup the semi-leptonic event selection (elec + jets)
## ---


## setup the lepton selection

## 'step1'
tightElectronSelection = countPatElectrons.clone( src = 'tightElectronsEJ', minNumber = 1, maxNumber = 1 )

## 'step2'
muonVeto               = countPatMuons.clone( src = 'looseMuons', maxNumber = 0 )

## 'step3'
secondElectronVeto     = countPatElectrons.clone( src = 'looseElectrons',
                                         maxNumber = 1
                                         )

## 'step4'
convElecRejection  = countPatElectrons.clone( src = 'goodElectronsEJ'     , minNumber = 1, maxNumber = 1 )


## setting up the semi-leptonic event selection;
## on these collection monitoring can still be
## performed
electronSelection          = cms.Sequence( tightElectronSelection *
                                           muonVeto               *
                                           secondElectronVeto     *
                                           convElecRejection 
                                         )

semiLeptonicElectronEvents = cms.Sequence( electronSelection      *
                                           leadingJetSelection    * 
                                           bottomJetSelection 
                                         )

## ---
##    provide a function to disable parts of the selection
## ---
def disableCountFilter(whichCountFilter):
    whichCountFilter.minNumber = 0
    whichCountFilter.maxNumber = 999999
