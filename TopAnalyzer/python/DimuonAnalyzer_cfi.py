import FWCore.ParameterSet.Config as cms

analyzeMuonPair = cms.EDAnalyzer("DimuonAnalyzer",
    # source
    muons = cms.InputTag("selectedPatMuons"),     
    # option to weight events
    useEventWeight = cms.bool(True),    
)


