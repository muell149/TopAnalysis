import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for the selection of semileptonic
# ttbar events with a muon in the final state
#-------------------------------------------------

process = cms.Process("Selection")

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
    '/store/data/Commissioning10/MinimumBias/RECO/v9/000/135/175/C88F2894-0D5C-DF11-AC7A-000423D9517C.root'
    ),
#    skipEvents = cms.untracked.uint32(6800)
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
process.GlobalTag.globaltag = cms.string('GR_R_36X_V10::All')

#-------------------------------------------------
# trigger
#-------------------------------------------------

from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.step1 = hltHighLevel.clone(HLTPaths = ["HLT_Mu9"])

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

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run36xOn35xInput
run36xOn35xInput(process)

## use the correct jet energy corrections
process.patJetCorrFactors.corrSample = "Spring10"
process.patJetCorrFactors.sampleType = "ttbar"

#-------------------------------------------------
# muon selection
#-------------------------------------------------

#process.load("TopQuarkAnalysis.TopObjectProducers.MuonImpactParameterSelector_cfi")
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
process.isolatedMuons010 = selectedPatMuons.clone(src = 'selectedPatMuons',
                                                  cut =
                                                  'isGlobalMuon &'
                                                  'pt > 20. &'
                                                  'abs(eta) < 2.1 &'
                                                  '(trackIso+caloIso)/pt < 0.1 &'
                                                  'innerTrack.numberOfValidHits >= 11 &'
                                                  'globalTrack.normalizedChi2 < 10.0 &'
                                                  'isolationR03.emVetoEt < 4 &'
                                                  'isolationR03.hadVetoEt < 6 &'
                                                  'abs(dB/edB) < 3'
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
# final selection paths
#-------------------------------------------------

process.looseSelection = cms.Path(process.step1 *
                                  process.step2 *
                                  process.patDefaultSequence *
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
                                  process.patDefaultSequence *
                                  process.isolatedMuons010 *
                                  process.isolatedMuons005 *
                                  process.step3a *
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
# write patTuple
#-------------------------------------------------

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('looseSelection')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple_semiLepMuon_looseSelection.root')
)

## save pat output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentTriggerMatch
process.out.outputCommands += patEventContentNoCleaning
process.out.outputCommands += ["keep *_selectedPatJets*_*_*",
                               "keep *_patMETs*_*_*"]

process.outpath = cms.EndPath(process.out)
