import FWCore.ParameterSet.Config as cms

filterMuonPair = cms.EDFilter("DiMuonFilter",

    ## sources
    muons = cms.InputTag("selectedPatMuons"),

    ## filter on charge of muon pair
    ## -1 for unlike, 1 for like sign
    ## 0: no filter
    filterCharge = cms.int32(0),
                              
    ## filter on mass of muon pair           
    filterMass = cms.bool(True),

    ## cuts on muon muon mass
    Cut   = cms.vdouble(76.,106.),

    ## determine if events are to be 
    ## selected (False) or vetoed (True)
    isVeto = cms.bool(False)
                              
)


