import FWCore.ParameterSet.Config as cms

analyzeTrigger = cms.EDAnalyzer("TriggerAnalyzer",

    TriggerResults = cms.InputTag('TriggerResults','','HLT'),
    #hltPaths_L3    = cms.vstring('HLT_IsoMu9','HLT_Mu5','HLT_Mu9','HLT_Mu11','HLT_Mu15','HLT_DoubleMu0','HLT_DoubleMu3')
    hltPaths_L3    = cms.vstring('HLT_Mu5','HLT_IsoMu9','HLT_Mu11','HLT_Mu15','HLT_DoubleMu3')
)




