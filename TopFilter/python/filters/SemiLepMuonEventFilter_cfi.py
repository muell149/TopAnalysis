import FWCore.ParameterSet.Config as cms

## define basic event filter
filterSemiLepMuonEvent = cms.EDFilter("SemiLepMuonEventFilter",
    weight  = cms.InputTag("eventWeight"),
    leptons = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),
    jets    = cms.VInputTag(cms.InputTag("selectedLayer1Jets")),

    ## selection switches                                      
    lepEta = cms.bool(True),
    lepPt  = cms.bool(True),
    jetEta = cms.bool(True),
    jetPt  = cms.bool(True),                                      
    trkIso = cms.bool(True),
    calIso = cms.bool(True),
    jetDist= cms.bool(True),

    ## predefine selection structure
    lepEtaFilter = cms.PSet(
      weight = cms.InputTag("eventWeight"),
      input  = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),
      cuts   = cms.PSet(
        mode = cms.uint32 ( 0),
        name = cms.string (''),
        min  = cms.vdouble(  ),
        max  = cms.vdouble(  )
      )              
    ),
    lepPtFilter = cms.PSet(
      weight = cms.InputTag("eventWeight"),
      input  = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),
      cuts   = cms.PSet(
        mode = cms.uint32 ( 0),
        name = cms.string (''),
        min  = cms.vdouble(  ),
        max  = cms.vdouble(  )
      )              
    ),
    jetEtaFilter = cms.PSet(
      weight = cms.InputTag("eventWeight"),
      input  = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),
      cuts   = cms.PSet(
        mode = cms.uint32 ( 0),
        name = cms.string (''),
        min  = cms.vdouble(  ),
        max  = cms.vdouble(  )
      )              
    ),
    jetPtFilter = cms.PSet(
      weight = cms.InputTag("eventWeight"),
      input  = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),
      cuts   = cms.PSet(
        mode = cms.uint32 ( 0),
        name = cms.string (''),
        min  = cms.vdouble(  ),
        max  = cms.vdouble(  )
      )              
    ),
    trkIsoFilter = cms.PSet(
      weight = cms.InputTag("eventWeight"),
      input  = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),
      cuts   = cms.PSet(
        type = cms.uint32 ( 0),
        mode = cms.uint32 ( 0),
        name = cms.string (''),
        min  = cms.vdouble(  ),
        max  = cms.vdouble(  )
      )     
    ),
    calIsoFilter = cms.PSet(
      weight = cms.InputTag("eventWeight"),
      input  = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),
      cuts   = cms.PSet(
        type = cms.uint32 ( 0),
        mode = cms.uint32 ( 0),
        name = cms.string (''),
        min  = cms.vdouble(  ),
        max  = cms.vdouble(  )
      )     
    ),
    jetDistFilter = cms.PSet(
      weight = cms.InputTag("eventWeight"),
      input  = cms.VInputTag(cms.InputTag("selectedLayer1Muons")),
      cuts   = cms.PSet(
        refs = cms.VInputTag(cms.InputTag("selectedLayer1Jets")),
        thres= cms.double( 0),
        mode = cms.uint32( 0),
        name = cms.string (''),
        min  = cms.vdouble(  ),
        max  = cms.vdouble(  )
      )    
    )
)


