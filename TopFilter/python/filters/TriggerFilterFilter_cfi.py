import FWCore.ParameterSet.Config as cms

filterTriggerFilters = cms.EDFilter("TriggerFilterFilter",

                                   trigger_event   = cms.InputTag("patTriggerEvent"),
				   ## hltFilter to be filtered on
				   hltFilter = cms.string("hltEle25CaloIdVTTrkIdTCaloIsoTTrkIsoTTrackIsolFilter")
                                   )
