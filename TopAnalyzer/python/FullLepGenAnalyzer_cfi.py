import FWCore.ParameterSet.Config as cms
from DileptonEventWeight_cfi import *

analyzeFullLepGenEvent = cms.EDAnalyzer("FullLepGenAnalyzer",
    weightPU     = eventWeightPUTag,
    weightLepSF  = eventWeightLepSFTag 
)



