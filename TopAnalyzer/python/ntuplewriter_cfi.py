import FWCore.ParameterSet.Config as cms
#from TopAnalysis.TopUtils.EventWeightPU_cfi import *

writeNTuple = cms.EDAnalyzer('NTupleWriter',
                       hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
                       FullLepEvent = cms.InputTag("ttFullLepEvent"),
                       src = cms.InputTag("genEvt"),
                       muons = cms.InputTag("muons"),
                       elecs = cms.InputTag("elecs"),
                       jets      = cms.InputTag("jets"),
                       met       = cms.InputTag("met"),
                       vertices  = cms.InputTag('offlinePrimaryVertices'),
                       weight    =  cms.InputTag('eventWeightPU', 'eventWeightPU'),
                       datatype  =  cms.InputTag("data"),
                       includeTrigger = cms.bool(False),
                       triggerResults = cms.InputTag('TriggerResults','','HLT'),
                       useLeadingJets  = cms.bool(False),
                       useBtagging     = cms.bool(True),
                       bAlgorithm      = cms.string("trackCountingHighEffBJetTags"),
                       bCut            = cms.double(1.7),
)

