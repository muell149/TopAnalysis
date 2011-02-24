import FWCore.ParameterSet.Config as cms

analyzeElectronNtuple = cms.EDAnalyzer("ElectronNtupleAnalyzer",
    
    # Source   
    electrons = cms.InputTag("selectedPatElectrons"),     
    jets  = cms.InputTag("selectedPatJets"),
    mets  = cms.InputTag("patMETsPF"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")                           
)

