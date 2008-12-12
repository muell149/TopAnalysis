import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.categories.append('TtSemiLepKinFitter')
#process.MessageLogger.categories.append('KinFitter')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    default             = cms.untracked.PSet( limit = cms.untracked.int32( 0) ),
    TtSemiLeptonicEvent = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
    TtSemiLepKinFitter  = cms.untracked.PSet( limit = cms.untracked.int32(-1) )
#    KinFitter           = cms.untracked.PSet( limit = cms.untracked.int32(-1) )
)

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #PAT test sample
    'file:/afs/cern.ch/cms/PRS/top/cmssw-data/relval200-for-pat-testing/FullSimTTBar-2_1_X_2008-07-08_STARTUP_V4-AODSIM.100.root'
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
process.GlobalTag.globaltag = cms.string('STARTUP_V7::All')

## Magnetic field now needs to be in the high-level py
process.load("Configuration.StandardSequences.MagneticField_cff")

#-------------------------------------------------
# tqaf configuration
#-------------------------------------------------

## std sequence for tqaf layer1
process.load("TopQuarkAnalysis.TopObjectProducers.tqafLayer1_cff")
process.p0 = cms.Path(process.tqafLayer1)

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced
## with 22X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
run22XonSummer08AODSIM(process)

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## std sequence to produce the ttSemiLepEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
process.ttSemiLepEvent.verbosity = cms.int32(1)
## change maximum number of jets taken into account per event (default: 4)
#process.ttSemiLepHypGeom              .maxNJets = cms.int32(5)
#process.ttSemiLepHypMaxSumPtWMass     .maxNJets = cms.int32(5)
#process.ttSemiLepHypWMassMaxSumPt     .maxNJets = cms.int32(5)
#process.ttSemiLepJetPartonMatch       .maxNJets = cms.int32(5)
#process.findTtSemiLepJetCombMVA       .maxNJets = cms.int32(5)
#process.kinFitTtSemiLepEventHypothesis.maxNJets = cms.int32(5)
## change maximum number of jet combinations taken into account per event (default: 1)
#process.findTtSemiLepJetCombMVA       .maxNComb = cms.int32(-1)
#process.kinFitTtSemiLepEventHypothesis.maxNComb = cms.int32(-1)

#-------------------------------------------------
# tqaf configuration
#-------------------------------------------------

## add event weight information
from TopAnalysis.TopUtils.EventWeightPlain_cfi import *
process.eventWeight = eventWeight

## analyze hypotheses
process.load("TopAnalysis.TopAnalyzer.SemiLepHypothesesAnalyzer_cff")

#-------------------------------------------------
# file service for output
#-------------------------------------------------

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeSemiLepHypotheses.root')
)

#-------------------------------------------------
# paths
#-------------------------------------------------

process.p2 = cms.Path(process.tqafLayer1 *
                      process.makeGenEvt *
                      process.makeTtSemiLepEvent *
                      process.eventWeight *
                      process.analyzeAllSemiLepHypotheses
                      )
