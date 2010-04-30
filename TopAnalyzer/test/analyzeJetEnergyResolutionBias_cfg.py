import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/mc/Spring10/TTbarJets-madgraph/AODSIM/START3X_V26_S09-v1/0016/2CB76F28-9D47-DF11-959F-003048C693E4.root'
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
