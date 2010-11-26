import FWCore.ParameterSet.Config as cms

filterTrigger = cms.EDFilter("TriggerFilter",

    TriggerResults = cms.InputTag('TriggerResults','','HLT'),

                     hltPaths  = cms.vstring('HLT_Mu9'),
                     vetoPaths = cms.vstring()

)
