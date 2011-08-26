import FWCore.ParameterSet.Config as cms
from DileptonEventWeight_cfi import *

analyzeJets = cms.EDAnalyzer("JetAnalyzer",

    # Source
    jets = cms.InputTag("selectedPatJets"),

    # only jets from first to last index
    from_to = cms.vint32(0,1),
    
    weightPU     = eventWeightPUTag,
    weightLepSF  = eventWeightLepSFTag 
)

