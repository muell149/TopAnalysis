import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
process.MessageLogger.categories.append('TtFullHadronicEvent')
process.MessageLogger.cerr.TtFullHadronicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
)

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0009/F651D737-75B7-DE11-BDD4-001D09F2512C.root'
    '/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_AODSIM-v1/0024/068F7867-2C88-DE11-B3C2-001F29C9A5AE.root'
     ),
     skipEvents = cms.untracked.uint32(0)                            
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V9::All')

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *

# run the 3.3.x software on Summer 09 MC from 3.1.x:
#   - change the name from "ak" (3.3.x) to "antikt) (3.1.x)
#   - run jet ID (not run in 3.1.x)
run33xOn31xMC( process,
               jetSrc = cms.InputTag("antikt5CaloJets"),
               jetIdTag = "antikt5"
               )

restrictInputToAOD31X(process)

## sequences for ttGenEvent and TtFullHadronicEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff")
## enable additional per-event printout from the TtFullHadronicEvent
#process.ttFullHadEvent.verbosity = 1
## change jet-parton matching algorithm
#process.ttFullHadJetPartonMatch.algorithm = "unambiguousOnly"

#from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *
#setForAllTtFullHadHypotheses(process, "maxNJets", 6)

#from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *
#setForAllTtFullHadHypotheses(process, "jetCorrectionLevel", "part")

## choose which hypotheses to produce
##from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import addTtFullHadHypotheses
##addTtFullHadHypotheses(process,
##                       ["kGenMatch", "kKinFit"]
##                       )
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import addTtFullHadHypotheses
addTtFullHadHypotheses(process,
                       ["kKinFit"]
                       )

## remove genMatch hypothesis from the process
##from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import removeTtFullHadHypGenMatch
##removeTtFullHadHypGenMatch(process)

## load HypothesisAnalyzer
process.load("TopAnalysis.TopAnalyzer.FullHadHypothesisAnalyzer_cff")

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeFullHadTopHypothesis.root')
)

## end path   
process.path = cms.Path(process.patDefaultSequence *
                        process.makeGenEvt *
                        process.makeTtFullHadEvent *
                        process.analyzeHypotheses
                        )
