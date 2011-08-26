import FWCore.ParameterSet.Config as cms
from DileptonEventWeight_cfi import *

analyzeMET = cms.EDAnalyzer("MetAnalyzer",

    # Source
    METs = cms.InputTag("patMETsPF"),
    weightPU     = eventWeightPUTag,
    weightLepSF  = eventWeightLepSFTag
)

