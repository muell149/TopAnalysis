import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for the selection of semileptonic
# ttbar events with a muon in the final state
#-------------------------------------------------
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/mc/Summer09/TTbar/AODSIM/MC_31X_V3_7TeV_AODSIM-v1/0005/6CA57A3D-EB9C-DE11-B3DB-002481DE4A28.root'
    ),
    skipEvents = cms.untracked.uint32(0)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",  
            fileName = cms.string('analyzeFullHadronicSelection_test.root')
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_3XY_V25::All')

#-------------------------------------------------
# event selection
#-------------------------------------------------

## select events that were generated in the fully hadronic channel
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for full-hadronic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

## apply realistic event selection
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")

## do kinFit of events needed for selection cuts
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *

addTtFullHadHypotheses(process,
                       ["kKinFit"]
                       )

removeTtFullHadHypGenMatch(process)

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

process.patJetCorrFactors.corrSample = 'Summer09_7TeV'
process.patJetCorrFactors.sampleType = "ttbar"

#-------------------------------------------------
# the path
#-------------------------------------------------

process.p1 = cms.Path(process.makeGenEvt *
                      process.ttFullHadronicFilter *
                      process.hltHt200 *
                      process.patDefaultSequence *
                      process.analyseFullHadronicSelection
                      )
