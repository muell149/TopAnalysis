import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for patTuple production
#-------------------------------------------------

process = cms.Process("SKIM")

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('topFilter')
process.MessageLogger.cerr.topFilter = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)
execfile("TopAnalysis/Configuration/analysis/firstCollisions/Source_Run132440_cff.py")

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#-------------------------------------------------
# trigger configuration
#-------------------------------------------------

#process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
#process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
#process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
#process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND NOT 43) OR (43 AND NOT 42))')
# monster event filter
process.monsterFilter = cms.EDFilter("FilterOutScraping",
                                     applyfilter = cms.untracked.bool(True),
                                     debugOn     = cms.untracked.bool(False),
                                     numtrack    = cms.untracked.uint32(10),
                                     thresh      = cms.untracked.double(0.25)
                                     )
# vertex filter
process.vertexFilter = cms.EDFilter("VertexSelector",
                                    src = cms.InputTag("offlinePrimaryVertices"),
                                    cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"),
                                    filter = cms.bool(True),
                                    )

#-------------------------------------------------
# jet selection
#-------------------------------------------------

## select jets
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
process.goodJets = selectedPatJets.clone(src = 'selectedPatJets',
                                         cut =
                                         'abs(eta) < 2.4 & pt > 20. &'
                                         '0.01 < emEnergyFraction &'
                                         '0.99 > emEnergyFraction &'
                                         'jetID.fHPD < 0.98 &'
                                         'jetID.n90Hits > 1'
                                         )

## select events with good jets
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
process.countJets = countPatJets.clone(src = 'goodJets',
                                       minNumber = 2
                                       )

process.jetSelection = cms.Sequence(process.goodJets *
                                    process.countJets)

#-------------------------------------------------
# final path
#-------------------------------------------------

## process path
process.p1 = cms.Path(#process.hltLevel1GTSeed *
                      process.monsterFilter *
                      process.vertexFilter *
                      process.jetSelection
                      )


## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p1')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple_Run132440.root')
)

## save pat output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentTriggerMatch
process.out.outputCommands += patEventContentNoCleaning
process.out.outputCommands += ["keep *_selectedPatJets*_*_*",
                               "keep *_patMETs*_*_*"]

process.outpath = cms.EndPath(process.out)
