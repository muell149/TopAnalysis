import FWCore.ParameterSet.Config as cms

analyzeBTags = cms.EDAnalyzer("BTagsAnalyzer",
    ## input collection                             
    src = cms.InputTag("selectedPatJets"),
    ## event weight
    weight = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(False),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("None"),
    )
)



