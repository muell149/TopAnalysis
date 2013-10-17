import FWCore.ParameterSet.Config as cms

analyzeGenLevelBJets = cms.EDAnalyzer("GenLevelBJetAnalyzer",
    ttGenEvent = cms.InputTag('genEvt'),
    genJets = cms.InputTag('ak5GenJetsPlusHadron','','SIM'),   
    deltaR = cms.double(0.5),
    flavour = cms.int32(5),
    resolveParticleName = cms.bool(False),
    requireTopBquark = cms.bool(False),
    noBBbarResonances = cms.bool(True),
    doImprovedHadronMatching = cms.bool(False),
    doValidationPlotsForImprovedHadronMatching = cms.bool(True)
)



