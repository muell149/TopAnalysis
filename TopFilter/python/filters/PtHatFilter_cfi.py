import FWCore.ParameterSet.Config as cms

filterPtHat        = cms.EDFilter("PtHatFilter",
    minPtHat       = cms.double(0.0),
    maxPtHat       = cms.double(999999.0),
    useEventWeight = cms.bool(False),
    weight         = cms.InputTag("eventWeight")
)
