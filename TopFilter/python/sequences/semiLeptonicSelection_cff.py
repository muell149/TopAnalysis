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
                                        cut = 'isGlobalMuon &'
                                              'abs(eta) < 2.5 & pt > 10.&'
                                              '(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.2'
                                              #'(trackIso+caloIso)/pt <  0.2'
                                              
                                        )
## NB: defintions also in electronSelection_cff.py
looseElectrons = selectedPatElectrons.clone(src = 'selectedPatElectrons',
                                            cut = 'et > 15. & abs(eta) < 2.5 &'
                                                  #'(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et <  0.2'
                                                  '(chargedHadronIso+neutralHadronIso+photonIso)/et < 0.2'
                                           )

## setup jet selection collection
tightLeadingJets = selectedPatJets.clone(src = 'goodJets',
                                         cut=''
                                         )
tightBottomJets  = selectedPatJets.clone(src = 'trackCountingHighEffBJets',
                                         cut=''
                                         )
tightLeadingPFJets = selectedPatJets.clone(src = 'goodJetsPF30',
                                           cut=''
                                           )
tightBottomPFJets  = selectedPatJets.clone(src = 'goodJetsPF30',
                                           cut='bDiscriminator(\"trackCountingHighEffBJetTags\") > 3.3'
                                           )
## setting up the collections for the semi-leptonic
## event selection; on these collection monitoring
## can still be performed
semiLeptonicSelection = cms.Sequence(vertexSelectedMuons       *
                                     vertexSelectedElectrons   *  
                                     looseElectrons            * 
                                     standAloneMuons           *
                                     looseElectronsEJ          *   
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
                                     unconvTightElectronsEJ    *
                                     goodElectronsEJ           *
                                     noKinTightElectronsEJ     *
                                     trackCountingHighPurBJets *
                                     trackCountingHighEffBJets *
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

## 'step3'
tightElectronSelection = countPatElectrons.clone( src = 'tightElectronsEJ', minNumber = 1, maxNumber = 1 )

## 'step4'
muonVeto               = countPatMuons.clone( src = 'looseMuons', maxNumber = 0 )

## 'step5': Z veto for looser electrons with inv. mass between 76 - 106 GeV
from TopAnalysis.TopFilter.filters.SecondElectronFilter_cfi import *
secondElectronVeto     = filterLooseElectrons.clone( elecsTight = 'tightElectronsEJ', 
                                                     elecsLoose = 'looseElectronsEJ'   , 
                                                     massWindow = cms.vdouble(76.,106.)
                                                   )  

## 'step6a'
convElecHitRejection  = countPatElectrons.clone( src = 'unconvTightElectronsEJ', minNumber = 1, maxNumber = 1 )

## 'step6b'
convElecTrkRejection  = countPatElectrons.clone( src = 'goodElectronsEJ'     , minNumber = 1, maxNumber = 1 )


## setting up the semi-leptonic event selection;
## on these collection monitoring can still be
## performed
electronSelection          = cms.Sequence( tightElectronSelection *
                                           muonVeto               *
                                           secondElectronVeto     *
                                           convElecHitRejection   *
                                           convElecTrkRejection 
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

