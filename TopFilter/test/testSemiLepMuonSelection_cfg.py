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
    fileNames = cms.untracked.vstring(
    '/store/mc/Spring10/TTbarJets-madgraph/AODSIM/START3X_V26_S09-v1/0016/2CB76F28-9D47-DF11-959F-003048C693E4.root'
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START38_V7::All')

#-------------------------------------------------
# event selection
#-------------------------------------------------

## select events that were generated in the semileptonic muon channel
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff")
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = False

## apply realistic event selection
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")

#-------------------------------------------------
# pat configuration
#-------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

from PhysicsTools.PatAlgos.tools.coreTools import *
removeSpecificPATObjects(process,
                         ['Photons', 'Taus'],
                         outputInProcess=False)
removeCleaning(process,
               outputInProcess=False)

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run36xOn35xInput
run36xOn35xInput(process)

## add ak5GenJet
process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.JetProducers.ak5GenJets_cfi")
process.patDefaultSequence.replace(getattr(process,"patCandidates"),
                                   process.genParticlesForJets
                                   + getattr(process,"ak5GenJets")
                                   + getattr(process,"patCandidates"))

process.patJetCorrFactors.corrSample = 'Spring10'
process.patJetCorrFactors.sampleType = "ttbar"

#-------------------------------------------------
# the path
#-------------------------------------------------

process.p1 = cms.Path(process.makeGenEvt *
                      process.ttSemiLeptonicFilter *
                      process.hltMu9 *
                      process.patDefaultSequence *
                      process.semiLeptonicSelection *
                      process.semiLeptonicEvents
                      )
