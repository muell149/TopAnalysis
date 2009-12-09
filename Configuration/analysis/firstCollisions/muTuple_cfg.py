import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for muTuple production
#-------------------------------------------------

process = cms.Process("MuTuple")

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

## select muons
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
process.goodMuons = selectedLayer1Muons.clone(src = 'selectedLayer1Muons',
                                              cut = 'combinedMuon.isNull = 0'
                                              )

## select events with good muons
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
process.countMuons = countLayer1Muons.clone(src = 'goodMuons',
                                            minNumber = 1
                                            )

#-------------------------------------------------
# process output
#-------------------------------------------------

## process path
process.p1 = cms.Path(process.goodMuons *
                      process.countMuons)

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
    fileName = cms.untracked.string('muTuple_Run123615.root')
)

process.outpath = cms.EndPath(process.out)
