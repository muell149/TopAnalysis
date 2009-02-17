import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected electron
# quantities
#-------------------------------------------------
process = cms.Process("Elec")

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
# elec analysis
#-------------------------------------------------

## analyze electrons
process.load("TopAnalysis.TopAnalyzer.ElecAnalyzer_cfi")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeElec.root')
)

process.p1 = cms.Path(process.analyzeElec)
