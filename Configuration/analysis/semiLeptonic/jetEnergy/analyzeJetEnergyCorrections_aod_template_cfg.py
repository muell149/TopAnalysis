import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of jet energy corrections
#-------------------------------------------------
process = cms.Process("JetEnergyCorrections")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.categories.append('JetPartonMatching')
process.MessageLogger.cerr.TtSemiLeptonicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)
process.MessageLogger.cerr.JetPartonMatching = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)
execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/Source_10TeV_cff.py")

## define maximal number of events to loop over
## ----------------------
## 50/pb at  7 TeV :  8,250
## 50/pb at 10 TeV : 20,750
## ----------------------
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V3::All')

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
from TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff import disableCountFilter
disableCountFilter(process.bottomJetSelection)

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

from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process, 
                    cms.InputTag('antikt5CaloJets'),   
                    doJTA            = True,            
                    doBTagging       = True,            
                    jetCorrLabel     = ('AK5','Calo'),  
                    doType1MET       = True,
                    genJetCollection = cms.InputTag("antikt5GenJets"),
                    doJetID          = False,
                    jetIdLabel       = "antikt5"
                    )

## choose sample type for flavor dependent JEC
process.jetCorrFactors.sampleType = "ttbar" ## dijet or ttbar

#-------------------------------------------------
# top analysis
#-------------------------------------------------

## analyze jet energy corrections
process.load("TopAnalysis.TopAnalyzer.JetEnergyCorrectionsAnalyzer_cff")

## printout for debugging
process.ttSemiLepJetPartonMatch   .verbosity = 1
process.ttSemiLepGenJetPartonMatch.verbosity = 1
process.ttSemiLepEventRaw         .verbosity = 1
#process.ttSemiLepEventOff         .verbosity = 1
#process.ttSemiLepEventRel         .verbosity = 1
#process.ttSemiLepEventAbs         .verbosity = 1
#process.ttSemiLepEventEmf         .verbosity = 1
#process.ttSemiLepEventHad         .verbosity = 1
#process.ttSemiLepEventUe          .verbosity = 1
#process.ttSemiLepEventPart        .verbosity = 1

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeJetEnergyCorrections.root')
)

process.p1 = cms.Path(process.makeGenEvt *
                      process.ttSemiLeptonicFilter *
                      process.hltMu9 *
                      process.patDefaultSequence *
                      process.semiLeptonicSelection *
                      process.semiLeptonicEvents *
                      process.makeJetEnergyCorrectionsAnalysis
                      )
