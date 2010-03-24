import FWCore.ParameterSet.Config as cms

## ---
##   use this file to test the TriggerEfficiency.cc module
## ---


# set sequence shortcut
process = cms.Process("TriggerEfficiency")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1

## define input
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_1.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_2.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_3.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_4.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_5.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_6.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_7.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_8.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_9.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_10.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_11.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_12.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_13.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_14.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_15.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_16.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_17.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_18.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_19.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_20.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_21.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_22.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_23.root',
    '/store/user/eschliec/Summer09/7TeV/TTBar/MCatNLO/patTuple_24.root'
    )
 )

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeTriggerEfficiency_test.root')
)

## ---
##    load tt full-hadronic filter
## ---

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for full-hadronic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

## ---
##    load trigger efficiency analyzer
## ---

## get trigger efficiency
process.load("TopAnalysis.TopAnalyzer.TriggerEfficiency_cfi")
process.analyzeTriggerEfficiency = process.analyzeTriggerEfficiency.clone()

## ---
##    run the final sequence
## ---

process.p1 = cms.Path(
    ## apply the filter
    process.makeGenEvt *
    process.ttFullHadronicFilter *
    ## apply the analyzer
    process.analyzeTriggerEfficiency          
    )
