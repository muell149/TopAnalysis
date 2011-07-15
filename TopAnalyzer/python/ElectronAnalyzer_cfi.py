import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzeElectrons = cms.EDAnalyzer("ElectronAnalyzer",

    # Source
    electrons = cms.InputTag("selectedPatElectrons"),
    jets  = cms.InputTag("selectedPatJets"),

    verbosity = cms.bool(False),
    # only muons from first to last index
    from_to = cms.vint32(0,1),
    weight = eventWeightInputTag
)

