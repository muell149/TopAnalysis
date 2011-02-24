import FWCore.ParameterSet.Config as cms

analyzeElectronPair = cms.EDAnalyzer("DiElectronAnalyzer",
    # source
    electrons = cms.InputTag("selectedPatElectrons"),
    # invariant mass bins in which n_entries is counted
    massBins = cms.vdouble(0.0, 12.0, 76.0, 106.0),     
    # option to weight events
    useEventWeight = cms.bool(False),    
    # option to correct hist entries to log bin width
    correctToWidth = cms.bool(True)     
)


