import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_AODSIM-v1/0024/068F7867-2C88-DE11-B3C2-001F29C9A5AE.root'
     )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V9::All')

process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.decaySubset.fillMode = "kME" # use the status 3 partons from the hard process (Matrix Element)
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttDecaySelection.allowedTopDecays.decayBranchA.electron = True
process.ttDecaySelection.allowedTopDecays.decayBranchA.muon     = True
# ??? process.ttDecaySelection.allowedTopDecays.decayBranchA.tau      = True
# ??? process.ttDecaySelection.restrictTauDecays = cms.PSet(leptonic = cms.bool(False))
# ??? process.ttDecaySelection.restrictTauDecays = cms.PSet(oneProng = cms.bool(False))
# ??? process.ttDecaySelection.restrictTauDecays = cms.PSet(threeProng = cms.bool(False))

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
