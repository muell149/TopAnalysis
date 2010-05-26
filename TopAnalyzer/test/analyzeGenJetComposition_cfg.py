import FWCore.ParameterSet.Config as cms

## ---
##   use this file to test the GenJetComposition.cc module
## ---


# set sequence shortcut
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1

## define input
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    #'/store/user/henderle/Spring10/WJets_MAD/PATtuple_1.root'
    '/store/user/henderle/Test/PATtuple.root'
    ),
    skipEvents = cms.untracked.uint32(0)
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeGenJetComposition_test.root')
)

## ---
##    load  GenJetComposition
## ---

## get particle content of jets with IDs
process.load("TopAnalysis.TopAnalyzer.GenJetComposition_cfi")
process.analyzeGenJetCompositionAll = process.analyzeGenJetComposition.clone()

## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
    ## apply the analyzer
    process.analyzeGenJetCompositionAll       
    )
