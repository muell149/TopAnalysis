import FWCore.ParameterSet.Config as cms

analyzeMuonPair = cms.EDAnalyzer("DimuonAnalyzer",
    # source
    muons = cms.InputTag("selectedPatMuons"),
    # invariant mass bins in which n_entries is counted
    massBins = cms.vdouble(0.0, 20.0, 76.0, 106.0),     
    # option to weight events
    useEventWeight = cms.bool(True),    
    # option to correct hist entries to log bin width
    correctToWidth = cms.bool(True)     
)


