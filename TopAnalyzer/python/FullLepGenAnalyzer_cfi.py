import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzeFullLepGenEvent = cms.EDAnalyzer("FullLepGenAnalyzer",
    weight = eventWeightInputTag
)



