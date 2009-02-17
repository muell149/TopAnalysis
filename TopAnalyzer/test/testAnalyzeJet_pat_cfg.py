import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected jets
# quantities
#-------------------------------------------------
process = cms.Process("Jets")

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
# jets analysis
#-------------------------------------------------

## analyze muons
process.load("TopAnalysis.TopAnalyzer.JetsAnalyzer_cfi")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJets.root')
)

process.p1 = cms.Path(process.analyzeJets)
