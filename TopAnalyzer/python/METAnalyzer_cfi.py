import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzeMET = cms.EDAnalyzer("MetAnalyzer",

    # Source
    METs = cms.InputTag("patMETsPF"),
    weight = eventWeightInputTag
)

