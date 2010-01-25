import FWCore.ParameterSet.Config as cms

## jet selector
from TopAnalysis.TopAnalyze.jetSelection_cff import *
## muon selector
from TopAnalysis.TopAnalyze.muonSelection_cff import *
## electron selector
from TopAnalysis.TopAnalyze.electronSelection_cff import *

## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
## electron count filter
from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *

## tag muon selection
tagMuons     = standAloneMuons
## tag electron selection
tagElectrons = isolatedElectrons
## tag jet selection
tagJets      = trackCountingHighPurBJets


## at least one tag muons
muonSelection  = countLayer1Muons.clone(src = 'tagMuons', minNumber = 1, maxNumber = 999)
## exact one very tight selected tag electron
electronSelection = countLayer1Electrons.clone(src = 'tagElectrons', minNumber = 1, maxNumber = 1)
## at least two very tight selected b jets
jetSelection   = countLayer1Jets.clone(src = 'tagJets', minNumber = 2)


tagCollections = cms.Sequence(tagMuons     *
                              tagElectrons *
                              tagJets 
                              )			       			       

tagSelection = cms.Sequence(muonSelection *
                            electronSelection *
                            jetSelection 
                            )
