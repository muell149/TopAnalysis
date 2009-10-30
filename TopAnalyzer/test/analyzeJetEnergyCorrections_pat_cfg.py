import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of jet energy corrections
#-------------------------------------------------
process = cms.Process("JetEnergyCorrections")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.categories.append('JetPartonMatching')
process.MessageLogger.cerr.TtSemiLeptonicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)
process.MessageLogger.cerr.JetPartonMatching = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)

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
    wantSummary = cms.untracked.bool(True)
)

#-------------------------------------------------
# event selection
#-------------------------------------------------

## select events that were generated in the semileptonic muon channel
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.decaySubset.fillMode = "kME" # use the status 3 partons from the hard process (Matrix Element)
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff")
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = False

## apply realistic event selection
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import disableCountFilter
disableCountFilter(process.bottomJetSelection)

#-------------------------------------------------
# top analysis
#-------------------------------------------------

## analyze jet energy corrections
process.load("TopAnalysis.TopAnalyzer.JetEnergyCorrectionsAnalyzer_cff")

## !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
## this will make all parts of this analysis that work with GenJets meaningless
## but it is needed since no GenJet collection was saved into the old PAT tuple
process.ttSemiLepGenJetPartonMatch.jets   = "selectedLayer1Jets"
process.analyzeJetEnergyGenMatch_raw .genJets = "selectedLayer1Jets"
process.analyzeJetEnergyGenMatch_off .genJets = "selectedLayer1Jets"
process.analyzeJetEnergyGenMatch_rel .genJets = "selectedLayer1Jets"
process.analyzeJetEnergyGenMatch_abs .genJets = "selectedLayer1Jets"
process.analyzeJetEnergyGenMatch_emf .genJets = "selectedLayer1Jets"
process.analyzeJetEnergyGenMatch_had .genJets = "selectedLayer1Jets"
process.analyzeJetEnergyGenMatch_ue  .genJets = "selectedLayer1Jets"
process.analyzeJetEnergyGenMatch_part.genJets = "selectedLayer1Jets"
## !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

## printout for debugging
process.ttSemiLepJetPartonMatch   .verbosity = 1
process.ttSemiLepGenJetPartonMatch.verbosity = 1
process.ttSemiLepEventAbs         .verbosity = 1

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJetEnergyCorrections.root')
)

process.p1 = cms.Path(process.makeGenEvt *
                      process.ttSemiLeptonicFilter *
                      process.hltMu9 *
                      process.semiLeptonicSelection *
                      process.semiLeptonicEvents *
                      process.makeJetEnergyCorrectionsAnalysis
                      )
