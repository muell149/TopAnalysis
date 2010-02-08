import FWCore.ParameterSet.Config as cms

## ---
##   use this file to test the GenParticle.cc module
## ---


# set sequence shortcut
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## define input
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(    

## add your favourite file here

      '/store/user/henderle/samples/Zjets_madgraph_10TeV/PATtuple_11.root'
    # '/store/user/henderle/samples/Wjets_madgraph_10TeV/PATtuple_1.root'
    # '/store/user/rwolf/ttbar09/patTuple_sig_0_ttbarx09.root'
    )
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
    fileName = cms.string('analyzeGenParticles_test.root')
)

## ---
##    load GenParticle
## ---

## get particle content of sample with IDs
process.load("TopAnalysis.TopAnalyzer.GenParticle_cfi")
process.analyzeGenParticles        = process.analyzeGenParticles.clone()

## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
    ## apply the analyzer
    process.analyzeGenParticles          
    )
