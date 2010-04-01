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
    ##contains lumi section 221
    '/store/data/Commissioning10/MinimumBias/RECO/v7/000/132/440/0AA7C390-0F3C-DF11-BD65-000423D998BA.root',
    ## contains lumi section 236
    '/store/data/Commissioning10/MinimumBias/RECO/v7/000/132/440/6A3533F5-103C-DF11-B3AA-00304879BAB2.root'
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
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39)')
# Monster Event filter
process.monsterFilter = cms.EDFilter("FilterOutScraping",
                                     applyfilter = cms.untracked.bool(True),
                                     debugOn     = cms.untracked.bool(False),
                                     numtrack    = cms.untracked.uint32(10),
                                     thresh      = cms.untracked.double(0.2)
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
                                       minNumber = 6
                                       )

process.jetSelection = cms.Sequence(process.goodJets *
                                    process.countJets)

#-------------------------------------------------
# final path
#-------------------------------------------------

## process path
process.p1 = cms.Path(process.hltLevel1GTSeed *
                      process.monsterFilter *
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
#    outputCommands = cms.untracked.vstring('drop *'),
    outputCommands = cms.untracked.vstring('keep *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple_withRECO_6jets_Run132440.root')
)

## save pat output
#from PhysicsTools.PatAlgos.patEventContent_cff import *
#process.out.outputCommands += patTriggerEventContent
#process.out.outputCommands += patExtraAodEventContent
#process.out.outputCommands += patEventContentTriggerMatch
#process.out.outputCommands += patEventContentNoCleaning
#process.out.outputCommands += ["keep *_selectedPatJets*_*_*",
#                               "keep *_patMETs*_*_*"]

process.outpath = cms.EndPath(process.out)
