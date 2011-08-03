import FWCore.ParameterSet.Config as cms

eventIDPrinter = cms.EDAnalyzer("EventIDPrinter",
    outputString = cms.string(''),
    runOnMC = cms.bool(False),
    showDetails = cms.bool(False),
    elecs = cms.InputTag("selectedPatElectrons"),
    muons = cms.InputTag("selectedPatMuons"),
    jets = cms.InputTag("selectedPatJets"),
    jecLevel = cms.string(''), #empty string = default jec level
    mets = cms.InputTag("pfMET")
)



