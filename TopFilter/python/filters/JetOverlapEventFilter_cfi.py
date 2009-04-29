import FWCore.ParameterSet.Config as cms

filterJetOverlapEvent = cms.EDFilter("JetOverlapEventFilter",
    src            = cms.InputTag("selectedLayer1Jets"),
    deltaR         = cms.double(0.6),
    useEventWeight = cms.bool(False),
    weight         = cms.InputTag("eventWeight")
)
