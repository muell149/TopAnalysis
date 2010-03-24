import FWCore.ParameterSet.Config as cms

filterTrigger        = cms.EDFilter("NewTriggerTestFilter",
      whichTrigger   = cms.string("QuadJet40"),
      useEventWeight = cms.bool(False),
      weight         = cms.InputTag("eventWeight")
)
