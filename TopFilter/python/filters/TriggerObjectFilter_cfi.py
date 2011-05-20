import FWCore.ParameterSet.Config as cms

filterTriggerObject = cms.EDFilter("TriggerObjectFilter",

                                   trigger_event   = cms.InputTag("patTriggerEvent"),
				   ## if trigger path is only given as a normal string,
				   ## it is converted to the vector;
                                   ## if trigger path is given as string vector hltPaths, 
                                   ## the normal string hltPath is ignored
				   hltPath = cms.string('HLT_Ele10_SW_L1R'),
                                   hltPaths = cms.vstring(),
                                   nMin  = cms.uint32(1),
                                   ptMin = cms.double(0),
                                   etMin = cms.double(0)
                                   )
