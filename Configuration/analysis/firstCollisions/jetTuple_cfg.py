import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for jetTuple production
#-------------------------------------------------

process = cms.Process("JetTuple")

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('topFilter')
process.MessageLogger.cerr.topFilter = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_1.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_10.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_11.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_12.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_13.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_14.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_15.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_16.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_17.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_18.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_19.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_2.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_20.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_21.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_3.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_4.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_5.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_6.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_7.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_8.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123615_9.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#-------------------------------------------------
# jet selection
#-------------------------------------------------

## select jets
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
process.goodJets = selectedLayer1Jets.clone(src = 'selectedLayer1Jets',
                                            cut =
                                            'abs(eta) < 2.4 & pt > 20. &'
                                            '0.05 < emEnergyFraction   &'
                                            '0.95 > emEnergyFraction'
                                            )

## select events with good jets
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
process.countJets = countLayer1Jets.clone(src = 'goodJets',
                                          minNumber = 1
                                          )

#-------------------------------------------------
# process output
#-------------------------------------------------

## process path
process.p1 = cms.Path(process.goodJets *
                      process.countJets)

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p1')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('keep *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('jetTuple_Run123615.root')
)

process.outpath = cms.EndPath(process.out)
