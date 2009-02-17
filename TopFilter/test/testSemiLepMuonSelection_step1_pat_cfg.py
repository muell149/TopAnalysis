import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for semi-leptonic ttbar event
# selection step1
#-------------------------------------------------
process = cms.Process("Step1")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
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
    wantSummary = cms.untracked.bool(False)
)

#-------------------------------------------------
# semi-leptonic ttbar selection step1
#-------------------------------------------------

## test basic event selection
process.load("TopAnalysis.TopFilter.sequences.semiLepMuonSelection_step1_cff")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('semiLepMuonSelection_step1.root')
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('patTuple_semiLepMuonSelection_step1.root')
)

process.p1 = cms.Path(process.selectSemiLepMuon *
                      process.out
                      )
