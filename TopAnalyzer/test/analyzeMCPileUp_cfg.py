import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

# source files

process.load("TopAnalysis.Configuration.samples.Spring11_WJets_PATtuple_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000000) )

#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring())

process.getMCPUDist = cms.EDAnalyzer('MCPileUp',
                                     
                                     PUSource    = cms.InputTag("addPileupInfo"),
                                     )

process.p = cms.Path(process.getMCPUDist)
