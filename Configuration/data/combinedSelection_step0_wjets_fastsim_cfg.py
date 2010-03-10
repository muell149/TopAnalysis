import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for tqaflayer1 & 2 production from
# fullsim for semi-leptonic ttbar events 
#-------------------------------------------------
process = cms.Process("PatTuple")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.categories.append('topFilter')
process.MessageLogger.cout = cms.untracked.PSet(
 INFO = cms.untracked.PSet(
   limit     = cms.untracked.int32( 0 ),
   topFilter = cms.untracked.PSet( limit = cms.untracked.int32(10) )
  )
)

process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('')
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry
process.load("Configuration.StandardSequences.Geometry_cff")

## configure conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('STARTUP_V7::All')

## Magnetic field now needs to be in the high-level py
process.load("Configuration.StandardSequences.MagneticField_cff")

#-------------------------------------------------
# tqaf configuration; if you want just to produce 
# tqafLayer2 on top of an already existing
# tqafLayer1 just comment the standard tqafLayer1
# production sequence
#-------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced
## with 22X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
run22XonSummer08AODSIM(process)

## process path
process.pat = cms.Path(process.patDefaultSequenceNoCleaning)


#-------------------------------------------------
# private uni Hamburg analysis code
#-------------------------------------------------

## add event weight information
process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")
process.wght = cms.Path(process.eventWeight)   

## test basic event selection
process.load("TopAnalysis.TopFilter.sequences.semiLepMuonSelection_step0_cff")
process.semiLepMuonSelection = cms.Path(process.slmFilterFullMon )   

process.load("TopAnalysis.TopFilter.sequences.fullLepElMuSelection_step0_cff")
process.fullLepElMuSelection = cms.Path(process.flemFilterFullMon)

process.load("TopAnalysis.TopFilter.sequences.fullLepMuonSelection_step0_cff")
process.fullLepMuonSelection = cms.Path(process.flmmFilterFullMon)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('combinedSelection_step0_PATv2_wjets_fastsim.root')
)

#-------------------------------------------------
# pat tuple event content; first ALL objects
# are dropped in this process; then patTuple
# content is added
#-------------------------------------------------

## add/change jet collection
from PhysicsTools.PatAlgos.tools.jetTools import *

addJetCollection(process,cms.InputTag('JetPlusTrackZSPCorJetIcone5'),
                 'JPTc',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('IC5','JPT'),
                 doType1MET   = True,
                 doL1Counters = True,
                 genJetCollection = cms.InputTag("iterativeCone5GenJets")
                 )

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
# process output; first the event selection is
# defined: only those events that have passed the
# full production path are selected and written
# to file; the event content has been defined
# above
#-------------------------------------------------

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('semiLepMuonSelection',
                                   'fullLepElMuSelection',
                                   'fullLepMuonSelection')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple_PATv2_wjets_fastsim.root')
)
# save PAT Layer 1 output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentTriggerMatch
process.out.outputCommands += patEventContentNoCleaning
process.out.outputCommands += ["keep *_selectedPatJets*_*_*",
                               "keep *_patMETs*_*_*"]
process.out.outputCommands += ["keep *_eventWeight_*_*"]
# drop stuff which is not needed
process.out.outputCommands += ["drop *_towerMaker_*_*"]

process.outpath = cms.EndPath(process.out)
