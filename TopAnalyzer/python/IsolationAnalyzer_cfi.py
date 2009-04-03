import FWCore.ParameterSet.Config as cms

analyzeisolationMET = cms.EDAnalyzer("IsolationAnalyzer",
    ptBins = cms.vdouble(0.0, 80.0, 170.0, 250.0, 9999.0),
    hist = cms.string('Isolation.hist'),
    modulename = cms.string('makeMVA'),
    missingEt = cms.InputTag("selectedLayer1METs"),
    ttbarMC = cms.bool(False),
    jets = cms.InputTag("selectedLayer1Jets"),
    muons = cms.InputTag("selectedLayer1Muons"),
    genEvent = cms.InputTag("genEvt"),
    discriminator = cms.string('DiscSel'),
    useMVA = cms.bool(False)
)



