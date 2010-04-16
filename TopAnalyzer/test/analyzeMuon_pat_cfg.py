import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected muon
# quantities
#-------------------------------------------------
process = cms.Process("Muon")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
## process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    "/store/user/rwolf/ttbar09/patTuple_all_0_ttbar09.root"
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
# muon analysis
#-------------------------------------------------

## analyze muons
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")
process.load("TopAnalysis.TopAnalyzer.MuonResolution_cfi")

## reconfigure for olf pat tuples
process.analyzeMuonQuality.src = "selectedLayer1Muons"    
process.analyzeMuonKinematics.src = "selectedLayer1Muons"
process.analyzeMuonResolution.src = "selectedLayer1Muons"

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeMuon_rec.root')
)

process.p1 = cms.Path(process.analyzeMuonQuality    +
                      process.analyzeMuonKinematics +
                      process.analyzeMuonResolution
                      )
