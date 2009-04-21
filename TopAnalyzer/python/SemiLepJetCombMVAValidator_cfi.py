import FWCore.ParameterSet.Config as cms

validateSemiLepJetCombMVA = cms.EDAnalyzer("SemiLepJetCombMVAValidator",
    match = cms.InputTag("ttSemiLepJetPartonMatch"),
    combs = cms.InputTag("findTtSemiLepJetCombMVA"),
    discs = cms.InputTag("findTtSemiLepJetCombMVA","Discriminators")
)



