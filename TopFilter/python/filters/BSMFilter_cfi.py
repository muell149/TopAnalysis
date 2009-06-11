import FWCore.ParameterSet.Config as cms

filterMET = cms.EDFilter("PtEventFilter",
    input  = cms.VInputTag(cms.InputTag("selectedLayer1METs")),
    useEventWeight = cms.bool(True),
    weight = cms.InputTag("eventWeight"),    
    cuts   = cms.PSet(
      mode = cms.uint32 ( 0),
      name = cms.string (''),
      min  = cms.vdouble(  ),
      max  = cms.vdouble(  )
    ) 
)

filterJetsnr = cms.EDFilter("PtEventFilter",
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

filterDiMuonMass = cms.EDFilter("DiMuonMassFilter",
                                  muons = cms.InputTag("selectedLayer1Muons")
                                  )
