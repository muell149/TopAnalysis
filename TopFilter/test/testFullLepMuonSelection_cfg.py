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
    '/store/mc/Spring10/TTbarJets-madgraph/AODSIM/START3X_V26_S09-v1/0016/2CB76F28-9D47-DF11-959F-003048C693E4.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
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

## remove cleaning (is applied later)
from PhysicsTools.PatAlgos.tools.coreTools import *
removeCleaning(process,False)


## test basic event selection

## filter trigger 
process.load("TopAnalysis.TopFilter.filters.TriggerFilter_cfi") 
process.filterTrigger.hltPaths  = cms.vstring('HLT_Mu9')
	  
## filter for muon and jet kinematics, muon iso and quality				     
process.load("TopAnalysis.TopFilter.sequences.fullLeptonicMuonMuonSelection_cff")

## filter for dimuon mass				     
from TopAnalysis.TopFilter.filters.DiMuonFilter_cfi import * 
process.filterDiMuonMassQCDveto       = filterMuonPair.clone()
process.filterDiMuonMassQCDveto.muons = cms.InputTag("isolatedMuons")
process.filterDiMuonMassQCDveto.Cut   = cms.vdouble(0.,12.)
process.filterDiMuonMassZveto       = filterMuonPair.clone()
process.filterDiMuonMassZveto.muons = cms.InputTag("isolatedMuons")
process.filterDiMuonMassZveto.Cut   = cms.vdouble(76.,106.)

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## std sequence to produce the ttFullLepEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttFullLepEvtBuilder_cff")

from TopQuarkAnalysis.TopEventProducers.sequences.ttFullLepEvtBuilder_cff import *		      
removeTtFullLepHypGenMatch(process)
#
setForAllTtFullLepHypotheses(process,"muons","isolatedMuons")
setForAllTtFullLepHypotheses(process,"jets","hardJets")
setForAllTtFullLepHypotheses(process,"mets","highMETs")
setForAllTtFullLepHypotheses(process,"maxNJets",3)
setForAllTtFullLepHypotheses(process,"jetCorrectionLevel","part")

process.kinSolutionTtFullLepEventHypothesis.neutrino_parameters = cms.vdouble(30.641,
                                                                              57.941,
				                                              22.344,
				                                              57.533,
				                                              22.232
								             )

## filter reconstructed events
from TopAnalysis.TopFilter.filters.FullLepHypothesesFilter_cfi import *
process.filterHypoValidity = filterFullLepHypothesis.clone()
process.filterHypoValidity.bAlgorithm      = cms.string("trackCountingHighEffBJetTags")
process.filterHypoValidity.bDiscriminator  = cms.vdouble(0)
process.filterHypoValidity.jets            = cms.InputTag("hardJets")

process.filterBtag = filterFullLepHypothesis.clone()
process.filterBtag.bAlgorithm      = cms.string("trackCountingHighEffBJetTags")
process.filterBtag.bDiscriminator  = cms.vdouble(1.7)
process.filterBtag.jets            = cms.InputTag("hardJets")


process.p1 = cms.Path(process.patDefaultSequence *
                      process.filterTrigger *
		      process.requireOneGoodMuon *		     
		      process.applyJetCleaning *
		      process.buildJets *
		      process.requireTwoGoodMuons *
		      process.requireTwoIsolatedMuons *
		      process.requireOneHardJet *
		      process.filterDiMuonMassQCDveto *     		                                      		     
		      process.filterDiMuonMassZveto *
		      process.requireMET *
		      process.requireTwoHardJets *      			    		     
                      process.makeTtFullLepEvent *	     		     
                      process.filterHypoValidity	*	     
		      process.filterBtag
                     )

