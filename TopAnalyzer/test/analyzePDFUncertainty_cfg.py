import FWCore.ParameterSet.Config as cms

## ---
##   use this file to test the PDFUncertainty.cc module
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
    '/store/user/henderle/TTJets_TuneZ2_7TeV-madgraph-tauola/PAT_FALL10HH/d11bd92e226f3f64b5cff39b069a59bb/fall10MC_2_1_Jua.root',
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
    fileName = cms.string('analyzePDFUncertainty_test.root')
)

## ---
##    load PDF uncertainty Analyszer
## ---

## get PDF uncertainties
process.load("TopAnalysis.TopAnalyzer.PDFUncertainty_cfi")
process.analyzePDFUncertainty = process.analyzePDFUncertainty.clone()

## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
    ## apply the analyzer
    process.analyzePDFUncertainty          
    )
