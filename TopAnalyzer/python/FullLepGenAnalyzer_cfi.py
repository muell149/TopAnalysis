import FWCore.ParameterSet.Config as cms
from DileptonEventWeight_cfi import *

analyzeFullLepGenEvent = cms.EDAnalyzer("FullLepGenAnalyzer",
   # src = cms.InputTag("genParticles"), ##pythia
    src = cms.InputTag("genEvt"),       ##herwig
    weightPU     = eventWeightPUTag,
    weightLepSF  = eventWeightLepSFTag 
)



