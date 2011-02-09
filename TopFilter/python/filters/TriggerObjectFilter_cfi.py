import FWCore.ParameterSet.Config as cms

filterTriggerObject = cms.EDFilter("TriggerObjectFilter",

                                   trigger_event   = cms.InputTag("patTriggerEvent"),
                                   hltPath = cms.string('HLT_Ele10_SW_L1R'),
                                   nMin  = cms.uint32(1),
                                   ptMin = cms.double(0),
                                   etMin = cms.double(0)
                                   )
