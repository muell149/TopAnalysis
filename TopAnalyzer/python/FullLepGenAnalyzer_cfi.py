import FWCore.ParameterSet.Config as cms
from DileptonEventWeight_cfi import *

analyzeFullLepGenEvent = cms.EDAnalyzer("FullLepGenAnalyzer",
    src = cms.InputTag("genEvt"),      
    weightPU     = eventWeightPUTag,
    weightLepSF  = cms.InputTag("") 
)
