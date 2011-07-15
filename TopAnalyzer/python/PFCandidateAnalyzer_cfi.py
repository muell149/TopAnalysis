import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzePFCandidate = cms.EDAnalyzer("PFCandidateAnalyzer",

    # Source
    src = cms.InputTag("pfSelectedMuons"),

    verbosity = cms.bool(False),
    # only muons from first to last index
    from_to = cms.vint32(0,1),
    weight = eventWeightInputTag
)
