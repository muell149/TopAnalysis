import FWCore.ParameterSet.Config as cms

analyzeEventBasics = cms.EDAnalyzer("EventBasicsAnalyzer",
    vertex = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("generalTracks"),
    met    = cms.InputTag("patMETs")
)
