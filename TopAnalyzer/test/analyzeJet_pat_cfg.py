import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected muon
# quantities
#-------------------------------------------------
process = cms.Process("Jet")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    )
)
execfile("TopAnalysis/Configuration/analysis/firstCollisions/Source_Run132658_cff.py")

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

#-------------------------------------------------
# jet analysis
#-------------------------------------------------

## produce different jet collections
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *

process.softJets = selectedPatJets.clone(src = 'selectedPatJets',
                                         cut = 'pt > 10.'
                                         )

process.hardJets = selectedPatJets.clone(src = 'selectedPatJets',
                                         cut = 'pt > 30.'
                                         )

process.softGoodJets = selectedPatJets.clone(src = 'softJets',
                                             cut = '0.01 < emEnergyFraction &'
                                             'jetID.fHPD < 0.98 &'
                                             'jetID.n90Hits > 1'
                                             )

process.hardGoodJets = selectedPatJets.clone(src = 'hardJets',
                                             cut = '0.01 < emEnergyFraction &'
                                             'jetID.fHPD < 0.98 &'
                                             'jetID.n90Hits > 1'
                                             )

## analyze jets
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")

process.analyzeJetQuality_softJets     = process.analyzeJetQuality.clone(src = 'softJets')
process.analyzeJetQuality_hardJets     = process.analyzeJetQuality.clone(src = 'hardJets')
process.analyzeJetQuality_softGoodJets = process.analyzeJetQuality.clone(src = 'softGoodJets')
process.analyzeJetQuality_hardGoodJets = process.analyzeJetQuality.clone(src = 'hardGoodJets')

process.analyzeJetKinematics_softJets     = process.analyzeJetKinematics.clone(src = 'softJets')
process.analyzeJetKinematics_hardJets     = process.analyzeJetKinematics.clone(src = 'hardJets')
process.analyzeJetKinematics_softGoodJets = process.analyzeJetKinematics.clone(src = 'softGoodJets')
process.analyzeJetKinematics_hardGoodJets = process.analyzeJetKinematics.clone(src = 'hardGoodJets')

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJet_rec.root')
)

process.analyzeSoftJets = cms.Sequence(process.softJets *
                                       process.analyzeJetQuality_softJets *
                                       process.analyzeJetKinematics_softJets)
                                       
process.analyzeHardJets = cms.Sequence(process.hardJets *
                                       process.analyzeJetQuality_hardJets *
                                       process.analyzeJetKinematics_hardJets)

process.analyzeSoftGoodJets = cms.Sequence(process.softGoodJets *
                                           process.analyzeJetQuality_softGoodJets *
                                           process.analyzeJetKinematics_softGoodJets)

process.analyzeHardGoodJets = cms.Sequence(process.hardGoodJets *
                                           process.analyzeJetQuality_hardGoodJets *
                                           process.analyzeJetKinematics_hardGoodJets)

process.p1 = cms.Path(process.analyzeSoftJets +
                      process.analyzeHardJets +
                      process.analyzeSoftGoodJets +
                      process.analyzeHardGoodJets
                      )
