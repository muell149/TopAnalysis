import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for mva training for jet parton 
# association
#-------------------------------------------------
process = cms.Process("TEST")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TtSemiLepJetCombMVATrainer')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    default                    = cms.untracked.PSet( limit = cms.untracked.int32( 0) ),
    TtSemiLepJetCombMVATrainer = cms.untracked.PSet( limit = cms.untracked.int32(-1) )
)

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    ## test-file at lxplus
    'file:/afs/cern.ch/cms/PRS/top/cmssw-data/relval200-for-pat-testing/FullSimTTBar-2_1_X_2008-07-08_STARTUP_V4-AODSIM.100.root'
    ## one file from the madgraph ttbar sample at desy
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v2/0000/027B51E9-8EED-DD11-9045-0015C5E9C0E1.root'
    ## one file from the tauola ttbar sample at desy
    #'/store/mc/Summer08/TauolaTTbar/GEN-SIM-RECO/IDEAL_V9_v2/0009/0054812D-26F7-DD11-99D7-001F2908F0E4.root'
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

## configure geometry
process.load("Configuration.StandardSequences.Geometry_cff")

## configure conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('IDEAL_V9::All')

## load magnetic field
process.load("Configuration.StandardSequences.MagneticField_cff")

#-------------------------------------------------
# tqaf configuration
#-------------------------------------------------

## std sequence for tqaf layer1
process.load("TopQuarkAnalysis.TopObjectProducers.tqafLayer1_cff")
process.selectedLayer1Jets.cut  = 'et > 40. & abs(eta) < 3.0 & nConstituents > 0'
process.selectedLayer1Muons.cut = 'pt > 30. & abs(eta) < 3.0 & (trackIso+caloIso)/pt < 0.1'
process.countLayer1Jets .minNumber = 4
process.countLayer1Muons.minNumber = 1
process.countLayer1Muons.maxNumber = 1

## std sequence for ttGenEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## configure ttGenEventFilters
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff")
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = False

## configure jet parton matching
process.load("TopQuarkAnalysis.TopTools.TtSemiLepJetPartonMatch_cfi")
process.ttSemiLepJetPartonMatch.algorithm  = 3 # 1 = minSumDist, 3 = unambiguousOnly
process.ttSemiLepJetPartonMatch.useMaxDist = True
process.ttSemiLepJetPartonMatch.maxDist    = 0.3
process.ttSemiLepJetPartonMatch.maxNJets   = 5

## configure mva trainer
process.load("TopQuarkAnalysis.TopJetCombination.TtSemiLepJetCombMVATrainTreeSaver_Muons_cff")
process.trainTtSemiLepJetCombMVA.maxNJets = process.ttSemiLepJetPartonMatch.maxNJets

## make trainer looper known to the process
from TopQuarkAnalysis.TopJetCombination.TtSemiLepJetCombMVATrainTreeSaver_Muons_cff import looper
process.looper = looper

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced with 22X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
run22XonSummer08AODSIM(process)

#-------------------------------------------------
# process paths
#-------------------------------------------------

## produce tqafLayer1 and ttGenEvt
process.p0 = cms.Path(process.tqafLayer1 *
                      process.makeGenEvt)

## make jet parton match and save tree for MVA training
process.p1 = cms.Path(process.ttSemiLeptonicFilter *
                      process.ttSemiLepJetPartonMatch *
                      process.saveTtSemiLepJetCombMVATrainTree)
