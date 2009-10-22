import FWCore.ParameterSet.Config as cms

analyzeMuonPair = cms.EDAnalyzer("DimuonAnalyzer",
    # source
    muons = cms.InputTag("selectedLayer1Muons"),     
    # option to weight events
    useEventWeight = cms.bool(True), 
)


