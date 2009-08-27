import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for patTuple production
#-------------------------------------------------

process = cms.Process("PatTuple")

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
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_AODSIM-v1/0026/F2B6764A-6D89-DE11-8585-0018FEFAC384.root')
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V3::All')

#-------------------------------------------------
# pat configuration
#-------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## process path
process.pat = cms.Path(process.patDefaultSequence)

## restrict input to AOD
from PhysicsTools.PatAlgos.tools.coreTools import *

restrictInputToAOD(process,
                   ['All']
                   )

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

addJetCollection(process,cms.InputTag('sisCone5CaloJets'),
                 'SC5',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('SC5','Calo'),
                 doType1MET   = True,
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("sisCone5GenJets")
                 )

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
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('commonTemplate.root')
)

#-------------------------------------------------
# process output:
# - first the event selection is defined: only
# those events that have passed the full
# production path are selected and written to file
# - for the event content, ALL objects
# are dropped before the patTuple content is added
#-------------------------------------------------

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pat')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple.root')
)
# save pat output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentTriggerMatch
process.out.outputCommands += patEventContentNoLayer1Cleaning
process.out.outputCommands += ["keep *_selectedLayer1Jets*_*_*",
                               "keep *_layer1METs*_*_*"]
process.out.outputCommands += ["keep *_eventWeight_*_*"]
# drop stuff which is not needed
process.out.outputCommands += ["drop *_towerMaker_*_*"]

process.outpath = cms.EndPath(process.out)
