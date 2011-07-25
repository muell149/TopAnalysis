import FWCore.ParameterSet.Config as cms

eventIDPrinter = cms.EDAnalyzer("EventIDPrinter",
    outputString = cms.string(''),
    runOnMC = cms.bool(False)
)



