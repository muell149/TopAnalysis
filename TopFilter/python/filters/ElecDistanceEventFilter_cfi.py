import FWCore.ParameterSet.Config as cms

## define basic event filters
filterElecJetDistance = cms.EDFilter("ElecDistanceEventFilter",
    input  = cms.VInputTag(cms.InputTag("selectedPatElectrons")),
    useEventWeight = cms.bool(True),
    weight = cms.InputTag("eventWeight"), 
    cuts    = cms.PSet(
      refs  = cms.InputTag("selectedPatJets"),
      thresh= cms.vdouble( 0),
      mode  = cms.uint32 ( 0),
      name  = cms.string ('ElecDistanceEventFilter'),
      min   = cms.vdouble(  ),
      max   = cms.vdouble(  )
    )    
)
