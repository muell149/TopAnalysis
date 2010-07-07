import FWCore.ParameterSet.Config as cms

# analyse jet quantities
process = cms.Process("test")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    ## add your favourite file here
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_1_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_2_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_3_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_4_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_5_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_6_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_7_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_8_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_9_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_10_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_11_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_12_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_13_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_14_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_15_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_16_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_17_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_18_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_19_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_20_1.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",  
            fileName = cms.string('analyzeJetQuality_test.root')
)

## setup the jet selection collection
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")

process.goodJets   = process.selectedPatJets.clone(src = 'selectedPatJets',
                                                   cut = 'abs(eta) < 2.4 & pt > 30.')

process.goodJetsPF = process.selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                                   cut = 'abs(eta) < 2.4 & pt > 20.')

## ---
##    MONITOR JET QUALITY
## ---

## jet quality analyzer
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")

## collect quality analyzers
process.caloJetQuality = process.analyzeJetQuality.clone(src = 'goodJets')
process.pfJetQuality   = process.analyzeJetQuality.clone(src = 'goodJetsPF')

## analyze the quality of the jets in the event
process.p1 = cms.Path(process.goodJets        *
                      process.caloJetQuality  +
                      process.goodJetsPF      *
                      process.pfJetQuality
                      )
