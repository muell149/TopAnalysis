import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of jet combinatorics
#-------------------------------------------------
process = cms.Process("JetCombinatorics")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('JetCombinatoricsAnalyzer')
process.MessageLogger.cerr.JetCombinatoricsAnalyzer = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
)
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_1.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_2.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_3.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_4.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_5.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_6.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_7.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_8.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_9.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_10.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_11.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_12.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_13.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_14.root',
    '/store/user/snaumann/TTbar/semiLepMuon_semiLepMuonSelection/2694332bcad71a09308e072bdb754340/patTuple_15.root'
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
# top analysis
#-------------------------------------------------

## produce generated top event
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## produce reconstructed top events
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
## process.ttSemiLepJetPartonMatch.verbosity = 1

## analyze jet combinatorics
process.load("TopAnalysis.TopAnalyzer.JetCombinatorics_cfi")
process.analyzeJetCombinatoricsGeom = process.analyzeJetCombinatorics.clone()
process.analyzeJetCombinatoricsGeom.analyze.hypoKey = "kGeom"
process.analyzeJetCombinatoricsMaxSumPtWMass = process.analyzeJetCombinatorics.clone()
process.analyzeJetCombinatoricsMaxSumPtWMass.analyze.hypoKey = "kMaxSumPtWMass"
process.analyzeJetCombinatoricsWMassMaxSumPt = process.analyzeJetCombinatorics.clone()
process.analyzeJetCombinatoricsWMassMaxSumPt.analyze.hypoKey = "kWMassMaxSumPt"

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJetCombinatorics.root')
)

process.p1 = cms.Path(process.makeGenEvt *
                      process.makeTtSemiLepEvent *
                      process.analyzeJetCombinatoricsGeom *
                      process.analyzeJetCombinatoricsMaxSumPtWMass *
                      process.analyzeJetCombinatoricsWMassMaxSumPt
                      )
