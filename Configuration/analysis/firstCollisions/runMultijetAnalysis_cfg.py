import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for multijet analysis
#-------------------------------------------------
process = cms.Process("ANALYZE")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)
execfile("TopAnalysis/Configuration/analysis/firstCollisions/Source_GoodRuns_cff.py")
#execfile("TopAnalysis/Configuration/analysis/firstCollisions/Source_QCD30_cff.py")

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#-------------------------------------------------
# refine jet selection
#-------------------------------------------------

## select jets
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
process.goodJets = selectedPatJets.clone(src = 'selectedPatJets',
                                         cut =
                                         'abs(eta) < 2.4 & pt > 30. &'
                                         '0.01 < emEnergyFraction &'
                                         '0.99 > emEnergyFraction &'
                                         'jetID.fHPD < 0.98 &'
                                         'jetID.n90Hits > 1'
                                         )

## select events with good jets
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
process.countJets = countPatJets.clone(src = 'goodJets',
                                       minNumber = 2
                                       )

process.jetSelection = cms.Sequence(process.goodJets *
                                    process.countJets)

#-------------------------------------------------
# analyzer
#-------------------------------------------------

process.load("TopAnalysis.TopAnalyzer.EventBasicsAnalyzer_cfi")
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")

process.analyzeJetQuality   .src = 'goodJets'
process.analyzeJetKinematics.src = 'goodJets'

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeMultijet_new.root')
)

process.p1 = cms.Path(process.jetSelection *
                      process.analyzeEventBasics *
                      process.analyzeJetQuality *
                      process.analyzeJetKinematics
                      )
