import FWCore.ParameterSet.Config as cms

writeTemplateTree = cms.EDAnalyzer("TemplateTreeWriter",

    MET      = cms.InputTag('patMETs'),
    muons    = cms.InputTag('selectedPatMuons'),
    allMuons = cms.InputTag('selectedPatMuons'),                            
)
