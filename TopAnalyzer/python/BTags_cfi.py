import FWCore.ParameterSet.Config as cms

analyzeBTags = cms.EDAnalyzer("BTagsAnalyzer",
    ## input collection                             
    src = cms.InputTag("selectedPatJets"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("None"),
    )
)



