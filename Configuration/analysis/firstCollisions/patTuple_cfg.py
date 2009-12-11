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
    limit = cms.untracked.int32(-1)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    ## files from Run 123801
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/123/801/10F05FA3-41E4-DE11-89C9-0030487D1BCC.root',
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/123/801/2E275957-49E4-DE11-B903-003048D37538.root',
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/123/801/30FECAA5-3CE4-DE11-9648-001617E30D52.root',
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/123/801/40953857-49E4-DE11-8C7B-000423D94990.root', ##!!!
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/123/801/AEC3C258-49E4-DE11-8512-003048D37514.root',
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/123/801/EAB34A72-3FE4-DE11-848C-001617C3B778.root'
    )
)
#process.source.firstRun = cms.untracked.uint32(123615)
#process.source.lastRun  = cms.untracked.uint32(123615)

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
process.GlobalTag.globaltag = cms.string('GR09_P_V7::All')

#-------------------------------------------------
# trigger configuration
#-------------------------------------------------

process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)

## select the "physics bits"
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41)')

#-------------------------------------------------
# pat configuration
#-------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## use the correct jet energy corrections
process.jetCorrFactors.corrSample = "900GeV"
#process.jetCorrFactors.corrSample = "2360GeV"

## switch off MC matching
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, 'All')

## add jet collections
from PhysicsTools.PatAlgos.tools.jetTools import *

#addJetCollection(process,cms.InputTag('JetPlusTrackZSPCorJetIcone5'),
#                 'JPTc',
#                 doJTA        = True,
#                 doBTagging   = True,
#                 jetCorrLabel = ('IC5','JPT'),
#                 doType1MET   = True,
#                 doL1Counters = False,
#                 genJetCollection = cms.InputTag("iterativeCone5GenJets")
#                 )

#addJetCollection(process,cms.InputTag('sisCone5CaloJets'),
#                 'SC5',
#                 doJTA        = True,
#                 doBTagging   = True,
#                 jetCorrLabel = ('SC5','Calo'),
#                 doType1MET   = True,
#                 doL1Counters = False,
#                 genJetCollection=cms.InputTag("sisCone5GenJets")
#                 )

#-------------------------------------------------
# private Uni Hamburg analysis code
#-------------------------------------------------

## add event weight information
process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")
process.wght = cms.Path(process.eventWeight)   

## basic event selection
#process.load("TopAnalysis.TopFilter.sequences.semiLepMuonSelection_step0_cff")
#process.semiLepMuonSelection = cms.Path(process.slmFilterFullMon )   

#process.load("TopAnalysis.TopFilter.sequences.fullLepElMuSelection_step0_cff")
#process.fullLepElMuSelection = cms.Path(process.flemFilterFullMon)

#process.load("TopAnalysis.TopFilter.sequences.fullLepMuonSelection_step0_cff")
#process.fullLepMuonSelection = cms.Path(process.flmmFilterFullMon)

## register TFileService
#process.TFileService = cms.Service("TFileService",
#    fileName = cms.string('commonTemplate.root')
#)

#-------------------------------------------------
# process output:
# - first the event selection is defined: only
# those events that have passed the full
# production path are selected and written to file
# - for the event content, ALL objects
# are dropped before the patTuple content is added
#-------------------------------------------------

## process path
process.p1 = cms.Path(process.hltLevel1GTSeed *
                      process.patDefaultSequence)

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
    fileName = cms.untracked.string('patTuple_Run123909.root')
)
## save pat output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentTriggerMatch
process.out.outputCommands += patEventContentNoLayer1Cleaning
process.out.outputCommands += ["keep *_selectedLayer1Jets*_*_*",
                               "keep *_layer1METs*_*_*"]
## and products from our UserCode
process.out.outputCommands += ["keep *_eventWeight_*_*"]
## drop stuff which is not needed
#process.out.outputCommands += ["drop *_towerMaker_*_*"]

process.outpath = cms.EndPath(process.out)
