import FWCore.ParameterSet.Config as cms

filterSemiLeptonicGenPhaseSpace = cms.EDFilter("SemiLeptonicGenPhaseSpaceFilter",
    ## ttGenEvent as input
    src            = cms.InputTag("genEvt"),
    ## cuts on the kinematics of the top decay products
    leptonMinPt    = cms.double(30.),
    leptonMaxEta   = cms.double(2.1),
    partonMinPt    = cms.double(30.),
    partonMaxEta   = cms.double(2.4),
    ## cuts on the kinematics of the tops
    topMinPt       = cms.double(0.), 
    topMaxPt       = cms.double(99999.),
    topMaxY        = cms.double(99999.),
    ## cuts on the kinematics of the ttbar system
    ttbarMinPt     = cms.double(0.), 
    ttbarMaxPt     = cms.double(99999.),
    ttbarMaxY      = cms.double(99999.),
    ## decide on which level cuts shall be made (combination possible)
    decayLevelCuts = cms.bool(True),
    topLevelCuts   = cms.bool(False),
    ttbarLevelCuts = cms.bool(False)
)
