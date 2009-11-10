import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of jet combinatorics
#-------------------------------------------------
process = cms.Process("JetCombinatorics")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('topFilter')
process.MessageLogger.cerr.topFilter = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)
process.MessageLogger.categories.append('JetPartonMatching')
process.MessageLogger.cerr.JetPartonMatching = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.cerr.TtSemiLeptonicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)
process.MessageLogger.categories.append('JetCombinatoricsAnalyzer')
process.MessageLogger.cerr.JetCombinatoricsAnalyzer = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 100

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
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_1.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_2.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_3.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_4.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_5.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_6.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_7.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_8.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_9.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_10.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_11.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_12.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_13.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_14.root',
    #'/store/user/snaumann/TTbar/notSemiLepMuon_semiLepMuonSelection/0aea8b07d63ecd458b98e1badefd7e71/patTuple_15.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#-------------------------------------------------
# top analysis
#-------------------------------------------------

# produce jet collection to be used for further analysis
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import selectedLayer1Jets
process.leadingJets = selectedLayer1Jets.clone()
process.leadingJets.src = "selectedLayer1Jets"
process.leadingJets.cut = "pt > 20 & abs(eta) < 2.4 & 0.05 < emEnergyFraction & emEnergyFraction < 0.95"

## remove events with overlapping jets
process.load("TopAnalysis.TopFilter.filters.JetOverlapEventFilter_cfi")
process.filterJetOverlapEvent.src = "leadingJets"
process.filterJetOverlapEvent.deltaR = 1.0

## produce generated top event
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## produce reconstructed top events
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
process.ttSemiLepJetPartonMatch.verbosity = 1
process.ttSemiLepEvent.verbosity = 1
from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import *
addTtSemiLepHypotheses(process,
                       ["kGeom", "kWMassMaxSumPt", "kMaxSumPtWMass", "kMVADisc", "kKinFit"]
                       )
#setForAllTtSemiLepHypotheses(process, "maxNJets", 4)
process.ttSemiLepJetPartonMatch.maxNJets = -1
setForAllTtSemiLepHypotheses(process, "jets", "leadingJets")

## GenMatch
process.ttSemiLepJetPartonMatch.algorithm = "unambiguousOnly"
process.ttSemiLepJetPartonMatch.maxDist   = 0.5
## Geom
#process.ttSemiLepHypGeom.useBTagging       = True
#process.ttSemiLepHypGeom.bTagAlgorithm     = "trackCountingHighEffBJetTags" #"trackCountingHighPurBJetTags"
#process.ttSemiLepHypGeom.minBDiscBJets     = 1.90 #2.17
#process.ttSemiLepHypGeom.maxBDiscLightJets = 3.99 #4.31
## KinFit
process.kinFitTtSemiLepEventHypothesis.maxNrIter   = 0
process.kinFitTtSemiLepEventHypothesis.constraints = [1, 2, 3, 4]

## analyze jet combinatorics
process.load("TopAnalysis.TopAnalyzer.JetCombinatorics_cfi")
process.analyzeJetCombinatoricsGenMatch      = process.analyzeJetCombinatorics.clone()
process.analyzeJetCombinatoricsGeom          = process.analyzeJetCombinatorics.clone()
process.analyzeJetCombinatoricsMaxSumPtWMass = process.analyzeJetCombinatorics.clone()
process.analyzeJetCombinatoricsWMassMaxSumPt = process.analyzeJetCombinatorics.clone()
process.analyzeJetCombinatoricsMVADisc       = process.analyzeJetCombinatorics.clone()
process.analyzeJetCombinatoricsKinFit        = process.analyzeJetCombinatorics.clone()
process.analyzeJetCombinatoricsGenMatch     .analyze.hypoKey = "kGenMatch"
process.analyzeJetCombinatoricsGeom         .analyze.hypoKey = "kGeom"
process.analyzeJetCombinatoricsMaxSumPtWMass.analyze.hypoKey = "kMaxSumPtWMass"
process.analyzeJetCombinatoricsWMassMaxSumPt.analyze.hypoKey = "kWMassMaxSumPt"
process.analyzeJetCombinatoricsMVADisc      .analyze.hypoKey = "kMVADisc"
process.analyzeJetCombinatoricsKinFit       .analyze.hypoKey = "kKinFit"

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJetCombinatorics.root')
)

process.p1 = cms.Path(process.leadingJets *
                      process.filterJetOverlapEvent *
                      process.makeGenEvt *
                      process.makeTtSemiLepEvent *
                      process.analyzeJetCombinatoricsGenMatch *
                      process.analyzeJetCombinatoricsGeom *
                      process.analyzeJetCombinatoricsMaxSumPtWMass *
                      process.analyzeJetCombinatoricsWMassMaxSumPt *
                      process.analyzeJetCombinatoricsMVADisc *
                      process.analyzeJetCombinatoricsKinFit
                      )
