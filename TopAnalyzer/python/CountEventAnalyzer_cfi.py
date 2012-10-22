import FWCore.ParameterSet.Config as cms

#
# module to print event ID (run, lumi, event)
#
countEvents = cms.EDAnalyzer("CountEventAnalyzer",
    includePDFWeights = cms.bool(False),
    pdfWeights = cms.InputTag(""),
)


