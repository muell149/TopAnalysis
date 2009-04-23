import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for semi-leptonic ttbar event
# selection step1
#-------------------------------------------------
process = cms.Process("Step1")

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
    fileNames = cms.untracked.vstring(
    ## add your favourite file here
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    ## reduce memory consumption    
    fileMode = cms.untracked.string('FULLMERGE'),
    ## switch event summary off
    wantSummary = cms.untracked.bool(False)
)

#-------------------------------------------------
# semi-leptonic ttbar selection step1
#-------------------------------------------------

## test basic event selection
process.load("TopAnalysis.TopFilter.sequences.semiLepMuonSelection_step1_cff")
process.p0 = cms.Path(process.selectSemiLepMuon)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('selection_step1.root')
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
##  outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p0') ),
    fileName = cms.untracked.string('patTuple_semiLepMuonSelection_step1.root')
)

process.p1 = cms.Path(process.out)
