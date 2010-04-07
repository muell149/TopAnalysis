import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for patTuple production
#-------------------------------------------------

process = cms.Process("PAT")

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
    fileNames = cms.untracked.vstring(
        '/store/data/Commissioning10/MinimumBias/RECO/v7/000/132/440/0AA7C390-0F3C-DF11-BD65-000423D998BA.root'
    )
)
#process.source.firstRun = cms.untracked.uint32(132440)
#process.source.lastRun  = cms.untracked.uint32(132440)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('GR10_P_V2::All')

#-------------------------------------------------
# trigger configuration
#-------------------------------------------------

process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND NOT 43) OR (43 AND NOT 42))')
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
# pat configuration
#-------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## use the correct jet energy corrections
process.patJetCorrFactors.corrSample = "Summer09_7TeV_ReReco332"
## choose sample type for flavor dependent JEC
process.patJetCorrFactors.sampleType = "ttbar" ## dijet or ttbar

## switch off MC matching
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, ['All'])

## add muon and electron user isolation
from PhysicsTools.PatAlgos.tools.electronTools import addElectronUserIsolation
addElectronUserIsolation(process)
from PhysicsTools.PatAlgos.tools.muonTools import addMuonUserIsolation
addMuonUserIsolation(process)

#-------------------------------------------------
# jet selection
#-------------------------------------------------

## select jets
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
process.goodJets = selectedPatJets.clone(src = 'selectedPatJets',
                                         cut =
                                         'abs(eta) < 5 & pt > 20. &'
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
process.p1 = cms.Path(process.hltLevel1GTSeed *
                      process.monsterFilter *
                      process.vertexFilter *
                      process.patDefaultSequence *
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
    fileName = cms.untracked.string('patTuple_Run132605.root')
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
