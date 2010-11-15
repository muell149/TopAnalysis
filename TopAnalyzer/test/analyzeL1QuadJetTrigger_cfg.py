import FWCore.ParameterSet.Config as cms

## ---
##   use this file to test the L1QuadJetTriggerAnalyzer.cc module
## ---


# set sequence shortcut
process = cms.Process("L1QuadJetTriggerAnalysis")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## define input
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_1_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_2_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_3_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_4_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_5_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_6_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_7_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_8_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_9_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_10_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_11_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_12_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_13_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_14_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_15_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_16_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_17_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_18_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_19_1.root',
    '/store/user/henderle/Spring10/TTbar_NLO/PATtuple_20_1.root'
    ),
    skipEvents = cms.untracked.uint32(0)
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeL1QuadJetTrigger_test.root')
)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_36Y_V10::All')

## ---
##    load Pat Trigger Event
## ---
process.load("TopAnalysis.TopUtils.patTriggerEvent_cff")
process.patTrigger.processName = cms.string('REDIGI')

## ---
##    load L1QuadJetTriggerAnalyzer
## ---
process.load("TopAnalysis.TopAnalyzer.L1QuadJetTriggerAnalyzer_cfi")
process.analyzeL1QuadJetTriggerLoose = process.analyzeL1QuadJetTrigger.clone()
process.analyzeL1QuadJetTriggerTight = process.analyzeL1QuadJetTrigger.clone()

## ---
##    configure event selection
## ---
## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for fully hadronic ttbar
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

## jet collection creation and selection
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi")
## create loose PFJets
process.looseLeadingJets = process.selectedPatJets.clone(src = 'selectedPatJetsAK5PF',
                                                         cut = 'abs(eta) < 2.4 & pt > 30.   &'
                                                               'chargedHadronEnergyFraction > 0.0 &'
                                                               'neutralHadronEnergyFraction/corrFactor("raw") < 0.99 &'
                                                               'chargedEmEnergyFraction/corrFactor("raw")     < 0.99 &'
                                                               'neutralEmEnergyFraction/corrFactor("raw")     < 0.99 &'
                                                               'chargedMultiplicity > 0 &'
                                                               'nConstituents > 1'
                                                         )
## create tight PFJets
process.tightLeadingJets = process.selectedPatJets.clone(src = 'looseLeadingJets',
                                                         cut = 'abs(eta) < 2.4 & pt > 40.   &'
                                                               'chargedHadronEnergyFraction > 0.0 &'
                                                               'neutralHadronEnergyFraction/corrFactor("raw") < 0.9  &'
                                                               'chargedEmEnergyFraction/corrFactor("raw")     < 0.99 &'
                                                               'neutralEmEnergyFraction/corrFactor("raw")     < 0.9  &'
                                                               'chargedMultiplicity > 0 &'
                                                               'nConstituents > 1'
                                                         )
## select all events with at least 6 jets
process.looseLeadingJetSelection = process.countPatJets.clone(src = 'looseLeadingJets',
                                                              minNumber = 6
                                                              )
process.tightLeadingJetSelection = process.countPatJets.clone(src = 'tightLeadingJets',
                                                              minNumber = 6
                                                              )

## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
    ## do genEvent selection
    process.makeGenEvt                   *
    process.ttFullHadronicFilter         *
    ## do loose jet selection
    process.looseLeadingJets             *
    process.looseLeadingJetSelection     *
    ## apply the analyzer for loose jets
    process.patTriggerSequence           *
    process.analyzeL1QuadJetTriggerLoose *
    ## do tight jet selection
    process.tightLeadingJets             *
    process.tightLeadingJetSelection     *
    ## apply the analyzer tight jets
    process.analyzeL1QuadJetTriggerTight
    )
