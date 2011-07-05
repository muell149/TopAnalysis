import FWCore.ParameterSet.Config as cms

analyzeMuons = cms.EDAnalyzer("MuonAnalyzer",

    # Source
    muons = cms.InputTag("selectedPatMuons"),
    jets  = cms.InputTag("hardJets"),

    verbosity = cms.bool(False),
    # only muons from first to last index
    from_to = cms.vint32(0,1),
    weight = cms.InputTag('eventWeightPU')
)
