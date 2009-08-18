import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected muon
# quantities
#-------------------------------------------------
process = cms.Process("Muon")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
## process.MessageLogger.cerr.FwkReport.reportEvery = 100


#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    "/store/user/rwolf/ttbar/patTuple_PATv2_ttbar_madgraph_1.root"
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

#-------------------------------------------------
# top analysis
#-------------------------------------------------

## produce top generated event
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff")
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True

## produce top reconstructed event
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
## process.ttSemiLepJetPartonMatch.verbosity = 1

## apply realistic event selection
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")

## analyze top quarks on generator level
process.load("TopAnalysis.TopAnalyzer.TopKinematics_gen_cfi")
process.load("TopAnalysis.TopAnalyzer.TopKinematics_rec_cfi")
process.load("TopAnalysis.TopAnalyzer.TopKinematics_match_cff")
process.analyzeSelectedTopGenKinematics = process.analyzeTopGenKinematics.clone()

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeTopQuarks.root')
)

process.p1 = cms.Path(process.makeGenEvt *
                      process.ttSemiLeptonicFilter *
                      process.makeTtSemiLepEvent *
                      process.analyzeTopGenKinematics +
                      process.analyzeTopRecKinematics +
                      process.analyzeTopRecKinematicsMatched *
                      process.semiLeptonicSelection *           ## comment this line to run w/o selection
                      process.analyzeSelectedTopGenKinematics
                      )
