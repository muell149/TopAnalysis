import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for tqaflayer1 & 2 production from
# fullsim for semi-leptonic ttbar events 
#-------------------------------------------------
process = cms.Process("Selection")

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
    '/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_7TeV_AODSIM-v1/0005/6CA57A3D-EB9C-DE11-B3DB-002481DE4A28.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_3XY_V25::All')


## eventWeight
process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")

## std sequence for tqaf layer1
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.coreTools import *
removeSpecificPATObjects(process,
                         ['Photons', 'Taus'],
                         outputInProcess=False)
removeCleaning(process,
               outputInProcess=False)

from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process, 
                    cms.InputTag('antikt5CaloJets'),   
                    doJTA            = True,            
                    doBTagging       = True,            
                    jetCorrLabel     = ('AK5','Calo'),  
                    doType1MET       = True,
                    genJetCollection = cms.InputTag("antikt5GenJets"),
                    doJetID          = False,
                    jetIdLabel       = "antikt5"
                    )

process.patJetCorrFactors.corrSample = 'Summer09_7TeV'
process.patJetCorrFactors.sampleType = "ttbar"

from PhysicsTools.PatAlgos.tools.muonTools import addMuonUserIsolation
addMuonUserIsolation(process)

## test basic event selection
process.load("TopAnalysis.TopFilter.filters.TriggerFilter_cfi")
process.load("TopAnalysis.TopFilter.sequences.fullLeptonicMuonMuonSelection_cff")
process.load("TopAnalysis.TopFilter.filters.DiMuonMassFilter_cfi")
process.filterDiMuonMass.muons = 'isolatedMuons'
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttFullLepEvtBuilder_cff")
process.kinSolutionTtFullLepEventHypothesis.muons = cms.InputTag("isolatedMuons")
process.kinSolutionTtFullLepEventHypothesis.jets = cms.InputTag("tightJets")
process.kinSolutionTtFullLepEventHypothesis.jetCorrectionLevel = cms.string("part")
process.ttFullLepHypKinSolution.muons = cms.InputTag("isolatedMuons")
process.ttFullLepHypKinSolution.jets = cms.InputTag("tightJets")
process.ttFullLepHypKinSolution.jetCorrectionLevel = cms.string("part")
process.ttFullLepHypGenMatch.muons = cms.InputTag("isolatedMuons")
process.ttFullLepHypGenMatch.jets = cms.InputTag("tightJets")
process.ttFullLepHypGenMatch.jetCorrectionLevel = cms.string("part")

process.load("TopAnalysis.TopFilter.filters.FullLepHypothesesFilter_cfi")



process.p1 = cms.Path(process.eventWeight *
                      process.patDefaultSequence *
                      process.filterTrigger *
		      process.buildCollections *
                      process.fullLeptonicMuonMuonSelection *
		      process.filterDiMuonMass *
		      process.makeGenEvt *
                      process.makeTtFullLepEvent *
		      process.filterFullLepHypothesis
                     )
