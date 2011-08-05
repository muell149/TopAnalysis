import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzeDiLeptons = cms.EDAnalyzer("DiLeptonObjAnalyzer",

    fileOutput = cms.bool(False),
    outputFile = cms.untracked.string('DiLeptonObjEvents.txt'),
    ###
    dileptons   = cms.InputTag('mergedDileptons'),
    jets        = cms.InputTag('goodIdJetsPF'),
    ###
    onlyfirst   = cms.bool(True),

    weight = eventWeightInputTag
)
