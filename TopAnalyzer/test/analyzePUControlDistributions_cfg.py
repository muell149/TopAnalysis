import FWCore.ParameterSet.Config as cms

process = cms.Process("USER")

# ================
#  Message Logger
# ================

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

# ==========================
#  Configuration of Process
# ==========================

# Process Options

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.TFileService = cms.Service("TFileService", fileName = cms.string("PUControlDistribution.root") )

#### Input Files

process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring("file:myOutputFile.root"))

#### Number of Events

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#### Load default configuration

process.load("TopAnalysis.TopAnalyzer.PUControlDistributions_cfi")

#### Define path

process.p = cms.Path(process.PUControlDistributions)
