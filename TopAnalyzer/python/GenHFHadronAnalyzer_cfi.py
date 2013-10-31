import FWCore.ParameterSet.Config as cms

analyzeGenHFHadron = cms.EDAnalyzer("GenHFHadronAnalyzer",
    ttGenEvent = cms.InputTag('genEvt'),
    genJets = cms.InputTag('ak5GenJetsPlusHadron','','SIM'),   
    flavour = cms.int32(5),
    onlyJetClusteredHadrons = cms.bool(False),
    noBBbarResonances = cms.bool(True),
    doValidationPlotsForImprovedHadronMatching = cms.bool(True)
)



