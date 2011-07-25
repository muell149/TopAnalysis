import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

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

process.PUControlDistributions = cms.EDAnalyzer('PUControlDistributionsAnalyzer',                                     
                                                PUSource                = cms.InputTag("addPileupInfo"),
                                                PVertexSource           = cms.InputTag("offlinePrimaryVertices"),
                                                PUEventWeightSource     = cms.InputTag("eventWeightPU","eventWeightPU"),
                                                PUEventWeightUpSource   = cms.InputTag("eventWeightPU","eventWeightPUUp"),
                                                PUEventWeightDownSource = cms.InputTag("eventWeightPU","eventWeightPUDown")                                                
                                                )

process.p = cms.Path(process.PUControlDistributions)
