import FWCore.ParameterSet.Config as cms

filterDiMuonMass = cms.EDFilter("DiMuonMassFilter",

    ## sources
    muons = cms.InputTag("selectedPatMuons"),
    
    ## determine if given mass window is to be 
    ## selected (False) or vetoed (True)
    isVeto = cms.bool(True),
    
    ## cuts on muon muon mass
    Cut   = cms.vdouble(76.,106.)
)


