import FWCore.ParameterSet.Config as cms

## define basic event filters
filterElecEta = cms.EDFilter("EtaEventFilter",
    input  = cms.VInputTag(cms.InputTag("selectedLayer1Electrons")),
    useEventWeight = cms.bool(True),    
    weight = cms.InputTag("eventWeight"),
    cuts   = cms.PSet(
      mode = cms.uint32 ( 0),
      name = cms.string (''),
      min  = cms.vdouble(  ),
      max  = cms.vdouble(  )
    )                               
)

filterMuonEta = cms.EDFilter("EtaEventFilter",
    input  = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),    
    useEventWeight = cms.bool(True),
    weight = cms.InputTag("eventWeight"),        
    cuts   = cms.PSet(
      mode = cms.uint32 ( 0),
      name = cms.string (''),
      min  = cms.vdouble(  ),
      max  = cms.vdouble(  )
    )                               
)

filterJetsEta = cms.EDFilter("EtaEventFilter",
    input  = cms.VInputTag(cms.InputTag("selectedLayer1Jets")),
    useEventWeight = cms.bool(True),
    weight = cms.InputTag("eventWeight"),
    cuts   = cms.PSet(
      mode = cms.uint32 ( 0),
      name = cms.string (''),
      min  = cms.vdouble(  ),
      max  = cms.vdouble(  )
    ) 
)
