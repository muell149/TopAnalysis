import FWCore.ParameterSet.Config as cms

## define basic event filters
filterMuonJetDistance = cms.EDFilter("MuonDistanceEventFilter",
    input  = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),    
    useEventWeight = cms.bool(True),
    weight = cms.InputTag("eventWeight"), 
    cuts    = cms.PSet(
      refs  = cms.InputTag("selectedLayer1Jets"),
      thresh= cms.vdouble( 0),
      mode  = cms.uint32 ( 0),
      name  = cms.string ('MuonDistanceEventFilter'),
      min   = cms.vdouble(  ),
      max   = cms.vdouble(  )
    )    
)
