import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for the selection of semileptonic
# ttbar events with a muon in the final state
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
execfile("TopAnalysis/Configuration/analysis/firstCollisions/Source_Run132656_cff.py")

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

process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")

process.goodJets.cut = ('abs(eta) < 5 & pt > 20. &'
                        '0.01 < emEnergyFraction &'
                        '0.99 > emEnergyFraction &'
                        'jetID.fHPD < 0.98 &'
                        'jetID.n90Hits > 1')
process.leadingJetSelection.minNumber = 4

process.p1 = cms.Path(process.hltMu9                *
                      process.semiLeptonicSelection *
                      process.muonSelection         *
                      process.secondMuonVeto        * 
                      process.electronVeto          *
                      process.leadingJetSelection
                      )

process.p2 = cms.Path(process.semiLeptonicSelection *
                      process.muonSelection         *
                      process.secondMuonVeto        * 
                      process.electronVeto          *
                      process.leadingJetSelection
                      )

process.p3 = cms.Path(process.secondMuonVeto        * 
                      process.electronVeto          *
                      process.leadingJetSelection
                      )

process.p4 = cms.Path(process.electronVeto          *
                      process.leadingJetSelection
                      )

process.p5 = cms.Path(process.leadingJetSelection
                      )

process.p6 = cms.Path(process.leadingJetSelection *
                      process.bottomJetSelection
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
    fileName = cms.untracked.string('semiLepMuonSelection_Run132654.root')
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
