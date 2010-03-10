import FWCore.ParameterSet.Config as cms

filterDiMuonMass = cms.EDAnalyzer("DiMuonMassFilter",

    ## sources
    muons = cms.InputTag("selectedPatMuons"),
    
    ## cuts on muon muon mass
    qcdCut = cms.double(20.),
    zCut   = cms.vdouble(76.,106.)
)


