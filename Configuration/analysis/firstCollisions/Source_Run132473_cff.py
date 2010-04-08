import FWCore.ParameterSet.Config as cms

## from /MinimumBias/Commissioning10-PromptReco-v8/RECO/
## ??? "multijet" events in 4 files dCache at DESY

process.source.fileNames = [
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132473_1.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132473_2.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132473_3.root',
    '/store/user/snaumann/firstCollisions_7TeV/patTuple_Run132473_4.root'
    ]
