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
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/user/snaumann/sync/patTuple_afterStep2_1.root'
    #'/store/mc/Summer09/TTbar/GEN-SIM-RECO/MC_3XY_V25_preproduction-v1/0003/84F29E99-202C-DF11-810C-00237DA14F92.root'
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
process.GlobalTag.globaltag = cms.string('START3X_V20::All')

#-------------------------------------------------
# trigger
#-------------------------------------------------

from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.step1 = hltHighLevel.clone(TriggerResultsTag = "TriggerResults::HLT8E29", HLTPaths = ["HLT_Mu9"])

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
                         ['Photons', 'Taus'],
                         outputInProcess=False)
removeCleaning(process,
               outputInProcess=False)

## use the correct jet energy corrections
process.patJetCorrFactors.corrSample = "Summer09_7TeV_ReReco332"

#-------------------------------------------------
# muon selection
#-------------------------------------------------

process.load("TopQuarkAnalysis.TopObjectProducers.MuonImpactParameterSelector_cfi")
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
process.isolatedMuons010 = selectedPatMuons.clone(src = 'impactParameterMuons',
                                                  cut =
                                                  'isGlobalMuon &'
                                                  'pt > 20. &'
                                                  'abs(eta) < 2.1 &'
                                                  '(trackIso+caloIso)/pt < 0.1 &'
                                                  'innerTrack.numberOfValidHits >= 11 &'
                                                  'globalTrack.normalizedChi2 < 10.0 &'
                                                  'isolationR03.emVetoEt < 4 &'
                                                  'isolationR03.hadVetoEt < 6'
                                                 )
process.isolatedMuons005 = selectedPatMuons.clone(src = 'isolatedMuons010',
                                                  cut = '(trackIso+caloIso)/pt < 0.05'
                                                  )
process.vetoMuons = selectedPatMuons.clone(src = 'selectedPatMuons',
                                           cut =
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
                                                   'abs(eta) < 2.4 &'
                                                   '(trackIso+caloIso)/et <  0.2'
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
# final selection paths
#-------------------------------------------------

process.looseSelection = cms.Path(process.step1 *
                                  process.step2 *
                                  #process.patDefaultSequence *
                                  process.impactParameterMuons *
                                  process.isolatedMuons010 *
                                  process.step3b *
                                  process.vetoMuons *
                                  process.step4 *
                                  process.vetoElectrons *
                                  process.step5 *
                                  process.goodJets *
                                  process.step6a *
                                  process.step6b *
                                  process.step6c
                                  )

process.tightSelection = cms.Path(process.step1 *
                                  process.step2 *
                                  #process.patDefaultSequence *
                                  process.impactParameterMuons *
                                  process.isolatedMuons010 *
                                  process.isolatedMuons005 *
                                  process.step3a *
                                  process.analyzeEventBasics *
                                  process.vetoMuons *
                                  process.step4 *
                                  process.vetoElectrons *
                                  process.step5 *
                                  process.goodJets *
                                  process.step6a *
                                  process.step6b *
                                  process.step6c *
                                  process.step7
                                  )

#-------------------------------------------------
# register TFileService
#-------------------------------------------------

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('synchronizationExercise.root')
)

#-------------------------------------------------
# optional: write patTuple
#-------------------------------------------------
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
