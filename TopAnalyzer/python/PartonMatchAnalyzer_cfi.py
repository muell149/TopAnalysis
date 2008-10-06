import FWCore.ParameterSet.Config as cms

analyzePartonMatch = cms.EDAnalyzer("PartonMatchAnalyzer",
    hist    = cms.string('analyzePartonMatch.hist'),
    matches = cms.VInputTag(cms.InputTag("ttSemiEvtJetPartonMatch")),
    sumDR   = cms.InputTag("ttSemiEvtJetPartonMatch","SumDR"),
    sumDPt  = cms.InputTag("ttSemiEvtJetPartonMatch","SumPt"),
    quarks  = cms.vint32(),
    jets    = cms.vint32(),
    ref     = cms.uint32(0)
)


