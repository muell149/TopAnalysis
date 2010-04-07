import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for the selection of
# fully hadronic ttbar events 
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
    fileNames = cms.untracked.vstring()
)
execfile("TopAnalysis/Configuration/analysis/firstCollisions/Source_Run132654_cff.py")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#-------------------------------------------------
# event selection
#-------------------------------------------------

process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")

process.goodJets.cut = ('abs(eta) < 2.4 & pt > 20. &'
                        '0.01 < emEnergyFraction &'
                        '0.99 > emEnergyFraction &'
                        'jetID.fHPD < 0.98 &'
                        'jetID.n90Hits > 1')

## setup good jet selection collection
process.goodJetSelection = process.countPatJets.clone(src = 'goodJets',
                                                      minNumber = 6
                                                      )

## modify tight jet selection due to change in good jet selection
process.tightLeadingJets = process.selectedPatJets.clone(src = 'goodJets',
                                                         cut = 'pt > 40'
                                                         )

## implimentation and configuration of kinematic fit
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *

addTtFullHadHypotheses(process,
                       ["kKinFit"]
                       )

removeTtFullHadHypGenMatch(process)

process.kinFitTtFullHadEventHypothesis.jets = 'goodJets'
process.kinFitTtFullHadEventHypothesis.jetCorrectionLevel = 'had'
process.kinFitTtFullHadEventHypothesis.bTags = 0
process.ttFullHadHypKinFit.jets = 'goodJets'

process.p1 = cms.Path(process.fullHadronicSelection *
                      process.fullHadronicEvents    *
                      process.makeTtFullHadEvent    *
                      process.filterKinFitQuality
                      )

process.p2 = cms.Path(process.goodJets            *
                      process.goodJetSelection    *
                      process.makeTtFullHadEvent  *
                      process.filterKinFitQuality
                      )

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p1')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('fullHadSelection_Run132654.root')
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
