import FWCore.ParameterSet.Config as cms

analyzeJetEnergyCorrections = cms.EDAnalyzer("JetEnergyCorrectionsAnalyzer",
    ## ttSemiLeptonicEvent
    semiLepEvt     = cms.InputTag("ttSemiLepEvent"),
    ## hypothesis key
    hypoKey        = cms.string("kGenMatch"),
    ## genJets plus matching to partons
    genJets        = cms.InputTag("ak5GenJets"),
    genJetMatching = cms.InputTag("ttSemiLepGenJetPartonMatch")
)



