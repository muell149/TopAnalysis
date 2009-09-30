import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of jet energy corrections
#-------------------------------------------------
process = cms.Process("JetEnergyCorrections")

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
# top analysis
#-------------------------------------------------

# produce jet collection to be used for further analysis
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import selectedLayer1Jets

## produce generated top event
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## produce reconstructed top events
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")

## analyze jet energy corrections
process.load("TopAnalysis.TopAnalyzer.JetEnergyCorrections_cfi")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJetEnergyCorrections.root')
)

process.p1 = cms.Path(process.makeGenEvt *
                      process.makeTtSemiLepEvent *
                      process.analyzeJetEnergyCorrections
                      )
