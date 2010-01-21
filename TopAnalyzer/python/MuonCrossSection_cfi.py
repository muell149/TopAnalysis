import FWCore.ParameterSet.Config as cms

analyzeMuonCrossSection = cms.EDAnalyzer("MuonCrossSectionAnalyzer",
    ## input collection                             
    src = cms.InputTag("selectedLayer1Muons"),
    ## event weight
    weight = cms.InputTag("eventWeight"),
    ## use the weight or not                             
    useWeight = cms.bool(False),
)



