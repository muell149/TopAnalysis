import FWCore.ParameterSet.Config as cms

filterMVADiscriminator = cms.EDFilter("MVADiscriminatorFilter",
    src     = cms.InputTag("mvaDisc","DiscSel"),
    minDisc = cms.double(-99999.0),
    maxDisc = cms.double( 99999.0)
)
