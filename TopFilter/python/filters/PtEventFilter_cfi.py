import FWCore.ParameterSet.Config as cms

## define basic event filters
filterElecPt = cms.EDFilter("PtEventFilter",
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

filterMuonPt = cms.EDFilter("PtEventFilter",
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

filterJetsPt = cms.EDFilter("PtEventFilter",
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
