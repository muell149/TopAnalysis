import FWCore.ParameterSet.Config as cms

## from /MinimumBias/Commissioning10-PromptReco-v8/RECO/
## 39 "multijet" events in 4 files dCache at DESY

process.source.fileNames = [
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132606_1.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132606_2.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132606_3.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132606_4.root'
    ]
