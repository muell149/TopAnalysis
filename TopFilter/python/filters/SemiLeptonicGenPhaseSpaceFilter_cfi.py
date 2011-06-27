import FWCore.ParameterSet.Config as cms

filterSemiLeptonicGenPhaseSpace = cms.EDFilter("SemiLeptonicGenPhaseSpaceFilter",
    src          = cms.InputTag("genEvt"),
    leptonMinPt  = cms.double(30.),
    leptonMaxEta = cms.double(2.1),
    partonMinPt  = cms.double(30.),
    partonMaxEta = cms.double(2.4)
)