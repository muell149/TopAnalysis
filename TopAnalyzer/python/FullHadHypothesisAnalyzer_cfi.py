import FWCore.ParameterSet.Config as cms

#
# module to make simple analyses of top event hypothese
#

analyzeHypothesis = cms.EDAnalyzer("FullHadHypothesisAnalyzer",
    fullHadEvent = cms.InputTag("ttFullHadEvent"),
    hypoClassKey = cms.InputTag("ttFullHadHypKinFit","Key")
)
