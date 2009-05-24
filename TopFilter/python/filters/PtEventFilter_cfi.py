import FWCore.ParameterSet.Config as cms

## define basic event filter
ptEventFilter = cms.EDFilter("PtEventFilter",
    ## input collection
    input  = cms.VInputTag(''),
    ## use event weight or not
    useEventWeight = cms.bool(True),
    ## input tag for event weight
    weight = cms.InputTag("eventWeight"),

    ## cut definition
    cuts   = cms.PSet(
      ## the follwoing modes are available:
      ##  0 : for any input object
      ##  1 : for at least one input objects
      mode = cms.uint32 ( 0),
      ## cut name
      name = cms.string (''),
      ## cut minimum
      min  = cms.vdouble(  ),
      ## cut maximum
      max  = cms.vdouble(  )
    )
)
