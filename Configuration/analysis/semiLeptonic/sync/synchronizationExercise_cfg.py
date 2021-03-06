import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the synchronization exercise
# in the muon+jets channel
#-------------------------------------------------

process = cms.Process("SYNC-ON-PAT")

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/user/snaumann/sync/patTuple_afterStep2_1_1.root'
    #'/store/mc/Spring10/TTbarJets-madgraph/AODSIM/START3X_V26_S09-v1/0011/40932C57-1247-DF11-8E83-0030487D5059.root'
    )
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
process.GlobalTag.globaltag = cms.string('START36_V9::All')

#-------------------------------------------------
# trigger
#-------------------------------------------------

from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.step1 = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::REDIGI", HLTPaths = ["HLT_Mu9"])

#-------------------------------------------------
# vertex filter
#-------------------------------------------------

# vertex filter
process.step2 = cms.EDFilter("VertexSelector",
                             src = cms.InputTag("offlinePrimaryVertices"),
                             cut = cms.string("!isFake && ndof > 4 && abs(z) < 15 && position.Rho < 2"),
                             filter = cms.bool(True),
                             )

#-------------------------------------------------
# pat configuration
#-------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## remove MC matching, photons, taus and cleaning from PAT default sequence
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, ['All'])

removeSpecificPATObjects(process,
                         ['Photons','Taus'],
                         outputInProcess=False)
removeCleaning(process,
               outputInProcess=False)

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run36xOn35xInput
run36xOn35xInput(process)

## use the correct jet energy corrections
process.patJetCorrFactors.corrSample = "Spring10"

#-------------------------------------------------
# muon selection
#-------------------------------------------------

#calculate impact parameter w.r.t beam spot (instead of primary vertex)
process.patMuons.usePV = False

from PhysicsTools.PatAlgos.cleaningLayer1.muonCleaner_cfi import *
process.isolatedMuons010 = cleanPatMuons.clone(preselection =
                                               'isGlobalMuon & isTrackerMuon &'
                                               'pt > 20. &'
                                               'abs(eta) < 2.1 &'
                                               '(trackIso+caloIso)/pt < 0.1 &'
                                               'innerTrack.numberOfValidHits > 10 &'
                                               'globalTrack.normalizedChi2 < 10.0 &'
                                               'globalTrack.hitPattern.numberOfValidMuonHits > 0 &'
                                               'abs(dB) < 0.02'
                                               )
process.isolatedMuons010.checkOverlaps = cms.PSet(
    jets = cms.PSet(src       = cms.InputTag("goodJets"),
                    algorithm = cms.string("byDeltaR"),
                    preselection        = cms.string(""),
                    deltaR              = cms.double(0.3),
                    checkRecoComponents = cms.bool(False),
                    pairCut             = cms.string(""),
                    requireNoOverlaps   = cms.bool(True),
                    )
    )
process.isolatedMuons005 = cleanPatMuons.clone(src = 'isolatedMuons010',
                                               preselection = '(trackIso+caloIso)/pt < 0.05'
                                               )
process.vetoMuons = cleanPatMuons.clone(preselection =
                                        'isGlobalMuon &'
                                        'pt > 10. &'
                                        'abs(eta) < 2.5 &'
                                        '(trackIso+caloIso)/pt < 0.2'
                                        )

from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
process.step3a = countPatMuons.clone(src = 'isolatedMuons005', minNumber = 1, maxNumber = 1)
process.step3b = countPatMuons.clone(src = 'isolatedMuons010', minNumber = 1, maxNumber = 1)
process.step4  = countPatMuons.clone(src = 'vetoMuons', maxNumber = 1)

#-------------------------------------------------
# electron selection
#-------------------------------------------------

from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *
process.vetoElectrons = selectedPatElectrons.clone(src = 'selectedPatElectrons',
                                                   cut =
                                                   'et > 15. &'
                                                   'abs(eta) < 2.5 &'
                                                   '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et <  0.2'
                                                   )

from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *
process.step5  = countPatMuons.clone(src = 'vetoElectrons', maxNumber = 0)

#-------------------------------------------------
# jet selection
#-------------------------------------------------

from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
process.goodJets = selectedPatJets.clone(src = 'selectedPatJets',
                                         cut =
                                         'pt > 30. &'
                                         'abs(eta) < 2.4 &'
                                         'emEnergyFraction > 0.01 &'
                                         'jetID.n90Hits > 1 &'
                                         'jetID.fHPD < 0.98'
                                         )

from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
process.step6a = countPatJets.clone(src = 'goodJets', minNumber = 1)
process.step6b = countPatJets.clone(src = 'goodJets', minNumber = 2)
process.step6c = countPatJets.clone(src = 'goodJets', minNumber = 3)
process.step7  = countPatJets.clone(src = 'goodJets', minNumber = 4)

#-------------------------------------------------
# dummy analyzer
#-------------------------------------------------

process.load("TopAnalysis.TopAnalyzer.EventBasicsAnalyzer_cfi")

#-------------------------------------------------
# TtSemiLeptonicEvent
#-------------------------------------------------

process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")

from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import *
addTtSemiLepHypotheses(process, ["kMaxSumPtWMass"])
removeTtSemiLepHypGenMatch(process)
setForAllTtSemiLepHypotheses(process, "jets", "goodJets")
setForAllTtSemiLepHypotheses(process, "maxNJets", -1)

#process.load("TopQuarkAnalysis.Examples.HypothesisAnalyzer_cfi")

#process.load("TopQuarkAnalysis.Examples.TopMuonAnalyzer_cfi")

#-------------------------------------------------
# final selection paths
#-------------------------------------------------

process.looseSequence = cms.Sequence(process.step1 *
                                     process.step2 *
                                     #process.patDefaultSequence *
                                     process.goodJets *
                                     process.isolatedMuons010 *
                                     process.step3b *
                                     #process.analyzeMuon *
                                     process.vetoMuons *
                                     process.step4 *
                                     process.vetoElectrons *
                                     process.step5 *
                                     process.step6a *
                                     process.step6b *
                                     process.step6c #*
                                     #process.analyzeEventBasics
                                     )

process.tightSequence = cms.Sequence(process.step1 *
                                     process.step2 *
                                     #process.patDefaultSequence *
                                     process.goodJets *
                                     process.isolatedMuons010 *
                                     process.isolatedMuons005 *
                                     process.step3a *
                                     process.vetoMuons *
                                     process.step4 *
                                     process.vetoElectrons *
                                     process.step5 *
                                     process.step6a *
                                     process.step6b *
                                     process.step6c *
                                     process.step7 #*
                                     #process.makeTtSemiLepEvent *
                                     #process.analyzeHypothesis
                                     )

process.looseSelection = cms.Path(process.looseSequence)

process.tightSelection = cms.Path(process.tightSequence)

##-------------------------------------------------
## register TFileService
##-------------------------------------------------
#
#process.TFileService = cms.Service("TFileService",
#    fileName = cms.string('synchronizationExercise.root')
#)
#
##-------------------------------------------------
## optional: write patTuple
##-------------------------------------------------
#
#process.patTuple = cms.Path(process.step1 *
#                            process.step2 *
#                            process.patDefaultSequence
#                            )
#
### define event selection
#process.EventSelection = cms.PSet(
#    SelectEvents = cms.untracked.PSet(
#        SelectEvents = cms.vstring('patTuple')
#    )
#)
#
### configure output module
#process.out = cms.OutputModule("PoolOutputModule",
#    process.EventSelection,
#    outputCommands = cms.untracked.vstring('drop *'),
#    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
#    fileName = cms.untracked.string('patTuple_afterStep2.root')
#)
#
### save pat output
#from PhysicsTools.PatAlgos.patEventContent_cff import *
#process.out.outputCommands += patTriggerEventContent
#process.out.outputCommands += patExtraAodEventContent
#process.out.outputCommands += patEventContentTriggerMatch
#process.out.outputCommands += patEventContentNoCleaning
#process.out.outputCommands += ["keep *_selectedPatJets*_*_*",
#                               "keep *_patMETs*_*_*"]
#
#process.outpath = cms.EndPath(process.out)
