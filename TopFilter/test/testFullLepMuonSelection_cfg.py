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
    '/store/mc/Spring10/TTbar/GEN-SIM-RECO/START3X_V26_S09-v1/0094/FEA115B1-AF4E-DF11-ACA5-0017A4770418.root'
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
process.GlobalTag.globaltag = cms.string('START38_V7::All')

## eventWeight
process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")


#-------------------------------------------------
# pat configuration
#-------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## use the correct jet energy corrections
process.patJetCorrFactors.corrSample = "Spring10"

## switch off MC matching
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, ['All'])

## run 361 on 35X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
run36xOn35xInput(process)

## calculate d0 wrt the beam spot
process.patMuons.usePV = False

## Add PfMET to the event content
from PhysicsTools.PatAlgos.tools.metTools import *
addPfMET(process, 'PF')

## Add particle flow jets
from PhysicsTools.PatAlgos.tools.jetTools import *
## addJetID(process, "antikt5PFJets", "pf")
addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5', 'PF'),
                 doType1MET   = False,
                 doL1Cleaning = False,
                 doL1Counters = False,
                 genJetCollection=cms.InputTag('ak5GenJets'),
                 doJetID      = True,
                ) 

## embed IsoDeposits
process.patMuons.isoDeposits = cms.PSet(
    tracker = cms.InputTag("muIsoDepositTk"),
    ecal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","ecal"),
    hcal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","hcal"),
    user    = cms.VInputTag(
                            cms.InputTag("muIsoDepositCalByAssociatorTowers","ho"),
                            cms.InputTag("muIsoDepositJets")
                           ),
    )

## embedding of jet constituents into the jets
process.patJets.embedCaloTowers = True
process.patJetsAK5PF.embedPFCandidates = True

## remove TagInfos from jets
process.patJets.addTagInfos = False
process.patJetsAK5PF.addTagInfos = False

#process.pat = cms.Path(process.patDefaultSequence)




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
