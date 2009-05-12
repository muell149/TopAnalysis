import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for validation of mva training for
# jet parton association
#-------------------------------------------------
process = cms.Process("TEST")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    ## test-file on cern afs
    'file:/afs/cern.ch/cms/PRS/top/cmssw-data/relval200-for-pat-testing/FullSimTTBar-2_1_X_2008-07-08_STARTUP_V4-AODSIM.100.root'
    ## one file from the madgraph ttbar sample
    #'/store/mc/Fall08/TTJets-madgraph/GEN-SIM-RECO/IDEAL_V9_v2/0000/027B51E9-8EED-DD11-9045-0015C5E9C0E1.root'
    ## one file from the tauola ttbar sample
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

## pat, ttGenEvent, ttGenEventFilter, jetPartonMatch
process.load("TopAnalysis.TopAnalyzer.SemiLepJetCombMVAStudy_muons_cff")

## switch jet collection to sisCone5CaloJets
from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process, 
        cms.InputTag('sisCone5CaloJets'), # Jet collection; must be already in the event when patDefaultSequence is executed
        doJTA=True,                       # Run Jet-Track association & JetCharge
        doBTagging=True,                  # Run b-tagging
        jetCorrLabel=('SC5','Calo'),      # Example jet correction name; set to None for no JEC
        doType1MET=True,                  # Recompute Type1 MET using these jets
        genJetCollection=cms.InputTag("sisCone5GenJets"))

## configure mva computer
process.load("TopQuarkAnalysis.TopJetCombination.TtSemiLepJetCombMVAComputer_cff")
process.findTtSemiLepJetCombMVA.jets = "selectedLayer1JetsLowPt"
process.findTtSemiLepJetCombMVA.mets = "scaledJetEnergy:layer1METs"
process.findTtSemiLepJetCombMVA.maxNJets = process.ttSemiLepJetPartonMatch.maxNJets
process.findTtSemiLepJetCombMVA.maxNComb = -1 # -1 = take all
#process.TtSemiLepJetCombMVAFileSource.ttSemiLepJetCombMVA = 'TopAnalysis/TopAnalyzer/data/SemiLepJetComb.mva'

## configure mva validator
process.load("TopAnalysis.TopAnalyzer.SemiLepJetCombMVAValidator_cfi")

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced with 22X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
run22XonSummer08AODSIM(process)
process.patDefaultSequence.remove(process.patPFCandidateIsoDepositSelection)
process.patDefaultSequence.remove(process.patPFTauIsolation)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('validateSemiLepJetCombMVA.root')
)

#-------------------------------------------------
# process path
#-------------------------------------------------

process.p = cms.Path(process.prepareSemiLepJetCombMVAStudy *
                     process.findTtSemiLepJetCombMVA *
                     process.validateSemiLepJetCombMVA)
