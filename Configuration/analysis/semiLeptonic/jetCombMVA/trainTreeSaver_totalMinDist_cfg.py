import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for mva training for jet parton 
# association
#-------------------------------------------------
process = cms.Process("TEST")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10
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
# analysis configuration
#-------------------------------------------------

## pat, ttGenEvent, ttGenEventFilter, jetPartonMatch, etc.
process.load("TopAnalysis.TopAnalyzer.SemiLepJetCombMVAStudy_muons_cff")
# 0 = totalMinDist, 1 = minSumDist, 2 = ptOrderedMinDist, 3 = unambiguousOnly
process.ttSemiLepJetPartonMatch.algorithm  = 0
process.ttSemiLepJetPartonMatch.useMaxDist = False

## switch jet collection to sisCone5CaloJets
from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process, 
        cms.InputTag('sisCone5CaloJets'), # Jet collection; must be already in the event when patDefaultSequence is executed
        doJTA=True,                       # Run Jet-Track association & JetCharge
        doBTagging=True,                  # Run b-tagging
        jetCorrLabel=('SC5','Calo'),      # Example jet correction name; set to None for no JEC
        doType1MET=True,                  # Recompute Type1 MET using these jets
        genJetCollection=cms.InputTag("sisCone5GenJets"))

## configure mva trainer
process.load("TopQuarkAnalysis.TopJetCombination.TtSemiLepJetCombMVATrainTreeSaver_cff")
process.trainTtSemiLepJetCombMVA.jets = "selectedLayer1JetsLowPt"
process.trainTtSemiLepJetCombMVA.maxNJets = process.ttSemiLepJetPartonMatch.maxNJets

## make trainer looper known to the process
from TopQuarkAnalysis.TopJetCombination.TtSemiLepJetCombMVATrainTreeSaver_cff import looper
process.looper = looper

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced with 22X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
run22XonSummer08AODSIM(process)

#-------------------------------------------------
# process path
#-------------------------------------------------

process.p = cms.Path(process.prepareSemiLepJetCombMVAStudy *
                     process.saveTtSemiLepJetCombMVATrainTree)
