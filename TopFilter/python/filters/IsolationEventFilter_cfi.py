import FWCore.ParameterSet.Config as cms

## define basic event filters
filterMuonIsolation = cms.EDFilter("MuonIsolationEventFilter",
    input  = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),    
    useEventWeight = cms.bool(True),
    weight = cms.InputTag("eventWeight"), 
    cuts   = cms.PSet(
      type = cms.uint32 ( 0),
      mode = cms.uint32 ( 0),
      name = cms.string (''),
      min  = cms.vdouble(  ),
      max  = cms.vdouble(  )
    )     
)
