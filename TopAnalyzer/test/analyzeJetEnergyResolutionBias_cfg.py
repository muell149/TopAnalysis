import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_7TeV_AODSIM-v1/0008/EEF99041-6C9E-DE11-9254-00163E11249A.root'
     )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_3XY_V25::All')

process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.decaySubset.fillMode = "kME" # use the status 3 partons from the hard process (Matrix Element)
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttDecaySelection.allowedTopDecays.decayBranchA.electron = True
process.ttDecaySelection.allowedTopDecays.decayBranchA.muon     = True
process.ttDecaySelection.allowedTopDecays.decayBranchA.tau      = True

process.load("TopAnalysis.TopAnalyzer.JetEnergyResolutionBiasAnalyzer_cfi")
process.analyzeJetEnergyResolutionBias_p20 = process.analyzeJetEnergyResolutionBias.clone(resFact = 1.2)
process.analyzeJetEnergyResolutionBias_m20 = process.analyzeJetEnergyResolutionBias.clone(resFact = 0.8)
process.analyzeJetEnergyResolutionBias_off = process.analyzeJetEnergyResolutionBias.clone(resFact = 0.0)

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJetEnergyResolutionBias.root')
)

## end path   
process.p1 = cms.Path(process.makeGenEvt *
                      process.ttDecaySelection *
                      process.analyzeJetEnergyResolutionBias *
                      process.analyzeJetEnergyResolutionBias_p20 *
                      process.analyzeJetEnergyResolutionBias_m20 *
                      process.analyzeJetEnergyResolutionBias_off)
