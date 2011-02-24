import FWCore.ParameterSet.Config as cms

analyzeJets = cms.EDAnalyzer("JetAnalyzer",
    
    # Source   
    jets = cms.InputTag("selectedPatJets"),    

    # only jets from first to last index    
    from_to = cms.vint32(0,1),
)

