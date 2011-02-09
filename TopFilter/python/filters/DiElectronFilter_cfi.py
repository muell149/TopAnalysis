import FWCore.ParameterSet.Config as cms

filterElectronPair = cms.EDFilter("DiElectronFilter",

    ## sources
    electrons = cms.InputTag("selectedPatElectrons"),
    
    ## determine if given mass window is to be 
    ## selected (False) or vetoed (True)
    isVeto = cms.bool(True),
    
    ## cuts on muon muon mass
    Cut   = cms.vdouble(76.,106.),
    
    ## filter on charge of muon pair
    ## -1 for unlike, 1 for like sign
    ## 0: no filter
    filterCharge = cms.int32(0)    
)


