import FWCore.ParameterSet.Config as cms
from PU_Eventweight_cfi import *

analyzeTrigger = cms.EDAnalyzer("TriggerAnalyzer",

    TriggerResults = cms.InputTag('TriggerResults','','HLT'),

    muons          = cms.InputTag('selectedPatMuons'),

    hltPaths      = cms.vstring(
        'HLT_DoubleMu6_v1',
        'HLT_DoubleMu7_v1',
        'HLT_Mu13_Mu8_v1', #only prompt reco >204/pb, not in MC
        'HLT_Mu17_Mu8_v1', #only prompt reco >204/pb, not in MC
        'HLT_Mu8_Ele17_CaloIdL_v1',
        'HLT_Mu8_Ele17_CaloIdL_v2', #v2 in MC, not in rereco
        'HLT_Mu17_Ele8_CaloIdL_v1',
        'HLT_Mu17_Ele8_CaloIdL_v2',
        'HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1',
        'HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2',
        'HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v1',
        'HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v2',
        'HLT_IsoMu17_v5',
        'HLT_IsoMu24_v1',
        'HLT_IsoMu30_v1',
    ),

    weight = eventWeightInputTag
)
