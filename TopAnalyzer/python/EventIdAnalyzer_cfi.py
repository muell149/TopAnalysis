import FWCore.ParameterSet.Config as cms

#
# module to print event ID (run, lumi, event)
#
analyzeEventId = cms.EDAnalyzer("EventIdAnalyzer",
    verbose = cms.bool(False),
    textFileName = cms.string("")
)


