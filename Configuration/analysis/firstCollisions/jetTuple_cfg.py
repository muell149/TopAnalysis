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
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_1.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_10.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_11.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_12.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_13.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_14.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_15.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_16.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_17.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_18.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_19.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_2.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_20.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_21.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_22.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_23.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_24.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_25.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_26.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_3.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_4.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_5.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_6.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_7.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_8.root',
    '/store/user/snaumann/firstCollisions/patTuple_Run123909_9.root'
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
process.goodJets = selectedPatJets.clone(src = 'selectedPatJets',
                                            cut =
                                            'abs(eta) < 5 & pt > 20. &'
                                            '0.01 < emEnergyFraction &'
                                            '0.99 > emEnergyFraction'
                                            )

## select events with good jets
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
process.countJets = countPatJets.clone(src = 'goodJets',
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
    fileName = cms.untracked.string('jetTuple_Run123909.root')
)

process.outpath = cms.EndPath(process.out)
