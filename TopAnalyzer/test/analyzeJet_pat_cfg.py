import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected muon
# quantities
#-------------------------------------------------
process = cms.Process("Muon")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/snaumann/ttbar/patTuple_1.root'
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
# jet analysis
#-------------------------------------------------

## analyze jets
#process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")
#process.load("TopAnalysis.TopAnalyzer.JetResolution_cfi")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJet_rec.root')
)

process.p1 = cms.Path(#process.analyzeJetQuality +
                      process.analyzeJetKinematics
                      #+ process.analyzeJetResolution
                      )
