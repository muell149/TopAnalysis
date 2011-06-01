import FWCore.ParameterSet.Config as cms

filterLeptonPair = cms.EDFilter("DiLeptonFilter",

    ## sources
    muons = cms.InputTag("selectedPatMuons"),
    elecs = cms.InputTag("cleanPatElectrons"),

    ## determine if given mass window is to be
    ## selected (False) or vetoed (True)
    isVeto = cms.bool(True),
    
    ## cuts on muon muon mass
    Cut   = cms.vdouble(81.,101.),
    
    ## filter on charge of muon pair
    ## -1 for unlike, 1 for like sign
    ## 0: no filter
    filterCharge = cms.int32(0)

)
