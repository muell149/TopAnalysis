import FWCore.ParameterSet.Config as cms

## ---
##   use this file to test the PtHat.cc module
## ---


# set sequence shortcut
process = cms.Process("Analysis")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## define input
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/eschliec/Private_QCD/MC_20100325-193017/patTuple_1.root'
   ),
    skipEvents = cms.untracked.uint32(0)
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzePtHat_test.root')
)

## ---
##    load PtHat Analyszer
## ---

## get particle content of sample with IDs
process.load("TopAnalysis.TopAnalyzer.PtHat_cfi")
process.analyzePtHat = process.analyzePtHat.clone()

## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
    ## apply the analyzer
    process.analyzePtHat          
    )
