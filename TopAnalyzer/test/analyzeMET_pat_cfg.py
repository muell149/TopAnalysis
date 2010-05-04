import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of MET distributions
#-------------------------------------------------
process = cms.Process("MET")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/henderle/Spring10/TTbar_MAD/PATtuple_1.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

#-------------------------------------------------
# MET analysis
#-------------------------------------------------

## analyze MET
process.load("TopAnalysis.TopAnalyzer.METKinematics_cfi")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeMETKinematics.root')
)
process.analyzePfMETKinematics       = process.analyzeMETKinematics.clone  (srcA = 'patMETsPF' )
process.analyzePatMETKinematics      = process.analyzeMETKinematics.clone  (srcA = 'patMETs'   )
process.analyzePatMETMuonCorrelation = process.analyzeMETCorrelations.clone(srcA = 'patMETs', srcB = 'selectedPatMuons' )

process.p1 = cms.Path(process.analyzePatMETKinematics*
                      process.analyzePfMETKinematics *
                      process.analyzePatMETMuonCorrelation )
