import FWCore.ParameterSet.Config as cms

filterEventShape = cms.EDFilter("EventShapeFilter",
    src            = cms.InputTag("selectedLayer1Jets"),
    maxIsotropy    = cms.double(1.0),
    minIsotropy    = cms.double(0.0),
    maxCircularity = cms.double(1.0),
    minCircularity = cms.double(0.0),
    maxSphericity  = cms.double(1.0),
    minSphericity  = cms.double(0.0),
    maxAplanarity  = cms.double(1.0),
    minAplanarity  = cms.double(0.0),
    maxC           = cms.double(1.0),
    minC           = cms.double(0.0),
    maxD           = cms.double(1.0),
    minD           = cms.double(0.0),
    useEventWeight = cms.bool(False),
    weight         = cms.InputTag("eventWeight")
)
