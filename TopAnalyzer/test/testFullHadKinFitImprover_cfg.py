import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.categories.append('TtFullHadronicEvent')
process.MessageLogger.cerr.TtFullHadronicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
)

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/MC_31X_V9-v1/0009/F651D737-75B7-DE11-BDD4-001D09F2512C.root'
    #'/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_AODSIM-v1/0024/068F7867-2C88-DE11-B3C2-001F29C9A5AE.root'
    '/store/mc/Spring10/TTbar-mcatnlo/AODSIM/START3X_V26_S09-v2/0048/00674B32-684A-DF11-86D7-003048678CA2.root'
     ),
     skipEvents = cms.untracked.uint32(0)                            
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_3XY_V26::All')

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *

# run the 3.3.x software on Summer 09 MC from 3.1.x:
#   - change the name from "ak" (3.3.x) to "antikt) (3.1.x)
#   - run jet ID (not run in 3.1.x)
#run33xOn31xMC( process,
#               jetSrc = cms.InputTag("antikt5CaloJets"),
#               jetIdTag = "antikt5"
#               )
#
#restrictInputToAOD31X(process)

## sequences for ttGenEvent and TtFullHadronicEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff")
## enable additional per-event printout from the TtFullHadronicEvent
#process.ttFullHadEvent.verbosity = 1
## change jet-parton matching algorithm
#process.ttFullHadJetPartonMatch.algorithm = "unambiguousOnly"

#from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *
#setForAllTtFullHadHypotheses(process, "maxNJets", 7)

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

process.kinFitTtFullHadEventHypothesis.bTags = 1
process.kinFitTtFullHadEventHypothesis.bTagAlgo = 'simpleSecondaryVertexBJetTags'
process.kinFitTtFullHadEventHypothesis.minBTagValueBJet = 2.02
process.kinFitTtFullHadEventHypothesis.maxBTagValueNonBJet = 3.4
process.kinFitTtFullHadEventHypothesis.jetCorrectionLevel = 'had'

## remove genMatch hypothesis from the process
##from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import removeTtFullHadHypGenMatch
##removeTtFullHadHypGenMatch(process)

## load HypothesisAnalyzer
process.load("TopAnalysis.TopAnalyzer.FullHadHypothesisAnalyzer_cff")

## load KinFitImprover
process.load("TopAnalysis.TopAnalyzer.KinFitImprover_cfi")
process.analyzeKinFitImprover_1 = process.analyzeKinFitImprover.clone( analyze = cms.PSet( comboType = cms.uint32( 1 ) ) )
process.analyzeKinFitImprover_2 = process.analyzeKinFitImprover.clone( analyze = cms.PSet( comboType = cms.uint32( 2 ) ) )
process.analyzeKinFitImprover_3 = process.analyzeKinFitImprover.clone( analyze = cms.PSet( comboType = cms.uint32( 3 ) ) )
process.analyzeKinFitImprover_4 = process.analyzeKinFitImprover.clone( analyze = cms.PSet( comboType = cms.uint32( 4 ) ) )

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('testFullHadKinFitImprover.root')
)

process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")

## end path   
process.path = cms.Path(process.genJetParticles *
                        process.ak5GenJets *
                        process.patDefaultSequence *
                        process.makeGenEvt *
                        process.makeTtFullHadEvent *
                        process.analyzeHypotheses *
                        process.analyzeKinFitImprover_1 *
                        process.analyzeKinFitImprover_2 *
                        process.analyzeKinFitImprover_3 *
                        process.analyzeKinFitImprover_4
                        )
