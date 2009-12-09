import FWCore.ParameterSet.Config as cms

filterTrigger = cms.EDAnalyzer("TriggerFilter",

    TriggerResults = cms.InputTag('TriggerResults','','HLT'),
    hltPaths_L3    = cms.vstring('HLT_Mu5','HLT_IsoMu9','HLT_Mu11','HLT_Mu15','HLT_DoubleMu3')
)




