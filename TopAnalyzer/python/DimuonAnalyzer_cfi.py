import FWCore.ParameterSet.Config as cms

analyzeMuonPair = cms.EDAnalyzer("DimuonAnalyzer",
    # source
    muons = cms.InputTag("selectedLayer1Muons"),     
    # option to weight events
    useEventWeight = cms.bool(True),
    # bins of di-combined two muon isolation
    isoBins = cms.vdouble(0, 0.5, 0.6, 0.7, 0.9) 
)


