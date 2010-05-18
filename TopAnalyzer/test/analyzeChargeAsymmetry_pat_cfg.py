import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file creating histograms needed for the
# determination of the charge asymmetry parameter
#-------------------------------------------------
process = cms.Process("p1")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 20

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    #'/store/user/henderle/Spring10/TTbar_NLO/PATtuple_1.root'
    '/store/user/henderle/Spring10/WJets_MAD/PATtuple_1.root'
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
# charge asymmetry analysis
#-------------------------------------------------

## plots to derive charge asymmetry parameter
process.load("TopAnalysis.TopAnalyzer.ChargeAsymmetry_cfi")
process.analyzeChargeAsymmetryMuons = process.analyzeChargeAsymmetry.clone(src = 'genParticles',
                                                                           analyze = cms.PSet(index = cms.int32(-1),
                                                                                              lepton= cms.int32(13)))

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeChargeAsymmetry.root')
)

process.p1 = cms.Path(process.analyzeChargeAsymmetryMuons)
